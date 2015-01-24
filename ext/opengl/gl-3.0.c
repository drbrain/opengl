/*
 * Copyright (C) 2013 Blaž Hrastnik <speed.the.bboy@gmail.com>
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

/*
	GL_APPLE_flush_buffer_range -> actually ARB_map_buffer_range

	GL_EXT_framebuffer_object -> GL_ARB_framebuffer_object

	GL_NV_half_float

	GL_EXT_transform_feedback

	-- New commands in OpenGL 3.0:

	ClearBufferiv(buffer, drawbuffer, value)
		return		void
		param		buffer		GLenum in value
		param		drawbuffer	DrawBufferName in value
		param		value		Int32 in array [COMPSIZE(buffer)]

	ClearBufferuiv(buffer, drawbuffer, value)
		return		void
		param		buffer		GLenum in value
		param		drawbuffer	DrawBufferName in value
		param		value		UInt32 in array [COMPSIZE(buffer)]

	ClearBufferfv(buffer, drawbuffer, value)
		return		void
		param		buffer		GLenum in value
		param		drawbuffer	DrawBufferName in value
		param		value		Float32 in array [COMPSIZE(buffer)]

	ClearBufferfi(buffer, drawbuffer, depth, stencil)
		return		void
		param		buffer		GLenum in value
		param		drawbuffer	DrawBufferName in value
		param		depth		Float32 in value
		param		stencil		Int32 in value

	GetStringi(name, index)
		return		String
		param		name		GLenum in value
		param		index		UInt32 in value

*/

/* GL_NV_conditional_render */
GL_FUNC_LOAD_2(BeginConditionalRender,GLvoid, GLuint, GLenum, "3.0")
GL_FUNC_LOAD_0(EndConditionalRender,GLvoid, "3.0")

/* #326 - GL_EXT_gpu_shader4 */
GL_FUNC_LOAD_2(VertexAttribI1i,GLvoid, GLuint,GLint, "3.0")
GL_FUNC_LOAD_3(VertexAttribI2i,GLvoid, GLuint,GLint,GLint, "3.0")
GL_FUNC_LOAD_4(VertexAttribI3i,GLvoid, GLuint,GLint,GLint,GLint, "3.0")
GL_FUNC_LOAD_5(VertexAttribI4i,GLvoid, GLuint,GLint,GLint,GLint,GLint, "3.0")
GL_FUNC_LOAD_2(VertexAttribI1ui,GLvoid, GLuint,GLuint, "3.0")
GL_FUNC_LOAD_3(VertexAttribI2ui,GLvoid, GLuint,GLuint,GLuint, "3.0")
GL_FUNC_LOAD_4(VertexAttribI3ui,GLvoid, GLuint,GLuint,GLuint,GLuint, "3.0")
GL_FUNC_LOAD_5(VertexAttribI4ui,GLvoid, GLuint,GLuint,GLuint,GLuint,GLuint, "3.0")

