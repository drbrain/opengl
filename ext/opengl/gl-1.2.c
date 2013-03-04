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

/* OpenGL 1.2 functions */

GL_FUNC_LOAD_4(BlendColor,GLvoid, GLclampf,GLclampf,GLclampf,GLclampf, "1.2")
GL_FUNC_LOAD_1(BlendEquation,GLvoid, GLenum, "1.2")
GL_FUNC_LOAD_5(CopyColorTable,GLvoid, GLenum,GLenum,GLint,GLint,GLsizei, "1.2")
GL_FUNC_LOAD_5(CopyColorSubTable,GLvoid, GLenum,GLsizei,GLint,GLint,GLsizei, "1.2")
GL_FUNC_LOAD_9(CopyTexSubImage3D,GLvoid, GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei, "1.2")

static void (APIENTRY * fptr_glDrawRangeElements)(GLenum,GLuint,GLuint,GLsizei,GLenum,GLvoid*);
static VALUE
gl_DrawRangeElements(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
	LOAD_GL_FUNC(glDrawRangeElements, "1.2");
	mode = (GLenum)NUM2INT(arg1);
	start = (GLuint)NUM2UINT(arg2);
	end = (GLuint)NUM2UINT(arg3);
	count = (GLsizei)NUM2UINT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CheckBufferBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING)) {
		fptr_glDrawRangeElements(mode, start, end, count, type, (GLvoid *)NUM2LONG(arg6));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg6);
		fptr_glDrawRangeElements(mode, start, end, count, type, RSTRING_PTR(data));
	}
	CHECK_GLERROR_FROM("glDrawRangeElements");
	return Qnil;
}

static void (APIENTRY * fptr_glColorTable)(GLenum,GLenum,GLsizei,GLenum,GLenum,GLvoid*);
static VALUE
gl_ColorTable(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glColorTable, "1.2");
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	width = (GLsizei)NUM2UINT(arg3);
	format = (GLenum)NUM2INT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glColorTable(target,internalformat,width,format,type,(GLvoid *)NUM2LONG(arg6));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg6);
		CheckDataSize(type,format,width,data);
		fptr_glColorTable(target,internalformat,width,format,type,(GLvoid*)RSTRING_PTR(data));
	}
	CHECK_GLERROR_FROM("glColorTable");
	return Qnil;
}

static void (APIENTRY * fptr_glColorTableParameterfv)(GLenum,GLenum,const GLfloat*);
static VALUE
gl_ColorTableParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {(GLfloat)0.0,(GLfloat)0.0,(GLfloat)0.0,(GLfloat)0.0};
	LOAD_GL_FUNC(glColorTableParameterfv, "1.2");
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cflt(arg3,params,4);
	fptr_glColorTableParameterfv(target,pname,params);
	CHECK_GLERROR_FROM("glColorTableParameterfv");
	return Qnil;
}

static void (APIENTRY * fptr_glColorTableParameteriv)(GLenum,GLenum,const GLint*);
static VALUE
gl_ColorTableParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	LOAD_GL_FUNC(glColorTableParameteriv, "1.2");
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cint(arg3,params,4);
	fptr_glColorTableParameteriv(target,pname,params);
	CHECK_GLERROR_FROM("glColorTableParameteriv");
	return Qnil;
}


static void (APIENTRY * fptr_glGetColorTableParameterfv)(GLenum,GLenum,GLfloat *);
static VALUE
gl_GetColorTableParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {(GLfloat)0.0,(GLfloat)0.0,(GLfloat)0.0,(GLfloat)0.0};
	GLsizei size;
	LOAD_GL_FUNC(glGetColorTableParameterfv, "1.2");
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch (pname) {
		case GL_COLOR_TABLE_SCALE:
		case GL_COLOR_TABLE_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetColorTableParameterfv(target,pname,params);
	RET_ARRAY_OR_SINGLE("glGetColorTableParameterfv", size, RETCONV_GLfloat,
			params);
}

