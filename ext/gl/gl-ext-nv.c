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

#include "../common/common.h"

/* OpenGL NVIDIA extensions */

/* #222 GL_NV_fence */
static void (APIENTRY * fptr_glGenFencesNV)(GLsizei,GLuint *);
static VALUE gl_GenFencesNV(VALUE obj,VALUE arg1)
{
	GLsizei n;
	GLuint *fences;
	VALUE ret;
	int i;
	LOAD_GL_EXT_FUNC(glGenFencesNV,"GL_NV_fence")
	n = (GLsizei)NUM2UINT(arg1);
	fences = ALLOC_N(GLuint, n);
	fptr_glGenFencesNV(n,fences);
	ret = rb_ary_new2(n);
	for (i = 0; i < n; i++)
		rb_ary_push(ret, INT2NUM(fences[i]));
	xfree(fences);
	CHECK_GLERROR
	return ret;
}

static void (APIENTRY * fptr_glDeleteFencesNV)(GLsizei,const GLuint *);
static VALUE gl_DeleteFencesNV(VALUE obj,VALUE arg1)
{
	GLsizei n;
	LOAD_GL_EXT_FUNC(glDeleteFencesNV,"GL_NV_fence")
	if (TYPE(arg1)==T_ARRAY) {
		GLuint *fences;
		n = RARRAY(arg1)->len;
		fences = ALLOC_N(GLuint,n);
		ary2cuint(arg1,fences,n); 
		fptr_glDeleteFencesNV(n,fences);
		xfree(fences);
	} else {
		GLuint fence;
		fence = NUM2UINT(arg1);
		fptr_glDeleteFencesNV(1,&fence);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glSetFenceNV)(GLuint,GLenum);
static VALUE gl_SetFenceNV(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glSetFenceNV,"GL_NV_fence")
	fptr_glSetFenceNV(NUM2UINT(arg1),NUM2UINT(arg2));
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glTestFenceNV)(GLuint);
static VALUE gl_TestFenceNV(VALUE obj,VALUE arg1)
{
	GLboolean ret;
	LOAD_GL_EXT_FUNC(glTestFenceNV,"GL_NV_fence")
	ret = fptr_glTestFenceNV(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

static GLboolean (APIENTRY * fptr_glIsFenceNV)(GLuint);
static VALUE gl_IsFenceNV(VALUE obj,VALUE arg1)
{
	GLboolean ret;
	LOAD_GL_EXT_FUNC(glIsFenceNV,"GL_NV_fence")
	ret = fptr_glIsFenceNV(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

GL_EXT_SIMPLE_FUNC_LOAD(FinishFenceNV,1,GLuint,NUM2UINT,"GL_NV_fence")

static void (APIENTRY * fptr_glGetFenceivNV)(GLuint,GLenum,GLint *);
static VALUE gl_GetFenceivNV(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLint ret = 0;
	LOAD_GL_EXT_FUNC(glGetFenceivNV,"GL_NV_fence")
	fptr_glGetFenceivNV(NUM2INT(arg1),NUM2INT(arg2),&ret);
	CHECK_GLERROR
	return INT2NUM(ret);
}

/* #233 GL_NV_vertex_program */
static void (APIENTRY * fptr_glLoadProgramNV)(GLenum,GLuint,GLsizei,const GLubyte *);
static VALUE gl_LoadProgramNV(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
	LOAD_GL_EXT_FUNC(glLoadProgramNV,"GL_NV_vertex_program")
	Check_Type(arg3,T_STRING);
	fptr_glLoadProgramNV(NUM2INT(arg1),NUM2UINT(arg2),RSTRING(arg3)->len,(GLubyte *)RSTRING(arg3)->ptr);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetProgramivNV)(GLuint,GLenum,GLint *);
static VALUE gl_GetProgramivNV(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLint ret = 0;
	LOAD_GL_EXT_FUNC(glGetProgramivNV,"GL_NV_vertex_program")
	fptr_glGetProgramivNV(NUM2INT(arg1),NUM2INT(arg2),&ret);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetProgramStringNV)(GLuint,GLenum,void *string);
static VALUE gl_GetProgramStringNV(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLsizei len = 0;
	char *buffer;
	VALUE ret_buffer;

	LOAD_GL_EXT_FUNC(glGetProgramStringNV,"GL_NV_vertex_program")
	LOAD_GL_EXT_FUNC(glGetProgramivNV,"GL_NV_vertex_program")

	fptr_glGetProgramivNV(NUM2INT(arg1),GL_PROGRAM_LENGTH_NV,&len);
	CHECK_GLERROR
	if (len<=0)
		return rb_str_new2("");
	
	buffer = ALLOC_N(GLchar,len+1);
	memset(buffer,0,sizeof(GLchar) * (len+1));
		fptr_glGetProgramStringNV(NUM2INT(arg1),NUM2INT(arg2),buffer);
	ret_buffer = rb_str_new2(buffer);
	xfree(buffer);

	CHECK_GLERROR
	return ret_buffer;
}

static void (APIENTRY * fptr_glBindProgramNV)(GLenum,GLuint);
static VALUE gl_BindProgramNV(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glBindProgramNV,"GL_NV_vertex_program")
	fptr_glBindProgramNV(NUM2INT(arg1),NUM2UINT(arg2));
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGenProgramsNV)(GLsizei, GLuint *);
static VALUE gl_GenProgramsNV(VALUE obj,VALUE arg1)
{
	GLsizei n;
	GLuint *programs;
	RArray *ret;
	int i;

	LOAD_GL_EXT_FUNC(glGenProgramsNV,"GL_NV_vertex_program")
	n = (GLsizei)NUM2UINT(arg1);
	programs = ALLOC_N(GLuint, n);
	fptr_glGenProgramsNV(n,programs);
	ret = RARRAY(rb_ary_new2(n));
	for (i = 0; i < n; i++)
		rb_ary_push((VALUE)ret, INT2NUM(programs[i]));
	xfree(programs);
	CHECK_GLERROR
	return (VALUE)ret;
}

static void (APIENTRY * fptr_glDeleteProgramsNV)(GLsizei,const GLuint *);
static VALUE gl_DeleteProgramsNV(VALUE obj,VALUE arg1)
{
	LOAD_GL_EXT_FUNC(glDeleteProgramsNV,"GL_NV_vertex_program")
	if (TYPE(arg1)==T_ARRAY) {
		GLsizei n;
		GLuint *programs;
		n = RARRAY(arg1)->len;
		programs = ALLOC_N(GLuint,n);
		ary2cuint(arg1,programs,n); 
		fptr_glDeleteProgramsNV( n, programs);
		xfree(programs);
	} else {
		GLuint program;
		program = NUM2INT(arg1);
		fptr_glDeleteProgramsNV( 1, &program);
	}
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glIsProgramNV)(GLuint);
static VALUE gl_IsProgramNV(VALUE obj,VALUE arg1)
{
	GLboolean ret = 0;
	LOAD_GL_EXT_FUNC(glIsProgramNV,"GL_NV_vertex_program")
	ret = fptr_glIsProgramNV(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glExecuteProgramNV)(GLenum,GLuint,const GLfloat *);
static VALUE gl_ExecuteProgramNV(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
	GLfloat params[4] = {0,0,0,0};
	LOAD_GL_EXT_FUNC(glExecuteProgramNV,"GL_NV_vertex_program")
	ary2cflt(arg3,params,4);
	fptr_glExecuteProgramNV(NUM2UINT(arg1),NUM2UINT(arg2),params);
	CHECK_GLERROR
	return Qnil;
}

extern VALUE g_VertexAttrib_ptr[];

static void (APIENTRY * fptr_glVertexAttribPointerNV)(GLuint,GLint,GLenum,GLsizei,const GLvoid *);
static VALUE gl_VertexAttribPointerNV(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3,VALUE arg4,VALUE arg5,VALUE arg6)
{
	GLuint index;
	GLuint size;
	GLenum type;
	GLsizei stride;

	LOAD_GL_EXT_FUNC(glVertexAttribPointerNV,"GL_NV_vertex_program")

	index = (GLuint)NUM2UINT(arg1);
	size = (GLuint)NUM2UINT(arg2);
	type = (GLenum)NUM2INT(arg3);
	stride = (GLsizei)NUM2UINT(arg4);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	if (CheckBufferBinding(GL_ARRAY_BUFFER_BINDING)) {
		g_VertexAttrib_ptr[index] = arg5;
		fptr_glVertexAttribPointerNV(index,size,type,stride,(GLvoid *)NUM2INT(arg5));
	} else {
		Check_Type(arg5, T_STRING);
		rb_str_freeze(arg5);
		g_VertexAttrib_ptr[index] = arg5;
		fptr_glVertexAttribPointerNV(index,size,type,stride,(GLvoid *)RSTRING(arg5)->ptr);
	}

	CHECK_GLERROR
	return Qnil;
}


static void (APIENTRY * fptr_glGetVertexAttribPointervNV)(GLuint,GLenum,GLvoid **);
static VALUE
gl_GetVertexAttribPointervNV(obj,arg1)
VALUE obj,arg1;
{
	GLuint index;
	LOAD_GL_EXT_FUNC(glGetVertexAttribPointervNV,"GL_NV_vertex_program")
	index =(GLuint) NUM2INT(arg1);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	return g_VertexAttrib_ptr[index];
}

#define PROGRAMPARAM_FUNC(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLenum,GLuint,_type_,_type_,_type_,_type_); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3,arg4,arg5,arg6) \
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6; \
{ \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),_conv_(arg3),_conv_(arg4),_conv_(arg5),_conv_(arg6)); \
	CHECK_GLERROR \
	return Qnil; \
}

PROGRAMPARAM_FUNC(ProgramParameter4dNV,GLdouble,NUM2DBL,"GL_NV_vertex_program")
PROGRAMPARAM_FUNC(ProgramParameter4fNV,GLfloat,NUM2DBL,"GL_NV_vertex_program")

#define PROGRAMPARAM_FUNC_V(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLenum,GLuint,const _type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	_type_ cary[4]; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	_conv_(arg3,cary,4); \
	fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),cary); \
	CHECK_GLERROR \
	return Qnil; \
}

