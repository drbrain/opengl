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
#define TRANSPOSEMATRIX_FUNC(_name_,_type_,_shorttype_) \
static void (APIENTRY * fptr_gl##_name_)(const _type_[]); \
static VALUE \
gl_##_name_(obj,arg1) \
VALUE obj,arg1; \
{ \
	_type_ m[4*4]; \
	LOAD_GL_EXT_FUNC(gl##_name_,"GL_ARB_transpose_matrix") \
	ary2cmat4x4##_shorttype_(arg1, m); \
	fptr_gl##_name_(m); \
	return Qnil; \
}

TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixfARB,GLfloat,flt)
TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixdARB,GLdouble,dbl)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixfARB,GLfloat,flt)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixdARB,GLdouble,dbl)

#undef TRANSPOSEMATRIX_FUNC

/* #5 GL_ARB_multisample */
static void (APIENTRY * fptr_glSampleCoverageARB)(GLclampf,GLboolean);
static VALUE gl_SampleCoverageARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glSampleCoverageARB,"GL_ARB_multisample")
	fptr_glSampleCoverageARB((GLclampf)NUM2DBL(arg1),(GLboolean)NUM2INT(arg2));
	return Qnil;
}

void gl_init_functions_ext_arb(VALUE module)
{
/* #3 GL_ARB_transpose_matrix */
	rb_define_module_function(module, "glLoadTransposeMatrixfARB", gl_LoadTransposeMatrixfARB, 1);
	rb_define_module_function(module, "glLoadTransposeMatrixdARB", gl_LoadTransposeMatrixdARB, 1);
	rb_define_module_function(module, "glMultTransposeMatrixfARB", gl_MultTransposeMatrixfARB, 1);
	rb_define_module_function(module, "glMultTransposeMatrixdARB", gl_MultTransposeMatrixdARB, 1);

/* #5 GL_ARB_multisample */
	rb_define_module_function(module, "glSampleCoverageARB", gl_SampleCoverageARB, 2);
}
