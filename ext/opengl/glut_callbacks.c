#include "common.h"

/* HACK experimental API */
void *rb_thread_call_with_gvl(void *(*func)(void *), void *data1);

static ID call_id; /* 'call' method id */
static VALUE idle_func = Qnil;
static VALUE joystick_func = Qnil;
static VALUE menustate_func = Qnil;
static VALUE menustatus_func = Qnil;
static VALUE timer_func = Qnil;

typedef void *(*gvl_call)(void *);

struct callback_args {
	union {
		int button;
		int dial;
		int special;
		int state;
		int value;
		int width;
		int x;
		unsigned char key;
		unsigned int button_mask;
	} arg0;
	union {
		int height;
		int state;
		int value;
		int x;
		int y;
	} arg1;
	union {
		int x;
		int y;
		int z;
	} arg2;
	union {
		int y;
		int z;
	} arg3;
} ;

static struct callback_args *
alloc_callback_args(void) {
	struct callback_args *args;
	args = (struct callback_args *)malloc(sizeof(struct callback_args));

	if (args == NULL) {
		fprintf(stderr, "[BUG] out of memory in opengl callback");
		abort();
	}

	return args;
}

/*
 * macros for registering callbacks -
 *
 * most GLUT callback functions are part of specific window state, so
 * the same callback may have different functions for each GLUT window
 *
 * callbacks that are not tied to specific window (idle,timer,menustate) are
 * registered manually
 */

#define WINDOW_CALLBACK_SETUP(_funcname)                                   \
static VALUE _funcname = Qnil;                                             \
static VALUE                                                               \
glut_ ## _funcname(VALUE self, VALUE callback)                             \
{                                                                          \
	int win = glutGetWindow();                                               \
																																					 \
	if (win == 0) {                                                          \
		rb_raise(rb_eRuntimeError, "glut%s needs current window", #_funcname); \
	}                                                                        \
																																					 \
	callback = rb_glut_check_callback(self, callback);                               \
																																					 \
	rb_ary_store(_funcname, win, callback);                                  \
																																					 \
	if (NIL_P(callback))                                                     \
		glut##_funcname(NULL);                                                 \
	else                                                                     \
		glut##_funcname(&glut_##_funcname##Callback0);                         \
																																					 \
	return Qnil;                                                             \
}

#define WINDOW_CALLBACK_DEFINE(module, _funcname) \
		rb_define_module_function(module, "glut"#_funcname, glut_##_funcname, 1); \
		rb_global_variable(&_funcname); \
		_funcname = rb_ary_new()

static void GLUTCALLBACK glut_DisplayFuncCallback0(void);
static void GLUTCALLBACK glut_ReshapeFuncCallback0(int, int);
static void GLUTCALLBACK glut_KeyboardFuncCallback0(unsigned char, int, int);
static void GLUTCALLBACK glut_MouseFuncCallback0(int, int, int, int);
static void GLUTCALLBACK glut_MotionFuncCallback0(int, int);
static void GLUTCALLBACK glut_PassiveMotionFuncCallback0(int, int);
static void GLUTCALLBACK glut_EntryFuncCallback0(int);
static void GLUTCALLBACK glut_VisibilityFuncCallback0(int);
static void GLUTCALLBACK glut_SpecialFuncCallback0(int, int, int);
static void GLUTCALLBACK glut_SpaceballMotionFuncCallback0(int, int, int);
static void GLUTCALLBACK glut_SpaceballRotateFuncCallback0(int, int, int);
static void GLUTCALLBACK glut_SpaceballButtonFuncCallback0(int, int);
static void GLUTCALLBACK glut_ButtonBoxFuncCallback0(int, int);
static void GLUTCALLBACK glut_DialsFuncCallback0(int, int);
static void GLUTCALLBACK glut_TabletMotionFuncCallback0(int, int);
static void GLUTCALLBACK glut_TabletButtonFuncCallback0(int, int, int, int);
static void GLUTCALLBACK glut_OverlayDisplayFuncCallback0(void);
static void GLUTCALLBACK glut_WindowStatusFuncCallback0(int);
static void GLUTCALLBACK glut_JoystickFuncCallback0(unsigned int, int, int, int);
static void GLUTCALLBACK glut_KeyboardUpFuncCallback0(unsigned char, int, int);
static void GLUTCALLBACK glut_SpecialUpFuncCallback0(int, int, int);

WINDOW_CALLBACK_SETUP(DisplayFunc)
WINDOW_CALLBACK_SETUP(ReshapeFunc)
WINDOW_CALLBACK_SETUP(KeyboardFunc)
WINDOW_CALLBACK_SETUP(MouseFunc)
WINDOW_CALLBACK_SETUP(MotionFunc)
WINDOW_CALLBACK_SETUP(PassiveMotionFunc)
WINDOW_CALLBACK_SETUP(EntryFunc)
WINDOW_CALLBACK_SETUP(VisibilityFunc)
WINDOW_CALLBACK_SETUP(SpecialFunc)
WINDOW_CALLBACK_SETUP(SpaceballMotionFunc)
WINDOW_CALLBACK_SETUP(SpaceballRotateFunc)
WINDOW_CALLBACK_SETUP(SpaceballButtonFunc)
WINDOW_CALLBACK_SETUP(ButtonBoxFunc)
WINDOW_CALLBACK_SETUP(DialsFunc)
WINDOW_CALLBACK_SETUP(TabletMotionFunc)
WINDOW_CALLBACK_SETUP(TabletButtonFunc)
WINDOW_CALLBACK_SETUP(OverlayDisplayFunc)
WINDOW_CALLBACK_SETUP(WindowStatusFunc)
WINDOW_CALLBACK_SETUP(KeyboardUpFunc)
WINDOW_CALLBACK_SETUP(SpecialUpFunc)

GLUT_SIMPLE_FUNCTION(ForceJoystickFunc)

static void *
glut_DisplayFuncCallback(void *ignored) {
	VALUE func;

	func = rb_ary_entry(DisplayFunc, glutGetWindow());

	if (!NIL_P(func))
		rb_funcall(func, call_id, 0);

	return NULL;
}

static void GLUTCALLBACK
glut_DisplayFuncCallback0(void) {
	rb_thread_call_with_gvl(glut_DisplayFuncCallback, NULL);
}

static void *
glut_ReshapeFuncCallback(struct callback_args *args) {
	VALUE func   = rb_ary_entry(ReshapeFunc, glutGetWindow());
	VALUE width  = INT2FIX(args->arg0.width);
	VALUE height = INT2FIX(args->arg1.height);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, width, height);

	return NULL;
}

static void GLUTCALLBACK
glut_ReshapeFuncCallback0(int width, int height) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.width = width;
	args->arg1.height = height;

	rb_thread_call_with_gvl((gvl_call)glut_ReshapeFuncCallback, args);

	free(args);
}

