/*
 * Last edit by previous maintainer:
 * 2001/12/01 05:28:29, yoshi
 *
 * $Date: 2006/07/09 02:31:19 $
 * $Author: john $
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

static VALUE mOGL;

void InitializeGL()
{
    mOGL = rb_define_module("GL");
    rb_define_module_function(mOGL, "ClearIndex", gl_ClearIndex, 1);
    rb_define_module_function(mOGL, "ClearColor", gl_ClearColor, 4);
    rb_define_module_function(mOGL, "Clear", gl_Clear, 1);
    rb_define_module_function(mOGL, "IndexMask", gl_IndexMask, 1);
    rb_define_module_function(mOGL, "ColorMask", gl_ColorMask, 4);
    rb_define_module_function(mOGL, "AlphaFunc", gl_AlphaFunc, 2);
    rb_define_module_function(mOGL, "BlendFunc", gl_BlendFunc, 2);
    rb_define_module_function(mOGL, "LogicOp", gl_LogicOp, 1);
    rb_define_module_function(mOGL, "CullFace", gl_CullFace, 1);
    rb_define_module_function(mOGL, "FrontFace", gl_FrontFace, 1);
    rb_define_module_function(mOGL, "PointSize", gl_PointSize, 1);
    rb_define_module_function(mOGL, "LineWidth", gl_LineWidth, 1);
    rb_define_module_function(mOGL, "LineStipple", gl_LineStipple, 2);
    rb_define_module_function(mOGL, "PolygonMode", gl_PolygonMode, 2);
    rb_define_module_function(mOGL, "PolygonOffset", gl_PolygonOffset, 2);
    rb_define_module_function(mOGL, "PolygonStipple", gl_PolygonStipple, 1);
    rb_define_module_function(mOGL, "GetPolygonStipple", gl_GetPolygonStipple, 0);
    rb_define_module_function(mOGL, "EdgeFlag", gl_EdgeFlag, 1);
    rb_define_module_function(mOGL, "Scissor", gl_Scissor, 4);
    rb_define_module_function(mOGL, "ClipPlane", gl_ClipPlane, 2);
    rb_define_module_function(mOGL, "DrawBuffer", gl_DrawBuffer, 1);
    rb_define_module_function(mOGL, "ReadBuffer", gl_ReadBuffer, 1);
    rb_define_module_function(mOGL, "Enable", gl_Enable, 1);
    rb_define_module_function(mOGL, "Disable", gl_Disable, 1);
    rb_define_module_function(mOGL, "IsEnabled", gl_IsEnabled, 1);
    rb_define_module_function(mOGL, "GetDoublev", gl_GetDoublev, 1);
    rb_define_alias(mOGL, "GetDouble", "GetDoublev");
    rb_define_module_function(mOGL, "PushAttrib", gl_PushAttrib, 1);
    rb_define_module_function(mOGL, "PopAttrib", gl_PopAttrib, 0);
    rb_define_module_function(mOGL, "RenderMode", gl_RenderMode, 1);
    rb_define_module_function(mOGL, "GetError", gl_GetError, 0);
    rb_define_module_function(mOGL, "GetString", gl_GetString, 1);
    rb_define_module_function(mOGL, "Finish", gl_Finish, 0);
    rb_define_module_function(mOGL, "Flush", gl_Flush, 0);
    rb_define_module_function(mOGL, "Hint", gl_Hint, 2);
    rb_define_module_function(mOGL, "ClearDepth", gl_ClearDepth, 1);
    rb_define_module_function(mOGL, "DepthFunc", gl_DepthFunc, 1);
    rb_define_module_function(mOGL, "DepthMask", gl_DepthMask, 1);
    rb_define_module_function(mOGL, "DepthRange", gl_DepthRange, 2);
    rb_define_module_function(mOGL, "ClearAccum", gl_ClearAccum, 4);
    rb_define_module_function(mOGL, "Accum", gl_Accum, 2);
    rb_define_module_function(mOGL, "MatrixMode", gl_MatrixMode, 1);
    rb_define_module_function(mOGL, "Ortho", gl_Ortho, 6);
    rb_define_module_function(mOGL, "Frustum", gl_Frustum, 6);
    rb_define_module_function(mOGL, "Viewport", gl_Viewport, 4);
    rb_define_module_function(mOGL, "PushMatrix", gl_PushMatrix, 0);
    rb_define_module_function(mOGL, "PopMatrix", gl_PopMatrix, 0);
    rb_define_module_function(mOGL, "LoadIdentity", gl_LoadIdentity, 0);
    rb_define_module_function(mOGL, "LoadMatrix", gl_LoadMatrixd, 1);
    rb_define_module_function(mOGL, "MultMatrix", gl_MultMatrixd, 1);
    rb_define_module_function(mOGL, "Rotated", gl_Rotated, 4);
    rb_define_module_function(mOGL, "Rotate", gl_Rotated, 4);
    rb_define_module_function(mOGL, "Scaled", gl_Scaled, 3);
    rb_define_module_function(mOGL, "Scale", gl_Scaled, 3);
    rb_define_module_function(mOGL, "Translated", gl_Translated, 3);
    rb_define_module_function(mOGL, "Translate", gl_Translated, 3);
    rb_define_module_function(mOGL, "IsList", gl_IsList, 1);
    rb_define_module_function(mOGL, "DeleteLists", gl_DeleteLists, 2);
    rb_define_module_function(mOGL, "GenLists", gl_GenLists, 1);
    rb_define_module_function(mOGL, "NewList", gl_NewList, 2);
    rb_define_module_function(mOGL, "EndList", gl_EndList, 0);
    rb_define_module_function(mOGL, "CallList", gl_CallList, 1);
    rb_define_module_function(mOGL, "CallLists", gl_CallLists, 1);
    rb_define_module_function(mOGL, "ListBase", gl_ListBase, 1);
    rb_define_module_function(mOGL, "Begin", gl_Begin, 1);
    rb_define_module_function(mOGL, "End", gl_End, 0);
    rb_define_module_function(mOGL, "Vertex2d", gl_Vertex2d, 2);
    rb_define_module_function(mOGL, "Vertex2f", gl_Vertex2f, 2);
    rb_define_module_function(mOGL, "Vertex2i", gl_Vertex2i, 2);
    rb_define_module_function(mOGL, "Vertex3d", gl_Vertex3d, 3);
    rb_define_module_function(mOGL, "Vertex3f", gl_Vertex3f, 3);
    rb_define_module_function(mOGL, "Vertex3i", gl_Vertex3i, 3);
    rb_define_module_function(mOGL, "Vertex4d", gl_Vertex4d, 4);
    rb_define_module_function(mOGL, "Vertex4f", gl_Vertex4f, 4);
    rb_define_module_function(mOGL, "Vertex4i", gl_Vertex4i, 4);
    rb_define_module_function(mOGL, "Vertex", gl_Vertex, -1);
    rb_define_module_function(mOGL, "Normal3d", gl_Normal3d, 3);
    rb_define_module_function(mOGL, "Normal3i", gl_Normal3i, 3);
    rb_define_module_function(mOGL, "Normal", gl_Normal, -1);
    rb_define_module_function(mOGL, "Indexd", gl_Indexd, 1);
    rb_define_module_function(mOGL, "Indexi", gl_Indexi, 1);
    rb_define_module_function(mOGL, "Index", gl_Indexi, 1);
    rb_define_module_function(mOGL, "Color3d", gl_Color3d, 3);
    rb_define_module_function(mOGL, "Color3f", gl_Color3f, 3);
    rb_define_module_function(mOGL, "Color3i", gl_Color3i, 3);
    rb_define_module_function(mOGL, "Color3s", gl_Color3s, 3);
    rb_define_module_function(mOGL, "Color3ub", gl_Color3ub, 3);
    rb_define_module_function(mOGL, "Color3ui", gl_Color3ui, 3);
    rb_define_module_function(mOGL, "Color3us", gl_Color3us, 3);
    rb_define_module_function(mOGL, "Color4b", gl_Color4b, 4);
    rb_define_module_function(mOGL, "Color4d", gl_Color4d, 4);
    rb_define_module_function(mOGL, "Color4f", gl_Color4f, 4);
    rb_define_module_function(mOGL, "Color4i", gl_Color4i, 4);
    rb_define_module_function(mOGL, "Color4s", gl_Color4s, 4);
    rb_define_module_function(mOGL, "Color4ub", gl_Color4ub, 4);
    rb_define_module_function(mOGL, "Color4ui", gl_Color4ui, 4);
    rb_define_module_function(mOGL, "Color4us", gl_Color4us, 4);
    rb_define_module_function(mOGL, "Color", gl_Color, -1);
    rb_define_module_function(mOGL, "TexCoord1d", gl_TexCoord1d, 1);
    rb_define_module_function(mOGL, "TexCoord1f", gl_TexCoord1f, 1);
    rb_define_module_function(mOGL, "TexCoord1i", gl_TexCoord1i, 1);
    rb_define_module_function(mOGL, "TexCoord1s", gl_TexCoord1s, 1);
    rb_define_module_function(mOGL, "TexCoord2d", gl_TexCoord2d, 2);
    rb_define_module_function(mOGL, "TexCoord2f", gl_TexCoord2f, 2);
    rb_define_module_function(mOGL, "TexCoord2i", gl_TexCoord2i, 2);
    rb_define_module_function(mOGL, "TexCoord2s", gl_TexCoord2s, 2);
    rb_define_module_function(mOGL, "TexCoord3d", gl_TexCoord3d, 3);
    rb_define_module_function(mOGL, "TexCoord3f", gl_TexCoord3f, 3);
    rb_define_module_function(mOGL, "TexCoord3i", gl_TexCoord3i, 3);
    rb_define_module_function(mOGL, "TexCoord3s", gl_TexCoord3s, 3);
    rb_define_module_function(mOGL, "TexCoord4d", gl_TexCoord4d, 4);
    rb_define_module_function(mOGL, "TexCoord4f", gl_TexCoord4f, 4);
    rb_define_module_function(mOGL, "TexCoord4i", gl_TexCoord4i, 4);
    rb_define_module_function(mOGL, "TexCoord4s", gl_TexCoord4s, 4);
    rb_define_module_function(mOGL, "TexCoord", gl_TexCoord, -1);
    rb_define_module_function(mOGL, "RasterPos2d", gl_RasterPos2d, 2);
    rb_define_module_function(mOGL, "RasterPos2i", gl_RasterPos2i, 2);
    rb_define_module_function(mOGL, "RasterPos3d", gl_RasterPos3d, 3);
    rb_define_module_function(mOGL, "RasterPos3i", gl_RasterPos3i, 3);
    rb_define_module_function(mOGL, "RasterPos4d", gl_RasterPos4d, 4);
    rb_define_module_function(mOGL, "RasterPos4i", gl_RasterPos4i, 4);
    rb_define_module_function(mOGL, "RasterPos", gl_RasterPos, -1);
    rb_define_module_function(mOGL, "Rectd", gl_Rectd, 4);
    rb_define_module_function(mOGL, "Recti", gl_Recti, 4);
    rb_define_module_function(mOGL, "Rect", gl_Rect, -1);
    rb_define_module_function(mOGL, "ShadeModel", gl_ShadeModel, 1);
    rb_define_module_function(mOGL, "Lightf", gl_Lightf, 3);
    rb_define_module_function(mOGL, "Lighti", gl_Lighti, 3);
    rb_define_module_function(mOGL, "Lightiv", gl_Lightiv, 3);
    rb_define_module_function(mOGL, "Lightfv", gl_Light, 3);
    rb_define_module_function(mOGL, "Light", gl_Light, 3);
    rb_define_module_function(mOGL, "LightModelf", gl_LightModelf, 2);
    rb_define_module_function(mOGL, "LightModeli", gl_LightModeli, 2);
    rb_define_module_function(mOGL, "LightModel", gl_LightModel, 2);
    rb_define_module_function(mOGL, "Materialf", gl_Materialf, 3);
    rb_define_module_function(mOGL, "Materiali", gl_Materiali, 3);
    rb_define_module_function(mOGL, "Material", gl_Material, 3);
    rb_define_module_function(mOGL, "GetMaterial", gl_GetMaterial, 2);
    rb_define_module_function(mOGL, "ColorMaterial", gl_ColorMaterial, 2);
    rb_define_module_function(mOGL, "PixelZoom", gl_PixelZoom, 2);
    rb_define_module_function(mOGL, "PixelStoref", gl_PixelStoref, 2);
    rb_define_module_function(mOGL, "PixelStorei", gl_PixelStorei, 2);
    rb_define_module_function(mOGL, "PixelStore", gl_PixelStoref, 2);
    rb_define_module_function(mOGL, "PixelTransferf", gl_PixelTransferf, 2);
    rb_define_module_function(mOGL, "PixelTransferi", gl_PixelTransferi, 2);
    rb_define_module_function(mOGL, "PixelTransfer", gl_PixelTransferf, 2);
    rb_define_module_function(mOGL, "Bitmap", gl_Bitmap, 7);
    rb_define_module_function(mOGL, "ReadPixels", gl_ReadPixels, 6);
    rb_define_module_function(mOGL, "DrawPixels", gl_DrawPixels, 5);
    rb_define_module_function(mOGL, "CopyPixels", gl_CopyPixels, 5);
    rb_define_module_function(mOGL, "StencilFunc", gl_StencilFunc, 3);
    rb_define_module_function(mOGL, "StencilMask", gl_StencilMask, 1);
    rb_define_module_function(mOGL, "StencilOp", gl_StencilOp, 3);
    rb_define_module_function(mOGL, "ClearStencil", gl_ClearStencil, 1);
    rb_define_module_function(mOGL, "TexGend", gl_TexGend, 3);
    rb_define_module_function(mOGL, "TexGeni", gl_TexGeni, 3);
    rb_define_module_function(mOGL, "TexGen", gl_TexGen, 3);
    rb_define_module_function(mOGL, "TexEnvf", gl_TexEnvf, 3);
    rb_define_module_function(mOGL, "TexEnvi", gl_TexEnvi, 3);
    rb_define_module_function(mOGL, "TexEnv", gl_TexEnvf, 3);
    rb_define_module_function(mOGL, "TexParameterf", gl_TexParameterf, 3);
    rb_define_module_function(mOGL, "TexParameteri", gl_TexParameteri, 3);
    rb_define_module_function(mOGL, "TexParameter", gl_TexParameterf, 3);
    rb_define_module_function(mOGL, "TexImage2D", gl_TexImage2D, 9);
    rb_define_module_function(mOGL, "Map1d", gl_Map1d, 6);
    rb_define_module_function(mOGL, "Map2d", gl_Map2d, 10);
    rb_define_module_function(mOGL, "EvalCoord1d", gl_EvalCoord1d, 1);
    rb_define_module_function(mOGL, "EvalCoord2d", gl_EvalCoord2d, 2);
    rb_define_module_function(mOGL, "MapGrid1d", gl_MapGrid1d, 3);
    rb_define_module_function(mOGL, "MapGrid2d", gl_MapGrid2d, 6);
    rb_define_module_function(mOGL, "EvalPoint1", gl_EvalPoint1, 1);
    rb_define_module_function(mOGL, "EvalPoint2", gl_EvalPoint2, 2);
    rb_define_module_function(mOGL, "EvalMesh1", gl_EvalMesh1, 3);
    rb_define_module_function(mOGL, "EvalMesh2", gl_EvalMesh2, 5);
    rb_define_module_function(mOGL, "Fogf", gl_Fogf, 2);
    rb_define_module_function(mOGL, "Fogi", gl_Fogi, 2);
    rb_define_module_function(mOGL, "Fog", gl_Fogfv, 2);
    rb_define_module_function(mOGL, "PassThrough", gl_PassThrough, 1);
    rb_define_module_function(mOGL, "FeedbackBuffer", gl_FeedbackBuffer, -1);
    rb_define_module_function(mOGL, "SelectBuffer", gl_SelectBuffer, -1);
    rb_define_module_function(mOGL, "InitNames", gl_InitNames, 0);
    rb_define_module_function(mOGL, "LoadName", gl_LoadName, 1);
    rb_define_module_function(mOGL, "PushName", gl_PushName, 1);
    rb_define_module_function(mOGL, "PopName", gl_PopName, 0);
#if defined(GL_VERSION_1_1)
    rb_define_module_function(mOGL, "EnableClientState", gl_EnableClientState, 1);
    rb_define_module_function(mOGL, "DisableClientState", gl_DisableClientState, 1);
    rb_define_module_function(mOGL, "PushClientAttrib", gl_PushClientAttrib, 1);
    rb_define_module_function(mOGL, "PopClientAttrib", gl_PopClientAttrib, 0);
    rb_define_module_function(mOGL, "VertexPointer", gl_VertexPointer, 4);
    rb_define_module_function(mOGL, "NormalPointer", gl_NormalPointer, 3);
    rb_define_module_function(mOGL, "ColorPointer", gl_ColorPointer, 4);
    rb_define_module_function(mOGL, "IndexPointer", gl_IndexPointer, 3);
    rb_define_module_function(mOGL, "TexCoordPointer", gl_TexCoordPointer, 4);
    rb_define_module_function(mOGL, "EdgeFlagPointer", gl_EdgeFlagPointer, 2);
    rb_define_module_function(mOGL, "ArrayElement", gl_ArrayElement, 1);
    rb_define_module_function(mOGL, "DrawArrays", gl_DrawArrays, 3);
    rb_define_module_function(mOGL, "DrawElements", gl_DrawElements, 4);
    rb_define_module_function(mOGL, "InterleavedArrays", gl_InterleavedArrays, 3);
    rb_define_module_function(mOGL, "GenTextures", gl_GenTextures, 1);
    rb_define_module_function(mOGL, "DeleteTextures", gl_DeleteTextures, 1);
    rb_define_module_function(mOGL, "BindTexture", gl_BindTexture, 2);
    rb_define_module_function(mOGL, "IsTexture", gl_IsTexture, 1);
    rb_define_module_function(mOGL, "TexSubImage2D", gl_TexSubImage2D, 9);
    rb_define_module_function(mOGL, "CopyTexImage1D", gl_CopyTexImage1D, 7);
    rb_define_module_function(mOGL, "CopyTexImage2D", gl_CopyTexImage2D, 8);
    rb_define_module_function(mOGL, "CopyTexSubImage1D", gl_CopyTexSubImage1D, 6);
    rb_define_module_function(mOGL, "CopyTexSubImage2D", gl_CopyTexSubImage2D, 8);
#endif /* GL_VERSION_1_1 */