PROGRAMPARAM_FUNC_V(ProgramParameter4dvNV,GLdouble,ary2cdbl,"GL_NV_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramParameter4fvNV,GLfloat,ary2cflt,"GL_NV_vertex_program")

#define GETPROGRAMPARAM_FUNC(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLenum,GLuint,GLenum,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	_type_ cary[4] = {0.0,0.0,0.0,0.0}; \
	VALUE ret; \
	int i; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),NUM2UINT(arg3),cary); \
	ret = rb_ary_new2(4); \
	for(i=0;i<4;i++) \
			rb_ary_push(ret, _conv_(cary[i])); \
	CHECK_GLERROR \
	return ret; \
}

GETPROGRAMPARAM_FUNC(GetProgramParameterdvNV,GLdouble,rb_float_new,"GL_NV_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramParameterfvNV,GLfloat,rb_float_new,"GL_NV_vertex_program")
#undef GETPROGRAMPARAM_FUNC

#define PROGRAMPARAM_MULTI_FUNC_V(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLenum,GLuint,GLuint,const _type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	_type_ *cary; \
	int len; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	len = RARRAY(rb_Array(arg3))->len; \
	if (len<=0 || (len % 4) != 0) \
		rb_raise(rb_eArgError, "Parameter array size must be multiplication of 4"); \
	cary = ALLOC_N(_type_,len); \
	_conv_(arg3,cary,len); \
	fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),len / 4, cary); \
	xfree(cary); \
	CHECK_GLERROR \
	return Qnil; \
}

