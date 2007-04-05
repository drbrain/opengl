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

#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

static VALUE module;

void gl_init_enums(VALUE);
void gl_init_functions_1_0__1_1(VALUE);
void gl_init_functions_1_2(VALUE);
void gl_init_functions_1_3(VALUE);
void gl_init_functions_1_4(VALUE);
void gl_init_functions_1_5(VALUE);
void gl_init_functions_2_0(VALUE);
void gl_init_functions_2_1(VALUE);

static VALUE
IsFunctionAvailable(obj,arg1)
VALUE obj,arg1;
{
	GLvoid *ret;
	Check_Type(arg1, T_STRING);
	ret = load_gl_function(RSTRING(arg1)->ptr,0); /* won't raise */
	if (ret==NULL)
		return Qfalse;
	else
		return Qtrue;
}

DLLEXPORT void Init_gl()
{
    module = rb_define_module("Gl");
	gl_init_enums(module);
	gl_init_functions_1_0__1_1(module);
	gl_init_functions_1_2(module);
	gl_init_functions_1_3(module);
	gl_init_functions_1_4(module);
	gl_init_functions_1_5(module);
	gl_init_functions_2_0(module);
	gl_init_functions_2_1(module);

	rb_define_module_function(module, "is_available?", IsFunctionAvailable, 1);
}
