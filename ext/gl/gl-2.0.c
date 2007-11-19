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

GL_SIMPLE_FUNC_LOAD(BlendEquationSeparate,2,GLenum,NUM2INT)
GL_SIMPLE_FUNC_LOAD(StencilOpSeparate,4,GLenum,NUM2INT)
GL_SIMPLE_FUNC_LOAD(AttachShader,2,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(CompileShader,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(DeleteProgram,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(DeleteShader,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(DetachShader,2,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(DisableVertexAttribArray,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(EnableVertexAttribArray,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(LinkProgram,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(UseProgram,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(ValidateProgram,1,GLuint,NUM2UINT)
GL_SIMPLE_FUNC_LOAD(Uniform1i,2,GLint,NUM2INT)
GL_SIMPLE_FUNC_LOAD(Uniform2i,3,GLint,NUM2INT)
GL_SIMPLE_FUNC_LOAD(Uniform3i,4,GLint,NUM2INT)
GL_SIMPLE_FUNC_LOAD(Uniform4i,5,GLint,NUM2INT)

static void (APIENTRY * fptr_glDrawBuffers)(GLsizei,GLenum *);
static VALUE
gl_DrawBuffers(obj,arg1)
VALUE obj,arg1;
{
	GLsizei size;
	GLenum *buffers;
	LOAD_GL_FUNC(glDrawBuffers)
	Check_Type(arg1,T_ARRAY); 
	size = RARRAY(arg1)->len;
	buffers = ALLOC_N(GLenum,size);
	ary2cuint(arg1,buffers,size);
	fptr_glDrawBuffers(size,buffers);
	xfree(buffers);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glStencilFuncSeparate)(GLenum,GLenum,GLint,GLuint);
static VALUE
gl_StencilFuncSeparate(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLenum face;
	GLenum func;
	GLint ref;
	GLuint mask;
	LOAD_GL_FUNC(glStencilFuncSeparate)
	face = (GLenum)NUM2INT(arg1);
	func = (GLenum)NUM2INT(arg2);
	ref = (GLint)NUM2INT(arg3);
	mask = (GLuint)NUM2UINT(arg4);
	fptr_glStencilFuncSeparate(face,func,ref,mask);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glStencilMaskSeparate)(GLenum face,GLuint mask);
static VALUE
gl_StencilMaskSeparate(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum face;
	GLuint mask;
	LOAD_GL_FUNC(glStencilMaskSeparate)
	face = (GLenum)NUM2INT(arg1);
	mask = (GLenum)NUM2INT(arg2);
	fptr_glStencilMaskSeparate(face,mask);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glBindAttribLocation)(GLuint,GLuint,GLchar *);
static VALUE
gl_BindAttribLocation(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLuint program;
	GLuint index;
	LOAD_GL_FUNC(glBindAttribLocation)
	program = (GLuint)NUM2UINT(arg1);
	index = (GLuint)NUM2UINT(arg2);
	Check_Type(arg3, T_STRING);
	fptr_glBindAttribLocation(program,index,RSTRING(arg3)->ptr);
	CHECK_GLERROR
	return Qnil;
}

static GLuint (APIENTRY * fptr_glCreateProgram)(void);
static VALUE
gl_CreateProgram(obj)
VALUE obj;
{
	GLuint ret;
	LOAD_GL_FUNC(glCreateProgram)
	ret = fptr_glCreateProgram();
	CHECK_GLERROR
	return INT2NUM(ret);
}

static GLuint (APIENTRY * fptr_glCreateShader)(GLenum);
static VALUE
gl_CreateShader(obj,arg1)
VALUE obj,arg1;
{
	GLenum shaderType;
	GLuint ret;
	LOAD_GL_FUNC(glCreateShader)
	shaderType = (GLenum)NUM2INT(arg1);
	ret = fptr_glCreateShader(shaderType);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetProgramiv)(GLuint,GLenum,GLint *);
static VALUE
gl_GetProgramiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLenum pname;
	GLint params = 0;
	LOAD_GL_FUNC(glGetProgramiv)
	program = (GLuint)NUM2UINT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetProgramiv(program,pname,&params);
	CHECK_GLERROR
	return INT2NUM(params);
}

static void (APIENTRY * fptr_glGetActiveAttrib)(GLuint,GLuint,GLsizei,GLsizei *,GLint *,GLenum *,GLchar *);
static VALUE
gl_GetActiveAttrib(obj,arg1,arg2)
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
	LOAD_GL_FUNC(glGetActiveAttrib)
	LOAD_GL_FUNC(glGetProgramiv)
	program = (GLuint)NUM2UINT(arg1);
	index = (GLuint)NUM2UINT(arg2);
	fptr_glGetProgramiv(program,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&max_size);
	CHECK_GLERROR
	if (max_size==0)
		rb_raise(rb_eTypeError, "Can't determine maximum attribute name length");
	buffer = allocate_buffer_with_string(max_size-1);
	fptr_glGetActiveAttrib(program,index,max_size,&written,&attrib_size,&attrib_type,RSTRING(buffer)->ptr);
	retary = rb_ary_new2(3);
	rb_ary_push(retary, INT2NUM(attrib_size));
	rb_ary_push(retary, INT2NUM(attrib_type));
	rb_ary_push(retary, buffer);
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetActiveUniform)(GLuint,GLuint,GLsizei,GLsizei*,GLint*,GLenum*,GLchar*);
static VALUE
gl_GetActiveUniform(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
	GLuint program;
	GLuint index;
	GLsizei max_size = 0;
	GLsizei written = 0;
	GLint uniform_size = 0;
	GLenum uniform_type = 0;
	VALUE buffer;
	VALUE retary;
	LOAD_GL_FUNC(glGetActiveUniform)
	LOAD_GL_FUNC(glGetProgramiv)
	program = (GLuint)NUM2UINT(arg1);
	index = (GLuint)NUM2UINT(arg2);
	fptr_glGetProgramiv(program,GL_ACTIVE_UNIFORM_MAX_LENGTH,&max_size);
	CHECK_GLERROR
	if (max_size==0)
		rb_raise(rb_eTypeError, "Can't determine maximum uniform name length");
	buffer = allocate_buffer_with_string(max_size-1);
	fptr_glGetActiveUniform(program,index,max_size,&written,&uniform_size,&uniform_type,RSTRING(buffer)->ptr);
	retary = rb_ary_new2(3);
	rb_ary_push(retary, INT2NUM(uniform_size));
	rb_ary_push(retary, INT2NUM(uniform_type));
	rb_ary_push(retary, buffer);
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetAttachedShaders)(GLuint,GLsizei,GLsizei *,GLuint *);
static VALUE
gl_GetAttachedShaders(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;
	GLint shaders_num = 0;
	GLuint *shaders;
	VALUE retary;
	GLsizei count = 0;
	GLint i;
	LOAD_GL_FUNC(glGetAttachedShaders)
	LOAD_GL_FUNC(glGetProgramiv)
	program = (GLuint)NUM2UINT(arg1);
	fptr_glGetProgramiv(program,GL_ATTACHED_SHADERS,&shaders_num);
	CHECK_GLERROR
	if (shaders_num<=0)
		return Qnil;
	shaders = ALLOC_N(GLuint,shaders_num);
	fptr_glGetAttachedShaders(program,shaders_num,&count,shaders);
	retary = rb_ary_new2(shaders_num);
	for(i=0;i<shaders_num;i++)
		rb_ary_push(retary, INT2NUM(shaders[i]));
	xfree(shaders);
	CHECK_GLERROR
	return retary;
}

static GLint (APIENTRY * fptr_glGetAttribLocation)(GLuint, GLchar *);
static VALUE
gl_GetAttribLocation(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLint ret;
	LOAD_GL_FUNC(glGetAttribLocation)
	program=(GLuint)NUM2UINT(arg1);
	Check_Type(arg2,T_STRING);
	ret = fptr_glGetAttribLocation(program,RSTRING(arg2)->ptr);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glGetProgramInfoLog)(GLuint,GLsizei,GLsizei *,GLchar *);
static VALUE
gl_GetProgramInfoLog(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;	
	GLint max_size = 0;
	GLsizei ret_length = 0;
	VALUE buffer;
	LOAD_GL_FUNC(glGetProgramInfoLog)
	LOAD_GL_FUNC(glGetProgramiv)
	program = (GLuint)NUM2UINT(arg1);
	fptr_glGetProgramiv(program,GL_INFO_LOG_LENGTH,&max_size);
	CHECK_GLERROR
	if (max_size<=0)
		return rb_str_new2("");
	buffer = allocate_buffer_with_string(max_size);
	fptr_glGetProgramInfoLog(program,max_size,&ret_length,RSTRING(buffer)->ptr);
	RSTRING(buffer)->len = ret_length;
	CHECK_GLERROR
	return buffer;
}

static void (APIENTRY * fptr_glGetShaderiv)(GLuint,GLenum,GLint *);
static VALUE
gl_GetShaderiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLenum pname;
	GLint params = 0;
	LOAD_GL_FUNC(glGetShaderiv)
	program = (GLuint)NUM2UINT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetShaderiv(program,pname,&params);
	CHECK_GLERROR
	return INT2NUM(params);
}

static void (APIENTRY * fptr_glGetShaderInfoLog)(GLuint,GLsizei,GLsizei *,GLchar *);
static VALUE
gl_GetShaderInfoLog(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;	
	GLint max_size = 0;
	GLsizei ret_length = 0;
	VALUE ret_buffer;
	GLchar *buffer;
	LOAD_GL_FUNC(glGetShaderInfoLog)
	LOAD_GL_FUNC(glGetShaderiv)
	program = (GLuint)NUM2UINT(arg1);
	fptr_glGetShaderiv(program,GL_INFO_LOG_LENGTH,&max_size);
	CHECK_GLERROR
	if (max_size<=0)
		return rb_str_new2("");
	buffer = ALLOC_N(GLchar,max_size+1);
	memset(buffer,0,sizeof(GLchar) * (max_size+1));
	fptr_glGetShaderInfoLog(program,max_size,&ret_length,buffer);
	ret_buffer = rb_str_new(buffer, ret_length);
	xfree(buffer);
	CHECK_GLERROR
	return ret_buffer;
}

static void (APIENTRY * fptr_glGetShaderSource)(GLuint,GLsizei,GLsizei *,GLchar *);
static VALUE
gl_GetShaderSource(obj,arg1)
VALUE obj,arg1;
{
	GLuint shader;
	GLint max_size = 0;
	GLsizei ret_length = 0;
	VALUE buffer;
	LOAD_GL_FUNC(glGetShaderSource)
	LOAD_GL_FUNC(glGetShaderiv)
	shader = (GLuint)NUM2UINT(arg1);
	fptr_glGetShaderiv(shader,GL_SHADER_SOURCE_LENGTH,&max_size);
	CHECK_GLERROR
	if (max_size==0)
		rb_raise(rb_eTypeError, "Can't determine maximum shader source length");
	buffer = allocate_buffer_with_string(max_size-1);
	fptr_glGetShaderSource(shader,max_size,&ret_length,RSTRING(buffer)->ptr);
	CHECK_GLERROR
	return buffer;
}

static GLint (APIENTRY * fptr_glGetUniformLocation)(GLuint,const GLchar*);
static VALUE
gl_GetUniformLocation(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLint ret;
	LOAD_GL_FUNC(glGetUniformLocation)
	program=(GLuint)NUM2UINT(arg1);
	Check_Type(arg2,T_STRING);
	ret = fptr_glGetUniformLocation(program,RSTRING(arg2)->ptr);
	CHECK_GLERROR
	return INT2NUM(ret);
}


#define GET_UNIFORM_SIZE \
	switch (uniform_type) { \
		case GL_FLOAT: \
		case GL_INT: \
		case GL_BOOL: \
		case GL_SAMPLER_1D: \
		case GL_SAMPLER_2D: \
		case GL_SAMPLER_3D: \
		case GL_SAMPLER_CUBE: \
		case GL_SAMPLER_1D_SHADOW: \
		case GL_SAMPLER_2D_SHADOW: \
			uniform_size = 1; \
			break; \
		case GL_FLOAT_VEC2: \
		case GL_INT_VEC2: \
		case GL_BOOL_VEC2: \
			uniform_size = 2; \
			break; \
		case GL_FLOAT_VEC3: \
		case GL_INT_VEC3: \
		case GL_BOOL_VEC3: \
			uniform_size = 3; \
			break; \
		case GL_FLOAT_VEC4: \
		case GL_INT_VEC4: \
		case GL_BOOL_VEC4: \
		case GL_FLOAT_MAT2: \
			uniform_size = 4; \
			break; \
		case GL_FLOAT_MAT2x3: \
		case GL_FLOAT_MAT3x2: \
			uniform_size = 6; \
			break; \
		case GL_FLOAT_MAT2x4: \
		case GL_FLOAT_MAT4x2: \
			uniform_size = 8; \
			break; \
		case GL_FLOAT_MAT3: \
			uniform_size = 9; \
			break; \
		case GL_FLOAT_MAT4x3: \
		case GL_FLOAT_MAT3x4: \
			uniform_size = 12; \
			break; \
		case GL_FLOAT_MAT4: \
			uniform_size = 16; \
			break; \
		default: \
			rb_raise(rb_eTypeError, "Unsupported type '%i'",uniform_type); \
	}

static void (APIENTRY * fptr_glGetUniformfv)(GLuint,GLint,GLfloat *);
static VALUE
gl_GetUniformfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLint location;
	GLfloat params[16];
	VALUE retary;
	GLint i;
	GLint unused = 0;
	GLenum uniform_type = 0;
	GLint uniform_size = 0;

	LOAD_GL_FUNC(glGetUniformfv)
	LOAD_GL_FUNC(glGetActiveUniform)
	program = (GLuint)NUM2UINT(arg1);
	location = (GLint)NUM2INT(arg2);

	fptr_glGetActiveUniform(program,location,0,NULL,&unused,&uniform_type,NULL);
	CHECK_GLERROR
	if (uniform_type==0)
		rb_raise(rb_eTypeError, "Can't determine the uniform's type");

	GET_UNIFORM_SIZE

	memset(params,0,16*sizeof(GLfloat));
	fptr_glGetUniformfv(program,location,params);
	retary = rb_ary_new2(uniform_size);
	for(i=0;i<uniform_size;i++)
		rb_ary_push(retary, rb_float_new(params[i]));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetUniformiv)(GLuint,GLint,GLint *);
static VALUE
gl_GetUniformiv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint program;
	GLint location;
	GLint params[16];
	VALUE retary;
	GLint i;
	GLint unused = 0;
	GLenum uniform_type = 0;
	GLint uniform_size = 0;
	LOAD_GL_FUNC(glGetUniformiv)
	LOAD_GL_FUNC(glGetActiveUniform)
	program = (GLuint)NUM2UINT(arg1);
	location = (GLint)NUM2INT(arg2);

	fptr_glGetActiveUniform(program,location,0,NULL,&unused,&uniform_type,NULL);
	CHECK_GLERROR
	if (uniform_type==0)
		rb_raise(rb_eTypeError, "Can't determine the uniform's type");

	GET_UNIFORM_SIZE

	memset(params,0,16*sizeof(GLint));
	fptr_glGetUniformiv(program,location,params);
	retary = rb_ary_new2(uniform_size);
	for(i=0;i<uniform_size;i++)
		rb_ary_push(retary, INT2NUM(params[i]));
	CHECK_GLERROR
	return retary;
}

#define GETVERTEXATTRIB_FUNC(_name_,_type_,_conv_) \
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
	LOAD_GL_FUNC(gl##_name_) \
	index = (GLuint)NUM2UINT(arg1); \
	pname = (GLenum)NUM2INT(arg2); \
	if (pname==GL_CURRENT_VERTEX_ATTRIB) \
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

GETVERTEXATTRIB_FUNC(GetVertexAttribdv,GLdouble,rb_float_new)
GETVERTEXATTRIB_FUNC(GetVertexAttribfv,GLfloat,rb_float_new)
GETVERTEXATTRIB_FUNC(GetVertexAttribiv,GLint,INT2NUM)
#undef GETVERTEXATTRIB_FUNC

VALUE g_VertexAttrib_ptr[_MAX_VERTEX_ATTRIBS];

static void (APIENTRY * fptr_glGetVertexAttribPointerv)(GLuint,GLenum,GLvoid **);
static VALUE
gl_GetVertexAttribPointerv(obj,arg1)
VALUE obj,arg1;
{
	GLuint index;
	LOAD_GL_FUNC(glGetVertexAttribPointerv)
	index =(GLuint) NUM2INT(arg1);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	return g_VertexAttrib_ptr[index];
}

static GLboolean (APIENTRY * fptr_glIsProgram)(GLuint);
static VALUE
gl_IsProgram(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;
	GLboolean ret;
	LOAD_GL_FUNC(glIsProgram)
	program = (GLuint)NUM2UINT(arg1);
	ret = fptr_glIsProgram(program);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static GLboolean (APIENTRY * fptr_glIsShader)(GLuint);
static VALUE
gl_IsShader(obj,arg1)
VALUE obj,arg1;
{
	GLuint program;
	GLboolean ret;
	LOAD_GL_FUNC(glIsShader)
	program = (GLuint)NUM2UINT(arg1);
	ret = fptr_glIsShader(program);
	CHECK_GLERROR
	return INT2NUM(ret);
}

static void (APIENTRY * fptr_glShaderSource)(GLuint,GLsizei,GLchar**,GLint *);
static VALUE
gl_ShaderSource(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLuint shader;
	GLint length;
	GLchar *str;
	LOAD_GL_FUNC(glShaderSource)
	shader = (GLuint)NUM2UINT(arg1);
	Check_Type(arg2,T_STRING);
	str = RSTRING(arg2)->ptr;
	length = RSTRING(arg2)->len;
	fptr_glShaderSource(shader,1,&str,&length);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform1f)(GLint,GLfloat);
static VALUE
gl_Uniform1f(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLint location;
	GLfloat v0;
	LOAD_GL_FUNC(glUniform1f)
	location = (GLint)NUM2INT(arg1);
	v0 = (GLfloat)NUM2DBL(arg2);
	fptr_glUniform1f(location,v0);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform2f)(GLint,GLfloat,GLfloat);
static VALUE
gl_Uniform2f(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLfloat v0;
	GLfloat v1;
	LOAD_GL_FUNC(glUniform2f)
	location = (GLint)NUM2INT(arg1);
	v0 = (GLfloat)NUM2DBL(arg2);
	v1 = (GLfloat)NUM2DBL(arg3);
	fptr_glUniform2f(location,v0,v1);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform3f)(GLint,GLfloat,GLfloat,GLfloat);
static VALUE
gl_Uniform3f(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	LOAD_GL_FUNC(glUniform3f)
	location = (GLint)NUM2INT(arg1);
	v0 = (GLfloat)NUM2DBL(arg2);
	v1 = (GLfloat)NUM2DBL(arg3);
	v2 = (GLfloat)NUM2DBL(arg4);
	fptr_glUniform3f(location,v0,v1,v2);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform4f)(GLint,GLfloat,GLfloat,GLfloat,GLfloat);
static VALUE
gl_Uniform4f(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
	GLint location;
	GLfloat v0;
	GLfloat v1;
	GLfloat v2;
	GLfloat v3;
	LOAD_GL_FUNC(glUniform4f)
	location = (GLint)NUM2INT(arg1);
	v0 = (GLfloat)NUM2DBL(arg2);
	v1 = (GLfloat)NUM2DBL(arg3);
	v2 = (GLfloat)NUM2DBL(arg4);
	v3 = (GLfloat)NUM2DBL(arg5);
	fptr_glUniform4f(location,v0,v1,v2,v3);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform1fv)(GLint,GLsizei,GLfloat *);
static VALUE
gl_Uniform1fv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLfloat *value;
	LOAD_GL_FUNC(glUniform1fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLfloat,1*count);
	ary2cflt(arg3,value,1*count);
	fptr_glUniform1fv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform2fv)(GLint,GLsizei,GLfloat *);
static VALUE
gl_Uniform2fv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLfloat *value;
	LOAD_GL_FUNC(glUniform2fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLfloat,2*count);
	ary2cflt(arg3,value,2*count);
	fptr_glUniform2fv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform3fv)(GLint,GLsizei,GLfloat *);
static VALUE
gl_Uniform3fv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLfloat *value;
	LOAD_GL_FUNC(glUniform3fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLfloat,3*count);
	ary2cflt(arg3,value,3*count);
	fptr_glUniform3fv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform4fv)(GLint,GLsizei,GLfloat *);
static VALUE
gl_Uniform4fv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLfloat *value;
	LOAD_GL_FUNC(glUniform4fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLfloat,4*count);
	ary2cflt(arg3,value,4*count);
	fptr_glUniform4fv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform1iv)(GLint,GLsizei,GLint *);
static VALUE
gl_Uniform1iv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLint *value;
	LOAD_GL_FUNC(glUniform1iv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLint,1*count);
	ary2cint(arg3,value,1*count);
	fptr_glUniform1iv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform2iv)(GLint,GLsizei,GLint *);
static VALUE
gl_Uniform2iv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLint *value;
	LOAD_GL_FUNC(glUniform2iv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLint,2*count);
	ary2cint(arg3,value,2*count);
	fptr_glUniform2iv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform3iv)(GLint,GLsizei,GLint *);
