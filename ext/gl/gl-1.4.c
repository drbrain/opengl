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

/* OpenGL 1.4 functions */
GL_SIMPLE_FUNC_LOAD(BlendFuncSeparate,4,GLenum,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(FogCoordf,1,GLfloat,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(FogCoordd,1,GLdouble,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3b,3,GLbyte,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3d,3,GLdouble,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3f,3,GLfloat,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3i,3,GLint,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3s,3,GLshort,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3ub,3,GLubyte,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3ui,3,GLuint,NUM2UINT,"1.4")
GL_SIMPLE_FUNC_LOAD(SecondaryColor3us,3,GLushort,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos2d,2,GLdouble,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos2f,2,GLfloat,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos2i,2,GLint,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos2s,2,GLshort,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos3d,3,GLdouble,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos3f,3,GLfloat,NUM2DBL,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos3i,3,GLint,NUM2INT,"1.4")
GL_SIMPLE_FUNC_LOAD(WindowPos3s,3,GLshort,NUM2INT,"1.4")

static void (APIENTRY * fptr_glFogCoordfv)(GLfloat *);
static VALUE
gl_FogCoordfv(obj,arg1)
VALUE obj,arg1;
{
	GLfloat coord;
	LOAD_GL_FUNC(glFogCoordfv,"1.4")
	Check_Type(arg1,T_ARRAY);
	ary2cflt(arg1,&coord,1);
	fptr_glFogCoordfv(&coord);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glFogCoorddv)(GLdouble *);
static VALUE
gl_FogCoorddv(obj,arg1)
VALUE obj,arg1;
{
	GLdouble coord;
	LOAD_GL_FUNC(glFogCoorddv,"1.4")
	Check_Type(arg1,T_ARRAY);
	ary2cdbl(arg1,&coord,1);
	fptr_glFogCoorddv(&coord);
	CHECK_GLERROR
	return Qnil;
}

extern VALUE g_FogCoord_ptr;
static void (APIENTRY * fptr_glFogCoordPointer)(GLenum,GLsizei,const GLvoid *);
static VALUE
gl_FogCoordPointer(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum type;
	GLsizei stride;
	LOAD_GL_FUNC(glFogCoordPointer,"1.4")
	type = (GLenum)NUM2INT(arg1);
	stride = (GLsizei)NUM2UINT(arg2);
	if (CheckBufferBinding(GL_ARRAY_BUFFER_BINDING)) {
		g_FogCoord_ptr = arg3;
		fptr_glFogCoordPointer(type, stride, (const GLvoid*)NUM2INT(arg3));
	} else {
		Check_Type(arg3, T_STRING);
		rb_str_freeze(arg3);
		g_FogCoord_ptr = arg3;
		fptr_glFogCoordPointer(type, stride, (const GLvoid*)RSTRING(arg3)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glMultiDrawArrays)(GLenum,GLint*,GLsizei*,GLsizei);
static VALUE
gl_MultiDrawArrays(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum mode;
	GLint *ary1;
	GLsizei *ary2;
  int len1,len2;
	LOAD_GL_FUNC(glMultiDrawArrays,"1.4")
  len1 = RARRAY(arg2)->len;
  len2 = RARRAY(arg3)->len;
	if (len1!=len2)
			rb_raise(rb_eArgError, "Passed arrays must have same length");
	mode = (GLenum)NUM2INT(arg1);
	ary1 = ALLOC_N(GLint,len1);
	ary2 = ALLOC_N(GLsizei,len2);
	ary2cint(arg2,ary1,len1);
	ary2cint(arg3,ary2,len2);
	fptr_glMultiDrawArrays(mode,ary1,ary2,len1);
	xfree(ary1);
	xfree(ary2);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glMultiDrawElements)(GLenum,const GLsizei *,GLenum,GLvoid **,GLsizei);
static VALUE
gl_MultiDrawElements(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum mode;
	GLenum type;
	GLsizei *counts;
	GLvoid **indices;
	GLint size;
	RArray *ary;
	int i;
	VALUE args[4];
	LOAD_GL_FUNC(glMultiDrawElements,"1.4")
	switch (rb_scan_args(argc, argv, "31", &args[0], &args[1], &args[2],&args[3])) {
		default:
		case 3:
			if (CheckBufferBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Element array buffer bound, but offsets array missing");
			mode = (GLenum)NUM2INT(args[0]);
			type = (GLenum)NUM2INT(args[1]);
			Check_Type(args[2],T_ARRAY);
			ary = RARRAY(args[2]);
			size = ary->len;
			counts = ALLOC_N(GLsizei,size);
			indices = ALLOC_N(GLvoid*,size);
			for (i=0;i<size;i++) {
				indices[i] = RSTRING(ary->ptr[i])->ptr;
				counts[i] = RSTRING(ary->ptr[i])->len;
			}
			fptr_glMultiDrawElements(mode,counts,type,indices,size);
			xfree(counts);
			xfree(indices);
			break;
		case 4:
			if (!CheckBufferBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Element array buffer not bound");
			mode = (GLenum)NUM2INT(args[0]);
			type = (GLenum)NUM2INT(args[1]);
			Check_Type(args[2],T_ARRAY);
			Check_Type(args[3],T_ARRAY);
			if (RARRAY(args[2])->len != RARRAY(args[3])->len)
				rb_raise(rb_eArgError, "Count and indices offset array must have same length");

			size = RARRAY(args[2])->len;

			counts = ALLOC_N(GLsizei,size);
			indices = ALLOC_N(GLvoid*,size);
			for (i=0;i<size;i++) {
				counts[i] = NUM2INT(rb_ary_entry(args[2],i));
				indices[i] = (GLvoid *) NUM2INT(rb_ary_entry(args[3],i));
			}
			fptr_glMultiDrawElements(mode,counts,type,indices,size);
			xfree(counts);
			xfree(indices);
			break;
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glPointParameterf)(GLenum,GLfloat);
static VALUE
gl_PointParameterf(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum pname;
	GLfloat param;
	LOAD_GL_FUNC(glPointParameterf,"1.4")
	pname = (GLenum)NUM2INT(arg1);
	param = (GLfloat)NUM2INT(arg2);
	fptr_glPointParameterf(pname,param);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glPointParameterfv)(GLenum,GLfloat *);
static VALUE
gl_PointParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum pname;
	GLfloat params[3] = {0.0,0.0,0.0};
	GLint size;
	LOAD_GL_FUNC(glPointParameterfv,"1.4")
	pname = (GLenum)NUM2INT(arg1);
	Check_Type(arg2,T_ARRAY);
	if (pname==GL_POINT_DISTANCE_ATTENUATION)
		size = 3;
	else
		size = 1;
	ary2cflt(arg2,params,size);
	fptr_glPointParameterfv(pname,params);	
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glPointParameteri)(GLenum,GLint);
static VALUE
gl_PointParameteri(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum pname;
	GLint param;
	LOAD_GL_FUNC(glPointParameteri,"1.4")
	pname = (GLenum)NUM2INT(arg1);
	param = (GLint)NUM2INT(arg2);
	fptr_glPointParameteri(pname,param);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glPointParameteriv)(GLenum,GLint *);
static VALUE
gl_PointParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum pname;
	GLint params[3] = {0.0,0.0,0.0};
	GLint size;
	LOAD_GL_FUNC(glPointParameteriv,"1.4")
	pname = (GLenum)NUM2INT(arg1);
	Check_Type(arg2,T_ARRAY);
	if (pname==GL_POINT_DISTANCE_ATTENUATION)
		size = 3;
	else
		size = 1;
	ary2cint(arg2,params,size);
	fptr_glPointParameteriv(pname,params);	
	CHECK_GLERROR
	return Qnil;
}

#define GLSECONDARYCOLOR_VFUNC(_name_,_type_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(_type_ *); \
VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	_type_ cary[3] = {0,0,0}; \
	LOAD_GL_FUNC(gl##_name_,"1.4") \
	Check_Type(arg1,T_ARRAY); \
	_conv_(arg1,cary,3); \
	fptr_gl##_name_(cary); \
	CHECK_GLERROR \
	return Qnil; \
}

GLSECONDARYCOLOR_VFUNC(SecondaryColor3bv,GLbyte,ary2cbyte)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3dv,GLdouble,ary2cdbl)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3fv,GLfloat,ary2cflt)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3iv,GLint,ary2cint)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3sv,GLshort,ary2cshort)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3uiv,GLuint,ary2cuint)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3ubv,GLubyte,ary2cubyte)
GLSECONDARYCOLOR_VFUNC(SecondaryColor3usv,GLushort,ary2cushort)
#undef GLSECONDARYCOLOR_VFUNC