#if defined (GL_VERSION_1_2)
    rb_define_module_function(mOGL, "DrawRangeElements", gl_DrawRangeElements, 6);
    rb_define_module_function(mOGL, "TexImage3D", gl_TexImage3D, 10);
    rb_define_module_function(mOGL, "TexSubImage3D", gl_TexSubImage3D, 11);
    rb_define_module_function(mOGL, "CopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
#endif /* GL_VERSION_1_2 */

    rb_define_const(mOGL, "FALSE", INT2NUM(GL_FALSE));
    rb_define_const(mOGL, "TRUE", INT2NUM(GL_TRUE));
    rb_define_const(mOGL, "BYTE", INT2NUM(GL_BYTE));
    rb_define_const(mOGL, "UNSIGNED_BYTE", INT2NUM(GL_UNSIGNED_BYTE));
    rb_define_const(mOGL, "SHORT", INT2NUM(GL_SHORT));
    rb_define_const(mOGL, "UNSIGNED_SHORT", INT2NUM(GL_UNSIGNED_SHORT));
    rb_define_const(mOGL, "INT", INT2NUM(GL_INT));
    rb_define_const(mOGL, "UNSIGNED_INT", INT2NUM(GL_UNSIGNED_INT));
    rb_define_const(mOGL, "FLOAT", INT2NUM(GL_FLOAT));
    rb_define_const(mOGL, "DOUBLE", INT2NUM(GL_DOUBLE));
    rb_define_const(mOGL, "GL_2_BYTES", INT2NUM(GL_2_BYTES));
    rb_define_const(mOGL, "GL_3_BYTES", INT2NUM(GL_3_BYTES));
    rb_define_const(mOGL, "GL_4_BYTES", INT2NUM(GL_4_BYTES));
    rb_define_const(mOGL, "LINES", INT2NUM(GL_LINES));
    rb_define_const(mOGL, "POINTS", INT2NUM(GL_POINTS));
    rb_define_const(mOGL, "LINE_STRIP", INT2NUM(GL_LINE_STRIP));
    rb_define_const(mOGL, "LINE_LOOP", INT2NUM(GL_LINE_LOOP));
    rb_define_const(mOGL, "TRIANGLES", INT2NUM(GL_TRIANGLES));
    rb_define_const(mOGL, "TRIANGLE_STRIP", INT2NUM(GL_TRIANGLE_STRIP));
    rb_define_const(mOGL, "TRIANGLE_FAN", INT2NUM(GL_TRIANGLE_FAN));
    rb_define_const(mOGL, "QUADS", INT2NUM(GL_QUADS));
    rb_define_const(mOGL, "QUAD_STRIP", INT2NUM(GL_QUAD_STRIP));
    rb_define_const(mOGL, "POLYGON", INT2NUM(GL_POLYGON));
    rb_define_const(mOGL, "EDGE_FLAG", INT2NUM(GL_EDGE_FLAG));
#if defined(GL_VERSION_1_1)
    rb_define_const(mOGL, "VERTEX_ARRAY", INT2NUM(GL_VERTEX_ARRAY));
    rb_define_const(mOGL, "NORMAL_ARRAY", INT2NUM(GL_NORMAL_ARRAY));
    rb_define_const(mOGL, "COLOR_ARRAY", INT2NUM(GL_COLOR_ARRAY));
    rb_define_const(mOGL, "INDEX_ARRAY", INT2NUM(GL_INDEX_ARRAY));
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY", INT2NUM(GL_TEXTURE_COORD_ARRAY));
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY", INT2NUM(GL_EDGE_FLAG_ARRAY));
    rb_define_const(mOGL, "VERTEX_ARRAY_SIZE", INT2NUM(GL_VERTEX_ARRAY_SIZE));
    rb_define_const(mOGL, "VERTEX_ARRAY_TYPE", INT2NUM(GL_VERTEX_ARRAY_TYPE));
    rb_define_const(mOGL, "VERTEX_ARRAY_STRIDE", INT2NUM(GL_VERTEX_ARRAY_STRIDE));
    rb_define_const(mOGL, "NORMAL_ARRAY_TYPE", INT2NUM(GL_NORMAL_ARRAY_TYPE));
    rb_define_const(mOGL, "NORMAL_ARRAY_STRIDE", INT2NUM(GL_NORMAL_ARRAY_STRIDE));
    rb_define_const(mOGL, "COLOR_ARRAY_SIZE", INT2NUM(GL_COLOR_ARRAY_SIZE));
    rb_define_const(mOGL, "COLOR_ARRAY_TYPE", INT2NUM(GL_COLOR_ARRAY_TYPE));
    rb_define_const(mOGL, "COLOR_ARRAY_STRIDE", INT2NUM(GL_COLOR_ARRAY_STRIDE));
    rb_define_const(mOGL, "INDEX_ARRAY_TYPE", INT2NUM(GL_INDEX_ARRAY_TYPE));
    rb_define_const(mOGL, "INDEX_ARRAY_STRIDE", INT2NUM(GL_INDEX_ARRAY_STRIDE));
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_SIZE", INT2NUM(GL_TEXTURE_COORD_ARRAY_SIZE));
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_TYPE", INT2NUM(GL_TEXTURE_COORD_ARRAY_TYPE));
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_STRIDE", INT2NUM(GL_TEXTURE_COORD_ARRAY_STRIDE));
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_STRIDE", INT2NUM(GL_EDGE_FLAG_ARRAY_STRIDE));
    rb_define_const(mOGL, "VERTEX_ARRAY_POINTER", INT2NUM(GL_VERTEX_ARRAY_POINTER));
    rb_define_const(mOGL, "NORMAL_ARRAY_POINTER", INT2NUM(GL_NORMAL_ARRAY_POINTER));
    rb_define_const(mOGL, "COLOR_ARRAY_POINTER", INT2NUM(GL_COLOR_ARRAY_POINTER));
    rb_define_const(mOGL, "INDEX_ARRAY_POINTER", INT2NUM(GL_INDEX_ARRAY_POINTER));
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_POINTER", INT2NUM(GL_TEXTURE_COORD_ARRAY_POINTER));
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_POINTER", INT2NUM(GL_EDGE_FLAG_ARRAY_POINTER));
    rb_define_const(mOGL, "V2F", INT2NUM(GL_V2F));
    rb_define_const(mOGL, "V3F", INT2NUM(GL_V3F));
    rb_define_const(mOGL, "C4UB_V2F", INT2NUM(GL_C4UB_V2F));
    rb_define_const(mOGL, "C4UB_V3F", INT2NUM(GL_C4UB_V3F));
    rb_define_const(mOGL, "C3F_V3F", INT2NUM(GL_C3F_V3F));
    rb_define_const(mOGL, "N3F_V3F", INT2NUM(GL_N3F_V3F));
    rb_define_const(mOGL, "C4F_N3F_V3F", INT2NUM(GL_C4F_N3F_V3F));
    rb_define_const(mOGL, "T2F_V3F", INT2NUM(GL_T2F_V3F));
    rb_define_const(mOGL, "T4F_V4F", INT2NUM(GL_T4F_V4F));
    rb_define_const(mOGL, "T2F_C4UB_V3F", INT2NUM(GL_T2F_C4UB_V3F));
    rb_define_const(mOGL, "T2F_C3F_V3F", INT2NUM(GL_T2F_C3F_V3F));
    rb_define_const(mOGL, "T2F_N3F_V3F", INT2NUM(GL_T2F_N3F_V3F));
    rb_define_const(mOGL, "T2F_C4F_N3F_V3F", INT2NUM(GL_T2F_C4F_N3F_V3F));
    rb_define_const(mOGL, "T4F_C4F_N3F_V4F", INT2NUM(GL_T4F_C4F_N3F_V4F));
#endif /* GL_VERSION_1_1 */
    rb_define_const(mOGL, "MATRIX_MODE", INT2NUM(GL_MATRIX_MODE));
    rb_define_const(mOGL, "MODELVIEW", INT2NUM(GL_MODELVIEW));
    rb_define_const(mOGL, "PROJECTION", INT2NUM(GL_PROJECTION));
    rb_define_const(mOGL, "TEXTURE", INT2NUM(GL_TEXTURE));
    rb_define_const(mOGL, "POINT_SMOOTH", INT2NUM(GL_POINT_SMOOTH));
    rb_define_const(mOGL, "POINT_SIZE", INT2NUM(GL_POINT_SIZE));
    rb_define_const(mOGL, "POINT_SIZE_GRANULARITY", INT2NUM(GL_POINT_SIZE_GRANULARITY));
    rb_define_const(mOGL, "POINT_SIZE_RANGE", INT2NUM(GL_POINT_SIZE_RANGE));
    rb_define_const(mOGL, "LINE_SMOOTH", INT2NUM(GL_LINE_SMOOTH));
    rb_define_const(mOGL, "LINE_STIPPLE", INT2NUM(GL_LINE_STIPPLE));
    rb_define_const(mOGL, "LINE_STIPPLE_PATTERN", INT2NUM(GL_LINE_STIPPLE_PATTERN));
    rb_define_const(mOGL, "LINE_STIPPLE_REPEAT", INT2NUM(GL_LINE_STIPPLE_REPEAT));
    rb_define_const(mOGL, "LINE_WIDTH", INT2NUM(GL_LINE_WIDTH));
    rb_define_const(mOGL, "LINE_WIDTH_GRANULARITY", INT2NUM(GL_LINE_WIDTH_GRANULARITY));
    rb_define_const(mOGL, "LINE_WIDTH_RANGE", INT2NUM(GL_LINE_WIDTH_RANGE));
    rb_define_const(mOGL, "POINT", INT2NUM(GL_POINT));
    rb_define_const(mOGL, "LINE", INT2NUM(GL_LINE));
    rb_define_const(mOGL, "FILL", INT2NUM(GL_FILL));
    rb_define_const(mOGL, "CCW", INT2NUM(GL_CCW));
    rb_define_const(mOGL, "CW", INT2NUM(GL_CW));
    rb_define_const(mOGL, "FRONT", INT2NUM(GL_FRONT));
    rb_define_const(mOGL, "BACK", INT2NUM(GL_BACK));
    rb_define_const(mOGL, "CULL_FACE", INT2NUM(GL_CULL_FACE));
    rb_define_const(mOGL, "CULL_FACE_MODE", INT2NUM(GL_CULL_FACE_MODE));
    rb_define_const(mOGL, "POLYGON_SMOOTH", INT2NUM(GL_POLYGON_SMOOTH));
    rb_define_const(mOGL, "POLYGON_STIPPLE", INT2NUM(GL_POLYGON_STIPPLE));
    rb_define_const(mOGL, "FRONT_FACE", INT2NUM(GL_FRONT_FACE));
    rb_define_const(mOGL, "POLYGON_MODE", INT2NUM(GL_POLYGON_MODE));
    rb_define_const(mOGL, "POLYGON_OFFSET_FACTOR", INT2NUM(GL_POLYGON_OFFSET_FACTOR));
    rb_define_const(mOGL, "POLYGON_OFFSET_UNITS", INT2NUM(GL_POLYGON_OFFSET_UNITS));
    rb_define_const(mOGL, "POLYGON_OFFSET_POINT", INT2NUM(GL_POLYGON_OFFSET_POINT));
    rb_define_const(mOGL, "POLYGON_OFFSET_LINE", INT2NUM(GL_POLYGON_OFFSET_LINE));
    rb_define_const(mOGL, "POLYGON_OFFSET_FILL", INT2NUM(GL_POLYGON_OFFSET_FILL));
    rb_define_const(mOGL, "COMPILE", INT2NUM(GL_COMPILE));
    rb_define_const(mOGL, "COMPILE_AND_EXECUTE", INT2NUM(GL_COMPILE_AND_EXECUTE));
    rb_define_const(mOGL, "LIST_BASE", INT2NUM(GL_LIST_BASE));
    rb_define_const(mOGL, "LIST_INDEX", INT2NUM(GL_LIST_INDEX));
    rb_define_const(mOGL, "LIST_MODE", INT2NUM(GL_LIST_MODE));
    rb_define_const(mOGL, "NEVER", INT2NUM(GL_NEVER));
    rb_define_const(mOGL, "LESS", INT2NUM(GL_LESS));
    rb_define_const(mOGL, "GEQUAL", INT2NUM(GL_GEQUAL));
    rb_define_const(mOGL, "LEQUAL", INT2NUM(GL_LEQUAL));
    rb_define_const(mOGL, "GREATER", INT2NUM(GL_GREATER));
    rb_define_const(mOGL, "NOTEQUAL", INT2NUM(GL_NOTEQUAL));
    rb_define_const(mOGL, "EQUAL", INT2NUM(GL_EQUAL));
    rb_define_const(mOGL, "ALWAYS", INT2NUM(GL_ALWAYS));
    rb_define_const(mOGL, "DEPTH_TEST", INT2NUM(GL_DEPTH_TEST));
    rb_define_const(mOGL, "DEPTH_BITS", INT2NUM(GL_DEPTH_BITS));
    rb_define_const(mOGL, "DEPTH_CLEAR_VALUE", INT2NUM(GL_DEPTH_CLEAR_VALUE));
    rb_define_const(mOGL, "DEPTH_FUNC", INT2NUM(GL_DEPTH_FUNC));
    rb_define_const(mOGL, "DEPTH_RANGE", INT2NUM(GL_DEPTH_RANGE));
    rb_define_const(mOGL, "DEPTH_WRITEMASK", INT2NUM(GL_DEPTH_WRITEMASK));
    rb_define_const(mOGL, "DEPTH_COMPONENT", INT2NUM(GL_DEPTH_COMPONENT));
    rb_define_const(mOGL, "LIGHTING", INT2NUM(GL_LIGHTING));
    rb_define_const(mOGL, "LIGHT0", INT2NUM(GL_LIGHT0));
    rb_define_const(mOGL, "LIGHT1", INT2NUM(GL_LIGHT1));
    rb_define_const(mOGL, "LIGHT2", INT2NUM(GL_LIGHT2));
    rb_define_const(mOGL, "LIGHT3", INT2NUM(GL_LIGHT3));
    rb_define_const(mOGL, "LIGHT4", INT2NUM(GL_LIGHT4));
    rb_define_const(mOGL, "LIGHT5", INT2NUM(GL_LIGHT5));
    rb_define_const(mOGL, "LIGHT6", INT2NUM(GL_LIGHT6));
    rb_define_const(mOGL, "LIGHT7", INT2NUM(GL_LIGHT7));
    rb_define_const(mOGL, "SPOT_EXPONENT", INT2NUM(GL_SPOT_EXPONENT));
    rb_define_const(mOGL, "SPOT_CUTOFF", INT2NUM(GL_SPOT_CUTOFF));
    rb_define_const(mOGL, "CONSTANT_ATTENUATION", INT2NUM(GL_CONSTANT_ATTENUATION));
    rb_define_const(mOGL, "LINEAR_ATTENUATION", INT2NUM(GL_LINEAR_ATTENUATION));
    rb_define_const(mOGL, "QUADRATIC_ATTENUATION", INT2NUM(GL_QUADRATIC_ATTENUATION));
    rb_define_const(mOGL, "AMBIENT", INT2NUM(GL_AMBIENT));
    rb_define_const(mOGL, "DIFFUSE", INT2NUM(GL_DIFFUSE));
    rb_define_const(mOGL, "SPECULAR", INT2NUM(GL_SPECULAR));
    rb_define_const(mOGL, "SHININESS", INT2NUM(GL_SHININESS));
    rb_define_const(mOGL, "EMISSION", INT2NUM(GL_EMISSION));
    rb_define_const(mOGL, "POSITION", INT2NUM(GL_POSITION));
    rb_define_const(mOGL, "SPOT_DIRECTION", INT2NUM(GL_SPOT_DIRECTION));
    rb_define_const(mOGL, "AMBIENT_AND_DIFFUSE", INT2NUM(GL_AMBIENT_AND_DIFFUSE));
    rb_define_const(mOGL, "COLOR_INDEXES", INT2NUM(GL_COLOR_INDEXES));
    rb_define_const(mOGL, "LIGHT_MODEL_TWO_SIDE", INT2NUM(GL_LIGHT_MODEL_TWO_SIDE));
    rb_define_const(mOGL, "LIGHT_MODEL_LOCAL_VIEWER", INT2NUM(GL_LIGHT_MODEL_LOCAL_VIEWER));
    rb_define_const(mOGL, "LIGHT_MODEL_AMBIENT", INT2NUM(GL_LIGHT_MODEL_AMBIENT));
    rb_define_const(mOGL, "FRONT_AND_BACK", INT2NUM(GL_FRONT_AND_BACK));
    rb_define_const(mOGL, "SHADE_MODEL", INT2NUM(GL_SHADE_MODEL));
    rb_define_const(mOGL, "FLAT", INT2NUM(GL_FLAT));
    rb_define_const(mOGL, "SMOOTH", INT2NUM(GL_SMOOTH));
    rb_define_const(mOGL, "COLOR_MATERIAL", INT2NUM(GL_COLOR_MATERIAL));
    rb_define_const(mOGL, "COLOR_MATERIAL_FACE", INT2NUM(GL_COLOR_MATERIAL_FACE));
    rb_define_const(mOGL, "COLOR_MATERIAL_PARAMETER", INT2NUM(GL_COLOR_MATERIAL_PARAMETER));
    rb_define_const(mOGL, "NORMALIZE", INT2NUM(GL_NORMALIZE));
    rb_define_const(mOGL, "CLIP_PLANE0", INT2NUM(GL_CLIP_PLANE0));
    rb_define_const(mOGL, "CLIP_PLANE1", INT2NUM(GL_CLIP_PLANE1));
    rb_define_const(mOGL, "CLIP_PLANE2", INT2NUM(GL_CLIP_PLANE2));
    rb_define_const(mOGL, "CLIP_PLANE3", INT2NUM(GL_CLIP_PLANE3));
    rb_define_const(mOGL, "CLIP_PLANE4", INT2NUM(GL_CLIP_PLANE4));
    rb_define_const(mOGL, "CLIP_PLANE5", INT2NUM(GL_CLIP_PLANE5));
    rb_define_const(mOGL, "ACCUM_RED_BITS", INT2NUM(GL_ACCUM_RED_BITS));
    rb_define_const(mOGL, "ACCUM_GREEN_BITS", INT2NUM(GL_ACCUM_GREEN_BITS));
    rb_define_const(mOGL, "ACCUM_BLUE_BITS", INT2NUM(GL_ACCUM_BLUE_BITS));
    rb_define_const(mOGL, "ACCUM_ALPHA_BITS", INT2NUM(GL_ACCUM_ALPHA_BITS));
    rb_define_const(mOGL, "ACCUM_CLEAR_VALUE", INT2NUM(GL_ACCUM_CLEAR_VALUE));
    rb_define_const(mOGL, "ACCUM", INT2NUM(GL_ACCUM));
    rb_define_const(mOGL, "ADD", INT2NUM(GL_ADD));
    rb_define_const(mOGL, "LOAD", INT2NUM(GL_LOAD));
    rb_define_const(mOGL, "MULT", INT2NUM(GL_MULT));
    rb_define_const(mOGL, "RETURN", INT2NUM(GL_RETURN));
    rb_define_const(mOGL, "ALPHA_TEST", INT2NUM(GL_ALPHA_TEST));
    rb_define_const(mOGL, "ALPHA_TEST_REF", INT2NUM(GL_ALPHA_TEST_REF));
    rb_define_const(mOGL, "ALPHA_TEST_FUNC", INT2NUM(GL_ALPHA_TEST_FUNC));
    rb_define_const(mOGL, "BLEND", INT2NUM(GL_BLEND));
    rb_define_const(mOGL, "BLEND_SRC", INT2NUM(GL_BLEND_SRC));
    rb_define_const(mOGL, "BLEND_DST", INT2NUM(GL_BLEND_DST));
    rb_define_const(mOGL, "ZERO", INT2NUM(GL_ZERO));
    rb_define_const(mOGL, "ONE", INT2NUM(GL_ONE));
    rb_define_const(mOGL, "SRC_COLOR", INT2NUM(GL_SRC_COLOR));
    rb_define_const(mOGL, "ONE_MINUS_SRC_COLOR", INT2NUM(GL_ONE_MINUS_SRC_COLOR));
    rb_define_const(mOGL, "DST_COLOR", INT2NUM(GL_DST_COLOR));
    rb_define_const(mOGL, "ONE_MINUS_DST_COLOR", INT2NUM(GL_ONE_MINUS_DST_COLOR));
    rb_define_const(mOGL, "SRC_ALPHA", INT2NUM(GL_SRC_ALPHA));
    rb_define_const(mOGL, "ONE_MINUS_SRC_ALPHA", INT2NUM(GL_ONE_MINUS_SRC_ALPHA));
    rb_define_const(mOGL, "DST_ALPHA", INT2NUM(GL_DST_ALPHA));
    rb_define_const(mOGL, "ONE_MINUS_DST_ALPHA", INT2NUM(GL_ONE_MINUS_DST_ALPHA));
    rb_define_const(mOGL, "SRC_ALPHA_SATURATE", INT2NUM(GL_SRC_ALPHA_SATURATE));
#if defined(GL_VERSION_1_2)
    rb_define_const(mOGL, "CONSTANT_COLOR", INT2NUM(GL_CONSTANT_COLOR));
    rb_define_const(mOGL, "ONE_MINUS_CONSTANT_COLOR", INT2NUM(GL_ONE_MINUS_CONSTANT_COLOR));
    rb_define_const(mOGL, "CONSTANT_ALPHA", INT2NUM(GL_CONSTANT_ALPHA));
    rb_define_const(mOGL, "ONE_MINUS_CONSTANT_ALPHA", INT2NUM(GL_ONE_MINUS_CONSTANT_ALPHA));
#endif /* GL_VERSION_1_2 */
    rb_define_const(mOGL, "FEEDBACK", INT2NUM(GL_FEEDBACK));
    rb_define_const(mOGL, "RENDER", INT2NUM(GL_RENDER));
    rb_define_const(mOGL, "SELECT", INT2NUM(GL_SELECT));
    rb_define_const(mOGL, "GL_2D", INT2NUM(GL_2D));
    rb_define_const(mOGL, "GL_3D", INT2NUM(GL_3D));
    rb_define_const(mOGL, "GL_3D_COLOR", INT2NUM(GL_3D_COLOR));
    rb_define_const(mOGL, "GL_3D_COLOR_TEXTURE", INT2NUM(GL_3D_COLOR_TEXTURE));
    rb_define_const(mOGL, "GL_4D_COLOR_TEXTURE", INT2NUM(GL_4D_COLOR_TEXTURE));
    rb_define_const(mOGL, "POINT_TOKEN", INT2NUM(GL_POINT_TOKEN));
    rb_define_const(mOGL, "LINE_TOKEN", INT2NUM(GL_LINE_TOKEN));
    rb_define_const(mOGL, "LINE_RESET_TOKEN", INT2NUM(GL_LINE_RESET_TOKEN));
    rb_define_const(mOGL, "POLYGON_TOKEN", INT2NUM(GL_POLYGON_TOKEN));
    rb_define_const(mOGL, "BITMAP_TOKEN", INT2NUM(GL_BITMAP_TOKEN));
    rb_define_const(mOGL, "DRAW_PIXEL_TOKEN", INT2NUM(GL_DRAW_PIXEL_TOKEN));
    rb_define_const(mOGL, "COPY_PIXEL_TOKEN", INT2NUM(GL_COPY_PIXEL_TOKEN));
    rb_define_const(mOGL, "PASS_THROUGH_TOKEN", INT2NUM(GL_PASS_THROUGH_TOKEN));
    rb_define_const(mOGL, "FEEDBACK_BUFFER_POINTER", INT2NUM(GL_FEEDBACK_BUFFER_POINTER));
    rb_define_const(mOGL, "FEEDBACK_BUFFER_SIZE", INT2NUM(GL_FEEDBACK_BUFFER_SIZE));
    rb_define_const(mOGL, "FEEDBACK_BUFFER_TYPE", INT2NUM(GL_FEEDBACK_BUFFER_TYPE));
    rb_define_const(mOGL, "FOG", INT2NUM(GL_FOG));
    rb_define_const(mOGL, "FOG_MODE", INT2NUM(GL_FOG_MODE));
    rb_define_const(mOGL, "FOG_DENSITY", INT2NUM(GL_FOG_DENSITY));
    rb_define_const(mOGL, "FOG_COLOR", INT2NUM(GL_FOG_COLOR));
    rb_define_const(mOGL, "FOG_INDEX", INT2NUM(GL_FOG_INDEX));
    rb_define_const(mOGL, "FOG_START", INT2NUM(GL_FOG_START));
    rb_define_const(mOGL, "FOG_END", INT2NUM(GL_FOG_END));
    rb_define_const(mOGL, "LINEAR", INT2NUM(GL_LINEAR));
    rb_define_const(mOGL, "EXP", INT2NUM(GL_EXP));
    rb_define_const(mOGL, "EXP2", INT2NUM(GL_EXP2));
    rb_define_const(mOGL, "LOGIC_OP", INT2NUM(GL_LOGIC_OP));
    rb_define_const(mOGL, "INDEX_LOGIC_OP", INT2NUM(GL_INDEX_LOGIC_OP));
    rb_define_const(mOGL, "COLOR_LOGIC_OP", INT2NUM(GL_COLOR_LOGIC_OP));
    rb_define_const(mOGL, "LOGIC_OP_MODE", INT2NUM(GL_LOGIC_OP_MODE));
    rb_define_const(mOGL, "CLEAR", INT2NUM(GL_CLEAR));
    rb_define_const(mOGL, "SET", INT2NUM(GL_SET));
    rb_define_const(mOGL, "COPY", INT2NUM(GL_COPY));
    rb_define_const(mOGL, "COPY_INVERTED", INT2NUM(GL_COPY_INVERTED));
    rb_define_const(mOGL, "NOOP", INT2NUM(GL_NOOP));
    rb_define_const(mOGL, "INVERT", INT2NUM(GL_INVERT));
    rb_define_const(mOGL, "AND", INT2NUM(GL_AND));
    rb_define_const(mOGL, "NAND", INT2NUM(GL_NAND));
    rb_define_const(mOGL, "OR", INT2NUM(GL_OR));
    rb_define_const(mOGL, "NOR", INT2NUM(GL_NOR));
    rb_define_const(mOGL, "XOR", INT2NUM(GL_XOR));
    rb_define_const(mOGL, "EQUIV", INT2NUM(GL_EQUIV));
    rb_define_const(mOGL, "AND_REVERSE", INT2NUM(GL_AND_REVERSE));
    rb_define_const(mOGL, "AND_INVERTED", INT2NUM(GL_AND_INVERTED));
    rb_define_const(mOGL, "OR_REVERSE", INT2NUM(GL_OR_REVERSE));
    rb_define_const(mOGL, "OR_INVERTED", INT2NUM(GL_OR_INVERTED));
    rb_define_const(mOGL, "STENCIL_TEST", INT2NUM(GL_STENCIL_TEST));
    rb_define_const(mOGL, "STENCIL_WRITEMASK", INT2NUM(GL_STENCIL_WRITEMASK));
    rb_define_const(mOGL, "STENCIL_BITS", INT2NUM(GL_STENCIL_BITS));
    rb_define_const(mOGL, "STENCIL_FUNC", INT2NUM(GL_STENCIL_FUNC));
    rb_define_const(mOGL, "STENCIL_VALUE_MASK", INT2NUM(GL_STENCIL_VALUE_MASK));
    rb_define_const(mOGL, "STENCIL_REF", INT2NUM(GL_STENCIL_REF));
    rb_define_const(mOGL, "STENCIL_FAIL", INT2NUM(GL_STENCIL_FAIL));
    rb_define_const(mOGL, "STENCIL_PASS_DEPTH_PASS", INT2NUM(GL_STENCIL_PASS_DEPTH_PASS));
    rb_define_const(mOGL, "STENCIL_PASS_DEPTH_FAIL", INT2NUM(GL_STENCIL_PASS_DEPTH_FAIL));
    rb_define_const(mOGL, "STENCIL_CLEAR_VALUE", INT2NUM(GL_STENCIL_CLEAR_VALUE));
    rb_define_const(mOGL, "STENCIL_INDEX", INT2NUM(GL_STENCIL_INDEX));
    rb_define_const(mOGL, "KEEP", INT2NUM(GL_KEEP));
    rb_define_const(mOGL, "REPLACE", INT2NUM(GL_REPLACE));
    rb_define_const(mOGL, "INCR", INT2NUM(GL_INCR));
    rb_define_const(mOGL, "DECR", INT2NUM(GL_DECR));
    rb_define_const(mOGL, "NONE", INT2NUM(GL_NONE));
    rb_define_const(mOGL, "LEFT", INT2NUM(GL_LEFT));
    rb_define_const(mOGL, "RIGHT", INT2NUM(GL_RIGHT));
    rb_define_const(mOGL, "FRONT_LEFT", INT2NUM(GL_FRONT_LEFT));
    rb_define_const(mOGL, "FRONT_RIGHT", INT2NUM(GL_FRONT_RIGHT));
    rb_define_const(mOGL, "BACK_LEFT", INT2NUM(GL_BACK_LEFT));
    rb_define_const(mOGL, "BACK_RIGHT", INT2NUM(GL_BACK_RIGHT));
    rb_define_const(mOGL, "AUX0", INT2NUM(GL_AUX0));
    rb_define_const(mOGL, "AUX1", INT2NUM(GL_AUX1));
    rb_define_const(mOGL, "AUX2", INT2NUM(GL_AUX2));
    rb_define_const(mOGL, "AUX3", INT2NUM(GL_AUX3));
    rb_define_const(mOGL, "COLOR_INDEX", INT2NUM(GL_COLOR_INDEX));
    rb_define_const(mOGL, "RED", INT2NUM(GL_RED));
    rb_define_const(mOGL, "GREEN", INT2NUM(GL_GREEN));
    rb_define_const(mOGL, "BLUE", INT2NUM(GL_BLUE));
    rb_define_const(mOGL, "ALPHA", INT2NUM(GL_ALPHA));
    rb_define_const(mOGL, "LUMINANCE", INT2NUM(GL_LUMINANCE));
    rb_define_const(mOGL, "LUMINANCE_ALPHA", INT2NUM(GL_LUMINANCE_ALPHA));
    rb_define_const(mOGL, "ALPHA_BITS", INT2NUM(GL_ALPHA_BITS));
    rb_define_const(mOGL, "RED_BITS", INT2NUM(GL_RED_BITS));
    rb_define_const(mOGL, "GREEN_BITS", INT2NUM(GL_GREEN_BITS));
    rb_define_const(mOGL, "BLUE_BITS", INT2NUM(GL_BLUE_BITS));
    rb_define_const(mOGL, "INDEX_BITS", INT2NUM(GL_INDEX_BITS));
    rb_define_const(mOGL, "SUBPIXEL_BITS", INT2NUM(GL_SUBPIXEL_BITS));
    rb_define_const(mOGL, "AUX_BUFFERS", INT2NUM(GL_AUX_BUFFERS));
    rb_define_const(mOGL, "READ_BUFFER", INT2NUM(GL_READ_BUFFER));
    rb_define_const(mOGL, "DRAW_BUFFER", INT2NUM(GL_DRAW_BUFFER));
    rb_define_const(mOGL, "DOUBLEBUFFER", INT2NUM(GL_DOUBLEBUFFER));
    rb_define_const(mOGL, "STEREO", INT2NUM(GL_STEREO));
    rb_define_const(mOGL, "BITMAP", INT2NUM(GL_BITMAP));
    rb_define_const(mOGL, "COLOR", INT2NUM(GL_COLOR));
    rb_define_const(mOGL, "DEPTH", INT2NUM(GL_DEPTH));
    rb_define_const(mOGL, "STENCIL", INT2NUM(GL_STENCIL));
    rb_define_const(mOGL, "DITHER", INT2NUM(GL_DITHER));
    rb_define_const(mOGL, "RGB", INT2NUM(GL_RGB));
    rb_define_const(mOGL, "RGBA", INT2NUM(GL_RGBA));
    rb_define_const(mOGL, "MAX_LIST_NESTING", INT2NUM(GL_MAX_LIST_NESTING));
    rb_define_const(mOGL, "MAX_ATTRIB_STACK_DEPTH", INT2NUM(GL_MAX_ATTRIB_STACK_DEPTH));
    rb_define_const(mOGL, "MAX_MODELVIEW_STACK_DEPTH", INT2NUM(GL_MAX_MODELVIEW_STACK_DEPTH));
    rb_define_const(mOGL, "MAX_NAME_STACK_DEPTH", INT2NUM(GL_MAX_NAME_STACK_DEPTH));
    rb_define_const(mOGL, "MAX_PROJECTION_STACK_DEPTH", INT2NUM(GL_MAX_PROJECTION_STACK_DEPTH));
    rb_define_const(mOGL, "MAX_TEXTURE_STACK_DEPTH", INT2NUM(GL_MAX_TEXTURE_STACK_DEPTH));
    rb_define_const(mOGL, "MAX_EVAL_ORDER", INT2NUM(GL_MAX_EVAL_ORDER));
    rb_define_const(mOGL, "MAX_LIGHTS", INT2NUM(GL_MAX_LIGHTS));
    rb_define_const(mOGL, "MAX_CLIP_PLANES", INT2NUM(GL_MAX_CLIP_PLANES));
    rb_define_const(mOGL, "MAX_TEXTURE_SIZE", INT2NUM(GL_MAX_TEXTURE_SIZE));
    rb_define_const(mOGL, "MAX_PIXEL_MAP_TABLE", INT2NUM(GL_MAX_PIXEL_MAP_TABLE));
    rb_define_const(mOGL, "MAX_VIEWPORT_DIMS", INT2NUM(GL_MAX_VIEWPORT_DIMS));
    rb_define_const(mOGL, "ATTRIB_STACK_DEPTH", INT2NUM(GL_ATTRIB_STACK_DEPTH));
    rb_define_const(mOGL, "CLIENT_ATTRIB_STACK_DEPTH", INT2NUM(GL_CLIENT_ATTRIB_STACK_DEPTH));
    rb_define_const(mOGL, "COLOR_CLEAR_VALUE", INT2NUM(GL_COLOR_CLEAR_VALUE));
    rb_define_const(mOGL, "COLOR_WRITEMASK", INT2NUM(GL_COLOR_WRITEMASK));
    rb_define_const(mOGL, "CURRENT_INDEX", INT2NUM(GL_CURRENT_INDEX));
    rb_define_const(mOGL, "CURRENT_COLOR", INT2NUM(GL_CURRENT_COLOR));
    rb_define_const(mOGL, "CURRENT_NORMAL", INT2NUM(GL_CURRENT_NORMAL));
    rb_define_const(mOGL, "CURRENT_RASTER_COLOR", INT2NUM(GL_CURRENT_RASTER_COLOR));
    rb_define_const(mOGL, "CURRENT_RASTER_DISTANCE", INT2NUM(GL_CURRENT_RASTER_DISTANCE));
    rb_define_const(mOGL, "CURRENT_RASTER_INDEX", INT2NUM(GL_CURRENT_RASTER_INDEX));
    rb_define_const(mOGL, "CURRENT_RASTER_POSITION", INT2NUM(GL_CURRENT_RASTER_POSITION));
    rb_define_const(mOGL, "CURRENT_RASTER_TEXTURE_COORDS", INT2NUM(GL_CURRENT_RASTER_TEXTURE_COORDS));
    rb_define_const(mOGL, "CURRENT_RASTER_POSITION_VALID", INT2NUM(GL_CURRENT_RASTER_POSITION_VALID));
    rb_define_const(mOGL, "CURRENT_TEXTURE_COORDS", INT2NUM(GL_CURRENT_TEXTURE_COORDS));
    rb_define_const(mOGL, "INDEX_CLEAR_VALUE", INT2NUM(GL_INDEX_CLEAR_VALUE));
    rb_define_const(mOGL, "INDEX_MODE", INT2NUM(GL_INDEX_MODE));
    rb_define_const(mOGL, "INDEX_WRITEMASK", INT2NUM(GL_INDEX_WRITEMASK));
    rb_define_const(mOGL, "MODELVIEW_MATRIX", INT2NUM(GL_MODELVIEW_MATRIX));
    rb_define_const(mOGL, "MODELVIEW_STACK_DEPTH", INT2NUM(GL_MODELVIEW_STACK_DEPTH));
    rb_define_const(mOGL, "NAME_STACK_DEPTH", INT2NUM(GL_NAME_STACK_DEPTH));
    rb_define_const(mOGL, "PROJECTION_MATRIX", INT2NUM(GL_PROJECTION_MATRIX));
    rb_define_const(mOGL, "PROJECTION_STACK_DEPTH", INT2NUM(GL_PROJECTION_STACK_DEPTH));
    rb_define_const(mOGL, "RENDER_MODE", INT2NUM(GL_RENDER_MODE));
    rb_define_const(mOGL, "RGBA_MODE", INT2NUM(GL_RGBA_MODE));
    rb_define_const(mOGL, "TEXTURE_MATRIX", INT2NUM(GL_TEXTURE_MATRIX));
    rb_define_const(mOGL, "TEXTURE_STACK_DEPTH", INT2NUM(GL_TEXTURE_STACK_DEPTH));
    rb_define_const(mOGL, "VIEWPORT", INT2NUM(GL_VIEWPORT));
    rb_define_const(mOGL, "AUTO_NORMAL", INT2NUM(GL_AUTO_NORMAL));
    rb_define_const(mOGL, "MAP1_COLOR_4", INT2NUM(GL_MAP1_COLOR_4));
    rb_define_const(mOGL, "MAP1_GRID_DOMAIN", INT2NUM(GL_MAP1_GRID_DOMAIN));
    rb_define_const(mOGL, "MAP1_GRID_SEGMENTS", INT2NUM(GL_MAP1_GRID_SEGMENTS));
    rb_define_const(mOGL, "MAP1_INDEX", INT2NUM(GL_MAP1_INDEX));
    rb_define_const(mOGL, "MAP1_NORMAL", INT2NUM(GL_MAP1_NORMAL));
    rb_define_const(mOGL, "MAP1_TEXTURE_COORD_1", INT2NUM(GL_MAP1_TEXTURE_COORD_1));
    rb_define_const(mOGL, "MAP1_TEXTURE_COORD_2", INT2NUM(GL_MAP1_TEXTURE_COORD_2));
    rb_define_const(mOGL, "MAP1_TEXTURE_COORD_3", INT2NUM(GL_MAP1_TEXTURE_COORD_3));
    rb_define_const(mOGL, "MAP1_TEXTURE_COORD_4", INT2NUM(GL_MAP1_TEXTURE_COORD_4));
    rb_define_const(mOGL, "MAP1_VERTEX_3", INT2NUM(GL_MAP1_VERTEX_3));
    rb_define_const(mOGL, "MAP1_VERTEX_4", INT2NUM(GL_MAP1_VERTEX_4));
    rb_define_const(mOGL, "MAP2_COLOR_4", INT2NUM(GL_MAP2_COLOR_4));
    rb_define_const(mOGL, "MAP2_GRID_DOMAIN", INT2NUM(GL_MAP2_GRID_DOMAIN));
    rb_define_const(mOGL, "MAP2_GRID_SEGMENTS", INT2NUM(GL_MAP2_GRID_SEGMENTS));
    rb_define_const(mOGL, "MAP2_INDEX", INT2NUM(GL_MAP2_INDEX));
    rb_define_const(mOGL, "MAP2_NORMAL", INT2NUM(GL_MAP2_NORMAL));
    rb_define_const(mOGL, "MAP2_TEXTURE_COORD_1", INT2NUM(GL_MAP2_TEXTURE_COORD_1));
    rb_define_const(mOGL, "MAP2_TEXTURE_COORD_2", INT2NUM(GL_MAP2_TEXTURE_COORD_2));
    rb_define_const(mOGL, "MAP2_TEXTURE_COORD_3", INT2NUM(GL_MAP2_TEXTURE_COORD_3));
    rb_define_const(mOGL, "MAP2_TEXTURE_COORD_4", INT2NUM(GL_MAP2_TEXTURE_COORD_4));
    rb_define_const(mOGL, "MAP2_VERTEX_3", INT2NUM(GL_MAP2_VERTEX_3));
    rb_define_const(mOGL, "MAP2_VERTEX_4", INT2NUM(GL_MAP2_VERTEX_4));
    rb_define_const(mOGL, "COEFF", INT2NUM(GL_COEFF));
    rb_define_const(mOGL, "DOMAIN", INT2NUM(GL_DOMAIN));
    rb_define_const(mOGL, "ORDER", INT2NUM(GL_ORDER));
    rb_define_const(mOGL, "FOG_HINT", INT2NUM(GL_FOG_HINT));
    rb_define_const(mOGL, "LINE_SMOOTH_HINT", INT2NUM(GL_LINE_SMOOTH_HINT));
    rb_define_const(mOGL, "PERSPECTIVE_CORRECTION_HINT", INT2NUM(GL_PERSPECTIVE_CORRECTION_HINT));
    rb_define_const(mOGL, "POINT_SMOOTH_HINT", INT2NUM(GL_POINT_SMOOTH_HINT));
    rb_define_const(mOGL, "POLYGON_SMOOTH_HINT", INT2NUM(GL_POLYGON_SMOOTH_HINT));
    rb_define_const(mOGL, "DONT_CARE", INT2NUM(GL_DONT_CARE));
    rb_define_const(mOGL, "FASTEST", INT2NUM(GL_FASTEST));
    rb_define_const(mOGL, "NICEST", INT2NUM(GL_NICEST));
    rb_define_const(mOGL, "SCISSOR_TEST", INT2NUM(GL_SCISSOR_TEST));
    rb_define_const(mOGL, "SCISSOR_BOX", INT2NUM(GL_SCISSOR_BOX));
    rb_define_const(mOGL, "MAP_COLOR", INT2NUM(GL_MAP_COLOR));
    rb_define_const(mOGL, "MAP_STENCIL", INT2NUM(GL_MAP_STENCIL));
    rb_define_const(mOGL, "INDEX_SHIFT", INT2NUM(GL_INDEX_SHIFT));
    rb_define_const(mOGL, "INDEX_OFFSET", INT2NUM(GL_INDEX_OFFSET));
    rb_define_const(mOGL, "RED_SCALE", INT2NUM(GL_RED_SCALE));
    rb_define_const(mOGL, "RED_BIAS", INT2NUM(GL_RED_BIAS));
    rb_define_const(mOGL, "GREEN_SCALE", INT2NUM(GL_GREEN_SCALE));
    rb_define_const(mOGL, "GREEN_BIAS", INT2NUM(GL_GREEN_BIAS));
    rb_define_const(mOGL, "BLUE_SCALE", INT2NUM(GL_BLUE_SCALE));
    rb_define_const(mOGL, "BLUE_BIAS", INT2NUM(GL_BLUE_BIAS));
    rb_define_const(mOGL, "ALPHA_SCALE", INT2NUM(GL_ALPHA_SCALE));
    rb_define_const(mOGL, "ALPHA_BIAS", INT2NUM(GL_ALPHA_BIAS));
    rb_define_const(mOGL, "DEPTH_SCALE", INT2NUM(GL_DEPTH_SCALE));
    rb_define_const(mOGL, "DEPTH_BIAS", INT2NUM(GL_DEPTH_BIAS));
    rb_define_const(mOGL, "PIXEL_MAP_S_TO_S_SIZE", INT2NUM(GL_PIXEL_MAP_S_TO_S_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_I_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_I_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_R_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_R_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_G_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_G_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_B_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_B_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_A_SIZE", INT2NUM(GL_PIXEL_MAP_I_TO_A_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_R_TO_R_SIZE", INT2NUM(GL_PIXEL_MAP_R_TO_R_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_G_TO_G_SIZE", INT2NUM(GL_PIXEL_MAP_G_TO_G_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_B_TO_B_SIZE", INT2NUM(GL_PIXEL_MAP_B_TO_B_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_A_TO_A_SIZE", INT2NUM(GL_PIXEL_MAP_A_TO_A_SIZE));
    rb_define_const(mOGL, "PIXEL_MAP_S_TO_S", INT2NUM(GL_PIXEL_MAP_S_TO_S));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_I", INT2NUM(GL_PIXEL_MAP_I_TO_I));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_R", INT2NUM(GL_PIXEL_MAP_I_TO_R));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_G", INT2NUM(GL_PIXEL_MAP_I_TO_G));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_B", INT2NUM(GL_PIXEL_MAP_I_TO_B));
    rb_define_const(mOGL, "PIXEL_MAP_I_TO_A", INT2NUM(GL_PIXEL_MAP_I_TO_A));
    rb_define_const(mOGL, "PIXEL_MAP_R_TO_R", INT2NUM(GL_PIXEL_MAP_R_TO_R));
    rb_define_const(mOGL, "PIXEL_MAP_G_TO_G", INT2NUM(GL_PIXEL_MAP_G_TO_G));
    rb_define_const(mOGL, "PIXEL_MAP_B_TO_B", INT2NUM(GL_PIXEL_MAP_B_TO_B));
    rb_define_const(mOGL, "PIXEL_MAP_A_TO_A", INT2NUM(GL_PIXEL_MAP_A_TO_A));
    rb_define_const(mOGL, "PACK_ALIGNMENT", INT2NUM(GL_PACK_ALIGNMENT));
    rb_define_const(mOGL, "PACK_LSB_FIRST", INT2NUM(GL_PACK_LSB_FIRST));
    rb_define_const(mOGL, "PACK_ROW_LENGTH", INT2NUM(GL_PACK_ROW_LENGTH));
    rb_define_const(mOGL, "PACK_SKIP_PIXELS", INT2NUM(GL_PACK_SKIP_PIXELS));
    rb_define_const(mOGL, "PACK_SKIP_ROWS", INT2NUM(GL_PACK_SKIP_ROWS));
    rb_define_const(mOGL, "PACK_SWAP_BYTES", INT2NUM(GL_PACK_SWAP_BYTES));
    rb_define_const(mOGL, "UNPACK_ALIGNMENT", INT2NUM(GL_UNPACK_ALIGNMENT));
    rb_define_const(mOGL, "UNPACK_LSB_FIRST", INT2NUM(GL_UNPACK_LSB_FIRST));
    rb_define_const(mOGL, "UNPACK_ROW_LENGTH", INT2NUM(GL_UNPACK_ROW_LENGTH));
    rb_define_const(mOGL, "UNPACK_SKIP_PIXELS", INT2NUM(GL_UNPACK_SKIP_PIXELS));
    rb_define_const(mOGL, "UNPACK_SKIP_ROWS", INT2NUM(GL_UNPACK_SKIP_ROWS));
    rb_define_const(mOGL, "UNPACK_SWAP_BYTES", INT2NUM(GL_UNPACK_SWAP_BYTES));
    rb_define_const(mOGL, "ZOOM_X", INT2NUM(GL_ZOOM_X));
    rb_define_const(mOGL, "ZOOM_Y", INT2NUM(GL_ZOOM_Y));
    rb_define_const(mOGL, "TEXTURE_ENV", INT2NUM(GL_TEXTURE_ENV));
    rb_define_const(mOGL, "TEXTURE_ENV_MODE", INT2NUM(GL_TEXTURE_ENV_MODE));
    rb_define_const(mOGL, "TEXTURE_1D", INT2NUM(GL_TEXTURE_1D));
    rb_define_const(mOGL, "TEXTURE_2D", INT2NUM(GL_TEXTURE_2D));
    rb_define_const(mOGL, "TEXTURE_WRAP_S", INT2NUM(GL_TEXTURE_WRAP_S));
    rb_define_const(mOGL, "TEXTURE_WRAP_T", INT2NUM(GL_TEXTURE_WRAP_T));
    rb_define_const(mOGL, "TEXTURE_MAG_FILTER", INT2NUM(GL_TEXTURE_MAG_FILTER));
    rb_define_const(mOGL, "TEXTURE_MIN_FILTER", INT2NUM(GL_TEXTURE_MIN_FILTER));
    rb_define_const(mOGL, "TEXTURE_ENV_COLOR", INT2NUM(GL_TEXTURE_ENV_COLOR));
    rb_define_const(mOGL, "TEXTURE_GEN_S", INT2NUM(GL_TEXTURE_GEN_S));
    rb_define_const(mOGL, "TEXTURE_GEN_T", INT2NUM(GL_TEXTURE_GEN_T));
    rb_define_const(mOGL, "TEXTURE_GEN_MODE", INT2NUM(GL_TEXTURE_GEN_MODE));
    rb_define_const(mOGL, "TEXTURE_BORDER_COLOR", INT2NUM(GL_TEXTURE_BORDER_COLOR));
    rb_define_const(mOGL, "TEXTURE_WIDTH", INT2NUM(GL_TEXTURE_WIDTH));
    rb_define_const(mOGL, "TEXTURE_HEIGHT", INT2NUM(GL_TEXTURE_HEIGHT));
    rb_define_const(mOGL, "TEXTURE_BORDER", INT2NUM(GL_TEXTURE_BORDER));
    rb_define_const(mOGL, "TEXTURE_COMPONENTS", INT2NUM(GL_TEXTURE_COMPONENTS));
    rb_define_const(mOGL, "TEXTURE_RED_SIZE", INT2NUM(GL_TEXTURE_RED_SIZE));
    rb_define_const(mOGL, "TEXTURE_GREEN_SIZE", INT2NUM(GL_TEXTURE_GREEN_SIZE));
    rb_define_const(mOGL, "TEXTURE_BLUE_SIZE", INT2NUM(GL_TEXTURE_BLUE_SIZE));
    rb_define_const(mOGL, "TEXTURE_ALPHA_SIZE", INT2NUM(GL_TEXTURE_ALPHA_SIZE));
    rb_define_const(mOGL, "TEXTURE_LUMINANCE_SIZE", INT2NUM(GL_TEXTURE_LUMINANCE_SIZE));
    rb_define_const(mOGL, "TEXTURE_INTENSITY_SIZE", INT2NUM(GL_TEXTURE_INTENSITY_SIZE));
    rb_define_const(mOGL, "NEAREST_MIPMAP_NEAREST", INT2NUM(GL_NEAREST_MIPMAP_NEAREST));
    rb_define_const(mOGL, "NEAREST_MIPMAP_LINEAR", INT2NUM(GL_NEAREST_MIPMAP_LINEAR));
    rb_define_const(mOGL, "LINEAR_MIPMAP_NEAREST", INT2NUM(GL_LINEAR_MIPMAP_NEAREST));
    rb_define_const(mOGL, "LINEAR_MIPMAP_LINEAR", INT2NUM(GL_LINEAR_MIPMAP_LINEAR));
    rb_define_const(mOGL, "OBJECT_LINEAR", INT2NUM(GL_OBJECT_LINEAR));
    rb_define_const(mOGL, "OBJECT_PLANE", INT2NUM(GL_OBJECT_PLANE));
    rb_define_const(mOGL, "EYE_LINEAR", INT2NUM(GL_EYE_LINEAR));
    rb_define_const(mOGL, "EYE_PLANE", INT2NUM(GL_EYE_PLANE));
    rb_define_const(mOGL, "SPHERE_MAP", INT2NUM(GL_SPHERE_MAP));
    rb_define_const(mOGL, "DECAL", INT2NUM(GL_DECAL));
    rb_define_const(mOGL, "MODULATE", INT2NUM(GL_MODULATE));
    rb_define_const(mOGL, "NEAREST", INT2NUM(GL_NEAREST));
    rb_define_const(mOGL, "REPEAT", INT2NUM(GL_REPEAT));
    rb_define_const(mOGL, "CLAMP", INT2NUM(GL_CLAMP));
    rb_define_const(mOGL, "S", INT2NUM(GL_S));
    rb_define_const(mOGL, "T", INT2NUM(GL_T));
    rb_define_const(mOGL, "R", INT2NUM(GL_R));
    rb_define_const(mOGL, "Q", INT2NUM(GL_Q));
    rb_define_const(mOGL, "TEXTURE_GEN_R", INT2NUM(GL_TEXTURE_GEN_R));
    rb_define_const(mOGL, "TEXTURE_GEN_Q", INT2NUM(GL_TEXTURE_GEN_Q));
#if defined(GL_VERSION_1_1)
    rb_define_const(mOGL, "PROXY_TEXTURE_1D", INT2NUM(GL_PROXY_TEXTURE_1D));
    rb_define_const(mOGL, "PROXY_TEXTURE_2D", INT2NUM(GL_PROXY_TEXTURE_2D));
    rb_define_const(mOGL, "TEXTURE_PRIORITY", INT2NUM(GL_TEXTURE_PRIORITY));
    rb_define_const(mOGL, "TEXTURE_RESIDENT", INT2NUM(GL_TEXTURE_RESIDENT));
    rb_define_const(mOGL, "TEXTURE_BINDING_1D", INT2NUM(GL_TEXTURE_BINDING_1D));
    rb_define_const(mOGL, "TEXTURE_BINDING_2D", INT2NUM(GL_TEXTURE_BINDING_2D));
    rb_define_const(mOGL, "TEXTURE_INTERNAL_FORMAT", INT2NUM(GL_TEXTURE_INTERNAL_FORMAT));
#endif /* GL_VERSION_1_1 */

#if defined(GL_VERSION_1_2)
    rb_define_const(mOGL, "PACK_SKIP_IMAGES", INT2NUM(GL_PACK_SKIP_IMAGES));
    rb_define_const(mOGL, "PACK_IMAGE_HEIGHT", INT2NUM(GL_PACK_IMAGE_HEIGHT));
    rb_define_const(mOGL, "UNPACK_SKIP_IMAGES", INT2NUM(GL_UNPACK_SKIP_IMAGES));
    rb_define_const(mOGL, "UNPACK_IMAGE_HEIGHT", INT2NUM(GL_UNPACK_IMAGE_HEIGHT));
    rb_define_const(mOGL, "TEXTURE_3D", INT2NUM(GL_TEXTURE_3D));
    rb_define_const(mOGL, "PROXY_TEXTURE_3D", INT2NUM(GL_PROXY_TEXTURE_3D));
    rb_define_const(mOGL, "TEXTURE_DEPTH", INT2NUM(GL_TEXTURE_DEPTH));
    rb_define_const(mOGL, "TEXTURE_WRAP_R", INT2NUM(GL_TEXTURE_WRAP_R));
    rb_define_const(mOGL, "MAX_3D_TEXTURE_SIZE", INT2NUM(GL_MAX_3D_TEXTURE_SIZE));
    rb_define_const(mOGL, "TEXTURE_BINDING_3D", INT2NUM(GL_TEXTURE_BINDING_3D));
#endif /* GL_VERSION_1_2 */

    rb_define_const(mOGL, "ALPHA4", INT2NUM(GL_ALPHA4));
    rb_define_const(mOGL, "ALPHA8", INT2NUM(GL_ALPHA8));
    rb_define_const(mOGL, "ALPHA12", INT2NUM(GL_ALPHA12));
    rb_define_const(mOGL, "ALPHA16", INT2NUM(GL_ALPHA16));
    rb_define_const(mOGL, "LUMINANCE4", INT2NUM(GL_LUMINANCE4));
    rb_define_const(mOGL, "LUMINANCE8", INT2NUM(GL_LUMINANCE8));
    rb_define_const(mOGL, "LUMINANCE12", INT2NUM(GL_LUMINANCE12));
    rb_define_const(mOGL, "LUMINANCE16", INT2NUM(GL_LUMINANCE16));
    rb_define_const(mOGL, "LUMINANCE4_ALPHA4", INT2NUM(GL_LUMINANCE4_ALPHA4));
    rb_define_const(mOGL, "LUMINANCE6_ALPHA2", INT2NUM(GL_LUMINANCE6_ALPHA2));
    rb_define_const(mOGL, "LUMINANCE8_ALPHA8", INT2NUM(GL_LUMINANCE8_ALPHA8));
    rb_define_const(mOGL, "LUMINANCE12_ALPHA4", INT2NUM(GL_LUMINANCE12_ALPHA4));
    rb_define_const(mOGL, "LUMINANCE12_ALPHA12", INT2NUM(GL_LUMINANCE12_ALPHA12));
    rb_define_const(mOGL, "LUMINANCE16_ALPHA16", INT2NUM(GL_LUMINANCE16_ALPHA16));
    rb_define_const(mOGL, "INTENSITY", INT2NUM(GL_INTENSITY));
    rb_define_const(mOGL, "INTENSITY4", INT2NUM(GL_INTENSITY4));
    rb_define_const(mOGL, "INTENSITY8", INT2NUM(GL_INTENSITY8));
    rb_define_const(mOGL, "INTENSITY12", INT2NUM(GL_INTENSITY12));
    rb_define_const(mOGL, "INTENSITY16", INT2NUM(GL_INTENSITY16));
    rb_define_const(mOGL, "R3_G3_B2", INT2NUM(GL_R3_G3_B2));
    rb_define_const(mOGL, "RGB4", INT2NUM(GL_RGB4));
    rb_define_const(mOGL, "RGB5", INT2NUM(GL_RGB5));
    rb_define_const(mOGL, "RGB8", INT2NUM(GL_RGB8));
    rb_define_const(mOGL, "RGB10", INT2NUM(GL_RGB10));
    rb_define_const(mOGL, "RGB12", INT2NUM(GL_RGB12));
    rb_define_const(mOGL, "RGB16", INT2NUM(GL_RGB16));
    rb_define_const(mOGL, "RGBA2", INT2NUM(GL_RGBA2));
    rb_define_const(mOGL, "RGBA4", INT2NUM(GL_RGBA4));
    rb_define_const(mOGL, "RGB5_A1", INT2NUM(GL_RGB5_A1));
    rb_define_const(mOGL, "RGBA8", INT2NUM(GL_RGBA8));
    rb_define_const(mOGL, "RGB10_A2", INT2NUM(GL_RGB10_A2));
    rb_define_const(mOGL, "RGBA12", INT2NUM(GL_RGBA12));
    rb_define_const(mOGL, "RGBA16", INT2NUM(GL_RGBA16));
    rb_define_const(mOGL, "VENDOR", INT2NUM(GL_VENDOR));
    rb_define_const(mOGL, "RENDERER", INT2NUM(GL_RENDERER));
    rb_define_const(mOGL, "VERSION", INT2NUM(GL_VERSION));
    rb_define_const(mOGL, "EXTENSIONS", INT2NUM(GL_EXTENSIONS));
    rb_define_const(mOGL, "INVALID_VALUE", INT2NUM(GL_INVALID_VALUE));
    rb_define_const(mOGL, "INVALID_ENUM", INT2NUM(GL_INVALID_ENUM));
    rb_define_const(mOGL, "INVALID_OPERATION", INT2NUM(GL_INVALID_OPERATION));
    rb_define_const(mOGL, "STACK_OVERFLOW", INT2NUM(GL_STACK_OVERFLOW));
    rb_define_const(mOGL, "STACK_UNDERFLOW", INT2NUM(GL_STACK_UNDERFLOW));
    rb_define_const(mOGL, "OUT_OF_MEMORY", INT2NUM(GL_OUT_OF_MEMORY));
#if 0
#if defined(CONSTANT_COLOR_EXT)
    rb_define_const(mOGL, "CONSTANT_COLOR_EXT", INT2NUM(GL_CONSTANT_COLOR_EXT));
#endif
#if defined(ONE_MINUS_CONSTANT_COLOR_EXT)
    rb_define_const(mOGL, "ONE_MINUS_CONSTANT_COLOR_EXT", INT2NUM(GL_ONE_MINUS_CONSTANT_COLOR_EXT));
#endif
#if defined(CONSTANT_ALPHA_EXT)
    rb_define_const(mOGL, "CONSTANT_ALPHA_EXT", INT2NUM(GL_CONSTANT_ALPHA_EXT));
#endif
#if defined(ONE_MINUS_CONSTANT_ALPHA_EXT)
    rb_define_const(mOGL, "ONE_MINUS_CONSTANT_ALPHA_EXT", INT2NUM(GL_ONE_MINUS_CONSTANT_ALPHA_EXT));
#endif
#if defined(BLEND_EQUATION_EXT)
    rb_define_const(mOGL, "BLEND_EQUATION_EXT", INT2NUM(GL_BLEND_EQUATION_EXT));
#endif
#if defined(MIN_EXT)
    rb_define_const(mOGL, "MIN_EXT", INT2NUM(GL_MIN_EXT));
#endif
#if defined(MAX_EXT)
    rb_define_const(mOGL, "MAX_EXT", INT2NUM(GL_MAX_EXT));
#endif
#if defined(FUNC_ADD_EXT)
    rb_define_const(mOGL, "FUNC_ADD_EXT", INT2NUM(GL_FUNC_ADD_EXT));
#endif
#if defined(FUNC_SUBTRACT_EXT)
    rb_define_const(mOGL, "FUNC_SUBTRACT_EXT", INT2NUM(GL_FUNC_SUBTRACT_EXT));
#endif
#if defined(FUNC_REVERSE_SUBTRACT_EXT)
    rb_define_const(mOGL, "FUNC_REVERSE_SUBTRACT_EXT", INT2NUM(GL_FUNC_REVERSE_SUBTRACT_EXT));
#endif
#if defined(BLEND_COLOR_EXT)
    rb_define_const(mOGL, "BLEND_COLOR_EXT", INT2NUM(GL_BLEND_COLOR_EXT));
#endif
#if defined(POLYGON_OFFSET_EXT)
    rb_define_const(mOGL, "POLYGON_OFFSET_EXT", INT2NUM(GL_POLYGON_OFFSET_EXT));
#endif
#if defined(POLYGON_OFFSET_FACTOR_EXT)
    rb_define_const(mOGL, "POLYGON_OFFSET_FACTOR_EXT", INT2NUM(GL_POLYGON_OFFSET_FACTOR_EXT));
#endif
#if defined(POLYGON_OFFSET_BIAS_EXT)
    rb_define_const(mOGL, "POLYGON_OFFSET_BIAS_EXT", INT2NUM(GL_POLYGON_OFFSET_BIAS_EXT));
#endif
#if defined(VERTEX_ARRAY_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_EXT", INT2NUM(GL_VERTEX_ARRAY_EXT));
#endif
#if defined(NORMAL_ARRAY_EXT)
    rb_define_const(mOGL, "NORMAL_ARRAY_EXT", INT2NUM(GL_NORMAL_ARRAY_EXT));
#endif
#if defined(COLOR_ARRAY_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_EXT", INT2NUM(GL_COLOR_ARRAY_EXT));
#endif
#if defined(INDEX_ARRAY_EXT)
    rb_define_const(mOGL, "INDEX_ARRAY_EXT", INT2NUM(GL_INDEX_ARRAY_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_EXT)
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_EXT)
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_EXT));
#endif
#if defined(VERTEX_ARRAY_SIZE_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_SIZE_EXT", INT2NUM(GL_VERTEX_ARRAY_SIZE_EXT));
#endif
#if defined(VERTEX_ARRAY_TYPE_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_TYPE_EXT", INT2NUM(GL_VERTEX_ARRAY_TYPE_EXT));
#endif
#if defined(VERTEX_ARRAY_STRIDE_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_STRIDE_EXT", INT2NUM(GL_VERTEX_ARRAY_STRIDE_EXT));
#endif
#if defined(VERTEX_ARRAY_COUNT_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_COUNT_EXT", INT2NUM(GL_VERTEX_ARRAY_COUNT_EXT));
#endif
#if defined(NORMAL_ARRAY_TYPE_EXT)
    rb_define_const(mOGL, "NORMAL_ARRAY_TYPE_EXT", INT2NUM(GL_NORMAL_ARRAY_TYPE_EXT));
#endif
#if defined(NORMAL_ARRAY_STRIDE_EXT)
    rb_define_const(mOGL, "NORMAL_ARRAY_STRIDE_EXT", INT2NUM(GL_NORMAL_ARRAY_STRIDE_EXT));
#endif
#if defined(NORMAL_ARRAY_COUNT_EXT)
    rb_define_const(mOGL, "NORMAL_ARRAY_COUNT_EXT", INT2NUM(GL_NORMAL_ARRAY_COUNT_EXT));
#endif
#if defined(COLOR_ARRAY_SIZE_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_SIZE_EXT", INT2NUM(GL_COLOR_ARRAY_SIZE_EXT));
#endif
#if defined(COLOR_ARRAY_TYPE_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_TYPE_EXT", INT2NUM(GL_COLOR_ARRAY_TYPE_EXT));
#endif
#if defined(COLOR_ARRAY_STRIDE_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_STRIDE_EXT", INT2NUM(GL_COLOR_ARRAY_STRIDE_EXT));
#endif
#if defined(COLOR_ARRAY_COUNT_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_COUNT_EXT", INT2NUM(GL_COLOR_ARRAY_COUNT_EXT));
#endif
#if defined(INDEX_ARRAY_TYPE_EXT)
    rb_define_const(mOGL, "INDEX_ARRAY_TYPE_EXT", INT2NUM(GL_INDEX_ARRAY_TYPE_EXT));
#endif
#if defined(INDEX_ARRAY_STRIDE_EXT)
    rb_define_const(mOGL, "INDEX_ARRAY_STRIDE_EXT", INT2NUM(GL_INDEX_ARRAY_STRIDE_EXT));
#endif
#if defined(INDEX_ARRAY_COUNT_EXT)
    rb_define_const(mOGL, "INDEX_ARRAY_COUNT_EXT", INT2NUM(GL_INDEX_ARRAY_COUNT_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_SIZE_EXT)
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_SIZE_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_SIZE_EXT));
#endif
#if defined(TEXTURE_COORD_ARRAY_TYPE_EXT)
    rb_define_const(mOGL, "TEXTURE_COORD_ARRAY_TYPE_EXT", INT2NUM(GL_TEXTURE_COORD_ARRAY_TYPE_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_STRIDE_EXT)
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_STRIDE_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_STRIDE_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_COUNT_EXT)
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_COUNT_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_COUNT_EXT));
#endif
#if defined(VERTEX_ARRAY_POINTER_EXT)
    rb_define_const(mOGL, "VERTEX_ARRAY_POINTER_EXT", INT2NUM(GL_VERTEX_ARRAY_POINTER_EXT));
