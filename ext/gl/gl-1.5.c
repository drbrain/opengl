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

/* OpenGL 1.5 functions */

GL_FUNC_LOAD_1(EndQuery,GLvoid, GLenum, "1.5")
GL_FUNC_LOAD_1(IsQuery,GLboolean, GLuint, "1.5")
GL_FUNC_LOAD_2(BeginQuery,GLvoid, GLenum,GLuint, "1.5")
GL_FUNC_LOAD_2(BindBuffer,GLvoid, GLenum,GLuint, "1.5")
GL_FUNC_LOAD_1(IsBuffer,GLboolean, GLuint, "1.5")
GL_FUNC_GENOBJECTS_LOAD(GenQueries,"1.5")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteQueries,"1.5")
GL_FUNC_GENOBJECTS_LOAD(GenBuffers,"1.5")
GL_FUNC_DELETEOBJECTS_LOAD(DeleteBuffers,"1.5")

static void (APIENTRY * fptr_glGetQueryiv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetQueryiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLint params = 0;
	VALUE retary;
	LOAD_GL_FUNC(glGetQueryiv,"1.5")
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetQueryiv(target,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary, INT2NUM(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetQueryObjectiv)(GLuint,GLenum,GLint *);
static VALUE
gl_GetQueryObjectiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint id;
	GLenum pname;
	GLint params = 0;
	VALUE retary;
	LOAD_GL_FUNC(glGetQueryObjectiv,"1.5")
	id = (GLuint)NUM2UINT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetQueryObjectiv(id,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary,INT2NUM(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetQueryObjectuiv)(GLuint,GLenum,GLuint *);
static VALUE
gl_GetQueryObjectuiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint id;
	GLenum pname;
	GLuint params = 0;
	VALUE retary;
	LOAD_GL_FUNC(glGetQueryObjectuiv,"1.5")
	id = (GLuint)NUM2UINT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetQueryObjectuiv(id,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary,INT2NUM(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glBufferData)(GLenum,GLsizeiptr,GLvoid *,GLenum);
static VALUE
gl_BufferData(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLenum target;
	GLsizeiptr size;
	GLenum usage;
	LOAD_GL_FUNC(glBufferData,"1.5")
	target = (GLenum)NUM2INT(arg1);
	size = (GLsizeiptr)NUM2INT(arg2);
	usage = (GLenum)NUM2INT(arg4);
	if (TYPE(arg3) == T_STRING) {
		fptr_glBufferData(target,size,(GLvoid *)RSTRING(arg3)->ptr,usage);
	} else if (NIL_P(arg3)) {
		fptr_glBufferData(target,size,NULL,usage);
	} else {
		Check_Type(arg3,T_STRING); /* force exception */
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glBufferSubData)(GLenum,GLintptr,GLsizeiptr,GLvoid *);
static VALUE
gl_BufferSubData(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLenum target;
	GLintptr offset;
	GLsizeiptr size;
	LOAD_GL_FUNC(glBufferSubData,"1.5")
	target = (GLenum)NUM2INT(arg1);
	offset = (GLintptr)NUM2INT(arg2);
	size = (GLsizeiptr)NUM2INT(arg3);
	Check_Type(arg4,T_STRING);
	fptr_glBufferSubData(target,offset,size,(GLvoid *)RSTRING(arg4)->ptr);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetBufferSubData)(GLenum,GLintptr,GLsizeiptr,GLvoid *);
static VALUE
gl_GetBufferSubData(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLintptr offset;
	GLsizeiptr size;
	VALUE data;
	LOAD_GL_FUNC(glGetBufferSubData,"1.5")
	target = (GLenum)NUM2INT(arg1);
	offset = (GLintptr)NUM2INT(arg2);
	size = (GLsizeiptr)NUM2INT(arg3);
	data = allocate_buffer_with_string(size);
	fptr_glGetBufferSubData(target,offset,size,(GLvoid *)RSTRING(data)->ptr);
	CHECK_GLERROR
	return data;
}

static void (APIENTRY * fptr_glGetBufferParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetBufferParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum value;
	GLint data = 0;
	VALUE retary;
	LOAD_GL_FUNC(glGetBufferParameteriv,"1.5")
	target = (GLenum)NUM2INT(arg1);
	value = (GLenum)NUM2INT(arg2);
	fptr_glGetBufferParameteriv(target,value,&data);
	retary = rb_ary_new2(1);
	rb_ary_push(retary,INT2NUM(data));
	CHECK_GLERROR
	return retary;
}

static GLvoid * (APIENTRY * fptr_glMapBuffer)(GLenum,GLenum);
static VALUE
gl_MapBuffer(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum access;
	GLint size = 0;
	VALUE data;
	GLvoid *buffer_ptr = NULL;
	LOAD_GL_FUNC(glMapBuffer,"1.5")
	LOAD_GL_FUNC(glGetBufferParameteriv,"1.5")
	target = (GLenum)NUM2INT(arg1);
	access = (GLenum)NUM2INT(arg2);
	fptr_glGetBufferParameteriv(target,GL_BUFFER_SIZE,&size);
	CHECK_GLERROR
	buffer_ptr = fptr_glMapBuffer(target,access);
	CHECK_GLERROR
	if (buffer_ptr==NULL || size<=0)
		return Qnil;
	data = allocate_buffer_with_string(size);
	memcpy(RSTRING(data)->ptr, buffer_ptr, size);
	return data;
}

static GLboolean (APIENTRY * fptr_glUnmapBuffer)(GLenum);
static VALUE
gl_UnmapBuffer(obj,arg1)
VALUE obj,arg1;
{
	GLenum target;
	GLboolean ret;
	LOAD_GL_FUNC(glUnmapBuffer,"1.5")
	target = (GLenum)NUM2INT(arg1);
	ret = fptr_glUnmapBuffer(target);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetBufferPointerv)(GLenum,GLenum,GLvoid **);
static VALUE
gl_GetBufferPointerv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	LOAD_GL_FUNC(glGetBufferPointerv,"1.5")
	rb_raise(rb_eArgError, "glGetBufferPointerv not implemented");
	CHECK_GLERROR
	return Qnil;
}

void gl_init_functions_1_5(VALUE module)
{
	rb_define_module_function(module, "glGenQueries", gl_GenQueries, 1);
	rb_define_module_function(module, "glDeleteQueries", gl_DeleteQueries, 1);
	rb_define_module_function(module, "glIsQuery", gl_IsQuery, 1);
	rb_define_module_function(module, "glBeginQuery", gl_BeginQuery, 2);
	rb_define_module_function(module, "glEndQuery", gl_EndQuery, 1);
	rb_define_module_function(module, "glGetQueryiv", gl_GetQueryiv, 2);
	rb_define_module_function(module, "glGetQueryObjectiv", gl_GetQueryObjectiv, 2);
	rb_define_module_function(module, "glGetQueryObjectuiv", gl_GetQueryObjectuiv, 2);
	rb_define_module_function(module, "glBindBuffer", gl_BindBuffer, 2);
	rb_define_module_function(module, "glDeleteBuffers", gl_DeleteBuffers, 1);
	rb_define_module_function(module, "glGenBuffers", gl_GenBuffers, 1);
	rb_define_module_function(module, "glIsBuffer", gl_IsBuffer, 1);
	rb_define_module_function(module, "glBufferData", gl_BufferData, 4);
	rb_define_module_function(module, "glBufferSubData", gl_BufferSubData, 4);
	rb_define_module_function(module, "glGetBufferSubData", gl_GetBufferSubData, 3);
	rb_define_module_function(module, "glMapBuffer", gl_MapBuffer, 2);
	rb_define_module_function(module, "glUnmapBuffer", gl_UnmapBuffer, 1);
	rb_define_module_function(module, "glGetBufferParameteriv", gl_GetBufferParameteriv, 2);
	rb_define_module_function(module, "glGetBufferPointerv", gl_GetBufferPointerv, 3);
}
