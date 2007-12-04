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

/* OpenGL ARB extensions */

/* #3 GL_ARB_transpose_matrix */
#define TRANSPOSEMATRIX_FUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(const _type_[]); \
static VALUE \
gl_##_name_(obj,arg1) \
VALUE obj,arg1; \
{ \
	_type_ m[4*4]; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_transpose_matrix") \
	_conv_(arg1, m, 4, 4); \
	fptr_gl##_name_(m); \
	CHECK_GLERROR \
	return Qnil; \
}

TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixfARB,GLfloat,ary2cmatfloat)
TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixdARB,GLdouble,ary2cmatdouble)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixfARB,GLfloat,ary2cmatfloat)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixdARB,GLdouble,ary2cmatdouble)

#undef TRANSPOSEMATRIX_FUNC

/* #5 GL_ARB_multisample */
static void (APIENTRY * fptr_glSampleCoverageARB)(GLclampf,GLboolean);
static VALUE gl_SampleCoverageARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glSampleCoverageARB,"GL_ARB_multisample")
	fptr_glSampleCoverageARB((GLclampf)NUM2DBL(arg1),(GLboolean)NUM2INT(arg2));
	CHECK_GLERROR
	return Qnil;
}

/* #14 GL_ARB_point_parameters */

static void (APIENTRY * fptr_glPointParameterfARB)(GLenum,GLfloat);
static VALUE gl_PointParameterfARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glPointParameterfARB,"GL_ARB_point_parameters")
	fptr_glPointParameterfARB(NUM2UINT(arg1),NUM2DBL(arg2));
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glPointParameterfvARB)(GLenum,GLfloat *);
static VALUE gl_PointParameterfvARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLfloat params[3] = {0.0,0.0,0.0};
	GLenum pname;
	GLint size;
	LOAD_GL_EXT_FUNC(glPointParameterfvARB,"GL_ARB_point_parameters")
	pname = NUM2UINT(arg1);
	Check_Type(arg2,T_ARRAY);
	if (pname==GL_POINT_DISTANCE_ATTENUATION)
		size = 3;
	else
		size = 1;
	ary2cflt(arg2,params,size);
	fptr_glPointParameterfvARB(pname,params);
	CHECK_GLERROR
	return Qnil;
}

/* #25 GL_ARB_window_pos */

GL_EXT_SIMPLE_FUNC_LOAD(WindowPos2dARB,2,GLdouble,NUM2DBL,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos2fARB,2,GLfloat,NUM2DBL,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos2iARB,2,GLint,NUM2INT,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos2sARB,2,GLshort,NUM2INT,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos3dARB,3,GLdouble,NUM2DBL,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos3fARB,3,GLfloat,NUM2DBL,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos3iARB,3,GLint,NUM2INT,"GL_ARB_window_pos")
GL_EXT_SIMPLE_FUNC_LOAD(WindowPos3sARB,3,GLshort,NUM2INT,"GL_ARB_window_pos")

#define WINDOWPOSFUNCV(_name_,_type_,_conv_,_size_,_ext_) \
static void (APIENTRY * fptr_gl##_name_)(const _type_ *); \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	_type_ cary[_size_]; \
	LOAD_GL_EXT_FUNC(gl##_name_,_ext_) \
	Check_Type(arg1,T_ARRAY); \
	if (RARRAY(arg1)->len != _size_) \
		rb_raise(rb_eArgError, "Incorrect array length - must have '%i' elements.",_size_); \
	_conv_(arg1,cary,_size_); \
	fptr_gl##_name_(cary); \
	CHECK_GLERROR \
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
static void (APIENTRY * fptr_glProgramStringARB)(GLenum,GLenum,GLsizei,const void *);
static VALUE gl_ProgramStringARB(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3)
{
	LOAD_GL_EXT_FUNC(glProgramStringARB,"GL_ARB_vertex_program")
	Check_Type(arg3,T_STRING);
	fptr_glProgramStringARB(NUM2INT(arg1),NUM2INT(arg2),RSTRING(arg3)->len,RSTRING(arg3)->ptr);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetProgramivARB)(GLenum,GLenum,GLint *);
static VALUE gl_GetProgramivARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLint ret = 0;
	LOAD_GL_EXT_FUNC(glGetProgramivARB,"GL_ARB_vertex_program")
	fptr_glGetProgramivARB(NUM2INT(arg1),NUM2INT(arg2),&ret);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetProgramStringARB)(GLenum,GLenum,void *string);
static VALUE gl_GetProgramStringARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	GLsizei len = 0;
	char *buffer;
	VALUE ret_buffer;

	LOAD_GL_EXT_FUNC(glGetProgramStringARB,"GL_ARB_vertex_program")
	LOAD_GL_EXT_FUNC(glGetProgramivARB,"GL_ARB_vertex_program")

	fptr_glGetProgramivARB(NUM2INT(arg1),GL_PROGRAM_LENGTH_ARB,&len);
	CHECK_GLERROR
	if (len<=0)
		return rb_str_new2("");
	
	buffer = ALLOC_N(GLchar,len+1);
	memset(buffer,0,sizeof(GLchar) * (len+1));
		fptr_glGetProgramStringARB(NUM2INT(arg1),NUM2INT(arg2),buffer);
	ret_buffer = rb_str_new2(buffer);
	xfree(buffer);

	CHECK_GLERROR
	return ret_buffer;
}

