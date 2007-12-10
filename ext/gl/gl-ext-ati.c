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

/* OpenGL ATI extensions */

/* #277 GL_ATI_draw_buffers */
static void (APIENTRY * fptr_glDrawBuffersATI)(GLsizei,const GLenum *);
static VALUE gl_DrawBuffersATI(VALUE obj,VALUE arg1)
{
	GLsizei size;
	GLenum *buffers;
	LOAD_GL_FUNC(glDrawBuffersATI,"GL_ATI_draw_buffers")
	Check_Type(arg1,T_ARRAY); 
	size = RARRAY(arg1)->len;
	buffers = ALLOC_N(GLenum,size);
	ary2cuint(arg1,buffers,size);
	fptr_glDrawBuffersATI(size,buffers);
	xfree(buffers);
	CHECK_GLERROR
	return Qnil;
}

void gl_init_functions_ext_ati(VALUE module)
{
/* #277 GL_ATI_draw_buffers */
	rb_define_module_function(module, "glDrawBuffersATI", gl_DrawBuffersATI, 1);
}
