/*
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

/* OpenGL ARB extensions */

/* #3 GL_ARB_transpose_matrix */
#define TRANSPOSEMATRIX_FUNC(_name_,_type_,_conv_) \
static VALUE \
gl_##_name_(obj,arg1) \
VALUE obj,arg1; \
{ \
  _type_ m[4*4]; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(const _type_[])); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_transpose_matrix"); \
  _conv_(arg1, m, 4, 4); \
  fptr_gl##_name_(m); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixfARB,GLfloat,ary2cmatfloat)
TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixdARB,GLdouble,ary2cmatdouble)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixfARB,GLfloat,ary2cmatfloat)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixdARB,GLdouble,ary2cmatdouble)

#undef TRANSPOSEMATRIX_FUNC

/* #5 GL_ARB_multisample */
GL_FUNC_LOAD_2(SampleCoverageARB,GLvoid, GLclampf,GLboolean, "GL_ARB_multisample")

/* #14 GL_ARB_point_parameters */
GL_FUNC_LOAD_2(PointParameterfARB,GLvoid, GLenum,GLfloat, "GL_ARB_point_parameters")

static VALUE gl_PointParameterfvARB(VALUE obj,VALUE arg1,VALUE arg2)
{
  GLfloat params[3] = {(GLfloat)0.0,(GLfloat)0.0,(GLfloat)0.0};
  GLenum pname;
  GLint size;
  DECL_GL_FUNC_PTR(GLvoid,glPointParameterfvARB,(GLenum,GLfloat *));
  LOAD_GL_FUNC(glPointParameterfvARB, "GL_ARB_point_parameters");
  pname = NUM2UINT(arg1);
  Check_Type(arg2,T_ARRAY);
  if (pname==GL_POINT_DISTANCE_ATTENUATION)
    size = 3;
  else
    size = 1;
  ary2cflt(arg2,params,size);
  fptr_glPointParameterfvARB(pname,params);
  CHECK_GLERROR_FROM("glPointParameterfvARB");
  return Qnil;
}

/* #25 GL_ARB_window_pos */
GL_FUNC_LOAD_2(WindowPos2dARB,GLvoid, GLdouble,GLdouble, "GL_ARB_window_pos")
GL_FUNC_LOAD_2(WindowPos2fARB,GLvoid, GLfloat,GLfloat, "GL_ARB_window_pos")
GL_FUNC_LOAD_2(WindowPos2iARB,GLvoid, GLint,GLint, "GL_ARB_window_pos")
GL_FUNC_LOAD_2(WindowPos2sARB,GLvoid, GLshort,GLshort, "GL_ARB_window_pos")
GL_FUNC_LOAD_3(WindowPos3dARB,GLvoid, GLdouble,GLdouble,GLdouble, "GL_ARB_window_pos")
GL_FUNC_LOAD_3(WindowPos3fARB,GLvoid, GLfloat,GLfloat,GLfloat, "GL_ARB_window_pos")
GL_FUNC_LOAD_3(WindowPos3iARB,GLvoid, GLint,GLint,GLint, "GL_ARB_window_pos")
GL_FUNC_LOAD_3(WindowPos3sARB,GLvoid, GLshort,GLshort,GLshort, "GL_ARB_window_pos")

#define WINDOWPOSFUNCV(_name_,_type_,_conv_,_size_,_ext_) \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
  _type_ cary[_size_]; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(const _type_ *)); \
  LOAD_GL_FUNC(gl##_name_, _ext_); \
  Check_Type(arg1,T_ARRAY); \
  if (RARRAY_LEN(arg1) != _size_) \
    rb_raise(rb_eArgError, "Incorrect array length - must have '%i' elements.",_size_); \
  _conv_(arg1,cary,_size_); \
  fptr_gl##_name_(cary); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

WINDOWPOSFUNCV(WindowPos2dvARB,GLdouble,ary2cdbl,2,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos2fvARB,GLfloat,ary2cflt,2,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos2ivARB,GLint,ary2cint,2,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos2svARB,GLshort,ary2cshort,2,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos3dvARB,GLdouble,ary2cdbl,3,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos3fvARB,GLfloat,ary2cflt,3,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos3ivARB,GLint,ary2cint,3,"GL_ARB_window_pos")
WINDOWPOSFUNCV(WindowPos3svARB,GLshort,ary2cshort,3,"GL_ARB_window_pos")
#undef WINDOWPOSFUNCV


/* #26 GL_ARB_vertex_program */
static VALUE gl_ProgramStringARB(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
  DECL_GL_FUNC_PTR(GLvoid,glProgramStringARB,(GLenum,GLenum,GLsizei,const void *));
  LOAD_GL_FUNC(glProgramStringARB, "GL_ARB_vertex_program");
  Check_Type(arg3,T_STRING);
  fptr_glProgramStringARB((GLenum)NUM2INT(arg1),(GLenum)NUM2INT(arg2),(GLsizei)RSTRING_LENINT(arg3),RSTRING_PTR(arg3));
  CHECK_GLERROR_FROM("glProgramStringARB");
  return Qnil;
}

static VALUE gl_GetProgramivARB(VALUE obj,VALUE arg1,VALUE arg2)
{
  GLint ret = 0;
  DECL_GL_FUNC_PTR(GLvoid,glGetProgramivARB,(GLenum,GLenum,GLint *));
  LOAD_GL_FUNC(glGetProgramivARB, "GL_ARB_vertex_program");
  fptr_glGetProgramivARB(NUM2INT(arg1),NUM2INT(arg2),&ret);
  CHECK_GLERROR_FROM("glGetProgramivARB");
  return cond_GLBOOL2RUBY(NUM2INT(arg2),ret);
}

static VALUE gl_GetProgramStringARB(VALUE obj,VALUE arg1,VALUE arg2)
{
  GLsizei len = 0;
  char *buffer;
  VALUE ret_buffer;

  DECL_GL_FUNC_PTR(GLvoid,glGetProgramStringARB,(GLenum,GLenum,void *string));
  DECL_GL_FUNC_PTR(GLvoid,glGetProgramivARB,(GLenum,GLenum,GLint *));
  LOAD_GL_FUNC(glGetProgramStringARB, "GL_ARB_vertex_program");
  LOAD_GL_FUNC(glGetProgramivARB, "GL_ARB_vertex_program");

  fptr_glGetProgramivARB(NUM2INT(arg1),GL_PROGRAM_LENGTH_ARB,&len);
  CHECK_GLERROR_FROM("glGetProgramivARB");
  if (len<=0)
    return rb_str_new2("");

  buffer = ALLOC_N(GLchar,len+1);
  memset(buffer,0,sizeof(GLchar) * (len+1));
    fptr_glGetProgramStringARB(NUM2INT(arg1),NUM2INT(arg2),buffer);
  ret_buffer = rb_str_new2(buffer);
  xfree(buffer);

  CHECK_GLERROR_FROM("glGetProgramStringARB");
  return ret_buffer;
}

GL_FUNC_GENOBJECTS_LOAD(GenProgramsARB,"GL_ARB_vertex_program")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteProgramsARB,"GL_ARB_vertex_program")
GL_FUNC_LOAD_2(BindProgramARB,GLvoid, GLenum,GLuint, "GL_ARB_vertex_program")
GL_FUNC_LOAD_1(IsProgramARB,GLboolean, GLuint, "GL_ARB_vertex_program")
GL_FUNC_LOAD_1(EnableVertexAttribArrayARB,GLvoid, GLuint, "GL_ARB_vertex_program")
GL_FUNC_LOAD_1(DisableVertexAttribArrayARB,GLvoid, GLuint, "GL_ARB_vertex_program")