static void *
glut_KeyboardFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(KeyboardFunc, glutGetWindow());
#if HAVE_SINGLE_BYTE_STRINGS
	VALUE key = rb_str_new((char *)&args->arg0.key, 1);
#else
	VALUE key = UINT2NUM((unsigned char)args->arg0.key);
#endif
	VALUE x = INT2FIX(args->arg1.x);
	VALUE y = INT2FIX(args->arg2.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, key, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_KeyboardFuncCallback0(unsigned char key, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.key = key;
	args->arg1.x   = x;
	args->arg2.y   = y;

	rb_thread_call_with_gvl((gvl_call)glut_KeyboardFuncCallback, args);

	free(args);
}

static void *
glut_KeyboardUpFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(KeyboardUpFunc, glutGetWindow());
#if HAVE_SINGLE_BYTE_STRINGS
	VALUE key = rb_str_new((char *)args->arg0.key, 1);
#else
	VALUE key = UINT2NUM((unsigned char)args->arg0.key);
#endif
	VALUE x = INT2FIX((int)args->arg1.x);
	VALUE y = INT2FIX((int)args->arg2.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, key, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_KeyboardUpFuncCallback0(unsigned char key, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.key = key;
	args->arg1.x   = x;
	args->arg2.y   = y;

	rb_thread_call_with_gvl((gvl_call)glut_KeyboardUpFuncCallback, args);

	free(args);
}

static void *
glut_MouseFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(MouseFunc, glutGetWindow());

	VALUE button = INT2FIX(args->arg0.button);
	VALUE state  = INT2FIX(args->arg1.state);
	VALUE x      = INT2FIX(args->arg2.x);
	VALUE y      = INT2FIX(args->arg3.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 4, button, state, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_MouseFuncCallback0(int button, int state, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.button = button;
	args->arg1.state  = state;
	args->arg2.x      = x;
	args->arg3.y      = y;

	rb_thread_call_with_gvl((gvl_call)glut_MouseFuncCallback, args);

	free(args);
}

static void *
glut_MotionFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(MotionFunc, glutGetWindow());
	VALUE x = INT2FIX(args->arg0.x);
	VALUE y = INT2FIX(args->arg1.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_MotionFuncCallback0(int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.x = x;
	args->arg1.y = y;

	rb_thread_call_with_gvl((gvl_call)glut_MotionFuncCallback, args);

	free(args);
}

static void *
glut_PassiveMotionFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(PassiveMotionFunc, glutGetWindow());
	VALUE x    = INT2FIX(args->arg0.x);
	VALUE y    = INT2FIX(args->arg1.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_PassiveMotionFuncCallback0(int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.x = x;
	args->arg1.y = y;

	rb_thread_call_with_gvl((gvl_call)glut_PassiveMotionFuncCallback, args);

	free(args);
}

static void *
glut_EntryFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(EntryFunc, glutGetWindow());
	VALUE state = INT2NUM(args->arg0.state);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 1, state);

	return NULL;
}

static void GLUTCALLBACK
glut_EntryFuncCallback0(int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.state = state;

	rb_thread_call_with_gvl((gvl_call)glut_EntryFuncCallback, args);

	free(args);
}

static void *
glut_VisibilityFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(VisibilityFunc, glutGetWindow());
	VALUE state = INT2NUM(args->arg0.state);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 1, state);

	return NULL;
}

static void GLUTCALLBACK
glut_VisibilityFuncCallback0(int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.state = state;

	rb_thread_call_with_gvl((gvl_call)glut_VisibilityFuncCallback, args);

	free(args);
}

static void *
glut_IdleFuncCallback(void *ignored) {
	if (!NIL_P(idle_func))
		rb_funcall(idle_func, call_id, 0);

	return NULL;
}

static void GLUTCALLBACK
glut_IdleFuncCallback0(void) {
	rb_thread_call_with_gvl((gvl_call)glut_IdleFuncCallback, NULL);
}

static void *
glut_TimerFuncCallback(struct callback_args *args) {
	VALUE value = INT2NUM(args->arg0.value);

	if (!NIL_P(timer_func))
		rb_funcall(timer_func, call_id, 1, value);

	return NULL;
}

static void GLUTCALLBACK
glut_TimerFuncCallback0(int value) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.value = value;

	rb_thread_call_with_gvl((gvl_call)glut_TimerFuncCallback, args);

	free(args);
}

