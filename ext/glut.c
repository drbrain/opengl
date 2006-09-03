/*
 * Last edit by previous maintainer:
 * 2004/03/02 01:13:06, yoshi
 *
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
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

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <ruby.h>

static int callId; /* 'call' method id */

/* callback define macro */
#define WINDOW_CALLBACK_SETUP(_funcname) \
static VALUE _funcname = Qnil; \
static void glut_ ## _funcname ## Callback(); \
static VALUE \
glut_ ## _funcname(obj,arg1) \
VALUE obj,arg1; \
{ \
    int win; \
    if (!rb_obj_is_kind_of(arg1,rb_cProc) && !NIL_P(arg1)) \
        rb_raise(rb_eTypeError, "GLUT.%s:%s",#_funcname, rb_class2name(CLASS_OF(arg1))); \
    win = glutGetWindow(); \
    if (win == 0) \
        rb_raise(rb_eRuntimeError, "GLUT.%s needs current window", #_funcname); \
    rb_ary_store(_funcname, win, arg1); \
    glut ## _funcname(glut_ ## _funcname ## Callback); \
    return Qnil; \
}

#define WINDOW_CALLBACK_DEFINE(_funcname) \
    rb_define_module_function(mGLUT, # _funcname, glut_ ## _funcname , 1); \
    rb_global_variable(&_funcname); \
    _funcname = rb_ary_new()


/*
 * GLUT Implementation
 */

/* GLUT initialization sub-API. */
static VALUE g_arg_array;

static VALUE glut_Init( int argc, VALUE * argv, VALUE obj)
{
#if 0
    int argcp = 1;
    if (TYPE(arg1) != T_STRING)
    rb_raise(rb_eTypeError, "GLUT.Init:%s", rb_class2name(CLASS_OF(arg1)));
    glutInit(&argcp, (char**)&(RSTRING(arg1)->ptr));
#endif
    int largc;
    char** largv;
    int i, j;
    int find;
    VALUE new_argv;
    VALUE arg1;
    VALUE ptr;
    if (rb_scan_args(argc, argv, "01", &arg1) == 0)
    {
        arg1 = rb_eval_string("ARGV");
    }
    Check_Type(arg1, T_ARRAY);
    largc = RARRAY(arg1)->len+1;
    largv = ALLOCA_N(char*, largc+2);
    largv[0] = STR2CSTR(rb_eval_string("$0"));
    for (i = 1; i < largc; i++)
    {
        largv[i] = STR2CSTR(RARRAY(arg1)->ptr[i-1]);
    }
    largv[i] = NULL;
    glutInit(&largc, largv);
    new_argv = rb_ary_new2(largc-1);
    g_arg_array = rb_ary_new();
    for (i = 0; i < RARRAY(arg1)->len; i++) {
        ptr = RARRAY(arg1)->ptr[i];
        find = 0;
        for (j = 1; largv[j]; j++)
        {
            if (STR2CSTR(ptr) == largv[j])
            {
                rb_ary_push(new_argv, ptr);
                find = 1;
                break;
            }
        }
        if (!find)
        {
            rb_ary_push(g_arg_array, ptr);
        }
    }
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


#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
static VALUE
glut_InitDisplayString(obj,arg1)
VALUE obj,arg1;
{
    if (TYPE(arg1) != T_STRING)
    rb_raise(rb_eTypeError, "GLUT.InitDisplay:%s",rb_class2name(CLASS_OF(arg1)));
    glutInitDisplayString(RSTRING(arg1)->ptr);
    return Qnil;
}
#endif


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


static VALUE
glut_MainLoop(obj)
VALUE obj;
{
    glutMainLoop();
    return Qnil;
}

/* Added by James to reflect MacOSX's CheckLoop. */
static VALUE
glut_CheckLoop(obj)
VALUE obj;
{
    glutMainLoop();
    return Qnil;
}


WINDOW_CALLBACK_SETUP(DisplayFunc);
WINDOW_CALLBACK_SETUP(ReshapeFunc);
WINDOW_CALLBACK_SETUP(KeyboardFunc);
WINDOW_CALLBACK_SETUP(MouseFunc);
WINDOW_CALLBACK_SETUP(MotionFunc);
WINDOW_CALLBACK_SETUP(PassiveMotionFunc);
WINDOW_CALLBACK_SETUP(EntryFunc);
WINDOW_CALLBACK_SETUP(VisibilityFunc);
/*
CALLBACK_DEFINE(IdleFunc);
CALLBACK_DEFINE(TimerFunc);
MENU_CALLBACK_DEFINE(MenuStateFunc);
*/
WINDOW_CALLBACK_SETUP(SpecialFunc);
WINDOW_CALLBACK_SETUP(SpaceballMotionFunc);
WINDOW_CALLBACK_SETUP(SpaceballRotateFunc);
WINDOW_CALLBACK_SETUP(SpaceballButtonFunc);
WINDOW_CALLBACK_SETUP(ButtonBoxFunc);
WINDOW_CALLBACK_SETUP(DialsFunc);
WINDOW_CALLBACK_SETUP(TabletMotionFunc);
WINDOW_CALLBACK_SETUP(TabletButtonFunc);
/*
MENU_CALLBACK_DEFINE(MenuStatusFunc);
*/
WINDOW_CALLBACK_SETUP(OverlayDisplayFunc);
WINDOW_CALLBACK_SETUP(WindowStatusFunc);


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
    if (TYPE(title) != T_STRING)
        rb_raise(rb_eTypeError, "GLUT.CreateWindow:%s", rb_class2name(CLASS_OF(title)));
    ret = glutCreateWindow(RSTRING(title)->ptr);

    /* setup callback */
/*
    glutDisplayFunc(glut_DisplayFuncCallback);
    glutReshapeFunc(glut_ReshapeFuncCallback);
    glutKeyboardFunc(glut_KeyboardFuncCallback);
    glutMouseFunc(glut_MouseFuncCallback);
    glutMotionFunc(glut_MotionFuncCallback);
    glutPassiveMotionFunc(glut_PassiveMotionFuncCallback);
    glutEntryFunc(glut_EntryFuncCallback);
    glutVisibilityFunc(glut_VisibilityFuncCallback);
    glutSpecialFunc(glut_SpecialFuncCallback);
    glutSpaceballMotionFunc(glut_SpaceballMotionFuncCallback);
    glutSpaceballRotateFunc(glut_SpaceballRotateFuncCallback);
    glutSpaceballButtonFunc(glut_SpaceballButtonFuncCallback);
    glutButtonBoxFunc(glut_ButtonBoxFuncCallback);
    glutDialsFunc(glut_DialsFuncCallback);
    glutTabletMotionFunc(glut_TabletMotionFuncCallback);
    glutTabletButtonFunc(glut_TabletButtonFuncCallback);
    glutOverlayDisplayFunc(glut_OverlayDisplayFuncCallback);
    glutWindowStatusFunc(glut_WindowStatusFuncCallback);
*/
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


static VALUE
glut_PostRedisplay(obj)
VALUE obj;
{
    glutPostRedisplay();
    return Qnil;
}


static VALUE
glut_SwapBuffers(obj)
VALUE obj;
{
    glutSwapBuffers();
    return Qnil;
}


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
    if (TYPE(arg1) != T_STRING)
    rb_raise(rb_eTypeError, "GLUT.SetWindowTitle:%s", rb_class2name(CLASS_OF(arg1)));
    glutSetWindowTitle(RSTRING(arg1)->ptr);
    return Qnil;
}


static VALUE
glut_SetIconTitle(obj, arg1)
VALUE obj,arg1;
{
    if (TYPE(arg1) != T_STRING)
    rb_raise(rb_eTypeError, "GLUT.IconTitle:%s", rb_class2name(CLASS_OF(arg1)));
    glutSetIconTitle(RSTRING(arg1)->ptr);
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


static VALUE
glut_PopWindow(obj)
VALUE obj;
{
    glutPopWindow();
    return Qnil;
}


static VALUE
glut_PushWidow(obj)
VALUE obj;
{
    glutPushWindow();
    return Qnil;
}


static VALUE
glut_IconifyWindow(obj)
VALUE obj;
{
    glutIconifyWindow();
    return Qnil;
}


static VALUE
glut_ShowWindow(obj)
VALUE obj;
{
    glutShowWindow();
    return Qnil;
}


static VALUE
glut_HideWindow(obj)
VALUE obj;
{
    glutHideWindow();
    return Qnil;
}


#if (GLUT_API_VERSION >= 3)
static VALUE
glut_FullScreen(obj)
VALUE obj;
{
    glutFullScreen();
    return Qnil;
}


static VALUE
glut_SetCursor(obj,arg1)
VALUE obj,arg1;
{
    int cursor;
    cursor = NUM2INT(arg1);
    glutSetCursor(cursor);
    return Qnil;
}


#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
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
#endif


/* GLUT overlay sub-API. */
static VALUE
glut_EstablishOverlay(obj)
VALUE obj;
{
    glutEstablishOverlay();
    return Qnil;
}


static VALUE
glut_RemoveOverlay(obj)
VALUE obj;
{
    glutRemoveOverlay();
    return Qnil;
}


static VALUE
glut_UseLayer(obj,arg1)
{
    GLenum layer;
    layer = (GLenum)NUM2INT(arg1);
    glutUseLayer(layer);
    return Qnil;
}


static VALUE
glut_PostOverlayRedisplay(obj)
VALUE obj;
{
    glutPostOverlayRedisplay();
    return Qnil;
}


static VALUE
glut_ShowOverlay(obj)
VALUE obj;
{
    glutShowOverlay();
    return Qnil;
}


static VALUE
glut_HideOverlay(obj)
VALUE obj;
{
    glutHideOverlay();
    return Qnil;
}
#endif


/* GLUT menu sub-API. */
static VALUE g_menucallback = Qnil;
static VALUE g_menuargs = Qnil;
static void
glut_CreateMenuCallback(value)
int value;
{
    VALUE arg_pair;
    VALUE func;
    arg_pair = (VALUE)value;
    func = rb_hash_aref(g_menucallback, rb_ary_entry(arg_pair, 0));
    rb_funcall(func, callId, 1, rb_ary_entry(arg_pair, 1));
}

    
static VALUE
glut_CreateMenu(obj,arg1)
VALUE obj,arg1;
{
    int menu;
    VALUE ret;
    if (!rb_obj_is_kind_of(arg1,rb_cProc) && !NIL_P(arg1))
    rb_raise(rb_eTypeError, "GLUT.CreateMenu:%s", rb_class2name(CLASS_OF(arg1)));
    menu = glutCreateMenu(glut_CreateMenuCallback);
    ret = INT2FIX(menu);
    rb_hash_aset(g_menucallback, ret, arg1);
    rb_hash_aset(g_menuargs, ret, rb_ary_new());
    return ret;
}

    
static VALUE
glut_DestroyMenu(obj,arg1)
VALUE obj,arg1;
{
    int menu;
    menu = INT2FIX(arg1);
    glutDestroyMenu(menu);
    rb_hash_aset(g_menucallback, menu, Qnil);
    rb_hash_aset(g_menuargs, menu, Qnil);
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
    int menu;
    menu = NUM2INT(arg1);
    glutSetMenu(menu);
    return Qnil;
}


static VALUE
glut_AddMenuEntry(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    int value;
    int curmenuid;
    VALUE arg_ary;
    VALUE arg_pair;
    if (TYPE(arg1) != T_STRING)
        rb_raise(rb_eTypeError, "GLUT.AddMenuEntry:%s", rb_class2name(CLASS_OF(arg1)));
    curmenuid = glutGetMenu();
    if (curmenuid == 0)
        rb_raise(rb_eRuntimeError, "GLUT.AddMenuEntry needs current menu");
    arg_ary = rb_hash_aref(g_menuargs, INT2FIX(curmenuid));
    arg_pair = rb_ary_new2(2);
    rb_ary_store(arg_pair, 0, INT2FIX(curmenuid));
    rb_ary_store(arg_pair, 1, arg2);
    rb_ary_push(arg_ary, arg_pair);
    glutAddMenuEntry(RSTRING(arg1)->ptr, arg_pair);
    return Qnil;
}


static VALUE
glut_AddSubMenu(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    int value;
    if (TYPE(arg1) != T_STRING)
        rb_raise(rb_eTypeError, "GLUT.AddSubMenu:%s", rb_class2name(CLASS_OF(arg1)));
    value = NUM2INT(arg2);
    glutAddSubMenu(RSTRING(arg1)->ptr, value);
    return Qnil;
}


static VALUE glut_ChangeToMenuEntry(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    VALUE arg_ary;
    VALUE arg_pair;
    int item,value;
    int curmenuid;
    item = NUM2INT(arg1);
    if (TYPE(arg2) != T_STRING)
        rb_raise(rb_eTypeError, "GLUT.ChangeToMenuEntry:%s", rb_class2name(CLASS_OF(arg1)));
    curmenuid = glutGetMenu();
    if (curmenuid == 0)
        rb_raise(rb_eRuntimeError, "GLUT.ChangeToMenuEntry needs current menu");
    arg_ary = rb_hash_aref(g_menuargs, INT2FIX(curmenuid));
    arg_pair = rb_ary_new2(2);
    rb_ary_store(arg_pair, 0, INT2FIX(curmenuid));
    rb_ary_store(arg_pair, 1, arg2);
    rb_ary_store(arg_ary, item, arg_pair);
    glutChangeToMenuEntry(item, RSTRING(arg2)->ptr, arg_pair);
    return Qnil;
}


static VALUE glut_ChangeToSubMenu(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    int item,submenu;
    item = NUM2INT(arg1);
    submenu = NUM2INT(arg3);
    if (TYPE(arg2) != T_STRING)
        rb_raise(rb_eTypeError, "GLUT.ChangeToSubMenu:%s",
            rb_class2name(CLASS_OF(arg1)));
    glutChangeToSubMenu(item, RSTRING(arg2)->ptr, submenu);
    return Qnil;
}


static VALUE glut_RemoveMenuItem( VALUE obj, VALUE arg1 )
{
    int item;
    int curmenuid;
    VALUE arg_ary;
    item = NUM2INT(arg1);
    glutRemoveMenuItem(item);
    curmenuid = glutGetMenu();
    if (curmenuid == 0)
        rb_raise(rb_eRuntimeError, "GLUT.RemoveMenuItem needs current menu");
    arg_ary = rb_hash_aref(g_menuargs, INT2FIX(curmenuid));
    rb_ary_delete(arg_ary, item);
    return Qnil;
}


static VALUE
glut_AttachMenu(obj,arg1)
VALUE obj, arg1;
{
    int button;
    button = NUM2INT(arg1);
    glutAttachMenu(button);
    return Qnil;
}


static VALUE
glut_DetachMenu(obj,arg1)
VALUE obj, arg1;
{
    int button;
    button = NUM2INT(arg1);
    glutDetachMenu(button);
    return Qnil;
}


/* GLUT  sub-API. */
static void glut_DisplayFuncCallback(void)
{
    VALUE func;
    func = rb_ary_entry(DisplayFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 0);
}


static void
glut_ReshapeFuncCallback(width, height)
int width, height;
{
    VALUE func;
    func = rb_ary_entry( ReshapeFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2, INT2FIX(width), INT2FIX(height));
}


static void
glut_KeyboardFuncCallback(key, x, y)
unsigned char key;
int x,y;
{
    VALUE func;
    func = rb_ary_entry(KeyboardFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 3, INT2FIX(key), INT2FIX(x), INT2FIX(y));
}


static void
glut_MouseFuncCallback(button, state, x, y)
int button, state, x, y;
{
    VALUE func;
    func = rb_ary_entry(MouseFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 4, INT2FIX(button), INT2FIX(state), INT2FIX(x), INT2FIX(y));
}


static void
glut_MotionFuncCallback(x, y)
int x, y;
{
    VALUE func;
    func = rb_ary_entry(MotionFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2FIX(x), INT2FIX(y));
}


static void
glut_PassiveMotionFuncCallback(x, y)
int x, y;
{
    VALUE func;
    func = rb_ary_entry(PassiveMotionFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2FIX(x), INT2FIX(y));
}


static void
glut_EntryFuncCallback(state)
int state;
{
    VALUE func;
    func = rb_ary_entry(EntryFunc,glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 1, INT2NUM(state));
}


static void
glut_VisibilityFuncCallback(state)
int state;
{
    VALUE func;
    func = rb_ary_entry(VisibilityFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 1, INT2NUM(state));
}


static VALUE idle_func = Qnil;
static void
glut_IdleFuncCallback()
{
    if (!NIL_P(idle_func))
        rb_funcall(idle_func, callId, 0);
}


static VALUE
glut_IdleFunc(obj, arg1)
VALUE obj,arg1;
{
    if (!rb_obj_is_kind_of(arg1,rb_cProc) && !NIL_P(arg1)) 
    rb_raise(rb_eTypeError, "glutIdleFunc:%s", rb_class2name(CLASS_OF(arg1)));
    idle_func = arg1;
    glutIdleFunc(glut_IdleFuncCallback);
    return Qnil;
}


static VALUE timer_func = Qnil;
static void
glut_TimerFuncCallback(value)
int value;
{
    if (!NIL_P(timer_func))
        rb_funcall(timer_func, callId, 1, INT2NUM(value));
}


static VALUE
glut_TimerFunc(obj, arg1, arg2, arg3)
VALUE obj,arg1,arg2,arg3;
{
    unsigned int millis;
    int value;
    millis = (unsigned int)NUM2INT(arg1);
    value = NUM2INT(arg3);
    if (!rb_obj_is_kind_of(arg2,rb_cProc)) 
    rb_raise(rb_eTypeError, "glutTimerFunc:%s", rb_class2name(CLASS_OF(arg2)));
    timer_func = arg2;
    glutTimerFunc(millis, glut_TimerFuncCallback, value);
    return Qnil;
}


static VALUE menustate_func = Qnil;
static void
glut_MenuStateFuncCallback(state)
int state;
{
    if (!NIL_P(menustate_func))
        rb_funcall(menustate_func, callId, 1, INT2NUM(state));
}


static VALUE
glut_MenuStateFunc(obj, arg1)
VALUE obj,arg1;
{
    if (!rb_obj_is_kind_of(arg1,rb_cProc)) 
    rb_raise(rb_eTypeError, "glutMenuStateFunc:%s",
              rb_class2name(CLASS_OF(arg1)));
    menustate_func = arg1;
    glutMenuStateFunc(glut_MenuStateFuncCallback);
    return Qnil;
}


#if (GLUT_API_VERSION >= 2)
static void
glut_SpecialFuncCallback(key, x, y)
int key, x, y;
{
    VALUE func;
    func = rb_ary_entry(SpecialFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 3,INT2NUM(key), INT2FIX(x), INT2FIX(y));
}


static void
glut_SpaceballMotionFuncCallback(x, y, z)
int x,y,z;
{
    VALUE func;
    func = rb_ary_entry(SpaceballMotionFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 3,INT2NUM(x), INT2FIX(y), INT2FIX(z));
}


static void
glut_SpaceballRotateFuncCallback(x, y, z)
int x,y,z;
{
    VALUE func;
    func = rb_ary_entry(SpaceballRotateFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 3,INT2NUM(x), INT2FIX(y), INT2FIX(z));
}


static void
glut_SpaceballButtonFuncCallback(button, state)
int button, state;
{
    VALUE func;
    func = rb_ary_entry(SpaceballButtonFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2NUM(button), INT2NUM(state));
}


static void
glut_ButtonBoxFuncCallback(button, state)
int button, state;
{
    VALUE func;
    func = rb_ary_entry(ButtonBoxFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2NUM(button), INT2NUM(state));
}


static void
glut_DialsFuncCallback(dial, value)
int dial, value;
{
    VALUE func;
    func = rb_ary_entry(DialsFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2NUM(dial), INT2NUM(value));
}


static void
glut_TabletMotionFuncCallback(x, y)
int x, y;
{
    VALUE func;
    func = rb_ary_entry(TabletMotionFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 2,INT2NUM(x), INT2NUM(y));
}


static void
glut_TabletButtonFuncCallback(button, state, x, y)
int button, state, x, y;
{
    VALUE func;
    func = rb_ary_entry(TabletButtonFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, 4, INT2NUM(button), INT2NUM(state), INT2NUM(x), INT2NUM(y));
}


#if (GLUT_API_VERSION >= 3)
/*
extern void APIENTRY glutMenuStatusFunc(void (*)(int status, int x, int y));
*/
static void
glut_OverlayDisplayFuncCallback()
{
    VALUE func;
    func = rb_ary_entry(OverlayDisplayFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 0);
}


#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
static void
glut_WindowStatusFuncCallback(state)
int state;
{
    VALUE func;
    func = rb_ary_entry(OverlayDisplayFunc, glutGetWindow());
    if (!NIL_P(func))
        rb_funcall(func, callId, 1, INT2NUM(state));
}
#endif
#endif
#endif


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


#if (GLUT_API_VERSION >= 2)
/* GLUT extension support sub-API */
static VALUE
glut_ExtensionSupported(obj,arg1)
VALUE obj,arg1;
{
    int ret;
    if (TYPE(arg1) != T_STRING)
        rb_raise(rb_eTypeError, "glutExtensionSupported:%s",
                 rb_class2name(CLASS_OF(arg1)));
    ret = glutExtensionSupported(RSTRING(arg1)->ptr);
    return INT2NUM(ret);
}
#endif


#if (GLUT_API_VERSION >= 3)
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
#endif



/* GLUT font sub-API */
static VALUE
glut_BitmapCharacter(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    int font;
    int character;
    font = NUM2INT(arg1);
    character = NUM2INT(arg2);
    glutBitmapCharacter((void*)font, character);
    return Qnil;
}

/* Added by James since the normal function is messed up. His comment:
 * > BitmapCharacterX is my own ugly, lazy hack to avoid bus errors when
 * > trying to display text via GLUT. What really needs to happen is for
 * > someone more experienced with Ruby extensions to figure out why we
 * > can't pass the font values as arguments to this function without it
 * > falling over!
 */
static VALUE
glut_BitmapCharacterX(obj,arg2)
VALUE obj,arg2;
{
    int font;
    int character;
    /* font = NUM2INT(arg1); */
    character = NUM2INT(arg2);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, character);
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
    ret = glutBitmapWidth((void*)font, character);
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
    glutStrokeCharacter((void*)font, character);
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
    ret = glutStrokeWidth((void*)font, character);
    return INT2NUM(ret);
}


#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
static VALUE
glut_BitmapLength(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    int font;
    int ret;
    if (TYPE(arg2) != T_STRING) rb_raise(rb_eTypeError, "glutBitmapLength:%s",
              rb_class2name(CLASS_OF(arg2)));
    font = NUM2INT(arg1);
    ret = glutBitmapLength((void *)font, (const unsigned char*)RSTRING(arg2)->ptr);
    return INT2NUM(ret);
}


static VALUE
glut_StrokeLength(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    int font;
    int ret;
    if (TYPE(arg2) != T_STRING) rb_raise(rb_eTypeError, "glutStrokeLength:%s",
              rb_class2name(CLASS_OF(arg2)));
    font = NUM2INT(arg1);
    ret = glutStrokeLength((void *)font, (const unsigned char*)RSTRING(arg2)->ptr);
    return INT2NUM(ret);
}
#endif


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


static VALUE
glut_WireDodecahedron(obj)
VALUE obj;
{
    glutWireDodecahedron();
    return Qnil;
}


static VALUE
glut_SolidDodecahedron(obj)
VALUE obj;
{
    glutSolidDodecahedron();
    return Qnil;
}


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


static VALUE
glut_WireOctahedron(obj)
VALUE obj;
{
    glutWireOctahedron();
    return Qnil;
}


static VALUE
glut_SolidOctahedron(obj)
VALUE obj;
{
    glutSolidOctahedron();
    return Qnil;
}


static VALUE
glut_WireTetrahedron(obj)
VALUE obj;
{
    glutWireTetrahedron();
    return Qnil;
}


static VALUE
glut_SolidTetrahedron(obj)
VALUE obj;
{
    glutSolidTetrahedron();
    return Qnil;
}


static VALUE
glut_WireIcosahedron(obj)
VALUE obj;
{
    glutWireIcosahedron();
    return Qnil;
}


static VALUE
glut_SolidIcosahedron(obj)
VALUE obj;
{
    glutSolidIcosahedron();
    return Qnil;
}


#if (GLUT_API_VERSION >= 4 || GLUT_XLIB_IMPLEMENTATION >= 9)
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


static VALUE
glut_SetupVideoResizing(obj)
VALUE obj;
{
    glutSetupVideoResizing();
    return Qnil;
}


static VALUE
glut_StopVideoResizing(obj)
VALUE obj;
{
    glutStopVideoResizing();
    return Qnil;
}


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
static VALUE
glut_ReportErrors(obj)
VALUE obj;
{
    glutReportErrors();
    return Qnil;
}
#endif


/* Added by James. */
static VALUE
glut_GameModeString(obj,arg1)
VALUE obj,arg1;
{
    if (TYPE(arg1) != T_STRING)
        rb_raise(rb_eTypeError, "glutGameModeString:%s",
                 rb_class2name(CLASS_OF(arg1)));
    glutGameModeString((const char*)RSTRING(arg1)->ptr);
    return Qnil;
}


static VALUE
glut_EnterGameMode(obj)
VALUE obj;
{
    glutEnterGameMode();
    return Qnil;
}
/* end "Added by James." */


static VALUE mGLUT;

void Init_glut()
{
    mGLUT = rb_define_module("GLUT");

    rb_global_variable( &g_arg_array );
    rb_global_variable( &g_menucallback );
    rb_global_variable( &g_menuargs );
    g_menucallback = rb_hash_new();
    g_menuargs = rb_hash_new();

    rb_define_module_function(mGLUT, "Init", glut_Init, -1);
    rb_define_module_function(mGLUT, "InitDisplayMode", glut_InitDisplayMode, 1);
    rb_define_module_function(mGLUT, "InitDisplayString", glut_InitDisplayString, 1);
    rb_define_module_function(mGLUT, "InitWindowPosition", glut_InitWindowPosition, 2);
    rb_define_module_function(mGLUT, "InitWindowSize", glut_InitWindowSize, 2);
    rb_define_module_function(mGLUT, "MainLoop", glut_MainLoop, 0);
    
    /* Added by James. */
    rb_define_module_function(mGLUT, "CheckLoop", glut_CheckLoop, 0);
    rb_define_module_function(mGLUT, "GameModeString", glut_GameModeString, 1);
    rb_define_module_function(mGLUT, "EnterGameMode", glut_EnterGameMode, 0);
    
    rb_define_module_function(mGLUT, "CreateWindow", glut_CreateWindow, -1);
    rb_define_module_function(mGLUT, "CreateSubWindow", glut_CreateSubWindow, 5);
    rb_define_module_function(mGLUT, "DestroyWindow", glut_DestroyWindow, 1);
    rb_define_module_function(mGLUT, "PostRedisplay", glut_PostRedisplay, 0);
    rb_define_module_function(mGLUT, "SwapBuffers", glut_SwapBuffers, 0);
    rb_define_module_function(mGLUT, "GetWindow", glut_GetWindow, 0);
    rb_define_module_function(mGLUT, "SetWindow", glut_SetWindow, 1);
    rb_define_module_function(mGLUT, "SetWindowTitle", glut_SetWindowTitle, 1);
    rb_define_module_function(mGLUT, "SetIconTitle", glut_SetIconTitle, 1);
    rb_define_module_function(mGLUT, "PositionWindow", glut_PositionWindow, 2);
    rb_define_module_function(mGLUT, "ReshapeWindow", glut_ReshapeWindow, 2);
    rb_define_module_function(mGLUT, "PopWindow", glut_PopWindow, 0);
    rb_define_module_function(mGLUT, "PushWidow", glut_PushWidow, 0);
    rb_define_module_function(mGLUT, "IconifyWindow", glut_IconifyWindow, 0);
    rb_define_module_function(mGLUT, "ShowWindow", glut_ShowWindow, 0);
    rb_define_module_function(mGLUT, "HideWindow", glut_HideWindow, 0);
    rb_define_module_function(mGLUT, "FullScreen", glut_FullScreen, 0);
    rb_define_module_function(mGLUT, "SetCursor", glut_SetCursor, 1);
    rb_define_module_function(mGLUT, "WarpPointer", glut_WarpPointer, 2);
    rb_define_module_function(mGLUT, "EstablishOverlay", glut_EstablishOverlay, 0);
    rb_define_module_function(mGLUT, "RemoveOverlay", glut_RemoveOverlay, 0);
    rb_define_module_function(mGLUT, "UseLayer", glut_UseLayer, 1);
    rb_define_module_function(mGLUT, "PostOverlayRedisplay", glut_PostOverlayRedisplay, 0);
    rb_define_module_function(mGLUT, "ShowOverlay", glut_ShowOverlay, 0);
    rb_define_module_function(mGLUT, "HideOverlay", glut_HideOverlay, 0);
    rb_define_module_function(mGLUT, "CreateMenu", glut_CreateMenu, 1);
    rb_define_module_function(mGLUT, "DestroyMenu", glut_DestroyMenu, 1);
    rb_define_module_function(mGLUT, "GetMenu", glut_GetMenu, 0);
    rb_define_module_function(mGLUT, "SetMenu", glut_SetMenu, 1);
    rb_define_module_function(mGLUT, "AddMenuEntry", glut_AddMenuEntry, 2);
    rb_define_module_function(mGLUT, "AddSubMenu", glut_AddSubMenu, 2);
    rb_define_module_function(mGLUT, "ChangeToMenuEntry", glut_ChangeToMenuEntry, 3);
    rb_define_module_function(mGLUT, "ChangeToSubMenu", glut_ChangeToSubMenu, 3);
    rb_define_module_function(mGLUT, "RemoveMenuItem", glut_RemoveMenuItem, 1);
    rb_define_module_function(mGLUT, "AttachMenu", glut_AttachMenu, 1);
    rb_define_module_function(mGLUT, "DetachMenu", glut_DetachMenu, 1);

    rb_define_module_function(mGLUT, "SetColor", glut_SetColor, 4);
    rb_define_module_function(mGLUT, "GetColor", glut_GetColor, 2);
    rb_define_module_function(mGLUT, "CopyColormap", glut_CopyColormap, 1);
    rb_define_module_function(mGLUT, "Get", glut_Get, 1);
    rb_define_module_function(mGLUT, "DeviceGet", glut_DeviceGet, 1);
    rb_define_module_function(mGLUT, "ExtensionSupported", glut_ExtensionSupported, 1);
    rb_define_module_function(mGLUT, "GetModifiers", glut_GetModifiers, 0);
    rb_define_module_function(mGLUT, "LayerGet", glut_LayerGet, 1);
    rb_define_module_function(mGLUT, "BitmapCharacter", glut_BitmapCharacter, 2);
    
    /* Added by James. */
    rb_define_module_function(mGLUT, "BitmapCharacterX", glut_BitmapCharacterX, 1);
    
    rb_define_module_function(mGLUT, "BitmapWidth", glut_BitmapWidth, 2);
    rb_define_module_function(mGLUT, "StrokeCharacter", glut_StrokeCharacter, 2);
    rb_define_module_function(mGLUT, "StrokeWidth", glut_StrokeWidth, 2);
    rb_define_module_function(mGLUT, "BitmapLength", glut_BitmapLength, 2);
    rb_define_module_function(mGLUT, "StrokeLength", glut_StrokeLength, 2);
    rb_define_module_function(mGLUT, "WireSphere", glut_WireSphere, 3);
    rb_define_module_function(mGLUT, "SolidSphere", glut_SolidSphere, 3);
    rb_define_module_function(mGLUT, "WireCone", glut_WireCone, 4);
    rb_define_module_function(mGLUT, "SolidCone", glut_SolidCone, 4);
    rb_define_module_function(mGLUT, "WireCube", glut_WireCube, 1);
    rb_define_module_function(mGLUT, "SolidCube", glut_SolidCube, 1);
    rb_define_module_function(mGLUT, "WireTorus", glut_WireTorus, 4);
    rb_define_module_function(mGLUT, "SolidTorus", glut_SolidTorus, 4);
    rb_define_module_function(mGLUT, "WireDodecahedron", glut_WireDodecahedron, 0);
    rb_define_module_function(mGLUT, "SolidDodecahedron", glut_SolidDodecahedron, 0);
    rb_define_module_function(mGLUT, "WireTeapot", glut_WireTeapot, 1);
    rb_define_module_function(mGLUT, "SolidTeapot", glut_SolidTeapot, 1);
    rb_define_module_function(mGLUT, "WireOctahedron", glut_WireOctahedron, 0);
    rb_define_module_function(mGLUT, "SolidOctahedron", glut_SolidOctahedron, 0);
    rb_define_module_function(mGLUT, "WireTetrahedron", glut_WireTetrahedron, 0);
    rb_define_module_function(mGLUT, "SolidTetrahedron", glut_SolidTetrahedron, 0);
    rb_define_module_function(mGLUT, "WireIcosahedron", glut_WireIcosahedron, 0);
    rb_define_module_function(mGLUT, "SolidIcosahedron", glut_SolidIcosahedron, 0);
    rb_define_module_function(mGLUT, "VideoResizeGet", glut_VideoResizeGet, 1);
    rb_define_module_function(mGLUT, "SetupVideoResizing", glut_SetupVideoResizing, 0);
    rb_define_module_function(mGLUT, "StopVideoResizing", glut_StopVideoResizing, 0);
    rb_define_module_function(mGLUT, "VideoResize", glut_VideoResize, 4);
    rb_define_module_function(mGLUT, "VideoPan", glut_VideoPan, 4);
    rb_define_module_function(mGLUT, "ReportErrors", glut_ReportErrors, 0);
    rb_define_module_function(mGLUT, "IdleFunc", glut_IdleFunc, 1);
    rb_define_module_function(mGLUT, "TimerFunc", glut_TimerFunc, 3);

    rb_define_const(mGLUT, "API_VERSION", INT2NUM(GLUT_API_VERSION));
    rb_define_const(mGLUT, "XLIB_IMPLEMENTATION", INT2NUM(GLUT_XLIB_IMPLEMENTATION));
    rb_define_const(mGLUT, "RGB", INT2NUM(GLUT_RGB));
    rb_define_const(mGLUT, "RGBA", INT2NUM(GLUT_RGBA));
    rb_define_const(mGLUT, "INDEX", INT2NUM(GLUT_INDEX));
    rb_define_const(mGLUT, "SINGLE", INT2NUM(GLUT_SINGLE));
    rb_define_const(mGLUT, "DOUBLE", INT2NUM(GLUT_DOUBLE));
    rb_define_const(mGLUT, "ACCUM", INT2NUM(GLUT_ACCUM));
    rb_define_const(mGLUT, "ALPHA", INT2NUM(GLUT_ALPHA));
    rb_define_const(mGLUT, "DEPTH", INT2NUM(GLUT_DEPTH));
    rb_define_const(mGLUT, "STENCIL", INT2NUM(GLUT_STENCIL));
    rb_define_const(mGLUT, "MULTISAMPLE", INT2NUM(GLUT_MULTISAMPLE));
    rb_define_const(mGLUT, "STEREO", INT2NUM(GLUT_STEREO));
    rb_define_const(mGLUT, "LUMINANCE", INT2NUM(GLUT_LUMINANCE));
    rb_define_const(mGLUT, "LEFT_BUTTON", INT2NUM(GLUT_LEFT_BUTTON));
    rb_define_const(mGLUT, "MIDDLE_BUTTON", INT2NUM(GLUT_MIDDLE_BUTTON));
    rb_define_const(mGLUT, "RIGHT_BUTTON", INT2NUM(GLUT_RIGHT_BUTTON));
    rb_define_const(mGLUT, "DOWN", INT2NUM(GLUT_DOWN));
    rb_define_const(mGLUT, "UP", INT2NUM(GLUT_UP));
    rb_define_const(mGLUT, "KEY_F1", INT2NUM(GLUT_KEY_F1));
    rb_define_const(mGLUT, "KEY_F2", INT2NUM(GLUT_KEY_F2));
    rb_define_const(mGLUT, "KEY_F3", INT2NUM(GLUT_KEY_F3));
    rb_define_const(mGLUT, "KEY_F4", INT2NUM(GLUT_KEY_F4));
    rb_define_const(mGLUT, "KEY_F5", INT2NUM(GLUT_KEY_F5));
    rb_define_const(mGLUT, "KEY_F6", INT2NUM(GLUT_KEY_F6));
    rb_define_const(mGLUT, "KEY_F7", INT2NUM(GLUT_KEY_F7));
    rb_define_const(mGLUT, "KEY_F8", INT2NUM(GLUT_KEY_F8));
    rb_define_const(mGLUT, "KEY_F9", INT2NUM(GLUT_KEY_F9));
    rb_define_const(mGLUT, "KEY_F10", INT2NUM(GLUT_KEY_F10));
    rb_define_const(mGLUT, "KEY_F11", INT2NUM(GLUT_KEY_F11));
    rb_define_const(mGLUT, "KEY_F12", INT2NUM(GLUT_KEY_F12));
    rb_define_const(mGLUT, "KEY_LEFT", INT2NUM(GLUT_KEY_LEFT));
    rb_define_const(mGLUT, "KEY_UP", INT2NUM(GLUT_KEY_UP));
    rb_define_const(mGLUT, "KEY_RIGHT", INT2NUM(GLUT_KEY_RIGHT));
    rb_define_const(mGLUT, "KEY_DOWN", INT2NUM(GLUT_KEY_DOWN));
    rb_define_const(mGLUT, "KEY_PAGE_UP", INT2NUM(GLUT_KEY_PAGE_UP));
    rb_define_const(mGLUT, "KEY_PAGE_DOWN", INT2NUM(GLUT_KEY_PAGE_DOWN));
    rb_define_const(mGLUT, "KEY_HOME", INT2NUM(GLUT_KEY_HOME));
    rb_define_const(mGLUT, "KEY_END", INT2NUM(GLUT_KEY_END));
    rb_define_const(mGLUT, "KEY_INSERT", INT2NUM(GLUT_KEY_INSERT));
    rb_define_const(mGLUT, "LEFT", INT2NUM(GLUT_LEFT));
    rb_define_const(mGLUT, "ENTERED", INT2NUM(GLUT_ENTERED));
    rb_define_const(mGLUT, "MENU_NOT_IN_USE", INT2NUM(GLUT_MENU_NOT_IN_USE));
    rb_define_const(mGLUT, "MENU_IN_USE", INT2NUM(GLUT_MENU_IN_USE));
    rb_define_const(mGLUT, "NOT_VISIBLE", INT2NUM(GLUT_NOT_VISIBLE));
    rb_define_const(mGLUT, "VISIBLE", INT2NUM(GLUT_VISIBLE));
    rb_define_const(mGLUT, "HIDDEN", INT2NUM(GLUT_HIDDEN));
    rb_define_const(mGLUT, "FULLY_RETAINED", INT2NUM(GLUT_FULLY_RETAINED));
    rb_define_const(mGLUT, "PARTIALLY_RETAINED", INT2NUM(GLUT_PARTIALLY_RETAINED));
    rb_define_const(mGLUT, "FULLY_COVERED", INT2NUM(GLUT_FULLY_COVERED));
    rb_define_const(mGLUT, "RED", INT2NUM(GLUT_RED));
    rb_define_const(mGLUT, "GREEN", INT2NUM(GLUT_GREEN));
    rb_define_const(mGLUT, "BLUE", INT2NUM(GLUT_BLUE));
    rb_define_const(mGLUT, "WINDOW_X", INT2NUM(GLUT_WINDOW_X));
    rb_define_const(mGLUT, "WINDOW_Y", INT2NUM(GLUT_WINDOW_Y));
    rb_define_const(mGLUT, "WINDOW_WIDTH", INT2NUM(GLUT_WINDOW_WIDTH));
    rb_define_const(mGLUT, "WINDOW_HEIGHT", INT2NUM(GLUT_WINDOW_HEIGHT));
    rb_define_const(mGLUT, "WINDOW_BUFFER_SIZE", INT2NUM(GLUT_WINDOW_BUFFER_SIZE));
    rb_define_const(mGLUT, "WINDOW_STENCIL_SIZE", INT2NUM(GLUT_WINDOW_STENCIL_SIZE));
    rb_define_const(mGLUT, "WINDOW_DEPTH_SIZE", INT2NUM(GLUT_WINDOW_DEPTH_SIZE));
    rb_define_const(mGLUT, "WINDOW_RED_SIZE", INT2NUM(GLUT_WINDOW_RED_SIZE));
    rb_define_const(mGLUT, "WINDOW_GREEN_SIZE", INT2NUM(GLUT_WINDOW_GREEN_SIZE));
    rb_define_const(mGLUT, "WINDOW_BLUE_SIZE", INT2NUM(GLUT_WINDOW_BLUE_SIZE));
    rb_define_const(mGLUT, "WINDOW_ALPHA_SIZE", INT2NUM(GLUT_WINDOW_ALPHA_SIZE));
    rb_define_const(mGLUT, "WINDOW_ACCUM_RED_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_RED_SIZE));
    rb_define_const(mGLUT, "WINDOW_ACCUM_GREEN_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_GREEN_SIZE));
    rb_define_const(mGLUT, "WINDOW_ACCUM_BLUE_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_BLUE_SIZE));
    rb_define_const(mGLUT, "WINDOW_ACCUM_ALPHA_SIZE", INT2NUM(GLUT_WINDOW_ACCUM_ALPHA_SIZE));
    rb_define_const(mGLUT, "WINDOW_DOUBLEBUFFER", INT2NUM(GLUT_WINDOW_DOUBLEBUFFER));
    rb_define_const(mGLUT, "WINDOW_RGBA", INT2NUM(GLUT_WINDOW_RGBA));
    rb_define_const(mGLUT, "WINDOW_PARENT", INT2NUM(GLUT_WINDOW_PARENT));
    rb_define_const(mGLUT, "WINDOW_NUM_CHILDREN", INT2NUM(GLUT_WINDOW_NUM_CHILDREN));
    rb_define_const(mGLUT, "WINDOW_COLORMAP_SIZE", INT2NUM(GLUT_WINDOW_COLORMAP_SIZE));
    rb_define_const(mGLUT, "WINDOW_NUM_SAMPLES", INT2NUM(GLUT_WINDOW_NUM_SAMPLES));
    rb_define_const(mGLUT, "WINDOW_STEREO", INT2NUM(GLUT_WINDOW_STEREO));
    rb_define_const(mGLUT, "WINDOW_CURSOR", INT2NUM(GLUT_WINDOW_CURSOR));
    rb_define_const(mGLUT, "SCREEN_WIDTH", INT2NUM(GLUT_SCREEN_WIDTH));
    rb_define_const(mGLUT, "SCREEN_HEIGHT", INT2NUM(GLUT_SCREEN_HEIGHT));
    rb_define_const(mGLUT, "SCREEN_WIDTH_MM", INT2NUM(GLUT_SCREEN_WIDTH_MM));
    rb_define_const(mGLUT, "SCREEN_HEIGHT_MM", INT2NUM(GLUT_SCREEN_HEIGHT_MM));
    rb_define_const(mGLUT, "MENU_NUM_ITEMS", INT2NUM(GLUT_MENU_NUM_ITEMS));
    rb_define_const(mGLUT, "DISPLAY_MODE_POSSIBLE", INT2NUM(GLUT_DISPLAY_MODE_POSSIBLE));
    rb_define_const(mGLUT, "INIT_WINDOW_X", INT2NUM(GLUT_INIT_WINDOW_X));
    rb_define_const(mGLUT, "INIT_WINDOW_Y", INT2NUM(GLUT_INIT_WINDOW_Y));
    rb_define_const(mGLUT, "INIT_WINDOW_WIDTH", INT2NUM(GLUT_INIT_WINDOW_WIDTH));
    rb_define_const(mGLUT, "INIT_WINDOW_HEIGHT", INT2NUM(GLUT_INIT_WINDOW_HEIGHT));
    rb_define_const(mGLUT, "INIT_DISPLAY_MODE", INT2NUM(GLUT_INIT_DISPLAY_MODE));
    rb_define_const(mGLUT, "ELAPSED_TIME", INT2NUM(GLUT_ELAPSED_TIME));
    rb_define_const(mGLUT, "HAS_KEYBOARD", INT2NUM(GLUT_HAS_KEYBOARD));
    rb_define_const(mGLUT, "HAS_MOUSE", INT2NUM(GLUT_HAS_MOUSE));
    rb_define_const(mGLUT, "HAS_SPACEBALL", INT2NUM(GLUT_HAS_SPACEBALL));
    rb_define_const(mGLUT, "HAS_DIAL_AND_BUTTON_BOX", INT2NUM(GLUT_HAS_DIAL_AND_BUTTON_BOX));
    rb_define_const(mGLUT, "HAS_TABLET", INT2NUM(GLUT_HAS_TABLET));
    rb_define_const(mGLUT, "NUM_MOUSE_BUTTONS", INT2NUM(GLUT_NUM_MOUSE_BUTTONS));
    rb_define_const(mGLUT, "NUM_SPACEBALL_BUTTONS", INT2NUM(GLUT_NUM_SPACEBALL_BUTTONS));
    rb_define_const(mGLUT, "NUM_BUTTON_BOX_BUTTONS", INT2NUM(GLUT_NUM_BUTTON_BOX_BUTTONS));
    rb_define_const(mGLUT, "NUM_DIALS", INT2NUM(GLUT_NUM_DIALS));
    rb_define_const(mGLUT, "NUM_TABLET_BUTTONS", INT2NUM(GLUT_NUM_TABLET_BUTTONS));
    rb_define_const(mGLUT, "OVERLAY_POSSIBLE", INT2NUM(GLUT_OVERLAY_POSSIBLE));
    rb_define_const(mGLUT, "LAYER_IN_USE", INT2NUM(GLUT_LAYER_IN_USE));
    rb_define_const(mGLUT, "HAS_OVERLAY", INT2NUM(GLUT_HAS_OVERLAY));
    rb_define_const(mGLUT, "TRANSPARENT_INDEX", INT2NUM(GLUT_TRANSPARENT_INDEX));
    rb_define_const(mGLUT, "NORMAL_DAMAGED", INT2NUM(GLUT_NORMAL_DAMAGED));
    rb_define_const(mGLUT, "OVERLAY_DAMAGED", INT2NUM(GLUT_OVERLAY_DAMAGED));
    rb_define_const(mGLUT, "VIDEO_RESIZE_POSSIBLE", INT2NUM(GLUT_VIDEO_RESIZE_POSSIBLE));
    rb_define_const(mGLUT, "VIDEO_RESIZE_IN_USE", INT2NUM(GLUT_VIDEO_RESIZE_IN_USE));
    rb_define_const(mGLUT, "VIDEO_RESIZE_X_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_X_DELTA));
    rb_define_const(mGLUT, "VIDEO_RESIZE_Y_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_Y_DELTA));
    rb_define_const(mGLUT, "VIDEO_RESIZE_WIDTH_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_WIDTH_DELTA));
    rb_define_const(mGLUT, "VIDEO_RESIZE_HEIGHT_DELTA", INT2NUM(GLUT_VIDEO_RESIZE_HEIGHT_DELTA));
    rb_define_const(mGLUT, "VIDEO_RESIZE_X", INT2NUM(GLUT_VIDEO_RESIZE_X));
    rb_define_const(mGLUT, "VIDEO_RESIZE_Y", INT2NUM(GLUT_VIDEO_RESIZE_Y));
    rb_define_const(mGLUT, "VIDEO_RESIZE_WIDTH", INT2NUM(GLUT_VIDEO_RESIZE_WIDTH));
    rb_define_const(mGLUT, "VIDEO_RESIZE_HEIGHT", INT2NUM(GLUT_VIDEO_RESIZE_HEIGHT));
    rb_define_const(mGLUT, "NORMAL", INT2NUM(GLUT_NORMAL));
    rb_define_const(mGLUT, "OVERLAY", INT2NUM(GLUT_OVERLAY));
    rb_define_const(mGLUT, "ACTIVE_SHIFT", INT2NUM(GLUT_ACTIVE_SHIFT));
    rb_define_const(mGLUT, "ACTIVE_CTRL", INT2NUM(GLUT_ACTIVE_CTRL));
    rb_define_const(mGLUT, "ACTIVE_ALT", INT2NUM(GLUT_ACTIVE_ALT));
    rb_define_const(mGLUT, "CURSOR_RIGHT_ARROW", INT2NUM(GLUT_CURSOR_RIGHT_ARROW));
    rb_define_const(mGLUT, "CURSOR_LEFT_ARROW", INT2NUM(GLUT_CURSOR_LEFT_ARROW));
    rb_define_const(mGLUT, "CURSOR_INFO", INT2NUM(GLUT_CURSOR_INFO));
    rb_define_const(mGLUT, "CURSOR_DESTROY", INT2NUM(GLUT_CURSOR_DESTROY));
    rb_define_const(mGLUT, "CURSOR_HELP", INT2NUM(GLUT_CURSOR_HELP));
    rb_define_const(mGLUT, "CURSOR_CYCLE", INT2NUM(GLUT_CURSOR_CYCLE));
    rb_define_const(mGLUT, "CURSOR_SPRAY", INT2NUM(GLUT_CURSOR_SPRAY));
    rb_define_const(mGLUT, "CURSOR_WAIT", INT2NUM(GLUT_CURSOR_WAIT));
    rb_define_const(mGLUT, "CURSOR_TEXT", INT2NUM(GLUT_CURSOR_TEXT));
    rb_define_const(mGLUT, "CURSOR_CROSSHAIR", INT2NUM(GLUT_CURSOR_CROSSHAIR));
    rb_define_const(mGLUT, "CURSOR_UP_DOWN", INT2NUM(GLUT_CURSOR_UP_DOWN));
    rb_define_const(mGLUT, "CURSOR_LEFT_RIGHT", INT2NUM(GLUT_CURSOR_LEFT_RIGHT));
    rb_define_const(mGLUT, "CURSOR_TOP_SIDE", INT2NUM(GLUT_CURSOR_TOP_SIDE));
    rb_define_const(mGLUT, "CURSOR_BOTTOM_SIDE", INT2NUM(GLUT_CURSOR_BOTTOM_SIDE));
    rb_define_const(mGLUT, "CURSOR_LEFT_SIDE", INT2NUM(GLUT_CURSOR_LEFT_SIDE));
    rb_define_const(mGLUT, "CURSOR_RIGHT_SIDE", INT2NUM(GLUT_CURSOR_RIGHT_SIDE));
    rb_define_const(mGLUT, "CURSOR_TOP_LEFT_CORNER", INT2NUM(GLUT_CURSOR_TOP_LEFT_CORNER));
    rb_define_const(mGLUT, "CURSOR_TOP_RIGHT_CORNER", INT2NUM(GLUT_CURSOR_TOP_RIGHT_CORNER));
    rb_define_const(mGLUT, "CURSOR_BOTTOM_RIGHT_CORNER", INT2NUM(GLUT_CURSOR_BOTTOM_RIGHT_CORNER));
    rb_define_const(mGLUT, "CURSOR_BOTTOM_LEFT_CORNER", INT2NUM(GLUT_CURSOR_BOTTOM_LEFT_CORNER));
    rb_define_const(mGLUT, "CURSOR_INHERIT", INT2NUM(GLUT_CURSOR_INHERIT));
    rb_define_const(mGLUT, "CURSOR_NONE", INT2NUM(GLUT_CURSOR_NONE));
    rb_define_const(mGLUT, "CURSOR_FULL_CROSSHAIR", INT2NUM(GLUT_CURSOR_FULL_CROSSHAIR));
    rb_define_const(mGLUT, "BITMAP_9_BY_15", INT2NUM((VALUE)GLUT_BITMAP_9_BY_15));
    rb_define_const(mGLUT, "BITMAP_8_BY_13", INT2NUM((VALUE)GLUT_BITMAP_8_BY_13));
    rb_define_const(mGLUT, "BITMAP_TIMES_ROMAN_10", INT2NUM((VALUE)GLUT_BITMAP_TIMES_ROMAN_10));
    rb_define_const(mGLUT, "BITMAP_TIMES_ROMAN_24", INT2NUM((VALUE)GLUT_BITMAP_TIMES_ROMAN_24));
    rb_define_const(mGLUT, "BITMAP_HELVETICA_10", INT2NUM((VALUE)GLUT_BITMAP_HELVETICA_10));
    rb_define_const(mGLUT, "BITMAP_HELVETICA_12", INT2NUM((VALUE)GLUT_BITMAP_HELVETICA_12));
    rb_define_const(mGLUT, "BITMAP_HELVETICA_18", INT2NUM((VALUE)GLUT_BITMAP_HELVETICA_18));
    rb_define_const(mGLUT, "STROKE_ROMAN", INT2NUM((VALUE)GLUT_STROKE_ROMAN));
    rb_define_const(mGLUT, "STROKE_MONO_ROMAN", INT2NUM((VALUE)GLUT_STROKE_MONO_ROMAN));

    callId = rb_intern("call");

    WINDOW_CALLBACK_DEFINE(DisplayFunc);
    WINDOW_CALLBACK_DEFINE(ReshapeFunc);
    WINDOW_CALLBACK_DEFINE(KeyboardFunc);
    WINDOW_CALLBACK_DEFINE(MouseFunc);
    WINDOW_CALLBACK_DEFINE(MotionFunc);
    WINDOW_CALLBACK_DEFINE(PassiveMotionFunc);
    WINDOW_CALLBACK_DEFINE(EntryFunc);
    WINDOW_CALLBACK_DEFINE(VisibilityFunc);
/*
    GENERAL_CALLBACK_DEFINE(IdleFunc);
    GENERAL_CALLBACK_DEFINE(TimerFunc);
    MENU_CALLBACK_DEFINE(MenuStateFunc);
*/
    WINDOW_CALLBACK_DEFINE(SpecialFunc);
    WINDOW_CALLBACK_DEFINE(SpaceballMotionFunc);
    WINDOW_CALLBACK_DEFINE(SpaceballRotateFunc);
    WINDOW_CALLBACK_DEFINE(SpaceballButtonFunc);
    WINDOW_CALLBACK_DEFINE(ButtonBoxFunc);
    WINDOW_CALLBACK_DEFINE(DialsFunc);
    WINDOW_CALLBACK_DEFINE(TabletMotionFunc);
    WINDOW_CALLBACK_DEFINE(TabletButtonFunc);
/*
    WINDOW_GLOBAL_VAR_DEFINE(MenuStatusFunc);
*/
    WINDOW_CALLBACK_DEFINE(OverlayDisplayFunc);
    WINDOW_CALLBACK_DEFINE(WindowStatusFunc);

    rb_gc_register_address(&idle_func);
    rb_gc_register_address(&timer_func);
    rb_gc_register_address(&menustate_func);
}