PROGRAMPARAM_MULTI_FUNC_V(ProgramParameters4dvNV,GLdouble,ary2cdbl,"GL_NV_vertex_program")
PROGRAMPARAM_MULTI_FUNC_V(ProgramParameters4fvNV,GLfloat,ary2cflt,"GL_NV_vertex_program")


#define VERTEXATTRIB_FUNC(_name_,_type_,_conv_,_size_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,TYPELIST##_size_(_type_)); \
static VALUE \
gl_##_name_(obj, index ARGLIST##_size_) \
VALUE obj, index ARGLIST##_size_ ; \
{ \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	fptr_gl##_name_(NUM2UINT(index),FUNCPARAMS##_size_(_type_,_conv_)); \
	CHECK_GLERROR \
	return Qnil; \
}

VERTEXATTRIB_FUNC(VertexAttrib1dNV,GLdouble,NUM2DBL,1,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib1fNV,GLfloat,NUM2DBL,1,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib1sNV,GLshort,NUM2INT,1,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2dNV,GLdouble,NUM2DBL,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2fNV,GLfloat,NUM2DBL,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2sNV,GLshort,NUM2INT,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3dNV,GLdouble,NUM2DBL,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3fNV,GLfloat,NUM2DBL,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3sNV,GLshort,NUM2INT,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4dNV,GLdouble,NUM2DBL,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4fNV,GLfloat,NUM2DBL,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4sNV,GLshort,NUM2INT,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4ubNV,GLubyte,NUM2UINT,4,"GL_NV_vertex_program")
#undef VERTEXATTRIB_FUNC


#define VERTEXATTRIB_FUNC_V(_name_,_type_,_conv_,_size_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint index; \
	_type_ v[_size_]; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_)  \
	index = (GLuint)NUM2UINT(arg1); \
	_conv_(arg2,v,_size_); \
	fptr_gl##_name_(index,v); \
	CHECK_GLERROR \
	return Qnil; \
}

VERTEXATTRIB_FUNC_V(VertexAttrib4ubvNV,GLubyte,ary2cubyte,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4dvNV,GLdouble,ary2cdbl,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4fvNV,GLfloat,ary2cflt,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib4svNV,GLshort,ary2cshort,4,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3dvNV,GLdouble,ary2cdbl,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3fvNV,GLfloat,ary2cflt,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib3svNV,GLshort,ary2cshort,3,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2dvNV,GLdouble,ary2cdbl,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2fvNV,GLfloat,ary2cflt,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib2svNV,GLshort,ary2cshort,2,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1dvNV,GLdouble,ary2cdbl,1,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1fvNV,GLfloat,ary2cflt,1,"GL_NV_vertex_program")
VERTEXATTRIB_FUNC_V(VertexAttrib1svNV,GLshort,ary2cshort,1,"GL_NV_vertex_program")
#undef VERTEXATTRIB_FUNC_V

#define VERTEXATTRIB_MULTI_FUNC_V(_name_,_type_,_conv_,_size_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLsizei,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint index; \
	_type_ *cary; \
	int len; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_)  \
	len = RARRAY(rb_Array(arg2))->len; \
	if (len<=0 || (len % _size_) != 0) \
		rb_raise(rb_eArgError, "Parameter array size must be multiplication of %i",_size_); \
	cary = ALLOC_N(_type_,len); \
	index = (GLuint)NUM2UINT(arg1); \
	_conv_(arg2,cary,len); \
	fptr_gl##_name_(index,len / _size_,cary); \
	xfree(cary); \
	CHECK_GLERROR \
	return Qnil; \
}

VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs4ubvNV,GLubyte,ary2cubyte,4,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs4dvNV,GLdouble,ary2cdbl,4,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs4fvNV,GLfloat,ary2cflt,4,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs4svNV,GLshort,ary2cshort,4,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs3dvNV,GLdouble,ary2cdbl,3,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs3fvNV,GLfloat,ary2cflt,3,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs3svNV,GLshort,ary2cshort,3,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs2dvNV,GLdouble,ary2cdbl,2,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs2fvNV,GLfloat,ary2cflt,2,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs2svNV,GLshort,ary2cshort,2,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs1dvNV,GLdouble,ary2cdbl,1,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs1fvNV,GLfloat,ary2cflt,1,"GL_NV_vertex_program")
VERTEXATTRIB_MULTI_FUNC_V(VertexAttribs1svNV,GLshort,ary2cshort,1,"GL_NV_vertex_program")
#undef VERTEXATTRIB_MULTI_FUNC_V

