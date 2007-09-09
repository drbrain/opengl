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

/* #5 GL_ARB_MULTISAMPLE */
static void (APIENTRY * fptr_glSampleCoverageARB)(GLclampf,GLboolean);
static VALUE gl_SampleCoverageARB(VALUE obj,VALUE arg1,VALUE arg2)
{
	LOAD_GL_EXT_FUNC(glSampleCoverageARB,"GL_ARB_multisample")
	fptr_glSampleCoverageARB((GLclampf)NUM2DBL(arg1),(GLboolean)NUM2INT(arg2));
	return Qnil;
}

void gl_init_functions_ext_arb(VALUE module)
{
	rb_define_module_function(module, "glSampleCoverageARB", gl_SampleCoverageARB, 2);
}