#endif
#if defined(NORMAL_ARRAY_POINTER_EXT)
    rb_define_const(mOGL, "NORMAL_ARRAY_POINTER_EXT", INT2NUM(GL_NORMAL_ARRAY_POINTER_EXT));
#endif
#if defined(COLOR_ARRAY_POINTER_EXT)
    rb_define_const(mOGL, "COLOR_ARRAY_POINTER_EXT", INT2NUM(GL_COLOR_ARRAY_POINTER_EXT));
#endif
#if defined(INDEX_ARRAY_POINTER_EXT)
    rb_define_const(mOGL, "INDEX_ARRAY_POINTER_EXT", INT2NUM(GL_INDEX_ARRAY_POINTER_EXT));
#endif
#if defined(EDGE_FLAG_ARRAY_POINTER_EXT)
    rb_define_const(mOGL, "EDGE_FLAG_ARRAY_POINTER_EXT", INT2NUM(GL_EDGE_FLAG_ARRAY_POINTER_EXT));
#endif
#if defined(TEXTURE_PRIORITY_EXT)
    rb_define_const(mOGL, "TEXTURE_PRIORITY_EXT", INT2NUM(GL_TEXTURE_PRIORITY_EXT));
#endif
#if defined(TEXTURE_RESIDENT_EXT)
    rb_define_const(mOGL, "TEXTURE_RESIDENT_EXT", INT2NUM(GL_TEXTURE_RESIDENT_EXT));