extern VALUE g_SecondaryColor_ptr;
static void (APIENTRY * fptr_glSecondaryColorPointer)(GLint,GLenum,GLsizei,const GLvoid *);
static VALUE
gl_SecondaryColorPointer(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLint size;
	GLenum type;
	GLsizei stride;
	LOAD_GL_FUNC(glSecondaryColorPointer,"1.4")
	size = (GLint)NUM2INT(arg1);
	type = (GLenum)NUM2INT(arg2);
	stride = (GLsizei)NUM2UINT(arg3);
	if (CheckBufferBinding(GL_ARRAY_BUFFER_BINDING)) {
		g_SecondaryColor_ptr = arg4;
		fptr_glSecondaryColorPointer(size,type, stride, (const GLvoid*)NUM2INT(arg4));
	} else {
		Check_Type(arg4, T_STRING);
		rb_str_freeze(arg4);
		g_SecondaryColor_ptr = arg4;
		fptr_glSecondaryColorPointer(size,type, stride, (const GLvoid*)RSTRING(arg4)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

#define GLWINDOWPOS_VFUNC(_name_,_type_,_size_,_conv_) \
static void (APIENTRY * fptr_gl##_name_)(_type_ *); \
VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	_type_ cary[_size_] = {TYPELIST##_size_(0)}; \
	LOAD_GL_FUNC(gl##_name_,"1.4") \
	Check_Type(arg1,T_ARRAY); \
	_conv_(arg1,cary,_size_); \
	fptr_gl##_name_(cary); \
	CHECK_GLERROR \
	return Qnil; \
}

GLWINDOWPOS_VFUNC(WindowPos2dv,GLdouble,2,ary2cdbl)
GLWINDOWPOS_VFUNC(WindowPos2fv,GLfloat,2,ary2cflt)
GLWINDOWPOS_VFUNC(WindowPos2iv,GLint,2,ary2cint)
GLWINDOWPOS_VFUNC(WindowPos2sv,GLshort,2,ary2cshort)
GLWINDOWPOS_VFUNC(WindowPos3dv,GLdouble,3,ary2cdbl)
GLWINDOWPOS_VFUNC(WindowPos3fv,GLfloat,3,ary2cflt)
GLWINDOWPOS_VFUNC(WindowPos3iv,GLint,3,ary2cint)
GLWINDOWPOS_VFUNC(WindowPos3sv,GLshort,3,ary2cshort)
#undef GLWINDOWPOS_VFUNC


void gl_init_functions_1_4(VALUE module)
{
	rb_define_module_function(module, "glBlendFuncSeparate", gl_BlendFuncSeparate, 4);
	rb_define_module_function(module, "glFogCoordf", gl_FogCoordf, 1);
	rb_define_module_function(module, "glFogCoordfv", gl_FogCoordfv, 1);
	rb_define_module_function(module, "glFogCoordd", gl_FogCoordd, 1);
	rb_define_module_function(module, "glFogCoorddv", gl_FogCoorddv, 1);
	rb_define_module_function(module, "glFogCoordPointer", gl_FogCoordPointer, 3);
	rb_define_module_function(module, "glMultiDrawArrays", gl_MultiDrawArrays, 3);
	rb_define_module_function(module, "glMultiDrawElements", gl_MultiDrawElements, -1);
	rb_define_module_function(module, "glPointParameterf", gl_PointParameterf, 2);
	rb_define_module_function(module, "glPointParameterfv", gl_PointParameterfv, 2);
	rb_define_module_function(module, "glPointParameteri", gl_PointParameteri, 2);
	rb_define_module_function(module, "glPointParameteriv", gl_PointParameteriv, 2);
	rb_define_module_function(module, "glSecondaryColor3b", gl_SecondaryColor3b, 3);
	rb_define_module_function(module, "glSecondaryColor3d", gl_SecondaryColor3d, 3);
	rb_define_module_function(module, "glSecondaryColor3f", gl_SecondaryColor3f, 3);
	rb_define_module_function(module, "glSecondaryColor3i", gl_SecondaryColor3i, 3);
	rb_define_module_function(module, "glSecondaryColor3s", gl_SecondaryColor3s, 3);
	rb_define_module_function(module, "glSecondaryColor3ub", gl_SecondaryColor3ub, 3);
	rb_define_module_function(module, "glSecondaryColor3ui", gl_SecondaryColor3ui, 3);
	rb_define_module_function(module, "glSecondaryColor3us", gl_SecondaryColor3us, 3);
	rb_define_module_function(module, "glSecondaryColor3bv", gl_SecondaryColor3bv, 1);
	rb_define_module_function(module, "glSecondaryColor3dv", gl_SecondaryColor3dv, 1);
	rb_define_module_function(module, "glSecondaryColor3fv", gl_SecondaryColor3fv, 1);
	rb_define_module_function(module, "glSecondaryColor3iv", gl_SecondaryColor3iv, 1);
	rb_define_module_function(module, "glSecondaryColor3sv", gl_SecondaryColor3sv, 1);
	rb_define_module_function(module, "glSecondaryColor3ubv", gl_SecondaryColor3ubv, 1);
	rb_define_module_function(module, "glSecondaryColor3uiv", gl_SecondaryColor3uiv, 1);
	rb_define_module_function(module, "glSecondaryColor3usv", gl_SecondaryColor3usv, 1);
	rb_define_module_function(module, "glSecondaryColorPointer", gl_SecondaryColorPointer, 4);
	rb_define_module_function(module, "glWindowPos2d", gl_WindowPos2d, 2);
	rb_define_module_function(module, "glWindowPos2f", gl_WindowPos2f, 2);
	rb_define_module_function(module, "glWindowPos2i", gl_WindowPos2i, 2);
	rb_define_module_function(module, "glWindowPos2s", gl_WindowPos2s, 2);
	rb_define_module_function(module, "glWindowPos3d", gl_WindowPos3d, 3);
	rb_define_module_function(module, "glWindowPos3f", gl_WindowPos3f, 3);
	rb_define_module_function(module, "glWindowPos3i", gl_WindowPos3i, 3);
	rb_define_module_function(module, "glWindowPos3s", gl_WindowPos3s, 3);
	rb_define_module_function(module, "glWindowPos2dv", gl_WindowPos2dv, 1);
	rb_define_module_function(module, "glWindowPos2fv", gl_WindowPos2fv, 1);
	rb_define_module_function(module, "glWindowPos2iv", gl_WindowPos2iv, 1);
	rb_define_module_function(module, "glWindowPos2sv", gl_WindowPos2sv, 1);
	rb_define_module_function(module, "glWindowPos3dv", gl_WindowPos3dv, 1);
	rb_define_module_function(module, "glWindowPos3fv", gl_WindowPos3fv, 1);
	rb_define_module_function(module, "glWindowPos3iv", gl_WindowPos3iv, 1);
	rb_define_module_function(module, "glWindowPos3sv", gl_WindowPos3sv, 1);
}
