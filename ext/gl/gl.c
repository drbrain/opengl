/*
 * Last edit by previous maintainer:
 * 2001/12/01 05:28:29, yoshi
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
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif defined WIN32
#include <windows.h>
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "../common/rbogl.h"

#if defined __CYGWIN__
#undef GL_VERSION_1_2
#endif

#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

static VALUE
gl_ClearIndex(obj,arg1)
{
    GLfloat c;
    c = (GLfloat)NUM2DBL(arg1);
    glClearIndex(c);
    return Qnil;
}
static VALUE
gl_ClearColor(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLclampf red;
    GLclampf green;
    GLclampf blue;
    GLclampf alpha;
    red = (GLclampf)NUM2DBL(arg1);
    green = (GLclampf)NUM2DBL(arg2);
    blue = (GLclampf)NUM2DBL(arg3);
    alpha = (GLclampf)NUM2DBL(arg4);
    glClearColor(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Clear(obj,arg1)
VALUE obj,arg1;
{
    GLbitfield mask;
    mask = (GLbitfield)NUM2INT(arg1);
    glClear(mask);
    return Qnil;
}
static VALUE
gl_IndexMask(obj,arg1)
VALUE obj,arg1;
{
    GLuint mask;
    mask = (GLuint)NUM2INT(arg1);
    glIndexMask(mask);
    return Qnil;
}
static VALUE
gl_ColorMask(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLboolean red;
    GLboolean green;
    GLboolean blue;
    GLboolean alpha;
    red = (GLboolean)NUM2INT(arg1);
    green = (GLboolean)NUM2INT(arg2);
    blue = (GLboolean)NUM2INT(arg3);
    alpha = (GLboolean)NUM2INT(arg4);
    glColorMask(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_AlphaFunc(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum func;
    GLclampf ref;
    func = (GLenum)NUM2INT(arg1);
    ref = (GLclampf)NUM2DBL(arg2);
    glAlphaFunc(func,ref);
    return Qnil;
}
static VALUE
gl_BlendFunc(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum sfactor;
    GLenum dfactor;
    sfactor = (GLenum)NUM2INT(arg1);
    dfactor = (GLenum)NUM2INT(arg2);
    glBlendFunc(sfactor,dfactor);
    return Qnil;
}
static VALUE
gl_LogicOp(obj,arg1)
VALUE obj,arg1;
{
    GLenum opcode;
    opcode = (GLenum)NUM2INT(arg1);
    glLogicOp(opcode);
    return Qnil;
}
static VALUE
gl_CullFace(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glCullFace(mode);
    return Qnil;
}
static VALUE
gl_FrontFace(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glFrontFace(mode);
    return Qnil;
}
static VALUE
gl_PointSize(obj,arg1)
VALUE obj,arg1;
{
    GLfloat size;
    size = (GLfloat)NUM2DBL(arg1);
    glPointSize(size);
    return Qnil;
}
static VALUE
gl_LineWidth(obj,arg1)
VALUE obj,arg1;
{
    GLfloat width;
    width = (GLfloat)NUM2DBL(arg1);
    glLineWidth(width);
    return Qnil;
}
static VALUE
gl_LineStipple(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLint factor;
    GLushort pattern;
    factor = (GLint)NUM2INT(arg1);
    pattern = (GLushort)(NUM2INT(arg2) & 0xFFFF);
    glLineStipple(factor,pattern);
    return Qnil;
}
static VALUE
gl_PolygonMode(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum face;
    GLenum mode;
    face = (GLenum)NUM2INT(arg1);
    mode = (GLenum)NUM2INT(arg2);
    glPolygonMode(face,mode);
    return Qnil;
}
static VALUE
gl_PolygonOffset(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLfloat factor;
    GLfloat units;
    factor = (GLfloat)NUM2DBL(arg1);
    units = (GLfloat)NUM2DBL(arg2);
    glPolygonOffset(factor,units);
    return Qnil;
}
static VALUE
gl_PolygonStipple(obj,arg1)
VALUE obj,arg1;
{
    GLubyte mask[128];
    RArray* ary;
    int i;
    memset(mask, 0x0, sizeof(GLubyte[128]));
    if (TYPE(arg1) == T_ARRAY) {
        ary = RARRAY(arg1);
    for(i = 0; i < ary->len && i < 128; i++)
        mask[i] = (GLubyte)NUM2INT(ary->ptr[i]);
    }
    else if (TYPE(arg1) == T_STRING) {
    if (RSTRING(arg1)->len < 128)
        rb_raise(rb_eArgError, "string length:%d", RSTRING(arg1)->len);
    memcpy(mask, RSTRING(arg1)->ptr, 128);
    }
    else
    rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(arg1));
    glPolygonStipple(mask);
    return Qnil;
}
static VALUE
gl_GetPolygonStipple(obj)
VALUE obj;
{
    GLubyte mask[128];
    glGetPolygonStipple(mask);
    return rb_str_new((const char*)mask, 128);
}

static VALUE
gl_EdgeFlag(obj,arg1)
VALUE obj,arg1;
{
    GLboolean flag;
    flag = (GLboolean)NUM2INT(arg1);
    glEdgeFlag(flag);
    return Qnil;
}
static VALUE
gl_Scissor(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    width = (GLsizei)NUM2INT(arg3);
    height = (GLsizei)NUM2INT(arg4);
    glScissor(x,y,width,height);
    return Qnil;
}
static VALUE
gl_ClipPlane(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum plane;
    GLdouble equation[4];
    plane = (GLenum)NUM2INT(arg1);
    if (TYPE(arg2) == T_ARRAY)
    ary2cdbl(arg2, equation, 4);
    else
    rb_raise(rb_eTypeError, "type mismatch:%s",rb_class2name(arg1));
    glClipPlane(plane,equation);
    return Qnil;
}
static VALUE
gl_DrawBuffer(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glDrawBuffer(mode);
    return Qnil;
}
static VALUE
gl_ReadBuffer(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glReadBuffer(mode);
    return Qnil;
}
static VALUE
gl_Enable(obj,arg1)
VALUE obj,arg1;
{
    GLenum cap;
    cap = (GLenum)NUM2INT(arg1);
    glEnable(cap);
    return Qnil;
}
static VALUE
gl_Disable(obj,arg1)
VALUE obj,arg1;
{
    GLenum cap;
    cap = (GLenum)NUM2INT(arg1);
    glDisable(cap);
    return Qnil;
}
static VALUE
gl_IsEnabled(obj,arg1)
VALUE obj,arg1;
{
    GLenum cap;
    GLboolean ret;
    cap = (GLenum)NUM2INT(arg1);
    ret = glIsEnabled(cap);
    return INT2NUM(ret);
}
static VALUE
gl_GetDoublev(obj,arg1)
VALUE obj,arg1;
{
    GLenum pname;
    int nitems;
    VALUE ary, ary2;
    int i,j;
    GLdouble items[32];

    pname = NUM2INT(arg1);
    switch(pname) {
    case GL_ACCUM_CLEAR_VALUE:
#ifdef GL_BLEND_COLOR_EXT
    case GL_BLEND_COLOR_EXT:
#endif
    case GL_COLOR_CLEAR_VALUE:
    case GL_COLOR_WRITEMASK:
    case GL_CURRENT_COLOR:
    case GL_CURRENT_RASTER_COLOR:
    case GL_CURRENT_RASTER_POSITION:
    case GL_CURRENT_RASTER_TEXTURE_COORDS:
    case GL_CURRENT_TEXTURE_COORDS:
    case GL_FOG_COLOR:
    case GL_LIGHT_MODEL_AMBIENT:
    case GL_MAP2_GRID_DOMAIN:
    case GL_SCISSOR_BOX:
    case GL_TEXTURE_ENV_COLOR:
    case GL_VIEWPORT:
        nitems = 4;
        break;
    case GL_CURRENT_NORMAL:
        nitems = 3;
        break;
    case GL_DEPTH_RANGE:    
    case GL_LINE_WIDTH_RANGE:
    case GL_MAP1_GRID_DOMAIN:
    case GL_MAP2_GRID_SEGMENTS:
    case GL_MAX_VIEWPORT_DIMS:
    case GL_POINT_SIZE_RANGE:
    case GL_POLYGON_MODE:
        nitems = 2;
        break;
    case GL_MODELVIEW_MATRIX:
    case GL_PROJECTION_MATRIX:
    case GL_TEXTURE_MATRIX:
        glGetDoublev(pname, items);
        ary = rb_ary_new2(4);
        for (i = 0; i < 4; i++) {
        ary2 = rb_ary_new2(4);
        rb_ary_push(ary, ary2);
        for (j = 0; j < 4; j++)
            rb_ary_push(ary2, rb_float_new(items[i*4+j]));
        }
        return ary;
    case GL_POLYGON_STIPPLE:
        glGetDoublev(pname, items);
        return rb_str_new((const char*)items, 32);
    default:
        glGetDoublev(pname, items);
        return rb_float_new(items[0]);
    }
    glGetDoublev(pname, items);
    ary = rb_ary_new2(nitems);
    for (i = 0; i < nitems; i++)
    rb_ary_push(ary, rb_float_new(items[i]));
    return ary;
}

static VALUE
gl_PushAttrib(obj,arg1)
VALUE obj,arg1;
{
    GLbitfield mask;
    mask = (GLbitfield)NUM2INT(arg1);
    glPushAttrib(mask);
    return Qnil;
}
static VALUE
gl_PopAttrib(obj)
VALUE obj;
{
    glPopAttrib();
    return Qnil;
}
static VALUE
gl_PushClientAttrib(obj,arg1)
VALUE obj,arg1;
{
    GLbitfield mask;
    mask = (GLbitfield)NUM2INT(arg1);
    glPushClientAttrib(mask);
    return Qnil;
}
static VALUE
gl_PopClientAttrib(obj)
VALUE obj;
{
    glPopClientAttrib();
    return Qnil;
}
static VALUE
gl_RenderMode(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    GLint ret;
    mode = (GLenum)NUM2INT(arg1);
    ret = glRenderMode(mode);
    return INT2NUM(ret);
}
static VALUE
gl_GetError(obj)
VALUE obj;
{
    GLenum ret;
    ret = glGetError();
    return INT2NUM(ret);
}
static VALUE
gl_GetString(obj,arg1)
VALUE obj,arg1;
{
    GLenum name;
    const GLubyte *ret;
    name = (GLenum)NUM2INT(arg1);
    ret = glGetString(name);
    return rb_str_new2((const char*)ret);
}
static VALUE
gl_Finish(obj)
VALUE obj;
{
    glFinish();
    return Qnil;
}
static VALUE
gl_Flush(obj)
VALUE obj;
{
    glFlush();
    return Qnil;
}
static VALUE
gl_Hint(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum target;
    GLenum mode;
    target = (GLenum)NUM2INT(arg1);
    mode = (GLenum)NUM2INT(arg2);
    glHint(target,mode);
    return Qnil;
}
static VALUE
gl_ClearDepth(obj,arg1)
VALUE obj,arg1;
{
    GLclampd depth;
    depth = (GLclampd)NUM2DBL(arg1);
    glClearDepth(depth);
    return Qnil;
}
static VALUE
gl_DepthFunc(obj,arg1)
VALUE obj,arg1;
{
    GLenum func;
    func = (GLenum)NUM2INT(arg1);
    glDepthFunc(func);
    return Qnil;
}
static VALUE
gl_DepthMask(obj,arg1)
VALUE obj,arg1;
{
    GLboolean flag;
    flag = (GLboolean)NUM2INT(arg1);
    glDepthMask(flag);
    return Qnil;
}
static VALUE
gl_DepthRange(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLclampd near_val;
    GLclampd far_val;
    near_val = (GLclampd)NUM2DBL(arg1);
    far_val = (GLclampd)NUM2DBL(arg2);
    glDepthRange(near_val,far_val);
    return Qnil;
}
static VALUE
gl_ClearAccum(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
    red = (GLfloat)NUM2DBL(arg1);
    green = (GLfloat)NUM2DBL(arg2);
    blue = (GLfloat)NUM2DBL(arg3);
    alpha = (GLfloat)NUM2DBL(arg4);
    glClearAccum(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Accum(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum op;
    GLfloat value;
    op = (GLenum)NUM2INT(arg1);
    value = (GLfloat)NUM2DBL(arg2);
    glAccum(op,value);
    return Qnil;
}
static VALUE
gl_MatrixMode(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glMatrixMode(mode);
    return Qnil;
}
static VALUE
gl_Ortho(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLdouble left;
    GLdouble right;
    GLdouble bottom;
    GLdouble top;
    GLdouble near_val;
    GLdouble far_val;
    left = (GLdouble)NUM2DBL(arg1);
    right = (GLdouble)NUM2DBL(arg2);
    bottom = (GLdouble)NUM2DBL(arg3);
    top = (GLdouble)NUM2DBL(arg4);
    near_val = (GLdouble)NUM2DBL(arg5);
    far_val = (GLdouble)NUM2DBL(arg6);
    glOrtho(left,right,bottom,top,near_val,far_val);
    return Qnil;
}
static VALUE
gl_Frustum(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLdouble left;
    GLdouble right;
    GLdouble bottom;
    GLdouble top;
    GLdouble near_val;
    GLdouble far_val;
    left = (GLdouble)NUM2DBL(arg1);
    right = (GLdouble)NUM2DBL(arg2);
    bottom = (GLdouble)NUM2DBL(arg3);
    top = (GLdouble)NUM2DBL(arg4);
    near_val = (GLdouble)NUM2DBL(arg5);
    far_val = (GLdouble)NUM2DBL(arg6);
    glFrustum(left,right,bottom,top,near_val,far_val);
    return Qnil;
}
static VALUE
gl_Viewport(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    width = (GLsizei)NUM2INT(arg3);
    height = (GLsizei)NUM2INT(arg4);
    glViewport(x,y,width,height);
    return Qnil;
}
static VALUE
gl_PushMatrix(obj)
VALUE obj;
{
    glPushMatrix();
    return Qnil;
}
static VALUE
gl_PopMatrix(obj)
VALUE obj;
{
    glPopMatrix();
    return Qnil;
}
static VALUE
gl_LoadIdentity(obj)
VALUE obj;
{
    glLoadIdentity();
    return Qnil;
}
static VALUE
gl_LoadMatrixd(obj,arg1)
VALUE obj,arg1;
{
    GLdouble m[4*4];
    ary2cmat4x4(arg1, m);
    glLoadMatrixd(m);
    return Qnil;
}
static VALUE
gl_MultMatrixd(obj,arg1)
VALUE obj,arg1;
{
    GLdouble m[4*4];
    ary2cmat4x4(arg1, m);
    glMultMatrixd(m);
    return Qnil;
}
static VALUE
gl_Rotated(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble angle;
    GLdouble x;
    GLdouble y;
    GLdouble z;
    angle = (GLdouble)NUM2DBL(arg1);
    x = (GLdouble)NUM2DBL(arg2);
    y = (GLdouble)NUM2DBL(arg3);
    z = (GLdouble)NUM2DBL(arg4);
    glRotated(angle,x,y,z);
    return Qnil;
}
static VALUE
gl_Scaled(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    glScaled(x,y,z);
    return Qnil;
}
static VALUE
gl_Translated(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    glTranslated(x,y,z);
    return Qnil;
}
static VALUE
gl_IsList(obj,arg1)
VALUE obj,arg1;
{
    GLuint list;
    GLboolean ret;
    list = (GLuint)NUM2INT(arg1);
    ret = glIsList(list);
    return INT2NUM(ret);
}
static VALUE
gl_DeleteLists(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLuint list;
    GLsizei range;
    list = (GLuint)NUM2INT(arg1);
    range = (GLsizei)NUM2INT(arg2);
    glDeleteLists(list,range);
    return Qnil;
}
static VALUE
gl_GenLists(obj,arg1)
VALUE obj,arg1;
{
    GLsizei range;
    GLuint ret;
    range = (GLsizei)NUM2INT(arg1);
    ret = glGenLists(range);
    return INT2NUM(ret);
}
static VALUE
gl_NewList(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLuint list;
    GLenum mode;
    list = (GLuint)NUM2INT(arg1);
    mode = (GLenum)NUM2INT(arg2);
    glNewList(list,mode);
    return Qnil;
}
static VALUE
gl_EndList(obj)
VALUE obj;
{
    glEndList();
    return Qnil;
}
static VALUE
gl_CallList(obj,arg1)
VALUE obj,arg1;
{
    GLuint list;
    list = (GLuint)NUM2INT(arg1);
    glCallList(list);
    return Qnil;
}
static VALUE
gl_CallLists(obj,arg1)
VALUE obj,arg1;
{
    GLsizei n;
    GLenum type;
    GLvoid *lists;
    if (TYPE(arg1) == T_STRING) {
    type = GL_BYTE;
    lists = RSTRING(arg1)->ptr;
    n = RSTRING(arg1)->len;
    }
    else if (TYPE(arg1) == T_ARRAY) {
    type = GL_INT;
    lists = ALLOC_N(int, RARRAY(arg1)->len);
    if (!lists)
        rb_raise(rb_eRuntimeError, "GL.CallLists memory allocation");
    n = ary2cint(arg1,lists,0);
    }
    glCallLists(n, type, lists);
    if (type == GL_INT) free(lists);
    return Qnil;
}
static VALUE
gl_ListBase(obj,arg1)
VALUE obj,arg1;
{
    GLuint base;
    base = (GLuint)NUM2INT(arg1);
    glListBase(base);
    return Qnil;
}
static VALUE
gl_Begin(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glBegin(mode);
    return Qnil;
}
static VALUE
gl_End(obj)
VALUE obj;
{
    glEnd();
    return Qnil;
}
static VALUE
gl_Vertex2d(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLdouble x;
    GLdouble y;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    glVertex2d(x,y);
    return Qnil;
}
static VALUE
gl_Vertex2f(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLfloat x;
    GLfloat y;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    glVertex2f(x,y);
    return Qnil;
}
static VALUE
gl_Vertex2i(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLint x;
    GLint y;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    glVertex2i(x,y);
    return Qnil;
}
static VALUE
gl_Vertex2s(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLshort x;
    GLshort y;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    glVertex2s(x,y);
    return Qnil;
}
static VALUE
gl_Vertex3d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    glVertex3d(x,y,z);
    return Qnil;
}
static VALUE
gl_Vertex3f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    z = (GLfloat)NUM2DBL(arg3);
    glVertex3f(x,y,z);
    return Qnil;
}
static VALUE
gl_Vertex3i(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint x;
    GLint y;
    GLint z;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    z = (GLint)NUM2INT(arg3);
    glVertex3i(x,y,z);
    return Qnil;
}
static VALUE
gl_Vertex3s(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLshort x;
    GLshort y;
    GLshort z;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    z = (GLshort)NUM2INT(arg3);
    glVertex3s(x,y,z);
    return Qnil;
}
static VALUE
gl_Vertex4d(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    GLdouble w;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    w = (GLdouble)NUM2DBL(arg4);
    glVertex4d(x,y,z,w);
    return Qnil;
}
static VALUE
gl_Vertex4f(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    z = (GLfloat)NUM2DBL(arg3);
    w = (GLfloat)NUM2DBL(arg4);
    glVertex4f(x,y,z,w);
    return Qnil;
}
static VALUE
gl_Vertex4i(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint x;
    GLint y;
    GLint z;
    GLint w;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    z = (GLint)NUM2INT(arg3);
    w = (GLint)NUM2INT(arg4);
    glVertex4i(x,y,z,w);
    return Qnil;
}
static VALUE
gl_Vertex4s(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLshort x;
    GLshort y;
    GLshort z;
    GLshort w;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    z = (GLshort)NUM2INT(arg3);
    w = (GLshort)NUM2INT(arg4);
    glVertex4s(x,y,z,w);
    return Qnil;
}
static VALUE
gl_Vertex(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    VALUE args[4];
    RArray *ary;
    switch (rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 2:
            gl_Vertex2d(obj,ary->ptr[0],ary->ptr[1]);
            break;
            case 3:
            gl_Vertex3d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2]);
            break;
            case 4:
            gl_Vertex4d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2],ary->ptr[3]);
            break;
            default:
            rb_raise(rb_eRuntimeError, "glVertex vertex num error!:%d", ary->len);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 2:
        gl_Vertex2d(obj,args[0], args[1]);
        break;
    case 3:
        gl_Vertex3d(obj,args[0], args[1], args[2]);
        break;
    case 4:
        gl_Vertex4d(obj,args[0], args[1], args[2], args[3]);
        break;
    }
    return Qnil;
}
static VALUE
gl_Normal3b(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLbyte nx;
    GLbyte ny;
    GLbyte nz;
    nx = (GLbyte)NUM2INT(arg1);
    ny = (GLbyte)NUM2INT(arg2);
    nz = (GLbyte)NUM2INT(arg3);
    glNormal3b(nx,ny,nz);
    return Qnil;
}
static VALUE
gl_Normal3d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble nx;
    GLdouble ny;
    GLdouble nz;
    nx = (GLdouble)NUM2DBL(arg1);
    ny = (GLdouble)NUM2DBL(arg2);
    nz = (GLdouble)NUM2DBL(arg3);
    glNormal3d(nx,ny,nz);
    return Qnil;
}
static VALUE
gl_Normal3f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLfloat nx;
    GLfloat ny;
    GLfloat nz;
    nx = (GLfloat)NUM2DBL(arg1);
    ny = (GLfloat)NUM2DBL(arg2);
    nz = (GLfloat)NUM2DBL(arg3);
    glNormal3f(nx,ny,nz);
    return Qnil;
}
static VALUE
gl_Normal3i(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint nx;
    GLint ny;
    GLint nz;
    nx = (GLint)NUM2INT(arg1);
    ny = (GLint)NUM2INT(arg2);
    nz = (GLint)NUM2INT(arg3);
    glNormal3i(nx,ny,nz);
    return Qnil;
}
static VALUE
gl_Normal3s(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLshort nx;
    GLshort ny;
    GLshort nz;
    nx = (GLshort)NUM2INT(arg1);
    ny = (GLshort)NUM2INT(arg2);
    nz = (GLshort)NUM2INT(arg3);
    glNormal3s(nx,ny,nz);
    return Qnil;
}
static VALUE
gl_Normal(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    int num;
    VALUE args[3];
    RArray* ary;
    switch (num = rb_scan_args(argc, argv, "12", &args[0], &args[1], &args[2])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 3:
            gl_Normal3d(obj,ary->ptr[0], ary->ptr[1],ary->ptr[2]);
            break;
            default:
            rb_raise(rb_eArgError, "array length:%d", ary->len);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 3:
        gl_Normal3d(obj,args[0], args[1], args[2]);
        break;
    default:
        rb_raise(rb_eArgError, "arg length:%d",num);
    }
    return Qnil;
}
static VALUE
gl_Indexd(obj,arg1)
VALUE obj,arg1;
{
    GLdouble c;
    c = (GLdouble)NUM2DBL(arg1);
    glIndexd(c);
    return Qnil;
}
static VALUE
gl_Indexf(obj,arg1)
VALUE obj,arg1;
{
    GLfloat c;
    c = (GLfloat)NUM2DBL(arg1);
    glIndexf(c);
    return Qnil;
}
static VALUE
gl_Indexi(obj,arg1)
VALUE obj,arg1;
{
    GLint c;
    c = (GLint)NUM2INT(arg1);
    glIndexi(c);
    return Qnil;
}
static VALUE
gl_Indexs(obj,arg1)
VALUE obj,arg1;
{
    GLshort c;
    c = (GLshort)NUM2INT(arg1);
    glIndexs(c);
    return Qnil;
}
static VALUE
gl_Indexub(obj,arg1)
VALUE obj,arg1;
{
    GLubyte c;
    c = (GLubyte)NUM2INT(arg1);
    glIndexub(c);
    return Qnil;
}
static VALUE
gl_Color3d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble red;
    GLdouble green;
    GLdouble blue;
    red = (GLdouble)NUM2DBL(arg1);
    green = (GLdouble)NUM2DBL(arg2);
    blue = (GLdouble)NUM2DBL(arg3);
    glColor3d(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    red = (GLfloat)NUM2DBL(arg1);
    green = (GLfloat)NUM2DBL(arg2);
    blue = (GLfloat)NUM2DBL(arg3);
    glColor3f(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3i(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint red;
    GLint green;
    GLint blue;
    red = (GLint)NUM2INT(arg1);
    green = (GLint)NUM2INT(arg2);
    blue = (GLint)NUM2INT(arg3);
    glColor3i(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3s(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLshort red;
    GLshort green;
    GLshort blue;
    red = (GLshort)NUM2INT(arg1);
    green = (GLshort)NUM2INT(arg2);
    blue = (GLshort)NUM2INT(arg3);
    glColor3s(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3ub(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
    red = (GLubyte)NUM2INT(arg1);
    green = (GLubyte)NUM2INT(arg2);
    blue = (GLubyte)NUM2INT(arg3);
    glColor3ub(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3ui(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLuint red;
    GLuint green;
    GLuint blue;
    red = (GLuint)NUM2INT(arg1);
    green = (GLuint)NUM2INT(arg2);
    blue = (GLuint)NUM2INT(arg3);
    glColor3ui(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color3us(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLushort red;
    GLushort green;
    GLushort blue;
    red = (GLushort)NUM2INT(arg1);
    green = (GLushort)NUM2INT(arg2);
    blue = (GLushort)NUM2INT(arg3);
    glColor3us(red,green,blue);
    return Qnil;
}
static VALUE
gl_Color4b(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLbyte red;
    GLbyte green;
    GLbyte blue;
    GLbyte alpha;
    red = (GLbyte)NUM2INT(arg1);
    green = (GLbyte)NUM2INT(arg2);
    blue = (GLbyte)NUM2INT(arg3);
    alpha = (GLbyte)NUM2INT(arg4);
    glColor4b(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4d(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble red;
    GLdouble green;
    GLdouble blue;
    GLdouble alpha;
    red = (GLdouble)NUM2DBL(arg1);
    green = (GLdouble)NUM2DBL(arg2);
    blue = (GLdouble)NUM2DBL(arg3);
    alpha = (GLdouble)NUM2DBL(arg4);
    glColor4d(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4f(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
    red = (GLfloat)NUM2DBL(arg1);
    green = (GLfloat)NUM2DBL(arg2);
    blue = (GLfloat)NUM2DBL(arg3);
    alpha = (GLfloat)NUM2DBL(arg4);
    glColor4f(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4i(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint red;
    GLint green;
    GLint blue;
    GLint alpha;
    red = (GLint)NUM2INT(arg1);
    green = (GLint)NUM2INT(arg2);
    blue = (GLint)NUM2INT(arg3);
    alpha = (GLint)NUM2INT(arg4);
    glColor4i(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4s(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLshort red;
    GLshort green;
    GLshort blue;
    GLshort alpha;
    red = (GLshort)NUM2INT(arg1);
    green = (GLshort)NUM2INT(arg2);
    blue = (GLshort)NUM2INT(arg3);
    alpha = (GLshort)NUM2INT(arg4);
    glColor4s(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4ub(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLubyte red;
    GLubyte green;
    GLubyte blue;
    GLubyte alpha;
    red = (GLubyte)NUM2INT(arg1);
    green = (GLubyte)NUM2INT(arg2);
    blue = (GLubyte)NUM2INT(arg3);
    alpha = (GLubyte)NUM2INT(arg4);
    glColor4ub(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4ui(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLuint red;
    GLuint green;
    GLuint blue;
    GLuint alpha;
    red = (GLuint)NUM2INT(arg1);
    green = (GLuint)NUM2INT(arg2);
    blue = (GLuint)NUM2INT(arg3);
    alpha = (GLuint)NUM2INT(arg4);
    glColor4ui(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color4us(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLushort red;
    GLushort green;
    GLushort blue;
    GLushort alpha;
    red = (GLushort)NUM2INT(arg1);
    green = (GLushort)NUM2INT(arg2);
    blue = (GLushort)NUM2INT(arg3);
    alpha = (GLushort)NUM2INT(arg4);
    glColor4us(red,green,blue,alpha);
    return Qnil;
}
static VALUE
gl_Color(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    int num;
    VALUE args[4];
    RArray *ary;
    switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 3:
            gl_Color3d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2]);
            break;
            case 4:
            gl_Color4d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2],ary->ptr[3]);
            break;
            default:
            rb_raise(rb_eArgError, "array length:%d", ary->len);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 3:
        gl_Color3d(obj,args[0], args[1], args[2]);
        break;
    case 4:
        gl_Color4d(obj,args[0], args[1], args[2], args[3]);
        break;
    default:
        rb_raise(rb_eArgError, "arg length:%d", num);
    }
    return Qnil;
}
static VALUE
gl_TexCoord1d(obj,arg1)
VALUE obj,arg1;
{
    GLdouble s;
    s = (GLdouble)NUM2DBL(arg1);
    glTexCoord1d(s);
    return Qnil;
}
static VALUE
gl_TexCoord1f(obj,arg1)
VALUE obj,arg1;
{
    GLfloat s;
    s = (GLfloat)NUM2DBL(arg1);
    glTexCoord1f(s);
    return Qnil;
}
static VALUE
gl_TexCoord1i(obj,arg1)
VALUE obj,arg1;
{
    GLint s;
    s = (GLint)NUM2INT(arg1);
    glTexCoord1i(s);
    return Qnil;
}
static VALUE
gl_TexCoord1s(obj,arg1)
VALUE obj,arg1;
{
    GLshort s;
    s = (GLshort)NUM2INT(arg1);
    glTexCoord1s(s);
    return Qnil;
}
static VALUE
gl_TexCoord2d(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLdouble s;
    GLdouble t;
    s = (GLdouble)NUM2DBL(arg1);
    t = (GLdouble)NUM2DBL(arg2);
    glTexCoord2d(s,t);
    return Qnil;
}
static VALUE
gl_TexCoord2f(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLfloat s;
    GLfloat t;
    s = (GLfloat)NUM2DBL(arg1);
    t = (GLfloat)NUM2DBL(arg2);
    glTexCoord2f(s,t);
    return Qnil;
}
static VALUE
gl_TexCoord2i(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLint s;
    GLint t;
    s = (GLint)NUM2INT(arg1);
    t = (GLint)NUM2INT(arg2);
    glTexCoord2i(s,t);
    return Qnil;
}
static VALUE
gl_TexCoord2s(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLshort s;
    GLshort t;
    s = (GLshort)NUM2INT(arg1);
    t = (GLshort)NUM2INT(arg2);
    glTexCoord2s(s,t);
    return Qnil;
}
static VALUE
gl_TexCoord3d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble s;
    GLdouble t;
    GLdouble r;
    s = (GLdouble)NUM2DBL(arg1);
    t = (GLdouble)NUM2DBL(arg2);
    r = (GLdouble)NUM2DBL(arg3);
    glTexCoord3d(s,t,r);
    return Qnil;
}
static VALUE
gl_TexCoord3f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLfloat s;
    GLfloat t;
    GLfloat r;
    s = (GLfloat)NUM2DBL(arg1);
    t = (GLfloat)NUM2DBL(arg2);
    r = (GLfloat)NUM2DBL(arg3);
    glTexCoord3f(s,t,r);
    return Qnil;
}
static VALUE
gl_TexCoord3i(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint s;
    GLint t;
    GLint r;
    s = (GLint)NUM2INT(arg1);
    t = (GLint)NUM2INT(arg2);
    r = (GLint)NUM2INT(arg3);
    glTexCoord3i(s,t,r);
    return Qnil;
}
static VALUE
gl_TexCoord3s(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLshort s;
    GLshort t;
    GLshort r;
    s = (GLshort)NUM2INT(arg1);
    t = (GLshort)NUM2INT(arg2);
    r = (GLshort)NUM2INT(arg3);
    glTexCoord3s(s,t,r);
    return Qnil;
}
static VALUE
gl_TexCoord4d(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble s;
    GLdouble t;
    GLdouble r;
    GLdouble q;
    s = (GLdouble)NUM2DBL(arg1);
    t = (GLdouble)NUM2DBL(arg2);
    r = (GLdouble)NUM2DBL(arg3);
    q = (GLdouble)NUM2DBL(arg4);
    glTexCoord4d(s,t,r,q);
    return Qnil;
}
static VALUE
gl_TexCoord4f(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat s;
    GLfloat t;
    GLfloat r;
    GLfloat q;
    s = (GLfloat)NUM2DBL(arg1);
    t = (GLfloat)NUM2DBL(arg2);
    r = (GLfloat)NUM2DBL(arg3);
    q = (GLfloat)NUM2DBL(arg4);
    glTexCoord4f(s,t,r,q);
    return Qnil;
}
static VALUE
gl_TexCoord4i(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint s;
    GLint t;
    GLint r;
    GLint q;
    s = (GLint)NUM2INT(arg1);
    t = (GLint)NUM2INT(arg2);
    r = (GLint)NUM2INT(arg3);
    q = (GLint)NUM2INT(arg4);
    glTexCoord4i(s,t,r,q);
    return Qnil;
}
static VALUE
gl_TexCoord4s(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLshort s;
    GLshort t;
    GLshort r;
    GLshort q;
    s = (GLshort)NUM2INT(arg1);
    t = (GLshort)NUM2INT(arg2);
    r = (GLshort)NUM2INT(arg3);
    q = (GLshort)NUM2INT(arg4);
    glTexCoord4s(s,t,r,q);
    return Qnil;
}
static VALUE
gl_TexCoord(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    int num;
    VALUE args[4];
    RArray *ary;
    switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 2:
            gl_TexCoord2d(obj,ary->ptr[0],ary->ptr[1]);
            break;
            case 3:
            gl_TexCoord3d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2]);
            break;
            case 4:
            gl_TexCoord4d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2],ary->ptr[3]);
            break;
            default:
            rb_raise(rb_eArgError, "array length:%d", num);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 2:
        gl_TexCoord2d(obj,args[0], args[1]);
        break;
    case 3:
        gl_TexCoord3d(obj,args[0], args[1], args[2]);
        break;
    case 4:
        gl_TexCoord4d(obj,args[0], args[1], args[2], args[3]);
        break;
    }
    return Qnil;
}
static VALUE
gl_RasterPos2d(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLdouble x;
    GLdouble y;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    glRasterPos2d(x,y);
    return Qnil;
}
static VALUE
gl_RasterPos2f(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLfloat x;
    GLfloat y;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    glRasterPos2f(x,y);
    return Qnil;
}
static VALUE
gl_RasterPos2i(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLint x;
    GLint y;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    glRasterPos2i(x,y);
    return Qnil;
}
static VALUE
gl_RasterPos2s(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLshort x;
    GLshort y;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    glRasterPos2s(x,y);
    return Qnil;
}
static VALUE
gl_RasterPos3d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    glRasterPos3d(x,y,z);
    return Qnil;
}
static VALUE
gl_RasterPos3f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    z = (GLfloat)NUM2DBL(arg3);
    glRasterPos3f(x,y,z);
    return Qnil;
}
static VALUE
gl_RasterPos3i(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint x;
    GLint y;
    GLint z;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    z = (GLint)NUM2INT(arg3);
    glRasterPos3i(x,y,z);
    return Qnil;
}
static VALUE
gl_RasterPos3s(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLshort x;
    GLshort y;
    GLshort z;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    z = (GLshort)NUM2INT(arg3);
    glRasterPos3s(x,y,z);
    return Qnil;
}
static VALUE
gl_RasterPos4d(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
    GLdouble w;
    x = (GLdouble)NUM2DBL(arg1);
    y = (GLdouble)NUM2DBL(arg2);
    z = (GLdouble)NUM2DBL(arg3);
    w = (GLdouble)NUM2DBL(arg4);
    glRasterPos4d(x,y,z,w);
    return Qnil;
}
static VALUE
gl_RasterPos4f(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
    x = (GLfloat)NUM2DBL(arg1);
    y = (GLfloat)NUM2DBL(arg2);
    z = (GLfloat)NUM2DBL(arg3);
    w = (GLfloat)NUM2DBL(arg4);
    glRasterPos4f(x,y,z,w);
    return Qnil;
}
static VALUE
gl_RasterPos4i(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint x;
    GLint y;
    GLint z;
    GLint w;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    z = (GLint)NUM2INT(arg3);
    w = (GLint)NUM2INT(arg4);
    glRasterPos4i(x,y,z,w);
    return Qnil;
}
static VALUE
gl_RasterPos4s(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLshort x;
    GLshort y;
    GLshort z;
    GLshort w;
    x = (GLshort)NUM2INT(arg1);
    y = (GLshort)NUM2INT(arg2);
    z = (GLshort)NUM2INT(arg3);
    w = (GLshort)NUM2INT(arg4);
    glRasterPos4s(x,y,z,w);
    return Qnil;
}
static VALUE
gl_RasterPos(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    int num;
    VALUE args[4];
    RArray *ary;
    switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 2:
            gl_RasterPos2d(obj,ary->ptr[0],ary->ptr[1]);
            break;
            case 3:
            gl_RasterPos3d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2]);
            break;
            case 4:
            gl_RasterPos4d(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2],ary->ptr[3]);
            break;
            default:
            rb_raise(rb_eArgError, "array length:%d", num);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 2:
        gl_RasterPos2d(obj,args[0], args[1]);
        break;
    case 3:
        gl_RasterPos3d(obj,args[0], args[1], args[2]);
        break;
    case 4:
        gl_RasterPos4d(obj,args[0], args[1], args[2], args[3]);
        break;
    }
    return Qnil;
}
static VALUE
gl_Rectd(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLdouble x1;
    GLdouble y1;
    GLdouble x2;
    GLdouble y2;
    x1 = (GLdouble)NUM2DBL(arg1);
    y1 = (GLdouble)NUM2DBL(arg2);
    x2 = (GLdouble)NUM2DBL(arg3);
    y2 = (GLdouble)NUM2DBL(arg4);
    glRectd(x1,y1,x2,y2);
    return Qnil;
}
static VALUE
gl_Rectf(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLfloat x1;
    GLfloat y1;
    GLfloat x2;
    GLfloat y2;
    x1 = (GLfloat)NUM2DBL(arg1);
    y1 = (GLfloat)NUM2DBL(arg2);
    x2 = (GLfloat)NUM2DBL(arg3);
    y2 = (GLfloat)NUM2DBL(arg4);
    glRectf(x1,y1,x2,y2);
    return Qnil;
}
static VALUE
gl_Recti(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLint x1;
    GLint y1;
    GLint x2;
    GLint y2;
    x1 = (GLint)NUM2INT(arg1);
    y1 = (GLint)NUM2INT(arg2);
    x2 = (GLint)NUM2INT(arg3);
    y2 = (GLint)NUM2INT(arg4);
    glRecti(x1,y1,x2,y2);
    return Qnil;
}
static VALUE
gl_Rects(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
    GLshort x1;
    GLshort y1;
    GLshort x2;
    GLshort y2;
    x1 = (GLshort)NUM2INT(arg1);
    y1 = (GLshort)NUM2INT(arg2);
    x2 = (GLshort)NUM2INT(arg3);
    y2 = (GLshort)NUM2INT(arg4);
    glRects(x1,y1,x2,y2);
    return Qnil;
}
static VALUE
gl_Rect(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    int num;
    VALUE args[4];
    RArray *ary;
    switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
        ary = RARRAY(args[0]);
        switch (ary->len) {
            case 4:
            gl_Rectd(obj,ary->ptr[0],ary->ptr[1],ary->ptr[2],ary->ptr[3]);
            break;
            default:
            rb_raise(rb_eArgError, "array length:%d", ary->len);
        }
        }
        else
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 4:
        gl_Rectd(obj,args[0], args[1], args[2], args[3]);
        break;
    default:
        rb_raise(rb_eArgError, "arg length:%d", num);
    }
    return Qnil;
}


static VALUE
gl_ShadeModel(obj,arg1)
VALUE obj,arg1;
{
    GLenum mode;
    mode = (GLenum)NUM2INT(arg1);
    glShadeModel(mode);
    return Qnil;
}
static VALUE
gl_Lightf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum light;
    GLenum pname;
    GLfloat param;
    light = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLfloat)NUM2DBL(arg3);
    glLightf(light,pname,param);
    return Qnil;
}
static VALUE
gl_Lighti(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum light;
    GLenum pname;
    GLint param;
    light = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLint)NUM2INT(arg3);
    glLighti(light,pname,param);
    return Qnil;
}
static VALUE
gl_Lightiv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum light;
    GLenum pname;
    GLint params[4];
    RArray* ary;
    int i;
    memset(params, 0x0, sizeof(GLint[4]));
    light = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if (TYPE(arg3) == T_ARRAY) {
    ary = RARRAY(arg3);
        for(i = 0; i < ary->len && i < 4; i++){
        params[i] = (GLint)NUM2INT(ary->ptr[i]);
    }
    } 
    else
    rb_raise(rb_eTypeError, "type mismatch:%s",rb_class2name(arg3));
    glLightiv(light,pname,params);
    return Qnil;
}
static VALUE
gl_Light(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum light;
    GLenum pname;
    GLfloat params[4];
    RArray* ary;
    memset(params, 0x0, sizeof(GLfloat[4]));
    light = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if (TYPE(arg3) == T_ARRAY) {
        ary = RARRAY(arg3);
    ary2cflt(arg3,params,4);
    glLightfv(light,pname,params);
    } 
    else {
    params[0] = (GLfloat)NUM2DBL(arg3);
    glLightf(light,pname,params[0]);
    }
    return Qnil;
}
static VALUE
gl_LightModelf(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLfloat)NUM2DBL(arg2);
    glLightModelf(pname,param);
    return Qnil;
}
static VALUE
gl_LightModeli(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLint param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLint)NUM2INT(arg2);
    glLightModeli(pname,param);
    return Qnil;
}
static VALUE
gl_LightModel(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat params[4];
    RArray* ary;
    memset(params, 0x0, sizeof(GLfloat[4]));
    pname = (GLenum)NUM2INT(arg1);
    if (TYPE(arg2) == T_ARRAY) {
    ary = RARRAY(arg2);
    ary2cflt(arg2,params,4);
    glLightModelfv(pname,params);
    }
    else {
    params[0] = (GLfloat)NUM2DBL(arg2);
    glLightModelf(pname,params[0]);
    }
    return Qnil;
}
static VALUE
gl_Materialf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum face;
    GLenum pname;
    GLfloat param;
    face = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLfloat)NUM2DBL(arg3);
    glMaterialf(face,pname,param);
    return Qnil;
}
static VALUE
gl_Materiali(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum face;
    GLenum pname;
    GLint param;
    face = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLint)NUM2INT(arg3);
    glMateriali(face,pname,param);
    return Qnil;
}
static VALUE
gl_Material(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum face;
    GLenum pname;
    GLfloat params[4];
    memset(params, 0x0, sizeof(GLfloat[4]));
    face = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if (TYPE(arg3) == T_ARRAY) {
    ary2cflt(arg3,params,4);
    glMaterialfv(face,pname,params);
    }
    else {
    params[0] = (GLfloat)NUM2DBL(arg3);
    glMaterialf(face,pname,params[0]);
    }
    return Qnil;
}
static VALUE
gl_GetMaterial(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum face;
    GLenum pname;
    GLfloat params[4];
    VALUE ret;
    int i;
    face = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    glGetMaterialfv(arg1, arg2, params);
    if (pname == GL_SHININESS) {
        ret = rb_ary_new2(1);
    rb_ary_push(ret, rb_float_new(params[0]));
    }
    else {
        ret = rb_ary_new2(4);
        for (i = 0; i < 4; i++) {
            rb_ary_push(ret, rb_float_new(params[i]));
        }
    }
    return ret;
}
static VALUE
gl_ColorMaterial(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum face;
    GLenum mode;
    face = (GLenum)NUM2INT(arg1);
    mode = (GLenum)NUM2INT(arg2);
    glColorMaterial(face,mode);
    return Qnil;
}
static VALUE
gl_PixelZoom(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLfloat xfactor;
    GLfloat yfactor;
    xfactor = (GLfloat)NUM2DBL(arg1);
    yfactor = (GLfloat)NUM2DBL(arg2);
    glPixelZoom(xfactor,yfactor);
    return Qnil;
}
static VALUE
gl_PixelStoref(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLfloat)NUM2DBL(arg2);
    glPixelStoref(pname,param);
    return Qnil;
}
static VALUE
gl_PixelStorei(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLint param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLint)NUM2INT(arg2);
    glPixelStorei(pname,param);
    return Qnil;
}
static VALUE
gl_PixelTransferf(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLfloat)NUM2DBL(arg2);
    glPixelTransferf(pname,param);
    return Qnil;
}
static VALUE
gl_PixelTransferi(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLint param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLint)NUM2INT(arg2);
    glPixelTransferi(pname,param);
    return Qnil;
}
static VALUE
gl_Bitmap(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
    GLsizei width;
    GLsizei height;
    GLfloat xorig;
    GLfloat yorig;
    GLfloat xmove;
    GLfloat ymove;
    const GLubyte *bitmap;
    width = (GLsizei)NUM2INT(arg1);
    height = (GLsizei)NUM2INT(arg2);
    xorig = (GLfloat)NUM2DBL(arg3);
    yorig = (GLfloat)NUM2DBL(arg4);
    xmove = (GLfloat)NUM2DBL(arg5);
    ymove = (GLfloat)NUM2DBL(arg6);
    if (TYPE(arg7) != T_STRING)
    rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(arg7)));
    if (RSTRING(arg7)->len < (width * height / 8))
    rb_raise(rb_eArgError, "string length:%d", RSTRING(arg7)->len);
    bitmap = (const GLubyte*)RSTRING(arg7)->ptr;
    glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
    return Qnil;
}
static VALUE
gl_ReadPixels(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    int format;
    int type;
    VALUE pixels;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    width = (GLsizei)NUM2INT(arg3);
    height = (GLsizei)NUM2INT(arg4);
    format = NUM2INT(arg5);
    type = NUM2INT(arg6);
    int type_size;
    int format_size;
    if (format != -1 && type != -1) {
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
        pixels = allocate_buffer_with_string(width*height*format_size*type_size);
    glReadPixels(x,y,width,height,format,type,(GLvoid*)RSTRING(pixels)->ptr);
    return pixels;
    }
    return Qnil;
}
static VALUE
gl_DrawPixels(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
    GLsizei width;
    GLsizei height;
    GLenum format;
    GLenum type;
    const char *pixels;
    width = (GLsizei)NUM2INT(arg1);
    height = (GLsizei)NUM2INT(arg2);
    format = (GLenum)NUM2INT(arg3);
    type = (GLenum)NUM2INT(arg4);
    if (format != -1 && type != -1) {
    if (TYPE(arg5) != T_STRING)
        rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(arg5));
    if (RSTRING(arg5)->len < width * height * glformat_size(format) * gltype_size(type) / 8)
        rb_raise(rb_eArgError, "string length:%d", RSTRING(arg5)->len);
    pixels = RSTRING(arg5)->ptr;
    glDrawPixels(width,height,format,type,pixels);
    }
    return Qnil;
}
static VALUE
gl_CopyPixels(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    GLenum type;
    x = (GLint)NUM2INT(arg1);
    y = (GLint)NUM2INT(arg2);
    width = (GLsizei)NUM2INT(arg3);
    height = (GLsizei)NUM2INT(arg4);
    type = (GLenum)NUM2INT(arg5);
    glCopyPixels(x,y,width,height,type);
    return Qnil;
}
static VALUE
gl_StencilFunc(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum func;
    GLint ref;
    GLuint mask;
    func = (GLenum)NUM2INT(arg1);
    ref = (GLint)NUM2INT(arg2);
    mask = (GLuint)NUM2INT(arg3);
    glStencilFunc(func,ref,mask);
    return Qnil;
}
static VALUE
gl_StencilMask(obj,arg1)
VALUE obj,arg1;
{
    GLuint mask;
    mask = (GLuint)NUM2INT(arg1);
    glStencilMask(mask);
    return Qnil;
}
static VALUE
gl_StencilOp(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum fail;
    GLenum zfail;
    GLenum zpass;
    fail = (GLenum)NUM2INT(arg1);
    zfail = (GLenum)NUM2INT(arg2);
    zpass = (GLenum)NUM2INT(arg3);
    glStencilOp(fail,zfail,zpass);
    return Qnil;
}
static VALUE
gl_ClearStencil(obj,arg1)
VALUE obj,arg1;
{
    GLint s;
    s = (GLint)NUM2INT(arg1);
    glClearStencil(s);
    return Qnil;
}
static VALUE
gl_TexGend(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum coord;
    GLenum pname;
    GLdouble param;
    coord = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLdouble)NUM2DBL(arg3);
    glTexGend(coord,pname,param);
    return Qnil;
}
static VALUE
gl_TexGenf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum coord;
    GLenum pname;
    GLfloat param;
    coord = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLfloat)NUM2DBL(arg3);
    glTexGenf(coord,pname,param);
    return Qnil;
}
static VALUE
gl_TexGeni(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum coord;
    GLenum pname;
    GLint param;
    coord = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLint)NUM2INT(arg3);
    glTexGeni(coord,pname,param);
    return Qnil;
}
static VALUE
gl_TexGen(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum coord;
    GLenum pname;
    GLdouble param[4];
    if (TYPE(arg3) == T_ARRAY) {
    coord = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    ary2cdbl(arg3,param,4);
    glTexGendv(coord,pname,param);
    }
    else {
        gl_TexGend(obj,arg1,arg2,arg3);
    }
    return Qnil;
}
static VALUE
gl_TexEnvf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum target;
    GLenum pname;
    GLfloat param;
    target = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLfloat)NUM2DBL(arg3);
    glTexEnvf(target,pname,param);
    return Qnil;
}
static VALUE
gl_TexEnvi(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum target;
    GLenum pname;
    GLint param;
    target = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLint)NUM2INT(arg3);
    glTexEnvi(target,pname,param);
    return Qnil;
}
static VALUE
gl_TexEnv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum target;
    GLenum pname;
    GLfloat param[4];
    int i;
    if (TYPE(arg3) == T_ARRAY) {
    target = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if ((i = ary2cflt(arg3,param,4)) != 4)
        rb_raise(rb_eArgError, "array length:%d", i);
    glTexEnvfv(target,pname,param);
    }
    else {
        gl_TexEnvf(obj,arg1,arg2,arg3);
    }
    return Qnil;
}
static VALUE
gl_TexParameterf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum target;
    GLenum pname;
    GLfloat param;
    target = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLfloat)NUM2DBL(arg3);
    glTexParameterf(target,pname,param);
    return Qnil;
}
static VALUE
gl_TexParameteri(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum target;
    GLenum pname;
    GLint param;
    target = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    param = (GLint)NUM2INT(arg3);
    glTexParameteri(target,pname,param);
    return Qnil;
}
static VALUE
gl_TexImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
    GLenum target;
    GLint level;
    GLint components;
    GLsizei width;
    GLsizei height;
    GLint border;
    GLenum format;
    GLenum type;
    const char *pixels;
    int size;
    int type_size;
    int format_size;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    components = (GLint)NUM2INT(arg3);
    width = (GLsizei)NUM2INT(arg4);
    height = (GLsizei)NUM2INT(arg5);
    border = (GLint)NUM2INT(arg6);
    format = (GLenum)NUM2INT(arg7);
    type = (GLenum)NUM2INT(arg8);
    if (TYPE(arg9) == T_STRING) {
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
    if (type_size == -1 || format_size == -1)
        return Qnil;
    size = type_size*format_size*height*width;
    if (RSTRING(arg9)->len < size)
        rb_raise(rb_eArgError, "string length:%d",RSTRING(arg9)->len);
     pixels = RSTRING(arg9)->ptr;
    } else if (NIL_P(arg9)) {
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
    if (type_size == -1 || format_size == -1)
        return Qnil;
    size = type_size*format_size*height*width;
     pixels = NULL;
    } else
    rb_raise(rb_eTypeError, "type mismatch:%s",rb_class2name(arg9));
    glTexImage2D(target,level,components,width,height,border,
         format,type,pixels);
    return Qnil;
}
static VALUE
gl_Map1d(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLenum target;
    GLdouble u1;
    GLdouble u2;
    GLint stride;
    GLint order;
    GLdouble *points;

    VALUE work_ary;

    target = (GLenum)NUM2INT(arg1);
    u1 = (GLdouble)NUM2DBL(arg2);
    u2 = (GLdouble)NUM2DBL(arg3);
    stride = (GLint)NUM2INT(arg4);
    order = (GLint)NUM2INT(arg5);
    points = ALLOC_N(GLdouble, order*stride);
    work_ary = rb_ary_new();
    mary2ary(arg6, work_ary);
    ary2cdbl(work_ary, points, order*stride);
    glMap1d(target, u1, u2, stride, order, points);
    free(points);
    return Qnil;
}
static VALUE
gl_Map2d(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10;
{
    GLenum target;
    GLdouble u1;
    GLdouble u2;
    GLint ustride;
    GLint uorder;
    GLdouble v1;
    GLdouble v2;
    GLint vstride;
    GLint vorder;
    GLdouble *points;

    VALUE work_ary;

    target = (GLenum)NUM2INT(arg1);
    u1 = (GLdouble)NUM2INT(arg2);
    u2 = (GLdouble)NUM2INT(arg3);
    ustride = (GLint)NUM2INT(arg4);
    uorder = (GLint)NUM2INT(arg5);
    v1 = (GLdouble)NUM2INT(arg6);
    v2 = (GLdouble)NUM2INT(arg7);
    vstride = (GLint)NUM2INT(arg8);
    vorder = (GLint)NUM2INT(arg9);
    points = ALLOC_N(GLdouble, MAX(ustride*uorder, vstride*vorder));
    work_ary = rb_ary_new();
    mary2ary(arg10, work_ary);
    ary2cdbl(arg10, points, MAX(ustride*uorder, vstride*vorder));
    glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
    free(points);
    return Qnil;
}
static VALUE
gl_EvalCoord1d(obj,arg1)
VALUE obj,arg1;
{
    GLdouble u;
    u = (GLdouble)NUM2DBL(arg1);
    glEvalCoord1d(u);
    return Qnil;
}
static VALUE
gl_EvalCoord2d(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLdouble u;
    GLdouble v;
    u = (GLdouble)NUM2DBL(arg1);
    v = (GLdouble)NUM2DBL(arg2);
    glEvalCoord2d(u,v);
    return Qnil;
}
static VALUE
gl_EvalCoord2dv(obj,arg1)
VALUE obj;
RArray arg1;
{
    return Qnil;
}
static VALUE
gl_MapGrid1d(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint un;
    GLdouble u1;
    GLdouble u2;
    un = (GLint)NUM2INT(arg1);
    u1 = (GLdouble)NUM2DBL(arg2);
    u2 = (GLdouble)NUM2DBL(arg3);
    glMapGrid1d(un,u1,u2);
    return Qnil;
}
static VALUE
gl_MapGrid1f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLint un;
    GLfloat u1;
    GLfloat u2;
    un = (GLint)NUM2INT(arg1);
    u1 = (GLfloat)NUM2DBL(arg2);
    u2 = (GLfloat)NUM2DBL(arg3);
    glMapGrid1f(un,u1,u2);
    return Qnil;
}
static VALUE
gl_MapGrid2d(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLint un;
    GLdouble u1;
    GLdouble u2;
    GLint vn;
    GLdouble v1;
    GLdouble v2;
    un = (GLint)NUM2INT(arg1);
    u1 = (GLdouble)NUM2DBL(arg2);
    u2 = (GLdouble)NUM2DBL(arg3);
    vn = (GLint)NUM2INT(arg4);
    v1 = (GLdouble)NUM2DBL(arg5);
    v2 = (GLdouble)NUM2DBL(arg6);
    glMapGrid2d(un,u1,u2,vn,v1,v2);
    return Qnil;
}
static VALUE
gl_MapGrid2f(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLint un;
    GLfloat u1;
    GLfloat u2;
    GLint vn;
    GLfloat v1;
    GLfloat v2;
    un = (GLint)NUM2INT(arg1);
    u1 = (GLfloat)NUM2DBL(arg2);
    u2 = (GLfloat)NUM2DBL(arg3);
    vn = (GLint)NUM2INT(arg4);
    v1 = (GLfloat)NUM2DBL(arg5);
    v2 = (GLfloat)NUM2DBL(arg6);
    glMapGrid2f(un,u1,u2,vn,v1,v2);
    return Qnil;
}
static VALUE
gl_EvalPoint1(obj,arg1)
VALUE obj,arg1;
{
    GLint i;
    i = (GLint)NUM2INT(arg1);
    glEvalPoint1(i);
    return Qnil;
}
static VALUE
gl_EvalPoint2(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLint i;
    GLint j;
    i = (GLint)NUM2INT(arg1);
    j = (GLint)NUM2INT(arg2);
    glEvalPoint2(i,j);
    return Qnil;
}
static VALUE
gl_EvalMesh1(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum mode;
    GLint i1;
    GLint i2;
    mode = (GLenum)NUM2INT(arg1);
    i1 = (GLint)NUM2INT(arg2);
    i2 = (GLint)NUM2INT(arg3);
    glEvalMesh1(mode,i1,i2);
    return Qnil;
}
static VALUE
gl_EvalMesh2(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
    GLenum mode;
    GLint i1;
    GLint i2;
    GLint j1;
    GLint j2;
    mode = (GLenum)NUM2INT(arg1);
    i1 = (GLint)NUM2INT(arg2);
    i2 = (GLint)NUM2INT(arg3);
    j1 = (GLint)NUM2INT(arg4);
    j2 = (GLint)NUM2INT(arg5);
    glEvalMesh2(mode,i1,i2,j1,j2);
    return Qnil;
}
static VALUE
gl_Fogf(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLfloat)NUM2DBL(arg2);
    glFogf(pname,param);
    return Qnil;
}
static VALUE
gl_Fogi(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLint param;
    pname = (GLenum)NUM2INT(arg1);
    param = (GLint)NUM2INT(arg2);
    glFogi(pname,param);
    return Qnil;
}
static VALUE
gl_Fogfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLfloat params[4];
    int i;
    RArray* ary;
    pname = (GLenum)NUM2INT(arg1);
    if (TYPE(arg2) == T_ARRAY) {
    ary = RARRAY(arg2);
    if ((i = ary2cflt(arg2,params,4)) != 4)
        rb_raise(rb_eArgError, "array length:%d", i);
    } 
    else
    params[0] = (GLfloat)NUM2DBL(arg2);
    glFogfv(pname,params);
    return Qnil;
}
static VALUE
gl_Fogiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum pname;
    GLint params[4];
    RArray* ary;
    int i;
    pname = (GLenum)NUM2INT(arg1);
    if (TYPE(arg2) == T_ARRAY) {
    ary = RARRAY(arg2);
    for(i = 0; i < ary->len && i < 4; i++){
        params[i] = (GLint)NUM2INT(ary->ptr[i]);
    }
    } 
    else
    params[0] = (GLint)NUM2INT(arg2);
    glFogiv(pname,params);
    return Qnil;
}
static VALUE
gl_PassThrough(obj,arg1)
VALUE obj,arg1;
{
    GLfloat token;
    token = (GLfloat)NUM2DBL(arg1);
    glPassThrough(token);
    return Qnil;
}
#define DEFAULT_BUFFER    512
static VALUE g_current_feed_buffer;
static VALUE
gl_FeedbackBuffer(argc, argv, obj)
int argc;
VALUE* argv;
VALUE obj;
{
    GLsizei size;
    GLenum type;
    if (argc == 0) {
        size = DEFAULT_BUFFER;
        type = GL_4D_COLOR_TEXTURE;
    }
    else if (argc == 2) {
        size = NUM2INT(argv[0]);
        type = NUM2INT(argv[1]);
    }
    else {
        rb_raise(rb_eTypeError, "GL.FeedbackBuffer");
    }
    g_current_feed_buffer = allocate_buffer_with_string(sizeof(GLfloat)*size);
    rb_str_freeze(g_current_feed_buffer);
    glFeedbackBuffer(size, type, (GLfloat*)RSTRING(g_current_feed_buffer)->ptr);
    return g_current_feed_buffer;
}
static VALUE g_current_sel_buffer;
static VALUE
gl_SelectBuffer(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
    VALUE args;
    GLsizei size;
    size = DEFAULT_BUFFER;
    rb_scan_args(argc, argv, "01", &args);
    if (args != Qnil)
    size = (GLsizei)NUM2INT(args);
    g_current_sel_buffer = allocate_buffer_with_string(sizeof(GLuint)*size);
    rb_str_freeze(g_current_sel_buffer);
    glSelectBuffer(size, (GLuint*)RSTRING(g_current_sel_buffer)->ptr);
    return g_current_sel_buffer;
}

static VALUE
gl_InitNames(obj)
VALUE obj;
{
    glInitNames();
    return Qnil;
}
static VALUE
gl_LoadName(obj,arg1)
VALUE obj,arg1;
{
    GLuint name;
    name = (GLuint)NUM2INT(arg1);
    glLoadName(name);
    return Qnil;
}
static VALUE
gl_PushName(obj,arg1)
VALUE obj,arg1;
{
    GLuint name;
    name = (GLuint)NUM2INT(arg1);
    glPushName(name);
    return Qnil;
}
static VALUE
gl_PopName(obj)
VALUE obj;
{
    glPopName();
    return Qnil;
}

#if defined(GL_VERSION_1_1)
static VALUE
gl_EnableClientState(obj,arg1)
VALUE obj,arg1;
{
    GLenum cap;
    cap = (GLenum)NUM2INT(arg1);
    glEnableClientState(cap);
    return Qnil;
}
static VALUE
gl_DisableClientState(obj,arg1)
VALUE obj,arg1;
{
    GLenum cap;
    cap = (GLenum)NUM2INT(arg1);
    glDisableClientState(cap);
    return Qnil;
}

static VALUE g_Vertex_ptr;
static VALUE g_Normal_ptr;
static VALUE g_Color_ptr;
static VALUE g_Index_ptr;
static VALUE g_TexCoord_ptr;
static VALUE g_EdgeFlag_ptr;
#define POINTER_FUNC(_func_) \
static VALUE \
gl_##_func_##Pointer(obj, arg1, arg2, arg3, arg4) \
VALUE obj, arg1, arg2, arg3, arg4; \
{ \
    GLint size; \
    GLenum type; \
    GLsizei stride; \
    size = (GLint)NUM2INT(arg1); \
    type = (GLenum)NUM2INT(arg2); \
    stride = (GLsizei)NUM2INT(arg3); \
    Check_Type(arg4, T_STRING); \
    rb_str_freeze(arg4); \
    g_##_func_##_ptr = arg4; \
    gl##_func_##Pointer(size, type, stride, (const GLvoid*)RSTRING(arg4)->ptr); \
    return Qnil; \
}

POINTER_FUNC(Vertex)
POINTER_FUNC(Color)
POINTER_FUNC(TexCoord)

#undef POINTER_FUNC

static VALUE
gl_NormalPointer(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
    GLenum type;
    GLsizei stride;
    type = (GLenum)NUM2INT(arg1);
    stride = (GLsizei)NUM2INT(arg2);
    Check_Type(arg3, T_STRING);
    rb_str_freeze(arg3);
    g_Normal_ptr = arg3;
    glNormalPointer(type, stride, (const GLvoid*)RSTRING(arg3)->ptr);
    return Qnil;
}
static VALUE
gl_IndexPointer(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
    GLenum type;
    GLsizei stride;
    type = (GLenum)NUM2INT(arg1);
    stride = (GLsizei)NUM2INT(arg2);
    Check_Type(arg3, T_STRING);
    rb_str_freeze(arg3);
    g_Index_ptr = arg3;
    glIndexPointer(type, stride, (const GLvoid*)RSTRING(arg3)->ptr);
    return Qnil;
}
static VALUE
gl_EdgeFlagPointer(obj, arg1, arg2)
VALUE obj, arg1, arg2;
{
    GLsizei stride;
    stride = (GLsizei)NUM2INT(arg1);
    Check_Type(arg2, T_STRING);
    rb_str_freeze(arg2);
    g_EdgeFlag_ptr = arg2;
    glEdgeFlagPointer(stride, (const GLboolean*)RSTRING(arg2)->ptr);
    return Qnil;
}
static VALUE
gl_GetPointerv(obj, arg1)
VALUE obj, arg1;
{
    GLenum pname;
    /*
    void* params;
    */
    pname = (GLenum)NUM2INT(arg1);
    switch (pname) {
        case GL_VERTEX_ARRAY_POINTER:
            return g_Vertex_ptr;
        case GL_NORMAL_ARRAY_POINTER:
            return g_Normal_ptr;
        case GL_COLOR_ARRAY_POINTER:
            return g_Color_ptr;
        case GL_INDEX_ARRAY_POINTER:
            return g_Index_ptr;
        case GL_TEXTURE_COORD_ARRAY_POINTER:
            return g_TexCoord_ptr;
        case GL_EDGE_FLAG_ARRAY_POINTER:
            return g_EdgeFlag_ptr;
    }