static void *
glut_MenuStateFuncCallback(struct callback_args *args) {
	VALUE state = INT2NUM(args->arg0.state);

	if (!NIL_P(menustate_func))
		rb_funcall(menustate_func, call_id, 1, state);

	return NULL;
}

static void GLUTCALLBACK
glut_MenuStateFuncCallback0(int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.state = state;

	rb_thread_call_with_gvl((gvl_call)glut_MenuStateFuncCallback, args);

	free(args);
}

static void *
glut_MenuStatusFuncCallback(struct callback_args *args) {
	VALUE state = INT2NUM(args->arg0.state);
	VALUE x     = INT2NUM(args->arg1.x);
	VALUE y     = INT2NUM(args->arg2.y);

	if (!NIL_P(menustatus_func))
		rb_funcall(menustatus_func, call_id, 3, state, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_MenuStatusFuncCallback0(int state, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.state = state;
	args->arg1.x     = x;
	args->arg2.y     = y;

	rb_thread_call_with_gvl((gvl_call)glut_MenuStatusFuncCallback, args);

	free(args);
}

static void *
glut_SpecialFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(SpecialFunc, glutGetWindow());
	VALUE key  = INT2NUM(args->arg0.key);
	VALUE x    = INT2NUM(args->arg1.x);
	VALUE y    = INT2NUM(args->arg2.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, key, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_SpecialFuncCallback0(int key, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.key = key;
	args->arg1.x   = x;
	args->arg2.y   = y;

	rb_thread_call_with_gvl((gvl_call)glut_SpecialFuncCallback, args);

	free(args);
}

static void *
glut_SpecialUpFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(SpecialUpFunc, glutGetWindow());
	VALUE key  = INT2NUM(args->arg0.key);
	VALUE x    = INT2NUM(args->arg1.x);
	VALUE y    = INT2NUM(args->arg2.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, key, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_SpecialUpFuncCallback0(int key, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.key = key;
	args->arg1.x   = x;
	args->arg2.y   = y;

	rb_thread_call_with_gvl((gvl_call)glut_SpecialUpFuncCallback, args);

	free(args);
}

static void *
glut_SpaceballMotionFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(SpaceballMotionFunc, glutGetWindow());
	VALUE x    = INT2NUM(args->arg0.x);
	VALUE y    = INT2NUM(args->arg1.y);
	VALUE z    = INT2NUM(args->arg2.z);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, x, y, z);

	return NULL;
}

static void GLUTCALLBACK
glut_SpaceballMotionFuncCallback0(int x, int y, int z) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.x = x;
	args->arg1.y = y;
	args->arg2.z = z;

	rb_thread_call_with_gvl((gvl_call)glut_SpaceballMotionFuncCallback, args);

	free(args);
}

static void *
glut_SpaceballRotateFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(SpaceballRotateFunc, glutGetWindow());
	VALUE x    = INT2NUM(args->arg0.x);
	VALUE y    = INT2NUM(args->arg1.y);
	VALUE z    = INT2NUM(args->arg2.z);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 3, x, y, z);

	return NULL;
}

