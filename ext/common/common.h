/*
 * Last edit by previous maintainer:
 * 2000/01/06 16:37:43, kusano
 *
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
 * Copyright (C) 2007 James Adam <james@lazyatom.com>
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

#ifndef _COMMON_H_
#define _COMMON_H_

#include <ruby.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <mach-o/dyld.h>
#include <stdlib.h>
#include <string.h>
#elif defined WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "gl-types.h"
#include "gl-enums.h"
#include "glu-enums.h"
#include "gl-error.h"

#ifndef APIENTRY
#define APIENTRY
#endif

#ifndef CALLBACK
#define CALLBACK
#endif

#ifndef GLUTCALLBACK
#define GLUTCALLBACK
#endif

#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

/* */

extern VALUE inside_begin_end;

typedef struct RArray RArray;

extern VALUE cProc;

#define LOAD_GL_FUNC(_NAME_) \
if (fptr_##_NAME_==NULL) \
fptr_##_NAME_ = load_gl_function(#_NAME_, 1);

#define LOAD_GL_EXT_FUNC(_NAME_,_EXTNAME_) \
if (fptr_##_NAME_==NULL) {\
	if (CheckExtension(_EXTNAME_)==GL_FALSE) \
		rb_raise(rb_eNotImpError,"Extension %s is not available on this system",_EXTNAME_); \
	fptr_##_NAME_ = load_gl_function(#_NAME_, 1); \
}

#define FORCE_PIXEL_STORE_MODE \
	glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT); \
	glPixelStorei(GL_PACK_ALIGNMENT, 1); \
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0); \
	glPixelStorei(GL_PACK_SKIP_ROWS, 0); \
	glPixelStorei(GL_PACK_ROW_LENGTH, 0); \
	glPixelStorei(GL_PACK_SKIP_IMAGES, 0); \
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0); \
	if (CheckExtension("GL_SGIS_texture4D")) { \
		glPixelStorei(GL_PACK_SKIP_VOLUMES_SGIS, 0); \
		glPixelStorei(GL_PACK_IMAGE_DEPTH_SGIS, 0); \
	}

#define RESTORE_PIXEL_STORE_MODE \
	glPopClientAttrib();

GLboolean CheckExtension(const char *name);
GLint CheckBufferBinding(GLint buffer);

/* -------------------------------------------------------------------- */
#ifndef NUM2DBL
#define NUM2DBL(_val) num2double(_val) 

static inline double num2double( VALUE val )
{
    struct RFloat* flt;
    if (NIL_P(val)) return 0;
    flt = RFLOAT(f_float(0, val));
    return flt->value;
}
#endif