#endif
#if defined(TEXTURE_1D_BINDING_EXT)
    rb_define_const(mOGL, "TEXTURE_1D_BINDING_EXT", INT2NUM(GL_TEXTURE_1D_BINDING_EXT));
#endif
#if defined(TEXTURE_2D_BINDING_EXT)
    rb_define_const(mOGL, "TEXTURE_2D_BINDING_EXT", INT2NUM(GL_TEXTURE_2D_BINDING_EXT));
#endif
#if defined(PACK_SKIP_IMAGES_EXT)
    rb_define_const(mOGL, "PACK_SKIP_IMAGES_EXT", INT2NUM(GL_PACK_SKIP_IMAGES_EXT));
#endif
#if defined(PACK_IMAGE_HEIGHT_EXT)
    rb_define_const(mOGL, "PACK_IMAGE_HEIGHT_EXT", INT2NUM(GL_PACK_IMAGE_HEIGHT_EXT));
#endif
#if defined(UNPACK_SKIP_IMAGES_EXT)
    rb_define_const(mOGL, "UNPACK_SKIP_IMAGES_EXT", INT2NUM(GL_UNPACK_SKIP_IMAGES_EXT));
#endif
#if defined(UNPACK_IMAGE_HEIGHT_EXT)
    rb_define_const(mOGL, "UNPACK_IMAGE_HEIGHT_EXT", INT2NUM(GL_UNPACK_IMAGE_HEIGHT_EXT));