static void (APIENTRY * fptr_glGetColorTableParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetColorTableParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	GLsizei size;
	LOAD_GL_FUNC(glGetColorTableParameteriv, "1.2");
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch (pname) {
		case GL_COLOR_TABLE_SCALE:
		case GL_COLOR_TABLE_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetColorTableParameteriv(target,pname,params);
	RET_ARRAY_OR_SINGLE("glGetColorTableParameteriv", size, RETCONV_GLint,
			params);
}

static void (APIENTRY * fptr_glGetColorTable)(GLenum,GLenum,GLenum,GLvoid *);
static VALUE
gl_GetColorTable(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum format;
	GLenum type;
	GLsizei width = 0;
	VALUE data;
	LOAD_GL_FUNC(glGetColorTable, "1.2");
	LOAD_GL_FUNC(glGetColorTableParameteriv, "1.2");
	target = (GLenum)NUM2INT(arg1);
	format = (GLenum)NUM2INT(arg2);
	type = (GLenum)NUM2INT(arg3);
	fptr_glGetColorTableParameteriv(target,GL_COLOR_TABLE_WIDTH,&width);
	CHECK_GLERROR_FROM("glGetColorTableParameteriv");
	data = allocate_buffer_with_string(GetDataSize(type,format,width));
	FORCE_PIXEL_STORE_MODE
	fptr_glGetColorTable(target,format,type,(GLvoid*)RSTRING_PTR(data));	
	RESTORE_PIXEL_STORE_MODE
	CHECK_GLERROR_FROM("glGetColorTable");
	return data;
}

static void (APIENTRY * fptr_glColorSubTable)(GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid *data);
static VALUE
gl_ColorSubTable(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLsizei start;
	GLsizei count;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glColorSubTable, "1.2");
	target = (GLenum)NUM2INT(arg1);	
	start = (GLsizei)NUM2UINT(arg2);	
	count = (GLsizei)NUM2UINT(arg3);	
	format = (GLenum)NUM2INT(arg4);	
	type = (GLenum)NUM2INT(arg5);	
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glColorSubTable(target,start,count,format,type,(GLvoid *)NUM2LONG(arg6));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg6);
		CheckDataSize(type,format,count,data);
		fptr_glColorSubTable(target,start,count,format,type,RSTRING_PTR(data));
	}
	CHECK_GLERROR_FROM("glColorSubTable");
	return Qnil;
}

static void (APIENTRY * fptr_glTexImage3D)(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*);
static VALUE
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
	const char *pixels;
	LOAD_GL_FUNC(glTexImage3D, "1.2");
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	internalFormat = (GLint)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	height = (GLsizei)NUM2UINT(arg5);
	depth = (GLsizei)NUM2UINT(arg6);
	border = (GLint)NUM2INT(arg7);
	format = (GLenum)NUM2INT(arg8);
	type = (GLenum)NUM2INT(arg9);

	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexImage3D( target, level, internalFormat, width, height,
						depth, border, format, type,(GLvoid *)NUM2LONG(arg10));
		CHECK_GLERROR_FROM("glTexImage3D");
		return Qnil;
	}

	if (target == GL_PROXY_TEXTURE_3D  ||
			target == GL_PROXY_TEXTURE_1D_STACK_MESAX ||
			target == GL_PROXY_TEXTURE_2D_STACK_MESAX ||
			target == GL_PROXY_TEXTURE_2D_ARRAY_EXT ||
			NIL_P(arg10)) { /* proxy texture, no data read */
		pixels = NULL;
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg10);

		CheckDataSize(type,format,width*height*depth,data);
		pixels = RSTRING_PTR(data);
	}
	fptr_glTexImage3D( target, level, internalFormat, width, height,
					depth, border, format, type,pixels);
	CHECK_GLERROR_FROM("glTexImage3D");
	return Qnil;
}

static void (APIENTRY * fptr_glTexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
static VALUE
gl_TexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11;
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
	LOAD_GL_FUNC(glTexSubImage3D, "1.2");
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	yoffset = (GLint)NUM2INT(arg4);
	zoffset = (GLint)NUM2INT(arg5);
	width = (GLsizei)NUM2UINT(arg6);
	height = (GLsizei)NUM2UINT(arg7);
	depth = (GLsizei)NUM2UINT(arg8);
	format = (GLenum)NUM2INT(arg9);
	type = (GLenum)NUM2INT(arg10);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
				width, height, depth,
				format, type, (GLvoid *)NUM2LONG(arg11));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg11);
		CheckDataSize(type,format,height*width*depth,data);
		fptr_glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
			width, height, depth,
			format, type, RSTRING_PTR(data));
	}
	CHECK_GLERROR_FROM("glTexSubImage3D");
	return Qnil;
}

void gl_init_functions_1_2(VALUE module)
{
	rb_define_module_function(module, "glBlendColor", gl_BlendColor, 4);
	rb_define_module_function(module, "glBlendEquation", gl_BlendEquation, 1);
	rb_define_module_function(module, "glDrawRangeElements", gl_DrawRangeElements, 6);
	rb_define_module_function(module, "glColorTable", gl_ColorTable, 6);
	rb_define_module_function(module, "glColorTableParameterfv", gl_ColorTableParameterfv, 3);
	rb_define_module_function(module, "glColorTableParameteriv", gl_ColorTableParameteriv, 3);
	rb_define_module_function(module, "glCopyColorTable", gl_CopyColorTable, 5);
	rb_define_module_function(module, "glGetColorTable", gl_GetColorTable, 3);
	rb_define_module_function(module, "glGetColorTableParameterfv", gl_GetColorTableParameterfv, 2);
	rb_define_module_function(module, "glGetColorTableParameteriv", gl_GetColorTableParameteriv, 2);
	rb_define_module_function(module, "glColorSubTable", gl_ColorSubTable, 6);
	rb_define_module_function(module, "glCopyColorSubTable", gl_CopyColorSubTable, 5);
	rb_define_module_function(module, "glTexImage3D", gl_TexImage3D, 10);
	rb_define_module_function(module, "glTexSubImage3D", gl_TexSubImage3D, 11);
	rb_define_module_function(module, "glCopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
}