static void (APIENTRY * fptr_glBindProgramARB)(GLenum,GLuint);
static VALUE gl_BindProgramARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glBindProgramARB,"GL_ARB_vertex_program")
	fptr_glBindProgramARB(NUM2INT(arg1),NUM2UINT(arg2));
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGenProgramsARB)(GLsizei, GLuint *);
static VALUE gl_GenProgramsARB(VALUE obj,VALUE arg1)
{
	GLsizei n;
	GLuint *programs;
	RArray *ret;
	int i;

	LOAD_GL_EXT_FUNC(glGenProgramsARB,"GL_ARB_vertex_program")
	n = (GLsizei)NUM2UINT(arg1);
	programs = ALLOC_N(GLuint, n);
	fptr_glGenProgramsARB(n,programs);
	ret = RARRAY(rb_ary_new2(n));
	for (i = 0; i < n; i++)
		rb_ary_push((VALUE)ret, INT2NUM(programs[i]));
	xfree(programs);
	CHECK_GLERROR
	return (VALUE)ret;
}

static void (APIENTRY * fptr_glDeleteProgramsARB)(GLsizei,const GLuint *);
static VALUE gl_DeleteProgramsARB(VALUE obj,VALUE arg1)
{
	LOAD_GL_EXT_FUNC(glDeleteProgramsARB,"GL_ARB_vertex_program")
	if (TYPE(arg1)==T_ARRAY) {
		GLsizei n;
		GLuint *programs;
		n = RARRAY(arg1)->len;
		programs = ALLOC_N(GLuint,n);
		ary2cuint(arg1,programs,n); 
		fptr_glDeleteProgramsARB( n, programs);
		xfree(programs);
	} else {
		GLuint program;
		program = NUM2INT(arg1);
		fptr_glDeleteProgramsARB( 1, &program);
	}
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glIsProgramARB)(GLuint);
static VALUE gl_IsProgramARB(VALUE obj,VALUE arg1)
{
	GLboolean ret = 0;
	LOAD_GL_EXT_FUNC(glIsProgramARB,"GL_ARB_vertex_program")
	ret = fptr_glIsProgramARB(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

GL_EXT_SIMPLE_FUNC_LOAD(EnableVertexAttribArrayARB,1,GLuint,NUM2UINT,"GL_ARB_vertex_program")
GL_EXT_SIMPLE_FUNC_LOAD(DisableVertexAttribArrayARB,1,GLuint,NUM2UINT,"GL_ARB_vertex_program")

extern VALUE g_VertexAttrib_ptr[];

static void (APIENTRY * fptr_glVertexAttribPointerARB)(GLuint,GLint,GLenum,GLboolean,GLsizei,const GLvoid *);
static VALUE gl_VertexAttribPointerARB(VALUE obj,VALUE arg1,VALUE arg2,VALUE arg3,VALUE arg4,VALUE arg5,VALUE arg6)
{
	GLuint index;
	GLuint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;

	LOAD_GL_EXT_FUNC(glVertexAttribPointerARB,"GL_ARB_vertex_program")

	index = (GLuint)NUM2UINT(arg1);
	size = (GLuint)NUM2UINT(arg2);
	type = (GLenum)NUM2INT(arg3);
	normalized = (GLboolean)NUM2INT(arg4);
	stride = (GLsizei)NUM2UINT(arg5);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	if (CheckBufferBinding(GL_ARRAY_BUFFER_BINDING)) {
		g_VertexAttrib_ptr[index] = arg6;
		fptr_glVertexAttribPointerARB(index,size,type,normalized,stride,(GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6, T_STRING);
		rb_str_freeze(arg6);
		g_VertexAttrib_ptr[index] = arg6;
		fptr_glVertexAttribPointerARB(index,size,type,normalized,stride,(GLvoid *)RSTRING(arg6)->ptr);
	}

	CHECK_GLERROR
	return Qnil;
}


static void (APIENTRY * fptr_glGetVertexAttribPointervARB)(GLuint,GLenum,GLvoid **);
static VALUE
gl_GetVertexAttribPointervARB(obj,arg1)
VALUE obj,arg1;
{
	GLuint index;
	LOAD_GL_EXT_FUNC(glGetVertexAttribPointervARB,"GL_ARB_vertex_program")
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

PROGRAMPARAM_FUNC(ProgramEnvParameter4dARB,GLdouble,NUM2DBL,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC(ProgramEnvParameter4fARB,GLfloat,NUM2DBL,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC(ProgramLocalParameter4dARB,GLdouble,NUM2DBL,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC(ProgramLocalParameter4fARB,GLfloat,NUM2DBL,"GL_ARB_vertex_program")
#undef PROGRAMPARAM_FUNC


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

PROGRAMPARAM_FUNC_V(ProgramEnvParameter4dvARB,GLdouble,ary2cdbl,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramEnvParameter4fvARB,GLfloat,ary2cflt,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramLocalParameter4dvARB,GLdouble,ary2cdbl,"GL_ARB_vertex_program")
PROGRAMPARAM_FUNC_V(ProgramLocalParameter4fvARB,GLfloat,ary2cflt,"GL_ARB_vertex_program")
#undef PROGRAMPARAM_FUNC_V

#define GETPROGRAMPARAM_FUNC(_name_,_type_,_extension_) \
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
			rb_ary_push(ret, rb_float_new(cary[i])); \
	CHECK_GLERROR \
	return ret; \
}

GETPROGRAMPARAM_FUNC(GetProgramEnvParameterdvARB,GLdouble,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramEnvParameterfvARB,GLfloat,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramLocalParameterdvARB,GLdouble,"GL_ARB_vertex_program")
GETPROGRAMPARAM_FUNC(GetProgramLocalParameterfvARB,GLfloat,"GL_ARB_vertex_program")

#undef GETPROGRAMPARAM_FUNC

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

VERTEXATTRIB_FUNC(VertexAttrib1dARB,GLdouble,NUM2DBL,1,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib1fARB,GLfloat,NUM2DBL,1,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib1sARB,GLshort,NUM2INT,1,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2dARB,GLdouble,NUM2DBL,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2fARB,GLfloat,NUM2DBL,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib2sARB,GLshort,NUM2INT,2,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3dARB,GLdouble,NUM2DBL,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3fARB,GLfloat,NUM2DBL,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib3sARB,GLshort,NUM2INT,3,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4dARB,GLdouble,NUM2DBL,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4fARB,GLfloat,NUM2DBL,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4sARB,GLshort,NUM2INT,4,"GL_ARB_vertex_program")
VERTEXATTRIB_FUNC(VertexAttrib4NubARB,GLubyte,NUM2UINT,4,"GL_ARB_vertex_program")
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
	if (pname==GL_CURRENT_VERTEX_ATTRIB_ARB) \
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

GETVERTEXATTRIB_FUNC(GetVertexAttribdvARB,GLdouble,rb_float_new,"GL_ARB_vertex_program")
GETVERTEXATTRIB_FUNC(GetVertexAttribfvARB,GLfloat,rb_float_new,"GL_ARB_vertex_program")
GETVERTEXATTRIB_FUNC(GetVertexAttribivARB,GLint,INT2NUM,"GL_ARB_vertex_program")
#undef GETVERTEXATTRIB_FUNC

/* #29 GL_ARB_occlusion_query */
static void (APIENTRY * fptr_glGenQueriesARB)(GLsizei,GLuint *);
static VALUE gl_GenQueriesARB(VALUE obj,VALUE arg1)
{
	GLsizei n;
	GLuint *queries;
	VALUE ret;
	int i;
	LOAD_GL_EXT_FUNC(glGenQueriesARB,"GL_ARB_occlusion_query")
	n = (GLsizei)NUM2UINT(arg1);
	queries = ALLOC_N(GLuint, n);
	fptr_glGenQueriesARB(n,queries);
	ret = rb_ary_new2(n);
	for (i = 0; i < n; i++)
		rb_ary_push(ret, INT2NUM(queries[i]));
	xfree(queries);
	CHECK_GLERROR
	return ret;
}

static void (APIENTRY * fptr_glDeleteQueriesARB)(GLsizei,const GLuint *);
static VALUE gl_DeleteQueriesARB(VALUE obj,VALUE arg1)
{
	GLsizei n;
	LOAD_GL_EXT_FUNC(glDeleteQueriesARB,"GL_ARB_occlusion_query")
	if (TYPE(arg1)==T_ARRAY) {
		GLuint *queries;
		n = RARRAY(arg1)->len;
		queries = ALLOC_N(GLuint,n);
		ary2cuint(arg1,queries,n); 
		fptr_glDeleteQueriesARB(n,queries);
		xfree(queries);
	} else {
		GLuint query;
		query = NUM2UINT(arg1);
		fptr_glDeleteQueriesARB(1,&query);
	}
	CHECK_GLERROR
	return Qnil;
}

static GLboolean (APIENTRY * fptr_glIsQueryARB)(GLuint);
static VALUE gl_IsQueryARB(VALUE obj,VALUE arg1)
{
	GLboolean ret = 0;
	LOAD_GL_EXT_FUNC(glIsQueryARB,"GL_ARB_occlusion_query")
	ret = fptr_glIsQueryARB(NUM2UINT(arg1));
	CHECK_GLERROR
	return INT2NUM(ret);
}

GL_EXT_SIMPLE_FUNC_LOAD(BeginQueryARB,2,GLuint,NUM2UINT,"GL_ARB_occlusion_query")
GL_EXT_SIMPLE_FUNC_LOAD(EndQueryARB,1,GLenum,NUM2UINT,"GL_ARB_occlusion_query")

#define GETQUERY_FUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLenum,_type_ *); \
static VALUE gl_##_name_(VALUE obj,VALUE arg1,VALUE arg2) \
{ \
	_type_ ret = 0; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_occlusion_query") \
	fptr_gl##_name_(NUM2INT(arg1),NUM2INT(arg2),&ret); \
	CHECK_GLERROR \
	return _conv_(ret); \
}

GETQUERY_FUNC(GetQueryivARB,GLint,INT2NUM)
GETQUERY_FUNC(GetQueryObjectivARB,GLint,INT2NUM)
GETQUERY_FUNC(GetQueryObjectuivARB,GLuint,INT2NUM)
#undef GETQUERY_FUNC

/* #30 GL_ARB_shader_objects */
GL_EXT_SIMPLE_FUNC_LOAD(DeleteObjectARB,1,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(DetachObjectARB,2,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(CompileShaderARB,1,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(AttachObjectARB,2,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(LinkProgramARB,1,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(UseProgramObjectARB,1,GLuint,NUM2UINT,"GL_ARB_shader_objects")
GL_EXT_SIMPLE_FUNC_LOAD(ValidateProgramARB,1,GLuint,NUM2UINT,"GL_ARB_shader_objects")

static GLuint (APIENTRY * fptr_glGetHandleARB)(GLenum);
static VALUE gl_GetHandleARB(VALUE obj,VALUE arg1)
{
	GLuint ret;
	LOAD_GL_EXT_FUNC(glGetHandleARB,"GL_ARB_shader_objects")
	ret = fptr_glGetHandleARB(NUM2INT(arg1));
	CHECK_GLERROR
	return UINT2NUM(ret);
}

static GLuint (APIENTRY * fptr_glCreateShaderObjectARB)(GLenum);
static VALUE gl_CreateShaderObjectARB(VALUE obj,VALUE arg1)
{
	GLuint ret;
	LOAD_GL_EXT_FUNC(glCreateShaderObjectARB,"GL_ARB_shader_objects")
	ret = fptr_glCreateShaderObjectARB(NUM2INT(arg1));
	CHECK_GLERROR
	return UINT2NUM(ret);
}

static GLuint (APIENTRY * fptr_glCreateProgramObjectARB)(void);
static VALUE gl_CreateProgramObjectARB(VALUE obj)
{
	GLuint ret;
	LOAD_GL_EXT_FUNC(glCreateProgramObjectARB,"GL_ARB_shader_objects")
	ret = fptr_glCreateProgramObjectARB();
	CHECK_GLERROR
	return UINT2NUM(ret);
}

static void (APIENTRY * fptr_glShaderSourceARB)(GLuint,GLsizei,GLchar**,GLint *);
static VALUE
gl_ShaderSourceARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint shader;
	GLint length;
	GLchar *str;
	LOAD_GL_EXT_FUNC(glShaderSourceARB,"GL_ARB_shader_objects")
	shader = (GLuint)NUM2UINT(arg1);
	Check_Type(arg2,T_STRING);
	str = RSTRING(arg2)->ptr;
	length = RSTRING(arg2)->len;
	fptr_glShaderSourceARB(shader,1,&str,&length);
	CHECK_GLERROR
	return Qnil;
}

#define GLUNIFORM_FUNC(_name_,_type_,_conv_,_size_) \
static void (APIENTRY * fptr_gl##_name_)(GLint,TYPELIST##_size_(_type_)); \
static VALUE \
gl_##_name_(obj,loc ARGLIST##_size_) \
VALUE obj,loc ARGLIST##_size_ ; \
{ \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_shader_objects") \
	fptr_gl##_name_(NUM2INT(loc),FUNCPARAMS##_size_(_type_,_conv_)); \
	return Qnil; \
}

GLUNIFORM_FUNC(Uniform1fARB,GLfloat,NUM2DBL,1)
GLUNIFORM_FUNC(Uniform2fARB,GLfloat,NUM2DBL,2)
GLUNIFORM_FUNC(Uniform3fARB,GLfloat,NUM2DBL,3)
GLUNIFORM_FUNC(Uniform4fARB,GLfloat,NUM2DBL,4)
GLUNIFORM_FUNC(Uniform1iARB,GLint,NUM2INT,1)
GLUNIFORM_FUNC(Uniform2iARB,GLint,NUM2INT,2)
GLUNIFORM_FUNC(Uniform3iARB,GLint,NUM2INT,3)
GLUNIFORM_FUNC(Uniform4iARB,GLint,NUM2INT,4)
#undef GLUNIFORM_FUNC

#define GLUNIFORM_VFUNC(_name_,_type_,_conv_,_size_) \
static void (APIENTRY * fptr_gl##_name_)(GLint,GLsizei,const _type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	GLint location; \
	GLsizei count; \
	_type_ *value; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_shader_objects") \
	location = (GLint)NUM2INT(arg1); \
	count = (GLsizei)NUM2UINT(arg2); \
	value = ALLOC_N(_type_,_size_*count); \
	_conv_(arg3,value,_size_*count); \
	fptr_gl##_name_(location,count,value); \
	xfree(value); \
	CHECK_GLERROR \
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
static void (APIENTRY * fptr_gl##_name_)(GLint,GLsizei,GLboolean,GLfloat *); \
static VALUE \
gl_##_name_(obj,arg1,arg2,arg3,arg4) \
VALUE obj,arg1,arg2,arg3,arg4; \
{ \
	GLint location; \
	GLsizei count; \
	GLboolean transpose; \
	GLfloat *value;	\
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_shader_objects") \
	location = (GLint)NUM2INT(arg1); \
	count = (GLint)NUM2INT(arg2); \
	transpose = (GLboolean)NUM2INT(arg3); \
	value = ALLOC_N(GLfloat, _size_*_size_*count); \
	ary2cmatfloat(arg4,value,_size_,_size_*count); \
	fptr_gl##_name_(location,count,transpose,value); \
	xfree(value); \
	CHECK_GLERROR \
	return Qnil; \
}

UNIFORMMATRIX_FUNC(UniformMatrix2fvARB,2)
UNIFORMMATRIX_FUNC(UniformMatrix3fvARB,3)
UNIFORMMATRIX_FUNC(UniformMatrix4fvARB,4)
#undef UNIFORMMATRIX_FUNC

#define GETOBJECTPARAMETER_FUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLenum,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint program; \
	GLenum pname; \
	_type_ params = 0; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_shader_objects") \
	program = (GLuint)NUM2UINT(arg1); \
	pname = (GLenum)NUM2INT(arg2); \
	fptr_gl##_name_(program,pname,&params); \
	CHECK_GLERROR \
	return _conv_(params); \
}

GETOBJECTPARAMETER_FUNC(GetObjectParameterivARB,GLint,INT2NUM)
GETOBJECTPARAMETER_FUNC(GetObjectParameterfvARB,GLfloat,rb_float_new)

#undef GETOBJECTPARAMETER_FUNC

static void (APIENTRY * fptr_glGetInfoLogARB)(GLuint,GLsizei,GLsizei *,GLchar *);
static VALUE
gl_GetInfoLogARB(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;	
	GLint max_size = 0;
	GLsizei ret_length = 0;
	VALUE buffer;
	LOAD_GL_EXT_FUNC(glGetInfoLogARB,"GL_ARB_shader_objects")
	LOAD_GL_EXT_FUNC(glGetObjectParameterivARB,"GL_ARB_shader_objects")
	program = (GLuint)NUM2UINT(arg1);
	fptr_glGetObjectParameterivARB(program,GL_OBJECT_INFO_LOG_LENGTH_ARB,&max_size);
	CHECK_GLERROR
	if (max_size<=0)
		return rb_str_new2("");
	buffer = allocate_buffer_with_string(max_size);
	fptr_glGetInfoLogARB(program,max_size,&ret_length,RSTRING(buffer)->ptr);
	RSTRING(buffer)->len = ret_length;
	CHECK_GLERROR
	return buffer;
}

static void (APIENTRY * fptr_glGetShaderSourceARB)(GLuint,GLsizei,GLsizei *,GLchar *);
static VALUE
gl_GetShaderSourceARB(obj,arg1)
VALUE obj,arg1;
{
	GLuint shader;
	GLint max_size = 0;
	GLsizei ret_length = 0;
	VALUE buffer;
	LOAD_GL_EXT_FUNC(glGetShaderSourceARB,"GL_ARB_shader_objects")
	LOAD_GL_EXT_FUNC(glGetObjectParameterivARB,"GL_ARB_shader_objects")
	shader = (GLuint)NUM2UINT(arg1);
	fptr_glGetObjectParameterivARB(shader,GL_OBJECT_SHADER_SOURCE_LENGTH_ARB,&max_size);
	CHECK_GLERROR
	if (max_size==0)
		rb_raise(rb_eTypeError, "Can't determine maximum shader source length");
	buffer = allocate_buffer_with_string(max_size-1);
	fptr_glGetShaderSourceARB(shader,max_size,&ret_length,RSTRING(buffer)->ptr);
	CHECK_GLERROR
	return buffer;
}

static void (APIENTRY * fptr_glGetActiveUniformARB)(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
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
	LOAD_GL_EXT_FUNC(glGetActiveUniformARB,"GL_ARB_shader_objects")
	LOAD_GL_EXT_FUNC(glGetObjectParameterivARB,"GL_EXT_sahder_objects")
	program = (GLuint)NUM2UINT(arg1);
	index = (GLuint)NUM2UINT(arg2);
	fptr_glGetObjectParameterivARB(program,GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB,&max_size);
	CHECK_GLERROR
	if (max_size==0)
		rb_raise(rb_eTypeError, "Can't determine maximum uniform name length");
	buffer = allocate_buffer_with_string(max_size-1);
	fptr_glGetActiveUniformARB(program,index,max_size,&written,&uniform_size,&uniform_type,RSTRING(buffer)->ptr);
	retary = rb_ary_new2(3);
	rb_ary_push(retary, INT2NUM(uniform_size));
	rb_ary_push(retary, INT2NUM(uniform_type));
	rb_ary_push(retary, buffer);
	CHECK_GLERROR
	return retary;
}

#define GETUNIFORM_FUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,GLint,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint program; \
	GLint location; \
	_type_ params[16]; \
	VALUE retary; \
	GLint i; \
	GLint unused = 0; \
	GLenum uniform_type = 0; \
	GLint uniform_size = 0; \
\
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_shader_objects") \
	LOAD_GL_EXT_FUNC(glGetActiveUniformARB,"GL_ARB_shader_objects") \
	program = (GLuint)NUM2UINT(arg1); \
	location = (GLint)NUM2INT(arg2); \
\
	fptr_glGetActiveUniformARB(program,location,0,NULL,&unused,&uniform_type,NULL); \
	CHECK_GLERROR \
	if (uniform_type==0) \
		rb_raise(rb_eTypeError, "Can't determine the uniform's type"); \
\
	uniform_size = get_uniform_size(uniform_type); \
\
	memset(params,0,16*sizeof(_type_)); \
	fptr_gl##_name_(program,location,params); \
	retary = rb_ary_new2(uniform_size); \
	for(i=0;i<uniform_size;i++) \
		rb_ary_push(retary, _conv_(params[i])); \
	CHECK_GLERROR \
	return retary; \
}

GETUNIFORM_FUNC(GetUniformfvARB,GLfloat,rb_float_new)
GETUNIFORM_FUNC(GetUniformivARB,GLint,INT2NUM)
#undef GETUNIFORM_FUNC

static GLint (APIENTRY * fptr_glGetUniformLocationARB)(GLuint,const GLchar*);
static VALUE
gl_GetUniformLocationARB(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLint ret;
	LOAD_GL_EXT_FUNC(glGetUniformLocationARB,"GL_ARB_shader_objects")
	program=(GLuint)NUM2UINT(arg1);
	Check_Type(arg2,T_STRING);
	ret = fptr_glGetUniformLocationARB(program,RSTRING(arg2)->ptr);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetAttachedObjectsARB)(GLuint,GLsizei,GLsizei *,GLuint *);
static VALUE
gl_GetAttachedObjectsARB(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;
	GLint shaders_num = 0;
	GLuint *shaders;
	VALUE retary;
	GLsizei count = 0;
	GLint i;
	LOAD_GL_EXT_FUNC(glGetAttachedObjectsARB,"GL_ARB_shader_objects")
	LOAD_GL_EXT_FUNC(glGetObjectParameterivARB,"GL_ARB_shader_objects")
	program = (GLuint)NUM2UINT(arg1);
	fptr_glGetObjectParameterivARB(program,GL_OBJECT_ATTACHED_OBJECTS_ARB,&shaders_num);
	CHECK_GLERROR
	if (shaders_num<=0)
		return Qnil;
	shaders = ALLOC_N(GLuint,shaders_num);
	fptr_glGetAttachedObjectsARB(program,shaders_num,&count,shaders);
	retary = rb_ary_new2(shaders_num);
	for(i=0;i<shaders_num;i++)
		rb_ary_push(retary, INT2NUM(shaders[i]));
	xfree(shaders);
	CHECK_GLERROR
	return retary;
}

/* #39 GL_ARB_color_buffer_float */
GL_EXT_SIMPLE_FUNC_LOAD(ClampColorARB,2,GLenum,NUM2INT,"GL_ARB_color_buffer_float")

void gl_init_functions_ext_arb(VALUE module)
{
/* #3 GL_ARB_transpose_matrix */
	rb_define_module_function(module, "glLoadTransposeMatrixfARB", gl_LoadTransposeMatrixfARB, 1);
	rb_define_module_function(module, "glLoadTransposeMatrixdARB", gl_LoadTransposeMatrixdARB, 1);
	rb_define_module_function(module, "glMultTransposeMatrixfARB", gl_MultTransposeMatrixfARB, 1);
	rb_define_module_function(module, "glMultTransposeMatrixdARB", gl_MultTransposeMatrixdARB, 1);

/* #5 GL_ARB_multisample */
	rb_define_module_function(module, "glSampleCoverageARB", gl_SampleCoverageARB, 2);

/* #14 GL_ARB_point_parameters */
	rb_define_module_function(module, "glPointParameterfARB", gl_PointParameterfARB, 2);
	rb_define_module_function(module, "glPointParameterfvARB", gl_PointParameterfvARB, 2);

/* #26 GL_ARB_window_pos */
	rb_define_module_function(module, "glWindowPos2dARB", gl_WindowPos2dARB, 2);
	rb_define_module_function(module, "glWindowPos2fARB", gl_WindowPos2fARB, 2);
	rb_define_module_function(module, "glWindowPos2iARB", gl_WindowPos2iARB, 2);
	rb_define_module_function(module, "glWindowPos2sARB", gl_WindowPos2sARB, 2);
	rb_define_module_function(module, "glWindowPos3dARB", gl_WindowPos3dARB, 3);
	rb_define_module_function(module, "glWindowPos3fARB", gl_WindowPos3fARB, 3);
	rb_define_module_function(module, "glWindowPos3iARB", gl_WindowPos3iARB, 3);
	rb_define_module_function(module, "glWindowPos3sARB", gl_WindowPos3sARB, 3);

	rb_define_module_function(module, "glWindowPos2dvARB", gl_WindowPos2dvARB, 1);
	rb_define_module_function(module, "glWindowPos2fvARB", gl_WindowPos2fvARB, 1);
	rb_define_module_function(module, "glWindowPos2ivARB", gl_WindowPos2ivARB, 1);
	rb_define_module_function(module, "glWindowPos2svARB", gl_WindowPos2svARB, 1);
	rb_define_module_function(module, "glWindowPos3dvARB", gl_WindowPos3dvARB, 1);
	rb_define_module_function(module, "glWindowPos3fvARB", gl_WindowPos3fvARB, 1);
	rb_define_module_function(module, "glWindowPos3ivARB", gl_WindowPos3ivARB, 1);
	rb_define_module_function(module, "glWindowPos3svARB", gl_WindowPos3svARB, 1);

/* #26 GL_ARB_vertex_program */
	rb_define_module_function(module, "glProgramStringARB", gl_ProgramStringARB, 3);
	rb_define_module_function(module, "glGetProgramStringARB", gl_GetProgramStringARB, 2);
	rb_define_module_function(module, "glGetProgramivARB", gl_GetProgramivARB, 2);
	rb_define_module_function(module, "glBindProgramARB", gl_BindProgramARB, 2);
	rb_define_module_function(module, "glGenProgramsARB", gl_GenProgramsARB, 1);
	rb_define_module_function(module, "glDeleteProgramsARB", gl_DeleteProgramsARB, 1);
	rb_define_module_function(module, "glIsProgramARB", gl_IsProgramARB, 1);
	rb_define_module_function(module, "glEnableVertexAttribArrayARB", gl_EnableVertexAttribArrayARB, 1);
	rb_define_module_function(module, "glDisableVertexAttribArrayARB", gl_DisableVertexAttribArrayARB, 1);
	rb_define_module_function(module, "glVertexAttribPointerARB", gl_VertexAttribPointerARB, 6);
	rb_define_module_function(module, "glGetVertexAttribPointervARB", gl_GetVertexAttribPointervARB, 1);
	rb_define_module_function(module, "glProgramEnvParameter4dARB", gl_ProgramEnvParameter4dARB, 6);
	rb_define_module_function(module, "glProgramEnvParameter4fARB", gl_ProgramEnvParameter4fARB, 6);
	rb_define_module_function(module, "glProgramLocalParameter4dARB", gl_ProgramLocalParameter4dARB, 6);
	rb_define_module_function(module, "glProgramLocalParameter4fARB", gl_ProgramLocalParameter4fARB, 6);
	rb_define_module_function(module, "glProgramEnvParameter4dvARB", gl_ProgramEnvParameter4dvARB, 3);
	rb_define_module_function(module, "glProgramEnvParameter4fvARB", gl_ProgramEnvParameter4fvARB, 3);
	rb_define_module_function(module, "glProgramLocalParameter4dvARB", gl_ProgramLocalParameter4dvARB, 3);
	rb_define_module_function(module, "glProgramLocalParameter4fvARB", gl_ProgramLocalParameter4fvARB, 3);
	rb_define_module_function(module, "glGetProgramEnvParameterdvARB", gl_GetProgramEnvParameterdvARB, 2);
	rb_define_module_function(module, "glGetProgramEnvParameterfvARB", gl_GetProgramEnvParameterfvARB, 2);
	rb_define_module_function(module, "glGetProgramLocalParameterdvARB", gl_GetProgramLocalParameterdvARB, 2);
	rb_define_module_function(module, "glGetProgramLocalParameterfvARB", gl_GetProgramLocalParameterfvARB, 2);
	rb_define_module_function(module, "glVertexAttrib1dARB", gl_VertexAttrib1dARB, 2);
	rb_define_module_function(module, "glVertexAttrib1fARB", gl_VertexAttrib1fARB, 2);
	rb_define_module_function(module, "glVertexAttrib1sARB", gl_VertexAttrib1sARB, 2);
	rb_define_module_function(module, "glVertexAttrib2dARB", gl_VertexAttrib2dARB, 3);
	rb_define_module_function(module, "glVertexAttrib2fARB", gl_VertexAttrib2fARB, 3);
	rb_define_module_function(module, "glVertexAttrib2sARB", gl_VertexAttrib2sARB, 3);
	rb_define_module_function(module, "glVertexAttrib3dARB", gl_VertexAttrib3dARB, 4);
	rb_define_module_function(module, "glVertexAttrib3fARB", gl_VertexAttrib3fARB, 4);
	rb_define_module_function(module, "glVertexAttrib3sARB", gl_VertexAttrib3sARB, 4);
	rb_define_module_function(module, "glVertexAttrib4NbvARB", gl_VertexAttrib4NbvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4NivARB", gl_VertexAttrib4NivARB, 2);
	rb_define_module_function(module, "glVertexAttrib4NsvARB", gl_VertexAttrib4NsvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4NubARB", gl_VertexAttrib4NubARB, 5);
	rb_define_module_function(module, "glVertexAttrib4NubvARB", gl_VertexAttrib4NubvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4NuivARB", gl_VertexAttrib4NuivARB, 2);
	rb_define_module_function(module, "glVertexAttrib4NusvARB", gl_VertexAttrib4NusvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4bvARB", gl_VertexAttrib4bvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4dARB", gl_VertexAttrib4dARB, 5);
	rb_define_module_function(module, "glVertexAttrib4fARB", gl_VertexAttrib4fARB, 5);
	rb_define_module_function(module, "glVertexAttrib4ivARB", gl_VertexAttrib4ivARB, 2);
	rb_define_module_function(module, "glVertexAttrib4sARB", gl_VertexAttrib4sARB, 5);
	rb_define_module_function(module, "glVertexAttrib4ubvARB", gl_VertexAttrib4ubvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4uivARB", gl_VertexAttrib4uivARB, 2);
	rb_define_module_function(module, "glVertexAttrib4usvARB", gl_VertexAttrib4usvARB, 2);
	rb_define_module_function(module, "glVertexAttrib1dvARB", gl_VertexAttrib1dvARB, 2);
	rb_define_module_function(module, "glVertexAttrib1fvARB", gl_VertexAttrib1fvARB, 2);
	rb_define_module_function(module, "glVertexAttrib1svARB", gl_VertexAttrib1svARB, 2);
	rb_define_module_function(module, "glVertexAttrib2dvARB", gl_VertexAttrib2dvARB, 2);
	rb_define_module_function(module, "glVertexAttrib2fvARB", gl_VertexAttrib2fvARB, 2);
	rb_define_module_function(module, "glVertexAttrib2svARB", gl_VertexAttrib2svARB, 2);
	rb_define_module_function(module, "glVertexAttrib3dvARB", gl_VertexAttrib3dvARB, 2);
	rb_define_module_function(module, "glVertexAttrib3fvARB", gl_VertexAttrib3fvARB, 2);
	rb_define_module_function(module, "glVertexAttrib3svARB", gl_VertexAttrib3svARB, 2);
	rb_define_module_function(module, "glVertexAttrib4dvARB", gl_VertexAttrib4dvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4fvARB", gl_VertexAttrib4fvARB, 2);
	rb_define_module_function(module, "glVertexAttrib4svARB", gl_VertexAttrib4svARB, 2);
	rb_define_module_function(module, "glGetVertexAttribdvARB", gl_GetVertexAttribdvARB, 2);
	rb_define_module_function(module, "glGetVertexAttribfvARB", gl_GetVertexAttribfvARB, 2);
	rb_define_module_function(module, "glGetVertexAttribivARB", gl_GetVertexAttribivARB, 2);

/* #29 GL_ARB_occlusion_query */
	rb_define_module_function(module, "glGenQueriesARB", gl_GenQueriesARB, 1);
	rb_define_module_function(module, "glDeleteQueriesARB", gl_DeleteQueriesARB, 1);
	rb_define_module_function(module, "glIsQueryARB", gl_IsQueryARB, 1);
	rb_define_module_function(module, "glBeginQueryARB", gl_BeginQueryARB, 2);
	rb_define_module_function(module, "glEndQueryARB", gl_EndQueryARB, 1);
	rb_define_module_function(module, "glGetQueryivARB", gl_GetQueryivARB, 2);
	rb_define_module_function(module, "glGetQueryObjectivARB", gl_GetQueryObjectivARB, 2);
	rb_define_module_function(module, "glGetQueryObjectuivARB", gl_GetQueryObjectuivARB, 2);

/* #30 GL_ARB_shader_objects */
	rb_define_module_function(module, "glDeleteObjectARB", gl_DeleteObjectARB, 1);
	rb_define_module_function(module, "glGetHandleARB", gl_GetHandleARB, 1);
	rb_define_module_function(module, "glDetachObjectARB", gl_DetachObjectARB, 2);
	rb_define_module_function(module, "glCreateShaderObjectARB", gl_CreateShaderObjectARB, 1);
	rb_define_module_function(module, "glShaderSourceARB", gl_ShaderSourceARB, 2);
	rb_define_module_function(module, "glCompileShaderARB", gl_CompileShaderARB, 1);
	rb_define_module_function(module, "glCreateProgramObjectARB", gl_CreateProgramObjectARB, 0);
	rb_define_module_function(module, "glAttachObjectARB", gl_AttachObjectARB, 2);
	rb_define_module_function(module, "glLinkProgramARB", gl_LinkProgramARB, 1);
	rb_define_module_function(module, "glUseProgramObjectARB", gl_UseProgramObjectARB, 1);
	rb_define_module_function(module, "glValidateProgramARB", gl_ValidateProgramARB, 1);
	rb_define_module_function(module, "glUniform1fARB", gl_Uniform1fARB, 2);
	rb_define_module_function(module, "glUniform2fARB", gl_Uniform2fARB, 3);
	rb_define_module_function(module, "glUniform3fARB", gl_Uniform3fARB, 4);
	rb_define_module_function(module, "glUniform4fARB", gl_Uniform4fARB, 5);
	rb_define_module_function(module, "glUniform1iARB", gl_Uniform1iARB, 2);
	rb_define_module_function(module, "glUniform2iARB", gl_Uniform2iARB, 3);
	rb_define_module_function(module, "glUniform3iARB", gl_Uniform3iARB, 4);
	rb_define_module_function(module, "glUniform4iARB", gl_Uniform4iARB, 5);
	rb_define_module_function(module, "glUniform1fvARB", gl_Uniform1fvARB, 3);
	rb_define_module_function(module, "glUniform2fvARB", gl_Uniform2fvARB, 3);
	rb_define_module_function(module, "glUniform3fvARB", gl_Uniform3fvARB, 3);
	rb_define_module_function(module, "glUniform4fvARB", gl_Uniform4fvARB, 3);
	rb_define_module_function(module, "glUniform1ivARB", gl_Uniform1ivARB, 3);
	rb_define_module_function(module, "glUniform2ivARB", gl_Uniform2ivARB, 3);
	rb_define_module_function(module, "glUniform3ivARB", gl_Uniform3ivARB, 3);
	rb_define_module_function(module, "glUniform4ivARB", gl_Uniform4ivARB, 3);
	rb_define_module_function(module, "glUniformMatrix2fvARB", gl_UniformMatrix2fvARB, 4);
	rb_define_module_function(module, "glUniformMatrix3fvARB", gl_UniformMatrix3fvARB, 4);
	rb_define_module_function(module, "glUniformMatrix4fvARB", gl_UniformMatrix4fvARB, 4);
	rb_define_module_function(module, "glGetObjectParameterfvARB", gl_GetObjectParameterfvARB, 2);
	rb_define_module_function(module, "glGetObjectParameterivARB", gl_GetObjectParameterivARB, 2);
	rb_define_module_function(module, "glGetInfoLogARB", gl_GetInfoLogARB, 1);
	rb_define_module_function(module, "glGetShaderSourceARB", gl_GetShaderSourceARB, 1);
	rb_define_module_function(module, "glGetAttachedObjectsARB", gl_GetAttachedObjectsARB, 1);
	rb_define_module_function(module, "glGetUniformLocationARB", gl_GetUniformLocationARB, 2);
	rb_define_module_function(module, "glGetActiveUniformARB", gl_GetActiveUniformARB, 2);
	rb_define_module_function(module, "glGetUniformfvARB", gl_GetUniformfvARB, 2);
	rb_define_module_function(module, "glGetUniformivARB", gl_GetUniformivARB, 2);

/* #39 GL_ARB_color_buffer_float */
	rb_define_module_function(module, "glClampColorARB", gl_ClampColorARB, 2);
}