#endif
#if defined(TEXTURE_3D_EXT)
    rb_define_const(mOGL, "TEXTURE_3D_EXT", INT2NUM(GL_TEXTURE_3D_EXT));
#endif
#if defined(PROXY_TEXTURE_3D_EXT)
    rb_define_const(mOGL, "PROXY_TEXTURE_3D_EXT", INT2NUM(GL_PROXY_TEXTURE_3D_EXT));
#endif
#if defined(TEXTURE_DEPTH_EXT)
    rb_define_const(mOGL, "TEXTURE_DEPTH_EXT", INT2NUM(GL_TEXTURE_DEPTH_EXT));
#endif
#if defined(TEXTURE_WRAP_R_EXT)
    rb_define_const(mOGL, "TEXTURE_WRAP_R_EXT", INT2NUM(GL_TEXTURE_WRAP_R_EXT));
#endif
#if defined(MAX_3D_TEXTURE_SIZE_EXT)
    rb_define_const(mOGL, "MAX_3D_TEXTURE_SIZE_EXT", INT2NUM(GL_MAX_3D_TEXTURE_SIZE_EXT));
#endif
#if defined(TEXTURE_3D_BINDING_EXT)
    rb_define_const(mOGL, "TEXTURE_3D_BINDING_EXT", INT2NUM(GL_TEXTURE_3D_BINDING_EXT));
