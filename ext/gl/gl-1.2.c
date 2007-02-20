/*
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
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

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif defined WIN32
#include <windows.h>
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "../common/rbogl.h"
#include "../common/gl-enums.h"

/* OpenGL 1.2 functions */

/*
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
*/



void gl_init_functions_1_2(VALUE module)
{
	/*
	rb_define_module_function(module, "glDrawRangeElements", gl_DrawRangeElements, 6);
	rb_define_module_function(module, "glTexImage3D", gl_TexImage3D, 10);
	rb_define_module_function(module, "glTexSubImage3D", gl_TexSubImage3D, 11);
	rb_define_module_function(module, "glCopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
	*/
}