#define GLVERTEXATTRIB_VFUNC(_name_,_type_,_conv_,_size_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	_type_ value[_size_]; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLuint,const _type_ *)); \
	LOAD_GL_FUNC(gl##_name_, "3.0"); \
	_conv_(arg2,value,_size_); \
	fptr_gl##_name_(NUM2UINT(arg1),value); \
	CHECK_GLERROR_FROM("gl" #_name_); \
	return Qnil; \
}

GLVERTEXATTRIB_VFUNC(VertexAttribI1iv,GLint,ary2cint,1)
GLVERTEXATTRIB_VFUNC(VertexAttribI2iv,GLint,ary2cint,2)
GLVERTEXATTRIB_VFUNC(VertexAttribI3iv,GLint,ary2cint,3)
GLVERTEXATTRIB_VFUNC(VertexAttribI4iv,GLint,ary2cint,4)
GLVERTEXATTRIB_VFUNC(VertexAttribI1uiv,GLuint,ary2cuint,1)
GLVERTEXATTRIB_VFUNC(VertexAttribI2uiv,GLuint,ary2cuint,2)
GLVERTEXATTRIB_VFUNC(VertexAttribI3uiv,GLuint,ary2cuint,3)
GLVERTEXATTRIB_VFUNC(VertexAttribI4uiv,GLuint,ary2cuint,4)
GLVERTEXATTRIB_VFUNC(VertexAttribI4bv,GLbyte,ary2cbyte,4)
GLVERTEXATTRIB_VFUNC(VertexAttribI4sv,GLshort,ary2cshort,4)
GLVERTEXATTRIB_VFUNC(VertexAttribI4ubv,GLubyte,ary2cubyte,4)
GLVERTEXATTRIB_VFUNC(VertexAttribI4usv,GLushort,ary2cushort,4)
#undef GLVERTEXATTRIB_VFUNC

#define GETVERTEXATTRIB_FUNC(_name_,_type_,_conv_,_extension_) \
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
	RET_ARRAY_OR_SINGLE_BOOL("gl" #_name_, size, _conv_, pname, params); \
}

GETVERTEXATTRIB_FUNC(GetVertexAttribIiv,GLint,cond_GLBOOL2RUBY,"3.0")
GETVERTEXATTRIB_FUNC(GetVertexAttribIuiv,GLuint,cond_GLBOOL2RUBY_U,"3.0")
#undef GETVERTEXATTRIB_FUNC

static VALUE gl_VertexAttribIPointer(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3,VALUE arg4,VALUE arg5)
{
	GLuint index;
	GLuint size;
	GLenum type;
	GLsizei stride;

  DECL_GL_FUNC_PTR(GLvoid,glVertexAttribIPointer,(GLuint,GLint,GLenum,GLsizei,const GLvoid *));
	LOAD_GL_FUNC(glVertexAttribIPointer, "3.0");

	index = (GLuint)NUM2UINT(arg1);
	size = (GLuint)NUM2UINT(arg2);
	type = (GLenum)NUM2INT(arg3);
	stride = (GLsizei)NUM2UINT(arg4);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	if (CHECK_BUFFER_BINDING(GL_ARRAY_BUFFER_BINDING)) {
		GET_GLIMPL_VARIABLE(VertexAttrib_ptr)[index] = arg5;
		fptr_glVertexAttribIPointer(index,size,type,stride,(GLvoid *)NUM2SIZET(arg5));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg5);
		rb_str_freeze(data);
		GET_GLIMPL_VARIABLE(VertexAttrib_ptr)[index] = data;
		fptr_glVertexAttribIPointer(index,size,type,stride,(GLvoid *)RSTRING_PTR(data));
	}

	CHECK_GLERROR_FROM("glVertexAttribIPointer");
	return Qnil;
}

GL_FUNC_LOAD_2(Uniform1ui,GLvoid, GLint,GLuint, "3.0")
GL_FUNC_LOAD_3(Uniform2ui,GLvoid, GLint,GLuint,GLuint, "3.0")
GL_FUNC_LOAD_4(Uniform3ui,GLvoid, GLint,GLuint,GLuint,GLuint, "3.0")
GL_FUNC_LOAD_5(Uniform4ui,GLvoid, GLint,GLuint,GLuint,GLuint,GLuint, "3.0")