#define GETVERTEXATTRIB_FUNC(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLenum,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint index; \
	GLenum pname; \
	_type_ params[4] = {0,0,0,0}; \
	GLint size; \
	GLint i; \
	VALUE retary; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	index = (GLuint)NUM2UINT(arg1); \
	pname = (GLenum)NUM2INT(arg2); \
	if (pname==GL_CURRENT_ATTRIB_NV) \
		size = 4; \
	else \
		size = 1; \
	fptr_gl##_name_(index,pname,params); \
	retary = rb_ary_new2(size); \
	for(i=0;i<size;i++) \
		rb_ary_push(retary, _conv_(params[i])); \
	CHECK_GLERROR \
	return retary; \
}

GETVERTEXATTRIB_FUNC(GetVertexAttribdvNV,GLdouble,rb_float_new,"GL_NV_vertex_program")
GETVERTEXATTRIB_FUNC(GetVertexAttribfvNV,GLfloat,rb_float_new,"GL_NV_vertex_program")
GETVERTEXATTRIB_FUNC(GetVertexAttribivNV,GLint,INT2NUM,"GL_NV_vertex_program")
#undef GETVERTEXATTRIB_FUNC

static void (APIENTRY * fptr_glTrackMatrixNV)(GLenum,GLuint,GLenum,GLenum);
static VALUE gl_TrackMatrixNV(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3,VALUE arg4)
{
	LOAD_GL_EXT_FUNC(glTrackMatrixNV,"GL_NV_vertex_program")
	fptr_glTrackMatrixNV(NUM2UINT(arg1),NUM2UINT(arg2),NUM2UINT(arg3),NUM2UINT(arg4));
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetTrackMatrixivNV)(GLenum,GLuint,GLenum,GLint *);
static VALUE gl_GetTrackMatrixivNV(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
	GLint ret = 0;
	LOAD_GL_EXT_FUNC(glGetTrackMatrixivNV,"GL_NV_vertex_program")
	fptr_glGetTrackMatrixivNV(NUM2UINT(arg1),NUM2UINT(arg2),NUM2UINT(arg3),&ret);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glRequestResidentProgramsNV)(GLsizei, GLuint *);
static VALUE gl_RequestResidentProgramsNV(VALUE obj,VALUE arg1)
{
	LOAD_GL_EXT_FUNC(glRequestResidentProgramsNV,"GL_NV_vertex_program")
	if (TYPE(arg1)==T_ARRAY) {
		GLsizei n;
		GLuint *programs;
		n = RARRAY(arg1)->len;
		programs = ALLOC_N(GLuint,n);
		ary2cuint(arg1,programs,n); 
		fptr_glRequestResidentProgramsNV( n, programs);
		xfree(programs);
	} else {
		GLuint program;
		program = NUM2INT(arg1);
		fptr_glRequestResidentProgramsNV( 1, &program);
	}
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glAreProgramsResidentNV)(GLsizei, const GLuint *, GLboolean *);
static VALUE gl_AreProgramsResidentNV(VALUE obj,VALUE arg1)
{
	GLuint *programs;
	GLboolean *residences;
	GLsizei size;
	GLboolean r;
	VALUE retary;
	VALUE ary;
	int i;
	LOAD_GL_EXT_FUNC(glAreProgramsResidentNV,"GL_NV_vertex_program")
	ary = rb_Array(arg1);
	size = RARRAY(ary)->len;
	programs = ALLOC_N(GLuint,size);
	residences = ALLOC_N(GLboolean,size);
	ary2cuint(ary,programs,size);	
	r = fptr_glAreProgramsResidentNV(size,programs,residences);
	retary = rb_ary_new2(size);
	if (r==GL_TRUE) { /* all are resident */
		for(i=0;i<size;i++)
			rb_ary_push(retary, INT2NUM(GL_TRUE));
	} else {
		for(i=0;i<size;i++)
			rb_ary_push(retary, INT2NUM(residences[i]));
	}
	xfree(programs);
	xfree(residences);
	CHECK_GLERROR
	return retary;
}

/* #261 GL_NV_occlusion_query */
static void (APIENTRY * fptr_glGenOcclusionQueriesNV)(GLsizei,GLuint *);
static VALUE gl_GenOcclusionQueriesNV(VALUE obj,VALUE arg1)
{
	GLsizei n;
	GLuint *occlusionqueries;
	VALUE ret;
	int i;
	LOAD_GL_EXT_FUNC(glGenOcclusionQueriesNV,"GL_NV_occlusion_query")
	n = (GLsizei)NUM2UINT(arg1);
	occlusionqueries = ALLOC_N(GLuint, n);
	fptr_glGenOcclusionQueriesNV(n,occlusionqueries);
	ret = rb_ary_new2(n);
	for (i = 0; i < n; i++)
		rb_ary_push(ret, INT2NUM(occlusionqueries[i]));
	xfree(occlusionqueries);
	CHECK_GLERROR
	return ret;
}