/*
    glGetPointerv(pname, &params);
*/
    return Qnil;
}
static VALUE
gl_ArrayElement(obj,arg1)
VALUE obj,arg1;
{
    GLint i;
    i = (GLint)NUM2INT(arg1);
    glArrayElement(i);
    return Qnil;
}
static VALUE
gl_DrawArrays(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
    GLenum mode;
    GLint first;
    GLsizei count;
    mode = (GLenum)NUM2INT(arg1);
    first = (GLint)NUM2INT(arg2);
    count = (GLsizei)NUM2INT(arg3);
    glDrawArrays(mode,first,count);
    return Qnil;
}
static VALUE
gl_DrawElements(obj, arg1, arg2, arg3, arg4)
VALUE obj, arg1, arg2, arg3, arg4;
{
    GLenum mode;
    GLsizei count;
    GLenum type;
    mode = (GLenum)NUM2INT(arg1);
    count = (GLsizei)NUM2INT(arg2);
    type = (GLenum)NUM2INT(arg3);
    Check_Type(arg4, T_STRING);
    glDrawElements(mode, count, type, (const GLvoid*)RSTRING(arg4)->ptr);
    return Qnil;
}
static VALUE
gl_InterleavedArrays(obj, arg1, arg2, arg3)
VALUE obj, arg1, arg2, arg3;
{
    GLenum format;
    GLsizei stride;
    format = (GLenum)NUM2INT(arg1);
    stride = (GLsizei)NUM2INT(arg2);
    Check_Type(arg3, T_STRING);
    glInterleavedArrays(format, stride, (const GLvoid*)RSTRING(arg3)->ptr);
    return Qnil;
}
static VALUE
gl_GenTextures(obj,arg1)
VALUE obj,arg1;
{
    GLsizei n;
    GLuint *textures;
    RArray *ret;
    int i;
    n = (GLsizei)NUM2INT(arg1);
    textures = ALLOC_N(GLuint, n);
    if (!textures)
    rb_raise(rb_eRuntimeError, "GL.GenTexture mamory allocation");
    glGenTextures(n, textures);
    ret = RARRAY(rb_ary_new2(n));
    for (i = 0; i < n; i++)
    rb_ary_push((VALUE)ret, INT2NUM(textures[i]));
    free(textures);
    return (VALUE)ret;
}
static VALUE
gl_DeleteTextures(obj,arg1)
VALUE obj,arg1;
{
    GLsizei n;
    GLuint *textures;
    RArray *ary;
    if (TYPE(arg1) != T_ARRAY)
    rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(arg1));
    ary = RARRAY(arg1);
    n = ary->len;
    textures = xmalloc(n);
    ary2cint((VALUE)ary,(int*)textures,0); /* OK? */
    glDeleteTextures( n, textures);
    free(textures);
    return Qnil;
}
static VALUE
gl_BindTexture(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
    GLenum target;
    GLuint texture;
    target = (GLenum)NUM2INT(arg1);
    texture = (GLuint)NUM2INT(arg2);
    glBindTexture(target,texture);
    return Qnil;
}
static VALUE
gl_IsTexture(obj,arg1)
VALUE obj,arg1;
{
    GLuint texture;
    GLboolean ret;
    texture = (GLuint)NUM2INT(arg1);
    ret = glIsTexture(texture);
    return INT2NUM(ret);
}
static VALUE
gl_TexSubImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
    GLenum target;
    GLint level;
    GLint components;
    GLint xoffset;
    GLint yoffset;
    GLsizei width;
    GLsizei height;
    GLenum format;
    GLenum type;
    const char *pixels;
    int size;
    int type_size;
    int format_size;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    xoffset = (GLint)NUM2INT(arg3);
    yoffset = (GLint)NUM2INT(arg4);
    width = (GLsizei)NUM2INT(arg5);
    height = (GLsizei)NUM2INT(arg6);
    format = (GLenum)NUM2INT(arg7);
    type = (GLenum)NUM2INT(arg8);
    if (TYPE(arg9) == T_STRING) {
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
    if (type_size == -1 || format_size == -1)
        return Qnil;
    size = type_size*format_size*height*width;
    if (RSTRING(arg9)->len < size)
        rb_raise(rb_eArgError, "string length:%d",RSTRING(arg9)->len);
     pixels = RSTRING(arg9)->ptr;
    } else
    rb_raise(rb_eTypeError, "type mismatch:%s",rb_class2name(arg9));
    glTexSubImage2D(target,level,xoffset,yoffset,width,height,
         format,type,pixels);
    return Qnil;
}
static VALUE
gl_CopyTexImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
    GLenum target;
    GLint level;
    GLenum internalformat;
    GLint x;
    GLint y;
    GLsizei width;
    GLint border;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    internalformat = (GLenum)NUM2INT(arg3);
    x = (GLint)NUM2INT(arg4);
    y = (GLint)NUM2INT(arg5);
    width = (GLsizei)NUM2INT(arg6);
    border = (GLint)NUM2INT(arg7);
    glCopyTexImage1D(target,level,internalformat,x,y,width,border);
    return Qnil;
}
static VALUE
gl_CopyTexImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8;
{
    GLenum target;
    GLint level;
    GLenum internalformat;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    GLint border;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    internalformat = (GLenum)NUM2INT(arg3);
    x = (GLint)NUM2INT(arg4);
    y = (GLint)NUM2INT(arg5);
    width = (GLsizei)NUM2INT(arg6);
    height = (GLsizei)NUM2INT(arg7);
    border = (GLint)NUM2INT(arg8);
    glCopyTexImage2D(target,level,internalformat,x,y,width,height,border);
    return Qnil;
}
static VALUE
gl_CopyTexSubImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLenum target;
    GLint level;
    GLint xoffset;
    GLint x;
    GLint y;
    GLsizei width;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    xoffset = (GLint)NUM2INT(arg3);
    x = (GLint)NUM2INT(arg4);
    y = (GLint)NUM2INT(arg5);
    width = (GLsizei)NUM2INT(arg6);
    glCopyTexSubImage1D(target,level,xoffset,x,y,width);
    return Qnil;
}
static VALUE
gl_CopyTexSubImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8;
{
    GLenum target;
    GLint level;
    GLint xoffset;
    GLint yoffset;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    xoffset = (GLint)NUM2INT(arg3);
    yoffset = (GLint)NUM2INT(arg4);
    x = (GLint)NUM2INT(arg5);
    y = (GLint)NUM2INT(arg6);
    width = (GLsizei)NUM2INT(arg7);
    height = (GLsizei)NUM2INT(arg8);
    glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);
    return Qnil;
}
#endif /* GL_VERSION_1_1 */

