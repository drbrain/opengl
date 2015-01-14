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

#define UNIFORMMATRIX_FUNC(_x_,_y_) \
static VALUE \
gl_UniformMatrix##_x_##x##_y_##fv(obj,arg1,arg2,arg3) \
VALUE obj,arg1,arg2,arg3; \
{ \
	GLint location; \
	GLsizei count; \
	GLboolean transpose; \
	GLfloat *value;	\
	DECL_GL_FUNC_PTR(GLvoid,glUniformMatrix##_x_##x##_y_##fv,(GLint,GLsizei,GLboolean,GLfloat *)); \
	LOAD_GL_FUNC(glUniformMatrix##_x_##x##_y_##fv,"2.1"); \
	location = (GLint)NUM2INT(arg1); \
	count = (GLsizei)RARRAY_LENINT(rb_funcall(rb_Array(arg3),rb_intern("flatten"),0)); \
	transpose = (GLboolean)RUBYBOOL2GL(arg2); \
	value = ALLOC_N(GLfloat, count); \
	ary2cmatfloatcount(arg3,value, _x_, _y_); \
	fptr_glUniformMatrix##_x_##x##_y_##fv(location,count /(_x_ * _y_),transpose,value); \
	xfree(value); \
	CHECK_GLERROR_FROM("glUniformMatrix" #_x_ "x" #_y_ "fv"); \
	return Qnil; \
}

UNIFORMMATRIX_FUNC(2,3)
UNIFORMMATRIX_FUNC(3,2)
UNIFORMMATRIX_FUNC(2,4)
UNIFORMMATRIX_FUNC(4,2)
UNIFORMMATRIX_FUNC(3,4)
UNIFORMMATRIX_FUNC(4,3)

#undef UNIFORMMATRIX_FUNC

void gl_init_functions_2_1(VALUE klass)
{
	rb_define_method(klass, "glUniformMatrix2x3fv", gl_UniformMatrix2x3fv, 3);
	rb_define_method(klass, "glUniformMatrix3x2fv", gl_UniformMatrix3x2fv, 3);
	rb_define_method(klass, "glUniformMatrix2x4fv", gl_UniformMatrix2x4fv, 3);
	rb_define_method(klass, "glUniformMatrix4x2fv", gl_UniformMatrix4x2fv, 3);
	rb_define_method(klass, "glUniformMatrix3x4fv", gl_UniformMatrix3x4fv, 3);
	rb_define_method(klass, "glUniformMatrix4x3fv", gl_UniformMatrix4x3fv, 3);
}