static VALUE gl_VertexAttribPointerARB(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3,VALUE arg4,VALUE arg5,VALUE arg6)
{
  GLuint index;
  GLuint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;

  DECL_GL_FUNC_PTR(GLvoid,glVertexAttribPointerARB,(GLuint,GLint,GLenum,GLboolean,GLsizei,const GLvoid *));
  LOAD_GL_FUNC(glVertexAttribPointerARB, "GL_ARB_vertex_program");

  index = (GLuint)NUM2UINT(arg1);
  size = (GLuint)NUM2UINT(arg2);
  type = (GLenum)NUM2INT(arg3);
  normalized = (GLboolean)RUBYBOOL2GL(arg4);
  stride = (GLsizei)NUM2UINT(arg5);
  if (index>_MAX_VERTEX_ATTRIBS)
    rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

  if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) {
    GET_GLIMPL_VARIABLE(VertexAttrib_ptr)[index] = arg6;
    fptr_glVertexAttribPointerARB(index,size,type,normalized,stride,(GLvoid *)NUM2SIZET(arg6));
  } else {
    VALUE data;
    data = pack_array_or_pass_string(type,arg6);
    rb_str_freeze(data);
    GET_GLIMPL_VARIABLE(VertexAttrib_ptr)[index] = data;
    fptr_glVertexAttribPointerARB(index,size,type,normalized,stride,(GLvoid *)RSTRING_PTR(data));
  }

  CHECK_GLERROR_FROM("glVertexAttribPointerARB");
  return Qnil;
}


static VALUE
gl_GetVertexAttribPointervARB(obj,arg1)
VALUE obj,arg1;
{
  GLuint index;
  DECL_GL_FUNC_PTR(GLvoid,glGetVertexAttribPointervARB,(GLuint,GLenum,GLvoid **));
  LOAD_GL_FUNC(glGetVertexAttribPointervARB, "GL_ARB_vertex_program");
  index =(GLuint) NUM2INT(arg1);
  if (index>_MAX_VERTEX_ATTRIBS)
    rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

  return GET_GLIMPL_VARIABLE(VertexAttrib_ptr)[index];
}

GL_FUNC_LOAD_6(ProgramEnvParameter4dARB,GLvoid, GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_6(ProgramEnvParameter4fARB,GLvoid, GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat, "GL_ARB_vertex_program")
GL_FUNC_LOAD_6(ProgramLocalParameter4dARB,GLvoid, GLenum,GLuint,GLdouble,GLdouble,GLdouble,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_6(ProgramLocalParameter4fARB,GLvoid, GLenum,GLuint,GLfloat,GLfloat,GLfloat,GLfloat, "GL_ARB_vertex_program")

#define PROGRAMPARAM_FUNC_V(_name_,_type_,_conv_,_extension_) \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
  _type_ cary[4]; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum,GLuint,const _type_ *)); \
  LOAD_GL_FUNC(gl##_name_, _extension_); \
  _conv_(arg3,cary,4); \
  fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),cary); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

PROGRAMPARAM_FUNC_V(ProgramEnvParameter4dvARB,GLdouble,ary2cdbl,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramEnvParameter4fvARB,GLfloat,ary2cflt,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramLocalParameter4dvARB,GLdouble,ary2cdbl,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramLocalParameter4fvARB,GLfloat,ary2cflt,"GL_ARB_vertex_program")
#undef PROGRAMPARAM_FUNC_V

#define GETPROGRAMPARAM_FUNC(_name_,_type_,_extension_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  _type_ cary[4] = {(_type_)0.0,(_type_)0.0,(_type_)0.0,(_type_)0.0}; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum,GLuint,_type_ *)); \
  LOAD_GL_FUNC(gl##_name_, _extension_); \
  fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),cary); \
  RET_ARRAY_OR_SINGLE("gl" #_name_, 4, RETCONV_##_type_, cary); \
}

GETPROGRAMPARAM_FUNC(GetProgramEnvParameterdvARB,GLdouble,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramEnvParameterfvARB,GLfloat,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramLocalParameterdvARB,GLdouble,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramLocalParameterfvARB,GLfloat,"GL_ARB_vertex_program")

#undef GETPROGRAMPARAM_FUNC