#endif
#endif

#if defined(GL_VERSION_1_2)
    rb_define_const(mOGL, "RESCALE_NORMAL", INT2NUM(GL_RESCALE_NORMAL));
    rb_define_const(mOGL, "CLAMP_TO_EDGE", INT2NUM(GL_CLAMP_TO_EDGE));
    rb_define_const(mOGL, "MAX_ELEMENTS_VERTICES", INT2NUM(GL_MAX_ELEMENTS_VERTICES));
    rb_define_const(mOGL, "MAX_ELEMENTS_INDICES", INT2NUM(GL_MAX_ELEMENTS_INDICES));
    rb_define_const(mOGL, "BGR", INT2NUM(GL_BGR));
    rb_define_const(mOGL, "BGRA", INT2NUM(GL_BGRA));
    rb_define_const(mOGL, "UNSIGNED_BYTE_3_3_2", INT2NUM(GL_UNSIGNED_BYTE_3_3_2));
    rb_define_const(mOGL, "UNSIGNED_BYTE_2_3_3_REV", INT2NUM(GL_UNSIGNED_BYTE_2_3_3_REV));
    rb_define_const(mOGL, "UNSIGNED_SHORT_5_6_5", INT2NUM(GL_UNSIGNED_SHORT_5_6_5));
    rb_define_const(mOGL, "UNSIGNED_SHORT_5_6_5_REV", INT2NUM(GL_UNSIGNED_SHORT_5_6_5_REV));
    rb_define_const(mOGL, "UNSIGNED_SHORT_4_4_4_4", INT2NUM(GL_UNSIGNED_SHORT_4_4_4_4));
    rb_define_const(mOGL, "UNSIGNED_SHORT_4_4_4_4_REV", INT2NUM(GL_UNSIGNED_SHORT_4_4_4_4_REV));
    rb_define_const(mOGL, "UNSIGNED_SHORT_5_5_5_1", INT2NUM(GL_UNSIGNED_SHORT_5_5_5_1));
    rb_define_const(mOGL, "UNSIGNED_SHORT_1_5_5_5_REV", INT2NUM(GL_UNSIGNED_SHORT_1_5_5_5_REV));
    rb_define_const(mOGL, "UNSIGNED_INT_8_8_8_8", INT2NUM(GL_UNSIGNED_INT_8_8_8_8));
    rb_define_const(mOGL, "UNSIGNED_INT_8_8_8_8_REV", INT2NUM(GL_UNSIGNED_INT_8_8_8_8_REV));
    rb_define_const(mOGL, "UNSIGNED_INT_10_10_10_2", INT2NUM(GL_UNSIGNED_INT_10_10_10_2));
    rb_define_const(mOGL, "UNSIGNED_INT_2_10_10_10_REV", INT2NUM(GL_UNSIGNED_INT_2_10_10_10_REV));
    rb_define_const(mOGL, "LIGHT_MODEL_COLOR_CONTROL", INT2NUM(GL_LIGHT_MODEL_COLOR_CONTROL));
    rb_define_const(mOGL, "SINGLE_COLOR", INT2NUM(GL_SINGLE_COLOR));
    rb_define_const(mOGL, "SEPARATE_SPECULAR_COLOR", INT2NUM(GL_SEPARATE_SPECULAR_COLOR));
    rb_define_const(mOGL, "TEXTURE_MIN_LOD", INT2NUM(GL_TEXTURE_MIN_LOD));
    rb_define_const(mOGL, "TEXTURE_MAX_LOD", INT2NUM(GL_TEXTURE_MAX_LOD));
    rb_define_const(mOGL, "TEXTURE_BASE_LEVEL", INT2NUM(GL_TEXTURE_BASE_LEVEL));
    rb_define_const(mOGL, "TEXTURE_MAX_LEVEL", INT2NUM(GL_TEXTURE_MAX_LEVEL));
