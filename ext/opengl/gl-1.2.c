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
GL_FUNC_LOAD_9(CopyTexSubImage3D,GLvoid, GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei, "1.2")

static VALUE
gl_DrawRangeElements(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
  DECL_GL_FUNC_PTR(GLvoid,glDrawRangeElements,(GLenum,GLuint,GLuint,GLsizei,GLenum,GLvoid*));
	LOAD_GL_FUNC(glDrawRangeElements, "1.2");
	mode = (GLenum)NUM2INT(arg1);
	start = (GLuint)NUM2UINT(arg2);
	end = (GLuint)NUM2UINT(arg3);
	count = (GLsizei)NUM2UINT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CHECK_BUFFER_BINDING(GL_ELEMENT_ARRAY_BUFFER_BINDING)) {
		fptr_glDrawRangeElements(mode, start, end, count, type, (GLvoid *)NUM2SIZET(arg6));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(type,arg6);
		fptr_glDrawRangeElements(mode, start, end, count, type, RSTRING_PTR(data));
	}
	CHECK_GLERROR_FROM("glDrawRangeElements");
	return Qnil;
}

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
  DECL_GL_FUNC_PTR(GLvoid,glTexImage3D,(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*));
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

	if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexImage3D( target, level, internalFormat, width, height,
						depth, border, format, type,(GLvoid *)NUM2SIZET(arg10));
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
  DECL_GL_FUNC_PTR(GLvoid,glTexSubImage3D,(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*));
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
	if (CHECK_BUFFER_BINDING(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
				width, height, depth,
				format, type, (GLvoid *)NUM2SIZET(arg11));
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

void gl_init_functions_1_2(VALUE klass)
{
	rb_define_method(klass, "glBlendColor", gl_BlendColor, 4);
	rb_define_method(klass, "glBlendEquation", gl_BlendEquation, 1);
	rb_define_method(klass, "glDrawRangeElements", gl_DrawRangeElements, 6);
	rb_define_method(klass, "glTexImage3D", gl_TexImage3D, 10);
	rb_define_method(klass, "glTexSubImage3D", gl_TexSubImage3D, 11);
	rb_define_method(klass, "glCopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
}