static void (APIENTRY * fptr_glDeleteOcclusionQueriesNV)(GLsizei,const GLuint *);
static VALUE gl_DeleteOcclusionQueriesNV(VALUE obj,VALUE arg1)
{
	GLsizei n;
	LOAD_GL_EXT_FUNC(glDeleteOcclusionQueriesNV,"GL_NV_occlusion_query")
	if (TYPE(arg1)==T_ARRAY) {
		GLuint *occlusionqueries;
		n = RARRAY(arg1)->len;
		occlusionqueries = ALLOC_N(GLuint,n);
		ary2cuint(arg1,occlusionqueries,n); 
		fptr_glDeleteOcclusionQueriesNV(n,occlusionqueries);
		xfree(occlusionqueries);
	} else {
		GLuint occlusionquery;
		occlusionquery = NUM2UINT(arg1);
		fptr_glDeleteOcclusionQueriesNV(1,&occlusionquery);
	}
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glIsOcclusionQueryNV)(GLuint);
static VALUE gl_IsOcclusionQueryNV(VALUE obj,VALUE arg1)
{
	GLboolean ret = 0;
	LOAD_GL_EXT_FUNC(glIsOcclusionQueryNV,"GL_NV_occlusion_query")
	ret = fptr_glIsOcclusionQueryNV(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

GL_EXT_SIMPLE_FUNC_LOAD(BeginOcclusionQueryNV,1,GLuint,NUM2UINT,"GL_NV_occlusion_query")
GL_EXT_SIMPLE_FUNC_LOAD(EndOcclusionQueryNV,0,0,0,"GL_NV_occlusion_query")

#define GETOCCLUSIONQUERY_FUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLenum,_type_ *); \
static VALUE gl_##_name_(VALUE obj,VALUE arg1,VALUE arg2) \
{ \
	_type_ ret = 0; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_NV_occlusion_query") \
	fptr_gl##_name_(NUM2INT(arg1),NUM2INT(arg2),&ret); \
	CHECK_GLERROR \
	return _conv_(ret); \
}

GETOCCLUSIONQUERY_FUNC(GetOcclusionQueryivNV,GLint,INT2NUM)
GETOCCLUSIONQUERY_FUNC(GetOcclusionQueryuivNV,GLuint,INT2NUM)
#undef GETOCCLUSIONQUERY_FUNC

/* #282 GL_NV_fragment_program */

#define PROGRAMNAMEDPARAM_FUNC(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLsizei,const GLubyte *,_type_,_type_,_type_,_type_); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3,arg4,arg5,arg6) \
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6; \
{ \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	Check_Type(arg2,T_STRING); \
	fptr_gl##_name_(NUM2UINT(arg1),RSTRING(arg2)->len,(GLubyte *)RSTRING(arg2)->ptr,_conv_(arg3),_conv_(arg4),_conv_(arg5),_conv_(arg6)); \
	CHECK_GLERROR \
	return Qnil; \
}

PROGRAMNAMEDPARAM_FUNC(ProgramNamedParameter4dNV,GLdouble,NUM2DBL,"GL_NV_fragment_program")
PROGRAMNAMEDPARAM_FUNC(ProgramNamedParameter4fNV,GLfloat,NUM2DBL,"GL_NV_fragment_program")
#undef PROGRAMNAMEDPARAM_FUNC

#define PROGRAMNAMEDPARAM_FUNC_V(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLsizei,const GLubyte *,const _type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	_type_ cary[4]; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	Check_Type(arg2,T_STRING); \
	_conv_(arg3,cary,4); \
	fptr_gl##_name_(NUM2UINT(arg1),RSTRING(arg2)->len,(GLubyte *)RSTRING(arg2)->ptr,cary); \
	CHECK_GLERROR \
	return Qnil; \
}

PROGRAMNAMEDPARAM_FUNC_V(ProgramNamedParameter4dvNV,GLdouble,ary2cdbl,"GL_NV_vertex_program")
PROGRAMNAMEDPARAM_FUNC_V(ProgramNamedParameter4fvNV,GLfloat,ary2cflt,"GL_NV_vertex_program")
#undef PROGRAMNAMEDPARAM_FUNC_V

#define GETPROGRAMNAMEDPARAM_FUNC(_name_,_type_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLsizei,const GLubyte *,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	_type_ cary[4] = {0.0,0.0,0.0,0.0}; \
	VALUE ret; \
	int i; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	Check_Type(arg2,T_STRING); \
	fptr_gl##_name_(NUM2UINT(arg1),RSTRING(arg2)->len,(GLubyte *)RSTRING(arg2)->ptr,cary); \
	ret = rb_ary_new2(4); \
	for(i=0;i<4;i++) \
			rb_ary_push(ret, rb_float_new(cary[i])); \
	CHECK_GLERROR \
	return ret; \
}

GETPROGRAMNAMEDPARAM_FUNC(GetProgramNamedParameterdvNV,GLdouble,"GL_NV_vertex_program")
GETPROGRAMNAMEDPARAM_FUNC(GetProgramNamedParameterfvNV,GLfloat,"GL_NV_vertex_program")
#undef GETPROGRAMNAMEDPARAM_FUNC

/* #322 GL_NV_gpu_program4 */
PROGRAMPARAM_FUNC(ProgramLocalParameterI4iNV,GLint,NUM2INT,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC(ProgramLocalParameterI4uiNV,GLuint,NUM2UINT,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC(ProgramEnvParameterI4iNV,GLint,NUM2INT,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC(ProgramEnvParameterI4uiNV,GLuint,NUM2UINT,"GL_NV_gpu_program4")

PROGRAMPARAM_FUNC_V(ProgramLocalParameterI4ivNV,GLint,ary2cint,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC_V(ProgramLocalParameterI4uivNV,GLuint,ary2cuint,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC_V(ProgramEnvParameterI4ivNV,GLint,ary2cint,"GL_NV_gpu_program4")
PROGRAMPARAM_FUNC_V(ProgramEnvParameterI4uivNV,GLuint,ary2cuint,"GL_NV_gpu_program4")

PROGRAMPARAM_MULTI_FUNC_V(ProgramLocalParametersI4ivNV,GLint,ary2cint,"GL_NV_gpu_program4")
PROGRAMPARAM_MULTI_FUNC_V(ProgramLocalParametersI4uivNV,GLuint,ary2cuint,"GL_NV_gpu_program4")
PROGRAMPARAM_MULTI_FUNC_V(ProgramEnvParametersI4ivNV,GLint,ary2cint,"GL_NV_gpu_program4")
PROGRAMPARAM_MULTI_FUNC_V(ProgramEnvParametersI4uivNV,GLuint,ary2cuint,"GL_NV_gpu_program4")

#undef PROGRAMPARAM_MULTI_FUNC_V
#undef PROGRAMPARAM_FUNC_V
#undef PROGRAMPARAM_FUNC

#define GETPROGRAMPARAM_FUNC_2(_name_,_type_,_conv_,_extension_) \
static void (APIENTRY * fptr_gl##_name_)(GLenum,GLuint,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	_type_ cary[4] = {0.0,0.0,0.0,0.0}; \
	VALUE ret; \
	int i; \
	LOAD_GL_EXT_FUNC(gl##_name_,_extension_) \
	fptr_gl##_name_(NUM2UINT(arg1),NUM2UINT(arg2),cary); \
	ret = rb_ary_new2(4); \
	for(i=0;i<4;i++) \
			rb_ary_push(ret, _conv_(cary[i])); \
	CHECK_GLERROR \
	return ret; \
}

GETPROGRAMPARAM_FUNC_2(GetProgramLocalParameterIivNV,GLint,INT2NUM,"GL_NV_gpu_program4")
GETPROGRAMPARAM_FUNC_2(GetProgramLocalParameterIuivNV,GLuint,UINT2NUM,"GL_NV_gpu_program4")
GETPROGRAMPARAM_FUNC_2(GetProgramEnvParameterIivNV,GLint,INT2NUM,"GL_NV_gpu_program4")
GETPROGRAMPARAM_FUNC_2(GetProgramEnvParameterIuivNV,GLuint,UINT2NUM,"GL_NV_gpu_program4")
#undef GETPROGRAMPARAM_FUNC_2


/* #334 GL_NV_depth_buffer_float */
GL_EXT_SIMPLE_FUNC_LOAD(DepthRangedNV,2,GLdouble,NUM2DBL,"GL_NV_depth_buffer_float")
GL_EXT_SIMPLE_FUNC_LOAD(ClearDepthdNV,1,GLdouble,NUM2DBL,"GL_NV_depth_buffer_float")
GL_EXT_SIMPLE_FUNC_LOAD(DepthBoundsdNV,2,GLdouble,NUM2DBL,"GL_NV_depth_buffer_float")

/* #336 GL_NV_framebuffer_multisample_coverage */
static void (APIENTRY * fptr_glRenderbufferStorageMultisampleCoverageNV)(GLenum,GLsizei,GLsizei,GLenum,GLsizei,GLsizei);
static VALUE gl_RenderbufferStorageMultisampleCoverageNV(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	LOAD_GL_EXT_FUNC(glRenderbufferStorageMultisampleCoverageNV,"GL_NV_framebuffer_multisample_coverage")
	fptr_glRenderbufferStorageMultisampleCoverageNV(NUM2UINT(arg1),NUM2INT(arg2),NUM2INT(arg3),
																									NUM2UINT(arg4),NUM2INT(arg5),NUM2INT(arg6));
	CHECK_GLERROR
	return Qnil;
}

void gl_init_functions_ext_nv(VALUE module)
{
/* #222 GL_NV_fence */
	rb_define_module_function(module, "glGenFencesNV", gl_GenFencesNV, 1);
	rb_define_module_function(module, "glDeleteFencesNV", gl_DeleteFencesNV, 1);
	rb_define_module_function(module, "glSetFenceNV", gl_SetFenceNV, 2);
	rb_define_module_function(module, "glTestFenceNV", gl_TestFenceNV, 1);
	rb_define_module_function(module, "glFinishFenceNV", gl_FinishFenceNV, 1);
	rb_define_module_function(module, "glIsFenceNV", gl_IsFenceNV, 1);
	rb_define_module_function(module, "glGetFenceivNV", gl_GetFenceivNV, 2);

/* #233 GL_NV_vertex_program */
	rb_define_module_function(module, "glLoadProgramNV", gl_LoadProgramNV, 3);
	rb_define_module_function(module, "glGetProgramStringNV", gl_GetProgramStringNV, 2);
	rb_define_module_function(module, "glGetProgramivNV", gl_GetProgramivNV, 2);
	rb_define_module_function(module, "glBindProgramNV", gl_BindProgramNV, 2);
	rb_define_module_function(module, "glGenProgramsNV", gl_GenProgramsNV, 1);
	rb_define_module_function(module, "glDeleteProgramsNV", gl_DeleteProgramsNV, 1);
	rb_define_module_function(module, "glIsProgramNV", gl_IsProgramNV, 1);
	rb_define_module_function(module, "glExecuteProgramNV", gl_ExecuteProgramNV, 3);
	rb_define_module_function(module, "glVertexAttribPointerNV", gl_VertexAttribPointerNV, 5);
	rb_define_module_function(module, "glGetVertexAttribPointervNV", gl_GetVertexAttribPointervNV, 1);
	rb_define_module_function(module, "glProgramParameter4dNV", gl_ProgramParameter4dNV, 6);
	rb_define_module_function(module, "glProgramParameter4fNV", gl_ProgramParameter4fNV, 6);
	rb_define_module_function(module, "glProgramParameter4dvNV", gl_ProgramParameter4dvNV, 3);
	rb_define_module_function(module, "glProgramParameter4fvNV", gl_ProgramParameter4fvNV, 3);
	rb_define_module_function(module, "glProgramParameters4dvNV", gl_ProgramParameters4dvNV, 3);
	rb_define_module_function(module, "glProgramParameters4fvNV", gl_ProgramParameters4fvNV, 3);
	rb_define_module_function(module, "glGetProgramParameterdvNV", gl_GetProgramParameterdvNV, 3);
	rb_define_module_function(module, "glGetProgramParameterfvNV", gl_GetProgramParameterfvNV, 3);
	rb_define_module_function(module, "glVertexAttrib1dNV", gl_VertexAttrib1dNV, 2);
	rb_define_module_function(module, "glVertexAttrib1fNV", gl_VertexAttrib1fNV, 2);
	rb_define_module_function(module, "glVertexAttrib1sNV", gl_VertexAttrib1sNV, 2);
	rb_define_module_function(module, "glVertexAttrib2dNV", gl_VertexAttrib2dNV, 3);
	rb_define_module_function(module, "glVertexAttrib2fNV", gl_VertexAttrib2fNV, 3);
	rb_define_module_function(module, "glVertexAttrib2sNV", gl_VertexAttrib2sNV, 3);
	rb_define_module_function(module, "glVertexAttrib3dNV", gl_VertexAttrib3dNV, 4);
	rb_define_module_function(module, "glVertexAttrib3fNV", gl_VertexAttrib3fNV, 4);
	rb_define_module_function(module, "glVertexAttrib3sNV", gl_VertexAttrib3sNV, 4);
	rb_define_module_function(module, "glVertexAttrib4dNV", gl_VertexAttrib4dNV, 5);
	rb_define_module_function(module, "glVertexAttrib4fNV", gl_VertexAttrib4fNV, 5);
	rb_define_module_function(module, "glVertexAttrib4sNV", gl_VertexAttrib4sNV, 5);
	rb_define_module_function(module, "glVertexAttrib4ubNV", gl_VertexAttrib4ubNV, 5);
	rb_define_module_function(module, "glVertexAttrib1dvNV", gl_VertexAttrib1dvNV, 2);
	rb_define_module_function(module, "glVertexAttrib1fvNV", gl_VertexAttrib1fvNV, 2);
	rb_define_module_function(module, "glVertexAttrib1svNV", gl_VertexAttrib1svNV, 2);
	rb_define_module_function(module, "glVertexAttrib2dvNV", gl_VertexAttrib2dvNV, 2);
	rb_define_module_function(module, "glVertexAttrib2fvNV", gl_VertexAttrib2fvNV, 2);
	rb_define_module_function(module, "glVertexAttrib2svNV", gl_VertexAttrib2svNV, 2);
	rb_define_module_function(module, "glVertexAttrib3dvNV", gl_VertexAttrib3dvNV, 2);
	rb_define_module_function(module, "glVertexAttrib3fvNV", gl_VertexAttrib3fvNV, 2);
	rb_define_module_function(module, "glVertexAttrib3svNV", gl_VertexAttrib3svNV, 2);
	rb_define_module_function(module, "glVertexAttrib4dvNV", gl_VertexAttrib4dvNV, 2);
	rb_define_module_function(module, "glVertexAttrib4fvNV", gl_VertexAttrib4fvNV, 2);
	rb_define_module_function(module, "glVertexAttrib4svNV", gl_VertexAttrib4svNV, 2);
	rb_define_module_function(module, "glVertexAttrib4ubvNV", gl_VertexAttrib4ubvNV, 2);
	rb_define_module_function(module, "glVertexAttribs1dvNV", gl_VertexAttribs1dvNV, 2);
	rb_define_module_function(module, "glVertexAttribs1fvNV", gl_VertexAttribs1fvNV, 2);
	rb_define_module_function(module, "glVertexAttribs1svNV", gl_VertexAttribs1svNV, 2);
	rb_define_module_function(module, "glVertexAttribs2dvNV", gl_VertexAttribs2dvNV, 2);
	rb_define_module_function(module, "glVertexAttribs2fvNV", gl_VertexAttribs2fvNV, 2);
	rb_define_module_function(module, "glVertexAttribs2svNV", gl_VertexAttribs2svNV, 2);
	rb_define_module_function(module, "glVertexAttribs3dvNV", gl_VertexAttribs3dvNV, 2);
	rb_define_module_function(module, "glVertexAttribs3fvNV", gl_VertexAttribs3fvNV, 2);
	rb_define_module_function(module, "glVertexAttribs3svNV", gl_VertexAttribs3svNV, 2);
	rb_define_module_function(module, "glVertexAttribs4dvNV", gl_VertexAttribs4dvNV, 2);
	rb_define_module_function(module, "glVertexAttribs4fvNV", gl_VertexAttribs4fvNV, 2);
	rb_define_module_function(module, "glVertexAttribs4svNV", gl_VertexAttribs4svNV, 2);
	rb_define_module_function(module, "glVertexAttribs4ubvNV", gl_VertexAttribs4ubvNV, 2);
	rb_define_module_function(module, "glGetVertexAttribdvNV", gl_GetVertexAttribdvNV, 2);
	rb_define_module_function(module, "glGetVertexAttribfvNV", gl_GetVertexAttribfvNV, 2);
	rb_define_module_function(module, "glGetVertexAttribivNV", gl_GetVertexAttribivNV, 2);
	rb_define_module_function(module, "glTrackMatrixNV", gl_TrackMatrixNV, 4);
	rb_define_module_function(module, "glGetTrackMatrixivNV", gl_GetTrackMatrixivNV, 3);
	rb_define_module_function(module, "glRequestResidentProgramsNV", gl_RequestResidentProgramsNV, 1);
	rb_define_module_function(module, "glAreProgramsResidentNV", gl_AreProgramsResidentNV, 1);

/* #261 GL_NV_occlusion_query */
	rb_define_module_function(module, "glGenOcclusionQueriesNV", gl_GenOcclusionQueriesNV, 1);
	rb_define_module_function(module, "glDeleteOcclusionQueriesNV", gl_DeleteOcclusionQueriesNV, 1);
	rb_define_module_function(module, "glIsOcclusionQueryNV", gl_IsOcclusionQueryNV, 1);
	rb_define_module_function(module, "glBeginOcclusionQueryNV", gl_BeginOcclusionQueryNV, 1);
	rb_define_module_function(module, "glEndOcclusionQueryNV", gl_EndOcclusionQueryNV, 0);
	rb_define_module_function(module, "glGetOcclusionQueryivNV", gl_GetOcclusionQueryivNV, 2);
	rb_define_module_function(module, "glGetOcclusionQueryuivNV", gl_GetOcclusionQueryuivNV, 2);

/* #282 GL_NV_fragment_program */
	rb_define_module_function(module, "glProgramNamedParameter4fNV", gl_ProgramNamedParameter4fNV, 6);
	rb_define_module_function(module, "glProgramNamedParameter4dNV", gl_ProgramNamedParameter4dNV, 6);
	rb_define_module_function(module, "glProgramNamedParameter4fvNV", gl_ProgramNamedParameter4fvNV, 3);
	rb_define_module_function(module, "glProgramNamedParameter4dvNV", gl_ProgramNamedParameter4dvNV, 3);
	rb_define_module_function(module, "glGetProgramNamedParameterdvNV", gl_GetProgramNamedParameterdvNV, 2);
	rb_define_module_function(module, "glGetProgramNamedParameterfvNV", gl_GetProgramNamedParameterfvNV, 2);

/* #322 GL_NV_gpu_program4 */
	rb_define_module_function(module, "glProgramLocalParameterI4iNV", gl_ProgramLocalParameterI4iNV, 6);
	rb_define_module_function(module, "glProgramLocalParameterI4uiNV", gl_ProgramLocalParameterI4uiNV, 6);
	rb_define_module_function(module, "glProgramLocalParameterI4ivNV", gl_ProgramLocalParameterI4ivNV, 3);
	rb_define_module_function(module, "glProgramLocalParameterI4uivNV", gl_ProgramLocalParameterI4uivNV, 3);
	rb_define_module_function(module, "glProgramLocalParametersI4ivNV", gl_ProgramLocalParametersI4ivNV, 3);
	rb_define_module_function(module, "glProgramLocalParametersI4uivNV", gl_ProgramLocalParametersI4uivNV, 3);
	rb_define_module_function(module, "glGetProgramLocalParameterIivNV", gl_GetProgramLocalParameterIivNV, 2);
	rb_define_module_function(module, "glGetProgramLocalParameterIuivNV", gl_GetProgramLocalParameterIuivNV, 2);
	rb_define_module_function(module, "glProgramEnvParameterI4iNV", gl_ProgramEnvParameterI4iNV, 6);
	rb_define_module_function(module, "glProgramEnvParameterI4uiNV", gl_ProgramEnvParameterI4uiNV, 6);
	rb_define_module_function(module, "glProgramEnvParameterI4ivNV", gl_ProgramEnvParameterI4ivNV, 3);
	rb_define_module_function(module, "glProgramEnvParameterI4uivNV", gl_ProgramEnvParameterI4uivNV, 3);
	rb_define_module_function(module, "glProgramEnvParametersI4ivNV", gl_ProgramEnvParametersI4ivNV, 3);
	rb_define_module_function(module, "glProgramEnvParametersI4uivNV", gl_ProgramEnvParametersI4uivNV, 3);
	rb_define_module_function(module, "glGetProgramEnvParameterIivNV", gl_GetProgramEnvParameterIivNV, 2);
	rb_define_module_function(module, "glGetProgramEnvParameterIuivNV", gl_GetProgramEnvParameterIuivNV, 2);

/* #334 GL_NV_depth_buffer_float */
	rb_define_module_function(module, "glDepthRangedNV", gl_DepthRangedNV, 2);
	rb_define_module_function(module, "glClearDepthdNV", gl_ClearDepthdNV, 1);
	rb_define_module_function(module, "glDepthBoundsdNV", gl_DepthBoundsdNV, 2);

/* #336 GL_NV_framebuffer_multisample_coverage */
	rb_define_module_function(module, "glRenderbufferStorageMultisampleCoverageNV", gl_RenderbufferStorageMultisampleCoverageNV, 6);

}