#if defined(GL_VERSION_1_2)
VALUE
gl_DrawRangeElements(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
    GLenum mode;
    GLuint start;
    GLuint end;
    GLsizei count;
    GLenum type;
    mode = (GLenum)NUM2INT(arg1);
    start = (GLuint)NUM2INT(arg2);
    end = (GLuint)NUM2INT(arg3);
    count = (GLsizei)NUM2INT(arg4);
    type = (GLenum)NUM2INT(arg5);
    Check_Type(arg6, T_STRING);
    glDrawRangeElements(mode, start, end, count, type, RSTRING(arg6)->ptr);
    return Qnil;
}
VALUE
gl_TexImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10;
{
    GLenum target;
    GLint level;
    GLint internalFormat;
    GLsizei width;
    GLsizei height;
    GLsizei depth;
    GLint border;
    GLenum format;
    GLenum type;
    int size;
    int type_size;
    int format_size;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    internalFormat = (GLint)NUM2INT(arg3);
    width = (GLsizei)NUM2INT(arg4);
    height = (GLsizei)NUM2INT(arg5);
    depth = (GLsizei)NUM2INT(arg6);
    border = (GLint)NUM2INT(arg7);
    format = (GLenum)NUM2INT(arg8);
    type = (GLenum)NUM2INT(arg9);
    Check_Type(arg10, T_STRING);
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
    if (type_size == -1 || format_size == -1)
        return Qnil;
    size = type_size*format_size*height*width*depth;
    if (RSTRING(arg10)->len < size)
        rb_raise(rb_eArgError, "string length:%d",RSTRING(arg10)->len);
    glTexImage3D( target, level, internalFormat, width, height,
                  depth, border, format, type,
                  (const GLvoid*)RSTRING(arg10)->ptr);
    return Qnil;
}
VALUE
gl_TexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11)
VALUE arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11;
{
    GLenum target;
    GLint level;
    GLint xoffset;
    GLint yoffset;
    GLint zoffset;
    GLsizei width;
    GLsizei height;
    GLsizei depth;
    GLenum format;
    GLenum type;
    int size;
    int type_size;
    int format_size;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    xoffset = (GLint)NUM2INT(arg3);
    yoffset = (GLint)NUM2INT(arg4);
    zoffset = (GLint)NUM2INT(arg5);
    width = (GLsizei)NUM2INT(arg6);
    height = (GLsizei)NUM2INT(arg7);
    depth = (GLsizei)NUM2INT(arg8);
    format = (GLenum)NUM2INT(arg9);
    type = (GLenum)NUM2INT(arg10);
    Check_Type(arg11, T_STRING);
    type_size = gltype_size(type) / 8;
    format_size = glformat_size(format);
    if (type_size == -1 || format_size == -1)
        return Qnil;
    size = type_size*format_size*height*width*depth;
    if (RSTRING(arg11)->len < size)
        rb_raise(rb_eArgError, "string length:%d",RSTRING(arg11)->len);
    glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
            width, height, depth,
            format, type, RSTRING(arg11)->ptr);
    return Qnil;
}
VALUE
gl_CopyTexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
    GLenum target;
    GLint level;
    GLint xoffset;
    GLint yoffset;
    GLint zoffset;
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
    target = (GLenum)NUM2INT(arg1);
    level = (GLint)NUM2INT(arg2);
    xoffset = (GLint)NUM2INT(arg3);
    yoffset = (GLint)NUM2INT(arg4);
    zoffset = (GLint)NUM2INT(arg5);
    x = (GLint)NUM2INT(arg6);
    y = (GLint)NUM2INT(arg7);
    width = (GLsizei)NUM2INT(arg8);
    height = (GLsizei)NUM2INT(arg9);
    glCopyTexSubImage3D( target, level,
            xoffset, yoffset, zoffset,
            x, y, width, height );
    return Qnil;
}