#define GLUNIFORM_VFUNC(_name_,_type_,_conv_,_size_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLint location; \
	GLsizei count; \
	_type_ *value; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLint,GLsizei,const _type_ *)); \
	LOAD_GL_FUNC(gl##_name_, "3.0"); \
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

GLUNIFORM_VFUNC(Uniform1uiv,GLuint,ary2cuint,1)
GLUNIFORM_VFUNC(Uniform2uiv,GLuint,ary2cuint,2)
GLUNIFORM_VFUNC(Uniform3uiv,GLuint,ary2cuint,3)
GLUNIFORM_VFUNC(Uniform4uiv,GLuint,ary2cuint,4)
#undef GLUNIFORM_VFUNC

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
	LOAD_GL_FUNC(gl##_name_, "3.0"); \
	LOAD_GL_FUNC(glGetActiveUniformARB, "3.0"); \
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
	RET_ARRAY_OR_SINGLE("gl" #_name_, uniform_size, RETCONV_##_type_, params); \
}

GETUNIFORM_FUNC(GetUniformuiv,GLuint)
#undef GETUNIFORM_FUNC

static VALUE gl_BindFragDataLocation(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
  DECL_GL_FUNC_PTR(GLvoid,glBindFragDataLocation,(GLuint,GLuint,const GLchar *));
	LOAD_GL_FUNC(glBindFragDataLocation, "3.0");
	Check_Type(arg3,T_STRING);
	fptr_glBindFragDataLocation(NUM2UINT(arg1),NUM2UINT(arg2),RSTRING_PTR(arg3));
	CHECK_GLERROR_FROM("glBindFragDataLocation");
	return Qnil;
}

static VALUE gl_GetFragDataLocation(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLint ret;
  DECL_GL_FUNC_PTR(GLint,glGetFragDataLocation,(GLuint,const GLchar *));
	LOAD_GL_FUNC(glGetFragDataLocation, "3.0");
	Check_Type(arg2,T_STRING);
	ret = fptr_glGetFragDataLocation(NUM2UINT(arg1),RSTRING_PTR(arg2));
	CHECK_GLERROR_FROM("glGetFragDataLocation");
	return INT2NUM(ret);
}

/* ARB_map_buffer_range */

/* #39 GL_ARB_color_buffer_float */

GL_FUNC_LOAD_2(ClampColor,GLvoid, GLenum,GLenum, "3.0")

/* #334 GL_NV_depth_buffer_float */

GL_FUNC_LOAD_2(DepthRanged,GLvoid, GLdouble,GLdouble, "3.0")
GL_FUNC_LOAD_1(ClearDepthd,GLvoid, GLdouble, "3.0")
GL_FUNC_LOAD_2(DepthBoundsd,GLvoid, GLdouble,GLdouble, "3.0")

/* GL_ARB_framebuffer_object */
GL_FUNC_LOAD_1(IsRenderbuffer,GLboolean, GLuint, "3.0")
GL_FUNC_LOAD_2(BindRenderbuffer,GLvoid, GLenum,GLuint, "3.0")
GL_FUNC_LOAD_4(RenderbufferStorage,GLvoid, GLenum,GLenum,GLsizei,GLsizei, "3.0")
GL_FUNC_GENOBJECTS_LOAD(GenRenderbuffers,"3.0")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteRenderbuffers,"3.0")

static VALUE gl_GetRenderbufferParameteriv(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLint param = 0;
  DECL_GL_FUNC_PTR(GLvoid,glGetRenderbufferParameteriv,(GLenum,GLenum,GLint *));
	LOAD_GL_FUNC(glGetRenderbufferParameteriv, "3.0");
	fptr_glGetRenderbufferParameteriv(NUM2UINT(arg1),NUM2UINT(arg2),&param);
	CHECK_GLERROR_FROM("glGetRenderbufferParameteriv");
	return INT2NUM(param);
}

GL_FUNC_GENOBJECTS_LOAD(GenFramebuffers,"3.0")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteFramebuffers,"3.0")
GL_FUNC_LOAD_1(IsFramebuffer,GLboolean, GLuint, "3.0")
GL_FUNC_LOAD_2(BindFramebuffer,GLvoid, GLenum,GLuint, "3.0")
GL_FUNC_LOAD_1(CheckFramebufferStatus,GLenum, GLenum, "3.0")
GL_FUNC_LOAD_5(FramebufferTexture1D,GLvoid, GLenum,GLenum,GLenum,GLuint,GLint, "3.0")
GL_FUNC_LOAD_5(FramebufferTexture2D,GLvoid, GLenum,GLenum,GLenum,GLuint,GLint, "3.0")
GL_FUNC_LOAD_6(FramebufferTexture3D,GLvoid, GLenum,GLenum,GLenum,GLuint,GLint,GLint, "3.0")
GL_FUNC_LOAD_5(FramebufferTextureLayer,GLvoid, GLenum,GLenum,GLuint,GLint,GLint, "3.0")
GL_FUNC_LOAD_4(FramebufferRenderbuffer,GLvoid, GLuint,GLuint,GLuint,GLuint, "3.0")

static VALUE gl_GetFramebufferAttachmentParameteriv(VALUE obj,VALUE arg1, VALUE arg2, VALUE arg3)
{
	GLint ret = 0;
  DECL_GL_FUNC_PTR(GLvoid,glGetFramebufferAttachmentParameteriv,(GLenum,GLenum,GLenum,GLint *));
	LOAD_GL_FUNC(glGetFramebufferAttachmentParameteriv, "3.0");
	fptr_glGetFramebufferAttachmentParameteriv(NUM2UINT(arg1),NUM2UINT(arg2),NUM2UINT(arg3),&ret);
	CHECK_GLERROR_FROM("glGetFramebufferAttachmentParameteriv");
	return cond_GLBOOL2RUBY(NUM2UINT(arg3),ret);
}

GL_FUNC_LOAD_1(GenerateMipmap,GLvoid, GLenum, "3.0")