GL_FUNC_LOAD_2(VertexAttrib1dARB,GLvoid, GLuint,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_2(VertexAttrib1fARB,GLvoid, GLuint,GLfloat, "GL_ARB_vertex_program")
GL_FUNC_LOAD_2(VertexAttrib1sARB,GLvoid, GLuint,GLshort, "GL_ARB_vertex_program")
GL_FUNC_LOAD_3(VertexAttrib2dARB,GLvoid, GLuint,GLdouble,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_3(VertexAttrib2fARB,GLvoid, GLuint,GLfloat,GLfloat, "GL_ARB_vertex_program")
GL_FUNC_LOAD_3(VertexAttrib2sARB,GLvoid, GLuint,GLshort,GLshort, "GL_ARB_vertex_program")
GL_FUNC_LOAD_4(VertexAttrib3dARB,GLvoid, GLuint,GLdouble,GLdouble,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_4(VertexAttrib3fARB,GLvoid, GLuint,GLfloat,GLfloat,GLfloat, "GL_ARB_vertex_program")
GL_FUNC_LOAD_4(VertexAttrib3sARB,GLvoid, GLuint,GLshort,GLshort,GLshort, "GL_ARB_vertex_program")
GL_FUNC_LOAD_5(VertexAttrib4dARB,GLvoid, GLuint,GLdouble,GLdouble,GLdouble,GLdouble, "GL_ARB_vertex_program")
GL_FUNC_LOAD_5(VertexAttrib4fARB,GLvoid, GLuint,GLfloat,GLfloat,GLfloat,GLfloat, "GL_ARB_vertex_program")
GL_FUNC_LOAD_5(VertexAttrib4sARB,GLvoid, GLuint,GLshort,GLshort,GLshort,GLshort, "GL_ARB_vertex_program")
GL_FUNC_LOAD_5(VertexAttrib4NubARB,GLvoid, GLuint,GLubyte,GLubyte,GLubyte,GLubyte, "GL_ARB_vertex_program")

#define VERTEXATTRIB_FUNC_V(_name_,_type_,_conv_,_size_,_extension_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLuint index; \
  _type_ v[_size_]; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,_type_ *)); \
  LOAD_GL_FUNC(gl##_name_, _extension_); \
  index = (GLuint)NUM2UINT(arg1); \
  _conv_(arg2,v,_size_); \
  fptr_gl##_name_(index,v); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

VERTEXATTRIB_FUNC_V(VertexAttrib4NbvARB,GLbyte,ary2cbyte,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4NivARB,GLint,ary2cint,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4NsvARB,GLshort,ary2cshort,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4NubvARB,GLubyte,ary2cubyte,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4NuivARB,GLuint,ary2cuint,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4NusvARB,GLushort,ary2cushort,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4uivARB,GLuint,ary2cuint,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4ubvARB,GLubyte,ary2cubyte,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4usvARB,GLushort,ary2cushort,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4bvARB,GLbyte,ary2cbyte,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4ivARB,GLint,ary2cint,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4dvARB,GLdouble,ary2cdbl,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4fvARB,GLfloat,ary2cflt,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4svARB,GLshort,ary2cshort,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3dvARB,GLdouble,ary2cdbl,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3fvARB,GLfloat,ary2cflt,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3svARB,GLshort,ary2cshort,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2dvARB,GLdouble,ary2cdbl,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2fvARB,GLfloat,ary2cflt,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2svARB,GLshort,ary2cshort,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1dvARB,GLdouble,ary2cdbl,1,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1fvARB,GLfloat,ary2cflt,1,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1svARB,GLshort,ary2cshort,1,"GL_ARB_vertex_program")
#undef VERTEXATTRIB_FUNC_V

#define GETVERTEXATTRIB_FUNC(_name_,_type_,_extension_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLuint index; \
  GLenum pname; \
  _type_ params[4] = {0,0,0,0}; \
  GLint size; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,GLenum,_type_ *)); \
  LOAD_GL_FUNC(gl##_name_, _extension_); \
  index = (GLuint)NUM2UINT(arg1); \
  pname = (GLenum)NUM2INT(arg2); \
  if (pname==GL_CURRENT_VERTEX_ATTRIB_ARB) \
    size = 4; \
  else \
    size = 1; \
  fptr_gl##_name_(index,pname,params); \
  RET_ARRAY_OR_SINGLE("gl" #_name_, size, RETCONV_##_type_, params); \
}

GETVERTEXATTRIB_FUNC(GetVertexAttribdvARB,GLdouble,"GL_ARB_vertex_program")
GETVERTEXATTRIB_FUNC(GetVertexAttribfvARB,GLfloat,"GL_ARB_vertex_program")
//GETVERTEXATTRIB_FUNC(GetVertexAttribivARB,GLint,INT2NUM,"GL_ARB_vertex_program")
#undef GETVERTEXATTRIB_FUNC

static VALUE
gl_GetVertexAttribivARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint index;
  GLenum pname;
  GLint params[4] = {0,0,0,0};
  GLint size;
  DECL_GL_FUNC_PTR(GLvoid,glGetVertexAttribivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetVertexAttribivARB, "GL_ARB_vertex_program");
  index = (GLuint)NUM2UINT(arg1);
  pname = (GLenum)NUM2INT(arg2);
  if (pname==GL_CURRENT_VERTEX_ATTRIB)
    size = 4;
  else
    size = 1;
  fptr_glGetVertexAttribivARB(index,pname,params);
  RET_ARRAY_OR_SINGLE_BOOL("glGetVertexAttribivARB", size, cond_GLBOOL2RUBY,
      pname, params);
}


/* #29 GL_ARB_occlusion_query */
GL_FUNC_GENOBJECTS_LOAD(GenQueriesARB,"GL_ARB_occlusion_query")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteQueriesARB,"GL_ARB_occlusion_query")
GL_FUNC_LOAD_1(IsQueryARB,GLboolean, GLuint, "GL_ARB_occlusion_query")
GL_FUNC_LOAD_2(BeginQueryARB,GLvoid, GLuint,GLuint, "GL_ARB_occlusion_query")
GL_FUNC_LOAD_1(EndQueryARB,GLvoid, GLenum, "GL_ARB_occlusion_query")

#define GETQUERY_FUNC(_name_,_type_,_conv_) \
static VALUE gl_##_name_(VALUE obj,VALUE arg1,VALUE arg2) \
{ \
  _type_ ret = 0; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,GLenum,_type_ *)); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_occlusion_query"); \
  fptr_gl##_name_(NUM2INT(arg1),NUM2INT(arg2),&ret); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return _conv_(NUM2INT(arg2),ret); \
}

GETQUERY_FUNC(GetQueryivARB,GLint,cond_GLBOOL2RUBY)
GETQUERY_FUNC(GetQueryObjectivARB,GLint,cond_GLBOOL2RUBY)
GETQUERY_FUNC(GetQueryObjectuivARB,GLuint,cond_GLBOOL2RUBY_U)
#undef GETQUERY_FUNC

