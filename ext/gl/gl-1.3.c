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

/* OpenGL 1.3 functions */

GL_FUNC_LOAD_1(ActiveTexture,GLvoid, GLenum, "1.3")
GL_FUNC_LOAD_1(ClientActiveTexture,GLvoid, GLenum, "1.3")
GL_FUNC_LOAD_2(MultiTexCoord1d,GLvoid, GLenum,GLdouble, "1.3")
GL_FUNC_LOAD_2(MultiTexCoord1f,GLvoid, GLenum,GLfloat, "1.3")
GL_FUNC_LOAD_2(MultiTexCoord1i,GLvoid, GLenum,GLint, "1.3")
GL_FUNC_LOAD_2(MultiTexCoord1s,GLvoid, GLenum,GLshort, "1.3")
GL_FUNC_LOAD_3(MultiTexCoord2d,GLvoid, GLenum,GLdouble,GLdouble, "1.3")
GL_FUNC_LOAD_3(MultiTexCoord2f,GLvoid, GLenum,GLfloat,GLfloat, "1.3")
GL_FUNC_LOAD_3(MultiTexCoord2i,GLvoid, GLenum,GLint,GLint, "1.3")
GL_FUNC_LOAD_3(MultiTexCoord2s,GLvoid, GLenum,GLshort,GLshort, "1.3")
GL_FUNC_LOAD_4(MultiTexCoord3d,GLvoid, GLenum,GLdouble,GLdouble,GLdouble, "1.3")
GL_FUNC_LOAD_4(MultiTexCoord3f,GLvoid, GLenum,GLfloat,GLfloat,GLfloat, "1.3")
GL_FUNC_LOAD_4(MultiTexCoord3i,GLvoid, GLenum,GLint,GLint,GLint, "1.3")
GL_FUNC_LOAD_4(MultiTexCoord3s,GLvoid, GLenum,GLshort,GLshort,GLshort, "1.3")
GL_FUNC_LOAD_5(MultiTexCoord4d,GLvoid, GLenum,GLdouble,GLdouble,GLdouble,GLdouble, "1.3")
GL_FUNC_LOAD_5(MultiTexCoord4f,GLvoid, GLenum,GLfloat,GLfloat,GLfloat,GLfloat, "1.3")
GL_FUNC_LOAD_5(MultiTexCoord4i,GLvoid, GLenum,GLint,GLint,GLint,GLint, "1.3")
GL_FUNC_LOAD_5(MultiTexCoord4s,GLvoid, GLenum,GLshort,GLshort,GLshort,GLshort, "1.3")
GL_FUNC_LOAD_2(SampleCoverage,GLvoid, GLclampf,GLboolean, "1.3")

#define GLMULTITEXCOORD_VFUNC(_type_) \
static VALUE \
gl_MultiTexCoord##_type_##v(argc,argv,obj) \
int argc; \
VALUE *argv; \
VALUE obj; \
{ \
	int num; \
	VALUE args[5]; \
	RArray *ary; \
	switch (num = rb_scan_args(argc, argv, "23", &args[0], &args[1], &args[2], &args[3],&args[4])) { \
	case 2: \
		if (TYPE(args[1]) == T_ARRAY) { \
		ary = RARRAY(args[1]); \
		switch (RARRAY_LEN(ary)) { \
			case 1: \
			gl_MultiTexCoord1##_type_(obj,args[0],RARRAY_PTR(ary)[0]); \
			break; \
			case 2: \
			gl_MultiTexCoord2##_type_(obj,args[0],RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1]); \
			break; \
			case 3: \
			gl_MultiTexCoord3##_type_(obj,args[0],RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2]); \
			break; \
			case 4: \
			gl_MultiTexCoord4##_type_(obj,args[0],RARRAY_PTR(ary)[0],RARRAY_PTR(ary)[1],RARRAY_PTR(ary)[2],RARRAY_PTR(ary)[3]); \
			break; \
			default: \
			rb_raise(rb_eArgError, "array length:%d", num); \
		} \
		} \
		else {	\
			gl_MultiTexCoord1##_type_(obj,args[0], args[1]); \
			break; \
		} \
		break; \
	case 3: \
		gl_MultiTexCoord2##_type_(obj,args[0], args[1], args[2]); \
		break; \
	case 4: \
		gl_MultiTexCoord3##_type_(obj,args[0], args[1], args[2], args[3]); \
		break; \
	case 5: \
		gl_MultiTexCoord4##_type_(obj,args[0], args[1], args[2], args[3], args[4]); \
		break; \
	default: \
		rb_raise(rb_eArgError, "too many arguments"); \
		break; \
	} \
	return Qnil; \
}

