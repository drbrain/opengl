/*
 * Copyright (C) 2013 Blaž Hrastnik <speed.the.bboy@gmail.com>
 *
 * This program is distributed under the terms of the MIT license.
 * See the included COPYRIGHT file for the terms of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "common.h"

static VALUE
glut_InitContextVersion(obj,majorVersion,minorVersion)
VALUE obj,majorVersion,minorVersion;
{
	glutInitContextVersion(NUM2INT(majorVersion), NUM2INT(minorVersion));
	return Qnil;
}

static VALUE
glut_InitContextFlags(obj,flags)
VALUE obj,flags;
{
	glutInitContextFlags(NUM2INT(flags));
	return Qnil;
}

static VALUE
glut_InitContextProfile(obj,profile)
VALUE obj,profile;
{
	glutInitContextProfile(NUM2INT(profile));
	return Qnil;
}

void Init_glut_ext() {
	VALUE mGlut = rb_path2class("Glut");

	rb_define_module_function(mGlut, "glutInitContextVersion", glut_InitContextVersion, 2);
	rb_define_module_function(mGlut, "glutInitContextFlags", glut_InitContextFlags, 1);
	rb_define_module_function(mGlut, "glutInitContextFlags", glut_InitContextFlags, 1);

	/* Context-related flags */
	rb_define_const(mGlut, "GLUT_INIT_MAJOR_VERSION", INT2NUM(GLUT_INIT_MAJOR_VERSION));
	rb_define_const(mGlut, "GLUT_INIT_MINOR_VERSION", INT2NUM(GLUT_INIT_MINOR_VERSION));
	rb_define_const(mGlut, "GLUT_INIT_FLAGS", INT2NUM(GLUT_INIT_FLAGS));
	rb_define_const(mGlut, "GLUT_INIT_PROFILE", INT2NUM(GLUT_INIT_PROFILE));

	/* Flags for glutInitContextFlags */
	rb_define_const(mGlut, "GLUT_FORWARD_COMPATIBLE", INT2NUM(GLUT_FORWARD_COMPATIBLE));
	rb_define_const(mGlut, "GLUT_DEBUG", INT2NUM(GLUT_DEBUG));

	/* Flags for glutInitContextProfile */
	rb_define_const(mGlut, "GLUT_CORE_PROFILE", INT2NUM(GLUT_CORE_PROFILE));
	rb_define_const(mGlut, "GLUT_COMPATIBILITY_PROFILE", INT2NUM(GLUT_COMPATIBILITY_PROFILE));

	
}