/* #30 GL_ARB_shader_objects */
GL_FUNC_LOAD_1(DeleteObjectARB,GLvoid, GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_2(DetachObjectARB,GLvoid, GLuint,GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(CompileShaderARB,GLvoid, GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_2(AttachObjectARB,GLvoid, GLuint,GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(LinkProgramARB,GLvoid, GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(UseProgramObjectARB,GLvoid, GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(ValidateProgramARB,GLvoid, GLuint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(GetHandleARB,GLuint, GLenum, "GL_ARB_shader_objects")
GL_FUNC_LOAD_1(CreateShaderObjectARB,GLuint, GLenum, "GL_ARB_shader_objects")
GL_FUNC_LOAD_0(CreateProgramObjectARB,GLuint, "GL_ARB_shader_objects")

static VALUE
gl_ShaderSourceARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint shader;
  GLint length;
  GLchar *str;
  DECL_GL_FUNC_PTR(GLvoid,glShaderSourceARB,(GLuint,GLsizei,GLchar**,GLint *));
  LOAD_GL_FUNC(glShaderSourceARB, "GL_ARB_shader_objects");
  shader = (GLuint)NUM2UINT(arg1);
  Check_Type(arg2,T_STRING);
  str = RSTRING_PTR(arg2);
  length = (GLint)RSTRING_LENINT(arg2);
  fptr_glShaderSourceARB(shader,1,&str,&length);
  CHECK_GLERROR_FROM("glShaderSourceARB");
  return Qnil;
}

GL_FUNC_LOAD_2(Uniform1fARB,GLvoid, GLint,GLfloat, "GL_ARB_shader_objects")
GL_FUNC_LOAD_3(Uniform2fARB,GLvoid, GLint,GLfloat,GLfloat, "GL_ARB_shader_objects")
GL_FUNC_LOAD_4(Uniform3fARB,GLvoid, GLint,GLfloat,GLfloat,GLfloat, "GL_ARB_shader_objects")
GL_FUNC_LOAD_5(Uniform4fARB,GLvoid, GLint,GLfloat,GLfloat,GLfloat,GLfloat, "GL_ARB_shader_objects")
GL_FUNC_LOAD_2(Uniform1iARB,GLvoid, GLint,GLint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_3(Uniform2iARB,GLvoid, GLint,GLint,GLint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_4(Uniform3iARB,GLvoid, GLint,GLint,GLint,GLint, "GL_ARB_shader_objects")
GL_FUNC_LOAD_5(Uniform4iARB,GLvoid, GLint,GLint,GLint,GLint,GLint, "GL_ARB_shader_objects")

#define GLUNIFORM_VFUNC(_name_,_type_,_conv_,_size_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLint location; \
  GLsizei count; \
  _type_ *value; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLint,GLsizei,const _type_ *)); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_shader_objects"); \
  Check_Type(arg2,T_ARRAY); \
  count = (GLsizei)RARRAY_LENINT(arg2); \
  if (count<=0 || (count % _size_) != 0) \
    rb_raise(rb_eArgError, "Parameter array size must be multiplication of %i",_size_); \
  location = (GLint)NUM2INT(arg1); \
  value = ALLOC_N(_type_,count); \
  _conv_(arg2,value,count); \
  fptr_gl##_name_(location,count / _size_,value); \
  xfree(value); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

GLUNIFORM_VFUNC(Uniform1fvARB,GLfloat,ary2cflt,1)
GLUNIFORM_VFUNC(Uniform2fvARB,GLfloat,ary2cflt,2)
GLUNIFORM_VFUNC(Uniform3fvARB,GLfloat,ary2cflt,3)
GLUNIFORM_VFUNC(Uniform4fvARB,GLfloat,ary2cflt,4)
GLUNIFORM_VFUNC(Uniform1ivARB,GLint,ary2cint,1)
GLUNIFORM_VFUNC(Uniform2ivARB,GLint,ary2cint,2)
GLUNIFORM_VFUNC(Uniform3ivARB,GLint,ary2cint,3)
GLUNIFORM_VFUNC(Uniform4ivARB,GLint,ary2cint,4)
#undef GLUNIFORM_VFUNC

#define UNIFORMMATRIX_FUNC(_name_,_size_) \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
  GLint location; \
  GLsizei count; \
  GLboolean transpose; \
  GLfloat *value;  \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLint,GLsizei,GLboolean,GLfloat *)); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_shader_objects"); \
  location = (GLint)NUM2INT(arg1); \
  count = (GLsizei)RARRAY_LENINT(rb_funcall(rb_Array(arg3),rb_intern("flatten"),0)); \
  transpose = (GLboolean)RUBYBOOL2GL(arg2); \
  value = ALLOC_N(GLfloat, count); \
  ary2cmatfloatcount(arg3,value,_size_,_size_); \
  fptr_gl##_name_(location,count / (_size_*_size_),transpose,value); \
  xfree(value); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return Qnil; \
}

UNIFORMMATRIX_FUNC(UniformMatrix2fvARB,2)
UNIFORMMATRIX_FUNC(UniformMatrix3fvARB,3)
UNIFORMMATRIX_FUNC(UniformMatrix4fvARB,4)
#undef UNIFORMMATRIX_FUNC

#define GETOBJECTPARAMETER_FUNC(_name_,_type_,_conv_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLuint program; \
  GLenum pname; \
  _type_ params = 0; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,GLenum,_type_ *)); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_shader_objects"); \
  program = (GLuint)NUM2UINT(arg1); \
  pname = (GLenum)NUM2INT(arg2); \
  fptr_gl##_name_(program,pname,&params); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  return _conv_(pname,params); \
}

GETOBJECTPARAMETER_FUNC(GetObjectParameterivARB,GLint,cond_GLBOOL2RUBY)
GETOBJECTPARAMETER_FUNC(GetObjectParameterfvARB,GLfloat,cond_GLBOOL2RUBY_F)

#undef GETOBJECTPARAMETER_FUNC

static VALUE
gl_GetInfoLogARB(obj,arg1)
VALUE obj,arg1;
{
  GLuint program;
  GLint max_size = 0;
  GLsizei ret_length = 0;
  VALUE buffer;
  DECL_GL_FUNC_PTR(GLvoid,glGetInfoLogARB,(GLuint,GLsizei,GLsizei *,GLchar *));
  DECL_GL_FUNC_PTR(GLvoid,glGetObjectParameterivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetInfoLogARB, "GL_ARB_shader_objects");
  LOAD_GL_FUNC(glGetObjectParameterivARB, "GL_ARB_shader_objects");
  program = (GLuint)NUM2UINT(arg1);
  fptr_glGetObjectParameterivARB(program,GL_OBJECT_INFO_LOG_LENGTH_ARB,&max_size);
  CHECK_GLERROR_FROM("glGetObjectParameterivARB");
  if (max_size<=0)
    return rb_str_new2("");
  buffer = allocate_buffer_with_string(max_size);
  fptr_glGetInfoLogARB(program,max_size,&ret_length,RSTRING_PTR(buffer));
  CHECK_GLERROR_FROM("glGetInfoLogARB");
  return buffer;
}

static VALUE
gl_GetShaderSourceARB(obj,arg1)
VALUE obj,arg1;
{
  GLuint shader;
  GLint max_size = 0;
  GLsizei ret_length = 0;
  VALUE buffer;
  DECL_GL_FUNC_PTR(GLvoid,glGetShaderSourceARB,(GLuint,GLsizei,GLsizei *,GLchar *));
  DECL_GL_FUNC_PTR(GLvoid,glGetObjectParameterivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetShaderSourceARB, "GL_ARB_shader_objects");
  LOAD_GL_FUNC(glGetObjectParameterivARB, "GL_ARB_shader_objects");
  shader = (GLuint)NUM2UINT(arg1);
  fptr_glGetObjectParameterivARB(shader,GL_OBJECT_SHADER_SOURCE_LENGTH_ARB,&max_size);
  CHECK_GLERROR_FROM("glGetObjectParameterivARB");
  if (max_size==0)
    rb_raise(rb_eTypeError, "Can't determine maximum shader source length");
  buffer = allocate_buffer_with_string(max_size-1);
  fptr_glGetShaderSourceARB(shader,max_size,&ret_length,RSTRING_PTR(buffer));
  CHECK_GLERROR_FROM("glGetShaderSourceARB");
  return buffer;
}

static VALUE
gl_GetActiveUniformARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint program;
  GLuint index;
  GLsizei max_size = 0;
  GLsizei written = 0;
  GLint uniform_size = 0;
  GLenum uniform_type = 0;
  VALUE buffer;
  VALUE retary;
  DECL_GL_FUNC_PTR(GLvoid,glGetActiveUniformARB,(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*));
  DECL_GL_FUNC_PTR(GLvoid,glGetObjectParameterivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetActiveUniformARB, "GL_ARB_shader_objects");
  LOAD_GL_FUNC(glGetObjectParameterivARB, "GL_ARB_shader_objects");
  program = (GLuint)NUM2UINT(arg1);
  index = (GLuint)NUM2UINT(arg2);
  fptr_glGetObjectParameterivARB(program,GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB,&max_size);
  CHECK_GLERROR_FROM("glGetObjectParameterivARB");
  /* Can't determine maximum uniform name length, so presume it */
  if (max_size==0) max_size = 256;
  buffer = allocate_buffer_with_string(max_size-1);

  fptr_glGetActiveUniformARB(program,index,max_size,&written,&uniform_size,&uniform_type,RSTRING_PTR(buffer));

  rb_str_set_len(buffer, written);
  retary = rb_ary_new2(3);
  rb_ary_push(retary, INT2NUM(uniform_size));
  rb_ary_push(retary, INT2NUM(uniform_type));
  rb_ary_push(retary, buffer);
  CHECK_GLERROR_FROM("glGetACtiveUniformARB");
  return retary;
}

#define GETUNIFORM_FUNC(_name_,_type_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
  GLuint program; \
  GLint location; \
  _type_ params[16]; \
  GLint unused = 0; \
  GLenum uniform_type = 0; \
  GLint uniform_size = 0; \
\
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,GLint,_type_ *)); \
  DECL_GL_FUNC_PTR(GLvoid,glGetActiveUniformARB,(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*)); \
  LOAD_GL_FUNC(gl##_name_, "GL_ARB_shader_objects"); \
  LOAD_GL_FUNC(glGetActiveUniformARB, "GL_ARB_shader_objects"); \
  program = (GLuint)NUM2UINT(arg1); \
  location = (GLint)NUM2INT(arg2); \
\
  fptr_glGetActiveUniformARB(program,location,0,NULL,&unused,&uniform_type,NULL); \
  CHECK_GLERROR_FROM("glGetActiveUniformARB"); \
  if (uniform_type==0) \
    rb_raise(rb_eTypeError, "Can't determine the uniform's type"); \
\
  uniform_size = get_uniform_size(uniform_type); \
\
  memset(params,0,16*sizeof(_type_)); \
  fptr_gl##_name_(program,location,params); \
  CHECK_GLERROR_FROM("gl" #_name_); \
  RET_ARRAY_OR_SINGLE("gl" #_name_, uniform_size, RETCONV_##_type_, params); \
}

GETUNIFORM_FUNC(GetUniformfvARB,GLfloat)
GETUNIFORM_FUNC(GetUniformivARB,GLint)
#undef GETUNIFORM_FUNC

static VALUE
gl_GetUniformLocationARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint program;
  GLint ret;
  DECL_GL_FUNC_PTR(GLint,glGetUniformLocationARB,(GLuint,const GLchar*));
  LOAD_GL_FUNC(glGetUniformLocationARB, "GL_ARB_shader_objects");
  program=(GLuint)NUM2UINT(arg1);
  Check_Type(arg2,T_STRING);
  ret = fptr_glGetUniformLocationARB(program,RSTRING_PTR(arg2));
  CHECK_GLERROR_FROM("glGetUniformLocationARB");
  return INT2NUM(ret);
}

static VALUE
gl_GetAttachedObjectsARB(obj,arg1)
VALUE obj,arg1;
{
  GLuint program;
  GLint shaders_num = 0;
  GLuint *shaders;
  GLsizei count = 0;
  DECL_GL_FUNC_PTR(GLvoid,glGetAttachedObjectsARB,(GLuint,GLsizei,GLsizei *,GLuint *));
  DECL_GL_FUNC_PTR(GLvoid,glGetObjectParameterivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetAttachedObjectsARB, "GL_ARB_shader_objects");
  LOAD_GL_FUNC(glGetObjectParameterivARB, "GL_ARB_shader_objects");
  program = (GLuint)NUM2UINT(arg1);
  fptr_glGetObjectParameterivARB(program,GL_OBJECT_ATTACHED_OBJECTS_ARB,&shaders_num);
  CHECK_GLERROR_FROM("glGetObjectParameterivARB");
  if (shaders_num<=0)
    return Qnil;
  shaders = ALLOC_N(GLuint,shaders_num);
  fptr_glGetAttachedObjectsARB(program,shaders_num,&count,shaders);
  RET_ARRAY_OR_SINGLE_FREE("glGetAttachedObjectsARB", count, RETCONV_GLuint,
      shaders);
}

/* #31 GL_ARB_vertex_shader */

static VALUE
gl_BindAttribLocationARB(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
  GLuint program;
  GLuint index;
  DECL_GL_FUNC_PTR(GLvoid,glBindAttribLocationARB,(GLuint,GLuint,GLchar *));
  LOAD_GL_FUNC(glBindAttribLocationARB, "GL_ARB_vertex_shader");
  program = (GLuint)NUM2UINT(arg1);
  index = (GLuint)NUM2UINT(arg2);
  Check_Type(arg3, T_STRING);
  fptr_glBindAttribLocationARB(program,index,RSTRING_PTR(arg3));
  CHECK_GLERROR_FROM("glBindAttribLocationARB");
  return Qnil;
}

static VALUE
gl_GetActiveAttribARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint program;
  GLuint index;
  GLsizei max_size = 0;
  GLsizei written = 0;
  GLint attrib_size = 0;
  GLenum attrib_type = 0;
  VALUE buffer;
  VALUE retary;
  DECL_GL_FUNC_PTR(GLvoid,glGetActiveAttribARB,(GLuint,GLuint,GLsizei,GLsizei *,GLint *,GLenum *,GLchar *));
  DECL_GL_FUNC_PTR(GLvoid,glGetObjectParameterivARB,(GLuint,GLenum,GLint *));
  LOAD_GL_FUNC(glGetActiveAttribARB, "GL_ARB_vertex_shader");
  LOAD_GL_FUNC(glGetObjectParameterivARB, "GL_ARB_vertex_shader");
  program = (GLuint)NUM2UINT(arg1);
  index = (GLuint)NUM2UINT(arg2);
  fptr_glGetObjectParameterivARB(program,GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB,&max_size);
  CHECK_GLERROR_FROM("glGetObjectParameterivARB");
  /* Can't determine maximum attribute name length, so presume it */
  if (max_size==0) max_size = 256;
  buffer = allocate_buffer_with_string(max_size-1);

  fptr_glGetActiveAttribARB(program,index,max_size,&written,&attrib_size,&attrib_type,RSTRING_PTR(buffer));

  rb_str_set_len(buffer, written);
  retary = rb_ary_new2(3);
  rb_ary_push(retary, INT2NUM(attrib_size));
  rb_ary_push(retary, INT2NUM(attrib_type));
  rb_ary_push(retary, buffer);
  CHECK_GLERROR_FROM("glGetActiveAttribARB");
  return retary;
}