/* -------------------------------------------------------------------- */
#define ARY2INTEGRAL(_type_,_convert_) \
static inline int ary2c##_type_( arg, cary, maxlen ) \
VALUE arg; \
GL##_type_ cary[]; \
int maxlen; \
{ \
    int i; \
    struct RArray* ary; \
    VALUE entry; \
    ary = RARRAY(rb_Array(arg)); \
    if (maxlen < 1) \
        maxlen = ary->len; \
    else \
        maxlen = maxlen < ary->len ? maxlen : ary->len; \
    for (i=0; i < maxlen; i++) \
    { \
        entry = rb_ary_entry((VALUE)ary,i); \
        cary[i] = (GL##_type_)_convert_(entry); \
    } \
    return i; \
}

ARY2INTEGRAL(int,NUM2INT)
ARY2INTEGRAL(uint,NUM2UINT)
ARY2INTEGRAL(byte,NUM2INT)
ARY2INTEGRAL(ubyte,NUM2INT)
ARY2INTEGRAL(short,NUM2INT)
ARY2INTEGRAL(ushort,NUM2INT)
ARY2INTEGRAL(boolean,NUM2INT)
#undef ARY2INTEGRAL

/* -------------------------------------------------------------------- */
static inline int ary2cflt(arg, cary, maxlen)
VALUE arg;
float cary[];
int maxlen;
{
    int i;
    struct RArray* ary;
    ary = RARRAY(rb_Array(arg));
    if (maxlen < 1)
        maxlen = ary->len;
    else
        maxlen = maxlen < ary->len ? maxlen : ary->len;
    for (i=0; i < maxlen; i++)
        cary[i] = (float)NUM2DBL(rb_ary_entry((VALUE)ary,i));
    return i;
}

/* -------------------------------------------------------------------- */
static inline int ary2cdbl(arg, cary, maxlen)
VALUE arg;
double cary[];
int maxlen;
{
    int i;
    struct RArray* ary;
    ary = RARRAY(rb_Array(arg));
    if (maxlen < 1)
        maxlen = ary->len;
    else
        maxlen = maxlen < ary->len ? maxlen : ary->len;
    for (i=0; i < maxlen; i++)
        cary[i] = NUM2DBL(rb_ary_entry((VALUE)ary,i));
    return i;
}

/* -------------------------------------------------------------------- */
/* Array.flatten */
static inline void mary2ary(src, ary)
VALUE src;
VALUE ary;
{
    struct RArray* tmp_ary;
    int i;
    tmp_ary = RARRAY(rb_Array(src));
    for (i = 0; i < tmp_ary->len; i++)
    {
        if (TYPE(tmp_ary->ptr[i]) == T_ARRAY)
            mary2ary((VALUE)tmp_ary->ptr[i], ary);
        else
            rb_ary_push(ary, tmp_ary->ptr[i]);
    }
}

/* -------------------------------------------------------------------- */
/* converts either array or object responding to #to_a to C-style array */
#define ARY2CMAT(_type_) \
static inline void ary2cmat##_type_(rary, cary, cols, rows) \
VALUE rary; \
_type_ cary[]; \
int cols,rows; \
{ \
	int i; \
\
	rary = rb_Array(rary); \
	rary = rb_funcall(rary,rb_intern("flatten"),0); \
\
	if (RARRAY(rary)->len != cols*rows) \
		rb_raise(rb_eArgError, "passed array/matrix must have %i*%i elements",cols,rows); \
\
	for (i=0; i < cols*rows; i++) \
		cary[i] = (_type_) NUM2DBL(rb_ary_entry(rary,i)); \
}

ARY2CMAT(double)
ARY2CMAT(float)
#undef ARY2CMAT

/* -------------------------------------------------------------------- */

/* gets number of components for given format */
static inline int glformat_size(GLenum format)
{
	switch(format)
	{
		case GL_COLOR_INDEX:
		case GL_RED:
		case GL_GREEN:
		case GL_BLUE:
		case GL_ALPHA:
		case GL_RED_INTEGER_EXT:
		case GL_GREEN_INTEGER_EXT:
		case GL_BLUE_INTEGER_EXT:
		case GL_ALPHA_INTEGER_EXT:
		case GL_STENCIL_INDEX:
		case GL_DEPTH_COMPONENT:
		case GL_LUMINANCE:
		case GL_LUMINANCE_INTEGER_EXT:
			return 1;
		
		case GL_LUMINANCE_ALPHA:
		case GL_LUMINANCE_ALPHA_INTEGER_EXT:
		case GL_422_EXT:
		case GL_422_REV_EXT:
		case GL_422_AVERAGE_EXT:
		case GL_422_REV_AVERAGE_EXT:
		case GL_YCRCB_422_SGIX:
		case GL_YCBCR_422_APPLE:
		case GL_YCBCR_MESA:
		case GL_DEPTH_STENCIL_NV:
		case GL_HILO_NV:
		case GL_DSDT_NV:
		case GL_DUDV_ATI:
		case GL_DU8DV8_ATI:
		case GL_FORMAT_SUBSAMPLE_24_24_OML:
			return 2;
		
		case GL_RGB:
		case GL_RGB_INTEGER_EXT:
		case GL_BGR_EXT:
		case GL_BGR_INTEGER_EXT:
		case GL_YCRCB_444_SGIX:
		case GL_DSDT_MAG_NV:
		case GL_FORMAT_SUBSAMPLE_244_244_OML:
			return 3;
		
		case GL_RGBA:
		case GL_RGBA_INTEGER_EXT:
		case GL_BGRA_EXT:
		case GL_BGRA_INTEGER_EXT:
		case GL_ABGR_EXT:
		case GL_CMYK_EXT:
		case GL_DSDT_MAG_VIB_NV:
			return 4;

		case GL_CMYKA_EXT:
			return 5;

		/* GL spec permits passing direct format size instead of enum (now obsolete) */
		case 1:
		case 2:
		case 3:
		case 4:
			return format;

		default:
			rb_raise(rb_eArgError, "Unknown GL format enum %i",format);
			return -1; /* not reached */
	}
}

/* computes unit (pixel) size for given type and format */
static inline int gltype_glformat_unit_size(GLenum type,GLenum format)
{
	unsigned int format_size;
	
	format_size = glformat_size(format);
	
	switch(type)
	{
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
		case GL_BITMAP:
			return 1*format_size;

		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
		case GL_HALF_FLOAT_ARB:
			return 2*format_size;

		case GL_INT:
		case GL_UNSIGNED_INT:
		case GL_FLOAT:
			return 4*format_size;

		/* in packed formats all components are packed into/unpacked from single datatype,
		   so number of components(format_size) doesn't matter for total size calculation */
		case GL_UNSIGNED_BYTE_3_3_2:
		case GL_UNSIGNED_BYTE_2_3_3_REV:
			return 1;

		case GL_UNSIGNED_SHORT_5_6_5:
		case GL_UNSIGNED_SHORT_5_6_5_REV:
		case GL_UNSIGNED_SHORT_4_4_4_4:
		case GL_UNSIGNED_SHORT_4_4_4_4_REV:
		case GL_UNSIGNED_SHORT_5_5_5_1:
		case GL_UNSIGNED_SHORT_1_5_5_5_REV:
		case GL_UNSIGNED_SHORT_8_8_APPLE:
		case GL_UNSIGNED_SHORT_8_8_REV_APPLE:
			return 2;

		case GL_UNSIGNED_INT_8_8_8_8:
		case GL_UNSIGNED_INT_8_8_8_8_REV:
		case GL_UNSIGNED_INT_10_10_10_2:
		case GL_UNSIGNED_INT_2_10_10_10_REV:
		case GL_UNSIGNED_INT_24_8_NV:
		case GL_UNSIGNED_INT_S8_S8_8_8_NV:
		case GL_UNSIGNED_INT_8_8_S8_S8_REV_NV:
		case GL_UNSIGNED_INT_10F_11F_11F_REV_EXT:
		case GL_UNSIGNED_INT_5_9_9_9_REV_EXT:
		case GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV:
			return 4;
	
		default:
			rb_raise(rb_eArgError, "Unknown GL type enum %i",type);
			return -1; /* not reached */
	}
}

static inline int GetDataSize(GLenum type,GLenum format,int num)
{
	int size;
	int unit_size;

	unit_size = gltype_glformat_unit_size(type,format);
	
	if (type==GL_BITMAP)
		size = unit_size*(num/8); /* FIXME account for alignment */
	else
		size = unit_size*num;

	return size;
}

/* Checks if data size of 'data' string confirms to passed format values */
/* 'num' is number of elements, each of size 'format' * 'type' */
static inline void CheckDataSize(GLenum type,GLenum format,int num,VALUE data)
{
	int size;

	size = GetDataSize(type,format,num);
	
	if (RSTRING(data)->len < size)
		rb_raise(rb_eArgError, "Length of specified data doesn't correspond to format and type parameters passed. Calculated length: %i",size);
}

/* -------------------------------------------------------------------- */
static inline VALUE allocate_buffer_with_string( int size )
{
    return rb_str_new(NULL, size);
}

/* -------------------------------------------------------------------- */
static inline void *load_gl_function(const char *name,int raise) 
{
	void *func_ptr = NULL;

#if defined(__APPLE__)
	static const struct mach_header* library = NULL;
	char* symbolName;
	NSSymbol symbol;
	if (library == NULL)
		library = NSAddImage("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL",NSADDIMAGE_OPTION_RETURN_ON_ERROR);

	if (library == NULL)
		rb_raise(rb_eRuntimeError,"Can't load OpenGL library for dynamic loading");
		
	/*  prepend a '_' for the Unix C symbol mangling convention  */
	symbolName = ALLOC_N(char,strlen(name) + 2);
	symbolName[0] = '_';
	strcpy(symbolName+1, name);

	symbol = NSLookupSymbolInImage(library,symbolName,NSLOOKUPSYMBOLINIMAGE_OPTION_BIND | NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR);
	xfree(symbolName);

	if (symbol == NULL)
		func_ptr = NULL;
	else
		func_ptr = NSAddressOfSymbol(symbol);
#elif defined(WIN32) || defined(_WIN32)
	func_ptr = wglGetProcAddress((LPCSTR)name);
#elif defined(GLX_VERSION_1_4)
	func_ptr = glXGetProcAddress((const GLubyte *)name);
#else
	func_ptr = glXGetProcAddressARB((const GLubyte *)name);
#endif

	if (func_ptr == NULL && raise == 1)
		rb_raise(rb_eNotImpError,"Function %s is not available on this system",name);

	return func_ptr;
}

/* -------------------------------------------------------------------- */

/* Macroset for defining simple functions, i.e. functions that take n arguments of
  the same type and pass them to GL API function without any additional processing.

  Some checking is implicit in _conversion_ argument - e.g. NUM2INT makes sure that
  user is really passing type that can be converted to INT, otherwire raises. */

#define ARGLIST0 obj
#define ARGLIST1 obj,arg1
#define ARGLIST2 obj,arg1,arg2
#define ARGLIST3 obj,arg1,arg2,arg3
#define ARGLIST4 obj,arg1,arg2,arg3,arg4
#define ARGLIST5 obj,arg1,arg2,arg3,arg4,arg5
#define ARGLIST6 obj,arg1,arg2,arg3,arg4,arg5,arg6

#define TYPELIST0(_ctype_) void
#define TYPELIST1(_ctype_) _ctype_
#define TYPELIST2(_ctype_) _ctype_,_ctype_
#define TYPELIST3(_ctype_) _ctype_,_ctype_,_ctype_
#define TYPELIST4(_ctype_) _ctype_,_ctype_,_ctype_,_ctype_
#define TYPELIST5(_ctype_) _ctype_,_ctype_,_ctype_,_ctype_,_ctype_
#define TYPELIST6(_ctype_) _ctype_,_ctype_,_ctype_,_ctype_,_ctype_,_ctype_

#define FUNCPARAMS0(_ctype_,_conversion_) 
#define FUNCPARAMS1(_ctype_,_conversion_) (_ctype_)_conversion_(arg1)
#define FUNCPARAMS2(_ctype_,_conversion_) (_ctype_)_conversion_(arg1),(_ctype_)_conversion_(arg2)
#define FUNCPARAMS3(_ctype_,_conversion_) (_ctype_)_conversion_(arg1),(_ctype_)_conversion_(arg2),(_ctype_)_conversion_(arg3)
#define FUNCPARAMS4(_ctype_,_conversion_) (_ctype_)_conversion_(arg1),(_ctype_)_conversion_(arg2),(_ctype_)_conversion_(arg3),(_ctype_)_conversion_(arg4)
#define FUNCPARAMS5(_ctype_,_conversion_) (_ctype_)_conversion_(arg1),(_ctype_)_conversion_(arg2),(_ctype_)_conversion_(arg3),(_ctype_)_conversion_(arg4),(_ctype_)_conversion_(arg5)
#define FUNCPARAMS6(_ctype_,_conversion_) (_ctype_)_conversion_(arg1),(_ctype_)_conversion_(arg2),(_ctype_)_conversion_(arg3),(_ctype_)_conversion_(arg4),(_ctype_)_conversion_(arg5),(_ctype_)_conversion_(arg6)

#define GL_SIMPLE_FUNC(_name_,_numparams_,_ctype_,_conversion_) \
static VALUE \
gl_##_name_(ARGLIST##_numparams_) \
VALUE ARGLIST##_numparams_; \
{ \
	gl##_name_(FUNCPARAMS##_numparams_(_ctype_,_conversion_)); \
	CHECK_GLERROR \
	return Qnil; \
} 

#define GL_SIMPLE_FUNC_LOAD(_name_,_numparams_,_ctype_,_conversion_) \
static void (APIENTRY * fptr_gl##_name_)( TYPELIST##_numparams_(_ctype_) ); \
static VALUE \
gl_##_name_(ARGLIST##_numparams_) \
VALUE ARGLIST##_numparams_; \
{ \
	LOAD_GL_FUNC(gl##_name_) \
	fptr_gl##_name_(FUNCPARAMS##_numparams_(_ctype_,_conversion_)); \
	CHECK_GLERROR \
	return Qnil; \
} 


#define GL_EXT_SIMPLE_FUNC_LOAD(_name_,_numparams_,_ctype_,_conversion_,_extensionname_) \
static void (APIENTRY * fptr_gl##_name_)( TYPELIST##_numparams_(_ctype_) ); \
static VALUE \
gl_##_name_(ARGLIST##_numparams_) \
VALUE ARGLIST##_numparams_; \
{ \
	LOAD_GL_EXT_FUNC(gl##_name_,_extensionname_) \
	fptr_gl##_name_(FUNCPARAMS##_numparams_(_ctype_,_conversion_)); \
	CHECK_GLERROR \
	return Qnil; \
} 

#endif /* _COMMON_H_ */