GLMULTITEXCOORD_VFUNC(d)
GLMULTITEXCOORD_VFUNC(f)
GLMULTITEXCOORD_VFUNC(i)
GLMULTITEXCOORD_VFUNC(s)
#undef GLTEXCOORD_VFUNC

#define TRANSPOSEMATRIX_FUNC(_name_,_type_) \
static void (APIENTRY * fptr_gl##_name_)(const _type_[]); \
static VALUE \
gl_##_name_(obj,arg1) \
VALUE obj,arg1; \
{ \
	_type_ m[4*4]; \
	LOAD_GL_FUNC(gl##_name_,"1.3") \
	ary2cmat##_type_(arg1, m, 4, 4); \
	fptr_gl##_name_(m); \
	CHECK_GLERROR \
	return Qnil; \
}

TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixf,float)
TRANSPOSEMATRIX_FUNC(LoadTransposeMatrixd,double)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixf,float)
TRANSPOSEMATRIX_FUNC(MultTransposeMatrixd,double)

#undef TRANSPOSEMATRIX_FUNC

static void (APIENTRY * fptr_glCompressedTexImage3D)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLsizei,GLint,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexImage3D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	internalformat = (GLenum)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	height = (GLsizei)NUM2UINT(arg5);
	depth = (GLsizei)NUM2UINT(arg6);
	border = (GLint)NUM2INT(arg7);
	imagesize = (GLsizei)NUM2UINT(arg8);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imagesize,(GLvoid *)NUM2LONG(arg9));
	} else {
		if (TYPE(arg9) == T_STRING || TYPE(arg9) == T_ARRAY) {
			VALUE data;
			data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg9);
			if (RSTRING_LEN(data) < imagesize)
				rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
			pixels = RSTRING_PTR(data);
		} else if (NIL_P(arg9)) {
			pixels = NULL;
		} else {
			Check_Type(arg9,T_STRING); /* force exception */
			return Qnil;
		}
		fptr_glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCompressedTexImage2D)(GLenum,GLint,GLenum,GLsizei,GLsizei,GLint,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8;
{
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexImage2D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	internalformat = (GLenum)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	height = (GLsizei)NUM2UINT(arg5);
	border = (GLint)NUM2INT(arg6);
	imagesize = (GLsizei)NUM2UINT(arg7);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexImage2D(target,level,internalformat,width,height,border,imagesize,(GLvoid *)NUM2LONG(arg8));
	} else {
		if (TYPE(arg8) == T_STRING || TYPE(arg8) == T_ARRAY) {
			VALUE data;
			data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg8);
			if (RSTRING_LEN(data) < imagesize)
				rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
			pixels = RSTRING_PTR(data);
		} else if (NIL_P(arg8)) {
			pixels = NULL;
		} else {
			Check_Type(arg8,T_STRING); /* force exception */
			return Qnil;
		}
		fptr_glCompressedTexImage2D(target,level,internalformat,width,height,border,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCompressedTexImage1D)(GLenum,GLint,GLenum,GLsizei,GLint,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
	GLenum target;
	GLint level;
	GLenum internalformat;
	GLsizei width;
	GLint border;
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexImage1D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	internalformat = (GLenum)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	border = (GLint)NUM2INT(arg5);
	imagesize = (GLsizei)NUM2UINT(arg6);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexImage1D(target,level,internalformat,width,border,imagesize,(GLvoid *)NUM2LONG(arg7));
	} else {
		if (TYPE(arg7) == T_STRING || TYPE(arg7) == T_ARRAY) {
			VALUE data;
			data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg7);
			if (RSTRING_LEN(data) < imagesize)
				rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
			pixels = RSTRING_PTR(data);
		} else if (NIL_P(arg7)) {
			pixels = NULL;
		} else {
			Check_Type(arg7,T_STRING); /* force exception */
			return Qnil;
		}
		fptr_glCompressedTexImage1D(target,level,internalformat,width,border,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCompressedTexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11)
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
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexSubImage3D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	yoffset = (GLint)NUM2INT(arg4);
	zoffset = (GLint)NUM2INT(arg5);
	width = (GLsizei)NUM2UINT(arg6);
	height = (GLsizei)NUM2UINT(arg7);
	depth = (GLsizei)NUM2UINT(arg8);
	format = (GLenum)NUM2INT(arg9);
	imagesize = (GLsizei)NUM2UINT(arg10);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imagesize,(GLvoid *)NUM2LONG(arg11));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg11);
		if (RSTRING_LEN(data) < imagesize)
			rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
		pixels = RSTRING_PTR(data);

		fptr_glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCompressedTexSubImage2D)(GLenum,GLint,GLint,GLint,GLsizei,GLsizei,GLenum,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexSubImage2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexSubImage2D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	yoffset = (GLint)NUM2INT(arg4);
	width = (GLsizei)NUM2UINT(arg5);
	height = (GLsizei)NUM2UINT(arg6);
	format = (GLenum)NUM2INT(arg7);
	imagesize = (GLsizei)NUM2UINT(arg8);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imagesize,(GLvoid *)NUM2LONG(arg9));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg9);
		if (RSTRING_LEN(data) < imagesize)
			rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
		pixels = RSTRING_PTR(data);
		fptr_glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCompressedTexSubImage1D)(GLenum,GLint,GLint,GLsizei,GLenum,GLsizei,GLvoid*);