#endif /* GL_VERSION_1_2 */

static VALUE module;

void Init_gl()
{
    module = rb_define_module("Gl");
    rb_define_module_function(module, "glClearIndex", gl_ClearIndex, 1);
    rb_define_module_function(module, "glClearColor", gl_ClearColor, 4);
    rb_define_module_function(module, "glClear", gl_Clear, 1);
    rb_define_module_function(module, "glIndexMask", gl_IndexMask, 1);
    rb_define_module_function(module, "glColorMask", gl_ColorMask, 4);
    rb_define_module_function(module, "glAlphaFunc", gl_AlphaFunc, 2);
    rb_define_module_function(module, "glBlendFunc", gl_BlendFunc, 2);
    rb_define_module_function(module, "glLogicOp", gl_LogicOp, 1);
    rb_define_module_function(module, "glCullFace", gl_CullFace, 1);
    rb_define_module_function(module, "glFrontFace", gl_FrontFace, 1);
    rb_define_module_function(module, "glPointSize", gl_PointSize, 1);
    rb_define_module_function(module, "glLineWidth", gl_LineWidth, 1);
    rb_define_module_function(module, "glLineStipple", gl_LineStipple, 2);
    rb_define_module_function(module, "glPolygonMode", gl_PolygonMode, 2);
    rb_define_module_function(module, "glPolygonOffset", gl_PolygonOffset, 2);
    rb_define_module_function(module, "glPolygonStipple", gl_PolygonStipple, 1);
    rb_define_module_function(module, "glGetPolygonStipple", gl_GetPolygonStipple, 0);
    rb_define_module_function(module, "glEdgeFlag", gl_EdgeFlag, 1);
    rb_define_module_function(module, "glScissor", gl_Scissor, 4);
    rb_define_module_function(module, "glClipPlane", gl_ClipPlane, 2);
    rb_define_module_function(module, "glDrawBuffer", gl_DrawBuffer, 1);
    rb_define_module_function(module, "glReadBuffer", gl_ReadBuffer, 1);
    rb_define_module_function(module, "glEnable", gl_Enable, 1);
    rb_define_module_function(module, "glDisable", gl_Disable, 1);
    rb_define_module_function(module, "glIsEnabled", gl_IsEnabled, 1);
    rb_define_module_function(module, "glGetDoublev", gl_GetDoublev, 1);
    rb_define_alias(module, "glGetDouble", "glGetDoublev");
    rb_define_module_function(module, "glPushAttrib", gl_PushAttrib, 1);
    rb_define_module_function(module, "glPopAttrib", gl_PopAttrib, 0);
    rb_define_module_function(module, "glRenderMode", gl_RenderMode, 1);
    rb_define_module_function(module, "glGetError", gl_GetError, 0);
    rb_define_module_function(module, "glGetString", gl_GetString, 1);
    rb_define_module_function(module, "glFinish", gl_Finish, 0);
    rb_define_module_function(module, "glFlush", gl_Flush, 0);
    rb_define_module_function(module, "glHint", gl_Hint, 2);
    rb_define_module_function(module, "glClearDepth", gl_ClearDepth, 1);
    rb_define_module_function(module, "glDepthFunc", gl_DepthFunc, 1);
    rb_define_module_function(module, "glDepthMask", gl_DepthMask, 1);
    rb_define_module_function(module, "glDepthRange", gl_DepthRange, 2);
    rb_define_module_function(module, "glClearAccum", gl_ClearAccum, 4);
    rb_define_module_function(module, "glAccum", gl_Accum, 2);
    rb_define_module_function(module, "glMatrixMode", gl_MatrixMode, 1);
    rb_define_module_function(module, "glOrtho", gl_Ortho, 6);
    rb_define_module_function(module, "glFrustum", gl_Frustum, 6);
    rb_define_module_function(module, "glViewport", gl_Viewport, 4);
    rb_define_module_function(module, "glPushMatrix", gl_PushMatrix, 0);
    rb_define_module_function(module, "glPopMatrix", gl_PopMatrix, 0);
    rb_define_module_function(module, "glLoadIdentity", gl_LoadIdentity, 0);
    rb_define_module_function(module, "glLoadMatrix", gl_LoadMatrixd, 1);
    rb_define_module_function(module, "glMultMatrix", gl_MultMatrixd, 1);
    rb_define_module_function(module, "glRotated", gl_Rotated, 4);
    rb_define_module_function(module, "glRotate", gl_Rotated, 4);
    rb_define_module_function(module, "glScaled", gl_Scaled, 3);
    rb_define_module_function(module, "glScale", gl_Scaled, 3);
    rb_define_module_function(module, "glTranslated", gl_Translated, 3);
    rb_define_module_function(module, "glTranslate", gl_Translated, 3);
    rb_define_module_function(module, "glIsList", gl_IsList, 1);
    rb_define_module_function(module, "glDeleteLists", gl_DeleteLists, 2);
    rb_define_module_function(module, "glGenLists", gl_GenLists, 1);
    rb_define_module_function(module, "glNewList", gl_NewList, 2);
    rb_define_module_function(module, "glEndList", gl_EndList, 0);
    rb_define_module_function(module, "glCallList", gl_CallList, 1);
    rb_define_module_function(module, "glCallLists", gl_CallLists, 1);
    rb_define_module_function(module, "glListBase", gl_ListBase, 1);
    rb_define_module_function(module, "glBegin", gl_Begin, 1);
    rb_define_module_function(module, "glEnd", gl_End, 0);
    rb_define_module_function(module, "glVertex2d", gl_Vertex2d, 2);
    rb_define_module_function(module, "glVertex2f", gl_Vertex2f, 2);
    rb_define_module_function(module, "glVertex2i", gl_Vertex2i, 2);
    rb_define_module_function(module, "glVertex3d", gl_Vertex3d, 3);
    rb_define_module_function(module, "glVertex3f", gl_Vertex3f, 3);
    rb_define_module_function(module, "glVertex3i", gl_Vertex3i, 3);
    rb_define_module_function(module, "glVertex4d", gl_Vertex4d, 4);
    rb_define_module_function(module, "glVertex4f", gl_Vertex4f, 4);
    rb_define_module_function(module, "glVertex4i", gl_Vertex4i, 4);
    rb_define_module_function(module, "glVertex", gl_Vertex, -1);
    rb_define_module_function(module, "glNormal3d", gl_Normal3d, 3);
    rb_define_module_function(module, "glNormal3i", gl_Normal3i, 3);
    rb_define_module_function(module, "glNormal", gl_Normal, -1);
    rb_define_module_function(module, "glIndexd", gl_Indexd, 1);
    rb_define_module_function(module, "glIndexi", gl_Indexi, 1);
    rb_define_module_function(module, "glIndex", gl_Indexi, 1);
    rb_define_module_function(module, "glColor3d", gl_Color3d, 3);
    rb_define_module_function(module, "glColor3f", gl_Color3f, 3);
    rb_define_module_function(module, "glColor3i", gl_Color3i, 3);
    rb_define_module_function(module, "glColor3s", gl_Color3s, 3);
    rb_define_module_function(module, "glColor3ub", gl_Color3ub, 3);
    rb_define_module_function(module, "glColor3ui", gl_Color3ui, 3);
    rb_define_module_function(module, "glColor3us", gl_Color3us, 3);
    rb_define_module_function(module, "glColor4b", gl_Color4b, 4);
    rb_define_module_function(module, "glColor4d", gl_Color4d, 4);
    rb_define_module_function(module, "glColor4f", gl_Color4f, 4);
    rb_define_module_function(module, "glColor4i", gl_Color4i, 4);
    rb_define_module_function(module, "glColor4s", gl_Color4s, 4);
    rb_define_module_function(module, "glColor4ub", gl_Color4ub, 4);
    rb_define_module_function(module, "glColor4ui", gl_Color4ui, 4);
    rb_define_module_function(module, "glColor4us", gl_Color4us, 4);
    rb_define_module_function(module, "glColor", gl_Color, -1);
    rb_define_module_function(module, "glTexCoord1d", gl_TexCoord1d, 1);
    rb_define_module_function(module, "glTexCoord1f", gl_TexCoord1f, 1);
    rb_define_module_function(module, "glTexCoord1i", gl_TexCoord1i, 1);
    rb_define_module_function(module, "glTexCoord1s", gl_TexCoord1s, 1);
    rb_define_module_function(module, "glTexCoord2d", gl_TexCoord2d, 2);
    rb_define_module_function(module, "glTexCoord2f", gl_TexCoord2f, 2);
    rb_define_module_function(module, "glTexCoord2i", gl_TexCoord2i, 2);
    rb_define_module_function(module, "glTexCoord2s", gl_TexCoord2s, 2);
    rb_define_module_function(module, "glTexCoord3d", gl_TexCoord3d, 3);
    rb_define_module_function(module, "glTexCoord3f", gl_TexCoord3f, 3);
    rb_define_module_function(module, "glTexCoord3i", gl_TexCoord3i, 3);
    rb_define_module_function(module, "glTexCoord3s", gl_TexCoord3s, 3);
    rb_define_module_function(module, "glTexCoord4d", gl_TexCoord4d, 4);
    rb_define_module_function(module, "glTexCoord4f", gl_TexCoord4f, 4);
    rb_define_module_function(module, "glTexCoord4i", gl_TexCoord4i, 4);
    rb_define_module_function(module, "glTexCoord4s", gl_TexCoord4s, 4);
    rb_define_module_function(module, "glTexCoord", gl_TexCoord, -1);
    rb_define_module_function(module, "glRasterPos2d", gl_RasterPos2d, 2);
    rb_define_module_function(module, "glRasterPos2i", gl_RasterPos2i, 2);
    rb_define_module_function(module, "glRasterPos3d", gl_RasterPos3d, 3);
    rb_define_module_function(module, "glRasterPos3i", gl_RasterPos3i, 3);
    rb_define_module_function(module, "glRasterPos4d", gl_RasterPos4d, 4);
    rb_define_module_function(module, "glRasterPos4i", gl_RasterPos4i, 4);
    rb_define_module_function(module, "glRasterPos", gl_RasterPos, -1);
    rb_define_module_function(module, "glRectd", gl_Rectd, 4);
    rb_define_module_function(module, "glRecti", gl_Recti, 4);
    rb_define_module_function(module, "glRect", gl_Rect, -1);
    rb_define_module_function(module, "glShadeModel", gl_ShadeModel, 1);
    rb_define_module_function(module, "glLightf", gl_Lightf, 3);
    rb_define_module_function(module, "glLighti", gl_Lighti, 3);
    rb_define_module_function(module, "glLightiv", gl_Lightiv, 3);
    rb_define_module_function(module, "glLightfv", gl_Light, 3);
    rb_define_module_function(module, "glLight", gl_Light, 3);
    rb_define_module_function(module, "glLightModelf", gl_LightModelf, 2);
    rb_define_module_function(module, "glLightModeli", gl_LightModeli, 2);
    rb_define_module_function(module, "glLightModel", gl_LightModel, 2);
    rb_define_module_function(module, "glMaterialf", gl_Materialf, 3);
    rb_define_module_function(module, "glMateriali", gl_Materiali, 3);
    rb_define_module_function(module, "glMaterial", gl_Material, 3);
    rb_define_module_function(module, "glGetMaterial", gl_GetMaterial, 2);
    rb_define_module_function(module, "glColorMaterial", gl_ColorMaterial, 2);
    rb_define_module_function(module, "glPixelZoom", gl_PixelZoom, 2);
    rb_define_module_function(module, "glPixelStoref", gl_PixelStoref, 2);
    rb_define_module_function(module, "glPixelStorei", gl_PixelStorei, 2);
    rb_define_module_function(module, "glPixelStore", gl_PixelStoref, 2);
    rb_define_module_function(module, "glPixelTransferf", gl_PixelTransferf, 2);
    rb_define_module_function(module, "glPixelTransferi", gl_PixelTransferi, 2);
    rb_define_module_function(module, "glPixelTransfer", gl_PixelTransferf, 2);
    rb_define_module_function(module, "glBitmap", gl_Bitmap, 7);
    rb_define_module_function(module, "glReadPixels", gl_ReadPixels, 6);
    rb_define_module_function(module, "glDrawPixels", gl_DrawPixels, 5);
    rb_define_module_function(module, "glCopyPixels", gl_CopyPixels, 5);
    rb_define_module_function(module, "glStencilFunc", gl_StencilFunc, 3);
    rb_define_module_function(module, "glStencilMask", gl_StencilMask, 1);
    rb_define_module_function(module, "glStencilOp", gl_StencilOp, 3);
    rb_define_module_function(module, "glClearStencil", gl_ClearStencil, 1);
    rb_define_module_function(module, "glTexGend", gl_TexGend, 3);
    rb_define_module_function(module, "glTexGeni", gl_TexGeni, 3);
    rb_define_module_function(module, "glTexGen", gl_TexGen, 3);
    rb_define_module_function(module, "glTexEnvf", gl_TexEnvf, 3);
    rb_define_module_function(module, "glTexEnvi", gl_TexEnvi, 3);
    rb_define_module_function(module, "glTexEnv", gl_TexEnvf, 3);
    rb_define_module_function(module, "glTexParameterf", gl_TexParameterf, 3);
    rb_define_module_function(module, "glTexParameteri", gl_TexParameteri, 3);
    rb_define_module_function(module, "glTexParameter", gl_TexParameterf, 3);
    rb_define_module_function(module, "glTexImage2D", gl_TexImage2D, 9);
    rb_define_module_function(module, "glMap1d", gl_Map1d, 6);
    rb_define_module_function(module, "glMap2d", gl_Map2d, 10);
    rb_define_module_function(module, "glEvalCoord1d", gl_EvalCoord1d, 1);
    rb_define_module_function(module, "glEvalCoord2d", gl_EvalCoord2d, 2);
    rb_define_module_function(module, "glMapGrid1d", gl_MapGrid1d, 3);
    rb_define_module_function(module, "glMapGrid2d", gl_MapGrid2d, 6);
    rb_define_module_function(module, "glEvalPoint1", gl_EvalPoint1, 1);
    rb_define_module_function(module, "glEvalPoint2", gl_EvalPoint2, 2);
    rb_define_module_function(module, "glEvalMesh1", gl_EvalMesh1, 3);
    rb_define_module_function(module, "glEvalMesh2", gl_EvalMesh2, 5);
    rb_define_module_function(module, "glFogf", gl_Fogf, 2);
    rb_define_module_function(module, "glFogi", gl_Fogi, 2);
    rb_define_module_function(module, "glFog", gl_Fogfv, 2);
    rb_define_module_function(module, "glPassThrough", gl_PassThrough, 1);
    rb_define_module_function(module, "glFeedbackBuffer", gl_FeedbackBuffer, -1);
    rb_define_module_function(module, "glSelectBuffer", gl_SelectBuffer, -1);
    rb_define_module_function(module, "glInitNames", gl_InitNames, 0);
    rb_define_module_function(module, "glLoadName", gl_LoadName, 1);
    rb_define_module_function(module, "glPushName", gl_PushName, 1);
    rb_define_module_function(module, "glPopName", gl_PopName, 0);
#if defined(GL_VERSION_1_1)
    rb_define_module_function(module, "glEnableClientState", gl_EnableClientState, 1);
    rb_define_module_function(module, "glDisableClientState", gl_DisableClientState, 1);
    rb_define_module_function(module, "glPushClientAttrib", gl_PushClientAttrib, 1);
    rb_define_module_function(module, "glPopClientAttrib", gl_PopClientAttrib, 0);
    rb_define_module_function(module, "glVertexPointer", gl_VertexPointer, 4);
    rb_define_module_function(module, "glNormalPointer", gl_NormalPointer, 3);
    rb_define_module_function(module, "glColorPointer", gl_ColorPointer, 4);
    rb_define_module_function(module, "glIndexPointer", gl_IndexPointer, 3);
    rb_define_module_function(module, "glTexCoordPointer", gl_TexCoordPointer, 4);
    rb_define_module_function(module, "glEdgeFlagPointer", gl_EdgeFlagPointer, 2);
    rb_define_module_function(module, "glArrayElement", gl_ArrayElement, 1);
    rb_define_module_function(module, "glDrawArrays", gl_DrawArrays, 3);
    rb_define_module_function(module, "glDrawElements", gl_DrawElements, 4);
    rb_define_module_function(module, "glInterleavedArrays", gl_InterleavedArrays, 3);
    rb_define_module_function(module, "glGenTextures", gl_GenTextures, 1);
    rb_define_module_function(module, "glDeleteTextures", gl_DeleteTextures, 1);
    rb_define_module_function(module, "glBindTexture", gl_BindTexture, 2);
    rb_define_module_function(module, "glIsTexture", gl_IsTexture, 1);
    rb_define_module_function(module, "glTexSubImage2D", gl_TexSubImage2D, 9);
    rb_define_module_function(module, "glCopyTexImage1D", gl_CopyTexImage1D, 7);
    rb_define_module_function(module, "glCopyTexImage2D", gl_CopyTexImage2D, 8);
    rb_define_module_function(module, "glCopyTexSubImage1D", gl_CopyTexSubImage1D, 6);
    rb_define_module_function(module, "glCopyTexSubImage2D", gl_CopyTexSubImage2D, 8);
#endif /* GL_VERSION_1_1 */

#if defined (GL_VERSION_1_2)
    rb_define_module_function(module, "glDrawRangeElements", gl_DrawRangeElements, 6);
    rb_define_module_function(module, "glTexImage3D", gl_TexImage3D, 10);
    rb_define_module_function(module, "glTexSubImage3D", gl_TexSubImage3D, 11);
    rb_define_module_function(module, "glCopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
#endif /* GL_VERSION_1_2 */

    rb_define_const(module, "GL_FALSE", INT2NUM(GL_FALSE));
    rb_define_const(module, "GL_TRUE", INT2NUM(GL_TRUE));
    rb_define_const(module, "GL_BYTE", INT2NUM(GL_BYTE));
    rb_define_const(module, "GL_UNSIGNED_BYTE", INT2NUM(GL_UNSIGNED_BYTE));
    rb_define_const(module, "GL_SHORT", INT2NUM(GL_SHORT));
    rb_define_const(module, "GL_UNSIGNED_SHORT", INT2NUM(GL_UNSIGNED_SHORT));
    rb_define_const(module, "GL_INT", INT2NUM(GL_INT));
    rb_define_const(module, "GL_UNSIGNED_INT", INT2NUM(GL_UNSIGNED_INT));
    rb_define_const(module, "GL_FLOAT", INT2NUM(GL_FLOAT));
    rb_define_const(module, "GL_DOUBLE", INT2NUM(GL_DOUBLE));
    rb_define_const(module, "GL_GL_2_BYTES", INT2NUM(GL_2_BYTES));
    rb_define_const(module, "GL_GL_3_BYTES", INT2NUM(GL_3_BYTES));
    rb_define_const(module, "GL_GL_4_BYTES", INT2NUM(GL_4_BYTES));
    rb_define_const(module, "GL_LINES", INT2NUM(GL_LINES));
    rb_define_const(module, "GL_POINTS", INT2NUM(GL_POINTS));
    rb_define_const(module, "GL_LINE_STRIP", INT2NUM(GL_LINE_STRIP));
    rb_define_const(module, "GL_LINE_LOOP", INT2NUM(GL_LINE_LOOP));
    rb_define_const(module, "GL_TRIANGLES", INT2NUM(GL_TRIANGLES));
    rb_define_const(module, "GL_TRIANGLE_STRIP", INT2NUM(GL_TRIANGLE_STRIP));
    rb_define_const(module, "GL_TRIANGLE_FAN", INT2NUM(GL_TRIANGLE_FAN));
    rb_define_const(module, "GL_QUADS", INT2NUM(GL_QUADS));
    rb_define_const(module, "GL_QUAD_STRIP", INT2NUM(GL_QUAD_STRIP));
    rb_define_const(module, "GL_POLYGON", INT2NUM(GL_POLYGON));
    rb_define_const(module, "GL_EDGE_FLAG", INT2NUM(GL_EDGE_FLAG));
#if defined(GL_VERSION_1_1)
    rb_define_const(module, "GL_VERTEX_ARRAY", INT2NUM(GL_VERTEX_ARRAY));
    rb_define_const(module, "GL_NORMAL_ARRAY", INT2NUM(GL_NORMAL_ARRAY));
    rb_define_const(module, "GL_COLOR_ARRAY", INT2NUM(GL_COLOR_ARRAY));
    rb_define_const(module, "GL_INDEX_ARRAY", INT2NUM(GL_INDEX_ARRAY));
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY", INT2NUM(GL_TEXTURE_COORD_ARRAY));
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY", INT2NUM(GL_EDGE_FLAG_ARRAY));
    rb_define_const(module, "GL_VERTEX_ARRAY_SIZE", INT2NUM(GL_VERTEX_ARRAY_SIZE));
    rb_define_const(module, "GL_VERTEX_ARRAY_TYPE", INT2NUM(GL_VERTEX_ARRAY_TYPE));
    rb_define_const(module, "GL_VERTEX_ARRAY_STRIDE", INT2NUM(GL_VERTEX_ARRAY_STRIDE));
    rb_define_const(module, "GL_NORMAL_ARRAY_TYPE", INT2NUM(GL_NORMAL_ARRAY_TYPE));
    rb_define_const(module, "GL_NORMAL_ARRAY_STRIDE", INT2NUM(GL_NORMAL_ARRAY_STRIDE));
    rb_define_const(module, "GL_COLOR_ARRAY_SIZE", INT2NUM(GL_COLOR_ARRAY_SIZE));
    rb_define_const(module, "GL_COLOR_ARRAY_TYPE", INT2NUM(GL_COLOR_ARRAY_TYPE));
    rb_define_const(module, "GL_COLOR_ARRAY_STRIDE", INT2NUM(GL_COLOR_ARRAY_STRIDE));
    rb_define_const(module, "GL_INDEX_ARRAY_TYPE", INT2NUM(GL_INDEX_ARRAY_TYPE));
    rb_define_const(module, "GL_INDEX_ARRAY_STRIDE", INT2NUM(GL_INDEX_ARRAY_STRIDE));
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_SIZE", INT2NUM(GL_TEXTURE_COORD_ARRAY_SIZE));
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_TYPE", INT2NUM(GL_TEXTURE_COORD_ARRAY_TYPE));
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_STRIDE", INT2NUM(GL_TEXTURE_COORD_ARRAY_STRIDE));
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_STRIDE", INT2NUM(GL_EDGE_FLAG_ARRAY_STRIDE));
    rb_define_const(module, "GL_VERTEX_ARRAY_POINTER", INT2NUM(GL_VERTEX_ARRAY_POINTER));
    rb_define_const(module, "GL_NORMAL_ARRAY_POINTER", INT2NUM(GL_NORMAL_ARRAY_POINTER));
    rb_define_const(module, "GL_COLOR_ARRAY_POINTER", INT2NUM(GL_COLOR_ARRAY_POINTER));
    rb_define_const(module, "GL_INDEX_ARRAY_POINTER", INT2NUM(GL_INDEX_ARRAY_POINTER));
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_POINTER", INT2NUM(GL_TEXTURE_COORD_ARRAY_POINTER));
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_POINTER", INT2NUM(GL_EDGE_FLAG_ARRAY_POINTER));
    rb_define_const(module, "GL_V2F", INT2NUM(GL_V2F));
    rb_define_const(module, "GL_V3F", INT2NUM(GL_V3F));
    rb_define_const(module, "GL_C4UB_V2F", INT2NUM(GL_C4UB_V2F));
    rb_define_const(module, "GL_C4UB_V3F", INT2NUM(GL_C4UB_V3F));
    rb_define_const(module, "GL_C3F_V3F", INT2NUM(GL_C3F_V3F));
    rb_define_const(module, "GL_N3F_V3F", INT2NUM(GL_N3F_V3F));
    rb_define_const(module, "GL_C4F_N3F_V3F", INT2NUM(GL_C4F_N3F_V3F));
    rb_define_const(module, "GL_T2F_V3F", INT2NUM(GL_T2F_V3F));
    rb_define_const(module, "GL_T4F_V4F", INT2NUM(GL_T4F_V4F));
    rb_define_const(module, "GL_T2F_C4UB_V3F", INT2NUM(GL_T2F_C4UB_V3F));
    rb_define_const(module, "GL_T2F_C3F_V3F", INT2NUM(GL_T2F_C3F_V3F));
    rb_define_const(module, "GL_T2F_N3F_V3F", INT2NUM(GL_T2F_N3F_V3F));
    rb_define_const(module, "GL_T2F_C4F_N3F_V3F", INT2NUM(GL_T2F_C4F_N3F_V3F));
    rb_define_const(module, "GL_T4F_C4F_N3F_V4F", INT2NUM(GL_T4F_C4F_N3F_V4F));
#endif /* GL_VERSION_1_1 */
    rb_define_const(module, "GL_MATRIX_MODE", INT2NUM(GL_MATRIX_MODE));
    rb_define_const(module, "GL_MODELVIEW", INT2NUM(GL_MODELVIEW));
    rb_define_const(module, "GL_PROJECTION", INT2NUM(GL_PROJECTION));
    rb_define_const(module, "GL_TEXTURE", INT2NUM(GL_TEXTURE));
    rb_define_const(module, "GL_POINT_SMOOTH", INT2NUM(GL_POINT_SMOOTH));
    rb_define_const(module, "GL_POINT_SIZE", INT2NUM(GL_POINT_SIZE));
    rb_define_const(module, "GL_POINT_SIZE_GRANULARITY", INT2NUM(GL_POINT_SIZE_GRANULARITY));
    rb_define_const(module, "GL_POINT_SIZE_RANGE", INT2NUM(GL_POINT_SIZE_RANGE));
    rb_define_const(module, "GL_LINE_SMOOTH", INT2NUM(GL_LINE_SMOOTH));
    rb_define_const(module, "GL_LINE_STIPPLE", INT2NUM(GL_LINE_STIPPLE));
    rb_define_const(module, "GL_LINE_STIPPLE_PATTERN", INT2NUM(GL_LINE_STIPPLE_PATTERN));
    rb_define_const(module, "GL_LINE_STIPPLE_REPEAT", INT2NUM(GL_LINE_STIPPLE_REPEAT));
    rb_define_const(module, "GL_LINE_WIDTH", INT2NUM(GL_LINE_WIDTH));
    rb_define_const(module, "GL_LINE_WIDTH_GRANULARITY", INT2NUM(GL_LINE_WIDTH_GRANULARITY));
    rb_define_const(module, "GL_LINE_WIDTH_RANGE", INT2NUM(GL_LINE_WIDTH_RANGE));
    rb_define_const(module, "GL_POINT", INT2NUM(GL_POINT));
    rb_define_const(module, "GL_LINE", INT2NUM(GL_LINE));
    rb_define_const(module, "GL_FILL", INT2NUM(GL_FILL));
    rb_define_const(module, "GL_CCW", INT2NUM(GL_CCW));
    rb_define_const(module, "GL_CW", INT2NUM(GL_CW));
    rb_define_const(module, "GL_FRONT", INT2NUM(GL_FRONT));
    rb_define_const(module, "GL_BACK", INT2NUM(GL_BACK));
    rb_define_const(module, "GL_CULL_FACE", INT2NUM(GL_CULL_FACE));
    rb_define_const(module, "GL_CULL_FACE_MODE", INT2NUM(GL_CULL_FACE_MODE));
    rb_define_const(module, "GL_POLYGON_SMOOTH", INT2NUM(GL_POLYGON_SMOOTH));
    rb_define_const(module, "GL_POLYGON_STIPPLE", INT2NUM(GL_POLYGON_STIPPLE));
    rb_define_const(module, "GL_FRONT_FACE", INT2NUM(GL_FRONT_FACE));
    rb_define_const(module, "GL_POLYGON_MODE", INT2NUM(GL_POLYGON_MODE));
    rb_define_const(module, "GL_POLYGON_OFFSET_FACTOR", INT2NUM(GL_POLYGON_OFFSET_FACTOR));
    rb_define_const(module, "GL_POLYGON_OFFSET_UNITS", INT2NUM(GL_POLYGON_OFFSET_UNITS));
    rb_define_const(module, "GL_POLYGON_OFFSET_POINT", INT2NUM(GL_POLYGON_OFFSET_POINT));
    rb_define_const(module, "GL_POLYGON_OFFSET_LINE", INT2NUM(GL_POLYGON_OFFSET_LINE));
    rb_define_const(module, "GL_POLYGON_OFFSET_FILL", INT2NUM(GL_POLYGON_OFFSET_FILL));
    rb_define_const(module, "GL_COMPILE", INT2NUM(GL_COMPILE));
    rb_define_const(module, "GL_COMPILE_AND_EXECUTE", INT2NUM(GL_COMPILE_AND_EXECUTE));
    rb_define_const(module, "GL_LIST_BASE", INT2NUM(GL_LIST_BASE));
    rb_define_const(module, "GL_LIST_INDEX", INT2NUM(GL_LIST_INDEX));
    rb_define_const(module, "GL_LIST_MODE", INT2NUM(GL_LIST_MODE));
    rb_define_const(module, "GL_NEVER", INT2NUM(GL_NEVER));
    rb_define_const(module, "GL_LESS", INT2NUM(GL_LESS));
    rb_define_const(module, "GL_GEQUAL", INT2NUM(GL_GEQUAL));
    rb_define_const(module, "GL_LEQUAL", INT2NUM(GL_LEQUAL));
    rb_define_const(module, "GL_GREATER", INT2NUM(GL_GREATER));
    rb_define_const(module, "GL_NOTEQUAL", INT2NUM(GL_NOTEQUAL));
    rb_define_const(module, "GL_EQUAL", INT2NUM(GL_EQUAL));
    rb_define_const(module, "GL_ALWAYS", INT2NUM(GL_ALWAYS));
    rb_define_const(module, "GL_DEPTH_TEST", INT2NUM(GL_DEPTH_TEST));
    rb_define_const(module, "GL_DEPTH_BITS", INT2NUM(GL_DEPTH_BITS));
    rb_define_const(module, "GL_DEPTH_CLEAR_VALUE", INT2NUM(GL_DEPTH_CLEAR_VALUE));
    rb_define_const(module, "GL_DEPTH_FUNC", INT2NUM(GL_DEPTH_FUNC));
    rb_define_const(module, "GL_DEPTH_RANGE", INT2NUM(GL_DEPTH_RANGE));
    rb_define_const(module, "GL_DEPTH_WRITEMASK", INT2NUM(GL_DEPTH_WRITEMASK));
    rb_define_const(module, "GL_DEPTH_COMPONENT", INT2NUM(GL_DEPTH_COMPONENT));
    rb_define_const(module, "GL_LIGHTING", INT2NUM(GL_LIGHTING));
    rb_define_const(module, "GL_LIGHT0", INT2NUM(GL_LIGHT0));
    rb_define_const(module, "GL_LIGHT1", INT2NUM(GL_LIGHT1));
    rb_define_const(module, "GL_LIGHT2", INT2NUM(GL_LIGHT2));
    rb_define_const(module, "GL_LIGHT3", INT2NUM(GL_LIGHT3));
    rb_define_const(module, "GL_LIGHT4", INT2NUM(GL_LIGHT4));
    rb_define_const(module, "GL_LIGHT5", INT2NUM(GL_LIGHT5));
    rb_define_const(module, "GL_LIGHT6", INT2NUM(GL_LIGHT6));
    rb_define_const(module, "GL_LIGHT7", INT2NUM(GL_LIGHT7));
    rb_define_const(module, "GL_SPOT_EXPONENT", INT2NUM(GL_SPOT_EXPONENT));
    rb_define_const(module, "GL_SPOT_CUTOFF", INT2NUM(GL_SPOT_CUTOFF));
    rb_define_const(module, "GL_CONSTANT_ATTENUATION", INT2NUM(GL_CONSTANT_ATTENUATION));
    rb_define_const(module, "GL_LINEAR_ATTENUATION", INT2NUM(GL_LINEAR_ATTENUATION));
    rb_define_const(module, "GL_QUADRATIC_ATTENUATION", INT2NUM(GL_QUADRATIC_ATTENUATION));
    rb_define_const(module, "GL_AMBIENT", INT2NUM(GL_AMBIENT));
    rb_define_const(module, "GL_DIFFUSE", INT2NUM(GL_DIFFUSE));
    rb_define_const(module, "GL_SPECULAR", INT2NUM(GL_SPECULAR));
    rb_define_const(module, "GL_SHININESS", INT2NUM(GL_SHININESS));
    rb_define_const(module, "GL_EMISSION", INT2NUM(GL_EMISSION));
    rb_define_const(module, "GL_POSITION", INT2NUM(GL_POSITION));
    rb_define_const(module, "GL_SPOT_DIRECTION", INT2NUM(GL_SPOT_DIRECTION));
    rb_define_const(module, "GL_AMBIENT_AND_DIFFUSE", INT2NUM(GL_AMBIENT_AND_DIFFUSE));
    rb_define_const(module, "GL_COLOR_INDEXES", INT2NUM(GL_COLOR_INDEXES));
    rb_define_const(module, "GL_LIGHT_MODEL_TWO_SIDE", INT2NUM(GL_LIGHT_MODEL_TWO_SIDE));
    rb_define_const(module, "GL_LIGHT_MODEL_LOCAL_VIEWER", INT2NUM(GL_LIGHT_MODEL_LOCAL_VIEWER));
    rb_define_const(module, "GL_LIGHT_MODEL_AMBIENT", INT2NUM(GL_LIGHT_MODEL_AMBIENT));
    rb_define_const(module, "GL_FRONT_AND_BACK", INT2NUM(GL_FRONT_AND_BACK));
    rb_define_const(module, "GL_SHADE_MODEL", INT2NUM(GL_SHADE_MODEL));
    rb_define_const(module, "GL_FLAT", INT2NUM(GL_FLAT));
    rb_define_const(module, "GL_SMOOTH", INT2NUM(GL_SMOOTH));
    rb_define_const(module, "GL_COLOR_MATERIAL", INT2NUM(GL_COLOR_MATERIAL));
    rb_define_const(module, "GL_COLOR_MATERIAL_FACE", INT2NUM(GL_COLOR_MATERIAL_FACE));
    rb_define_const(module, "GL_COLOR_MATERIAL_PARAMETER", INT2NUM(GL_COLOR_MATERIAL_PARAMETER));
    rb_define_const(module, "GL_NORMALIZE", INT2NUM(GL_NORMALIZE));
    rb_define_const(module, "GL_CLIP_PLANE0", INT2NUM(GL_CLIP_PLANE0));
    rb_define_const(module, "GL_CLIP_PLANE1", INT2NUM(GL_CLIP_PLANE1));
    rb_define_const(module, "GL_CLIP_PLANE2", INT2NUM(GL_CLIP_PLANE2));
    rb_define_const(module, "GL_CLIP_PLANE3", INT2NUM(GL_CLIP_PLANE3));
    rb_define_const(module, "GL_CLIP_PLANE4", INT2NUM(GL_CLIP_PLANE4));
    rb_define_const(module, "GL_CLIP_PLANE5", INT2NUM(GL_CLIP_PLANE5));
    rb_define_const(module, "GL_ACCUM_RED_BITS", INT2NUM(GL_ACCUM_RED_BITS));
    rb_define_const(module, "GL_ACCUM_GREEN_BITS", INT2NUM(GL_ACCUM_GREEN_BITS));
    rb_define_const(module, "GL_ACCUM_BLUE_BITS", INT2NUM(GL_ACCUM_BLUE_BITS));
    rb_define_const(module, "GL_ACCUM_ALPHA_BITS", INT2NUM(GL_ACCUM_ALPHA_BITS));
    rb_define_const(module, "GL_ACCUM_CLEAR_VALUE", INT2NUM(GL_ACCUM_CLEAR_VALUE));
    rb_define_const(module, "GL_ACCUM", INT2NUM(GL_ACCUM));
    rb_define_const(module, "GL_ADD", INT2NUM(GL_ADD));
    rb_define_const(module, "GL_LOAD", INT2NUM(GL_LOAD));
    rb_define_const(module, "GL_MULT", INT2NUM(GL_MULT));
    rb_define_const(module, "GL_RETURN", INT2NUM(GL_RETURN));
    rb_define_const(module, "GL_ALPHA_TEST", INT2NUM(GL_ALPHA_TEST));
    rb_define_const(module, "GL_ALPHA_TEST_REF", INT2NUM(GL_ALPHA_TEST_REF));
    rb_define_const(module, "GL_ALPHA_TEST_FUNC", INT2NUM(GL_ALPHA_TEST_FUNC));
    rb_define_const(module, "GL_BLEND", INT2NUM(GL_BLEND));
    rb_define_const(module, "GL_BLEND_SRC", INT2NUM(GL_BLEND_SRC));
    rb_define_const(module, "GL_BLEND_DST", INT2NUM(GL_BLEND_DST));
    rb_define_const(module, "GL_ZERO", INT2NUM(GL_ZERO));
    rb_define_const(module, "GL_ONE", INT2NUM(GL_ONE));
    rb_define_const(module, "GL_SRC_COLOR", INT2NUM(GL_SRC_COLOR));
    rb_define_const(module, "GL_ONE_MINUS_SRC_COLOR", INT2NUM(GL_ONE_MINUS_SRC_COLOR));
    rb_define_const(module, "GL_DST_COLOR", INT2NUM(GL_DST_COLOR));
    rb_define_const(module, "GL_ONE_MINUS_DST_COLOR", INT2NUM(GL_ONE_MINUS_DST_COLOR));
    rb_define_const(module, "GL_SRC_ALPHA", INT2NUM(GL_SRC_ALPHA));
    rb_define_const(module, "GL_ONE_MINUS_SRC_ALPHA", INT2NUM(GL_ONE_MINUS_SRC_ALPHA));
    rb_define_const(module, "GL_DST_ALPHA", INT2NUM(GL_DST_ALPHA));
    rb_define_const(module, "GL_ONE_MINUS_DST_ALPHA", INT2NUM(GL_ONE_MINUS_DST_ALPHA));
    rb_define_const(module, "GL_SRC_ALPHA_SATURATE", INT2NUM(GL_SRC_ALPHA_SATURATE));
#if defined(GL_VERSION_1_2)
    rb_define_const(module, "GL_CONSTANT_COLOR", INT2NUM(GL_CONSTANT_COLOR));
    rb_define_const(module, "GL_ONE_MINUS_CONSTANT_COLOR", INT2NUM(GL_ONE_MINUS_CONSTANT_COLOR));
    rb_define_const(module, "GL_CONSTANT_ALPHA", INT2NUM(GL_CONSTANT_ALPHA));
    rb_define_const(module, "GL_ONE_MINUS_CONSTANT_ALPHA", INT2NUM(GL_ONE_MINUS_CONSTANT_ALPHA));
#endif /* GL_VERSION_1_2 */
    rb_define_const(module, "GL_FEEDBACK", INT2NUM(GL_FEEDBACK));
    rb_define_const(module, "GL_RENDER", INT2NUM(GL_RENDER));
    rb_define_const(module, "GL_SELECT", INT2NUM(GL_SELECT));
    rb_define_const(module, "GL_GL_2D", INT2NUM(GL_2D));
    rb_define_const(module, "GL_GL_3D", INT2NUM(GL_3D));
    rb_define_const(module, "GL_GL_3D_COLOR", INT2NUM(GL_3D_COLOR));
    rb_define_const(module, "GL_GL_3D_COLOR_TEXTURE", INT2NUM(GL_3D_COLOR_TEXTURE));
    rb_define_const(module, "GL_GL_4D_COLOR_TEXTURE", INT2NUM(GL_4D_COLOR_TEXTURE));
    rb_define_const(module, "GL_POINT_TOKEN", INT2NUM(GL_POINT_TOKEN));
    rb_define_const(module, "GL_LINE_TOKEN", INT2NUM(GL_LINE_TOKEN));
    rb_define_const(module, "GL_LINE_RESET_TOKEN", INT2NUM(GL_LINE_RESET_TOKEN));
    rb_define_const(module, "GL_POLYGON_TOKEN", INT2NUM(GL_POLYGON_TOKEN));
    rb_define_const(module, "GL_BITMAP_TOKEN", INT2NUM(GL_BITMAP_TOKEN));
    rb_define_const(module, "GL_DRAW_PIXEL_TOKEN", INT2NUM(GL_DRAW_PIXEL_TOKEN));
    rb_define_const(module, "GL_COPY_PIXEL_TOKEN", INT2NUM(GL_COPY_PIXEL_TOKEN));
    rb_define_const(module, "GL_PASS_THROUGH_TOKEN", INT2NUM(GL_PASS_THROUGH_TOKEN));
    rb_define_const(module, "GL_FEEDBACK_BUFFER_POINTER", INT2NUM(GL_FEEDBACK_BUFFER_POINTER));
    rb_define_const(module, "GL_FEEDBACK_BUFFER_SIZE", INT2NUM(GL_FEEDBACK_BUFFER_SIZE));
    rb_define_const(module, "GL_FEEDBACK_BUFFER_TYPE", INT2NUM(GL_FEEDBACK_BUFFER_TYPE));
    rb_define_const(module, "GL_FOG", INT2NUM(GL_FOG));
    rb_define_const(module, "GL_FOG_MODE", INT2NUM(GL_FOG_MODE));
    rb_define_const(module, "GL_FOG_DENSITY", INT2NUM(GL_FOG_DENSITY));
    rb_define_const(module, "GL_FOG_COLOR", INT2NUM(GL_FOG_COLOR));
    rb_define_const(module, "GL_FOG_INDEX", INT2NUM(GL_FOG_INDEX));
    rb_define_const(module, "GL_FOG_START", INT2NUM(GL_FOG_START));
    rb_define_const(module, "GL_FOG_END", INT2NUM(GL_FOG_END));
    rb_define_const(module, "GL_LINEAR", INT2NUM(GL_LINEAR));
    rb_define_const(module, "GL_EXP", INT2NUM(GL_EXP));
    rb_define_const(module, "GL_EXP2", INT2NUM(GL_EXP2));
    rb_define_const(module, "GL_LOGIC_OP", INT2NUM(GL_LOGIC_OP));
    rb_define_const(module, "GL_INDEX_LOGIC_OP", INT2NUM(GL_INDEX_LOGIC_OP));
    rb_define_const(module, "GL_COLOR_LOGIC_OP", INT2NUM(GL_COLOR_LOGIC_OP));
    rb_define_const(module, "GL_LOGIC_OP_MODE", INT2NUM(GL_LOGIC_OP_MODE));
    rb_define_const(module, "GL_CLEAR", INT2NUM(GL_CLEAR));
    rb_define_const(module, "GL_SET", INT2NUM(GL_SET));
    rb_define_const(module, "GL_COPY", INT2NUM(GL_COPY));
    rb_define_const(module, "GL_COPY_INVERTED", INT2NUM(GL_COPY_INVERTED));
    rb_define_const(module, "GL_NOOP", INT2NUM(GL_NOOP));
    rb_define_const(module, "GL_INVERT", INT2NUM(GL_INVERT));
    rb_define_const(module, "GL_AND", INT2NUM(GL_AND));
    rb_define_const(module, "GL_NAND", INT2NUM(GL_NAND));
    rb_define_const(module, "GL_OR", INT2NUM(GL_OR));
    rb_define_const(module, "GL_NOR", INT2NUM(GL_NOR));
    rb_define_const(module, "GL_XOR", INT2NUM(GL_XOR));
    rb_define_const(module, "GL_EQUIV", INT2NUM(GL_EQUIV));
    rb_define_const(module, "GL_AND_REVERSE", INT2NUM(GL_AND_REVERSE));
    rb_define_const(module, "GL_AND_INVERTED", INT2NUM(GL_AND_INVERTED));
    rb_define_const(module, "GL_OR_REVERSE", INT2NUM(GL_OR_REVERSE));
    rb_define_const(module, "GL_OR_INVERTED", INT2NUM(GL_OR_INVERTED));
    rb_define_const(module, "GL_STENCIL_TEST", INT2NUM(GL_STENCIL_TEST));
    rb_define_const(module, "GL_STENCIL_WRITEMASK", INT2NUM(GL_STENCIL_WRITEMASK));
    rb_define_const(module, "GL_STENCIL_BITS", INT2NUM(GL_STENCIL_BITS));
    rb_define_const(module, "GL_STENCIL_FUNC", INT2NUM(GL_STENCIL_FUNC));
    rb_define_const(module, "GL_STENCIL_VALUE_MASK", INT2NUM(GL_STENCIL_VALUE_MASK));
    rb_define_const(module, "GL_STENCIL_REF", INT2NUM(GL_STENCIL_REF));
    rb_define_const(module, "GL_STENCIL_FAIL", INT2NUM(GL_STENCIL_FAIL));
    rb_define_const(module, "GL_STENCIL_PASS_DEPTH_PASS", INT2NUM(GL_STENCIL_PASS_DEPTH_PASS));
    rb_define_const(module, "GL_STENCIL_PASS_DEPTH_FAIL", INT2NUM(GL_STENCIL_PASS_DEPTH_FAIL));
    rb_define_const(module, "GL_STENCIL_CLEAR_VALUE", INT2NUM(GL_STENCIL_CLEAR_VALUE));
    rb_define_const(module, "GL_STENCIL_INDEX", INT2NUM(GL_STENCIL_INDEX));
    rb_define_const(module, "GL_KEEP", INT2NUM(GL_KEEP));
    rb_define_const(module, "GL_REPLACE", INT2NUM(GL_REPLACE));
    rb_define_const(module, "GL_INCR", INT2NUM(GL_INCR));
    rb_define_const(module, "GL_DECR", INT2NUM(GL_DECR));
    rb_define_const(module, "GL_NONE", INT2NUM(GL_NONE));
    rb_define_const(module, "GL_LEFT", INT2NUM(GL_LEFT));
    rb_define_const(module, "GL_RIGHT", INT2NUM(GL_RIGHT));
    rb_define_const(module, "GL_FRONT_LEFT", INT2NUM(GL_FRONT_LEFT));
    rb_define_const(module, "GL_FRONT_RIGHT", INT2NUM(GL_FRONT_RIGHT));
    rb_define_const(module, "GL_BACK_LEFT", INT2NUM(GL_BACK_LEFT));
    rb_define_const(module, "GL_BACK_RIGHT", INT2NUM(GL_BACK_RIGHT));
    rb_define_const(module, "GL_AUX0", INT2NUM(GL_AUX0));
    rb_define_const(module, "GL_AUX1", INT2NUM(GL_AUX1));
    rb_define_const(module, "GL_AUX2", INT2NUM(GL_AUX2));
    rb_define_const(module, "GL_AUX3", INT2NUM(GL_AUX3));
    rb_define_const(module, "GL_COLOR_INDEX", INT2NUM(GL_COLOR_INDEX));
    rb_define_const(module, "GL_RED", INT2NUM(GL_RED));
    rb_define_const(module, "GL_GREEN", INT2NUM(GL_GREEN));
    rb_define_const(module, "GL_BLUE", INT2NUM(GL_BLUE));
    rb_define_const(module, "GL_ALPHA", INT2NUM(GL_ALPHA));
    rb_define_const(module, "GL_LUMINANCE", INT2NUM(GL_LUMINANCE));
    rb_define_const(module, "GL_LUMINANCE_ALPHA", INT2NUM(GL_LUMINANCE_ALPHA));
    rb_define_const(module, "GL_ALPHA_BITS", INT2NUM(GL_ALPHA_BITS));
    rb_define_const(module, "GL_RED_BITS", INT2NUM(GL_RED_BITS));
    rb_define_const(module, "GL_GREEN_BITS", INT2NUM(GL_GREEN_BITS));
    rb_define_const(module, "GL_BLUE_BITS", INT2NUM(GL_BLUE_BITS));
    rb_define_const(module, "GL_INDEX_BITS", INT2NUM(GL_INDEX_BITS));
    rb_define_const(module, "GL_SUBPIXEL_BITS", INT2NUM(GL_SUBPIXEL_BITS));
    rb_define_const(module, "GL_AUX_BUFFERS", INT2NUM(GL_AUX_BUFFERS));
    rb_define_const(module, "GL_READ_BUFFER", INT2NUM(GL_READ_BUFFER));
    rb_define_const(module, "GL_DRAW_BUFFER", INT2NUM(GL_DRAW_BUFFER));
    rb_define_const(module, "GL_DOUBLEBUFFER", INT2NUM(GL_DOUBLEBUFFER));
    rb_define_const(module, "GL_STEREO", INT2NUM(GL_STEREO));
    rb_define_const(module, "GL_BITMAP", INT2NUM(GL_BITMAP));
    rb_define_const(module, "GL_COLOR", INT2NUM(GL_COLOR));
    rb_define_const(module, "GL_DEPTH", INT2NUM(GL_DEPTH));
    rb_define_const(module, "GL_STENCIL", INT2NUM(GL_STENCIL));
    rb_define_const(module, "GL_DITHER", INT2NUM(GL_DITHER));
    rb_define_const(module, "GL_RGB", INT2NUM(GL_RGB));
    rb_define_const(module, "GL_RGBA", INT2NUM(GL_RGBA));
    rb_define_const(module, "GL_MAX_LIST_NESTING", INT2NUM(GL_MAX_LIST_NESTING));
    rb_define_const(module, "GL_MAX_ATTRIB_STACK_DEPTH", INT2NUM(GL_MAX_ATTRIB_STACK_DEPTH));
    rb_define_const(module, "GL_MAX_MODELVIEW_STACK_DEPTH", INT2NUM(GL_MAX_MODELVIEW_STACK_DEPTH));
    rb_define_const(module, "GL_MAX_NAME_STACK_DEPTH", INT2NUM(GL_MAX_NAME_STACK_DEPTH));
    rb_define_const(module, "GL_MAX_PROJECTION_STACK_DEPTH", INT2NUM(GL_MAX_PROJECTION_STACK_DEPTH));
    rb_define_const(module, "GL_MAX_TEXTURE_STACK_DEPTH", INT2NUM(GL_MAX_TEXTURE_STACK_DEPTH));
    rb_define_const(module, "GL_MAX_EVAL_ORDER", INT2NUM(GL_MAX_EVAL_ORDER));
    rb_define_const(module, "GL_MAX_LIGHTS", INT2NUM(GL_MAX_LIGHTS));
    rb_define_const(module, "GL_MAX_CLIP_PLANES", INT2NUM(GL_MAX_CLIP_PLANES));
    rb_define_const(module, "GL_MAX_TEXTURE_SIZE", INT2NUM(GL_MAX_TEXTURE_SIZE));
    rb_define_const(module, "GL_MAX_PIXEL_MAP_TABLE", INT2NUM(GL_MAX_PIXEL_MAP_TABLE));
    rb_define_const(module, "GL_MAX_VIEWPORT_DIMS", INT2NUM(GL_MAX_VIEWPORT_DIMS));
    rb_define_const(module, "GL_ATTRIB_STACK_DEPTH", INT2NUM(GL_ATTRIB_STACK_DEPTH));
    rb_define_const(module, "GL_CLIENT_ATTRIB_STACK_DEPTH", INT2NUM(GL_CLIENT_ATTRIB_STACK_DEPTH));
    rb_define_const(module, "GL_COLOR_CLEAR_VALUE", INT2NUM(GL_COLOR_CLEAR_VALUE));
    rb_define_const(module, "GL_COLOR_WRITEMASK", INT2NUM(GL_COLOR_WRITEMASK));
    rb_define_const(module, "GL_CURRENT_INDEX", INT2NUM(GL_CURRENT_INDEX));
    rb_define_const(module, "GL_CURRENT_COLOR", INT2NUM(GL_CURRENT_COLOR));
    rb_define_const(module, "GL_CURRENT_NORMAL", INT2NUM(GL_CURRENT_NORMAL));
    rb_define_const(module, "GL_CURRENT_RASTER_COLOR", INT2NUM(GL_CURRENT_RASTER_COLOR));
    rb_define_const(module, "GL_CURRENT_RASTER_DISTANCE", INT2NUM(GL_CURRENT_RASTER_DISTANCE));
    rb_define_const(module, "GL_CURRENT_RASTER_INDEX", INT2NUM(GL_CURRENT_RASTER_INDEX));
    rb_define_const(module, "GL_CURRENT_RASTER_POSITION", INT2NUM(GL_CURRENT_RASTER_POSITION));
    rb_define_const(module, "GL_CURRENT_RASTER_TEXTURE_COORDS", INT2NUM(GL_CURRENT_RASTER_TEXTURE_COORDS));
    rb_define_const(module, "GL_CURRENT_RASTER_POSITION_VALID", INT2NUM(GL_CURRENT_RASTER_POSITION_VALID));
    rb_define_const(module, "GL_CURRENT_TEXTURE_COORDS", INT2NUM(GL_CURRENT_TEXTURE_COORDS));
    rb_define_const(module, "GL_INDEX_CLEAR_VALUE", INT2NUM(GL_INDEX_CLEAR_VALUE));
    rb_define_const(module, "GL_INDEX_MODE", INT2NUM(GL_INDEX_MODE));
    rb_define_const(module, "GL_INDEX_WRITEMASK", INT2NUM(GL_INDEX_WRITEMASK));
    rb_define_const(module, "GL_MODELVIEW_MATRIX", INT2NUM(GL_MODELVIEW_MATRIX));
    rb_define_const(module, "GL_MODELVIEW_STACK_DEPTH", INT2NUM(GL_MODELVIEW_STACK_DEPTH));
    rb_define_const(module, "GL_NAME_STACK_DEPTH", INT2NUM(GL_NAME_STACK_DEPTH));
    rb_define_const(module, "GL_PROJECTION_MATRIX", INT2NUM(GL_PROJECTION_MATRIX));
    rb_define_const(module, "GL_PROJECTION_STACK_DEPTH", INT2NUM(GL_PROJECTION_STACK_DEPTH));
    rb_define_const(module, "GL_RENDER_MODE", INT2NUM(GL_RENDER_MODE));
    rb_define_const(module, "GL_RGBA_MODE", INT2NUM(GL_RGBA_MODE));
    rb_define_const(module, "GL_TEXTURE_MATRIX", INT2NUM(GL_TEXTURE_MATRIX));
    rb_define_const(module, "GL_TEXTURE_STACK_DEPTH", INT2NUM(GL_TEXTURE_STACK_DEPTH));
    rb_define_const(module, "GL_VIEWPORT", INT2NUM(GL_VIEWPORT));
    rb_define_const(module, "GL_AUTO_NORMAL", INT2NUM(GL_AUTO_NORMAL));
    rb_define_const(module, "GL_MAP1_COLOR_4", INT2NUM(GL_MAP1_COLOR_4));
    rb_define_const(module, "GL_MAP1_GRID_DOMAIN", INT2NUM(GL_MAP1_GRID_DOMAIN));
    rb_define_const(module, "GL_MAP1_GRID_SEGMENTS", INT2NUM(GL_MAP1_GRID_SEGMENTS));
    rb_define_const(module, "GL_MAP1_INDEX", INT2NUM(GL_MAP1_INDEX));
    rb_define_const(module, "GL_MAP1_NORMAL", INT2NUM(GL_MAP1_NORMAL));
    rb_define_const(module, "GL_MAP1_TEXTURE_COORD_1", INT2NUM(GL_MAP1_TEXTURE_COORD_1));
    rb_define_const(module, "GL_MAP1_TEXTURE_COORD_2", INT2NUM(GL_MAP1_TEXTURE_COORD_2));
    rb_define_const(module, "GL_MAP1_TEXTURE_COORD_3", INT2NUM(GL_MAP1_TEXTURE_COORD_3));
    rb_define_const(module, "GL_MAP1_TEXTURE_COORD_4", INT2NUM(GL_MAP1_TEXTURE_COORD_4));
    rb_define_const(module, "GL_MAP1_VERTEX_3", INT2NUM(GL_MAP1_VERTEX_3));
    rb_define_const(module, "GL_MAP1_VERTEX_4", INT2NUM(GL_MAP1_VERTEX_4));
    rb_define_const(module, "GL_MAP2_COLOR_4", INT2NUM(GL_MAP2_COLOR_4));
    rb_define_const(module, "GL_MAP2_GRID_DOMAIN", INT2NUM(GL_MAP2_GRID_DOMAIN));
    rb_define_const(module, "GL_MAP2_GRID_SEGMENTS", INT2NUM(GL_MAP2_GRID_SEGMENTS));
    rb_define_const(module, "GL_MAP2_INDEX", INT2NUM(GL_MAP2_INDEX));
    rb_define_const(module, "GL_MAP2_NORMAL", INT2NUM(GL_MAP2_NORMAL));
    rb_define_const(module, "GL_MAP2_TEXTURE_COORD_1", INT2NUM(GL_MAP2_TEXTURE_COORD_1));
    rb_define_const(module, "GL_MAP2_TEXTURE_COORD_2", INT2NUM(GL_MAP2_TEXTURE_COORD_2));
    rb_define_const(module, "GL_MAP2_TEXTURE_COORD_3", INT2NUM(GL_MAP2_TEXTURE_COORD_3));
    rb_define_const(module, "GL_MAP2_TEXTURE_COORD_4", INT2NUM(GL_MAP2_TEXTURE_COORD_4));
    rb_define_const(module, "GL_MAP2_VERTEX_3", INT2NUM(GL_MAP2_VERTEX_3));
    rb_define_const(module, "GL_MAP2_VERTEX_4", INT2NUM(GL_MAP2_VERTEX_4));
    rb_define_const(module, "GL_COEFF", INT2NUM(GL_COEFF));
    rb_define_const(module, "GL_DOMAIN", INT2NUM(GL_DOMAIN));
    rb_define_const(module, "GL_ORDER", INT2NUM(GL_ORDER));
    rb_define_const(module, "GL_FOG_HINT", INT2NUM(GL_FOG_HINT));
    rb_define_const(module, "GL_LINE_SMOOTH_HINT", INT2NUM(GL_LINE_SMOOTH_HINT));
    rb_define_const(module, "GL_PERSPECTIVE_CORRECTION_HINT", INT2NUM(GL_PERSPECTIVE_CORRECTION_HINT));
    rb_define_const(module, "GL_POINT_SMOOTH_HINT", INT2NUM(GL_POINT_SMOOTH_HINT));
    rb_define_const(module, "GL_POLYGON_SMOOTH_HINT", INT2NUM(GL_POLYGON_SMOOTH_HINT));
    rb_define_const(module, "GL_DONT_CARE", INT2NUM(GL_DONT_CARE));
    rb_define_const(module, "GL_FASTEST", INT2NUM(GL_FASTEST));
    rb_define_const(module, "GL_NICEST", INT2NUM(GL_NICEST));
    rb_define_const(module, "GL_SCISSOR_TEST", INT2NUM(GL_SCISSOR_TEST));
    rb_define_const(module, "GL_SCISSOR_BOX", INT2NUM(GL_SCISSOR_BOX));
    rb_define_const(module, "GL_MAP_COLOR", INT2NUM(GL_MAP_COLOR));
    rb_define_const(module, "GL_MAP_STENCIL", INT2NUM(GL_MAP_STENCIL));
    rb_define_const(module, "GL_INDEX_SHIFT", INT2NUM(GL_INDEX_SHIFT));
    rb_define_const(module, "GL_INDEX_OFFSET", INT2NUM(GL_INDEX_OFFSET));
    rb_define_const(module, "GL_RED_SCALE", INT2NUM(GL_RED_SCALE));
    rb_define_const(module, "GL_RED_BIAS", INT2NUM(GL_RED_BIAS));
    rb_define_const(module, "GL_GREEN_SCALE", INT2NUM(GL_GREEN_SCALE));
    rb_define_const(module, "GL_GREEN_BIAS", INT2NUM(GL_GREEN_BIAS));
    rb_define_const(module, "GL_BLUE_SCALE", INT2NUM(GL_BLUE_SCALE));
    rb_define_const(module, "GL_BLUE_BIAS", INT2NUM(GL_BLUE_BIAS));
    rb_define_const(module, "GL_ALPHA_SCALE", INT2NUM(GL_ALPHA_SCALE));
    rb_define_const(module, "GL_ALPHA_BIAS", INT2NUM(GL_ALPHA_BIAS));
    rb_define_const(module, "GL_DEPTH_SCALE", INT2NUM(GL_DEPTH_SCALE));
    rb_define_const(module, "GL_DEPTH_BIAS", INT2NUM(GL_DEPTH_BIAS));
    rb_define_const(module, "GL_PIXEL_MAP_S_TO_S_SIZE", INT2NUM(GL_PIXEL_MAP_S_TO_S_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_I_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_I_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_R_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_R_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_G_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_G_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_B_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_B_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_A_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_A_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_R_TO_R_SIZE", INT2NUM(GL_PIXEL_MAP_R_TO_R_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_G_TO_G_SIZE", INT2NUM(GL_PIXEL_MAP_G_TO_G_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_B_TO_B_SIZE", INT2NUM(GL_PIXEL_MAP_B_TO_B_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_A_TO_A_SIZE", INT2NUM(GL_PIXEL_MAP_A_TO_A_SIZE));
    rb_define_const(module, "GL_PIXEL_MAP_S_TO_S", INT2NUM(GL_PIXEL_MAP_S_TO_S));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_I", INT2NUM(GL_PIXEL_MAP_I_TO_I));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_R", INT2NUM(GL_PIXEL_MAP_I_TO_R));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_G", INT2NUM(GL_PIXEL_MAP_I_TO_G));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_B", INT2NUM(GL_PIXEL_MAP_I_TO_B));
    rb_define_const(module, "GL_PIXEL_MAP_I_TO_A", INT2NUM(GL_PIXEL_MAP_I_TO_A));
    rb_define_const(module, "GL_PIXEL_MAP_R_TO_R", INT2NUM(GL_PIXEL_MAP_R_TO_R));
    rb_define_const(module, "GL_PIXEL_MAP_G_TO_G", INT2NUM(GL_PIXEL_MAP_G_TO_G));
    rb_define_const(module, "GL_PIXEL_MAP_B_TO_B", INT2NUM(GL_PIXEL_MAP_B_TO_B));
    rb_define_const(module, "GL_PIXEL_MAP_A_TO_A", INT2NUM(GL_PIXEL_MAP_A_TO_A));
    rb_define_const(module, "GL_PACK_ALIGNMENT", INT2NUM(GL_PACK_ALIGNMENT));
    rb_define_const(module, "GL_PACK_LSB_FIRST", INT2NUM(GL_PACK_LSB_FIRST));
    rb_define_const(module, "GL_PACK_ROW_LENGTH", INT2NUM(GL_PACK_ROW_LENGTH));
    rb_define_const(module, "GL_PACK_SKIP_PIXELS", INT2NUM(GL_PACK_SKIP_PIXELS));
    rb_define_const(module, "GL_PACK_SKIP_ROWS", INT2NUM(GL_PACK_SKIP_ROWS));
    rb_define_const(module, "GL_PACK_SWAP_BYTES", INT2NUM(GL_PACK_SWAP_BYTES));
    rb_define_const(module, "GL_UNPACK_ALIGNMENT", INT2NUM(GL_UNPACK_ALIGNMENT));
    rb_define_const(module, "GL_UNPACK_LSB_FIRST", INT2NUM(GL_UNPACK_LSB_FIRST));
    rb_define_const(module, "GL_UNPACK_ROW_LENGTH", INT2NUM(GL_UNPACK_ROW_LENGTH));
    rb_define_const(module, "GL_UNPACK_SKIP_PIXELS", INT2NUM(GL_UNPACK_SKIP_PIXELS));
    rb_define_const(module, "GL_UNPACK_SKIP_ROWS", INT2NUM(GL_UNPACK_SKIP_ROWS));
    rb_define_const(module, "GL_UNPACK_SWAP_BYTES", INT2NUM(GL_UNPACK_SWAP_BYTES));
    rb_define_const(module, "GL_ZOOM_X", INT2NUM(GL_ZOOM_X));
    rb_define_const(module, "GL_ZOOM_Y", INT2NUM(GL_ZOOM_Y));
    rb_define_const(module, "GL_TEXTURE_ENV", INT2NUM(GL_TEXTURE_ENV));
    rb_define_const(module, "GL_TEXTURE_ENV_MODE", INT2NUM(GL_TEXTURE_ENV_MODE));
    rb_define_const(module, "GL_TEXTURE_1D", INT2NUM(GL_TEXTURE_1D));
    rb_define_const(module, "GL_TEXTURE_2D", INT2NUM(GL_TEXTURE_2D));
    rb_define_const(module, "GL_TEXTURE_WRAP_S", INT2NUM(GL_TEXTURE_WRAP_S));
    rb_define_const(module, "GL_TEXTURE_WRAP_T", INT2NUM(GL_TEXTURE_WRAP_T));
    rb_define_const(module, "GL_TEXTURE_MAG_FILTER", INT2NUM(GL_TEXTURE_MAG_FILTER));
    rb_define_const(module, "GL_TEXTURE_MIN_FILTER", INT2NUM(GL_TEXTURE_MIN_FILTER));
    rb_define_const(module, "GL_TEXTURE_ENV_COLOR", INT2NUM(GL_TEXTURE_ENV_COLOR));
    rb_define_const(module, "GL_TEXTURE_GEN_S", INT2NUM(GL_TEXTURE_GEN_S));
    rb_define_const(module, "GL_TEXTURE_GEN_T", INT2NUM(GL_TEXTURE_GEN_T));
    rb_define_const(module, "GL_TEXTURE_GEN_MODE", INT2NUM(GL_TEXTURE_GEN_MODE));
    rb_define_const(module, "GL_TEXTURE_BORDER_COLOR", INT2NUM(GL_TEXTURE_BORDER_COLOR));
    rb_define_const(module, "GL_TEXTURE_WIDTH", INT2NUM(GL_TEXTURE_WIDTH));
    rb_define_const(module, "GL_TEXTURE_HEIGHT", INT2NUM(GL_TEXTURE_HEIGHT));
    rb_define_const(module, "GL_TEXTURE_BORDER", INT2NUM(GL_TEXTURE_BORDER));
    rb_define_const(module, "GL_TEXTURE_COMPONENTS", INT2NUM(GL_TEXTURE_COMPONENTS));
    rb_define_const(module, "GL_TEXTURE_RED_SIZE", INT2NUM(GL_TEXTURE_RED_SIZE));
    rb_define_const(module, "GL_TEXTURE_GREEN_SIZE", INT2NUM(GL_TEXTURE_GREEN_SIZE));
    rb_define_const(module, "GL_TEXTURE_BLUE_SIZE", INT2NUM(GL_TEXTURE_BLUE_SIZE));
    rb_define_const(module, "GL_TEXTURE_ALPHA_SIZE", INT2NUM(GL_TEXTURE_ALPHA_SIZE));
    rb_define_const(module, "GL_TEXTURE_LUMINANCE_SIZE", INT2NUM(GL_TEXTURE_LUMINANCE_SIZE));
    rb_define_const(module, "GL_TEXTURE_INTENSITY_SIZE", INT2NUM(GL_TEXTURE_INTENSITY_SIZE));
    rb_define_const(module, "GL_NEAREST_MIPMAP_NEAREST", INT2NUM(GL_NEAREST_MIPMAP_NEAREST));
    rb_define_const(module, "GL_NEAREST_MIPMAP_LINEAR", INT2NUM(GL_NEAREST_MIPMAP_LINEAR));
    rb_define_const(module, "GL_LINEAR_MIPMAP_NEAREST", INT2NUM(GL_LINEAR_MIPMAP_NEAREST));
    rb_define_const(module, "GL_LINEAR_MIPMAP_LINEAR", INT2NUM(GL_LINEAR_MIPMAP_LINEAR));
    rb_define_const(module, "GL_OBJECT_LINEAR", INT2NUM(GL_OBJECT_LINEAR));
    rb_define_const(module, "GL_OBJECT_PLANE", INT2NUM(GL_OBJECT_PLANE));
    rb_define_const(module, "GL_EYE_LINEAR", INT2NUM(GL_EYE_LINEAR));
    rb_define_const(module, "GL_EYE_PLANE", INT2NUM(GL_EYE_PLANE));
    rb_define_const(module, "GL_SPHERE_MAP", INT2NUM(GL_SPHERE_MAP));
    rb_define_const(module, "GL_DECAL", INT2NUM(GL_DECAL));
    rb_define_const(module, "GL_MODULATE", INT2NUM(GL_MODULATE));
    rb_define_const(module, "GL_NEAREST", INT2NUM(GL_NEAREST));
    rb_define_const(module, "GL_REPEAT", INT2NUM(GL_REPEAT));
    rb_define_const(module, "GL_CLAMP", INT2NUM(GL_CLAMP));
    rb_define_const(module, "GL_S", INT2NUM(GL_S));
    rb_define_const(module, "GL_T", INT2NUM(GL_T));
    rb_define_const(module, "GL_R", INT2NUM(GL_R));
    rb_define_const(module, "GL_Q", INT2NUM(GL_Q));
    rb_define_const(module, "GL_TEXTURE_GEN_R", INT2NUM(GL_TEXTURE_GEN_R));
    rb_define_const(module, "GL_TEXTURE_GEN_Q", INT2NUM(GL_TEXTURE_GEN_Q));
#if defined(GL_VERSION_1_1)
    rb_define_const(module, "GL_PROXY_TEXTURE_1D", INT2NUM(GL_PROXY_TEXTURE_1D));
    rb_define_const(module, "GL_PROXY_TEXTURE_2D", INT2NUM(GL_PROXY_TEXTURE_2D));
    rb_define_const(module, "GL_TEXTURE_PRIORITY", INT2NUM(GL_TEXTURE_PRIORITY));
    rb_define_const(module, "GL_TEXTURE_RESIDENT", INT2NUM(GL_TEXTURE_RESIDENT));
    rb_define_const(module, "GL_TEXTURE_BINDING_1D", INT2NUM(GL_TEXTURE_BINDING_1D));
    rb_define_const(module, "GL_TEXTURE_BINDING_2D", INT2NUM(GL_TEXTURE_BINDING_2D));
    rb_define_const(module, "GL_TEXTURE_INTERNAL_FORMAT", INT2NUM(GL_TEXTURE_INTERNAL_FORMAT));
#endif /* GL_VERSION_1_1 */

#if defined(GL_VERSION_1_2)
    rb_define_const(module, "GL_PACK_SKIP_IMAGES", INT2NUM(GL_PACK_SKIP_IMAGES));
    rb_define_const(module, "GL_PACK_IMAGE_HEIGHT", INT2NUM(GL_PACK_IMAGE_HEIGHT));
    rb_define_const(module, "GL_UNPACK_SKIP_IMAGES", INT2NUM(GL_UNPACK_SKIP_IMAGES));
    rb_define_const(module, "GL_UNPACK_IMAGE_HEIGHT", INT2NUM(GL_UNPACK_IMAGE_HEIGHT));
    rb_define_const(module, "GL_TEXTURE_3D", INT2NUM(GL_TEXTURE_3D));
    rb_define_const(module, "GL_PROXY_TEXTURE_3D", INT2NUM(GL_PROXY_TEXTURE_3D));
    rb_define_const(module, "GL_TEXTURE_DEPTH", INT2NUM(GL_TEXTURE_DEPTH));
    rb_define_const(module, "GL_TEXTURE_WRAP_R", INT2NUM(GL_TEXTURE_WRAP_R));
    rb_define_const(module, "GL_MAX_3D_TEXTURE_SIZE", INT2NUM(GL_MAX_3D_TEXTURE_SIZE));
    rb_define_const(module, "GL_TEXTURE_BINDING_3D", INT2NUM(GL_TEXTURE_BINDING_3D));
#endif /* GL_VERSION_1_2 */

    rb_define_const(module, "GL_ALPHA4", INT2NUM(GL_ALPHA4));
    rb_define_const(module, "GL_ALPHA8", INT2NUM(GL_ALPHA8));
    rb_define_const(module, "GL_ALPHA12", INT2NUM(GL_ALPHA12));
    rb_define_const(module, "GL_ALPHA16", INT2NUM(GL_ALPHA16));
    rb_define_const(module, "GL_LUMINANCE4", INT2NUM(GL_LUMINANCE4));
    rb_define_const(module, "GL_LUMINANCE8", INT2NUM(GL_LUMINANCE8));
    rb_define_const(module, "GL_LUMINANCE12", INT2NUM(GL_LUMINANCE12));
    rb_define_const(module, "GL_LUMINANCE16", INT2NUM(GL_LUMINANCE16));
    rb_define_const(module, "GL_LUMINANCE4_ALPHA4", INT2NUM(GL_LUMINANCE4_ALPHA4));
    rb_define_const(module, "GL_LUMINANCE6_ALPHA2", INT2NUM(GL_LUMINANCE6_ALPHA2));
    rb_define_const(module, "GL_LUMINANCE8_ALPHA8", INT2NUM(GL_LUMINANCE8_ALPHA8));
    rb_define_const(module, "GL_LUMINANCE12_ALPHA4", INT2NUM(GL_LUMINANCE12_ALPHA4));
    rb_define_const(module, "GL_LUMINANCE12_ALPHA12", INT2NUM(GL_LUMINANCE12_ALPHA12));
    rb_define_const(module, "GL_LUMINANCE16_ALPHA16", INT2NUM(GL_LUMINANCE16_ALPHA16));
    rb_define_const(module, "GL_INTENSITY", INT2NUM(GL_INTENSITY));
    rb_define_const(module, "GL_INTENSITY4", INT2NUM(GL_INTENSITY4));
    rb_define_const(module, "GL_INTENSITY8", INT2NUM(GL_INTENSITY8));
    rb_define_const(module, "GL_INTENSITY12", INT2NUM(GL_INTENSITY12));
    rb_define_const(module, "GL_INTENSITY16", INT2NUM(GL_INTENSITY16));
    rb_define_const(module, "GL_R3_G3_B2", INT2NUM(GL_R3_G3_B2));
    rb_define_const(module, "GL_RGB4", INT2NUM(GL_RGB4));
    rb_define_const(module, "GL_RGB5", INT2NUM(GL_RGB5));
    rb_define_const(module, "GL_RGB8", INT2NUM(GL_RGB8));
    rb_define_const(module, "GL_RGB10", INT2NUM(GL_RGB10));
    rb_define_const(module, "GL_RGB12", INT2NUM(GL_RGB12));
    rb_define_const(module, "GL_RGB16", INT2NUM(GL_RGB16));
    rb_define_const(module, "GL_RGBA2", INT2NUM(GL_RGBA2));
    rb_define_const(module, "GL_RGBA4", INT2NUM(GL_RGBA4));
    rb_define_const(module, "GL_RGB5_A1", INT2NUM(GL_RGB5_A1));
    rb_define_const(module, "GL_RGBA8", INT2NUM(GL_RGBA8));
    rb_define_const(module, "GL_RGB10_A2", INT2NUM(GL_RGB10_A2));
    rb_define_const(module, "GL_RGBA12", INT2NUM(GL_RGBA12));
    rb_define_const(module, "GL_RGBA16", INT2NUM(GL_RGBA16));
    rb_define_const(module, "GL_VENDOR", INT2NUM(GL_VENDOR));
    rb_define_const(module, "GL_RENDERER", INT2NUM(GL_RENDERER));
    rb_define_const(module, "GL_VERSION", INT2NUM(GL_VERSION));
    rb_define_const(module, "GL_EXTENSIONS", INT2NUM(GL_EXTENSIONS));
    rb_define_const(module, "GL_INVALID_VALUE", INT2NUM(GL_INVALID_VALUE));
    rb_define_const(module, "GL_INVALID_ENUM", INT2NUM(GL_INVALID_ENUM));
    rb_define_const(module, "GL_INVALID_OPERATION", INT2NUM(GL_INVALID_OPERATION));
    rb_define_const(module, "GL_STACK_OVERFLOW", INT2NUM(GL_STACK_OVERFLOW));
    rb_define_const(module, "GL_STACK_UNDERFLOW", INT2NUM(GL_STACK_UNDERFLOW));
    rb_define_const(module, "GL_OUT_OF_MEMORY", INT2NUM(GL_OUT_OF_MEMORY));
#if 0
#if defined(CONSTANT_COLOR_EXT)
    rb_define_const(module, "GL_CONSTANT_COLOR_EXT", INT2NUM(GL_CONSTANT_COLOR_EXT));
#endif
#if defined(ONE_MINUS_CONSTANT_COLOR_EXT)
    rb_define_const(module, "GL_ONE_MINUS_CONSTANT_COLOR_EXT", INT2NUM(GL_ONE_MINUS_CONSTANT_COLOR_EXT));
#endif
#if defined(CONSTANT_ALPHA_EXT)
    rb_define_const(module, "GL_CONSTANT_ALPHA_EXT", INT2NUM(GL_CONSTANT_ALPHA_EXT));
#endif
#if defined(ONE_MINUS_CONSTANT_ALPHA_EXT)
    rb_define_const(module, "GL_ONE_MINUS_CONSTANT_ALPHA_EXT", INT2NUM(GL_ONE_MINUS_CONSTANT_ALPHA_EXT));
#endif
#if defined(BLEND_EQUATION_EXT)
    rb_define_const(module, "GL_BLEND_EQUATION_EXT", INT2NUM(GL_BLEND_EQUATION_EXT));
#endif
#if defined(MIN_EXT)
    rb_define_const(module, "GL_MIN_EXT", INT2NUM(GL_MIN_EXT));
#endif
#if defined(MAX_EXT)
    rb_define_const(module, "GL_MAX_EXT", INT2NUM(GL_MAX_EXT));
#endif
#if defined(FUNC_ADD_EXT)
    rb_define_const(module, "GL_FUNC_ADD_EXT", INT2NUM(GL_FUNC_ADD_EXT));
#endif
#if defined(FUNC_SUBTRACT_EXT)
    rb_define_const(module, "GL_FUNC_SUBTRACT_EXT", INT2NUM(GL_FUNC_SUBTRACT_EXT));
#endif
#if defined(FUNC_REVERSE_SUBTRACT_EXT)
    rb_define_const(module, "GL_FUNC_REVERSE_SUBTRACT_EXT", INT2NUM(GL_FUNC_REVERSE_SUBTRACT_EXT));
#endif
#if defined(BLEND_COLOR_EXT)
    rb_define_const(module, "GL_BLEND_COLOR_EXT", INT2NUM(GL_BLEND_COLOR_EXT));
#endif
#if defined(POLYGON_OFFSET_EXT)
    rb_define_const(module, "GL_POLYGON_OFFSET_EXT", INT2NUM(GL_POLYGON_OFFSET_EXT));
#endif
#if defined(POLYGON_OFFSET_FACTOR_EXT)
    rb_define_const(module, "GL_POLYGON_OFFSET_FACTOR_EXT", INT2NUM(GL_POLYGON_OFFSET_FACTOR_EXT));
#endif
#if defined(POLYGON_OFFSET_BIAS_EXT)
    rb_define_const(module, "GL_POLYGON_OFFSET_BIAS_EXT", INT2NUM(GL_POLYGON_OFFSET_BIAS_EXT));
#endif
#if defined(VERTEX_ARRAY_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_EXT", INT2NUM(GL_VERTEX_ARRAY_EXT));
#endif
#if defined(NORMAL_ARRAY_EXT)
    rb_define_const(module, "GL_NORMAL_ARRAY_EXT", INT2NUM(GL_NORMAL_ARRAY_EXT));
#endif
#if defined(COLOR_ARRAY_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_EXT", INT2NUM(GL_COLOR_ARRAY_EXT));
#endif
#if defined(INDEX_ARRAY_EXT)
    rb_define_const(module, "GL_INDEX_ARRAY_EXT", INT2NUM(GL_INDEX_ARRAY_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_EXT)
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_EXT)
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_EXT));
#endif
#if defined(VERTEX_ARRAY_SIZE_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_SIZE_EXT", INT2NUM(GL_VERTEX_ARRAY_SIZE_EXT));
#endif
#if defined(VERTEX_ARRAY_TYPE_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_TYPE_EXT", INT2NUM(GL_VERTEX_ARRAY_TYPE_EXT));
#endif
#if defined(VERTEX_ARRAY_STRIDE_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_STRIDE_EXT", INT2NUM(GL_VERTEX_ARRAY_STRIDE_EXT));
#endif
#if defined(VERTEX_ARRAY_COUNT_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_COUNT_EXT", INT2NUM(GL_VERTEX_ARRAY_COUNT_EXT));
#endif
#if defined(NORMAL_ARRAY_TYPE_EXT)
    rb_define_const(module, "GL_NORMAL_ARRAY_TYPE_EXT", INT2NUM(GL_NORMAL_ARRAY_TYPE_EXT));