static void GLUTCALLBACK
glut_SpaceballRotateFuncCallback0(int x, int y, int z) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.x = x;
	args->arg1.y = y;
	args->arg2.z = z;

	rb_thread_call_with_gvl((gvl_call)glut_SpaceballRotateFuncCallback, args);

	free(args);
}

static void *
glut_SpaceballButtonFuncCallback(struct callback_args *args) {
	VALUE func   = rb_ary_entry(SpaceballButtonFunc, glutGetWindow());
	VALUE button = INT2NUM(args->arg0.button);
	VALUE state  = INT2NUM(args->arg1.state);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, button, state);

	return NULL;
}

static void GLUTCALLBACK
glut_SpaceballButtonFuncCallback0(int button, int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.button = button;
	args->arg1.state  = state;

	rb_thread_call_with_gvl((gvl_call)glut_SpaceballButtonFuncCallback, args);

	free(args);
}

static void *
glut_ButtonBoxFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(ButtonBoxFunc, glutGetWindow());
	VALUE button = INT2NUM(args->arg0.button);
	VALUE state  = INT2NUM(args->arg1.state);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, button, state);

	return NULL;
}

static void GLUTCALLBACK
glut_ButtonBoxFuncCallback0(int button, int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.button = button;
	args->arg1.state  = state;

	rb_thread_call_with_gvl((gvl_call)glut_ButtonBoxFuncCallback, args);

	free(args);
}

static void *
glut_DialsFuncCallback(struct callback_args *args) {
	VALUE func  = rb_ary_entry(DialsFunc, glutGetWindow());
	VALUE dial  = INT2NUM(args->arg0.dial);
	VALUE value = INT2NUM(args->arg1.value);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, dial, value);

	return NULL;
}

static void GLUTCALLBACK
glut_DialsFuncCallback0(int dial, int value) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.dial  = dial;
	args->arg1.value = value;

	rb_thread_call_with_gvl((gvl_call)glut_DialsFuncCallback, args);

	free(args);
}

static void *
glut_TabletMotionFuncCallback(struct callback_args *args) {
	VALUE func = rb_ary_entry(TabletMotionFunc, glutGetWindow());
	VALUE x    = INT2NUM(args->arg0.x);
	VALUE y    = INT2NUM(args->arg1.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 2, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_TabletMotionFuncCallback0(int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.x = x;
	args->arg1.y = y;

	rb_thread_call_with_gvl((gvl_call)glut_TabletMotionFuncCallback, args);

	free(args);
}

static void *
glut_TabletButtonFuncCallback(struct callback_args *args) {
	VALUE func   = rb_ary_entry(TabletButtonFunc, glutGetWindow());
	VALUE button = INT2NUM(args->arg0.button);
	VALUE state  = INT2NUM(args->arg1.state);
	VALUE x      = INT2NUM(args->arg2.x);
	VALUE y      = INT2NUM(args->arg3.y);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 4, button, state, x, y);

	return NULL;
}

static void GLUTCALLBACK
glut_TabletButtonFuncCallback0(int button, int state, int x, int y) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.button = button;
	args->arg1.state  = state;
	args->arg2.x      = x;
	args->arg3.y      = y;

	rb_thread_call_with_gvl((gvl_call)glut_TabletButtonFuncCallback, args);

	free(args);
}

static void *
glut_OverlayDisplayFuncCallback(void) {
	VALUE func = rb_ary_entry(OverlayDisplayFunc, glutGetWindow());

	if (!NIL_P(func))
		rb_funcall(func, call_id, 0);

	return NULL;
}

static void GLUTCALLBACK
glut_OverlayDisplayFuncCallback0(void) {
	rb_thread_call_with_gvl((gvl_call)glut_OverlayDisplayFuncCallback, NULL);
}

static void *
glut_WindowStatusFuncCallback(struct callback_args *args) {
	VALUE func  = rb_ary_entry(WindowStatusFunc, glutGetWindow());
	VALUE state = INT2NUM(args->arg0.state);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 1, state);

	return NULL;
}

