/*
 * Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
 *
 * This program is distributed under the terms of the MIT license.
 * See the included MIT-LICENSE file for the terms of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * To add a callback to this file, do the following, replacing "Foo" with
 * the glut function name:
 *
 * 1: In the %wrapper section, add a WINDOW_CALLBACK_SETUP(FooFunc)
 * 2: In the %wrapper section, add static void glut_FooFuncCallback(...)
 *    { ... }  The job of this function is to look up the proc
 *    registered for Foo and make a call with the correct key, and other
 *    param types.
 * 3: In the %init section, add a WINDOW_CALLBACK_DEFINE(FooFunc)
 * 4: At the end of the file, add a %ignore glutFooFunc;
 */

%runtime %{
static int callId; /* 'call' method id */
/* callback define macro */
/*
 * This macro defines a
 * Assuming a call to WINDOW_CALLBACK_SETUP(DisplayFunc);, you'll get:
 *
 *   static VALUE DisplayFunc = Qnil;
 *   static void glut_DisplayFuncCallback();
 *   static VALUE glut_DisplayFunc(obj,arg1)
 *     VALUE obj,arg1;
 *   {
 *     int win;
 *     if (!rb_obj_is_kind_of(arg1,rb_cProc) && !((VALUE)(arg1) == Qnil))
 *       rb_raise(rb_eTypeError, "GLUT.%s:%s","DisplayFunc",
 *                rb_class2name(rb_class_of((VALUE)(arg1))));
 *     win = glutGetWindow();
 *     if (win == 0)
 *       rb_raise(rb_eRuntimeError,
 *                "GLUT.%s needs current window",
 *                "DisplayFunc");
 *     rb_ary_store(DisplayFunc, win, arg1);
 *     glutDisplayFunc(glut_DisplayFuncCallback);
 *     return Qnil;
 *   };
 *
 */
#define WINDOW_CALLBACK_SETUP(_funcname) \
static VALUE _funcname = Qnil; \
static void glut_ ## _funcname ## Callback(); \
static VALUE \
_wrap_glut ## _funcname(obj,arg1) \
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

/*
 * There are two macros here, because what I really wanted was for
 * WINDOW_CALLBACK_DEFINE(DisplayFunc) to produce, amongst other things,
 * a line like:
 *
 *   rb_define_module_function(mGLUT, "glutDisplayFunc", ...
 *
 * But I couldn't get a macro to work in one pass.  All of these failed:
 *
 *   rb_define_module_function(mGLUT,  "glut ## _funcname", ...
 *
 * Produces rb_define_module_function(mGLUT, "glut ## _funcname", ...
 *
 *   rb_define_module_function(mGLUT,  \"glut ## _funcname\", ...
 *   rb_define_module_function(mGLUT,  \\"glut ## _funcname\\", ...
 *
 * So I make the first macro to concatenate glut and the _funcname, and
 * then in the second macro, I can wrap it in double quotes....
 *
 */
#define WINDOW_CALLBACK_DEFINE_X(_funcname, _glutName) \
    rb_define_module_function(mGLUT,  # _glutName, _wrap_glut ## _funcname , 1); \
    rb_global_variable(&_funcname); \
    _funcname = rb_ary_new() \

#define WINDOW_CALLBACK_DEFINE(_funcname) \
    WINDOW_CALLBACK_DEFINE_X(_funcname, glut ## _funcname)
%}

%wrapper %{

WINDOW_CALLBACK_SETUP(DisplayFunc);
WINDOW_CALLBACK_SETUP(ReshapeFunc);
WINDOW_CALLBACK_SETUP(KeyboardFunc);
WINDOW_CALLBACK_SETUP(MouseFunc);
WINDOW_CALLBACK_SETUP(MotionFunc);
WINDOW_CALLBACK_SETUP(PassiveMotionFunc);
WINDOW_CALLBACK_SETUP(EntryFunc);
WINDOW_CALLBACK_SETUP(VisibilityFunc);


/*
WINDOW_CALLBACK_SETUP(SpecialFunc);
WINDOW_CALLBACK_SETUP(SpaceballMotionFunc);
WINDOW_CALLBACK_SETUP(SpaceballRotateFunc);
WINDOW_CALLBACK_SETUP(SpaceballButtonFunc);
WINDOW_CALLBACK_SETUP(ButtonBoxFunc);
WINDOW_CALLBACK_SETUP(DialsFunc);
WINDOW_CALLBACK_SETUP(TabletMotionFunc);
WINDOW_CALLBACK_SETUP(TabletButtonFunc);

WINDOW_CALLBACK_SETUP(OverlayDisplayFunc);
WINDOW_CALLBACK_SETUP(WindowStatusFunc);
*/

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

%}

%init %{
  WINDOW_CALLBACK_DEFINE(DisplayFunc);
  WINDOW_CALLBACK_DEFINE(ReshapeFunc);
  WINDOW_CALLBACK_DEFINE(KeyboardFunc);
  WINDOW_CALLBACK_DEFINE(MouseFunc);
  WINDOW_CALLBACK_DEFINE(MotionFunc);
  WINDOW_CALLBACK_DEFINE(PassiveMotionFunc);
  WINDOW_CALLBACK_DEFINE(EntryFunc);
  WINDOW_CALLBACK_DEFINE(VisibilityFunc);


  callId = rb_intern("call");
%}


%ignore glutDisplayFunc;
%ignore glutReshapeFunc;
%ignore glutKeyboardFunc;
%ignore glutMouseFunc;
%ignore glutMotionFunc;
%ignore glutPassiveMotionFunc;
%ignore glutEntryFunc;
%ignore glutVisibilityFunc;