#endif
#if defined(NORMAL_ARRAY_STRIDE_EXT)
    rb_define_const(module, "GL_NORMAL_ARRAY_STRIDE_EXT", INT2NUM(GL_NORMAL_ARRAY_STRIDE_EXT));
#endif
#if defined(NORMAL_ARRAY_COUNT_EXT)
    rb_define_const(module, "GL_NORMAL_ARRAY_COUNT_EXT", INT2NUM(GL_NORMAL_ARRAY_COUNT_EXT));
#endif
#if defined(COLOR_ARRAY_SIZE_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_SIZE_EXT", INT2NUM(GL_COLOR_ARRAY_SIZE_EXT));
#endif
#if defined(COLOR_ARRAY_TYPE_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_TYPE_EXT", INT2NUM(GL_COLOR_ARRAY_TYPE_EXT));
#endif
#if defined(COLOR_ARRAY_STRIDE_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_STRIDE_EXT", INT2NUM(GL_COLOR_ARRAY_STRIDE_EXT));
#endif
#if defined(COLOR_ARRAY_COUNT_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_COUNT_EXT", INT2NUM(GL_COLOR_ARRAY_COUNT_EXT));
#endif
#if defined(INDEX_ARRAY_TYPE_EXT)
    rb_define_const(module, "GL_INDEX_ARRAY_TYPE_EXT", INT2NUM(GL_INDEX_ARRAY_TYPE_EXT));