static VALUE
gl_Uniform3iv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLint *value;
	LOAD_GL_FUNC(glUniform3iv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLint,3*count);
	ary2cint(arg3,value,3*count);
	fptr_glUniform3iv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniform4iv)(GLint,GLsizei,GLint *);
static VALUE
gl_Uniform4iv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLint location;
	GLsizei count;
	GLint *value;
	LOAD_GL_FUNC(glUniform4iv)
	location = (GLint)NUM2INT(arg1);
	count = (GLsizei)NUM2UINT(arg2);
	value = ALLOC_N(GLint,4*count);
	ary2cint(arg3,value,4*count);
	fptr_glUniform4iv(location,count,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniformMatrix2fv)(GLint,GLsizei,GLboolean,GLfloat *);
static VALUE
gl_UniformMatrix2fv(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat *value;	
	LOAD_GL_FUNC(glUniformMatrix2fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLint)NUM2INT(arg2);
	transpose = (GLboolean)NUM2INT(arg3);
	value = ALLOC_N(GLfloat, 2*2*count);
	ary2cflt(arg4,value,2*2*count);
	fptr_glUniformMatrix2fv(location,count,transpose,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniformMatrix3fv)(GLint,GLsizei,GLboolean,GLfloat *);
static VALUE
gl_UniformMatrix3fv(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat *value;	
	LOAD_GL_FUNC(glUniformMatrix3fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLint)NUM2INT(arg2);
	transpose = (GLboolean)NUM2INT(arg3);
	value = ALLOC_N(GLfloat, 3*3*count);
	ary2cflt(arg4,value,3*3*count);
	fptr_glUniformMatrix3fv(location,count,transpose,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glUniformMatrix4fv)(GLint,GLsizei,GLboolean,GLfloat *);
static VALUE
gl_UniformMatrix4fv(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLint location;
	GLsizei count;
	GLboolean transpose;
	GLfloat *value;	
	LOAD_GL_FUNC(glUniformMatrix4fv)
	location = (GLint)NUM2INT(arg1);
	count = (GLint)NUM2INT(arg2);
	transpose = (GLboolean)NUM2INT(arg3);
	value = ALLOC_N(GLfloat, 4*4*count);
	ary2cflt(arg4,value,4*4*count);
	fptr_glUniformMatrix4fv(location,count,transpose,value);
	xfree(value);
	CHECK_GLERROR
	return Qnil;
}

#define VERTEXATTRIB_FUNC(_name_,_type_,_conv_,_size_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,TYPELIST##_size_(_type_)); \
static VALUE \
gl_##_name_(obj, index ARGLIST##_size_) \
VALUE obj, index ARGLIST##_size_ ; \
{ \
	LOAD_GL_FUNC(gl##_name_) \
	fptr_gl##_name_(NUM2UINT(index),FUNCPARAMS##_size_(_type_,_conv_)); \
	CHECK_GLERROR \
	return Qnil; \
}

VERTEXATTRIB_FUNC(VertexAttrib1d,GLdouble,NUM2DBL,1)
VERTEXATTRIB_FUNC(VertexAttrib1f,GLfloat,NUM2DBL,1)
VERTEXATTRIB_FUNC(VertexAttrib1s,GLshort,NUM2INT,1)
VERTEXATTRIB_FUNC(VertexAttrib2d,GLdouble,NUM2DBL,2)
VERTEXATTRIB_FUNC(VertexAttrib2f,GLfloat,NUM2DBL,2)
VERTEXATTRIB_FUNC(VertexAttrib2s,GLshort,NUM2INT,2)
VERTEXATTRIB_FUNC(VertexAttrib3d,GLdouble,NUM2DBL,3)
VERTEXATTRIB_FUNC(VertexAttrib3f,GLfloat,NUM2DBL,3)
VERTEXATTRIB_FUNC(VertexAttrib3s,GLshort,NUM2INT,3)
VERTEXATTRIB_FUNC(VertexAttrib4d,GLdouble,NUM2DBL,4)
VERTEXATTRIB_FUNC(VertexAttrib4f,GLfloat,NUM2DBL,4)
VERTEXATTRIB_FUNC(VertexAttrib4s,GLshort,NUM2INT,4)
VERTEXATTRIB_FUNC(VertexAttrib4Nub,GLubyte,NUM2UINT,4)
#undef VERTEXATTRIB_FUNC


#define VERTEXATTRIB_FUNC_V(_name_,_type_,_conv_,_size_) \
static void (APIENTRY * fptr_gl##_name_)(GLuint,_type_ *); \
static VALUE \
gl_##_name_(obj,arg1,arg2) \
VALUE obj,arg1,arg2; \
{ \
	GLuint index; \
	_type_ v[_size_]; \
	LOAD_GL_FUNC(gl##_name_)  \
	index = (GLuint)NUM2UINT(arg1); \
	_conv_(arg2,v,_size_); \
	fptr_gl##_name_(index,v); \
	CHECK_GLERROR \
	return Qnil; \
}

VERTEXATTRIB_FUNC_V(VertexAttrib4Nbv,GLbyte,ary2cbyte,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4Niv,GLint,ary2cint,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4Nsv,GLshort,ary2cshort,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4Nubv,GLubyte,ary2cubyte,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4Nuiv,GLuint,ary2cuint,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4Nusv,GLushort,ary2cushort,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4uiv,GLuint,ary2cuint,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4ubv,GLubyte,ary2cubyte,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4usv,GLushort,ary2cushort,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4bv,GLbyte,ary2cbyte,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4iv,GLint,ary2cint,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4dv,GLdouble,ary2cdbl,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4fv,GLfloat,ary2cflt,4)
VERTEXATTRIB_FUNC_V(VertexAttrib4sv,GLshort,ary2cshort,4)
VERTEXATTRIB_FUNC_V(VertexAttrib3dv,GLdouble,ary2cdbl,3)
VERTEXATTRIB_FUNC_V(VertexAttrib3fv,GLfloat,ary2cflt,3)
VERTEXATTRIB_FUNC_V(VertexAttrib3sv,GLshort,ary2cshort,3)
VERTEXATTRIB_FUNC_V(VertexAttrib2dv,GLdouble,ary2cdbl,2)
VERTEXATTRIB_FUNC_V(VertexAttrib2fv,GLfloat,ary2cflt,2)
VERTEXATTRIB_FUNC_V(VertexAttrib2sv,GLshort,ary2cshort,2)
VERTEXATTRIB_FUNC_V(VertexAttrib1dv,GLdouble,ary2cdbl,1)
VERTEXATTRIB_FUNC_V(VertexAttrib1fv,GLfloat,ary2cflt,1)
VERTEXATTRIB_FUNC_V(VertexAttrib1sv,GLshort,ary2cshort,1)
#undef VERTEXATTRIB_FUNC_V

static void (APIENTRY * fptr_glVertexAttribPointer)(GLuint,GLint,GLenum,GLboolean,GLsizei,GLvoid *);
static VALUE
gl_VertexAttribPointer(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLuint index;
	GLuint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	LOAD_GL_FUNC(glVertexAttribPointer)
	index = (GLuint)NUM2UINT(arg1);
	size = (GLuint)NUM2UINT(arg2);
	type = (GLenum)NUM2INT(arg3);
	normalized = (GLboolean)NUM2INT(arg4);
	stride = (GLsizei)NUM2UINT(arg5);
	if (index>_MAX_VERTEX_ATTRIBS)
		rb_raise(rb_eArgError, "Index too large, maximum allowed value '%i'",_MAX_VERTEX_ATTRIBS);

	if (CheckBufferBinding(GL_ARRAY_BUFFER_BINDING)) {
		g_VertexAttrib_ptr[index] = arg6;
		fptr_glVertexAttribPointer(index,size,type,normalized,stride,(GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6, T_STRING);
		rb_str_freeze(arg6);
		g_VertexAttrib_ptr[index] = arg6;
		fptr_glVertexAttribPointer(index,size,type,normalized,stride,(GLvoid *)RSTRING(arg6)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

void gl_init_functions_2_0(VALUE module)
{
	rb_define_module_function(module, "glBlendEquationSeparate", gl_BlendEquationSeparate, 2);
	rb_define_module_function(module, "glDrawBuffers", gl_DrawBuffers, 1);
	rb_define_module_function(module, "glStencilOpSeparate", gl_StencilOpSeparate, 4);
	rb_define_module_function(module, "glStencilFuncSeparate", gl_StencilFuncSeparate, 4);
	rb_define_module_function(module, "glStencilMaskSeparate", gl_StencilMaskSeparate, 2);
	rb_define_module_function(module, "glAttachShader", gl_AttachShader, 2);
	rb_define_module_function(module, "glBindAttribLocation", gl_BindAttribLocation, 3);
	rb_define_module_function(module, "glCompileShader", gl_CompileShader, 1);
	rb_define_module_function(module, "glCreateProgram", gl_CreateProgram, 0);
	rb_define_module_function(module, "glCreateShader", gl_CreateShader, 1);
	rb_define_module_function(module, "glDeleteProgram", gl_DeleteProgram, 1);
	rb_define_module_function(module, "glDeleteShader", gl_DeleteShader, 1);
	rb_define_module_function(module, "glDetachShader", gl_DetachShader, 2);
	rb_define_module_function(module, "glDisableVertexAttribArray", gl_DisableVertexAttribArray, 1);
	rb_define_module_function(module, "glEnableVertexAttribArray", gl_EnableVertexAttribArray, 1);
	rb_define_module_function(module, "glGetActiveAttrib", gl_GetActiveAttrib, 2);
	rb_define_module_function(module, "glGetActiveUniform", gl_GetActiveUniform, 2);
	rb_define_module_function(module, "glGetAttachedShaders", gl_GetAttachedShaders, 1);
	rb_define_module_function(module, "glGetAttribLocation", gl_GetAttribLocation, 2);
	rb_define_module_function(module, "glGetProgramiv", gl_GetProgramiv, 2);
	rb_define_module_function(module, "glGetProgramInfoLog", gl_GetProgramInfoLog, 1);
	rb_define_module_function(module, "glGetShaderiv", gl_GetShaderiv, 2);
	rb_define_module_function(module, "glGetShaderInfoLog", gl_GetShaderInfoLog, 1);
	rb_define_module_function(module, "glGetShaderSource", gl_GetShaderSource, 1);
	rb_define_module_function(module, "glGetUniformLocation", gl_GetUniformLocation, 2);
	rb_define_module_function(module, "glGetUniformfv", gl_GetUniformfv, 2);
	rb_define_module_function(module, "glGetUniformiv", gl_GetUniformiv, 2);
	rb_define_module_function(module, "glGetVertexAttribdv", gl_GetVertexAttribdv, 2);
	rb_define_module_function(module, "glGetVertexAttribfv", gl_GetVertexAttribfv, 2);
	rb_define_module_function(module, "glGetVertexAttribiv", gl_GetVertexAttribiv, 2);
	rb_define_module_function(module, "glGetVertexAttribPointerv", gl_GetVertexAttribPointerv, 1);
	rb_define_module_function(module, "glIsProgram", gl_IsProgram, 1);
	rb_define_module_function(module, "glIsShader", gl_IsShader, 1);
	rb_define_module_function(module, "glLinkProgram", gl_LinkProgram, 1);
	rb_define_module_function(module, "glShaderSource", gl_ShaderSource, 2);
	rb_define_module_function(module, "glUseProgram", gl_UseProgram, 1);
	rb_define_module_function(module, "glUniform1f", gl_Uniform1f, 2);
	rb_define_module_function(module, "glUniform2f", gl_Uniform2f, 3);
	rb_define_module_function(module, "glUniform3f", gl_Uniform3f, 4);
	rb_define_module_function(module, "glUniform4f", gl_Uniform4f, 5);
	rb_define_module_function(module, "glUniform1i", gl_Uniform1i, 2);
	rb_define_module_function(module, "glUniform2i", gl_Uniform2i, 3);
	rb_define_module_function(module, "glUniform3i", gl_Uniform3i, 4);
	rb_define_module_function(module, "glUniform4i", gl_Uniform4i, 5);
	rb_define_module_function(module, "glUniform1fv", gl_Uniform1fv, 3);
	rb_define_module_function(module, "glUniform2fv", gl_Uniform2fv, 3);
	rb_define_module_function(module, "glUniform3fv", gl_Uniform3fv, 3);
	rb_define_module_function(module, "glUniform4fv", gl_Uniform4fv, 3);
	rb_define_module_function(module, "glUniform1iv", gl_Uniform1iv, 3);
	rb_define_module_function(module, "glUniform2iv", gl_Uniform2iv, 3);
	rb_define_module_function(module, "glUniform3iv", gl_Uniform3iv, 3);
	rb_define_module_function(module, "glUniform4iv", gl_Uniform4iv, 3);
	rb_define_module_function(module, "glUniformMatrix2fv", gl_UniformMatrix2fv, 4);
	rb_define_module_function(module, "glUniformMatrix3fv", gl_UniformMatrix3fv, 4);
	rb_define_module_function(module, "glUniformMatrix4fv", gl_UniformMatrix4fv, 4);
	rb_define_module_function(module, "glValidateProgram", gl_ValidateProgram, 1);
	rb_define_module_function(module, "glVertexAttrib1d", gl_VertexAttrib1d, 2);
	rb_define_module_function(module, "glVertexAttrib1f", gl_VertexAttrib1f, 2);
	rb_define_module_function(module, "glVertexAttrib1s", gl_VertexAttrib1s, 2);
	rb_define_module_function(module, "glVertexAttrib2d", gl_VertexAttrib2d, 3);
	rb_define_module_function(module, "glVertexAttrib2f", gl_VertexAttrib2f, 3);
	rb_define_module_function(module, "glVertexAttrib2s", gl_VertexAttrib2s, 3);
	rb_define_module_function(module, "glVertexAttrib3d", gl_VertexAttrib3d, 4);
	rb_define_module_function(module, "glVertexAttrib3f", gl_VertexAttrib3f, 4);
	rb_define_module_function(module, "glVertexAttrib3s", gl_VertexAttrib3s, 4);
	rb_define_module_function(module, "glVertexAttrib4Nbv", gl_VertexAttrib4Nbv, 2);
	rb_define_module_function(module, "glVertexAttrib4Niv", gl_VertexAttrib4Niv, 2);
	rb_define_module_function(module, "glVertexAttrib4Nsv", gl_VertexAttrib4Nsv, 2);
	rb_define_module_function(module, "glVertexAttrib4Nub", gl_VertexAttrib4Nub, 5);
	rb_define_module_function(module, "glVertexAttrib4Nubv", gl_VertexAttrib4Nubv, 2);
	rb_define_module_function(module, "glVertexAttrib4Nuiv", gl_VertexAttrib4Nuiv, 2);
	rb_define_module_function(module, "glVertexAttrib4Nusv", gl_VertexAttrib4Nusv, 2);
	rb_define_module_function(module, "glVertexAttrib4bv", gl_VertexAttrib4bv, 2);
	rb_define_module_function(module, "glVertexAttrib4d", gl_VertexAttrib4d, 5);
	rb_define_module_function(module, "glVertexAttrib4f", gl_VertexAttrib4f, 5);
	rb_define_module_function(module, "glVertexAttrib4iv", gl_VertexAttrib4iv, 2);
	rb_define_module_function(module, "glVertexAttrib4s", gl_VertexAttrib4s, 5);
	rb_define_module_function(module, "glVertexAttrib4ubv", gl_VertexAttrib4ubv, 2);
	rb_define_module_function(module, "glVertexAttrib4uiv", gl_VertexAttrib4uiv, 2);
	rb_define_module_function(module, "glVertexAttrib4usv", gl_VertexAttrib4usv, 2);
	rb_define_module_function(module, "glVertexAttrib1dv", gl_VertexAttrib1dv, 2);
	rb_define_module_function(module, "glVertexAttrib1fv", gl_VertexAttrib1fv, 2);
	rb_define_module_function(module, "glVertexAttrib1sv", gl_VertexAttrib1sv, 2);
	rb_define_module_function(module, "glVertexAttrib2dv", gl_VertexAttrib2dv, 2);
	rb_define_module_function(module, "glVertexAttrib2fv", gl_VertexAttrib2fv, 2);
	rb_define_module_function(module, "glVertexAttrib2sv", gl_VertexAttrib2sv, 2);
	rb_define_module_function(module, "glVertexAttrib3dv", gl_VertexAttrib3dv, 2);
	rb_define_module_function(module, "glVertexAttrib3fv", gl_VertexAttrib3fv, 2);
	rb_define_module_function(module, "glVertexAttrib3sv", gl_VertexAttrib3sv, 2);
	rb_define_module_function(module, "glVertexAttrib4dv", gl_VertexAttrib4dv, 2);
	rb_define_module_function(module, "glVertexAttrib4fv", gl_VertexAttrib4fv, 2);
	rb_define_module_function(module, "glVertexAttrib4sv", gl_VertexAttrib4sv, 2);
	rb_define_module_function(module, "glVertexAttribPointer", gl_VertexAttribPointer, 6);

	{
		int i;
		for (i=0;i<_MAX_VERTEX_ATTRIBS;i++)
			rb_global_variable(&g_VertexAttrib_ptr[i]);
	}
}