static VALUE
gl_GetAttribLocationARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
  GLuint program;
  GLint ret;
  DECL_GL_FUNC_PTR(GLint,glGetAttribLocationARB,(GLuint,const GLchar*));
  LOAD_GL_FUNC(glGetAttribLocationARB, "GL_ARB_shader_objects");
  program=(GLuint)NUM2UINT(arg1);
  Check_Type(arg2,T_STRING);
  ret = fptr_glGetAttribLocationARB(program,RSTRING_PTR(arg2));
  CHECK_GLERROR_FROM("glGetAttribLocationARB");
  return INT2NUM(ret);
}


/* #39 GL_ARB_color_buffer_float */
GL_FUNC_LOAD_2(ClampColorARB,GLvoid, GLenum,GLenum, "GL_ARB_color_buffer_float")

void gl_init_functions_ext_arb(VALUE klass)
{
/* #3 GL_ARB_transpose_matrix */
  rb_define_method(klass, "glLoadTransposeMatrixfARB", gl_LoadTransposeMatrixfARB, 1);
  rb_define_method(klass, "glLoadTransposeMatrixdARB", gl_LoadTransposeMatrixdARB, 1);
  rb_define_method(klass, "glMultTransposeMatrixfARB", gl_MultTransposeMatrixfARB, 1);
  rb_define_method(klass, "glMultTransposeMatrixdARB", gl_MultTransposeMatrixdARB, 1);

/* #5 GL_ARB_multisample */
  rb_define_method(klass, "glSampleCoverageARB", gl_SampleCoverageARB, 2);

/* #14 GL_ARB_point_parameters */
  rb_define_method(klass, "glPointParameterfARB", gl_PointParameterfARB, 2);
  rb_define_method(klass, "glPointParameterfvARB", gl_PointParameterfvARB, 2);

/* #26 GL_ARB_window_pos */
  rb_define_method(klass, "glWindowPos2dARB", gl_WindowPos2dARB, 2);
  rb_define_method(klass, "glWindowPos2fARB", gl_WindowPos2fARB, 2);
  rb_define_method(klass, "glWindowPos2iARB", gl_WindowPos2iARB, 2);
  rb_define_method(klass, "glWindowPos2sARB", gl_WindowPos2sARB, 2);
  rb_define_method(klass, "glWindowPos3dARB", gl_WindowPos3dARB, 3);
  rb_define_method(klass, "glWindowPos3fARB", gl_WindowPos3fARB, 3);
  rb_define_method(klass, "glWindowPos3iARB", gl_WindowPos3iARB, 3);
  rb_define_method(klass, "glWindowPos3sARB", gl_WindowPos3sARB, 3);

  rb_define_method(klass, "glWindowPos2dvARB", gl_WindowPos2dvARB, 1);
  rb_define_method(klass, "glWindowPos2fvARB", gl_WindowPos2fvARB, 1);
  rb_define_method(klass, "glWindowPos2ivARB", gl_WindowPos2ivARB, 1);
  rb_define_method(klass, "glWindowPos2svARB", gl_WindowPos2svARB, 1);
  rb_define_method(klass, "glWindowPos3dvARB", gl_WindowPos3dvARB, 1);
  rb_define_method(klass, "glWindowPos3fvARB", gl_WindowPos3fvARB, 1);
  rb_define_method(klass, "glWindowPos3ivARB", gl_WindowPos3ivARB, 1);
  rb_define_method(klass, "glWindowPos3svARB", gl_WindowPos3svARB, 1);

/* #26 GL_ARB_vertex_program */
  rb_define_method(klass, "glProgramStringARB", gl_ProgramStringARB, 3);
  rb_define_method(klass, "glGetProgramStringARB", gl_GetProgramStringARB, 2);
  rb_define_method(klass, "glGetProgramivARB", gl_GetProgramivARB, 2);
  rb_define_method(klass, "glBindProgramARB", gl_BindProgramARB, 2);
  rb_define_method(klass, "glGenProgramsARB", gl_GenProgramsARB, 1);
  rb_define_method(klass, "glDeleteProgramsARB", gl_DeleteProgramsARB, 1);
  rb_define_method(klass, "glIsProgramARB", gl_IsProgramARB, 1);
  rb_define_method(klass, "glEnableVertexAttribArrayARB", gl_EnableVertexAttribArrayARB, 1);
  rb_define_method(klass, "glDisableVertexAttribArrayARB", gl_DisableVertexAttribArrayARB, 1);
  rb_define_method(klass, "glVertexAttribPointerARB", gl_VertexAttribPointerARB, 6);
  rb_define_method(klass, "glGetVertexAttribPointervARB", gl_GetVertexAttribPointervARB, 1);
  rb_define_method(klass, "glProgramEnvParameter4dARB", gl_ProgramEnvParameter4dARB, 6);
  rb_define_method(klass, "glProgramEnvParameter4fARB", gl_ProgramEnvParameter4fARB, 6);
  rb_define_method(klass, "glProgramLocalParameter4dARB", gl_ProgramLocalParameter4dARB, 6);
  rb_define_method(klass, "glProgramLocalParameter4fARB", gl_ProgramLocalParameter4fARB, 6);
  rb_define_method(klass, "glProgramEnvParameter4dvARB", gl_ProgramEnvParameter4dvARB, 3);
  rb_define_method(klass, "glProgramEnvParameter4fvARB", gl_ProgramEnvParameter4fvARB, 3);
  rb_define_method(klass, "glProgramLocalParameter4dvARB", gl_ProgramLocalParameter4dvARB, 3);
  rb_define_method(klass, "glProgramLocalParameter4fvARB", gl_ProgramLocalParameter4fvARB, 3);
  rb_define_method(klass, "glGetProgramEnvParameterdvARB", gl_GetProgramEnvParameterdvARB, 2);
  rb_define_method(klass, "glGetProgramEnvParameterfvARB", gl_GetProgramEnvParameterfvARB, 2);
  rb_define_method(klass, "glGetProgramLocalParameterdvARB", gl_GetProgramLocalParameterdvARB, 2);
  rb_define_method(klass, "glGetProgramLocalParameterfvARB", gl_GetProgramLocalParameterfvARB, 2);
  rb_define_method(klass, "glVertexAttrib1dARB", gl_VertexAttrib1dARB, 2);
  rb_define_method(klass, "glVertexAttrib1fARB", gl_VertexAttrib1fARB, 2);
  rb_define_method(klass, "glVertexAttrib1sARB", gl_VertexAttrib1sARB, 2);
  rb_define_method(klass, "glVertexAttrib2dARB", gl_VertexAttrib2dARB, 3);
  rb_define_method(klass, "glVertexAttrib2fARB", gl_VertexAttrib2fARB, 3);
  rb_define_method(klass, "glVertexAttrib2sARB", gl_VertexAttrib2sARB, 3);
  rb_define_method(klass, "glVertexAttrib3dARB", gl_VertexAttrib3dARB, 4);
  rb_define_method(klass, "glVertexAttrib3fARB", gl_VertexAttrib3fARB, 4);
  rb_define_method(klass, "glVertexAttrib3sARB", gl_VertexAttrib3sARB, 4);
  rb_define_method(klass, "glVertexAttrib4NbvARB", gl_VertexAttrib4NbvARB, 2);
  rb_define_method(klass, "glVertexAttrib4NivARB", gl_VertexAttrib4NivARB, 2);
  rb_define_method(klass, "glVertexAttrib4NsvARB", gl_VertexAttrib4NsvARB, 2);
  rb_define_method(klass, "glVertexAttrib4NubARB", gl_VertexAttrib4NubARB, 5);
  rb_define_method(klass, "glVertexAttrib4NubvARB", gl_VertexAttrib4NubvARB, 2);
  rb_define_method(klass, "glVertexAttrib4NuivARB", gl_VertexAttrib4NuivARB, 2);
  rb_define_method(klass, "glVertexAttrib4NusvARB", gl_VertexAttrib4NusvARB, 2);
  rb_define_method(klass, "glVertexAttrib4bvARB", gl_VertexAttrib4bvARB, 2);
  rb_define_method(klass, "glVertexAttrib4dARB", gl_VertexAttrib4dARB, 5);
  rb_define_method(klass, "glVertexAttrib4fARB", gl_VertexAttrib4fARB, 5);
  rb_define_method(klass, "glVertexAttrib4ivARB", gl_VertexAttrib4ivARB, 2);
  rb_define_method(klass, "glVertexAttrib4sARB", gl_VertexAttrib4sARB, 5);
  rb_define_method(klass, "glVertexAttrib4ubvARB", gl_VertexAttrib4ubvARB, 2);
  rb_define_method(klass, "glVertexAttrib4uivARB", gl_VertexAttrib4uivARB, 2);
  rb_define_method(klass, "glVertexAttrib4usvARB", gl_VertexAttrib4usvARB, 2);
  rb_define_method(klass, "glVertexAttrib1dvARB", gl_VertexAttrib1dvARB, 2);
  rb_define_method(klass, "glVertexAttrib1fvARB", gl_VertexAttrib1fvARB, 2);
  rb_define_method(klass, "glVertexAttrib1svARB", gl_VertexAttrib1svARB, 2);
  rb_define_method(klass, "glVertexAttrib2dvARB", gl_VertexAttrib2dvARB, 2);
  rb_define_method(klass, "glVertexAttrib2fvARB", gl_VertexAttrib2fvARB, 2);
  rb_define_method(klass, "glVertexAttrib2svARB", gl_VertexAttrib2svARB, 2);
  rb_define_method(klass, "glVertexAttrib3dvARB", gl_VertexAttrib3dvARB, 2);
  rb_define_method(klass, "glVertexAttrib3fvARB", gl_VertexAttrib3fvARB, 2);
  rb_define_method(klass, "glVertexAttrib3svARB", gl_VertexAttrib3svARB, 2);
  rb_define_method(klass, "glVertexAttrib4dvARB", gl_VertexAttrib4dvARB, 2);
  rb_define_method(klass, "glVertexAttrib4fvARB", gl_VertexAttrib4fvARB, 2);
  rb_define_method(klass, "glVertexAttrib4svARB", gl_VertexAttrib4svARB, 2);
  rb_define_method(klass, "glGetVertexAttribdvARB", gl_GetVertexAttribdvARB, 2);
  rb_define_method(klass, "glGetVertexAttribfvARB", gl_GetVertexAttribfvARB, 2);
  rb_define_method(klass, "glGetVertexAttribivARB", gl_GetVertexAttribivARB, 2);

/* #29 GL_ARB_occlusion_query */
  rb_define_method(klass, "glGenQueriesARB", gl_GenQueriesARB, 1);
  rb_define_method(klass, "glDeleteQueriesARB", gl_DeleteQueriesARB, 1);
  rb_define_method(klass, "glIsQueryARB", gl_IsQueryARB, 1);
  rb_define_method(klass, "glBeginQueryARB", gl_BeginQueryARB, 2);
  rb_define_method(klass, "glEndQueryARB", gl_EndQueryARB, 1);
  rb_define_method(klass, "glGetQueryivARB", gl_GetQueryivARB, 2);
  rb_define_method(klass, "glGetQueryObjectivARB", gl_GetQueryObjectivARB, 2);
  rb_define_method(klass, "glGetQueryObjectuivARB", gl_GetQueryObjectuivARB, 2);

/* #30 GL_ARB_shader_objects */
  rb_define_method(klass, "glDeleteObjectARB", gl_DeleteObjectARB, 1);
  rb_define_method(klass, "glGetHandleARB", gl_GetHandleARB, 1);
  rb_define_method(klass, "glDetachObjectARB", gl_DetachObjectARB, 2);
  rb_define_method(klass, "glCreateShaderObjectARB", gl_CreateShaderObjectARB, 1);
  rb_define_method(klass, "glShaderSourceARB", gl_ShaderSourceARB, 2);
  rb_define_method(klass, "glCompileShaderARB", gl_CompileShaderARB, 1);
  rb_define_method(klass, "glCreateProgramObjectARB", gl_CreateProgramObjectARB, 0);
  rb_define_method(klass, "glAttachObjectARB", gl_AttachObjectARB, 2);
  rb_define_method(klass, "glLinkProgramARB", gl_LinkProgramARB, 1);
  rb_define_method(klass, "glUseProgramObjectARB", gl_UseProgramObjectARB, 1);
  rb_define_method(klass, "glValidateProgramARB", gl_ValidateProgramARB, 1);
  rb_define_method(klass, "glUniform1fARB", gl_Uniform1fARB, 2);
  rb_define_method(klass, "glUniform2fARB", gl_Uniform2fARB, 3);
  rb_define_method(klass, "glUniform3fARB", gl_Uniform3fARB, 4);
  rb_define_method(klass, "glUniform4fARB", gl_Uniform4fARB, 5);
  rb_define_method(klass, "glUniform1iARB", gl_Uniform1iARB, 2);
  rb_define_method(klass, "glUniform2iARB", gl_Uniform2iARB, 3);
  rb_define_method(klass, "glUniform3iARB", gl_Uniform3iARB, 4);
  rb_define_method(klass, "glUniform4iARB", gl_Uniform4iARB, 5);
  rb_define_method(klass, "glUniform1fvARB", gl_Uniform1fvARB, 2);
  rb_define_method(klass, "glUniform2fvARB", gl_Uniform2fvARB, 2);
  rb_define_method(klass, "glUniform3fvARB", gl_Uniform3fvARB, 2);
  rb_define_method(klass, "glUniform4fvARB", gl_Uniform4fvARB, 2);
  rb_define_method(klass, "glUniform1ivARB", gl_Uniform1ivARB, 2);
  rb_define_method(klass, "glUniform2ivARB", gl_Uniform2ivARB, 2);
  rb_define_method(klass, "glUniform3ivARB", gl_Uniform3ivARB, 2);
  rb_define_method(klass, "glUniform4ivARB", gl_Uniform4ivARB, 2);
  rb_define_method(klass, "glUniformMatrix2fvARB", gl_UniformMatrix2fvARB, 3);
  rb_define_method(klass, "glUniformMatrix3fvARB", gl_UniformMatrix3fvARB, 3);
  rb_define_method(klass, "glUniformMatrix4fvARB", gl_UniformMatrix4fvARB, 3);
  rb_define_method(klass, "glGetObjectParameterfvARB", gl_GetObjectParameterfvARB, 2);
  rb_define_method(klass, "glGetObjectParameterivARB", gl_GetObjectParameterivARB, 2);
  rb_define_method(klass, "glGetInfoLogARB", gl_GetInfoLogARB, 1);
  rb_define_method(klass, "glGetShaderSourceARB", gl_GetShaderSourceARB, 1);
  rb_define_method(klass, "glGetAttachedObjectsARB", gl_GetAttachedObjectsARB, 1);
  rb_define_method(klass, "glGetUniformLocationARB", gl_GetUniformLocationARB, 2);
  rb_define_method(klass, "glGetActiveUniformARB", gl_GetActiveUniformARB, 2);
  rb_define_method(klass, "glGetUniformfvARB", gl_GetUniformfvARB, 2);
  rb_define_method(klass, "glGetUniformivARB", gl_GetUniformivARB, 2);

/* #31 GL_ARB_vertex_shader */
  rb_define_method(klass, "glBindAttribLocationARB", gl_BindAttribLocationARB, 3);
  rb_define_method(klass, "glGetActiveAttribARB", gl_GetActiveAttribARB, 2);
  rb_define_method(klass, "glGetAttribLocationARB", gl_GetAttribLocationARB, 2);

/* #39 GL_ARB_color_buffer_float */
  rb_define_method(klass, "glClampColorARB", gl_ClampColorARB, 2);
}