#endif
#if defined(INDEX_ARRAY_STRIDE_EXT)
    rb_define_const(module, "GL_INDEX_ARRAY_STRIDE_EXT", INT2NUM(GL_INDEX_ARRAY_STRIDE_EXT));
#endif
#if defined(INDEX_ARRAY_COUNT_EXT)
    rb_define_const(module, "GL_INDEX_ARRAY_COUNT_EXT", INT2NUM(GL_INDEX_ARRAY_COUNT_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_SIZE_EXT)
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_SIZE_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_SIZE_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_TYPE_EXT)
    rb_define_const(module, "GL_TEXTURE_COORD_ARRAY_TYPE_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_TYPE_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_STRIDE_EXT)
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_STRIDE_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_STRIDE_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_COUNT_EXT)
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_COUNT_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_COUNT_EXT));
#endif
#if defined(VERTEX_ARRAY_POINTER_EXT)
    rb_define_const(module, "GL_VERTEX_ARRAY_POINTER_EXT", INT2NUM(GL_VERTEX_ARRAY_POINTER_EXT));
#endif
#if defined(NORMAL_ARRAY_POINTER_EXT)
    rb_define_const(module, "GL_NORMAL_ARRAY_POINTER_EXT", INT2NUM(GL_NORMAL_ARRAY_POINTER_EXT));