#endif /* GL_VERSION_1_2 */

    rb_define_const(mOGL, "CURRENT_BIT", INT2NUM(GL_CURRENT_BIT));
    rb_define_const(mOGL, "POINT_BIT", INT2NUM(GL_POINT_BIT));
    rb_define_const(mOGL, "LINE_BIT", INT2NUM(GL_LINE_BIT));
    rb_define_const(mOGL, "POLYGON_BIT", INT2NUM(GL_POLYGON_BIT));
    rb_define_const(mOGL, "POLYGON_STIPPLE_BIT", INT2NUM(GL_POLYGON_STIPPLE_BIT));
    rb_define_const(mOGL, "PIXEL_MODE_BIT", INT2NUM(GL_PIXEL_MODE_BIT));
    rb_define_const(mOGL, "LIGHTING_BIT", INT2NUM(GL_LIGHTING_BIT));
    rb_define_const(mOGL, "FOG_BIT", INT2NUM(GL_FOG_BIT));
    rb_define_const(mOGL, "DEPTH_BUFFER_BIT", INT2NUM(GL_DEPTH_BUFFER_BIT));
    rb_define_const(mOGL, "ACCUM_BUFFER_BIT", INT2NUM(GL_ACCUM_BUFFER_BIT));
    rb_define_const(mOGL, "STENCIL_BUFFER_BIT", INT2NUM(GL_STENCIL_BUFFER_BIT));
    rb_define_const(mOGL, "VIEWPORT_BIT", INT2NUM(GL_VIEWPORT_BIT));
    rb_define_const(mOGL, "TRANSFORM_BIT", INT2NUM(GL_TRANSFORM_BIT));
    rb_define_const(mOGL, "ENABLE_BIT", INT2NUM(GL_ENABLE_BIT));
    rb_define_const(mOGL, "COLOR_BUFFER_BIT", INT2NUM(GL_COLOR_BUFFER_BIT));
    rb_define_const(mOGL, "HINT_BIT", INT2NUM(GL_HINT_BIT));
    rb_define_const(mOGL, "EVAL_BIT", INT2NUM(GL_EVAL_BIT));
    rb_define_const(mOGL, "LIST_BIT", INT2NUM(GL_LIST_BIT));
    rb_define_const(mOGL, "TEXTURE_BIT", INT2NUM(GL_TEXTURE_BIT));
    rb_define_const(mOGL, "SCISSOR_BIT", INT2NUM(GL_SCISSOR_BIT));
    rb_define_const(mOGL, "ALL_ATTRIB_BITS", INT2NUM(GL_ALL_ATTRIB_BITS));
#if defined(GL_VERSION_1_1)
    rb_define_const(mOGL, "CLIENT_PIXEL_STORE_BIT", INT2NUM(GL_CLIENT_PIXEL_STORE_BIT));
    rb_define_const(mOGL, "CLIENT_VERTEX_ARRAY_BIT", INT2NUM(GL_CLIENT_VERTEX_ARRAY_BIT));
#ifndef GL_ALL_CLIENT_ATTRIB_BITS
#define GL_ALL_CLIENT_ATTRIB_BITS GL_CLIENT_ALL_ATTRIB_BITS
#endif
    rb_define_const(mOGL, "ALL_CLIENT_ATTRIB_BITS", INT2NUM(GL_ALL_CLIENT_ATTRIB_BITS));
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
