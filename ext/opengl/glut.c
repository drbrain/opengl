/*
 * Last edit by previous maintainer:
 * 2004/03/02 01:13:06, yoshi
 *
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2005 James Adam <james@lazyatom.com>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
 * Copyright (C) 2007 Jan Dvorak <jan.dvorak@kraxnet.cz>
 *
 * This program is distributed under the terms of the MIT license.
 * See the included COPYRIGHT file for the terms of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "common.h"

/* HACK experimental API */
void *rb_thread_call_with_gvl(void *(*func)(void *), void *data1);

static ID call_id; /* 'call' method id */
static VALUE idle_func = Qnil;
static VALUE menustate_func = Qnil;
static VALUE menustatus_func = Qnil;
static VALUE timer_func = Qnil;

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
  callback = check_callback(self, callback);                               \
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

#define WINDOW_CALLBACK_DEFINE(_funcname) \
    rb_define_module_function(module, "glut" # _funcname, glut_ ## _funcname , 1); \
    rb_global_variable(&_funcname); \
    _funcname = rb_ary_new()

#define GLUT_SIMPLE_FUNCTION(_name_) \
static VALUE \
glut_##_name_(obj) \
VALUE obj; \
{ \
    glut##_name_(); \
    return Qnil; \
}

static VALUE
check_callback(VALUE self, VALUE callback)
{
  VALUE inspect;

	if (NIL_P(callback))
    return callback;

  if (rb_respond_to(callback, call_id))
    return callback;

  if (SYMBOL_P(callback))
    return rb_obj_method(self, callback);

  inspect = rb_inspect(callback);
  rb_raise(rb_eArgError, "%s must respond to call", StringValueCStr(inspect));
}

/*
 * GLUT Implementation
 */

/* GLUT initialization sub-API. */

static VALUE glut_Init( int argc, VALUE * argv, VALUE obj)
{
	int largc;
	char** largv;
	VALUE new_argv;
	VALUE orig_arg;
	int i;

	if (rb_scan_args(argc, argv, "01", &orig_arg) == 0)
		orig_arg = rb_eval_string("[$0] + ARGV");
	else 
		Check_Type(orig_arg, T_ARRAY);
	
	/* converts commandline parameters from ruby to C, passes them
	to glutInit and returns the parameters stripped of glut-specific
	commands ("-display","-geometry" etc.) */
	largc = (int)RARRAY_LENINT(orig_arg);
	largv = ALLOCA_N(char*, largc);
	for (i = 0; i < largc; i++)
		largv[i] = StringValueCStr(RARRAY_PTR(orig_arg)[i]);
	
	glutInit(&largc, largv);
	
	new_argv = rb_ary_new2(largc);
	for (i = 0; i < largc; i++)
		rb_ary_push(new_argv,rb_str_new2(largv[i]));

	rb_ary_shift(new_argv);

	return new_argv;
}

static VALUE glut_InitDisplayMode(obj,arg1)
VALUE obj,arg1;
{
	unsigned int mode;
	mode = (unsigned int)NUM2INT(arg1);
	glutInitDisplayMode(mode);
	return Qnil;
}

static VALUE
glut_InitDisplayString(obj,arg1)
VALUE obj,arg1;
{
	Check_Type(arg1,T_STRING);
	glutInitDisplayString(RSTRING_PTR(arg1));
	return Qnil;
}

static VALUE
glut_InitWindowPosition(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int x,y;
	x = NUM2INT(arg1);
	y = NUM2INT(arg2);
	glutInitWindowPosition(x,y);
	return Qnil;
}

static VALUE
glut_InitWindowSize(obj, arg1, arg2)
VALUE obj,arg1,arg2;
{
	int width,height;
	width = NUM2INT(arg1);
	height = NUM2INT(arg2);
	glutInitWindowSize(width,height);
	return Qnil;
}

VALUE glut_MainLoop0(void *ignored) {
  glutMainLoop();

  return Qnil; /* never reached */
}

static VALUE
glut_MainLoop(void) {
  rb_thread_blocking_region(glut_MainLoop0, NULL, NULL, NULL);

  return Qnil; /* never reached */
}

static VALUE
glut_CheckLoop(void) {
  rb_warn("calling fake CheckLoop implementation which never returns");

  glut_MainLoop();

  return Qnil;
}

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

/* special case, 2 params */
static VALUE JoystickFunc = Qnil;
static VALUE
glut_JoystickFunc(obj,callback,arg2)
VALUE obj,callback,arg2;
{
	int win;
	int pollinterval;

  callback = check_callback(obj, callback);
	pollinterval=NUM2INT(arg2);
	win = glutGetWindow();

	if (win == 0)
		rb_raise(rb_eRuntimeError, "glutJoystickFunc needs current window");

	rb_ary_store(JoystickFunc, win, callback);

	if (NIL_P(callback))
		glutJoystickFunc(NULL, pollinterval);
	else
		glutJoystickFunc(glut_JoystickFuncCallback0, pollinterval);

	return Qnil;
}

/* GLUT window sub-API. */ 
static VALUE glut_CreateWindow(argc, argv, obj)
int argc;
VALUE* argv;
VALUE obj;
{
	int ret;
	VALUE title;
	rb_scan_args(argc, argv, "01", &title);
	if (argc == 0)
		title = rb_eval_string("$0");
	Check_Type(title,T_STRING);
	ret = glutCreateWindow(RSTRING_PTR(title));
	return INT2NUM(ret);
}


static VALUE
glut_CreateSubWindow(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
	int win, x, y, width, height;
	int ret;
	win = NUM2INT(arg1);
	x = NUM2INT(arg2);
	y = NUM2INT(arg3);
	width = NUM2INT(arg4);
	height = NUM2INT(arg5);
	ret = glutCreateSubWindow(win, x, y, width, height);
	return INT2NUM(ret);
}

static VALUE
glut_DestroyWindow(obj,arg1)
VALUE obj,arg1;
{
	int win;
	win = NUM2INT(arg1);
	glutDestroyWindow(win);
	return Qnil;
}

GLUT_SIMPLE_FUNCTION(PostRedisplay)
GLUT_SIMPLE_FUNCTION(SwapBuffers)

static VALUE
glut_GetWindow(obj)
VALUE obj;
{
	int ret;
	ret = glutGetWindow();
	return INT2NUM(ret);
}

static VALUE
glut_SetWindow(obj,arg1)
VALUE obj,arg1;
{
	int win;
	win = NUM2INT(arg1);
	glutSetWindow(win);
	return Qnil;
}

static VALUE
glut_SetWindowTitle(obj,arg1)
VALUE obj,arg1;
{
	Check_Type(arg1,T_STRING);
	glutSetWindowTitle(RSTRING_PTR(arg1));
	return Qnil;
}

static VALUE
glut_SetIconTitle(obj, arg1)
VALUE obj,arg1;
{
	Check_Type(arg1,T_STRING);
	glutSetIconTitle(RSTRING_PTR(arg1));
	return Qnil;
}

static VALUE
glut_PositionWindow(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int x,y;
	x = NUM2INT(arg1);
	y = NUM2INT(arg2);
	glutPositionWindow(x,y);
	return Qnil;
}

static VALUE
glut_ReshapeWindow(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int width,height;
	width = NUM2INT(arg1);
	height = NUM2INT(arg2);
	glutReshapeWindow(width, height);
	return Qnil;
}

GLUT_SIMPLE_FUNCTION(PopWindow)
GLUT_SIMPLE_FUNCTION(PushWindow)
GLUT_SIMPLE_FUNCTION(IconifyWindow)
GLUT_SIMPLE_FUNCTION(ShowWindow)
GLUT_SIMPLE_FUNCTION(HideWindow)
GLUT_SIMPLE_FUNCTION(FullScreen)

static VALUE
glut_SetCursor(obj,arg1)
VALUE obj,arg1;
{
	int cursor;
	cursor = NUM2INT(arg1);
	glutSetCursor(cursor);
	return Qnil;
}

static VALUE
glut_WarpPointer(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int x,y;
	x = NUM2INT(arg1);
	y = NUM2INT(arg2);
	glutWarpPointer(x,y);
	return Qnil;
}

/* GLUT overlay sub-API. */
GLUT_SIMPLE_FUNCTION(EstablishOverlay)
GLUT_SIMPLE_FUNCTION(RemoveOverlay)
GLUT_SIMPLE_FUNCTION(PostOverlayRedisplay)
GLUT_SIMPLE_FUNCTION(ShowOverlay)
GLUT_SIMPLE_FUNCTION(HideOverlay)

static VALUE
glut_UseLayer(obj,arg1)
VALUE obj, arg1;
{
	GLenum layer;
	layer = (GLenum)NUM2INT(arg1);
	glutUseLayer(layer);
	return Qnil;
}

/* GLUT menu sub-API. */
static VALUE g_menucallback = Qnil;
static void GLUTCALLBACK
glut_CreateMenuCallback(int value)
{
	VALUE func;
	int menu;
	menu = glutGetMenu();
	func = rb_ary_entry(g_menucallback, menu);

	rb_funcall(func, call_id, 1, INT2NUM(value));
}

static VALUE
glut_CreateMenu(obj,callback)
VALUE obj,callback;
{
	int menu;

  callback = check_callback(obj, callback);

	if (NIL_P(callback))
		menu = glutCreateMenu(NULL);
	else
		menu = glutCreateMenu(glut_CreateMenuCallback);

	rb_ary_store(g_menucallback, menu, callback);

	return INT2FIX(menu);
}

static VALUE
glut_DestroyMenu(obj,arg1)
VALUE obj,arg1;
{
	int menu;
	menu = NUM2INT(arg1);
	glutDestroyMenu(menu);
	//rb_hash_aset(g_menucallback, menu, Qnil);
	//rb_hash_aset(g_menuargs, menu, Qnil);
	return Qnil;
}

static VALUE
glut_GetMenu(obj)
VALUE obj;
{
	int ret;
	ret = glutGetMenu();
	return INT2NUM(ret);
}

static VALUE
glut_SetMenu(obj,arg1)
VALUE obj,arg1;
{
	glutSetMenu(NUM2INT(arg1));
	return Qnil;
}

static VALUE
glut_AddMenuEntry(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	Check_Type(arg1,T_STRING);
	glutAddMenuEntry(RSTRING_PTR(arg1), NUM2INT(arg2));
	return Qnil;
}

static VALUE
glut_AddSubMenu(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	Check_Type(arg1,T_STRING);
	glutAddSubMenu(RSTRING_PTR(arg1), NUM2INT(arg2));
	return Qnil;
}

static VALUE glut_ChangeToMenuEntry(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	Check_Type(arg2,T_STRING);
	glutChangeToMenuEntry(NUM2INT(arg1), RSTRING_PTR(arg2), NUM2INT(arg3));
	return Qnil;
}

static VALUE glut_ChangeToSubMenu(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	Check_Type(arg2,T_STRING);
	glutChangeToSubMenu(NUM2INT(arg1), RSTRING_PTR(arg2), NUM2INT(arg3));
	return Qnil;
}

static VALUE glut_RemoveMenuItem( VALUE obj, VALUE arg1 )
{
	glutRemoveMenuItem(NUM2INT(arg1));
	return Qnil;
}

static VALUE
glut_AttachMenu(obj,arg1)
VALUE obj, arg1;
{
	glutAttachMenu(NUM2INT(arg1));
	return Qnil;
}

static VALUE
glut_DetachMenu(obj,arg1)
VALUE obj, arg1;
{
	glutDetachMenu(NUM2INT(arg1));
	return Qnil;
}

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

typedef void *(*gvl_call)(void *);

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
  VALUE key = rb_str_new((char *)args->arg0.key, 1);
#else
  VALUE key = UINT2FIX((unsigned char)args->arg0.key);
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
  VALUE key = UINT2FIX((unsigned char)args->arg0.key);
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

static VALUE
glut_IdleFunc(VALUE self, VALUE callback) {
  callback = check_callback(self, callback);

	idle_func = callback;

	if (NIL_P(callback))
		glutIdleFunc(NULL);
	else
		glutIdleFunc(glut_IdleFuncCallback0);

	return Qnil;
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

static VALUE
glut_TimerFunc(VALUE self, VALUE _msec, VALUE callback, VALUE _value) {
	unsigned int msec = NUM2UINT(_msec);
	int value = NUM2INT(_value);

  timer_func = check_callback(self, callback);

	glutTimerFunc(msec, glut_TimerFuncCallback0, value);

	return Qnil;
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

static VALUE
glut_MenuStateFunc(VALUE self, VALUE callback) {
  menustate_func = check_callback(self, callback);

	if (NIL_P(menustate_func))
		glutMenuStateFunc(NULL);
	else
		glutMenuStateFunc(glut_MenuStateFuncCallback0);

	return Qnil;
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

static VALUE
glut_MenuStatusFunc(VALUE self, VALUE callback) {
  menustatus_func = check_callback(self, callback);

	if (NIL_P(menustatus_func))
		glutMenuStatusFunc(NULL);
	else
		glutMenuStatusFunc(glut_MenuStatusFuncCallback0);

	return Qnil;
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
	VALUE func        = rb_ary_entry(JoystickFunc, glutGetWindow());
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

/* GLUT color index sub-API. */
static VALUE
glut_SetColor(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	int set;
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	set = NUM2INT(arg1);
	red = (GLfloat)NUM2DBL(arg2);
	green = (GLfloat)NUM2DBL(arg3);
	blue = (GLfloat)NUM2DBL(arg4);
	glutSetColor(set, red, green, blue);
	return Qnil;
}

static VALUE
glut_GetColor(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int ndx;
	int component;
	GLfloat ret;
	ndx = NUM2INT(arg1);
	component = NUM2INT(arg2);
	ret = (GLfloat)glutGetColor(ndx, component);
	return rb_float_new(ret);
}

static VALUE
glut_CopyColormap(obj,arg1)
VALUE obj,arg1;
{
	int win;
	win = NUM2INT(arg1);
	glutCopyColormap(win);
	return Qnil;
}

/* GLUT state retrieval sub-API. */
static VALUE
glut_Get(obj,arg1)
VALUE obj,arg1;
{
	GLenum type;
	int ret;
	type = (GLenum)NUM2INT(arg1);
	ret = glutGet(type);
	return INT2NUM(ret);
}

static VALUE
glut_DeviceGet(obj,arg1)
VALUE obj,arg1;
{
	GLenum type;
	int ret;
	type = (GLenum)NUM2INT(arg1);
	ret = glutDeviceGet(type);
	return INT2NUM(ret);
}

/* GLUT extension support sub-API */
static VALUE
glut_ExtensionSupported(obj,arg1)
VALUE obj,arg1;
{
	int ret;
	Check_Type(arg1,T_STRING);
	ret = glutExtensionSupported(RSTRING_PTR(arg1));
	return INT2NUM(ret);
}

static VALUE
glut_GetModifiers(obj)
VALUE obj;
{
	int ret;
	ret = glutGetModifiers();
	return INT2NUM(ret);
}

static VALUE
glut_LayerGet(obj,arg1)
VALUE obj,arg1;
{
	GLenum type;
	int ret;
	type = (GLenum)NUM2INT(arg1);
	ret = glutLayerGet(type);
	return INT2NUM(ret);
}

/* GLUT font sub-API */

/* Some glut implementations define font enums as addresses of local functions
 * which are then called by glut internally. This may lead to crashes or bus
 * errors on some platforms, so to be safe we hardcode the values passed
 * to/from ruby
 */

static inline void * bitmap_font_map(int f)
{
	switch (f) {
		case 0: return (void *)GLUT_BITMAP_9_BY_15;
		case 1: return (void *)GLUT_BITMAP_8_BY_13;
		case 2: return (void *)GLUT_BITMAP_TIMES_ROMAN_10; 
		case 3: return (void *)GLUT_BITMAP_TIMES_ROMAN_24;
		case 4: return (void *)GLUT_BITMAP_HELVETICA_10;
		case 5: return (void *)GLUT_BITMAP_HELVETICA_12;
		case 6: return (void *)GLUT_BITMAP_HELVETICA_18;
		default:
			rb_raise(rb_eArgError, "Unsupported font %d", f);
	}

	return (void *) 0; /* not reached */
}

static inline void * stroke_font_map(int f)
{
	switch (f) {
		case 7: return (void *)GLUT_STROKE_ROMAN;
		case 8: return (void *)GLUT_STROKE_MONO_ROMAN;
		default:
			rb_raise(rb_eArgError, "Unsupported font %d", f);
	}

	return (void *) 0; /* not reached */
}

static VALUE
glut_BitmapCharacter(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int character;
	int font;
	font = NUM2INT(arg1);
	character = NUM2INT(arg2);
	glutBitmapCharacter(bitmap_font_map(font),character);
	return Qnil;
}

static VALUE
glut_BitmapWidth(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int font;
	int character;
	int ret;
	font = NUM2INT(arg1);
	character = NUM2INT(arg2);
	ret = glutBitmapWidth(bitmap_font_map(font), character);
	return INT2NUM(ret);
}

static VALUE
glut_StrokeCharacter(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int font;
	int character;
	font = NUM2INT(arg1);
	character = NUM2INT(arg2);
	glutStrokeCharacter(stroke_font_map(font), character);
	return Qnil;
}

static VALUE
glut_StrokeWidth(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int font;
	int character;
	int ret;
	font = NUM2INT(arg1);
	character = NUM2INT(arg2);
	ret = glutStrokeWidth(stroke_font_map(font), character);
	return INT2NUM(ret);
}

static VALUE
glut_BitmapLength(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int font;
	int ret;
	Check_Type(arg2,T_STRING);
	font = NUM2INT(arg1);
	ret = glutBitmapLength(bitmap_font_map(font), (const unsigned char*)RSTRING_PTR(arg2));
	return INT2NUM(ret);
}

static VALUE
glut_StrokeLength(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	int font;
	int ret;
	Check_Type(arg2,T_STRING);
	font = NUM2INT(arg1);
	ret = glutStrokeLength(stroke_font_map(font), (const unsigned char*)RSTRING_PTR(arg2));
	return INT2NUM(ret);
}

/* GLUT pre-built models sub-API */
static VALUE
glut_WireSphere(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLdouble radius;
	GLint slices;
	GLint stacks;
	radius = (GLdouble)NUM2DBL(arg1);
	slices = (GLint)NUM2INT(arg2);
	stacks = (GLint)NUM2INT(arg3);
	glutWireSphere(radius, slices, stacks);
	return Qnil;
}

static VALUE
glut_SolidSphere(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLdouble radius;
	GLint slices;
	GLint stacks;
	radius = (GLdouble)NUM2DBL(arg1);
	slices = (GLint)NUM2INT(arg2);
	stacks = (GLint)NUM2INT(arg3);
	glutSolidSphere(radius, slices, stacks);
	return Qnil;
}

static VALUE
glut_WireCone(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;
	base = (GLdouble)NUM2DBL(arg1);
	height = (GLdouble)NUM2DBL(arg2);
	slices = (GLint)NUM2INT(arg3);
	stacks = (GLint)NUM2INT(arg4);
	glutWireCone(base, height, slices, stacks);
	return Qnil;
}

static VALUE
glut_SolidCone(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble base;
	GLdouble height;
	GLint slices;
	GLint stacks;
	base = (GLdouble)NUM2DBL(arg1);
	height = (GLdouble)NUM2DBL(arg2);
	slices = (GLint)NUM2INT(arg3);
	stacks = (GLint)NUM2INT(arg4);
	glutSolidCone(base, height, slices, stacks);
	return Qnil;
}

static VALUE
glut_WireCube(obj,arg1)
VALUE obj,arg1;
{
	GLdouble size;
	size = (GLdouble)NUM2DBL(arg1);
	glutWireCube(size);
	return Qnil;
}

static VALUE
glut_SolidCube(obj,arg1)
VALUE obj,arg1;
{
	GLdouble size;
	size = (GLdouble)NUM2DBL(arg1);
	glutSolidCube(size);
	return Qnil;
}

static VALUE
glut_WireTorus(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint sides;
	GLint rings;
	innerRadius = (GLdouble)NUM2DBL(arg1);
	outerRadius = (GLdouble)NUM2DBL(arg2);
	sides = (GLint)NUM2INT(arg3);
	rings = (GLint)NUM2INT(arg4);
	glutWireTorus(innerRadius, outerRadius, sides, rings);
	return Qnil;
}

static VALUE
glut_SolidTorus(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint sides;
	GLint rings;
	innerRadius = (GLdouble)NUM2DBL(arg1);
	outerRadius = (GLdouble)NUM2DBL(arg2);
	sides = (GLint)NUM2INT(arg3);
	rings = (GLint)NUM2INT(arg4);
	glutSolidTorus(innerRadius, outerRadius, sides, rings);
	return Qnil;
}

GLUT_SIMPLE_FUNCTION(WireDodecahedron)
GLUT_SIMPLE_FUNCTION(SolidDodecahedron)
GLUT_SIMPLE_FUNCTION(WireOctahedron)
GLUT_SIMPLE_FUNCTION(SolidOctahedron)
GLUT_SIMPLE_FUNCTION(WireTetrahedron)
GLUT_SIMPLE_FUNCTION(SolidTetrahedron)
GLUT_SIMPLE_FUNCTION(WireIcosahedron)
GLUT_SIMPLE_FUNCTION(SolidIcosahedron)

static VALUE
glut_WireTeapot(obj,arg1)
VALUE obj,arg1;
{
	GLdouble size;
	size = (GLdouble)NUM2DBL(arg1);
	glutWireTeapot(size);
	return Qnil;
}

static VALUE
glut_SolidTeapot(obj,arg1)
VALUE obj,arg1;
{
	GLdouble size;
	size = (GLdouble)NUM2DBL(arg1);
	glutSolidTeapot(size);
	return Qnil;
}

/* GLUT video resize sub-API. */
static VALUE
glut_VideoResizeGet(obj,arg1)
VALUE obj,arg1;
{
	GLenum param;
	int ret;
	param = (GLenum)NUM2INT(arg1);
	ret = glutVideoResizeGet(param);
	return INT2NUM(ret);
}

GLUT_SIMPLE_FUNCTION(SetupVideoResizing)
GLUT_SIMPLE_FUNCTION(StopVideoResizing)

static VALUE
glut_VideoResize(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	int x;
	int y;
	int width;
	int height;
	x = NUM2INT(arg1);
	y = NUM2INT(arg2);
	width = NUM2INT(arg3);
	height = NUM2INT(arg4);
	glutVideoResize(x,y, width, height);
	return Qnil;
}

static VALUE
glut_VideoPan(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	int x;
	int y;
	int width;
	int height;
	x = NUM2INT(arg1);
	y = NUM2INT(arg2);
	width = NUM2INT(arg3);
	height = NUM2INT(arg4);
	glutVideoPan(x,y, width, height);
	return Qnil;
}

/* GLUT debugging sub-API. */
GLUT_SIMPLE_FUNCTION(ReportErrors)

static VALUE
glut_GameModeString(obj,arg1)
VALUE obj,arg1;
{
	Check_Type(arg1,T_STRING);
	glutGameModeString((const char*)RSTRING_PTR(arg1));
	return Qnil;
}

GLUT_SIMPLE_FUNCTION(EnterGameMode)
GLUT_SIMPLE_FUNCTION(LeaveGameMode)

GLUT_SIMPLE_FUNCTION(ForceJoystickFunc)

static VALUE
glut_GameModeGet(obj,arg1)
VALUE obj,arg1;
{
	GLenum info;
	int i;
	info = (GLenum)NUM2INT(arg1);
	i = glutGameModeGet(info);
	return INT2NUM(i);
}

static VALUE
glut_SetKeyRepeat(obj,arg1)
VALUE obj,arg1;
{
	GLenum repeatMode;
	repeatMode = (int) NUM2INT(arg1);
	glutSetKeyRepeat(repeatMode);
	return Qnil;
}

static VALUE
glut_IgnoreKeyRepeat(obj,arg1)
VALUE obj,arg1;
{
	GLenum ignore;
	ignore = (int) NUM2INT(arg1);
	glutIgnoreKeyRepeat(ignore);
	return Qnil;
}

static VALUE
glut_PostWindowOverlayRedisplay(obj,arg1)
VALUE obj,arg1;
{
	int win;
	win = (int) NUM2INT(arg1);
	glutPostWindowOverlayRedisplay(win);
	return Qnil;
}

static VALUE
glut_PostWindowRedisplay(obj,arg1)
VALUE obj,arg1;
{
	int win;
	win = (int) NUM2INT(arg1);
	glutPostWindowRedisplay(win);
	return Qnil;
}

static VALUE module;

DLLEXPORT void Init_glut()
{
	call_id = rb_intern("call");
	
	module = rb_define_module("Glut");
	
	rb_global_variable( &g_menucallback );
	g_menucallback = rb_ary_new();
	
	rb_define_module_function(module, "glutInit", glut_Init, -1);
	rb_define_module_function(module, "glutInitDisplayMode", glut_InitDisplayMode, 1);
	rb_define_module_function(module, "glutInitDisplayString", glut_InitDisplayString, 1);
	rb_define_module_function(module, "glutInitWindowPosition", glut_InitWindowPosition, 2);
	rb_define_module_function(module, "glutInitWindowSize", glut_InitWindowSize, 2);
	rb_define_module_function(module, "glutMainLoop", glut_MainLoop, 0);
	rb_define_module_function(module, "glutCheckLoop", glut_CheckLoop, 0);
	rb_define_module_function(module, "glutGameModeString", glut_GameModeString, 1);
	rb_define_module_function(module, "glutEnterGameMode", glut_EnterGameMode, 0);
	rb_define_module_function(module, "glutLeaveGameMode", glut_LeaveGameMode, 0);
	rb_define_module_function(module, "glutCreateWindow", glut_CreateWindow, -1);
	rb_define_module_function(module, "glutCreateSubWindow", glut_CreateSubWindow, 5);
	rb_define_module_function(module, "glutDestroyWindow", glut_DestroyWindow, 1);
	rb_define_module_function(module, "glutPostRedisplay", glut_PostRedisplay, 0);
	rb_define_module_function(module, "glutSwapBuffers", glut_SwapBuffers, 0);
	rb_define_module_function(module, "glutGetWindow", glut_GetWindow, 0);
	rb_define_module_function(module, "glutSetWindow", glut_SetWindow, 1);
	rb_define_module_function(module, "glutSetWindowTitle", glut_SetWindowTitle, 1);
	rb_define_module_function(module, "glutSetIconTitle", glut_SetIconTitle, 1);
	rb_define_module_function(module, "glutPositionWindow", glut_PositionWindow, 2);
	rb_define_module_function(module, "glutReshapeWindow", glut_ReshapeWindow, 2);
	rb_define_module_function(module, "glutPopWindow", glut_PopWindow, 0);
	rb_define_module_function(module, "glutPushWindow", glut_PushWindow, 0);
	rb_define_module_function(module, "glutIconifyWindow", glut_IconifyWindow, 0);
	rb_define_module_function(module, "glutShowWindow", glut_ShowWindow, 0);
	rb_define_module_function(module, "glutHideWindow", glut_HideWindow, 0);
	rb_define_module_function(module, "glutFullScreen", glut_FullScreen, 0);
	rb_define_module_function(module, "glutSetCursor", glut_SetCursor, 1);
	rb_define_module_function(module, "glutWarpPointer", glut_WarpPointer, 2);
	rb_define_module_function(module, "glutEstablishOverlay", glut_EstablishOverlay, 0);
	rb_define_module_function(module, "glutRemoveOverlay", glut_RemoveOverlay, 0);
	rb_define_module_function(module, "glutUseLayer", glut_UseLayer, 1);
	rb_define_module_function(module, "glutPostOverlayRedisplay", glut_PostOverlayRedisplay, 0);
	rb_define_module_function(module, "glutShowOverlay", glut_ShowOverlay, 0);
	rb_define_module_function(module, "glutHideOverlay", glut_HideOverlay, 0);
	rb_define_module_function(module, "glutCreateMenu", glut_CreateMenu, 1);
	rb_define_module_function(module, "glutDestroyMenu", glut_DestroyMenu, 1);
	rb_define_module_function(module, "glutGetMenu", glut_GetMenu, 0);
	rb_define_module_function(module, "glutSetMenu", glut_SetMenu, 1);
	rb_define_module_function(module, "glutAddMenuEntry", glut_AddMenuEntry, 2);
	rb_define_module_function(module, "glutAddSubMenu", glut_AddSubMenu, 2);
	rb_define_module_function(module, "glutChangeToMenuEntry", glut_ChangeToMenuEntry, 3);
	rb_define_module_function(module, "glutChangeToSubMenu", glut_ChangeToSubMenu, 3);
	rb_define_module_function(module, "glutRemoveMenuItem", glut_RemoveMenuItem, 1);
	rb_define_module_function(module, "glutAttachMenu", glut_AttachMenu, 1);
	rb_define_module_function(module, "glutDetachMenu", glut_DetachMenu, 1);
	rb_define_module_function(module, "glutSetColor", glut_SetColor, 4);
	rb_define_module_function(module, "glutGetColor", glut_GetColor, 2);
	rb_define_module_function(module, "glutCopyColormap", glut_CopyColormap, 1);
	rb_define_module_function(module, "glutGet", glut_Get, 1);
	rb_define_module_function(module, "glutDeviceGet", glut_DeviceGet, 1);
	rb_define_module_function(module, "glutExtensionSupported", glut_ExtensionSupported, 1);
	rb_define_module_function(module, "glutGetModifiers", glut_GetModifiers, 0);
	rb_define_module_function(module, "glutLayerGet", glut_LayerGet, 1);
	rb_define_module_function(module, "glutBitmapCharacter", glut_BitmapCharacter, 2);
	rb_define_module_function(module, "glutBitmapWidth", glut_BitmapWidth, 2);
	rb_define_module_function(module, "glutStrokeCharacter", glut_StrokeCharacter, 2);
	rb_define_module_function(module, "glutStrokeWidth", glut_StrokeWidth, 2);
	rb_define_module_function(module, "glutBitmapLength", glut_BitmapLength, 2);
	rb_define_module_function(module, "glutStrokeLength", glut_StrokeLength, 2);
	rb_define_module_function(module, "glutWireSphere", glut_WireSphere, 3);
	rb_define_module_function(module, "glutSolidSphere", glut_SolidSphere, 3);
	rb_define_module_function(module, "glutWireCone", glut_WireCone, 4);
	rb_define_module_function(module, "glutSolidCone", glut_SolidCone, 4);
	rb_define_module_function(module, "glutWireCube", glut_WireCube, 1);
	rb_define_module_function(module, "glutSolidCube", glut_SolidCube, 1);
	rb_define_module_function(module, "glutWireTorus", glut_WireTorus, 4);
	rb_define_module_function(module, "glutSolidTorus", glut_SolidTorus, 4);
	rb_define_module_function(module, "glutWireDodecahedron", glut_WireDodecahedron, 0);
	rb_define_module_function(module, "glutSolidDodecahedron", glut_SolidDodecahedron, 0);
	rb_define_module_function(module, "glutWireTeapot", glut_WireTeapot, 1);
	rb_define_module_function(module, "glutSolidTeapot", glut_SolidTeapot, 1);
	rb_define_module_function(module, "glutWireOctahedron", glut_WireOctahedron, 0);
	rb_define_module_function(module, "glutSolidOctahedron", glut_SolidOctahedron, 0);
	rb_define_module_function(module, "glutWireTetrahedron", glut_WireTetrahedron, 0);
	rb_define_module_function(module, "glutSolidTetrahedron", glut_SolidTetrahedron, 0);
	rb_define_module_function(module, "glutWireIcosahedron", glut_WireIcosahedron, 0);
	rb_define_module_function(module, "glutSolidIcosahedron", glut_SolidIcosahedron, 0);
	rb_define_module_function(module, "glutVideoResizeGet", glut_VideoResizeGet, 1);
	rb_define_module_function(module, "glutSetupVideoResizing", glut_SetupVideoResizing, 0);
	rb_define_module_function(module, "glutStopVideoResizing", glut_StopVideoResizing, 0);
	rb_define_module_function(module, "glutVideoResize", glut_VideoResize, 4);
	rb_define_module_function(module, "glutVideoPan", glut_VideoPan, 4);
	rb_define_module_function(module, "glutReportErrors", glut_ReportErrors, 0);
	rb_define_module_function(module, "glutIdleFunc", glut_IdleFunc, 1);
	rb_define_module_function(module, "glutTimerFunc", glut_TimerFunc, 3);
	rb_define_module_function(module, "glutMenuStateFunc", glut_MenuStateFunc, 1);
	rb_define_module_function(module, "glutMenuStatusFunc", glut_MenuStatusFunc, 1);
	rb_define_module_function(module, "glutForceJoystickFunc", glut_ForceJoystickFunc, 0);
	rb_define_module_function(module, "glutGameModeGet", glut_GameModeGet, 1);
	rb_define_module_function(module, "glutSetKeyRepeat", glut_SetKeyRepeat, 1);
	rb_define_module_function(module, "glutIgnoreKeyRepeat", glut_IgnoreKeyRepeat, 1);
	rb_define_module_function(module, "glutPostWindowOverlayRedisplay", glut_PostWindowOverlayRedisplay, 1);
	rb_define_module_function(module, "glutPostWindowRedisplay", glut_PostWindowRedisplay, 1);
	
	rb_define_const(module, "GLUT_API_VERSION", INT2NUM(GLUT_API_VERSION));
	rb_define_const(module, "GLUT_XLIB_IMPLEMENTATION", INT2NUM(GLUT_XLIB_IMPLEMENTATION));
	rb_define_const(module, "GLUT_RGB", INT2NUM(GLUT_RGB));
	rb_define_const(module, "GLUT_RGBA", INT2NUM(GLUT_RGBA));
	rb_define_const(module, "GLUT_INDEX", INT2NUM(GLUT_INDEX));
	rb_define_const(module, "GLUT_SINGLE", INT2NUM(GLUT_SINGLE));
	rb_define_const(module, "GLUT_DOUBLE", INT2NUM(GLUT_DOUBLE));
	rb_define_const(module, "GLUT_ACCUM", INT2NUM(GLUT_ACCUM));
	rb_define_const(module, "GLUT_ALPHA", INT2NUM(GLUT_ALPHA));
	rb_define_const(module, "GLUT_DEPTH", INT2NUM(GLUT_DEPTH));
	rb_define_const(module, "GLUT_STENCIL", INT2NUM(GLUT_STENCIL));
	rb_define_const(module, "GLUT_MULTISAMPLE", INT2NUM(GLUT_MULTISAMPLE));
	rb_define_const(module, "GLUT_STEREO", INT2NUM(GLUT_STEREO));
	rb_define_const(module, "GLUT_LUMINANCE", INT2NUM(GLUT_LUMINANCE));
	rb_define_const(module, "GLUT_LEFT_BUTTON", INT2NUM(GLUT_LEFT_BUTTON));
	rb_define_const(module, "GLUT_MIDDLE_BUTTON", INT2NUM(GLUT_MIDDLE_BUTTON));
	rb_define_const(module, "GLUT_RIGHT_BUTTON", INT2NUM(GLUT_RIGHT_BUTTON));
	rb_define_const(module, "GLUT_DOWN", INT2NUM(GLUT_DOWN));
	rb_define_const(module, "GLUT_UP", INT2NUM(GLUT_UP));
	rb_define_const(module, "GLUT_KEY_F1", INT2NUM(GLUT_KEY_F1));
	rb_define_const(module, "GLUT_KEY_F2", INT2NUM(GLUT_KEY_F2));
	rb_define_const(module, "GLUT_KEY_F3", INT2NUM(GLUT_KEY_F3));
	rb_define_const(module, "GLUT_KEY_F4", INT2NUM(GLUT_KEY_F4));
	rb_define_const(module, "GLUT_KEY_F5", INT2NUM(GLUT_KEY_F5));
	rb_define_const(module, "GLUT_KEY_F6", INT2NUM(GLUT_KEY_F6));
	rb_define_const(module, "GLUT_KEY_F7", INT2NUM(GLUT_KEY_F7));
	rb_define_const(module, "GLUT_KEY_F8", INT2NUM(GLUT_KEY_F8));
	rb_define_const(module, "GLUT_KEY_F9", INT2NUM(GLUT_KEY_F9));
	rb_define_const(module, "GLUT_KEY_F10", INT2NUM(GLUT_KEY_F10));
	rb_define_const(module, "GLUT_KEY_F11", INT2NUM(GLUT_KEY_F11));
	rb_define_const(module, "GLUT_KEY_F12", INT2NUM(GLUT_KEY_F12));
	rb_define_const(module, "GLUT_KEY_LEFT", INT2NUM(GLUT_KEY_LEFT));
	rb_define_const(module, "GLUT_KEY_UP", INT2NUM(GLUT_KEY_UP));
	rb_define_const(module, "GLUT_KEY_RIGHT", INT2NUM(GLUT_KEY_RIGHT));
	rb_define_const(module, "GLUT_KEY_DOWN", INT2NUM(GLUT_KEY_DOWN));
	rb_define_const(module, "GLUT_KEY_PAGE_UP", INT2NUM(GLUT_KEY_PAGE_UP));
	rb_define_const(module, "GLUT_KEY_PAGE_DOWN", INT2NUM(GLUT_KEY_PAGE_DOWN));
	rb_define_const(module, "GLUT_KEY_HOME", INT2NUM(GLUT_KEY_HOME));
	rb_define_const(module, "GLUT_KEY_END", INT2NUM(GLUT_KEY_END));
	rb_define_const(module, "GLUT_KEY_INSERT", INT2NUM(GLUT_KEY_INSERT));
	rb_define_const(module, "GLUT_LEFT", INT2NUM(GLUT_LEFT));
	rb_define_const(module, "GLUT_ENTERED", INT2NUM(GLUT_ENTERED));
	rb_define_const(module, "GLUT_MENU_NOT_IN_USE", INT2NUM(GLUT_MENU_NOT_IN_USE));
	rb_define_const(module, "GLUT_MENU_IN_USE", INT2NUM(GLUT_MENU_IN_USE));
	rb_define_const(module, "GLUT_NOT_VISIBLE", INT2NUM(GLUT_NOT_VISIBLE));
	rb_define_const(module, "GLUT_VISIBLE", INT2NUM(GLUT_VISIBLE));
	rb_define_const(module, "GLUT_HIDDEN", INT2NUM(GLUT_HIDDEN));
	rb_define_const(module, "GLUT_FULLY_RETAINED", INT2NUM(GLUT_FULLY_RETAINED));
	rb_define_const(module, "GLUT_PARTIALLY_RETAINED", INT2NUM(GLUT_PARTIALLY_RETAINED));
	rb_define_const(module, "GLUT_FULLY_COVERED", INT2NUM(GLUT_FULLY_COVERED));
	rb_define_const(module, "GLUT_RED", INT2NUM(GLUT_RED));
	rb_define_const(module, "GLUT_GREEN", INT2NUM(GLUT_GREEN));
	rb_define_const(module, "GLUT_BLUE", INT2NUM(GLUT_BLUE));
	rb_define_const(module, "GLUT_WINDOW_X", INT2NUM(GLUT_WINDOW_X));
	rb_define_const(module, "GLUT_WINDOW_Y", INT2NUM(GLUT_WINDOW_Y));
	rb_define_const(module, "GLUT_WINDOW_WIDTH", INT2NUM(GLUT_WINDOW_WIDTH));
	rb_define_const(module, "GLUT_WINDOW_HEIGHT", INT2NUM(GLUT_WINDOW_HEIGHT));
	rb_define_const(module, "GLUT_WINDOW_BUFFER_SIZE", INT2NUM(GLUT_WINDOW_BUFFER_SIZE));
	rb_define_const(module, "GLUT_WINDOW_STENCIL_SIZE", INT2NUM(GLUT_WINDOW_STENCIL_SIZE));
	rb_define_const(module, "GLUT_WINDOW_DEPTH_SIZE", INT2NUM(GLUT_WINDOW_DEPTH_SIZE));
	rb_define_const(module, "GLUT_WINDOW_RED_SIZE", INT2NUM(GLUT_WINDOW_RED_SIZE));
	rb_define_const(module, "GLUT_WINDOW_GREEN_SIZE", INT2NUM(GLUT_WINDOW_GREEN_SIZE));
	rb_define_const(module, "GLUT_WINDOW_BLUE_SIZE", INT2NUM(GLUT_WINDOW_BLUE_SIZE));
	rb_define_const(module, "GLUT_WINDOW_ALPHA_SIZE", INT2NUM(GLUT_WINDOW_ALPHA_SIZE));
	rb_define_const(module, "GLUT_WINDOW_ACCUM_RED_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_RED_SIZE));
	rb_define_const(module, "GLUT_WINDOW_ACCUM_GREEN_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_GREEN_SIZE));
	rb_define_const(module, "GLUT_WINDOW_ACCUM_BLUE_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_BLUE_SIZE));
	rb_define_const(module, "GLUT_WINDOW_ACCUM_ALPHA_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_ALPHA_SIZE));
	rb_define_const(module, "GLUT_WINDOW_DOUBLEBUFFER", INT2NUM(GLUT_WINDOW_DOUBLEBUFFER));
	rb_define_const(module, "GLUT_WINDOW_RGBA", INT2NUM(GLUT_WINDOW_RGBA));
	rb_define_const(module, "GLUT_WINDOW_PARENT", INT2NUM(GLUT_WINDOW_PARENT));
	rb_define_const(module, "GLUT_WINDOW_NUM_CHILDREN", INT2NUM(GLUT_WINDOW_NUM_CHILDREN));
	rb_define_const(module, "GLUT_WINDOW_COLORMAP_SIZE", INT2NUM(GLUT_WINDOW_COLORMAP_SIZE));
	rb_define_const(module, "GLUT_WINDOW_NUM_SAMPLES", INT2NUM(GLUT_WINDOW_NUM_SAMPLES));
	rb_define_const(module, "GLUT_WINDOW_STEREO", INT2NUM(GLUT_WINDOW_STEREO));
	rb_define_const(module, "GLUT_WINDOW_CURSOR", INT2NUM(GLUT_WINDOW_CURSOR));
	rb_define_const(module, "GLUT_SCREEN_WIDTH", INT2NUM(GLUT_SCREEN_WIDTH));
	rb_define_const(module, "GLUT_SCREEN_HEIGHT", INT2NUM(GLUT_SCREEN_HEIGHT));
	rb_define_const(module, "GLUT_SCREEN_WIDTH_MM", INT2NUM(GLUT_SCREEN_WIDTH_MM));
	rb_define_const(module, "GLUT_SCREEN_HEIGHT_MM", INT2NUM(GLUT_SCREEN_HEIGHT_MM));
	rb_define_const(module, "GLUT_MENU_NUM_ITEMS", INT2NUM(GLUT_MENU_NUM_ITEMS));
	rb_define_const(module, "GLUT_DISPLAY_MODE_POSSIBLE", INT2NUM(GLUT_DISPLAY_MODE_POSSIBLE));
	rb_define_const(module, "GLUT_INIT_WINDOW_X", INT2NUM(GLUT_INIT_WINDOW_X));
	rb_define_const(module, "GLUT_INIT_WINDOW_Y", INT2NUM(GLUT_INIT_WINDOW_Y));
	rb_define_const(module, "GLUT_INIT_WINDOW_WIDTH", INT2NUM(GLUT_INIT_WINDOW_WIDTH));
	rb_define_const(module, "GLUT_INIT_WINDOW_HEIGHT", INT2NUM(GLUT_INIT_WINDOW_HEIGHT));
	rb_define_const(module, "GLUT_INIT_DISPLAY_MODE", INT2NUM(GLUT_INIT_DISPLAY_MODE));
	rb_define_const(module, "GLUT_ELAPSED_TIME", INT2NUM(GLUT_ELAPSED_TIME));
	rb_define_const(module, "GLUT_HAS_KEYBOARD", INT2NUM(GLUT_HAS_KEYBOARD));
	rb_define_const(module, "GLUT_HAS_MOUSE", INT2NUM(GLUT_HAS_MOUSE));
	rb_define_const(module, "GLUT_HAS_SPACEBALL", INT2NUM(GLUT_HAS_SPACEBALL));
	rb_define_const(module, "GLUT_HAS_DIAL_AND_BUTTON_BOX", INT2NUM(GLUT_HAS_DIAL_AND_BUTTON_BOX));
	rb_define_const(module, "GLUT_HAS_TABLET", INT2NUM(GLUT_HAS_TABLET));
	rb_define_const(module, "GLUT_NUM_MOUSE_BUTTONS", INT2NUM(GLUT_NUM_MOUSE_BUTTONS));
	rb_define_const(module, "GLUT_NUM_SPACEBALL_BUTTONS", INT2NUM(GLUT_NUM_SPACEBALL_BUTTONS));
	rb_define_const(module, "GLUT_NUM_BUTTON_BOX_BUTTONS", INT2NUM(GLUT_NUM_BUTTON_BOX_BUTTONS));
	rb_define_const(module, "GLUT_NUM_DIALS", INT2NUM(GLUT_NUM_DIALS));
	rb_define_const(module, "GLUT_NUM_TABLET_BUTTONS", INT2NUM(GLUT_NUM_TABLET_BUTTONS));
	rb_define_const(module, "GLUT_OVERLAY_POSSIBLE", INT2NUM(GLUT_OVERLAY_POSSIBLE));
	rb_define_const(module, "GLUT_LAYER_IN_USE", INT2NUM(GLUT_LAYER_IN_USE));
	rb_define_const(module, "GLUT_HAS_OVERLAY", INT2NUM(GLUT_HAS_OVERLAY));
	rb_define_const(module, "GLUT_TRANSPARENT_INDEX", INT2NUM(GLUT_TRANSPARENT_INDEX));
	rb_define_const(module, "GLUT_NORMAL_DAMAGED", INT2NUM(GLUT_NORMAL_DAMAGED));
	rb_define_const(module, "GLUT_OVERLAY_DAMAGED", INT2NUM(GLUT_OVERLAY_DAMAGED));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_POSSIBLE", INT2NUM(GLUT_VIDEO_RESIZE_POSSIBLE));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_IN_USE", INT2NUM(GLUT_VIDEO_RESIZE_IN_USE));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_X_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_X_DELTA));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_Y_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_Y_DELTA));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_WIDTH_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_WIDTH_DELTA));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_HEIGHT_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_HEIGHT_DELTA));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_X", INT2NUM(GLUT_VIDEO_RESIZE_X));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_Y", INT2NUM(GLUT_VIDEO_RESIZE_Y));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_WIDTH", INT2NUM(GLUT_VIDEO_RESIZE_WIDTH));
	rb_define_const(module, "GLUT_VIDEO_RESIZE_HEIGHT", INT2NUM(GLUT_VIDEO_RESIZE_HEIGHT));
	rb_define_const(module, "GLUT_NORMAL", INT2NUM(GLUT_NORMAL));
	rb_define_const(module, "GLUT_OVERLAY", INT2NUM(GLUT_OVERLAY));
	rb_define_const(module, "GLUT_ACTIVE_SHIFT", INT2NUM(GLUT_ACTIVE_SHIFT));
	rb_define_const(module, "GLUT_ACTIVE_CTRL", INT2NUM(GLUT_ACTIVE_CTRL));
	rb_define_const(module, "GLUT_ACTIVE_ALT", INT2NUM(GLUT_ACTIVE_ALT));
	rb_define_const(module, "GLUT_CURSOR_RIGHT_ARROW", INT2NUM(GLUT_CURSOR_RIGHT_ARROW));
	rb_define_const(module, "GLUT_CURSOR_LEFT_ARROW", INT2NUM(GLUT_CURSOR_LEFT_ARROW));
	rb_define_const(module, "GLUT_CURSOR_INFO", INT2NUM(GLUT_CURSOR_INFO));
	rb_define_const(module, "GLUT_CURSOR_DESTROY", INT2NUM(GLUT_CURSOR_DESTROY));
	rb_define_const(module, "GLUT_CURSOR_HELP", INT2NUM(GLUT_CURSOR_HELP));
	rb_define_const(module, "GLUT_CURSOR_CYCLE", INT2NUM(GLUT_CURSOR_CYCLE));
	rb_define_const(module, "GLUT_CURSOR_SPRAY", INT2NUM(GLUT_CURSOR_SPRAY));
	rb_define_const(module, "GLUT_CURSOR_WAIT", INT2NUM(GLUT_CURSOR_WAIT));
	rb_define_const(module, "GLUT_CURSOR_TEXT", INT2NUM(GLUT_CURSOR_TEXT));
	rb_define_const(module, "GLUT_CURSOR_CROSSHAIR", INT2NUM(GLUT_CURSOR_CROSSHAIR));
	rb_define_const(module, "GLUT_CURSOR_UP_DOWN", INT2NUM(GLUT_CURSOR_UP_DOWN));
	rb_define_const(module, "GLUT_CURSOR_LEFT_RIGHT", INT2NUM(GLUT_CURSOR_LEFT_RIGHT));
	rb_define_const(module, "GLUT_CURSOR_TOP_SIDE", INT2NUM(GLUT_CURSOR_TOP_SIDE));
	rb_define_const(module, "GLUT_CURSOR_BOTTOM_SIDE", INT2NUM(GLUT_CURSOR_BOTTOM_SIDE));
	rb_define_const(module, "GLUT_CURSOR_LEFT_SIDE", INT2NUM(GLUT_CURSOR_LEFT_SIDE));
	rb_define_const(module, "GLUT_CURSOR_RIGHT_SIDE", INT2NUM(GLUT_CURSOR_RIGHT_SIDE));
	rb_define_const(module, "GLUT_CURSOR_TOP_LEFT_CORNER", INT2NUM(GLUT_CURSOR_TOP_LEFT_CORNER));
	rb_define_const(module, "GLUT_CURSOR_TOP_RIGHT_CORNER", INT2NUM(GLUT_CURSOR_TOP_RIGHT_CORNER));
	rb_define_const(module, "GLUT_CURSOR_BOTTOM_RIGHT_CORNER", INT2NUM(GLUT_CURSOR_BOTTOM_RIGHT_CORNER));
	rb_define_const(module, "GLUT_CURSOR_BOTTOM_LEFT_CORNER", INT2NUM(GLUT_CURSOR_BOTTOM_LEFT_CORNER));
	rb_define_const(module, "GLUT_CURSOR_INHERIT", INT2NUM(GLUT_CURSOR_INHERIT));
	rb_define_const(module, "GLUT_CURSOR_NONE", INT2NUM(GLUT_CURSOR_NONE));
	rb_define_const(module, "GLUT_CURSOR_FULL_CROSSHAIR", INT2NUM(GLUT_CURSOR_FULL_CROSSHAIR));

	/* hardcoded, see bitmap_font_map for explanation */
	rb_define_const(module, "GLUT_BITMAP_9_BY_15", INT2NUM(0));
	rb_define_const(module, "GLUT_BITMAP_8_BY_13", INT2NUM(1));
	rb_define_const(module, "GLUT_BITMAP_TIMES_ROMAN_10", INT2NUM(2));
	rb_define_const(module, "GLUT_BITMAP_TIMES_ROMAN_24", INT2NUM(3));
	rb_define_const(module, "GLUT_BITMAP_HELVETICA_10", INT2NUM(4));
	rb_define_const(module, "GLUT_BITMAP_HELVETICA_12", INT2NUM(5));
	rb_define_const(module, "GLUT_BITMAP_HELVETICA_18", INT2NUM(6));
	rb_define_const(module, "GLUT_STROKE_ROMAN", INT2NUM(7));
	rb_define_const(module, "GLUT_STROKE_MONO_ROMAN", INT2NUM(8));

	rb_define_const(module, "GLUT_WINDOW_FORMAT_ID", INT2NUM(GLUT_WINDOW_FORMAT_ID));
	rb_define_const(module, "GLUT_DEVICE_IGNORE_KEY_REPEAT", INT2NUM(GLUT_DEVICE_IGNORE_KEY_REPEAT));
	rb_define_const(module, "GLUT_DEVICE_KEY_REPEAT", INT2NUM(GLUT_DEVICE_KEY_REPEAT));
	rb_define_const(module, "GLUT_HAS_JOYSTICK", INT2NUM(GLUT_HAS_JOYSTICK));
	rb_define_const(module, "GLUT_OWNS_JOYSTICK", INT2NUM(GLUT_OWNS_JOYSTICK));
	rb_define_const(module, "GLUT_JOYSTICK_BUTTONS", INT2NUM(GLUT_JOYSTICK_BUTTONS));
	rb_define_const(module, "GLUT_JOYSTICK_AXES", INT2NUM(GLUT_JOYSTICK_AXES));
	rb_define_const(module, "GLUT_JOYSTICK_POLL_RATE", INT2NUM(GLUT_JOYSTICK_POLL_RATE));
	rb_define_const(module, "GLUT_KEY_REPEAT_OFF", INT2NUM(GLUT_KEY_REPEAT_OFF));
	rb_define_const(module, "GLUT_KEY_REPEAT_ON", INT2NUM(GLUT_KEY_REPEAT_ON));
	rb_define_const(module, "GLUT_KEY_REPEAT_DEFAULT", INT2NUM(GLUT_KEY_REPEAT_DEFAULT));
	rb_define_const(module, "GLUT_JOYSTICK_BUTTON_A", INT2NUM(GLUT_JOYSTICK_BUTTON_A));
	rb_define_const(module, "GLUT_JOYSTICK_BUTTON_B", INT2NUM(GLUT_JOYSTICK_BUTTON_B));
	rb_define_const(module, "GLUT_JOYSTICK_BUTTON_C", INT2NUM(GLUT_JOYSTICK_BUTTON_C));
	rb_define_const(module, "GLUT_JOYSTICK_BUTTON_D", INT2NUM(GLUT_JOYSTICK_BUTTON_D));
	rb_define_const(module, "GLUT_GAME_MODE_ACTIVE", INT2NUM(GLUT_GAME_MODE_ACTIVE));
	rb_define_const(module, "GLUT_GAME_MODE_POSSIBLE", INT2NUM(GLUT_GAME_MODE_POSSIBLE));
	rb_define_const(module, "GLUT_GAME_MODE_WIDTH", INT2NUM(GLUT_GAME_MODE_WIDTH));
	rb_define_const(module, "GLUT_GAME_MODE_HEIGHT", INT2NUM(GLUT_GAME_MODE_HEIGHT));
	rb_define_const(module, "GLUT_GAME_MODE_PIXEL_DEPTH", INT2NUM(GLUT_GAME_MODE_PIXEL_DEPTH));
	rb_define_const(module, "GLUT_GAME_MODE_REFRESH_RATE", INT2NUM(GLUT_GAME_MODE_REFRESH_RATE));
	rb_define_const(module, "GLUT_GAME_MODE_DISPLAY_CHANGED", INT2NUM(GLUT_GAME_MODE_DISPLAY_CHANGED));
	
	
	WINDOW_CALLBACK_DEFINE(DisplayFunc);
	WINDOW_CALLBACK_DEFINE(ReshapeFunc);
	WINDOW_CALLBACK_DEFINE(KeyboardFunc);
	WINDOW_CALLBACK_DEFINE(MouseFunc);
	WINDOW_CALLBACK_DEFINE(MotionFunc);
	WINDOW_CALLBACK_DEFINE(PassiveMotionFunc);
	WINDOW_CALLBACK_DEFINE(EntryFunc);
	WINDOW_CALLBACK_DEFINE(VisibilityFunc);
	WINDOW_CALLBACK_DEFINE(SpecialFunc);
	WINDOW_CALLBACK_DEFINE(SpaceballMotionFunc);
	WINDOW_CALLBACK_DEFINE(SpaceballRotateFunc);
	WINDOW_CALLBACK_DEFINE(SpaceballButtonFunc);
	WINDOW_CALLBACK_DEFINE(ButtonBoxFunc);
	WINDOW_CALLBACK_DEFINE(DialsFunc);
	WINDOW_CALLBACK_DEFINE(TabletMotionFunc);
	WINDOW_CALLBACK_DEFINE(TabletButtonFunc);
	WINDOW_CALLBACK_DEFINE(OverlayDisplayFunc);
	WINDOW_CALLBACK_DEFINE(WindowStatusFunc);
	WINDOW_CALLBACK_DEFINE(KeyboardUpFunc);
	WINDOW_CALLBACK_DEFINE(SpecialUpFunc);
	
	/* special case, 2 params */
	rb_define_module_function(module, "glutJoystickFunc",glut_JoystickFunc , 2);
	rb_global_variable(&JoystickFunc);
	JoystickFunc = rb_ary_new();
	
	rb_gc_register_address(&idle_func);
	rb_gc_register_address(&timer_func);
	rb_gc_register_address(&menustate_func);
}