static void GLUTCALLBACK
glut_WindowStatusFuncCallback0(int state) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.state = state;

	rb_thread_call_with_gvl((gvl_call)glut_WindowStatusFuncCallback, args);

	free(args);
}

static void *
glut_JoystickFuncCallback(struct callback_args *args) {
	VALUE func        = rb_ary_entry(joystick_func, glutGetWindow());
	VALUE button_mask = UINT2NUM(args->arg0.button_mask);
	VALUE x           = INT2NUM(args->arg1.x);
	VALUE y           = INT2NUM(args->arg2.y);
	VALUE z           = INT2NUM(args->arg3.z);

	if (!NIL_P(func))
		rb_funcall(func, call_id, 4, button_mask, x, y, z);

	return NULL;
}

static void GLUTCALLBACK
glut_JoystickFuncCallback0(unsigned int button_mask, int x, int y, int z) {
	struct callback_args *args = alloc_callback_args();

	args->arg0.button_mask = button_mask;
	args->arg1.x           = x;
	args->arg2.y           = y;
	args->arg3.z           = z;

	rb_thread_call_with_gvl((gvl_call)glut_JoystickFuncCallback, args);

	free(args);
}

static VALUE
glut_JoystickFunc(VALUE self, VALUE callback, VALUE _poll_interval) {
	int win = glutGetWindow();
	int poll_interval = NUM2INT(_poll_interval);

	if (win == 0)
		rb_raise(rb_eRuntimeError, "glutJoystickFunc needs current window");

	callback = rb_glut_check_callback(self, callback);

	rb_ary_store(joystick_func, win, callback);

	if (NIL_P(callback))
		glutJoystickFunc(NULL, -1);
	else
		glutJoystickFunc(glut_JoystickFuncCallback0, poll_interval);

	return Qnil;
}

static VALUE
glut_IdleFunc(VALUE self, VALUE callback) {
	callback = rb_glut_check_callback(self, callback);

	idle_func = callback;

	if (NIL_P(callback))
		glutIdleFunc(NULL);
	else
		glutIdleFunc(glut_IdleFuncCallback0);

	return Qnil;
}

static VALUE
glut_MenuStateFunc(VALUE self, VALUE callback) {
	menustate_func = rb_glut_check_callback(self, callback);

	if (NIL_P(menustate_func))
		glutMenuStateFunc(NULL);
	else
		glutMenuStateFunc(glut_MenuStateFuncCallback0);

	return Qnil;
}

static VALUE
glut_MenuStatusFunc(VALUE self, VALUE callback) {
	menustatus_func = rb_glut_check_callback(self, callback);

	if (NIL_P(menustatus_func))
		glutMenuStatusFunc(NULL);
	else
		glutMenuStatusFunc(glut_MenuStatusFuncCallback0);

	return Qnil;
}

static VALUE
glut_TimerFunc(VALUE self, VALUE _msec, VALUE callback, VALUE _value) {
	unsigned int msec = NUM2UINT(_msec);
	int value = NUM2INT(_value);

	timer_func = rb_glut_check_callback(self, callback);

	glutTimerFunc(msec, glut_TimerFuncCallback0, value);

	return Qnil;
}

void Init_glut_callbacks() {
	VALUE mGlut = rb_path2class("Glut");

	call_id = rb_intern("call");
	joystick_func = rb_ary_new();

	rb_global_variable(&joystick_func);
	rb_gc_register_address(&idle_func);
	rb_gc_register_address(&timer_func);
	rb_gc_register_address(&menustate_func);

	rb_define_module_function(mGlut, "glutJoystickFunc", glut_JoystickFunc, 2);
	rb_define_module_function(mGlut, "glutForceJoystickFunc", glut_ForceJoystickFunc, 0);
	rb_define_module_function(mGlut, "glutIdleFunc", glut_IdleFunc, 1);
	rb_define_module_function(mGlut, "glutMenuStateFunc", glut_MenuStateFunc, 1);
	rb_define_module_function(mGlut, "glutMenuStatusFunc", glut_MenuStatusFunc, 1);
	rb_define_module_function(mGlut, "glutTimerFunc", glut_TimerFunc, 3);

	WINDOW_CALLBACK_DEFINE(mGlut, ButtonBoxFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, DialsFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, DisplayFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, EntryFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, KeyboardFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, KeyboardUpFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, MotionFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, MouseFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, OverlayDisplayFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, PassiveMotionFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, ReshapeFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, SpaceballButtonFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, SpaceballMotionFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, SpaceballRotateFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, SpecialFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, SpecialUpFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, TabletButtonFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, TabletMotionFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, VisibilityFunc);
	WINDOW_CALLBACK_DEFINE(mGlut, WindowStatusFunc);
}