/* GL_NV_half_float */

/* #317 - GL_EXT_framebuffer_multisample */
GL_FUNC_LOAD_5(RenderbufferStorageMultisample,GLvoid, GLenum,GLsizei,GLenum,GLsizei,GLsizei, "3.0")

/* #316 - GL_EXT_framebuffer_blit */
GL_FUNC_LOAD_10(BlitFramebuffer,GLvoid, GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLint,GLbitfield,GLenum, "3.0")

/* #343 - GL_EXT_texture_integer */
GL_FUNC_LOAD_4(ClearColorIi,GLvoid, GLint,GLint,GLint,GLint, "3.0")
GL_FUNC_LOAD_4(ClearColorIui,GLvoid, GLuint,GLuint,GLuint,GLuint, "3.0")

#define TEXPARAMETER_VFUNC(_name_,_type_,_conv_) \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	GLenum target; \
	GLenum pname; \
	_type_ params[4] = {0,0,0,0}; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum,GLenum,_type_ *)); \
	LOAD_GL_FUNC(gl##_name_, "3.0"); \
	target = (GLenum)NUM2UINT(arg1); \
	pname = (GLenum)NUM2UINT(arg2); \
	Check_Type(arg3,T_ARRAY); \
	_conv_(arg3,params,4); \
	fptr_gl##_name_(target,pname,params); \
	CHECK_GLERROR_FROM("gl" #_name_); \
	return Qnil; \
}

TEXPARAMETER_VFUNC(TexParameterIiv,GLint,ary2cint)
TEXPARAMETER_VFUNC(TexParameterIuiv,GLuint,ary2cuint)
#undef TEXPARAMETER_VFUNC

#define GETTEXPARAMETER_VFUNC(_name_,_type_,_conv_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLenum target; \
	GLenum pname; \
	_type_ params[4] = {0,0,0,0}; \
	int size; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum,GLenum,_type_ *)); \
	LOAD_GL_FUNC(gl##_name_, "3.0"); \
	target = (GLenum)NUM2INT(arg1); \
	pname = (GLenum)NUM2INT(arg2); \
	switch(pname) { \
		case GL_TEXTURE_BORDER_COLOR: \
		case GL_TEXTURE_BORDER_VALUES_NV: \
		case GL_POST_TEXTURE_FILTER_BIAS_SGIX: \
		case GL_POST_TEXTURE_FILTER_SCALE_SGIX: \
			size = 4; \
			break; \
		default: \
			size = 1; \
			break; \
	} \
	fptr_gl##_name_(target,pname,params); \
	RET_ARRAY_OR_SINGLE_BOOL("gl" #_name_, size, _conv_, pname, params); \
}

GETTEXPARAMETER_VFUNC(GetTexParameterIiv,GLint,cond_GLBOOL2RUBY)
GETTEXPARAMETER_VFUNC(GetTexParameterIuiv,GLuint,cond_GLBOOL2RUBY_U)
#undef GETTEXPARAMETER_VFUNC

/* #340 - GL_EXT_draw_buffers2 */
GL_FUNC_LOAD_5(ColorMaski,GLvoid, GLuint,GLboolean,GLboolean,GLboolean,GLboolean, "3.0")

#define GETINDEXED_FUNC(_name_,_type_,_conv_,_extension_) \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLenum target; \
	GLenum pname; \
	_type_ result; \
  DECL_GL_FUNC_PTR(GLvoid,gl##_name_,(GLenum,GLenum,_type_ *)); \
	LOAD_GL_FUNC(gl##_name_, _extension_); \
	target = (GLenum)NUM2INT(arg1); \
	pname  = (GLuint)NUM2INT(arg2); \
	fptr_gl##_name_(target,pname,&result); \
	return _conv_(result); \
}

GETINDEXED_FUNC(GetBooleani_v, GLboolean, GLBOOL2RUBY, "3.0")
GETINDEXED_FUNC(GetIntegeri_v, GLint, INT2NUM, "3.0")
#undef GETINDEXED_FUNC

GL_FUNC_LOAD_2(Enablei,GLvoid, GLenum,GLuint, "3.0")
GL_FUNC_LOAD_2(Disablei,GLvoid, GLenum,GLuint, "3.0")
GL_FUNC_LOAD_2(IsEnabledi,GLvoid, GLenum,GLuint, "3.0")

/*  GL_APPLE_vertex_array_object --> ARB_vertex_array_object */
GL_FUNC_GENOBJECTS_LOAD(GenVertexArrays, "3.0");
GL_FUNC_DELETEOBJECTS_LOAD(DeleteVertexArrays, "3.0");
GL_FUNC_LOAD_1(BindVertexArray,GLvoid, GLuint, "3.0");
GL_FUNC_LOAD_1(IsVertexArray,GLboolean, GLuint, "3.0");


void gl_init_functions_3_0(VALUE klass)
{
	/* GL_NV_conditional_render */
	rb_define_method(klass, "glBeginConditionalRender", gl_BeginConditionalRender, 2);
	rb_define_method(klass, "glEndConditionalRender", gl_EndConditionalRender, 0);

	/* #326 - GL_EXT_gpu_shader4 */
	rb_define_method(klass, "glVertexAttribI1i", gl_VertexAttribI1i, 2);
	rb_define_method(klass, "glVertexAttribI2i", gl_VertexAttribI2i, 3);
	rb_define_method(klass, "glVertexAttribI3i", gl_VertexAttribI3i, 4);
	rb_define_method(klass, "glVertexAttribI4i", gl_VertexAttribI4i, 5);
	rb_define_method(klass, "glVertexAttribI1ui", gl_VertexAttribI1ui, 2);
	rb_define_method(klass, "glVertexAttribI2ui", gl_VertexAttribI2ui, 3);
	rb_define_method(klass, "glVertexAttribI3ui", gl_VertexAttribI3ui, 4);
	rb_define_method(klass, "glVertexAttribI4ui", gl_VertexAttribI4ui, 5);
	rb_define_method(klass, "glVertexAttribI1iv", gl_VertexAttribI1iv, 2);
	rb_define_method(klass, "glVertexAttribI2iv", gl_VertexAttribI2iv, 2);
	rb_define_method(klass, "glVertexAttribI3iv", gl_VertexAttribI3iv, 2);
	rb_define_method(klass, "glVertexAttribI4iv", gl_VertexAttribI4iv, 2);
	rb_define_method(klass, "glVertexAttribI1uiv", gl_VertexAttribI1uiv, 2);
	rb_define_method(klass, "glVertexAttribI2uiv", gl_VertexAttribI2uiv, 2);
	rb_define_method(klass, "glVertexAttribI3uiv", gl_VertexAttribI3uiv, 2);
	rb_define_method(klass, "glVertexAttribI4uiv", gl_VertexAttribI4uiv, 2);
	rb_define_method(klass, "glVertexAttribI4bv", gl_VertexAttribI4bv, 2);
	rb_define_method(klass, "glVertexAttribI4sv", gl_VertexAttribI4sv, 2);
	rb_define_method(klass, "glVertexAttribI4ubv", gl_VertexAttribI4ubv, 2);
	rb_define_method(klass, "glVertexAttribI4usv", gl_VertexAttribI4usv, 2);
	rb_define_method(klass, "glVertexAttribIPointer", gl_VertexAttribIPointer, 5);
	rb_define_method(klass, "glGetVertexAttribIiv", gl_GetVertexAttribIiv, 2);
	rb_define_method(klass, "glGetVertexAttribIuiv", gl_GetVertexAttribIuiv, 2);
	rb_define_method(klass, "glUniform1ui", gl_Uniform1ui, 2);
	rb_define_method(klass, "glUniform2ui", gl_Uniform2ui, 3);
	rb_define_method(klass, "glUniform3ui", gl_Uniform3ui, 4);
	rb_define_method(klass, "glUniform4ui", gl_Uniform4ui, 5);
	rb_define_method(klass, "glUniform1uiv", gl_Uniform1uiv, 2);
	rb_define_method(klass, "glUniform2uiv", gl_Uniform2uiv, 2);
	rb_define_method(klass, "glUniform3uiv", gl_Uniform3uiv, 2);
	rb_define_method(klass, "glUniform4uiv", gl_Uniform4uiv, 2);
	rb_define_method(klass, "glGetUniformuiv", gl_GetUniformuiv, 2);
	rb_define_method(klass, "glBindFragDataLocation", gl_BindFragDataLocation, 3);
	rb_define_method(klass, "glGetFragDataLocation", gl_GetFragDataLocation, 2);

	/* GL_NV_conditional_render */

	/* GL_APPLE_flush_buffer_range */

	/* #39 GL_ARB_color_buffer_float */
	rb_define_method(klass, "glClampColor", gl_ClampColor, 2);

	/* #334 GL_NV_depth_buffer_float */
	rb_define_method(klass, "glDepthRanged", gl_DepthRanged, 2);
	rb_define_method(klass, "glClearDepthd", gl_ClearDepthd, 1);
	rb_define_method(klass, "glDepthBoundsd", gl_DepthBoundsd, 2);

	/* #310 - GL_EXT_framebuffer_object */
	rb_define_method(klass, "glIsRenderbuffer", gl_IsRenderbuffer, 1);
	rb_define_method(klass, "glBindRenderbuffer", gl_BindRenderbuffer, 2);
	rb_define_method(klass, "glDeleteRenderbuffers", gl_DeleteRenderbuffers, 1);
	rb_define_method(klass, "glGenRenderbuffers", gl_GenRenderbuffers, 1);
	rb_define_method(klass, "glRenderbufferStorage", gl_RenderbufferStorage, 4);
	rb_define_method(klass, "glGetRenderbufferParameteriv", gl_GetRenderbufferParameteriv, 2);
	rb_define_method(klass, "glIsFramebuffer", gl_IsFramebuffer, 1);
	rb_define_method(klass, "glBindFramebuffer", gl_BindFramebuffer, 2);
	rb_define_method(klass, "glDeleteFramebuffers", gl_DeleteFramebuffers, 1);
	rb_define_method(klass, "glGenFramebuffers", gl_GenFramebuffers, 1);
	rb_define_method(klass, "glCheckFramebufferStatus", gl_CheckFramebufferStatus, 1);
	rb_define_method(klass, "glFramebufferTexture1D", gl_FramebufferTexture1D, 5);
	rb_define_method(klass, "glFramebufferTexture2D", gl_FramebufferTexture2D, 5);
	rb_define_method(klass, "glFramebufferTexture3D", gl_FramebufferTexture3D, 6);
	rb_define_method(klass, "glFramebufferRenderbuffer", gl_FramebufferRenderbuffer, 4);
	rb_define_method(klass, "glFramebufferTextureLayer", gl_FramebufferTextureLayer, 5);
	rb_define_method(klass, "glGetFramebufferAttachmentParameteriv", gl_GetFramebufferAttachmentParameteriv, 3);
	rb_define_method(klass, "glGenerateMipmap", gl_GenerateMipmap, 1);

	/* #317 - GL_EXT_framebuffer_multisample */
	rb_define_method(klass, "glRenderbufferStorageMultisample", gl_RenderbufferStorageMultisample, 5);

	/* #316 - GL_EXT_framebuffer_blit */
	rb_define_method(klass, "glBlitFramebuffer", gl_BlitFramebuffer, 10);

	/* #343 - GL_EXT_texture_integer */
	rb_define_method(klass, "glClearColorIi", gl_ClearColorIi, 4);
	rb_define_method(klass, "glClearColorIui", gl_ClearColorIui, 4);
	rb_define_method(klass, "glTexParameterIiv", gl_TexParameterIiv, 3);
	rb_define_method(klass, "glTexParameterIuiv", gl_TexParameterIuiv, 3);
	rb_define_method(klass, "glGetTexParameterIiv", gl_GetTexParameterIiv, 2);
	rb_define_method(klass, "glGetTexParameterIuiv", gl_GetTexParameterIuiv, 2);

	/* #340 - GL_EXT_draw_buffers2 */
	rb_define_method(klass, "glColorMaski", gl_ColorMaski, 5);
	rb_define_method(klass, "glGetBooleani_v", gl_GetBooleani_v, 2);
	rb_define_method(klass, "glGetIntegeri_v", gl_GetIntegeri_v, 2);
	rb_define_method(klass, "glEnablei", gl_Enablei, 2);
	rb_define_method(klass, "glDisablei", gl_Disablei, 2);
	rb_define_method(klass, "glIsEnabledi", gl_IsEnabledi, 2);

  rb_define_method(klass, "glBindVertexArray", gl_BindVertexArray, 1);
  rb_define_method(klass, "glDeleteVertexArrays", gl_DeleteVertexArrays, 1);
  rb_define_method(klass, "glGenVertexArrays", gl_GenVertexArrays, 1);
  rb_define_method(klass, "glIsVertexArray", gl_IsVertexArray, 1);
}