#endif
#if defined(COLOR_ARRAY_POINTER_EXT)
    rb_define_const(module, "GL_COLOR_ARRAY_POINTER_EXT", INT2NUM(GL_COLOR_ARRAY_POINTER_EXT));
#endif
#if defined(INDEX_ARRAY_POINTER_EXT)
    rb_define_const(module, "GL_INDEX_ARRAY_POINTER_EXT", INT2NUM(GL_INDEX_ARRAY_POINTER_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_POINTER_EXT)
    rb_define_const(module, "GL_EDGE_FLAG_ARRAY_POINTER_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_POINTER_EXT));
#endif
#if defined(TEXTURE_PRIORITY_EXT)
    rb_define_const(module, "GL_TEXTURE_PRIORITY_EXT", INT2NUM(GL_TEXTURE_PRIORITY_EXT));
#endif
#if defined(TEXTURE_RESIDENT_EXT)
    rb_define_const(module, "GL_TEXTURE_RESIDENT_EXT", INT2NUM(GL_TEXTURE_RESIDENT_EXT));
#endif
#if defined(TEXTURE_1D_BINDING_EXT)
    rb_define_const(module, "GL_TEXTURE_1D_BINDING_EXT", INT2NUM(GL_TEXTURE_1D_BINDING_EXT));
#endif
#if defined(TEXTURE_2D_BINDING_EXT)
    rb_define_const(module, "GL_TEXTURE_2D_BINDING_EXT", INT2NUM(GL_TEXTURE_2D_BINDING_EXT));
#endif
#if defined(PACK_SKIP_IMAGES_EXT)
    rb_define_const(module, "GL_PACK_SKIP_IMAGES_EXT", INT2NUM(GL_PACK_SKIP_IMAGES_EXT));
#endif
#if defined(PACK_IMAGE_HEIGHT_EXT)
    rb_define_const(module, "GL_PACK_IMAGE_HEIGHT_EXT", INT2NUM(GL_PACK_IMAGE_HEIGHT_EXT));
#endif
#if defined(UNPACK_SKIP_IMAGES_EXT)
    rb_define_const(module, "GL_UNPACK_SKIP_IMAGES_EXT", INT2NUM(GL_UNPACK_SKIP_IMAGES_EXT));
#endif
#if defined(UNPACK_IMAGE_HEIGHT_EXT)
    rb_define_const(module, "GL_UNPACK_IMAGE_HEIGHT_EXT", INT2NUM(GL_UNPACK_IMAGE_HEIGHT_EXT));
#endif
#if defined(TEXTURE_3D_EXT)
    rb_define_const(module, "GL_TEXTURE_3D_EXT", INT2NUM(GL_TEXTURE_3D_EXT));
#endif
#if defined(PROXY_TEXTURE_3D_EXT)
    rb_define_const(module, "GL_PROXY_TEXTURE_3D_EXT", INT2NUM(GL_PROXY_TEXTURE_3D_EXT));
#endif
#if defined(TEXTURE_DEPTH_EXT)
    rb_define_const(module, "GL_TEXTURE_DEPTH_EXT", INT2NUM(GL_TEXTURE_DEPTH_EXT));
#endif
#if defined(TEXTURE_WRAP_R_EXT)
    rb_define_const(module, "GL_TEXTURE_WRAP_R_EXT", INT2NUM(GL_TEXTURE_WRAP_R_EXT));
#endif
#if defined(MAX_3D_TEXTURE_SIZE_EXT)
    rb_define_const(module, "GL_MAX_3D_TEXTURE_SIZE_EXT", INT2NUM(GL_MAX_3D_TEXTURE_SIZE_EXT));
#endif
#if defined(TEXTURE_3D_BINDING_EXT)
    rb_define_const(module, "GL_TEXTURE_3D_BINDING_EXT", INT2NUM(GL_TEXTURE_3D_BINDING_EXT));
#endif
#endif

#if defined(GL_VERSION_1_2)
    rb_define_const(module, "GL_RESCALE_NORMAL", INT2NUM(GL_RESCALE_NORMAL));
    rb_define_const(module, "GL_CLAMP_TO_EDGE", INT2NUM(GL_CLAMP_TO_EDGE));
    rb_define_const(module, "GL_MAX_ELEMENTS_VERTICES", INT2NUM(GL_MAX_ELEMENTS_VERTICES));
    rb_define_const(module, "GL_MAX_ELEMENTS_INDICES", INT2NUM(GL_MAX_ELEMENTS_INDICES));
    rb_define_const(module, "GL_BGR", INT2NUM(GL_BGR));
    rb_define_const(module, "GL_BGRA", INT2NUM(GL_BGRA));
    rb_define_const(module, "GL_UNSIGNED_BYTE_3_3_2", INT2NUM(GL_UNSIGNED_BYTE_3_3_2));
    rb_define_const(module, "GL_UNSIGNED_BYTE_2_3_3_REV", INT2NUM(GL_UNSIGNED_BYTE_2_3_3_REV));
    rb_define_const(module, "GL_UNSIGNED_SHORT_5_6_5", INT2NUM(GL_UNSIGNED_SHORT_5_6_5));
    rb_define_const(module, "GL_UNSIGNED_SHORT_5_6_5_REV", INT2NUM(GL_UNSIGNED_SHORT_5_6_5_REV));
    rb_define_const(module, "GL_UNSIGNED_SHORT_4_4_4_4", INT2NUM(GL_UNSIGNED_SHORT_4_4_4_4));
    rb_define_const(module, "GL_UNSIGNED_SHORT_4_4_4_4_REV", INT2NUM(GL_UNSIGNED_SHORT_4_4_4_4_REV));
    rb_define_const(module, "GL_UNSIGNED_SHORT_5_5_5_1", INT2NUM(GL_UNSIGNED_SHORT_5_5_5_1));
    rb_define_const(module, "GL_UNSIGNED_SHORT_1_5_5_5_REV", INT2NUM(GL_UNSIGNED_SHORT_1_5_5_5_REV));
    rb_define_const(module, "GL_UNSIGNED_INT_8_8_8_8", INT2NUM(GL_UNSIGNED_INT_8_8_8_8));
    rb_define_const(module, "GL_UNSIGNED_INT_8_8_8_8_REV", INT2NUM(GL_UNSIGNED_INT_8_8_8_8_REV));
    rb_define_const(module, "GL_UNSIGNED_INT_10_10_10_2", INT2NUM(GL_UNSIGNED_INT_10_10_10_2));
    rb_define_const(module, "GL_UNSIGNED_INT_2_10_10_10_REV", INT2NUM(GL_UNSIGNED_INT_2_10_10_10_REV));
    rb_define_const(module, "GL_LIGHT_MODEL_COLOR_CONTROL", INT2NUM(GL_LIGHT_MODEL_COLOR_CONTROL));
    rb_define_const(module, "GL_SINGLE_COLOR", INT2NUM(GL_SINGLE_COLOR));
    rb_define_const(module, "GL_SEPARATE_SPECULAR_COLOR", INT2NUM(GL_SEPARATE_SPECULAR_COLOR));
    rb_define_const(module, "GL_TEXTURE_MIN_LOD", INT2NUM(GL_TEXTURE_MIN_LOD));
    rb_define_const(module, "GL_TEXTURE_MAX_LOD", INT2NUM(GL_TEXTURE_MAX_LOD));
    rb_define_const(module, "GL_TEXTURE_BASE_LEVEL", INT2NUM(GL_TEXTURE_BASE_LEVEL));
    rb_define_const(module, "GL_TEXTURE_MAX_LEVEL", INT2NUM(GL_TEXTURE_MAX_LEVEL));
#endif /* GL_VERSION_1_2 */

    rb_define_const(module, "GL_CURRENT_BIT", INT2NUM(GL_CURRENT_BIT));
    rb_define_const(module, "GL_POINT_BIT", INT2NUM(GL_POINT_BIT));
    rb_define_const(module, "GL_LINE_BIT", INT2NUM(GL_LINE_BIT));
    rb_define_const(module, "GL_POLYGON_BIT", INT2NUM(GL_POLYGON_BIT));
    rb_define_const(module, "GL_POLYGON_STIPPLE_BIT", INT2NUM(GL_POLYGON_STIPPLE_BIT));
    rb_define_const(module, "GL_PIXEL_MODE_BIT", INT2NUM(GL_PIXEL_MODE_BIT));
    rb_define_const(module, "GL_LIGHTING_BIT", INT2NUM(GL_LIGHTING_BIT));
    rb_define_const(module, "GL_FOG_BIT", INT2NUM(GL_FOG_BIT));
    rb_define_const(module, "GL_DEPTH_BUFFER_BIT", INT2NUM(GL_DEPTH_BUFFER_BIT));
    rb_define_const(module, "GL_ACCUM_BUFFER_BIT", INT2NUM(GL_ACCUM_BUFFER_BIT));
    rb_define_const(module, "GL_STENCIL_BUFFER_BIT", INT2NUM(GL_STENCIL_BUFFER_BIT));
    rb_define_const(module, "GL_VIEWPORT_BIT", INT2NUM(GL_VIEWPORT_BIT));
    rb_define_const(module, "GL_TRANSFORM_BIT", INT2NUM(GL_TRANSFORM_BIT));
    rb_define_const(module, "GL_ENABLE_BIT", INT2NUM(GL_ENABLE_BIT));
    rb_define_const(module, "GL_COLOR_BUFFER_BIT", INT2NUM(GL_COLOR_BUFFER_BIT));
    rb_define_const(module, "GL_HINT_BIT", INT2NUM(GL_HINT_BIT));
    rb_define_const(module, "GL_EVAL_BIT", INT2NUM(GL_EVAL_BIT));
    rb_define_const(module, "GL_LIST_BIT", INT2NUM(GL_LIST_BIT));
    rb_define_const(module, "GL_TEXTURE_BIT", INT2NUM(GL_TEXTURE_BIT));
    rb_define_const(module, "GL_SCISSOR_BIT", INT2NUM(GL_SCISSOR_BIT));
    rb_define_const(module, "GL_ALL_ATTRIB_BITS", INT2NUM(GL_ALL_ATTRIB_BITS));
#if defined(GL_VERSION_1_1)
    rb_define_const(module, "GL_CLIENT_PIXEL_STORE_BIT", INT2NUM(GL_CLIENT_PIXEL_STORE_BIT));
    rb_define_const(module, "GL_CLIENT_VERTEX_ARRAY_BIT", INT2NUM(GL_CLIENT_VERTEX_ARRAY_BIT));
#ifndef GL_ALL_CLIENT_ATTRIB_BITS
#define GL_ALL_CLIENT_ATTRIB_BITS GL_CLIENT_ALL_ATTRIB_BITS
#endif
    rb_define_const(module, "GL_ALL_CLIENT_ATTRIB_BITS", INT2NUM(GL_ALL_CLIENT_ATTRIB_BITS));
#endif /* GL_VERSION_1_1 */

    rb_global_variable(&g_current_sel_buffer);
    rb_global_variable(&g_current_feed_buffer);
    rb_global_variable(&g_Vertex_ptr);
    rb_global_variable(&g_Normal_ptr);
    rb_global_variable(&g_Color_ptr);
    rb_global_variable(&g_Index_ptr);
    rb_global_variable(&g_TexCoord_ptr);
    rb_global_variable(&g_EdgeFlag_ptr);
}
