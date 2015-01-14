/*
* Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
* Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
* Copyright (C) 2007 Jan Dvorak <jan.dvorak@kraxnet.cz>
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

#include "common.h"

#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/* OpenGL 1.0 + 1.1 functions */

GL_FUNC_STATIC_2(Accum,GLvoid, GLenum,GLfloat)
GL_FUNC_STATIC_2(AlphaFunc,GLvoid, GLenum,GLclampf)
GL_FUNC_STATIC_1(ArrayElement,GLvoid, GLint)
GL_FUNC_STATIC_2(BindTexture,GLvoid, GLenum,GLuint)
GL_FUNC_STATIC_2(BlendFunc,GLvoid, GLenum,GLenum)
GL_FUNC_STATIC_1(CallList,GLvoid, GLuint)
GL_FUNC_STATIC_1(Clear,GLvoid, GLbitfield)
GL_FUNC_STATIC_4(ClearAccum,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(ClearColor,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_1(ClearDepth,GLvoid, GLclampd)
GL_FUNC_STATIC_1(ClearIndex,GLvoid, GLfloat)
GL_FUNC_STATIC_1(ClearStencil,GLvoid, GLint)
GL_FUNC_STATIC_3(Color3b,GLvoid, GLbyte,GLbyte,GLbyte)
GL_FUNC_STATIC_3(Color3d,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(Color3f,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(Color3i,GLvoid, GLint,GLint,GLint)
GL_FUNC_STATIC_3(Color3s,GLvoid, GLshort,GLshort,GLshort)
GL_FUNC_STATIC_3(Color3ub,GLvoid, GLubyte,GLubyte,GLubyte)
GL_FUNC_STATIC_3(Color3ui,GLvoid, GLuint,GLuint,GLuint)
GL_FUNC_STATIC_3(Color3us,GLvoid, GLushort,GLushort,GLushort)
GL_FUNC_STATIC_4(Color4b,GLvoid, GLbyte,GLbyte,GLbyte,GLbyte)
GL_FUNC_STATIC_4(Color4d,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(Color4f,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(Color4i,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_4(Color4s,GLvoid, GLshort,GLshort,GLshort,GLshort)
GL_FUNC_STATIC_4(Color4ub,GLvoid, GLubyte,GLubyte,GLubyte,GLubyte)
GL_FUNC_STATIC_4(Color4ui,GLvoid, GLuint,GLuint,GLuint,GLuint)
GL_FUNC_STATIC_4(Color4us,GLvoid, GLushort,GLushort,GLushort,GLushort)
GL_FUNC_STATIC_4(ColorMask,GLvoid, GLboolean,GLboolean,GLboolean,GLboolean)
GL_FUNC_STATIC_2(ColorMaterial,GLvoid, GLenum,GLenum)
GL_FUNC_STATIC_5(CopyPixels,GLvoid, GLint,GLint,GLsizei,GLsizei,GLenum)
GL_FUNC_STATIC_7(CopyTexImage1D,GLvoid, GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLint)
GL_FUNC_STATIC_8(CopyTexImage2D,GLvoid, GLenum,GLint,GLenum,GLint,GLint,GLsizei,GLsizei,GLint)
GL_FUNC_STATIC_6(CopyTexSubImage1D,GLvoid, GLenum,GLint,GLint,GLint,GLint,GLsizei)
GL_FUNC_STATIC_8(CopyTexSubImage2D,GLvoid, GLenum,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei)
GL_FUNC_STATIC_1(CullFace,GLvoid, GLenum)
GL_FUNC_STATIC_2(DeleteLists,GLvoid, GLuint,GLuint)
GL_FUNC_STATIC_1(DepthFunc,GLvoid, GLenum)
GL_FUNC_STATIC_1(DepthMask,GLvoid, GLboolean)
GL_FUNC_STATIC_2(DepthRange,GLvoid, GLclampd,GLclampd)
GL_FUNC_STATIC_3(DrawArrays,GLvoid, GLenum,GLint,GLsizei)
GL_FUNC_STATIC_1(DrawBuffer,GLvoid, GLenum)
GL_FUNC_STATIC_1(EdgeFlag,GLvoid, GLboolean)
GL_FUNC_STATIC_1(EvalCoord1d,GLvoid, GLdouble)
GL_FUNC_STATIC_1(EvalCoord1f,GLvoid, GLfloat)
GL_FUNC_STATIC_2(EvalCoord2d,GLvoid, GLdouble,GLdouble)
GL_FUNC_STATIC_2(EvalCoord2f,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_3(EvalMesh1,GLvoid, GLenum,GLint,GLint)
GL_FUNC_STATIC_5(EvalMesh2,GLvoid, GLenum,GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_1(EvalPoint1,GLvoid, GLint)
GL_FUNC_STATIC_2(EvalPoint2,GLvoid, GLint,GLint)
GL_FUNC_STATIC_0(Finish,GLvoid)
GL_FUNC_STATIC_0(Flush,GLvoid)
GL_FUNC_STATIC_2(Fogi,GLvoid, GLenum,GLint)
GL_FUNC_STATIC_2(Fogf,GLvoid, GLenum,GLfloat)
GL_FUNC_STATIC_1(FrontFace,GLvoid, GLenum)
GL_FUNC_STATIC_6(Frustum,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_1(GenLists,GLuint, GLsizei)
GL_FUNC_STATIC_0(GetError,GLenum)
GL_FUNC_STATIC_2(Hint,GLvoid, GLenum,GLenum)
GL_FUNC_STATIC_1(Indexd,GLvoid, GLdouble)
GL_FUNC_STATIC_1(Indexf,GLvoid, GLfloat)
GL_FUNC_STATIC_1(Indexi,GLvoid, GLint)
GL_FUNC_STATIC_1(IndexMask,GLvoid, GLuint)
GL_FUNC_STATIC_1(Indexs,GLvoid, GLshort)
GL_FUNC_STATIC_1(Indexub,GLvoid, GLubyte)
GL_FUNC_STATIC_0(InitNames,GLvoid)
GL_FUNC_STATIC_1(IsEnabled,GLboolean, GLenum)
GL_FUNC_STATIC_1(IsList,GLboolean, GLuint)
GL_FUNC_STATIC_1(IsTexture,GLboolean, GLuint)
GL_FUNC_STATIC_2(LightModelf,GLvoid, GLenum,GLfloat)
GL_FUNC_STATIC_2(LightModeli,GLvoid, GLenum,GLint)
GL_FUNC_STATIC_3(Lightf,GLvoid, GLenum,GLenum,GLfloat)
GL_FUNC_STATIC_3(Lighti,GLvoid, GLenum,GLenum,GLint)
GL_FUNC_STATIC_2(LineStipple,GLvoid, GLint,GLushort)
GL_FUNC_STATIC_1(LineWidth,GLvoid, GLfloat)
GL_FUNC_STATIC_1(ListBase,GLvoid, GLuint)
GL_FUNC_STATIC_0(LoadIdentity,GLvoid)
GL_FUNC_STATIC_1(LoadName,GLvoid, GLuint)
GL_FUNC_STATIC_1(LogicOp,GLvoid, GLenum)
GL_FUNC_STATIC_3(MapGrid1d,GLvoid, GLint,GLdouble,GLdouble)
GL_FUNC_STATIC_3(MapGrid1f,GLvoid, GLint,GLfloat,GLfloat)
GL_FUNC_STATIC_6(MapGrid2d,GLvoid, GLint,GLdouble,GLdouble,GLint,GLdouble,GLdouble)
GL_FUNC_STATIC_6(MapGrid2f,GLvoid, GLint,GLfloat,GLfloat,GLint,GLfloat,GLfloat)
GL_FUNC_STATIC_3(Materialf,GLvoid, GLenum,GLenum,GLfloat)
GL_FUNC_STATIC_3(Materiali,GLvoid, GLenum,GLenum,GLint)
GL_FUNC_STATIC_1(MatrixMode,GLvoid, GLenum)
GL_FUNC_STATIC_3(Normal3b,GLvoid, GLbyte,GLbyte,GLbyte)
GL_FUNC_STATIC_3(Normal3d,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(Normal3f,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(Normal3i,GLvoid, GLint,GLint,GLint)
GL_FUNC_STATIC_3(Normal3s,GLvoid, GLshort,GLshort,GLshort)
GL_FUNC_STATIC_6(Ortho,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_1(PassThrough,GLvoid, GLfloat)
GL_FUNC_STATIC_2(PixelStoref,GLvoid, GLenum,GLfloat)
GL_FUNC_STATIC_2(PixelStorei,GLvoid, GLenum,GLint)
GL_FUNC_STATIC_2(PixelTransferf,GLvoid, GLenum,GLfloat)
GL_FUNC_STATIC_2(PixelTransferi,GLvoid, GLenum,GLint)
GL_FUNC_STATIC_2(PixelZoom,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_1(PointSize,GLvoid, GLfloat)
GL_FUNC_STATIC_2(PolygonMode,GLvoid, GLenum,GLenum)
GL_FUNC_STATIC_2(PolygonOffset,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_0(PopAttrib,GLvoid)
GL_FUNC_STATIC_0(PopClientAttrib,GLvoid)
GL_FUNC_STATIC_0(PopName,GLvoid)
GL_FUNC_STATIC_1(PushAttrib,GLvoid, GLbitfield)
GL_FUNC_STATIC_1(PushClientAttrib,GLvoid, GLbitfield)
GL_FUNC_STATIC_1(PushName,GLvoid, GLuint)
GL_FUNC_STATIC_2(RasterPos2d,GLvoid, GLdouble,GLdouble)
GL_FUNC_STATIC_2(RasterPos2f,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_2(RasterPos2i,GLvoid, GLint,GLint)
GL_FUNC_STATIC_2(RasterPos2s,GLvoid, GLshort,GLshort)
GL_FUNC_STATIC_3(RasterPos3d,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(RasterPos3f,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(RasterPos3i,GLvoid, GLint,GLint,GLint)
GL_FUNC_STATIC_3(RasterPos3s,GLvoid, GLshort,GLshort,GLshort)
GL_FUNC_STATIC_4(RasterPos4d,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(RasterPos4f,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(RasterPos4i,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_4(RasterPos4s,GLvoid, GLshort,GLshort,GLshort,GLshort)
GL_FUNC_STATIC_1(ReadBuffer,GLvoid, GLenum)
GL_FUNC_STATIC_4(Rectd,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(Rectf,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(Recti,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_4(Rects,GLvoid, GLshort,GLshort,GLshort,GLshort)
GL_FUNC_STATIC_1(RenderMode,GLint, GLenum)
GL_FUNC_STATIC_4(Rotated,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(Rotatef,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(Scaled,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(Scalef,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(Scissor,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_1(ShadeModel,GLvoid, GLenum)
GL_FUNC_STATIC_3(StencilFunc,GLvoid, GLenum,GLint,GLuint)
GL_FUNC_STATIC_1(StencilMask,GLvoid, GLuint)
GL_FUNC_STATIC_3(StencilOp,GLvoid, GLenum,GLenum,GLenum)
GL_FUNC_STATIC_1(TexCoord1d,GLvoid, GLdouble)
GL_FUNC_STATIC_1(TexCoord1f,GLvoid, GLfloat)
GL_FUNC_STATIC_1(TexCoord1i,GLvoid, GLint)
GL_FUNC_STATIC_1(TexCoord1s,GLvoid, GLshort)
GL_FUNC_STATIC_2(TexCoord2d,GLvoid, GLdouble,GLdouble)
GL_FUNC_STATIC_2(TexCoord2f,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_2(TexCoord2i,GLvoid, GLint,GLint)
GL_FUNC_STATIC_2(TexCoord2s,GLvoid, GLshort,GLshort)
GL_FUNC_STATIC_3(TexCoord3d,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(TexCoord3f,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(TexCoord3i,GLvoid, GLint,GLint,GLint)
GL_FUNC_STATIC_3(TexCoord3s,GLvoid, GLshort,GLshort,GLshort)
GL_FUNC_STATIC_4(TexCoord4d,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(TexCoord4f,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(TexCoord4i,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_4(TexCoord4s,GLvoid, GLshort,GLshort,GLshort,GLshort)
GL_FUNC_STATIC_3(TexEnvf,GLvoid, GLenum,GLenum,GLfloat)
GL_FUNC_STATIC_3(TexEnvi,GLvoid, GLenum,GLenum,GLint)
GL_FUNC_STATIC_3(TexGend,GLvoid, GLenum,GLenum,GLdouble)
GL_FUNC_STATIC_3(TexGenf,GLvoid, GLenum,GLenum,GLfloat)
GL_FUNC_STATIC_3(TexGeni,GLvoid, GLenum,GLenum,GLint)
GL_FUNC_STATIC_3(TexParameterf,GLvoid, GLenum,GLenum,GLfloat)
GL_FUNC_STATIC_3(TexParameteri,GLvoid, GLenum,GLenum,GLint)
GL_FUNC_STATIC_3(Translated,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(Translatef,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_2(Vertex2d,GLvoid, GLdouble,GLdouble)
GL_FUNC_STATIC_2(Vertex2f,GLvoid, GLfloat,GLfloat)
GL_FUNC_STATIC_2(Vertex2i,GLvoid, GLint,GLint)
GL_FUNC_STATIC_2(Vertex2s,GLvoid, GLshort,GLshort)
GL_FUNC_STATIC_3(Vertex3d,GLvoid, GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_3(Vertex3f,GLvoid, GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_3(Vertex3i,GLvoid, GLint,GLint,GLint)
GL_FUNC_STATIC_3(Vertex3s,GLvoid, GLshort,GLshort,GLshort)
GL_FUNC_STATIC_4(Vertex4d,GLvoid, GLdouble,GLdouble,GLdouble,GLdouble)
GL_FUNC_STATIC_4(Vertex4f,GLvoid, GLfloat,GLfloat,GLfloat,GLfloat)
GL_FUNC_STATIC_4(Vertex4i,GLvoid, GLint,GLint,GLint,GLint)
GL_FUNC_STATIC_4(Vertex4s,GLvoid, GLshort,GLshort,GLshort,GLshort)
GL_FUNC_STATIC_4(Viewport,GLvoid, GLuint,GLuint,GLuint,GLuint)

struct gl_endisable_args {
    VALUE obj;
    VALUE caps;
  };

static VALUE
gl_Enable1(struct gl_endisable_args *args)
{
  long i;
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glEnable,(GLenum cap));

  LOAD_GL_FUNC(glEnable, NULL);
  for (i = 0; i < RARRAY_LEN(args->caps); i++) {
    fptr_glEnable(CONV_GLenum(rb_ary_entry(args->caps, i)));

    CHECK_GLERROR_FROM("glEnable");
  }

  return Qnil;
}

static VALUE
gl_Enable0(struct gl_endisable_args *args)
{
  gl_Enable1(args);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_Disable1(struct gl_endisable_args *args)
{
  long i;
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glDisable,(GLenum cap));

  LOAD_GL_FUNC(glDisable, NULL);
  for (i = 0; i < RARRAY_LEN(args->caps); i++) {
    fptr_glDisable(CONV_GLenum(rb_ary_entry(args->caps, i)));

    CHECK_GLERROR_FROM("glDisable");
  }

  return Qnil;
}

static VALUE
gl_Disable0(struct gl_endisable_args *args)
{
  gl_Disable1(args);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_Enable(int argc, VALUE *argv, VALUE obj)
{
  int i;
  VALUE caps, rev;

  rb_scan_args(argc, argv, "1*", NULL, NULL);

  caps = rb_ary_new2(argc);

  for (i = 0; i < argc; i++)
    rb_ary_push(caps, argv[i]);

  rev = rb_ary_reverse(caps);

  if (rb_block_given_p()){
    struct gl_endisable_args enargs = { obj, caps };
    struct gl_endisable_args disargs = { obj, rev };
    return rb_ensure(gl_Enable0, (VALUE)&enargs, gl_Disable1, (VALUE)&disargs);
  } else {
    struct gl_endisable_args args = { obj, caps };
    gl_Enable0(&args);
  }

  return Qnil;
}

static VALUE
gl_Disable(int argc, VALUE *argv, VALUE obj)
{
  int i;
  VALUE caps, rev;

  rb_scan_args(argc, argv, "1*", NULL, NULL);

  caps = rb_ary_new2(argc);

  for (i = 0; i < argc; i++)
    rb_ary_push(caps, argv[i]);

  rev = rb_ary_reverse(caps);

  if (rb_block_given_p()){
    struct gl_endisable_args disargs = { obj, caps };
    struct gl_endisable_args enargs = { obj, rev };
    return rb_ensure(gl_Disable0, (VALUE)&disargs, gl_Enable1, (VALUE)&enargs);
  } else {
    struct gl_endisable_args args = { obj, caps };
    gl_Disable0(&args);
  }

  return Qnil;
}

struct gl_client_state_args {
    VALUE obj;
    VALUE ary;
  };

static VALUE
gl_EnableClientState1(struct gl_client_state_args *args)
{
  long i;
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glEnableClientState,(GLenum cap));

  LOAD_GL_FUNC(glEnableClientState, NULL);
  for (i = 0; i < RARRAY_LEN(args->ary); i++) {
    fptr_glEnableClientState(CONV_GLenum(rb_ary_entry(args->ary, i)));

    CHECK_GLERROR_FROM("glEnableClientState");
  }

  return Qnil;
}

static VALUE
gl_EnableClientState0(struct gl_client_state_args *args)
{
  gl_EnableClientState1(args);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_DisableClientState1(struct gl_client_state_args *args)
{
  long i;
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glDisableClientState,(GLenum cap));

  LOAD_GL_FUNC(glDisableClientState, NULL);
  for (i = 0; i < RARRAY_LEN(args->ary); i++) {
    fptr_glDisableClientState(CONV_GLenum(rb_ary_entry(args->ary, i)));

    CHECK_GLERROR_FROM("glDisableClientState");
  }

  return Qnil;
}

static VALUE
gl_DisableClientState0(struct gl_client_state_args *args)
{
  gl_DisableClientState1(args);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_EnableClientState(int argc, VALUE *argv, VALUE obj)
{
  int i;
  VALUE ary, rev;

  rb_scan_args(argc, argv, "1*", NULL, NULL);

  ary = rb_ary_new2(argc);

  for (i = 0; i < argc; i++)
    rb_ary_push(ary, argv[i]);

  rev = rb_ary_reverse(ary);

  if (rb_block_given_p()){
    struct gl_client_state_args enargs = { obj, ary };
    struct gl_client_state_args disargs = { obj, rev };
    return rb_ensure(gl_EnableClientState0, (VALUE)&enargs, gl_DisableClientState1, (VALUE)&disargs);
  } else {
    struct gl_client_state_args args = { obj, ary };
    gl_EnableClientState0(&args);
  }

  return Qnil;
}

static VALUE
gl_DisableClientState(int argc, VALUE *argv, VALUE obj)
{
  int i;
  VALUE ary, rev;

  rb_scan_args(argc, argv, "1*", NULL, NULL);

  ary = rb_ary_new2(argc);

  for (i = 0; i < argc; i++)
    rb_ary_push(ary, argv[i]);

  rev = rb_ary_reverse(ary);

  if (rb_block_given_p()){
    struct gl_client_state_args disargs = { obj, ary };
    struct gl_client_state_args enargs = { obj, rev };
    return rb_ensure(gl_DisableClientState0, (VALUE)&disargs, gl_EnableClientState1, (VALUE)&enargs);
  } else {
    struct gl_client_state_args args = { obj, ary };
    gl_DisableClientState0(&args);
  }

  return Qnil;
}

struct gl_begin0_args {
    VALUE obj;
    GLenum mode;
  };

static VALUE
gl_Begin0(struct gl_begin0_args *args)
{
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glBegin,(GLenum mode));

  LOAD_GL_FUNC(glBegin, NULL);
  fptr_glBegin(args->mode);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_End(VALUE obj)
{
  DECL_GL_FUNC_PTR(void,glEnd,(void));

  LOAD_GL_FUNC(glEnd, NULL);
  SET_GLIMPL_VARIABLE(inside_begin_end, Qfalse);

  fptr_glEnd();

  CHECK_GLERROR_FROM("glEnd");

  return Qnil;
}

static VALUE
gl_Begin(VALUE obj, VALUE mode)
{
  struct gl_begin0_args args = { obj, CONV_GLenum(mode) };

  SET_GLIMPL_VARIABLE(inside_begin_end, Qtrue);

  if (rb_block_given_p())
    return rb_ensure(gl_Begin0, (VALUE)&args, gl_End, obj);
  else
    gl_Begin0(&args);

  return Qnil;
}

static VALUE
gl_PopMatrix(VALUE obj)
{
  DECL_GL_FUNC_PTR(void,glPopMatrix,(void));

  LOAD_GL_FUNC(glPopMatrix, NULL);
  fptr_glPopMatrix();

  CHECK_GLERROR_FROM("glPopMatrix");

  return Qnil;
}

static VALUE
gl_PushMatrix0(VALUE obj)
{
  DECL_GL_FUNC_PTR(void,glPushMatrix,(void));

  LOAD_GL_FUNC(glPushMatrix, NULL);
  fptr_glPushMatrix();

  if (rb_block_given_p())
    rb_yield(Qnil);

  return Qnil;
}

static VALUE
gl_PushMatrix(VALUE obj)
{
  if (rb_block_given_p())
    return rb_ensure(gl_PushMatrix0, obj, gl_PopMatrix, obj);
  else {
    DECL_GL_FUNC_PTR(void,glPushMatrix,(void));
    LOAD_GL_FUNC(glPushMatrix, NULL);
    fptr_glPushMatrix();
  }

  return Qnil;
}

struct gl_list_args {
  VALUE obj;
  VALUE list;
  VALUE mode;
};

static VALUE
gl_NewList0(struct gl_list_args *args)
{
  GLuint list;
  GLenum mode;
  VALUE obj = args->obj;
  DECL_GL_FUNC_PTR(void,glNewList,(GLuint list, GLenum mode));

  LOAD_GL_FUNC(glNewList, NULL);
  list = (GLuint)NUM2UINT(args->list);
  mode = RUBY2GLENUM(args->mode);

  fptr_glNewList(list, mode);

  if (rb_block_given_p())
    rb_yield(Qundef);

  return Qnil;
}

static VALUE
gl_EndList(VALUE obj)
{
  DECL_GL_FUNC_PTR(void,glEndList,(void));

  LOAD_GL_FUNC(glEndList, NULL);
  fptr_glEndList();

  return Qnil;
}

static VALUE
gl_NewList(VALUE obj, VALUE list, VALUE mode)
{
  struct gl_list_args args = { obj, list, mode };

  if (rb_block_given_p())
    return rb_ensure(gl_NewList0, (VALUE)&args, gl_EndList, obj);
  else
    gl_NewList0(&args);

  return Qnil;
}

static VALUE
gl_CallLists(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLsizei n;
  GLenum type;
  VALUE lists;
  DECL_GL_FUNC_PTR(GLvoid,glCallLists,(GLsizei n, GLenum type, const GLvoid *lists));

  LOAD_GL_FUNC(glCallLists, NULL);
  type = CONV_GLenum(arg1);
  lists = pack_array_or_pass_string(type,arg2);
  n = (GLsizei)RSTRING_LENINT(lists) / gltype_glformat_unit_size(type,1);
  fptr_glCallLists(n, type, RSTRING_PTR(lists));
  CHECK_GLERROR_FROM("glCallLists");
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
  DECL_GL_FUNC_PTR(void,glBitmap,(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap));

  LOAD_GL_FUNC(glBitmap, NULL);
  width = (GLsizei)NUM2UINT(arg1);
  height = (GLsizei)NUM2UINT(arg2);
  xorig = (GLfloat)NUM2DBL(arg3);
  yorig = (GLfloat)NUM2DBL(arg4);
  xmove = (GLfloat)NUM2DBL(arg5);
  ymove = (GLfloat)NUM2DBL(arg6);
  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glBitmap(width, height, xorig, yorig, xmove, ymove, (GLubyte *)NUM2SIZET(arg7));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg7);

    if ((RSTRING_LEN(data)*8) < (width * height))
      rb_raise(rb_eArgError, "string length:%li", RSTRING_LEN(data));

    fptr_glBitmap(width, height, xorig, yorig, xmove, ymove, (const GLubyte *)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glBitmap");
  return Qnil;
}

static VALUE
gl_EdgeFlagv(obj,arg1)
VALUE obj,arg1;
{
  GLboolean flag[1] = { GL_FALSE };
  DECL_GL_FUNC_PTR(void,glEdgeFlagv,(const GLboolean *flag));

  LOAD_GL_FUNC(glEdgeFlagv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cboolean(arg1,flag,1);
  fptr_glEdgeFlagv(flag);
  CHECK_GLERROR_FROM("glEdgeFlagv");
  return Qnil;
}

static VALUE
gl_Indexdv(obj,arg1)
VALUE obj,arg1;
{
  GLdouble c[1] = {0.0};
  DECL_GL_FUNC_PTR(void,glIndexdv,(const GLdouble *c));

  LOAD_GL_FUNC(glIndexdv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cdbl(arg1,c,1);
  fptr_glIndexdv(c);
  CHECK_GLERROR_FROM("glIndexdv");
  return Qnil;
}

static VALUE
gl_Indexfv(obj,arg1)
VALUE obj,arg1;
{
  GLfloat c[1] = { (GLfloat)0.0 };
  DECL_GL_FUNC_PTR(void,glIndexfv,(const GLfloat *c));

  LOAD_GL_FUNC(glIndexfv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cflt(arg1,c,1);
  fptr_glIndexfv(c);
  CHECK_GLERROR_FROM("glIndexfv");
  return Qnil;
}

static VALUE
gl_Indexiv(obj,arg1)
VALUE obj,arg1;
{
  GLint c[1] = {0};
  DECL_GL_FUNC_PTR(void,glIndexiv,(const GLint *c));

  LOAD_GL_FUNC(glIndexiv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cint(arg1,c,1);
  fptr_glIndexiv(c);
  CHECK_GLERROR_FROM("glIndexiv");
  return Qnil;
}

static VALUE
gl_Indexsv(obj,arg1)
VALUE obj,arg1;
{
  GLshort c[1] = {0};
  DECL_GL_FUNC_PTR(void,glIndexsv,(const GLshort *c));

  LOAD_GL_FUNC(glIndexsv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cshort(arg1,c,1);
  fptr_glIndexsv(c);
  CHECK_GLERROR_FROM("glIndexsv");
  return Qnil;
}

static VALUE
gl_ClipPlane(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum plane;
  GLdouble equation[4];
  DECL_GL_FUNC_PTR(void,glClipPlane,(GLenum plane, const GLdouble *equation));

  LOAD_GL_FUNC(glClipPlane, NULL);
  plane = (GLenum)NUM2INT(arg1);
  Check_Type(arg2,T_ARRAY);
  ary2cdbl(arg2, equation, 4);
  fptr_glClipPlane(plane,equation);
  CHECK_GLERROR_FROM("glClipPlane");
  return Qnil;
}

static VALUE
gl_Fogfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glFogfv,(GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glFogfv, NULL);
  pname = (GLenum)NUM2INT(arg1);
  Check_Type(arg2,T_ARRAY);
  ary2cflt(arg2,params,4);
  fptr_glFogfv(pname,params);
  CHECK_GLERROR_FROM("glFogfv");
  return Qnil;
}

static VALUE
gl_Fogiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glFogiv,(GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glFogiv, NULL);
  pname = (GLenum)NUM2INT(arg1);
  Check_Type(arg2,T_ARRAY);
  ary2cint(arg2,params,4);
  fptr_glFogiv(pname,params);
  CHECK_GLERROR_FROM("glFogiv");
  return Qnil;
}

static VALUE
gl_Lightfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum light;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glLightfv,(GLenum light, GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glLightfv, NULL);
  light = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cflt(arg3,params,4);
  fptr_glLightfv(light,pname,params);
  CHECK_GLERROR_FROM("glLightfv");
  return Qnil;
}

static VALUE
gl_Lightiv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum light;
  GLenum pname;
  GLint params[4]={0,0,0,0};
  DECL_GL_FUNC_PTR(void,glLightiv,(GLenum light, GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glLightiv, NULL);
  light = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cint(arg3,params,4);
  fptr_glLightiv(light,pname,params);
  CHECK_GLERROR_FROM("glLightiv");
  return Qnil;
}

static VALUE
gl_LightModelfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glLightModelfv,(GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glLightModelfv, NULL);
  pname = (GLenum)NUM2INT(arg1);
  Check_Type(arg2,T_ARRAY);
  ary2cflt(arg2,params,4);
  fptr_glLightModelfv(pname,params);
  CHECK_GLERROR_FROM("glLightModelfv");
  return Qnil;
}

static VALUE
gl_LightModeliv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glLightModeliv,(GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glLightModeliv, NULL);
  pname = (GLenum)NUM2INT(arg1);
  Check_Type(arg2,T_ARRAY);
  ary2cint(arg2,params,4);
  fptr_glLightModeliv(pname,params);
  CHECK_GLERROR_FROM("glLightModeliv");
  return Qnil;
}


static VALUE
gl_Materialfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum face;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glMaterialfv,(GLenum face, GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glMaterialfv, NULL);
  face = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cflt(arg3,params,4);
  fptr_glMaterialfv(face,pname,params);
  CHECK_GLERROR_FROM("glMaterialfv");
  return Qnil;
}

static VALUE
gl_Materialiv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum face;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glMaterialiv,(GLenum face, GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glMaterialiv, NULL);
  face = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cint(arg3,params,4);
  fptr_glMaterialiv(face,pname,params);
  CHECK_GLERROR_FROM("glMaterialiv");
  return Qnil;
}

static VALUE
gl_PolygonStipple(obj,arg1)
VALUE obj,arg1;
{
  DECL_GL_FUNC_PTR(void,glPolygonStipple,(const GLubyte *mask));

  LOAD_GL_FUNC(glPolygonStipple, NULL);
  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glPolygonStipple((GLubyte *)NUM2SIZET(arg1));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg1);
    if (RSTRING_LEN(data) < 128)
      rb_raise(rb_eArgError, "string length:%li", RSTRING_LEN(data));

    fptr_glPolygonStipple((GLubyte *)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glPolygonStipple");
  return Qnil;
}


static VALUE
gl_TexParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glTexParameterfv,(GLenum target, GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glTexParameterfv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cflt(arg3,params,4);
  fptr_glTexParameterfv(target,pname,params);
  CHECK_GLERROR_FROM("glTexParameterfv");
  return Qnil;
}

static VALUE
gl_TexParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glTexParameteriv,(GLenum target, GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glTexParameteriv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cint(arg3,params,4);
  fptr_glTexParameteriv(target,pname,params);
  CHECK_GLERROR_FROM("glTexParameteriv");
  return Qnil;
}

static VALUE
gl_TexImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8;
{
  GLenum target;
  GLint level;
  GLint components;
  GLsizei width;
  GLint border;
  GLenum format;
  GLenum type;
  const char *pixels;
  DECL_GL_FUNC_PTR(void,glTexImage1D,(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels));

  LOAD_GL_FUNC(glTexImage1D, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  components = (GLint)NUM2INT(arg3);
  width = (GLsizei)NUM2UINT(arg4);
  border = (GLint)NUM2INT(arg5);
  format = (GLenum)NUM2INT(arg6);
  type = (GLenum)NUM2INT(arg7);

  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glTexImage1D(target,level,components,width,border,format,type,(GLvoid *)NUM2SIZET(arg8));
    CHECK_GLERROR_FROM("glTexImage1D");
    return Qnil;
  }

  if (target == GL_PROXY_TEXTURE_1D || NIL_P(arg8)) { /* proxy texture, no data read */
    pixels = NULL;
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg8);
    CheckDataSize(type,format,width,data);
    pixels = RSTRING_PTR(data);
  }
  fptr_glTexImage1D(target,level,components,width,border,format,type,pixels);
  CHECK_GLERROR_FROM("glTexImage1D");
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
  DECL_GL_FUNC_PTR(void,glTexImage2D,(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels));

  LOAD_GL_FUNC(glTexImage2D, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  components = (GLint)NUM2INT(arg3);
  width = (GLsizei)NUM2UINT(arg4);
  height = (GLsizei)NUM2UINT(arg5);
  border = (GLint)NUM2INT(arg6);
  format = (GLenum)NUM2INT(arg7);
  type = (GLenum)NUM2INT(arg8);

  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glTexImage2D(target,level,components,width,height,border,format,type,(GLvoid *)NUM2SIZET(arg9));
    CHECK_GLERROR_FROM("glTexImage2D");
    return Qnil;
  }

  if (target == GL_PROXY_TEXTURE_2D || target == GL_PROXY_TEXTURE_1D_ARRAY_EXT || target == GL_PROXY_TEXTURE_CUBE_MAP || NIL_P(arg9)) { /* proxy texture, no data read */
    pixels = NULL;
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg9);
    CheckDataSize(type,format,width*height,data);
    pixels = RSTRING_PTR(data);
  }
  fptr_glTexImage2D(target,level,components,width,height,border,format,type,pixels);
  CHECK_GLERROR_FROM("glTexImage2D");
  return Qnil;
}

static VALUE
gl_TexEnvfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glTexEnvfv,(GLenum target, GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glTexEnvfv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cflt(arg3,params,4);
  fptr_glTexEnvfv(target,pname,params);
  CHECK_GLERROR_FROM("glTexEnvfv");
  return Qnil;
}

static VALUE
gl_TexEnviv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glTexEnviv,(GLenum target, GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glTexEnviv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cint(arg3,params,4);
  fptr_glTexEnviv(target,pname,params);
  CHECK_GLERROR_FROM("glTexEnviv");
  return Qnil;
}


static VALUE
gl_TexGendv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum coord;
  GLenum pname;
  GLdouble params[4] = {0.0,0.0,0.0,0.0};
  DECL_GL_FUNC_PTR(void,glTexGendv,(GLenum coord, GLenum pname, const GLdouble *params));

  LOAD_GL_FUNC(glTexGendv, NULL);
  coord = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cdbl(arg3,params,4);
  fptr_glTexGendv(coord,pname,params);
  CHECK_GLERROR_FROM("glTexGendv");
  return Qnil;
}


static VALUE
gl_TexGenfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum coord;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glTexGenfv,(GLenum coord, GLenum pname, const GLfloat *params));

  LOAD_GL_FUNC(glTexGenfv, NULL);
  coord = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cflt(arg3,params,4);
  fptr_glTexGenfv(coord,pname,params);
  CHECK_GLERROR_FROM("glTexGenfv");
  return Qnil;
}


static VALUE
gl_TexGeniv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum coord;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glTexGeniv,(GLenum coord, GLenum pname, const GLint *params));

  LOAD_GL_FUNC(glTexGeniv, NULL);
  coord = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  Check_Type(arg3,T_ARRAY);
  ary2cint(arg3,params,4);
  fptr_glTexGeniv(coord,pname,params);
  CHECK_GLERROR_FROM("glTexGeniv");
  return Qnil;
}
static VALUE
gl_FeedbackBuffer(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLsizei size;
  GLenum type;
  VALUE current_feed_buffer;
  DECL_GL_FUNC_PTR(void,glFeedbackBuffer,(GLsizei size, GLenum type, GLfloat *buffer));

  LOAD_GL_FUNC(glFeedbackBuffer, NULL);
  size = (GLsizei)NUM2UINT(arg1);
  type = (GLenum)NUM2INT(arg2);
  current_feed_buffer = allocate_buffer_with_string(sizeof(GLfloat)*size);
  rb_str_freeze(current_feed_buffer);
  fptr_glFeedbackBuffer(size, type, (GLfloat*)RSTRING_PTR(current_feed_buffer));
  CHECK_GLERROR_FROM("glFeedbackBuffer");
  SET_GLIMPL_VARIABLE(current_feed_buffer, current_feed_buffer);
  return current_feed_buffer;
}

static VALUE
gl_SelectBuffer(obj,arg1)
VALUE obj,arg1;
{
  GLsizei size;
  VALUE current_sel_buffer;
  DECL_GL_FUNC_PTR(void,glSelectBuffer,(GLsizei size, GLuint *buffer));

  LOAD_GL_FUNC(glSelectBuffer, NULL);
  size = (GLsizei)NUM2UINT(arg1);
  current_sel_buffer = allocate_buffer_with_string(sizeof(GLuint)*size);
  rb_str_freeze(current_sel_buffer);
  fptr_glSelectBuffer(size, (GLuint*)RSTRING_PTR(current_sel_buffer));
  CHECK_GLERROR_FROM("glSelectBuffer");
  SET_GLIMPL_VARIABLE(current_sel_buffer, current_sel_buffer);
  return current_sel_buffer;
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
  DECL_GL_FUNC_PTR(void,glMap1d,(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points));

  LOAD_GL_FUNC(glMap1d, NULL);
  target = (GLenum)NUM2INT(arg1);
  u1 = (GLdouble)NUM2DBL(arg2);
  u2 = (GLdouble)NUM2DBL(arg3);
  stride = (GLint)NUM2INT(arg4);
  order = (GLint)NUM2INT(arg5);
  points = ALLOC_N(GLdouble, order*stride);
  work_ary = rb_funcall(arg6,rb_intern("flatten"),0);
  ary2cdbl(work_ary, points, order*stride);
  fptr_glMap1d(target, u1, u2, stride, order, points);
  xfree(points);
  CHECK_GLERROR_FROM("glMap1d");
  return Qnil;
}

static VALUE
gl_Map1f(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
  GLenum target;
  GLfloat u1;
  GLfloat u2;
  GLint stride;
  GLint order;
  GLfloat *points;

  VALUE work_ary;
  DECL_GL_FUNC_PTR(void,glMap1f,(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points));

  LOAD_GL_FUNC(glMap1f, NULL);
  target = (GLenum)NUM2INT(arg1);
  u1 = (GLfloat)NUM2DBL(arg2);
  u2 = (GLfloat)NUM2DBL(arg3);
  stride = (GLint)NUM2INT(arg4);
  order = (GLint)NUM2INT(arg5);
  points = ALLOC_N(GLfloat, order*stride);
  work_ary = rb_funcall(arg6,rb_intern("flatten"),0);
  ary2cflt(work_ary, points, order*stride);
  fptr_glMap1f(target, u1, u2, stride, order, points);
  xfree(points);
  CHECK_GLERROR_FROM("glMap1f");
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
  DECL_GL_FUNC_PTR(void,glMap2d,(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points));

  LOAD_GL_FUNC(glMap2d, NULL);
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
  work_ary = rb_funcall(arg10,rb_intern("flatten"),0);
  ary2cdbl(work_ary, points, MAX(ustride*uorder, vstride*vorder));
  fptr_glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  xfree(points);
  CHECK_GLERROR_FROM("glMap2d");
  return Qnil;
}

static VALUE
gl_Map2f(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10;
{
  GLenum target;
  GLfloat u1;
  GLfloat u2;
  GLint ustride;
  GLint uorder;
  GLfloat v1;
  GLfloat v2;
  GLint vstride;
  GLint vorder;
  GLfloat *points;

  VALUE work_ary;
  DECL_GL_FUNC_PTR(void,glMap2f,(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points));

  LOAD_GL_FUNC(glMap2f, NULL);
  target = (GLenum)NUM2INT(arg1);
  u1 = (GLfloat)NUM2INT(arg2);
  u2 = (GLfloat)NUM2INT(arg3);
  ustride = (GLint)NUM2INT(arg4);
  uorder = (GLint)NUM2INT(arg5);
  v1 = (GLfloat)NUM2INT(arg6);
  v2 = (GLfloat)NUM2INT(arg7);
  vstride = (GLint)NUM2INT(arg8);
  vorder = (GLint)NUM2INT(arg9);
  points = ALLOC_N(GLfloat, MAX(ustride*uorder, vstride*vorder));
  work_ary = rb_funcall(arg10,rb_intern("flatten"),0);
  ary2cflt(work_ary, points, MAX(ustride*uorder, vstride*vorder));
  fptr_glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
  xfree(points);
  CHECK_GLERROR_FROM("glMap2f");
  return Qnil;
}

static VALUE
gl_EvalCoord1dv(obj,arg1)
VALUE obj,arg1;
{
  GLdouble params[1] = {0.0};
  DECL_GL_FUNC_PTR(void,glEvalCoord1dv,(const GLdouble *u));

  LOAD_GL_FUNC(glEvalCoord1dv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cdbl(arg1,params,1);
  fptr_glEvalCoord1dv(params);
  CHECK_GLERROR_FROM("glEvalCoord1dv");
  return Qnil;
}

static VALUE
gl_EvalCoord1fv(obj,arg1)
VALUE obj,arg1;
{
  GLfloat params[1] = {(GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glEvalCoord1fv,(const GLfloat *u));

  LOAD_GL_FUNC(glEvalCoord1fv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cflt(arg1,params,1);
  fptr_glEvalCoord1fv(params);
  CHECK_GLERROR_FROM("glEvalCoord1fv");
  return Qnil;
}

static VALUE
gl_EvalCoord2dv(obj,arg1)
VALUE obj,arg1;
{
  GLdouble params[2] = {0.0,0.0};
  DECL_GL_FUNC_PTR(void,glEvalCoord2dv,(const GLdouble *u));

  LOAD_GL_FUNC(glEvalCoord2dv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cdbl(arg1,params,2);
  fptr_glEvalCoord2dv(params);
  CHECK_GLERROR_FROM("glEvalCoord2fv");
  return Qnil;
}

static VALUE
gl_EvalCoord2fv(obj,arg1)
VALUE obj,arg1;
{
  GLfloat params[2] = {(GLfloat)0.0,(GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glEvalCoord2fv,(const GLfloat *u));

  LOAD_GL_FUNC(glEvalCoord2fv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cflt(arg1,params,2);
  fptr_glEvalCoord2fv(params);
  CHECK_GLERROR_FROM("glEvalCoord2fv");
  return Qnil;
}


#define GLPIXELMAP_FUNC(_type_,_vartype_,_convert_) \
static VALUE \
gl_PixelMap##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  GLenum map; \
  _vartype_ *values; \
  GLsizei size; \
  VALUE args[4]; \
  DECL_GL_FUNC_PTR(void,glPixelMap##_type_##v,(GLenum map, GLsizei mapsize, const _vartype_ *values)); \
  LOAD_GL_FUNC(glPixelMap##_type_##v, NULL); \
  switch(rb_scan_args(argc, argv, "21", &args[0], &args[1], &args[2])) { \
    default: \
    case 2: \
      if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) \
        rb_raise(rb_eArgError, "Pixel unpack buffer bound, but offset argument missing"); \
      map = (GLenum)NUM2INT(args[0]); \
      Check_Type(args[1],T_ARRAY); \
      size = (int)RARRAY_LENINT(args[1]); \
      values = ALLOC_N(_vartype_,size); \
      _convert_(args[1],values,size); \
      fptr_glPixelMap##_type_##v(map,size,values); \
      xfree(values); \
      break; \
    case 3: \
      if (!CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) \
        rb_raise(rb_eArgError, "Pixel unpack buffer not bound"); \
      map = (GLenum)NUM2INT(args[0]);	 \
      size = (GLsizei)NUM2INT(args[1]); \
      fptr_glPixelMap##_type_##v(map,size,(GLvoid *)NUM2SIZET(args[2])); \
      break; \
  } \
  CHECK_GLERROR_FROM("glPixelMap" #_type_ "v"); \
  return Qnil; \
}

GLPIXELMAP_FUNC(f,GLfloat,ary2cflt)
GLPIXELMAP_FUNC(ui,GLuint,ary2cuint)
GLPIXELMAP_FUNC(us,GLushort,ary2cushort)
#undef GLPIXELMAP_FUNC


static VALUE
gl_ReadPixels(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
  GLint x;
  GLint y;
  GLsizei width;
  GLsizei height;
  int format;
  int type;
  VALUE pixels;
  VALUE args[7];
  int numargs;
  DECL_GL_FUNC_PTR(void,glReadPixels,(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels));

  LOAD_GL_FUNC(glReadPixels, NULL);
  numargs = rb_scan_args(argc, argv, "61", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6]);
  x = (GLint)NUM2INT(args[0]);
  y = (GLint)NUM2INT(args[1]);
  width = (GLsizei)NUM2UINT(args[2]);
  height = (GLsizei)NUM2UINT(args[3]);
  format = NUM2INT(args[4]);
  type = NUM2INT(args[5]);

  switch(numargs) {
    default:
    case 6:
      if (CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
        rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");
      pixels = allocate_buffer_with_string(GetDataSize(type,format,width*height));
      FORCE_PIXEL_STORE_MODE
      fptr_glReadPixels(x,y,width,height,format,type,(GLvoid*)RSTRING_PTR(pixels));
      RESTORE_PIXEL_STORE_MODE
      CHECK_GLERROR_FROM("glReadPixels");
      return pixels;
      break;
    case 7:
      if (!CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
        rb_raise(rb_eArgError, "Pixel pack buffer not bound");
      FORCE_PIXEL_STORE_MODE
      fptr_glReadPixels(x,y,width,height,format,type,(GLvoid*)NUM2SIZET(args[6]));
      RESTORE_PIXEL_STORE_MODE
      CHECK_GLERROR_FROM("glReadPixels");
      return Qnil;
      break;
  }
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
  DECL_GL_FUNC_PTR(void,glDrawPixels,(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels));

  LOAD_GL_FUNC(glDrawPixels, NULL);
  width = (GLsizei)NUM2UINT(arg1);
  height = (GLsizei)NUM2UINT(arg2);
  format = (GLenum)NUM2INT(arg3);
  type = (GLenum)NUM2INT(arg4);
  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glDrawPixels(width,height,format,type,(GLvoid *)NUM2SIZET(arg5));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg5);
    CheckDataSize(type,format,width*height,data);
    pixels = RSTRING_PTR(data);
    fptr_glDrawPixels(width,height,format,type,pixels);
  }
  CHECK_GLERROR_FROM("glDrawPixels");
  return Qnil;
}

static VALUE
gl_GetClipPlane(obj,arg1)
VALUE obj,arg1;
{
  GLenum plane;
  GLdouble equation[4] = {0.0,0.0,0.0,0.0};
  VALUE retary;
  int i;
  DECL_GL_FUNC_PTR(void,glGetClipPlane,(GLenum plane, GLdouble *equation));

  LOAD_GL_FUNC(glGetClipPlane, NULL);
  plane = (GLenum)NUM2INT(arg1);
  fptr_glGetClipPlane(plane,equation);
  retary = rb_ary_new2(4);
  for(i=0;i<4;i++)
    rb_ary_push(retary, rb_float_new(equation[i]));
  CHECK_GLERROR_FROM("glGetClipPlane");
  return retary;
}

#define GLGET_FUNC(_name_,_type_,_conv_) \
static VALUE \
gl_Get##_name_##v(obj,arg1) \
VALUE obj,arg1; \
{ \
  GLenum pname; \
  int nitems; \
  VALUE ary, ary2; \
  int i,j; \
  _type_ items[64];  \
  DECL_GL_FUNC_PTR(void,glGet##_name_##v,(GLenum pname, _type_ *params)); \
  LOAD_GL_FUNC(glGet##_name_##v, NULL); \
  pname = NUM2INT(arg1); \
  switch(pname) { \
  case GL_ACCUM_CLEAR_VALUE: \
  case GL_BLEND_COLOR: \
  case GL_COLOR_CLEAR_VALUE: \
  case GL_COLOR_WRITEMASK: \
  case GL_CURRENT_COLOR: \
  case GL_CURRENT_RASTER_COLOR: \
  case GL_CURRENT_RASTER_POSITION: \
  case GL_CURRENT_RASTER_SECONDARY_COLOR: \
  case GL_CURRENT_RASTER_TEXTURE_COORDS: \
  case GL_CURRENT_TEXTURE_COORDS: \
  case GL_FOG_COLOR: \
  case GL_LIGHT_MODEL_AMBIENT: \
  case GL_MAP2_GRID_DOMAIN: \
  case GL_CURRENT_SECONDARY_COLOR: \
  case GL_SCISSOR_BOX: \
  case GL_TEXTURE_ENV_COLOR: \
  case GL_VIEWPORT: \
  case GL_REFERENCE_PLANE_EQUATION_SGIX: \
  case GL_FOG_OFFSET_VALUE_SGIX: \
  case GL_TEXTURE_ENV_BIAS_SGIX: \
  case GL_CULL_VERTEX_OBJECT_POSITION_EXT: \
  case GL_CULL_VERTEX_EYE_POSITION_EXT: \
  case GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX: \
  case GL_CONSTANT_COLOR0_NV: \
  case GL_CONSTANT_COLOR1_NV: \
  case GL_TEXTURE_COLOR_WRITEMASK_SGIS: \
  case GL_FLOAT_CLEAR_COLOR_VALUE_NV: \
  case GL_RGBA_SIGNED_COMPONENTS_EXT: \
    nitems = 4; \
    break; \
  case GL_CURRENT_NORMAL: \
  case GL_POINT_DISTANCE_ATTENUATION: \
  case GL_SPRITE_AXIS_SGIX: \
  case GL_SPRITE_TRANSLATION_SGIX: \
  case GL_CURRENT_RASTER_NORMAL_SGIX: \
  case GL_CURRENT_TANGENT_EXT: \
  case GL_CURRENT_BINORMAL_EXT: \
    nitems = 3; \
    break; \
  case GL_DEPTH_RANGE:	 \
  case GL_LINE_WIDTH_RANGE: \
  case GL_MAP1_GRID_DOMAIN: \
  case GL_MAP2_GRID_SEGMENTS: \
  case GL_MAX_VIEWPORT_DIMS: \
  case GL_POINT_SIZE_RANGE: \
  case GL_POLYGON_MODE: \
  case GL_ALIASED_LINE_WIDTH_RANGE: \
  case GL_ALIASED_POINT_SIZE_RANGE: \
  case GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX: \
  case GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX: \
  case GL_FOG_FUNC_SGIS: \
  case GL_DEPTH_BOUNDS_EXT: \
    nitems = 2; \
    break; \
  case GL_MODELVIEW_MATRIX: \
  case GL_PROJECTION_MATRIX: \
  case GL_TEXTURE_MATRIX: \
  case GL_COLOR_MATRIX: \
  case GL_TRANSPOSE_MODELVIEW_MATRIX: \
  case GL_TRANSPOSE_PROJECTION_MATRIX: \
  case GL_TRANSPOSE_TEXTURE_MATRIX: \
  case GL_TRANSPOSE_COLOR_MATRIX: \
  case GL_TRANSPOSE_CURRENT_MATRIX_ARB: \
  case GL_MODELVIEW0_ARB: \
  case GL_MODELVIEW1_ARB: \
  case GL_MODELVIEW2_ARB: \
  case GL_MODELVIEW3_ARB: \
  case GL_MODELVIEW4_ARB: \
  case GL_MODELVIEW5_ARB: \
  case GL_MODELVIEW6_ARB: \
  case GL_MODELVIEW7_ARB: \
  case GL_MODELVIEW8_ARB: \
  case GL_MODELVIEW9_ARB: \
  case GL_MODELVIEW10_ARB: \
  case GL_MODELVIEW11_ARB: \
  case GL_MODELVIEW12_ARB: \
  case GL_MODELVIEW13_ARB: \
  case GL_MODELVIEW14_ARB: \
  case GL_MODELVIEW15_ARB: \
  case GL_MODELVIEW16_ARB: \
  case GL_MODELVIEW17_ARB: \
  case GL_MODELVIEW18_ARB: \
  case GL_MODELVIEW19_ARB: \
  case GL_MODELVIEW20_ARB: \
  case GL_MODELVIEW21_ARB: \
  case GL_MODELVIEW22_ARB: \
  case GL_MODELVIEW23_ARB: \
  case GL_MODELVIEW24_ARB: \
  case GL_MODELVIEW25_ARB: \
  case GL_MODELVIEW26_ARB: \
  case GL_MODELVIEW27_ARB: \
  case GL_MODELVIEW28_ARB: \
  case GL_MODELVIEW29_ARB: \
  case GL_MODELVIEW30_ARB: \
  case GL_MODELVIEW31_ARB: \
  case GL_MATRIX_PALETTE_ARB: \
  case GL_PIXEL_TRANSFORM_2D_MATRIX_EXT: \
  case GL_MODELVIEW1_MATRIX_EXT: \
  case GL_CURRENT_MATRIX_NV: \
    fptr_glGet##_name_##v(pname, items); \
    ary = rb_ary_new2(4); \
    for (i = 0; i < 4; i++) { \
      ary2 = rb_ary_new2(4); \
      rb_ary_push(ary, ary2); \
      for (j = 0; j < 4; j++) \
        rb_ary_push(ary2, _conv_(items[i*4+j])); \
    } \
    CHECK_GLERROR_FROM("glGet" #_name_ "v"); \
    return ary; \
  case GL_POLYGON_STIPPLE: \
    fptr_glGet##_name_##v(pname, items); \
    CHECK_GLERROR_FROM("glGet" #_name_ "v"); \
    return rb_str_new((const char*)items, 32); \
  case GL_COMPRESSED_TEXTURE_FORMATS: \
    { \
      DECL_GL_FUNC_PTR(void,glGetIntegerv,(GLenum pname, GLint *params)); \
      LOAD_GL_FUNC(glGetIntegerv, NULL); \
      fptr_glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &nitems); \
      CHECK_GLERROR_FROM("glGetIntegerv"); \
      if (nitems<=0||nitems>64) \
        return INT2NUM(0); \
    } \
    break; \
  default: /* size=1 */ \
    fptr_glGet##_name_##v(pname, items); \
    CHECK_GLERROR_FROM("glGet" #_name_ "v"); \
    return _conv_(items[0]); \
  } \
  fptr_glGet##_name_##v(pname, items); \
  ary = rb_ary_new2(nitems); \
  for (i = 0; i < nitems; i++) \
    rb_ary_push(ary, _conv_(items[i])); \
  CHECK_GLERROR_FROM("glGet" #_name_ "v"); \
  return ary; \
}

GLGET_FUNC(Double,GLdouble,rb_float_new)
GLGET_FUNC(Float,GLfloat,rb_float_new)
GLGET_FUNC(Integer,GLint,INT2NUM)
GLGET_FUNC(Boolean,GLboolean,GLBOOL2RUBY)

#undef GLGET_FUNC


static VALUE
gl_GetLightfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum light;
  GLenum pname;
  GLsizei size;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  DECL_GL_FUNC_PTR(void,glGetLightfv,(GLenum light, GLenum pname, GLfloat *params));

  LOAD_GL_FUNC(glGetLightfv, NULL);
  light = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_AMBIENT:
    case GL_DIFFUSE:
    case GL_SPECULAR:
    case GL_POSITION:
      size = 4;
      break;
    case GL_SPOT_DIRECTION:
      size = 3;
      break;
    case GL_CONSTANT_ATTENUATION:
    case GL_LINEAR_ATTENUATION:
    case GL_QUADRATIC_ATTENUATION:
    case GL_SPOT_EXPONENT:
    case GL_SPOT_CUTOFF:
      size = 1;
      break;
    default:
      rb_raise(rb_eArgError, "unknown pname:%d",pname);
      break; /* not reached */
  }
  fptr_glGetLightfv(light,pname,params);
  RET_ARRAY_OR_SINGLE("glGetLightfv", size, rb_float_new, params);
}

static VALUE
gl_GetLightiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum light;
  GLenum pname;
  GLsizei size;
  GLint params[4] = {0,0,0,0};
  DECL_GL_FUNC_PTR(void,glGetLightiv,(GLenum light, GLenum pname, GLint *params));

  LOAD_GL_FUNC(glGetLightiv, NULL);
  light = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_AMBIENT:
    case GL_DIFFUSE:
    case GL_SPECULAR:
    case GL_POSITION:
      size = 4;
      break;
    case GL_SPOT_DIRECTION:
      size = 3;
      break;
    case GL_CONSTANT_ATTENUATION:
    case GL_LINEAR_ATTENUATION:
    case GL_QUADRATIC_ATTENUATION:
    case GL_SPOT_EXPONENT:
    case GL_SPOT_CUTOFF:
      size = 1;
      break;
    default:
      rb_raise(rb_eArgError, "unknown pname:%d",pname);
      break; /* not reached */
  }
  fptr_glGetLightiv(light,pname,params);
  RET_ARRAY_OR_SINGLE("glGetLightiv", size, INT2NUM, params);
}

#define GETMAP_FUNC(_name_,_type_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLenum target; \
  GLenum query; \
  int dims; \
  int pointsize; \
  int size=0; \
  _type_ *points; \
  GLint order[2] = {0,0}; /* for GL_COEFF, [order] or [uorder,vorder] (MAP1/MAP2) */ \
  DECL_GL_FUNC_PTR(void,gl##_name_,(GLenum target, GLenum query, _type_ *v)); \
  LOAD_GL_FUNC(gl##_name_, NULL); \
  target = (GLenum)NUM2INT(arg1); \
  query = (GLenum)NUM2INT(arg2); \
  switch(target) { \
    case GL_MAP1_INDEX: \
    case GL_MAP1_TEXTURE_COORD_1: dims=1; pointsize=1; break; \
    case GL_MAP1_TEXTURE_COORD_2: dims=1; pointsize=2; break; \
    case GL_MAP1_VERTEX_3: \
    case GL_MAP1_NORMAL: \
    case GL_MAP1_TEXTURE_COORD_3: dims=1; pointsize=3; break; \
    case GL_MAP1_COLOR_4: \
    case GL_MAP1_TEXTURE_COORD_4: \
    case GL_MAP1_VERTEX_4: dims=1; pointsize=4; break; \
    case GL_MAP2_INDEX: \
    case GL_MAP2_TEXTURE_COORD_1: dims=2; pointsize=1; break; \
    case GL_MAP2_TEXTURE_COORD_2: dims=2; pointsize=2; break; \
    case GL_MAP2_VERTEX_3: \
    case GL_MAP2_NORMAL:  \
    case GL_MAP2_TEXTURE_COORD_3: dims=2; pointsize=3; break; \
    case GL_MAP2_COLOR_4:  \
    case GL_MAP2_TEXTURE_COORD_4: \
    case GL_MAP2_VERTEX_4: dims=2; pointsize=4; break; \
    default: \
      rb_raise(rb_eArgError, "unknown target:%d",target); \
      break; /* not reached */ \
  } \
  switch(query) { \
    case GL_ORDER: size = dims;	break; \
    case GL_DOMAIN: size = dims*2; break; \
    case GL_COEFF: \
      { \
        DECL_GL_FUNC_PTR(void,glGetMapiv,(GLenum target, GLenum query, GLint *v)); \
        LOAD_GL_FUNC(glGetMapiv, NULL); \
        fptr_glGetMapiv(target,GL_ORDER,order); \
        CHECK_GLERROR_FROM("glGetMapiv"); \
        if (dims==1) \
          size = order[0] * pointsize; \
        else \
          size = (order[0]*order[1]) * pointsize; \
      } \
      break; \
    default: \
      rb_raise(rb_eArgError, "unknown target:%d",target); \
      break; /* not reached */ \
  } \
  points = ALLOC_N(_type_,size); \
  fptr_gl##_name_(target,query,points); \
\
  RET_ARRAY_OR_SINGLE_FREE("gl" #_name_, size, RETCONV_##_type_, points); \
}

GETMAP_FUNC(GetMapdv,GLdouble)
GETMAP_FUNC(GetMapfv,GLfloat)
GETMAP_FUNC(GetMapiv,GLint)
#undef GETMAP_FUNC

static VALUE
gl_GetMaterialfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum face;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  int size;
  DECL_GL_FUNC_PTR(void,glGetMaterialfv,(GLenum face, GLenum pname, GLfloat *params));

  LOAD_GL_FUNC(glGetMaterialfv, NULL);
  face = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_AMBIENT:
    case GL_DIFFUSE:
    case GL_SPECULAR:
    case GL_EMISSION:
      size = 4;
      break;
    case GL_COLOR_INDEXES:
      size = 3;
      break;
    case GL_SHININESS:
      size = 1;
      break;
    default:
      rb_raise(rb_eArgError, "unknown pname:%d",pname);
      break; /* not reached */
  }
  fptr_glGetMaterialfv(face,pname,params);
  RET_ARRAY_OR_SINGLE("glGetMaterialfv", size, rb_float_new, params);
}

static VALUE
gl_GetMaterialiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum face;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  int size;
  DECL_GL_FUNC_PTR(void,glGetMaterialiv,(GLenum face, GLenum pname, GLint *params));

  LOAD_GL_FUNC(glGetMaterialiv, NULL);
  face = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_AMBIENT:
    case GL_DIFFUSE:
    case GL_SPECULAR:
    case GL_EMISSION:
      size = 4;
      break;
    case GL_COLOR_INDEXES:
      size = 3;
      break;
    case GL_SHININESS:
      size = 1;
      break;
    default:
      rb_raise(rb_eArgError, "unknown pname:%d",pname);
      break; /* not reached */
  }
  fptr_glGetMaterialiv(face,pname,params);
  RET_ARRAY_OR_SINGLE("glGetMaterialiv", size, INT2NUM, params);
}

#define GLGETPIXELMAP_FUNC(_type_,_vartype_,_convert_) \
static VALUE \
gl_GetPixelMap##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  GLenum map; \
  GLenum map_size; \
  GLint size = 0; \
  _vartype_ *values; \
  VALUE args[2]; \
  DECL_GL_FUNC_PTR(void,glGetPixelMap##_type_##v,(GLenum map, _vartype_ *values)); \
  LOAD_GL_FUNC(glGetPixelMap##_type_##v, NULL); \
  switch (rb_scan_args(argc, argv, "11", &args[0], &args[1])) { \
    default: \
    case 1: \
      if (CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING)) \
        rb_raise(rb_eArgError, \
            "Pixel pack buffer bound, but offset argument missing"); \
\
      map = (GLenum)NUM2INT(args[0]); \
      switch(map) { \
        case GL_PIXEL_MAP_I_TO_I: map_size=GL_PIXEL_MAP_I_TO_I_SIZE; break; \
        case GL_PIXEL_MAP_S_TO_S: map_size=GL_PIXEL_MAP_S_TO_S_SIZE; break; \
        case GL_PIXEL_MAP_I_TO_R: map_size=GL_PIXEL_MAP_I_TO_R_SIZE; break; \
        case GL_PIXEL_MAP_I_TO_G: map_size=GL_PIXEL_MAP_I_TO_G_SIZE; break; \
        case GL_PIXEL_MAP_I_TO_B: map_size=GL_PIXEL_MAP_I_TO_B_SIZE; break; \
        case GL_PIXEL_MAP_I_TO_A: map_size=GL_PIXEL_MAP_I_TO_A_SIZE; break; \
        case GL_PIXEL_MAP_R_TO_R: map_size=GL_PIXEL_MAP_R_TO_R_SIZE; break; \
        case GL_PIXEL_MAP_G_TO_G: map_size=GL_PIXEL_MAP_G_TO_G_SIZE; break; \
        case GL_PIXEL_MAP_B_TO_B: map_size=GL_PIXEL_MAP_B_TO_B_SIZE; break; \
        case GL_PIXEL_MAP_A_TO_A: map_size=GL_PIXEL_MAP_A_TO_A_SIZE; break; \
        default: \
          rb_raise(rb_eArgError, "unknown map:%d",map); \
          break; \
      } \
      { \
        DECL_GL_FUNC_PTR(void,glGetIntegerv,(GLenum pname, GLint *params)); \
        LOAD_GL_FUNC(glGetIntegerv, NULL); \
        fptr_glGetIntegerv(map_size,&size); \
      } \
      CHECK_GLERROR_FROM("glGetIntegerv"); \
      values = ALLOC_N(_vartype_,size); \
      fptr_glGetPixelMap##_type_##v(map,values); \
      RET_ARRAY_OR_SINGLE_FREE("glGetPixelMap" #_type_ "v", size, _convert_, \
          values); \
      break; \
    case 2: \
      if (!CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING)) \
        rb_raise(rb_eArgError, "Pixel pack buffer not bound"); \
\
      map = (GLenum)NUM2INT(args[0]); \
      fptr_glGetPixelMap##_type_##v(map,(GLvoid*)NUM2SIZET(args[1])); \
      CHECK_GLERROR_FROM("glGetPixelMap" #_type_ "v"); \
      return Qnil; \
  } \
}

GLGETPIXELMAP_FUNC(f,GLfloat,rb_float_new)
GLGETPIXELMAP_FUNC(ui,GLuint,INT2NUM)
GLGETPIXELMAP_FUNC(us,GLushort,INT2NUM)
#undef GLGETPIXELMAP_FUNC

static VALUE
gl_GetPolygonStipple(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
  VALUE args[1];
  GLubyte mask[128];
  DECL_GL_FUNC_PTR(void,glGetPolygonStipple,(GLubyte *mask));

  LOAD_GL_FUNC(glGetPolygonStipple, NULL);
  switch(rb_scan_args(argc, argv, "01", &args[0])) {
    default:
    case 0:
      if (CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
        rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");
      memset(mask, 0x0, sizeof(GLubyte)*128);
      FORCE_PIXEL_STORE_MODE
      fptr_glGetPolygonStipple(mask);
      RESTORE_PIXEL_STORE_MODE
      CHECK_GLERROR_FROM("glGetPolygonStipple");
      return rb_str_new((const char*)mask, 128);
    case 1:
      if (!CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
        rb_raise(rb_eArgError, "Pixel pack buffer not bound");
      fptr_glGetPolygonStipple((GLvoid *)NUM2SIZET(args[0]));
      CHECK_GLERROR_FROM("glGetPolygonStipple");
      return Qnil;
  }
}

static VALUE
gl_GetString(obj,arg1)
VALUE obj,arg1;
{
  GLenum name;
  const GLubyte *ret;
  DECL_GL_FUNC_PTR(const GLubyte *,glGetString,(GLenum name));

  LOAD_GL_FUNC(glGetString, NULL);
  name = (GLenum)NUM2INT(arg1);
  ret = fptr_glGetString(name);
  CHECK_GLERROR_FROM("glGetString");
  return rb_str_new2((const char*)ret);
}

#define GETTEXENVFUNC(_name_,_type_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLenum target; \
  GLenum pname; \
  _type_ params[4] = {(_type_)0.0, (_type_)0.0, (_type_)0.0, (_type_)0.0}; \
  int size; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum target, GLenum pname, _type_ *params)); \
  LOAD_GL_FUNC(gl##_name_, NULL); \
  target = (GLenum)NUM2INT(arg1); \
  pname = (GLenum)NUM2INT(arg2); \
  switch(pname) { \
    case GL_TEXTURE_ENV_COLOR: \
    case GL_TEXTURE_ENV_BIAS_SGIX: \
    case GL_CULL_MODES_NV: \
    case GL_OFFSET_TEXTURE_MATRIX_NV: \
      size = 4; \
      break; \
    case GL_CONST_EYE_NV: \
      size = 3; \
      break; \
    default: \
      size = 1; \
      break; \
  } \
  fptr_gl##_name_(target,pname,params); \
  RET_ARRAY_OR_SINGLE("gl" #_name_, size, RETCONV_##_type_, params); \
}

GETTEXENVFUNC(GetTexEnvfv,GLfloat)
GETTEXENVFUNC(GetTexEnviv,GLint)
#undef GETTEXENVFUNC

#define GETTEXGENFUNC(_name_,_type_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLenum coord; \
  GLenum pname; \
  _type_ params[4] = {(_type_)0.0, (_type_)0.0, (_type_)0.0, (_type_)0.0}; \
  int size; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum coord, GLenum pname, _type_ *params)); \
  LOAD_GL_FUNC(gl##_name_, NULL); \
  coord = (GLenum)NUM2INT(arg1); \
  pname = (GLenum)NUM2INT(arg2); \
  switch(pname) { \
    case GL_OBJECT_PLANE: \
    case GL_EYE_PLANE: \
      size = 4; \
      break; \
    default: \
      size = 1; \
      break; \
  } \
  fptr_gl##_name_(coord,pname,params); \
  RET_ARRAY_OR_SINGLE("gl" #_name_, size, RETCONV_##_type_, params); \
}

GETTEXGENFUNC(GetTexGendv,GLdouble)
GETTEXGENFUNC(GetTexGenfv,GLfloat)
GETTEXGENFUNC(GetTexGeniv,GLint)
#undef GETTEXGENFUNC

static VALUE
gl_GetTexImage(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
  GLenum tex;
  GLint lod;
  GLenum format;
  GLenum type;
  GLint width = 0;
  GLint height = 0;
  GLint depth = 0;
  GLint size4d = 0;
  GLint size;
  VALUE pixels;
  VALUE args[5];
  int numargs;
  DECL_GL_FUNC_PTR(void,glGetTexImage,(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels));

  LOAD_GL_FUNC(glGetTexImage, NULL);
  numargs = rb_scan_args(argc, argv, "41", &args[0], &args[1], &args[2], &args[3], &args[4]);
  tex = (GLenum)NUM2INT(args[0]);
  lod = (GLint)NUM2INT(args[1]);
  format = (GLenum)NUM2INT(args[2]);
  type = (GLenum)NUM2INT(args[3]);
  switch(numargs) {
    default:
    case 4:
      {
        DECL_GL_FUNC_PTR(void,glGetTexLevelParameteriv,(GLenum target, GLint level, GLenum pname, GLint *params));
        LOAD_GL_FUNC(glGetTexLevelParameteriv, NULL);
        if (CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
          rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");

        size = 1;
        switch(tex) {
          case GL_TEXTURE_4D_SGIS:
            fptr_glGetTexLevelParameteriv(tex,lod,GL_TEXTURE_4DSIZE_SGIS,&size4d);
            size *= size4d;
            /* fall through */
          case GL_TEXTURE_3D:
          case GL_TEXTURE_1D_STACK_MESAX:
          case GL_TEXTURE_2D_STACK_MESAX:
            fptr_glGetTexLevelParameteriv(tex,lod,GL_TEXTURE_DEPTH,&depth);
            size *= depth;
            /* fall through */
          case GL_TEXTURE_2D:
          case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
          case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
          case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
          case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
          case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
          case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
          case GL_TEXTURE_RECTANGLE_ARB:
          case GL_DETAIL_TEXTURE_2D_SGIS:
            fptr_glGetTexLevelParameteriv(tex,lod,GL_TEXTURE_HEIGHT,&height);
            size *= height;
            /* fall through */
          case GL_TEXTURE_1D:
            fptr_glGetTexLevelParameteriv(tex,lod,GL_TEXTURE_WIDTH,&width);
            size *= width;
            break;
          default:
            rb_raise(rb_eArgError, "Target type not supported");
        }
        CHECK_GLERROR_FROM("glGetTexLevelParameteriv");
        pixels = allocate_buffer_with_string(GetDataSize(type,format,size));

        FORCE_PIXEL_STORE_MODE
        fptr_glGetTexImage(tex,lod,format,type,(GLvoid*)RSTRING_PTR(pixels));
        RESTORE_PIXEL_STORE_MODE
        CHECK_GLERROR_FROM("glGetTexImage");
        return pixels;
      }
      break;
    case 5:
      if (!CHECK_BUFFER_BINDING(GL_PIXEL_PACK_BUFFER_BINDING))
        rb_raise(rb_eArgError, "Pixel pack buffer not bound");

      FORCE_PIXEL_STORE_MODE
      fptr_glGetTexImage(tex,lod,format,type,(GLvoid*)NUM2SIZET(args[4]));
      RESTORE_PIXEL_STORE_MODE
      CHECK_GLERROR_FROM("glGetTexImage");
    return Qnil;
  }
}

static VALUE
gl_GetTexParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum target;
  GLenum pname;
  GLfloat params[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0};
  int size;
  DECL_GL_FUNC_PTR(void,glGetTexParameterfv,(GLenum target, GLenum pname, GLfloat *params));

  LOAD_GL_FUNC(glGetTexParameterfv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_TEXTURE_BORDER_COLOR:
    case GL_TEXTURE_BORDER_VALUES_NV:
    case GL_POST_TEXTURE_FILTER_BIAS_SGIX:
    case GL_POST_TEXTURE_FILTER_SCALE_SGIX:
      size = 4;
      break;
    default:
      size = 1;
      break;
  }
  fptr_glGetTexParameterfv(target,pname,params);
  RET_ARRAY_OR_SINGLE("glGetTexParameterfv", size, RETCONV_GLfloat, params);
}

static VALUE
gl_GetTexParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLenum target;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  int size;
  DECL_GL_FUNC_PTR(void,glGetTexParameteriv,(GLenum target, GLenum pname, GLint *params));

  LOAD_GL_FUNC(glGetTexParameteriv, NULL);
  target = (GLenum)NUM2INT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  switch(pname) {
    case GL_TEXTURE_BORDER_COLOR:
    case GL_TEXTURE_BORDER_VALUES_NV:
    case GL_POST_TEXTURE_FILTER_BIAS_SGIX:
    case GL_POST_TEXTURE_FILTER_SCALE_SGIX:
      size = 4;
      break;
    default:
      size = 1;
      break;
  }
  fptr_glGetTexParameteriv(target,pname,params);
  RET_ARRAY_OR_SINGLE_BOOL("glGetTexParameteriv", size, cond_GLBOOL2RUBY,
      pname, params);
}

static VALUE
gl_GetTexLevelParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLint level;
  GLenum pname;
  GLfloat params = (GLfloat)0.0;
  DECL_GL_FUNC_PTR(void,glGetTexLevelParameterfv,(GLenum target, GLint level, GLenum pname, GLfloat *params));

  LOAD_GL_FUNC(glGetTexLevelParameterfv, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  pname = (GLenum)NUM2INT(arg3);
  fptr_glGetTexLevelParameterfv(target,level,pname,&params);
  CHECK_GLERROR_FROM("glGetTexLevelParameterfv");
  return RETCONV_GLfloat(params);
}

static VALUE
gl_GetTexLevelParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum target;
  GLint level;
  GLenum pname;
  GLint params = 0;
  DECL_GL_FUNC_PTR(void,glGetTexLevelParameteriv,(GLenum target, GLint level, GLenum pname, GLint *params));

  LOAD_GL_FUNC(glGetTexLevelParameteriv, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  pname = (GLenum)NUM2INT(arg3);
  fptr_glGetTexLevelParameteriv(target,level,pname,&params);
  CHECK_GLERROR_FROM("glGetTexLevelParameteriv");
  return cond_GLBOOL2RUBY(pname,params);
}


static VALUE
gl_LoadMatrixf(obj,arg1)
VALUE obj,arg1;
{
  GLfloat m[4*4];
  DECL_GL_FUNC_PTR(void,glLoadMatrixf,(const GLfloat *m));

  LOAD_GL_FUNC(glLoadMatrixf, NULL);
  ary2cmatfloat(arg1, m, 4, 4);
  fptr_glLoadMatrixf(m);
  CHECK_GLERROR_FROM("glLoadMatrixf");
  return Qnil;
}

static VALUE
gl_LoadMatrixd(obj,arg1)
VALUE obj,arg1;
{
  GLdouble m[4*4];
  DECL_GL_FUNC_PTR(void,glLoadMatrixd,(const GLdouble *m));

  LOAD_GL_FUNC(glLoadMatrixd, NULL);
  ary2cmatdouble(arg1, m, 4, 4);
  fptr_glLoadMatrixd(m);
  CHECK_GLERROR_FROM("glLoadMatrixd");
  return Qnil;
}

static VALUE
gl_MultMatrixf(obj,arg1)
VALUE obj,arg1;
{
  GLfloat m[4*4];
  DECL_GL_FUNC_PTR(void,glMultMatrixf,(const GLfloat *m));

  LOAD_GL_FUNC(glMultMatrixf, NULL);
  ary2cmatfloat(arg1, m, 4, 4);
  fptr_glMultMatrixf(m);
  CHECK_GLERROR_FROM("glMultMatrixf");
  return Qnil;
}

static VALUE
gl_MultMatrixd(obj,arg1)
VALUE obj,arg1;
{
  GLdouble m[4*4];
  DECL_GL_FUNC_PTR(void,glMultMatrixd,(const GLdouble *m));

  LOAD_GL_FUNC(glMultMatrixd, NULL);
  ary2cmatdouble(arg1, m, 4, 4);
  fptr_glMultMatrixd(m);
  CHECK_GLERROR_FROM("glMultMatrixd");
  return Qnil;
}


#define POINTER_FUNC(_func_) \
static VALUE \
gl_##_func_##Pointer(obj, arg1, arg2, arg3, arg4) \
VALUE obj, arg1, arg2, arg3, arg4; \
{ \
  GLint size; \
  GLenum type; \
  GLsizei stride; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_func_##Pointer,(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)); \
  LOAD_GL_FUNC(gl##_func_##Pointer, NULL); \
  size = (GLint)NUM2INT(arg1); \
  type = (GLenum)NUM2INT(arg2); \
  stride = (GLsizei)NUM2UINT(arg3); \
  if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) { \
    SET_GLIMPL_VARIABLE(_func_##_ptr, arg4); \
    fptr_gl##_func_##Pointer(size, type, stride, (const GLvoid*)NUM2SIZET(arg4)); \
  } else { \
    VALUE data; \
    data = pack_array_or_pass_string(type,arg4); \
    rb_str_freeze(data); \
    SET_GLIMPL_VARIABLE(_func_##_ptr, data); \
    fptr_gl##_func_##Pointer(size, type, stride, (const GLvoid*)RSTRING_PTR(data)); \
  } \
  CHECK_GLERROR_FROM("gl" #_func_ "Pointer"); \
  return Qnil; \
}

POINTER_FUNC(Vertex)
POINTER_FUNC(Color)
POINTER_FUNC(TexCoord)

#undef POINTER_FUNC

static VALUE
gl_DrawElements(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
  GLenum mode;
  GLsizei count;
  GLenum type;
  DECL_GL_FUNC_PTR(void,glDrawElements,(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices));

  LOAD_GL_FUNC(glDrawElements, NULL);
  mode = (GLenum)NUM2INT(arg1);
  count = (GLsizei)NUM2UINT(arg2);
  type = (GLenum)NUM2INT(arg3);
  if (CHECK_BUFFER_BINDING(GL_ELEMENT_ARRAY_BUFFER_BINDING)) {
    fptr_glDrawElements(mode, count, type, (const GLvoid*)NUM2SIZET(arg4));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg4);
    fptr_glDrawElements(mode, count, type, (const GLvoid*)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glDrawElements");
  return Qnil;
}

static VALUE
gl_EdgeFlagPointer(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLsizei stride;
  DECL_GL_FUNC_PTR(void,glEdgeFlagPointer,(GLsizei stride, const GLvoid *ptr));

  LOAD_GL_FUNC(glEdgeFlagPointer, NULL);
  stride = (GLsizei)NUM2UINT(arg1);
  if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) {
    SET_GLIMPL_VARIABLE(EdgeFlag_ptr, arg2);
    fptr_glEdgeFlagPointer(stride, (const GLvoid*) NUM2SIZET(arg2));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg2);
    rb_str_freeze(data);
    SET_GLIMPL_VARIABLE(EdgeFlag_ptr, data);
    fptr_glEdgeFlagPointer(stride, (const GLvoid*)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glEdgeFlagPointer");
  return Qnil;
}

static VALUE
gl_GetPointerv(obj,arg1)
VALUE obj,arg1;
{
  GLenum pname;

  pname = (GLenum)NUM2INT(arg1);
  switch (pname) {
    case GL_VERTEX_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(Vertex_ptr);
    case GL_NORMAL_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(Normal_ptr);
    case GL_COLOR_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(Color_ptr);
    case GL_INDEX_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(Index_ptr);
    case GL_TEXTURE_COORD_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(TexCoord_ptr);
    case GL_EDGE_FLAG_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(EdgeFlag_ptr);
    case GL_FOG_COORD_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(FogCoord_ptr);
    case GL_SECONDARY_COLOR_ARRAY_POINTER:
      return GET_GLIMPL_VARIABLE(SecondaryColor_ptr);
    case GL_FEEDBACK_BUFFER_POINTER:
      return GET_GLIMPL_VARIABLE(current_feed_buffer);
    case GL_SELECTION_BUFFER_POINTER:
      return GET_GLIMPL_VARIABLE(current_sel_buffer);
    default:
      rb_raise(rb_eArgError, "Invalid pname %d",pname);
      break; /* not reached */
  }
  return Qnil;
}

static VALUE
gl_IndexPointer(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum type;
  GLsizei stride;
  DECL_GL_FUNC_PTR(void,glIndexPointer,(GLenum type, GLsizei stride, const GLvoid *ptr));

  LOAD_GL_FUNC(glIndexPointer, NULL);
  type = (GLenum)NUM2INT(arg1);
  stride = (GLsizei)NUM2UINT(arg2);
  if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) {
    SET_GLIMPL_VARIABLE(Index_ptr, arg3);
    fptr_glIndexPointer(type, stride, (const GLvoid*)NUM2SIZET(arg3));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg3);
    SET_GLIMPL_VARIABLE(Index_ptr, data);
    fptr_glIndexPointer(type, stride, (const GLvoid*)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glIndexPointer");
  return Qnil;
}

static VALUE
gl_InterleavedArrays(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum format;
  GLsizei stride;
  VALUE data;
  DECL_GL_FUNC_PTR(void,glInterleavedArrays,(GLenum format, GLsizei stride, const GLvoid *pointer));

  LOAD_GL_FUNC(glInterleavedArrays, NULL);
  format = (GLenum)NUM2INT(arg1);
  stride = (GLsizei)NUM2UINT(arg2);
  /* FIXME: add support for GL_C4UB_V2F,GL_C4UB_V3F, GL_T2F_C4UB_V3 */
  data = pack_array_or_pass_string(GL_FLOAT,arg3);
  rb_str_freeze(data);
  fptr_glInterleavedArrays(format, stride, (const GLvoid*)RSTRING_PTR(data));
  CHECK_GLERROR_FROM("glInterleavedArrays");
  return Qnil;
}

static VALUE
gl_NormalPointer(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLenum type;
  GLsizei stride;
  DECL_GL_FUNC_PTR(void,glNormalPointer,(GLenum type, GLsizei stride, const GLvoid *ptr));

  LOAD_GL_FUNC(glNormalPointer, NULL);
  type = (GLenum)NUM2INT(arg1);
  stride = (GLsizei)NUM2UINT(arg2);
  if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) {
    SET_GLIMPL_VARIABLE(Normal_ptr, arg3);
    fptr_glNormalPointer(type, stride, (const GLvoid*)NUM2SIZET(arg3));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg3);
    rb_str_freeze(data);
    SET_GLIMPL_VARIABLE(Normal_ptr, data);
    fptr_glNormalPointer(type, stride, (const GLvoid*)RSTRING_PTR(data));
  }
  CHECK_GLERROR_FROM("glNormalPointer");
  return Qnil;
}


static VALUE
gl_TexSubImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
  GLenum target;
  GLint level;
  GLint xoffset;
  GLsizei width;
  GLenum format;
  GLenum type;
  VALUE data;
  DECL_GL_FUNC_PTR(void,glTexSubImage1D,(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels));

  LOAD_GL_FUNC(glTexSubImage1D, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  xoffset = (GLint)NUM2INT(arg3);
  width = (GLsizei)NUM2UINT(arg4);
  format = (GLenum)NUM2INT(arg5);
  type = (GLenum)NUM2INT(arg6);

  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glTexSubImage1D(target,level,xoffset,width,format,type,(GLvoid *)NUM2SIZET(arg7));
    CHECK_GLERROR_FROM("glTexSubImage1D");
    return Qnil;
  }

  data = pack_array_or_pass_string(type,arg7);
  CheckDataSize(type,format,width,data);

  fptr_glTexSubImage1D(target,level,xoffset,width,format,type,RSTRING_PTR(data));
  CHECK_GLERROR_FROM("glTexSubImage1D");
  return Qnil;
}

static VALUE
gl_TexSubImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
  GLenum target;
  GLint level;
  GLint xoffset;
  GLint yoffset;
  GLsizei width;
  GLsizei height;
  GLenum format;
  GLenum type;
  VALUE data;
  DECL_GL_FUNC_PTR(void,glTexSubImage2D,(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels));

  LOAD_GL_FUNC(glTexSubImage2D, NULL);
  target = (GLenum)NUM2INT(arg1);
  level = (GLint)NUM2INT(arg2);
  xoffset = (GLint)NUM2INT(arg3);
  yoffset = (GLint)NUM2INT(arg4);
  width = (GLsizei)NUM2UINT(arg5);
  height = (GLsizei)NUM2UINT(arg6);
  format = (GLenum)NUM2INT(arg7);
  type = (GLenum)NUM2INT(arg8);

  if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
    fptr_glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,(GLvoid *)NUM2SIZET(arg9));
    CHECK_GLERROR_FROM("glTexSubImage2D");
    return Qnil;
  }

  data = pack_array_or_pass_string(type,arg9);
  CheckDataSize(type,format,width*height,data);

  fptr_glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,RSTRING_PTR(data));
  CHECK_GLERROR_FROM("glTexSubImage2D");
  return Qnil;
}

static VALUE
gl_AreTexturesResident(obj,arg1)
VALUE obj,arg1;
{
  GLuint *textures;
  GLboolean *residences;
  GLsizei size;
  GLboolean r;
  VALUE retary;
  VALUE ary;
  int i;
  DECL_GL_FUNC_PTR(GLboolean,glAreTexturesResident,(GLsizei n, const GLuint *textures, GLboolean *residences));

  LOAD_GL_FUNC(glAreTexturesResident, NULL);
  ary = rb_Array(arg1);
  size = (int)RARRAY_LENINT(ary);
  textures = ALLOC_N(GLuint,size);
  residences = ALLOC_N(GLboolean,size);
  ary2cuint(ary,textures,size);
  r = fptr_glAreTexturesResident(size,textures,residences);
  retary = rb_ary_new2(size);
  if (r==GL_TRUE) { /* all are resident */
    for(i=0;i<size;i++)
      rb_ary_push(retary, GLBOOL2RUBY(GL_TRUE));
  } else {
    for(i=0;i<size;i++)
      rb_ary_push(retary, GLBOOL2RUBY(residences[i]));
  }
  xfree(textures);
  xfree(residences);
  CHECK_GLERROR_FROM("glAreTexturesResident");
  return retary;
}

GL_FUNC_GENOBJECTS(GenTextures)
GL_FUNC_DELETEOBJECTS(DeleteTextures)

static VALUE
gl_PrioritizeTextures(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint *textures;
  GLclampf *priorities;
  GLsizei size;
  DECL_GL_FUNC_PTR(void,glPrioritizeTextures,(GLsizei n, const GLuint *textures, const GLclampf *priorities));

  LOAD_GL_FUNC(glPrioritizeTextures, NULL);
  Check_Type(arg1,T_ARRAY);
  Check_Type(arg2,T_ARRAY);
  if ((size = (GLsizei)RARRAY_LENINT(arg1)) != (GLsizei)RARRAY_LENINT(arg2))
    rb_raise(rb_eArgError, "passed arrays must have the same length");
  textures = ALLOC_N(GLuint,size);
  priorities = ALLOC_N(GLclampf,size);
  ary2cuint(arg1,textures,size);
  ary2cflt(arg2,priorities,size);
  fptr_glPrioritizeTextures(size,textures,priorities);
  xfree(textures);
  xfree(priorities);
  CHECK_GLERROR_FROM("glPrioritizeTextures");
  return Qnil;
}

static VALUE
gl_Indexubv(obj,arg1)
VALUE obj,arg1;
{
  GLubyte c[1] = {0};
  DECL_GL_FUNC_PTR(void,glIndexubv,(const GLubyte *c));

  LOAD_GL_FUNC(glIndexubv, NULL);
  Check_Type(arg1,T_ARRAY);
  ary2cubyte(arg1,c,1);
  fptr_glIndexubv(c);
  CHECK_GLERROR_FROM("glIndexubv");
  return Qnil;
}


/* additional functions */

#define GLCOLOR_VFUNC(_type_) \
static VALUE \
gl_Color##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  int num; \
  VALUE args[4]; \
  VALUE ary; \
  switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) { \
  case 1: \
    ary = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    switch (RARRAY_LEN(ary)) { \
      case 3: \
      gl_Color3##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
      break; \
      case 4: \
      gl_Color4##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2],RARRAY_PTR(ary)[3]); \
      break; \
      default: \
      rb_raise(rb_eArgError, "array length:%li", RARRAY_LEN(ary)); \
    } \
    break; \
  case 3: \
    gl_Color3##_type_(obj,args[0], args[1], args[2]); \
    break; \
  case 4: \
    gl_Color4##_type_(obj,args[0], args[1], args[2], args[3]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "arg length:%d", num); \
  } \
  return Qnil; \
}

GLCOLOR_VFUNC(b)
GLCOLOR_VFUNC(d)
GLCOLOR_VFUNC(f)
GLCOLOR_VFUNC(i)
GLCOLOR_VFUNC(s)
GLCOLOR_VFUNC(ub)
GLCOLOR_VFUNC(ui)
GLCOLOR_VFUNC(us)
#undef GLCOLOR_VFUNC

#define GLNORMAL_VFUNC(_type_) \
static VALUE \
gl_Normal##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  int num; \
  VALUE args[3]; \
  VALUE ary; \
  switch (num = rb_scan_args(argc, argv, "12", &args[0], &args[1], &args[2])) { \
  case 1: \
    ary = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    switch (RARRAY_LEN(ary)) { \
      case 3: \
      gl_Normal3##_type_(obj,RARRAY_PTR(ary)[0], RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
      break; \
      default: \
      rb_raise(rb_eArgError, "array length: %li", RARRAY_LEN(ary)); \
    } \
    break; \
  case 3: \
    gl_Normal3##_type_(obj,args[0], args[1], args[2]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "arg length:%d",num); \
  } \
  return Qnil; \
}

GLNORMAL_VFUNC(b)
GLNORMAL_VFUNC(d)
GLNORMAL_VFUNC(f)
GLNORMAL_VFUNC(i)
GLNORMAL_VFUNC(s)
#undef GLNORMAL_VFUNC

#define GLRASTERPOS_VFUNC(_type_) \
static VALUE \
gl_RasterPos##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  int num; \
  VALUE args[4]; \
  VALUE ary; \
  switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) { \
  case 1: \
    ary = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    switch (RARRAY_LEN(ary)) { \
      case 2: \
      gl_RasterPos2##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1]); \
      break; \
      case 3: \
      gl_RasterPos3##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
      break; \
      case 4: \
      gl_RasterPos4##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2],RARRAY_PTR(ary)[3]); \
      break; \
      default: \
      rb_raise(rb_eArgError, "array length:%d", num); \
    } \
    break; \
  case 2: \
    gl_RasterPos2##_type_(obj,args[0], args[1]); \
    break; \
  case 3: \
    gl_RasterPos3##_type_(obj,args[0], args[1], args[2]); \
    break; \
  case 4: \
    gl_RasterPos4##_type_(obj,args[0], args[1], args[2], args[3]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "too many arguments"); \
  } \
  return Qnil; \
}

GLRASTERPOS_VFUNC(d)
GLRASTERPOS_VFUNC(f)
GLRASTERPOS_VFUNC(i)
GLRASTERPOS_VFUNC(s)
#undef GLRASTERPOS_VFUNC

#define GLRECT_VFUNC(_type_) \
static VALUE \
gl_Rect##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  int num; \
  VALUE args[4]; \
  VALUE ary1, ary2; \
  switch (num = rb_scan_args(argc, argv, "22", &args[0], &args[1], &args[2], &args[3])) { \
  case 2: \
    ary1 = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    ary2 = rb_convert_type(args[1], T_ARRAY, "Array", "to_a"); \
    if (RARRAY_LEN(ary1) != 2) \
      rb_raise(rb_eArgError, "first array must be of length 2 (was %li)", \
          RARRAY_LEN(ary1)); \
\
    if (RARRAY_LEN(ary2) != 2) \
      rb_raise(rb_eArgError, "second array must be of length 2 (was %li)", \
          RARRAY_LEN(ary2)); \
\
    gl_Rect##_type_(obj, \
        RARRAY_PTR(ary1)[0], RARRAY_PTR(ary1)[1], \
        RARRAY_PTR(ary2)[0], RARRAY_PTR(ary2)[1]); \
    break; \
  case 4: \
    gl_Rect##_type_(obj,args[0], args[1], args[2], args[3]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "arg length: %d", num); \
  } \
  return Qnil; \
}

GLRECT_VFUNC(d)
GLRECT_VFUNC(f)
GLRECT_VFUNC(i)
GLRECT_VFUNC(s)
#undef GLRECT_VFUNC

#define GLTEXCOORD_VFUNC(_type_) \
static VALUE \
gl_TexCoord##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  int num; \
  VALUE args[4]; \
  VALUE ary; \
  switch (num = rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) { \
  case 1: \
    ary = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    switch (RARRAY_LEN(ary)) { \
      case 1: \
      gl_TexCoord1##_type_(obj,RARRAY_PTR(ary)[0]); \
      break; \
      case 2: \
      gl_TexCoord2##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1]); \
      break; \
      case 3: \
      gl_TexCoord3##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
      break; \
      case 4: \
      gl_TexCoord4##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2],RARRAY_PTR(ary)[3]); \
      break; \
      default: \
        rb_raise(rb_eArgError, "array length: %d", num); \
    } \
    break; \
  case 2: \
    gl_TexCoord2##_type_(obj,args[0], args[1]); \
    break; \
  case 3: \
    gl_TexCoord3##_type_(obj,args[0], args[1], args[2]); \
    break; \
  case 4: \
    gl_TexCoord4##_type_(obj,args[0], args[1], args[2], args[3]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "too many arguments"); \
    break; \
  } \
  return Qnil; \
}

GLTEXCOORD_VFUNC(d)
GLTEXCOORD_VFUNC(f)
GLTEXCOORD_VFUNC(i)
GLTEXCOORD_VFUNC(s)
#undef GLTEXCOORD_VFUNC

#define GLVERTEX_VFUNC(_type_) \
static VALUE \
gl_Vertex##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
  VALUE args[4]; \
  VALUE ary; \
  switch (rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) { \
  case 1: \
    ary = rb_convert_type(args[0], T_ARRAY, "Array", "to_a"); \
    switch (RARRAY_LEN(ary)) { \
      case 2: \
      gl_Vertex2##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1]); \
      break; \
      case 3: \
      gl_Vertex3##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
      break; \
      case 4: \
      gl_Vertex4##_type_(obj,RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2],RARRAY_PTR(ary)[3]); \
      break; \
      default: \
      rb_raise(rb_eRuntimeError, "glVertex vertex num error!: %ld", RARRAY_LEN(ary)); \
    } \
    break; \
  case 2: \
    gl_Vertex2##_type_(obj,args[0], args[1]); \
    break; \
  case 3: \
    gl_Vertex3##_type_(obj,args[0], args[1], args[2]); \
    break; \
  case 4: \
    gl_Vertex4##_type_(obj,args[0], args[1], args[2], args[3]); \
    break; \
  default: \
    rb_raise(rb_eArgError, "too many arguments"); \
    break; \
  } \
  return Qnil; \
}

GLVERTEX_VFUNC(d)
GLVERTEX_VFUNC(f)
GLVERTEX_VFUNC(i)
GLVERTEX_VFUNC(s)
#undef GLVERTEX_VFUNC

/* */

static VALUE
gl_LightModel(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  if (TYPE(arg2) == T_ARRAY)
    gl_LightModelfv(obj,arg1,arg2);
  else
    gl_LightModelf(obj,arg1,arg2);

  return Qnil;
}

static VALUE
gl_Material(VALUE self, VALUE face, VALUE pname, VALUE param)
{
  VALUE ary;

  if (RB_TYPE_P(param, T_ARRAY)) {
    gl_Materialfv(self, face, pname, param);
  } else if (rb_respond_to(param, rb_intern("to_a")) && (ary = rb_convert_type(param, T_ARRAY, "Array", "to_a"))) {
    gl_Materialfv(self, face, pname, ary);
  } else {
    gl_Materialf(self, face, pname, param);
  }

  return Qnil;
}

static VALUE
gl_Fog(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  if (TYPE(arg2) == T_ARRAY)
    gl_Fogfv(obj,arg1,arg2);
  else
    gl_Fogf(obj,arg1,arg2);

  return Qnil;
}

static VALUE
gl_Light(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  if (TYPE(arg3) == T_ARRAY)
    gl_Lightfv(obj,arg1,arg2,arg3);
  else
    gl_Lightf(obj,arg1,arg2,arg3);

  return Qnil;
}

static VALUE
gl_TexParameter(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  if (TYPE(arg3) == T_ARRAY)
    gl_TexParameterfv(obj,arg1,arg2,arg3);
  else
    gl_TexParameterf(obj,arg1,arg2,arg3);

  return Qnil;
}

static VALUE
gl_TexEnv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  if (TYPE(arg3) == T_ARRAY)
    gl_TexEnvfv(obj,arg1,arg2,arg3);
  else
    gl_TexEnvf(obj,arg1,arg2,arg3);

  return Qnil;
}

static VALUE
gl_TexGen(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  if (TYPE(arg3) == T_ARRAY)
    gl_TexGenfv(obj,arg1,arg2,arg3);
  else
    gl_TexGenf(obj,arg1,arg2,arg3);

  return Qnil;
}

/* init */
void gl_init_functions_1_0__1_1(VALUE klass)
{
  /* OpenGL 1.0 functions */
  rb_define_method(klass, "glNewList", gl_NewList, 2);
  rb_define_method(klass, "glEndList", gl_EndList, 0);
  rb_define_method(klass, "glCallList", gl_CallList, 1);
  rb_define_method(klass, "glCallLists", gl_CallLists, 2);
  rb_define_method(klass, "glDeleteLists", gl_DeleteLists, 2);
  rb_define_method(klass, "glGenLists", gl_GenLists, 1);
  rb_define_method(klass, "glListBase", gl_ListBase, 1);
  rb_define_method(klass, "glBegin", gl_Begin, 1);
  rb_define_method(klass, "glBitmap", gl_Bitmap, 7);
  rb_define_method(klass, "glColor3b", gl_Color3b, 3);
  rb_define_method(klass, "glColor3d", gl_Color3d, 3);
  rb_define_method(klass, "glColor3f", gl_Color3f, 3);
  rb_define_method(klass, "glColor3i", gl_Color3i, 3);
  rb_define_method(klass, "glColor3s", gl_Color3s, 3);
  rb_define_method(klass, "glColor3ub", gl_Color3ub, 3);
  rb_define_method(klass, "glColor3ui", gl_Color3ui, 3);
  rb_define_method(klass, "glColor3us", gl_Color3us, 3);
  rb_define_method(klass, "glColor4b", gl_Color4b, 4);
  rb_define_method(klass, "glColor4d", gl_Color4d, 4);
  rb_define_method(klass, "glColor4f", gl_Color4f, 4);
  rb_define_method(klass, "glColor4i", gl_Color4i, 4);
  rb_define_method(klass, "glColor4s", gl_Color4s, 4);
  rb_define_method(klass, "glColor4ub", gl_Color4ub, 4);
  rb_define_method(klass, "glColor4ui", gl_Color4ui, 4);
  rb_define_method(klass, "glColor4us", gl_Color4us, 4);
  rb_define_method(klass, "glEdgeFlag", gl_EdgeFlag, 1);
  rb_define_method(klass, "glEdgeFlagv", gl_EdgeFlagv, 1);
  rb_define_method(klass, "glEnd", gl_End, 0);
  rb_define_method(klass, "glIndexd", gl_Indexd, 1);
  rb_define_method(klass, "glIndexdv", gl_Indexdv, 1);
  rb_define_method(klass, "glIndexf", gl_Indexf, 1);
  rb_define_method(klass, "glIndexfv", gl_Indexfv, 1);
  rb_define_method(klass, "glIndexi", gl_Indexi, 1);
  rb_define_method(klass, "glIndexiv", gl_Indexiv, 1);
  rb_define_method(klass, "glIndexs", gl_Indexs, 1);
  rb_define_method(klass, "glIndexsv", gl_Indexsv, 1);
  rb_define_method(klass, "glNormal3b", gl_Normal3b, 3);
  rb_define_method(klass, "glNormal3d", gl_Normal3d, 3);
  rb_define_method(klass, "glNormal3f", gl_Normal3f, 3);
  rb_define_method(klass, "glNormal3i", gl_Normal3i, 3);
  rb_define_method(klass, "glNormal3s", gl_Normal3s, 3);
  rb_define_method(klass, "glRasterPos2d", gl_RasterPos2d, 2);
  rb_define_method(klass, "glRasterPos2f", gl_RasterPos2f, 2);
  rb_define_method(klass, "glRasterPos2i", gl_RasterPos2i, 2);
  rb_define_method(klass, "glRasterPos2s", gl_RasterPos2s, 2);
  rb_define_method(klass, "glRasterPos3d", gl_RasterPos3d, 3);
  rb_define_method(klass, "glRasterPos3f", gl_RasterPos3f, 3);
  rb_define_method(klass, "glRasterPos3i", gl_RasterPos3i, 3);
  rb_define_method(klass, "glRasterPos3s", gl_RasterPos3s, 3);
  rb_define_method(klass, "glRasterPos4d", gl_RasterPos4d, 4);
  rb_define_method(klass, "glRasterPos4f", gl_RasterPos4f, 4);
  rb_define_method(klass, "glRasterPos4i", gl_RasterPos4i, 4);
  rb_define_method(klass, "glRasterPos4s", gl_RasterPos4s, 4);
  rb_define_method(klass, "glRectd", gl_Rectd, 4);
  rb_define_method(klass, "glRectf", gl_Rectf, 4);
  rb_define_method(klass, "glRecti", gl_Recti, 4);
  rb_define_method(klass, "glRects", gl_Rects, 4);
  rb_define_method(klass, "glTexCoord1d", gl_TexCoord1d, 1);
  rb_define_method(klass, "glTexCoord1f", gl_TexCoord1f, 1);
  rb_define_method(klass, "glTexCoord1i", gl_TexCoord1i, 1);
  rb_define_method(klass, "glTexCoord1s", gl_TexCoord1s, 1);
  rb_define_method(klass, "glTexCoord2d", gl_TexCoord2d, 2);
  rb_define_method(klass, "glTexCoord2f", gl_TexCoord2f, 2);
  rb_define_method(klass, "glTexCoord2i", gl_TexCoord2i, 2);
  rb_define_method(klass, "glTexCoord2s", gl_TexCoord2s, 2);
  rb_define_method(klass, "glTexCoord3d", gl_TexCoord3d, 3);
  rb_define_method(klass, "glTexCoord3f", gl_TexCoord3f, 3);
  rb_define_method(klass, "glTexCoord3i", gl_TexCoord3i, 3);
  rb_define_method(klass, "glTexCoord3s", gl_TexCoord3s, 3);
  rb_define_method(klass, "glTexCoord4d", gl_TexCoord4d, 4);
  rb_define_method(klass, "glTexCoord4f", gl_TexCoord4f, 4);
  rb_define_method(klass, "glTexCoord4i", gl_TexCoord4i, 4);
  rb_define_method(klass, "glTexCoord4s", gl_TexCoord4s, 4);
  rb_define_method(klass, "glVertex2d", gl_Vertex2d, 2);
  rb_define_method(klass, "glVertex2f", gl_Vertex2f, 2);
  rb_define_method(klass, "glVertex2i", gl_Vertex2i, 2);
  rb_define_method(klass, "glVertex2s", gl_Vertex2s, 2);
  rb_define_method(klass, "glVertex3d", gl_Vertex3d, 3);
  rb_define_method(klass, "glVertex3f", gl_Vertex3f, 3);
  rb_define_method(klass, "glVertex3i", gl_Vertex3i, 3);
  rb_define_method(klass, "glVertex3s", gl_Vertex3s, 3);
  rb_define_method(klass, "glVertex4d", gl_Vertex4d, 4);
  rb_define_method(klass, "glVertex4f", gl_Vertex4f, 4);
  rb_define_method(klass, "glVertex4i", gl_Vertex4i, 4);
  rb_define_method(klass, "glVertex4s", gl_Vertex4s, 4);
  rb_define_method(klass, "glClipPlane", gl_ClipPlane, 2);
  rb_define_method(klass, "glColorMaterial", gl_ColorMaterial, 2);
  rb_define_method(klass, "glCullFace", gl_CullFace, 1);
  rb_define_method(klass, "glFogf", gl_Fogf, 2);
  rb_define_method(klass, "glFogfv", gl_Fogfv, 2);
  rb_define_method(klass, "glFogi", gl_Fogi, 2);
  rb_define_method(klass, "glFogiv", gl_Fogiv, 2);
  rb_define_method(klass, "glFrontFace", gl_FrontFace, 1);
  rb_define_method(klass, "glHint", gl_Hint, 2);
  rb_define_method(klass, "glLightf", gl_Lightf, 3);
  rb_define_method(klass, "glLightfv", gl_Lightfv, 3);
  rb_define_method(klass, "glLighti", gl_Lighti, 3);
  rb_define_method(klass, "glLightiv", gl_Lightiv, 3);
  rb_define_method(klass, "glLightModelf", gl_LightModelf, 2);
  rb_define_method(klass, "glLightModelfv", gl_LightModelfv, 2);
  rb_define_method(klass, "glLightModeli", gl_LightModeli, 2);
  rb_define_method(klass, "glLightModeliv", gl_LightModeliv, 2);
  rb_define_method(klass, "glLineStipple", gl_LineStipple, 2);
  rb_define_method(klass, "glLineWidth", gl_LineWidth, 1);
  rb_define_method(klass, "glMaterialf", gl_Materialf, 3);
  rb_define_method(klass, "glMaterialfv", gl_Materialfv, 3);
  rb_define_method(klass, "glMateriali", gl_Materiali, 3);
  rb_define_method(klass, "glMaterialiv", gl_Materialiv, 3);
  rb_define_method(klass, "glPointSize", gl_PointSize, 1);
  rb_define_method(klass, "glPolygonMode", gl_PolygonMode, 2);
  rb_define_method(klass, "glPolygonStipple", gl_PolygonStipple, 1);
  rb_define_method(klass, "glScissor", gl_Scissor, 4);
  rb_define_method(klass, "glShadeModel", gl_ShadeModel, 1);
  rb_define_method(klass, "glTexParameterf", gl_TexParameterf, 3);
  rb_define_method(klass, "glTexParameterfv", gl_TexParameterfv, 3);
  rb_define_method(klass, "glTexParameteri", gl_TexParameteri, 3);
  rb_define_method(klass, "glTexParameteriv", gl_TexParameteriv, 3);
  rb_define_method(klass, "glTexImage1D", gl_TexImage1D, 8);
  rb_define_method(klass, "glTexImage2D", gl_TexImage2D, 9);
  rb_define_method(klass, "glTexEnvf", gl_TexEnvf, 3);
  rb_define_method(klass, "glTexEnvfv", gl_TexEnvfv, 3);
  rb_define_method(klass, "glTexEnvi", gl_TexEnvi, 3);
  rb_define_method(klass, "glTexEnviv", gl_TexEnviv, 3);
  rb_define_method(klass, "glTexGend", gl_TexGend, 3);
  rb_define_method(klass, "glTexGendv", gl_TexGendv, 3);
  rb_define_method(klass, "glTexGenf", gl_TexGenf, 3);
  rb_define_method(klass, "glTexGenfv", gl_TexGenfv, 3);
  rb_define_method(klass, "glTexGeni", gl_TexGeni, 3);
  rb_define_method(klass, "glTexGeniv", gl_TexGeniv, 3);
  rb_define_method(klass, "glFeedbackBuffer", gl_FeedbackBuffer, 2);
  rb_define_method(klass, "glSelectBuffer", gl_SelectBuffer, 1);
  rb_define_method(klass, "glRenderMode", gl_RenderMode, 1);
  rb_define_method(klass, "glInitNames", gl_InitNames, 0);
  rb_define_method(klass, "glLoadName", gl_LoadName, 1);
  rb_define_method(klass, "glPassThrough", gl_PassThrough, 1);
  rb_define_method(klass, "glPopName", gl_PopName, 0);
  rb_define_method(klass, "glPushName", gl_PushName, 1);
  rb_define_method(klass, "glDrawBuffer", gl_DrawBuffer, 1);
  rb_define_method(klass, "glClear", gl_Clear, 1);
  rb_define_method(klass, "glClearAccum", gl_ClearAccum, 4);
  rb_define_method(klass, "glClearIndex", gl_ClearIndex, 1);
  rb_define_method(klass, "glClearColor", gl_ClearColor, 4);
  rb_define_method(klass, "glClearStencil", gl_ClearStencil, 1);
  rb_define_method(klass, "glClearDepth", gl_ClearDepth, 1);
  rb_define_method(klass, "glStencilMask", gl_StencilMask, 1);
  rb_define_method(klass, "glColorMask", gl_ColorMask, 4);
  rb_define_method(klass, "glDepthMask", gl_DepthMask, 1);
  rb_define_method(klass, "glIndexMask", gl_IndexMask, 1);
  rb_define_method(klass, "glAccum", gl_Accum, 2);
  rb_define_method(klass, "glDisable", gl_Disable, -1);
  rb_define_method(klass, "glEnable", gl_Enable, -1);
  rb_define_method(klass, "glFinish", gl_Finish, 0);
  rb_define_method(klass, "glFlush", gl_Flush, 0);
  rb_define_method(klass, "glPopAttrib", gl_PopAttrib, 0);
  rb_define_method(klass, "glPushAttrib", gl_PushAttrib, 1);
  rb_define_method(klass, "glMap1d", gl_Map1d, 6);
  rb_define_method(klass, "glMap1f", gl_Map1f, 6);
  rb_define_method(klass, "glMap2d", gl_Map2d, 10);
  rb_define_method(klass, "glMap2f", gl_Map2f, 10);
  rb_define_method(klass, "glMapGrid1d", gl_MapGrid1d, 3);
  rb_define_method(klass, "glMapGrid1f", gl_MapGrid1f, 3);
  rb_define_method(klass, "glMapGrid2d", gl_MapGrid2d, 6);
  rb_define_method(klass, "glMapGrid2f", gl_MapGrid2f, 6);
  rb_define_method(klass, "glEvalCoord1d", gl_EvalCoord1d, 1);
  rb_define_method(klass, "glEvalCoord1dv", gl_EvalCoord1dv, 1);
  rb_define_method(klass, "glEvalCoord1f", gl_EvalCoord1f, 1);
  rb_define_method(klass, "glEvalCoord1fv", gl_EvalCoord1fv, 1);
  rb_define_method(klass, "glEvalCoord2d", gl_EvalCoord2d, 2);
  rb_define_method(klass, "glEvalCoord2dv", gl_EvalCoord2dv, 1);
  rb_define_method(klass, "glEvalCoord2f", gl_EvalCoord2f, 2);
  rb_define_method(klass, "glEvalCoord2fv", gl_EvalCoord2fv, 1);
  rb_define_method(klass, "glEvalMesh1", gl_EvalMesh1, 3);
  rb_define_method(klass, "glEvalPoint1", gl_EvalPoint1, 1);
  rb_define_method(klass, "glEvalMesh2", gl_EvalMesh2, 5);
  rb_define_method(klass, "glEvalPoint2", gl_EvalPoint2, 2);
  rb_define_method(klass, "glAlphaFunc", gl_AlphaFunc, 2);
  rb_define_method(klass, "glBlendFunc", gl_BlendFunc, 2);
  rb_define_method(klass, "glLogicOp", gl_LogicOp, 1);
  rb_define_method(klass, "glStencilFunc", gl_StencilFunc, 3);
  rb_define_method(klass, "glStencilOp", gl_StencilOp, 3);
  rb_define_method(klass, "glDepthFunc", gl_DepthFunc, 1);
  rb_define_method(klass, "glPixelZoom", gl_PixelZoom, 2);
  rb_define_method(klass, "glPixelTransferf", gl_PixelTransferf, 2);
  rb_define_method(klass, "glPixelTransferi", gl_PixelTransferi, 2);
  rb_define_method(klass, "glPixelStoref", gl_PixelStoref, 2);
  rb_define_method(klass, "glPixelStorei", gl_PixelStorei, 2);
  rb_define_method(klass, "glPixelMapfv", gl_PixelMapfv, -1);
  rb_define_method(klass, "glPixelMapuiv", gl_PixelMapuiv, -1);
  rb_define_method(klass, "glPixelMapusv", gl_PixelMapusv, -1);
  rb_define_method(klass, "glReadBuffer", gl_ReadBuffer, 1);
  rb_define_method(klass, "glCopyPixels", gl_CopyPixels, 5);
  rb_define_method(klass, "glReadPixels", gl_ReadPixels, -1);
  rb_define_method(klass, "glDrawPixels", gl_DrawPixels, 5);
  rb_define_method(klass, "glGetBooleanv", gl_GetBooleanv, 1);
  rb_define_method(klass, "glGetClipPlane", gl_GetClipPlane, 1);
  rb_define_method(klass, "glGetDoublev", gl_GetDoublev, 1);
  rb_define_method(klass, "glGetError", gl_GetError, 0);
  rb_define_method(klass, "glGetFloatv", gl_GetFloatv, 1);
  rb_define_method(klass, "glGetIntegerv", gl_GetIntegerv, 1);
  rb_define_method(klass, "glGetLightfv", gl_GetLightfv, 2);
  rb_define_method(klass, "glGetLightiv", gl_GetLightiv, 2);
  rb_define_method(klass, "glGetMapdv", gl_GetMapdv, 2);
  rb_define_method(klass, "glGetMapfv", gl_GetMapfv, 2);
  rb_define_method(klass, "glGetMapiv", gl_GetMapiv, 2);
  rb_define_method(klass, "glGetMaterialfv", gl_GetMaterialfv, 2);
  rb_define_method(klass, "glGetMaterialiv", gl_GetMaterialiv, 2);
  rb_define_method(klass, "glGetPixelMapfv", gl_GetPixelMapfv, -1);
  rb_define_method(klass, "glGetPixelMapuiv", gl_GetPixelMapuiv, -1);
  rb_define_method(klass, "glGetPixelMapusv", gl_GetPixelMapusv, -1);
  rb_define_method(klass, "glGetPolygonStipple", gl_GetPolygonStipple, -1);
  rb_define_method(klass, "glGetString", gl_GetString, 1);
  rb_define_method(klass, "glGetTexEnvfv", gl_GetTexEnvfv, 2);
  rb_define_method(klass, "glGetTexEnviv", gl_GetTexEnviv, 2);
  rb_define_method(klass, "glGetTexGendv", gl_GetTexGendv, 2);
  rb_define_method(klass, "glGetTexGenfv", gl_GetTexGenfv, 2);
  rb_define_method(klass, "glGetTexGeniv", gl_GetTexGeniv, 2);
  rb_define_method(klass, "glGetTexImage", gl_GetTexImage, -1);
  rb_define_method(klass, "glGetTexParameterfv", gl_GetTexParameterfv, 2);
  rb_define_method(klass, "glGetTexParameteriv", gl_GetTexParameteriv, 2);
  rb_define_method(klass, "glGetTexLevelParameterfv", gl_GetTexLevelParameterfv, 3);
  rb_define_method(klass, "glGetTexLevelParameteriv", gl_GetTexLevelParameteriv, 3);
  rb_define_method(klass, "glIsEnabled", gl_IsEnabled, 1);
  rb_define_method(klass, "glIsList", gl_IsList, 1);
  rb_define_method(klass, "glDepthRange", gl_DepthRange, 2);
  rb_define_method(klass, "glFrustum", gl_Frustum, 6);
  rb_define_method(klass, "glLoadIdentity", gl_LoadIdentity, 0);
  rb_define_method(klass, "glLoadMatrixf", gl_LoadMatrixf, 1);
  rb_define_method(klass, "glLoadMatrixd", gl_LoadMatrixd, 1);
  rb_define_method(klass, "glMatrixMode", gl_MatrixMode, 1);
  rb_define_method(klass, "glMultMatrixf", gl_MultMatrixf, 1);
  rb_define_method(klass, "glMultMatrixd", gl_MultMatrixd, 1);
  rb_define_method(klass, "glOrtho", gl_Ortho, 6);
  rb_define_method(klass, "glPopMatrix", gl_PopMatrix, 0);
  rb_define_method(klass, "glPushMatrix", gl_PushMatrix, 0);
  rb_define_method(klass, "glRotated", gl_Rotated, 4);
  rb_define_method(klass, "glRotatef", gl_Rotatef, 4);
  rb_define_method(klass, "glScaled", gl_Scaled, 3);
  rb_define_method(klass, "glScalef", gl_Scalef, 3);
  rb_define_method(klass, "glTranslated", gl_Translated, 3);
  rb_define_method(klass, "glTranslatef", gl_Translatef, 3);
  rb_define_method(klass, "glViewport", gl_Viewport, 4);

  /* OpenGL 1.1 functions */
  rb_define_method(klass, "glArrayElement", gl_ArrayElement, 1);
  rb_define_method(klass, "glColorPointer", gl_ColorPointer, 4);
  rb_define_method(klass, "glDisableClientState", gl_DisableClientState, -1);
  rb_define_method(klass, "glDrawArrays", gl_DrawArrays, 3);
  rb_define_method(klass, "glDrawElements", gl_DrawElements, 4);
  rb_define_method(klass, "glEdgeFlagPointer", gl_EdgeFlagPointer, 2);
  rb_define_method(klass, "glEnableClientState", gl_EnableClientState, -1);
  rb_define_method(klass, "glGetPointerv", gl_GetPointerv, 1);
  rb_define_method(klass, "glIndexPointer", gl_IndexPointer, 3);
  rb_define_method(klass, "glInterleavedArrays", gl_InterleavedArrays, 3);
  rb_define_method(klass, "glNormalPointer", gl_NormalPointer, 3);
  rb_define_method(klass, "glTexCoordPointer", gl_TexCoordPointer, 4);
  rb_define_method(klass, "glVertexPointer", gl_VertexPointer, 4);
  rb_define_method(klass, "glPolygonOffset", gl_PolygonOffset, 2);
  rb_define_method(klass, "glCopyTexImage1D", gl_CopyTexImage1D, 7);
  rb_define_method(klass, "glCopyTexImage2D", gl_CopyTexImage2D, 8);
  rb_define_method(klass, "glCopyTexSubImage1D", gl_CopyTexSubImage1D, 6);
  rb_define_method(klass, "glCopyTexSubImage2D", gl_CopyTexSubImage2D, 8);
  rb_define_method(klass, "glTexSubImage1D", gl_TexSubImage1D, 7);
  rb_define_method(klass, "glTexSubImage2D", gl_TexSubImage2D, 9);
  rb_define_method(klass, "glAreTexturesResident", gl_AreTexturesResident, 1);
  rb_define_method(klass, "glBindTexture", gl_BindTexture, 2);
  rb_define_method(klass, "glDeleteTextures", gl_DeleteTextures, 1);
  rb_define_method(klass, "glGenTextures", gl_GenTextures, 1);
  rb_define_method(klass, "glIsTexture", gl_IsTexture, 1);
  rb_define_method(klass, "glPrioritizeTextures", gl_PrioritizeTextures, 2);
  rb_define_method(klass, "glIndexub", gl_Indexub, 1);
  rb_define_method(klass, "glIndexubv", gl_Indexubv, 1);
  rb_define_method(klass, "glPopClientAttrib", gl_PopClientAttrib, 0);
  rb_define_method(klass, "glPushClientAttrib", gl_PushClientAttrib, 1);

  /* additional functions */
  rb_define_method(klass, "glColor", gl_Colordv, -1);
  rb_define_method(klass, "glColor3bv", gl_Colorbv, -1);
  rb_define_method(klass, "glColor3dv", gl_Colordv, -1);
  rb_define_method(klass, "glColor3fv", gl_Colorfv, -1);
  rb_define_method(klass, "glColor3iv", gl_Coloriv, -1);
  rb_define_method(klass, "glColor3sv", gl_Colorsv, -1);
  rb_define_method(klass, "glColor3ubv", gl_Colorubv, -1);
  rb_define_method(klass, "glColor3uiv", gl_Coloruiv, -1);
  rb_define_method(klass, "glColor3usv", gl_Colorusv, -1);
  rb_define_method(klass, "glColor4bv", gl_Colorbv, -1);
  rb_define_method(klass, "glColor4dv", gl_Colordv, -1);
  rb_define_method(klass, "glColor4fv", gl_Colorfv, -1);
  rb_define_method(klass, "glColor4iv", gl_Coloriv, -1);
  rb_define_method(klass, "glColor4sv", gl_Colorsv, -1);
  rb_define_method(klass, "glColor4ubv", gl_Colorubv, -1);
  rb_define_method(klass, "glColor4uiv", gl_Coloruiv, -1);
  rb_define_method(klass, "glColor4usv", gl_Colorusv, -1);

  rb_define_method(klass, "glNormal", gl_Normaldv, -1);
  rb_define_method(klass, "glNormal3bv", gl_Normalbv, -1);
  rb_define_method(klass, "glNormal3dv", gl_Normaldv, -1);
  rb_define_method(klass, "glNormal3fv", gl_Normalfv, -1);
  rb_define_method(klass, "glNormal3iv", gl_Normaliv, -1);
  rb_define_method(klass, "glNormal3sv", gl_Normalsv, -1);

  rb_define_method(klass, "glRasterPos", gl_RasterPosdv, -1);
  rb_define_method(klass, "glRasterPos2dv", gl_RasterPosdv, -1);
  rb_define_method(klass, "glRasterPos2fv", gl_RasterPosfv, -1);
  rb_define_method(klass, "glRasterPos2iv", gl_RasterPosiv, -1);
  rb_define_method(klass, "glRasterPos2sv", gl_RasterPossv, -1);
  rb_define_method(klass, "glRasterPos3dv", gl_RasterPosdv, -1);
  rb_define_method(klass, "glRasterPos3fv", gl_RasterPosfv, -1);
  rb_define_method(klass, "glRasterPos3iv", gl_RasterPosiv, -1);
  rb_define_method(klass, "glRasterPos3sv", gl_RasterPossv, -1);
  rb_define_method(klass, "glRasterPos4dv", gl_RasterPosdv, -1);
  rb_define_method(klass, "glRasterPos4fv", gl_RasterPosfv, -1);
  rb_define_method(klass, "glRasterPos4iv", gl_RasterPosiv, -1);
  rb_define_method(klass, "glRasterPos4sv", gl_RasterPossv, -1);

  rb_define_method(klass, "glRect", gl_Rectdv, -1);
  rb_define_method(klass, "glRectdv", gl_Rectdv, -1);
  rb_define_method(klass, "glRectfv", gl_Rectfv, -1);
  rb_define_method(klass, "glRectiv", gl_Rectiv, -1);
  rb_define_method(klass, "glRectsv", gl_Rectsv, -1);

  rb_define_method(klass, "glTexCoord", gl_TexCoorddv, -1);
  rb_define_method(klass, "glTexCoord1dv", gl_TexCoorddv, -1);
  rb_define_method(klass, "glTexCoord1fv", gl_TexCoordfv, -1);
  rb_define_method(klass, "glTexCoord1iv", gl_TexCoordiv, -1);
  rb_define_method(klass, "glTexCoord1sv", gl_TexCoordsv, -1);
  rb_define_method(klass, "glTexCoord2dv", gl_TexCoorddv, -1);
  rb_define_method(klass, "glTexCoord2fv", gl_TexCoordfv, -1);
  rb_define_method(klass, "glTexCoord2iv", gl_TexCoordiv, -1);
  rb_define_method(klass, "glTexCoord2sv", gl_TexCoordsv, -1);
  rb_define_method(klass, "glTexCoord3dv", gl_TexCoorddv, -1);
  rb_define_method(klass, "glTexCoord3fv", gl_TexCoordfv, -1);
  rb_define_method(klass, "glTexCoord3iv", gl_TexCoordiv, -1);
  rb_define_method(klass, "glTexCoord3sv", gl_TexCoordsv, -1);
  rb_define_method(klass, "glTexCoord4dv", gl_TexCoorddv, -1);
  rb_define_method(klass, "glTexCoord4fv", gl_TexCoordfv, -1);
  rb_define_method(klass, "glTexCoord4iv", gl_TexCoordiv, -1);
  rb_define_method(klass, "glTexCoord4sv", gl_TexCoordsv, -1);

  rb_define_method(klass, "glVertex", gl_Vertexdv, -1);
  rb_define_method(klass, "glVertex2dv", gl_Vertexdv, -1);
  rb_define_method(klass, "glVertex2fv", gl_Vertexfv, -1);
  rb_define_method(klass, "glVertex2iv", gl_Vertexiv, -1);
  rb_define_method(klass, "glVertex2sv", gl_Vertexsv, -1);
  rb_define_method(klass, "glVertex3dv", gl_Vertexdv, -1);
  rb_define_method(klass, "glVertex3fv", gl_Vertexfv, -1);
  rb_define_method(klass, "glVertex3iv", gl_Vertexiv, -1);
  rb_define_method(klass, "glVertex3sv", gl_Vertexsv, -1);
  rb_define_method(klass, "glVertex4dv", gl_Vertexdv, -1);
  rb_define_method(klass, "glVertex4fv", gl_Vertexfv, -1);
  rb_define_method(klass, "glVertex4iv", gl_Vertexiv, -1);
  rb_define_method(klass, "glVertex4sv", gl_Vertexsv, -1);

  /* these simply calls normal or vector (*v) function depending on
    if array or single value is passed to them */
  rb_define_method(klass, "glLightModel", gl_LightModel, 2);
  rb_define_method(klass, "glMaterial", gl_Material, 3);
  rb_define_method(klass, "glFog", gl_Fog, 2);
  rb_define_method(klass, "glLight", gl_Light, 3);
  rb_define_method(klass, "glTexParameter", gl_TexParameter, 3);
  rb_define_method(klass, "glTexEnv", gl_TexEnv, 3);
  rb_define_method(klass, "glTexGen", gl_TexGen, 3);

  /* aliases */
  rb_define_method(klass, "glMultMatrix", gl_MultMatrixd, 1);
  rb_define_method(klass, "glLoadMatrix", gl_LoadMatrixd, 1);
  rb_define_method(klass, "glRotate", gl_Rotated, 4);
  rb_define_method(klass, "glScale", gl_Scaled, 3);
  rb_define_method(klass, "glTranslate", gl_Translated, 3);

  rb_define_method(klass, "glPixelStore", gl_PixelStoref, 2);
  rb_define_method(klass, "glPixelTransfer", gl_PixelTransferf, 2);
  rb_define_method(klass, "glIndex", gl_Indexi, 1);
  rb_define_method(klass, "glGetMaterial", gl_GetMaterialfv, 2);
  rb_define_method(klass, "glGetDouble", gl_GetDoublev, 1);
}