static VALUE
gl_CompressedTexSubImage1D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
	GLenum target;
	GLint level;
	GLint xoffset;
	GLsizei width;
	GLenum format;
	GLsizei imagesize;
	GLvoid *pixels;
	LOAD_GL_FUNC(glCompressedTexSubImage1D,"1.3")
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	format = (GLenum)NUM2INT(arg5);
	imagesize = (GLsizei)NUM2UINT(arg6);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glCompressedTexSubImage1D(target,level,xoffset,width,format,imagesize,(GLvoid *)NUM2LONG(arg7));
	} else {
		VALUE data;
		data = pack_array_or_pass_string(GL_UNSIGNED_BYTE,arg7);
		if (RSTRING_LEN(data) < imagesize)
			rb_raise(rb_eArgError, "string length:%li",RSTRING_LEN(data));
		pixels = RSTRING_PTR(data);
		fptr_glCompressedTexSubImage1D(target,level,xoffset,width,format,imagesize,pixels);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetCompressedTexImage)(GLenum,GLint,GLvoid*);
static VALUE
gl_GetCompressedTexImage(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum target;
	GLint lod;
	GLsizei size = 0;
	VALUE data;
	VALUE args[3];
	int numargs;
	LOAD_GL_FUNC(glGetCompressedTexImage,"1.3")
	numargs = rb_scan_args(argc, argv, "21", &args[0], &args[1], &args[2]);
	target = (GLenum)NUM2INT(args[0]);
	lod = (GLenum)NUM2INT(args[1]);
	switch(numargs) {
		default:
		case 2:
			if (CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");
			glGetTexLevelParameteriv(target,lod,GL_TEXTURE_COMPRESSED_IMAGE_SIZE,&size); /* 1.0 function */
			CHECK_GLERROR
			data = allocate_buffer_with_string(size);
			fptr_glGetCompressedTexImage(target,lod,(GLvoid*)RSTRING_PTR(data));
			CHECK_GLERROR
			return data;
		case 3:
			fptr_glGetCompressedTexImage(target,lod,(GLvoid*)NUM2LONG(args[2]));
			CHECK_GLERROR
			return Qnil;	
	}
}

void gl_init_functions_1_3(VALUE module)
{
	rb_define_module_function(module, "glActiveTexture", gl_ActiveTexture, 1);
	rb_define_module_function(module, "glClientActiveTexture", gl_ClientActiveTexture, 1);
	rb_define_module_function(module, "glMultiTexCoord1d", gl_MultiTexCoord1d, 2);
	rb_define_module_function(module, "glMultiTexCoord1f", gl_MultiTexCoord1f, 2);
	rb_define_module_function(module, "glMultiTexCoord1i", gl_MultiTexCoord1i, 2);
	rb_define_module_function(module, "glMultiTexCoord1s", gl_MultiTexCoord1s, 2);
	rb_define_module_function(module, "glMultiTexCoord2d", gl_MultiTexCoord2d, 3);
	rb_define_module_function(module, "glMultiTexCoord2f", gl_MultiTexCoord2f, 3);
	rb_define_module_function(module, "glMultiTexCoord2i", gl_MultiTexCoord2i, 3);
	rb_define_module_function(module, "glMultiTexCoord2s", gl_MultiTexCoord2s, 3);
	rb_define_module_function(module, "glMultiTexCoord3d", gl_MultiTexCoord3d, 4);
	rb_define_module_function(module, "glMultiTexCoord3f", gl_MultiTexCoord3f, 4);
	rb_define_module_function(module, "glMultiTexCoord3i", gl_MultiTexCoord3i, 4);
	rb_define_module_function(module, "glMultiTexCoord3s", gl_MultiTexCoord3s, 4);
	rb_define_module_function(module, "glMultiTexCoord4d", gl_MultiTexCoord4d, 5);
	rb_define_module_function(module, "glMultiTexCoord4f", gl_MultiTexCoord4f, 5);
	rb_define_module_function(module, "glMultiTexCoord4i", gl_MultiTexCoord4i, 5);
	rb_define_module_function(module, "glMultiTexCoord4s", gl_MultiTexCoord4s, 5);
	rb_define_module_function(module, "glLoadTransposeMatrixf", gl_LoadTransposeMatrixf, 1);
	rb_define_module_function(module, "glLoadTransposeMatrixd", gl_LoadTransposeMatrixd, 1);
	rb_define_module_function(module, "glMultTransposeMatrixf", gl_MultTransposeMatrixf, 1);
	rb_define_module_function(module, "glMultTransposeMatrixd", gl_MultTransposeMatrixd, 1);
	rb_define_module_function(module, "glSampleCoverage", gl_SampleCoverage, 2);
	rb_define_module_function(module, "glCompressedTexImage3D", gl_CompressedTexImage3D, 9);
	rb_define_module_function(module, "glCompressedTexImage2D", gl_CompressedTexImage2D, 8);
	rb_define_module_function(module, "glCompressedTexImage1D", gl_CompressedTexImage1D, 7);
	rb_define_module_function(module, "glCompressedTexSubImage3D", gl_CompressedTexSubImage3D, 11);
	rb_define_module_function(module, "glCompressedTexSubImage2D", gl_CompressedTexSubImage2D, 9);
	rb_define_module_function(module, "glCompressedTexSubImage1D", gl_CompressedTexSubImage1D, 7);
	rb_define_module_function(module, "glGetCompressedTexImage", gl_GetCompressedTexImage, -1);

	/* Additional functions */

	rb_define_module_function(module, "glMultiTexCoord", gl_MultiTexCoorddv, -1);
	rb_define_module_function(module, "glMultiTexCoord1dv", gl_MultiTexCoorddv, -1);
	rb_define_module_function(module, "glMultiTexCoord1fv", gl_MultiTexCoordfv, -1);
	rb_define_module_function(module, "glMultiTexCoord1iv", gl_MultiTexCoordiv, -1);
	rb_define_module_function(module, "glMultiTexCoord1sv", gl_MultiTexCoordsv, -1);
	rb_define_module_function(module, "glMultiTexCoord2dv", gl_MultiTexCoorddv, -1);
	rb_define_module_function(module, "glMultiTexCoord2fv", gl_MultiTexCoordfv, -1);
	rb_define_module_function(module, "glMultiTexCoord2iv", gl_MultiTexCoordiv, -1);
	rb_define_module_function(module, "glMultiTexCoord2sv", gl_MultiTexCoordsv, -1);
	rb_define_module_function(module, "glMultiTexCoord3dv", gl_MultiTexCoorddv, -1);
	rb_define_module_function(module, "glMultiTexCoord3fv", gl_MultiTexCoordfv, -1);
	rb_define_module_function(module, "glMultiTexCoord3iv", gl_MultiTexCoordiv, -1);
	rb_define_module_function(module, "glMultiTexCoord3sv", gl_MultiTexCoordsv, -1);
	rb_define_module_function(module, "glMultiTexCoord4dv", gl_MultiTexCoorddv, -1);
	rb_define_module_function(module, "glMultiTexCoord4fv", gl_MultiTexCoordfv, -1);
	rb_define_module_function(module, "glMultiTexCoord4iv", gl_MultiTexCoordiv, -1);
	rb_define_module_function(module, "glMultiTexCoord4sv", gl_MultiTexCoordsv, -1);
}
