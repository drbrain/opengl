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

#include <ctype.h>

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

#include "funcdef.h"
#include "conv.h"

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

/* at least GL_MAX_VERTEX_ATTRIBS - usually 16 or 32 on today's high-end cards */
#define _MAX_VERTEX_ATTRIBS 64

typedef struct RArray RArray;

extern VALUE cProc;

/* For now we do not honor pixel store modes, so we need to
  force them to defaults on each affected function call for
  correct size requirement calculations */
#define FORCE_PIXEL_STORE_MODE \
	glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT); \
	glPixelStorei(GL_PACK_ALIGNMENT, 1); \
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0); \
	glPixelStorei(GL_PACK_SKIP_ROWS, 0); \
	glPixelStorei(GL_PACK_ROW_LENGTH, 0); \
	glPixelStorei(GL_PACK_SKIP_IMAGES, 0); \
	glPixelStorei(GL_PACK_IMAGE_HEIGHT, 0); \
	if (CheckVersionExtension("GL_SGIS_texture4D")) { \
		glPixelStorei(GL_PACK_SKIP_VOLUMES_SGIS, 0); \
		glPixelStorei(GL_PACK_IMAGE_DEPTH_SGIS, 0); \
	}

#define RESTORE_PIXEL_STORE_MODE \
	glPopClientAttrib();

GLboolean CheckVersionExtension(const char *name);
GLint CheckBufferBinding(GLint buffer);

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

/* returns size(units) for given type of shader uniform var */
static inline int get_uniform_size(GLenum uniform_type)
{
	int uniform_size = 0;

	switch (uniform_type) { 
		case GL_FLOAT: 
		case GL_INT: 
		case GL_UNSIGNED_INT: 
		case GL_BOOL: 
		case GL_SAMPLER_1D: 
		case GL_SAMPLER_2D: 
		case GL_SAMPLER_3D: 
		case GL_SAMPLER_CUBE: 
		case GL_SAMPLER_1D_SHADOW: 
		case GL_SAMPLER_2D_SHADOW: 
		case GL_SAMPLER_2D_RECT_ARB: 
		case GL_SAMPLER_2D_RECT_SHADOW_ARB: 
		case GL_SAMPLER_1D_ARRAY_EXT: 
		case GL_SAMPLER_2D_ARRAY_EXT: 
		case GL_SAMPLER_BUFFER_EXT: 
		case GL_SAMPLER_1D_ARRAY_SHADOW_EXT: 
		case GL_SAMPLER_2D_ARRAY_SHADOW_EXT: 
		case GL_SAMPLER_CUBE_SHADOW_EXT: 
		case GL_INT_SAMPLER_1D_EXT: 
		case GL_INT_SAMPLER_2D_EXT: 
		case GL_INT_SAMPLER_3D_EXT: 
		case GL_INT_SAMPLER_CUBE_EXT: 
		case GL_INT_SAMPLER_2D_RECT_EXT: 
		case GL_INT_SAMPLER_1D_ARRAY_EXT: 
		case GL_INT_SAMPLER_2D_ARRAY_EXT: 
		case GL_INT_SAMPLER_BUFFER_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_1D_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_2D_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_3D_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_CUBE_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_2D_RECT_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY_EXT: 
		case GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT: 
			uniform_size = 1; 
			break; 
		case GL_FLOAT_VEC2: 
		case GL_INT_VEC2: 
		case GL_UNSIGNED_INT_VEC2_EXT: 
		case GL_BOOL_VEC2: 
			uniform_size = 2; 
			break; 
		case GL_FLOAT_VEC3: 
		case GL_INT_VEC3: 
		case GL_UNSIGNED_INT_VEC3_EXT: 
		case GL_BOOL_VEC3: 
			uniform_size = 3; 
			break; 
		case GL_FLOAT_VEC4: 
		case GL_INT_VEC4: 
		case GL_UNSIGNED_INT_VEC4_EXT: 
		case GL_BOOL_VEC4: 
		case GL_FLOAT_MAT2: 
			uniform_size = 4; 
			break; 
		case GL_FLOAT_MAT2x3: 
		case GL_FLOAT_MAT3x2: 
			uniform_size = 6; 
			break; 
		case GL_FLOAT_MAT2x4: 
		case GL_FLOAT_MAT4x2: 
			uniform_size = 8; 
			break; 
		case GL_FLOAT_MAT3: 
			uniform_size = 9; 
			break; 
		case GL_FLOAT_MAT4x3: 
		case GL_FLOAT_MAT3x4: 
			uniform_size = 12; 
			break; 
		case GL_FLOAT_MAT4: 
			uniform_size = 16; 
			break; 
		default: 
			rb_raise(rb_eTypeError, "Unsupported uniform type '%i'",uniform_type);
	}
	return uniform_size;
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
	
	if (RSTRING_LEN(data) < size)
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

static inline VALUE pack_array_or_pass_string(GLenum type,VALUE ary)
{
	char *type_str;

	if (TYPE(ary)==T_STRING)
		return ary;

	Check_Type(ary,T_ARRAY);

	switch(type) {
		case GL_FLOAT:          type_str = "f*"; break;
		case GL_DOUBLE:         type_str = "d*"; break;
		case GL_BYTE:	          type_str = "c*"; break;
		case GL_SHORT:          type_str = "s*"; break;
		case GL_INT:            type_str = "i*"; break;
		case GL_UNSIGNED_BYTE:  type_str = "C*"; break;
		case GL_UNSIGNED_SHORT: type_str = "S*"; break;
		case GL_UNSIGNED_INT:	  type_str = "I*"; break;
		default:
			rb_raise(rb_eTypeError,"Unknown type %i",type);
			return Qnil; /* not reached */
	}

	return rb_funcall(ary,rb_intern("pack"),1,rb_str_new2(type_str));
}

/* -------------------------------------------------------------------- */

#endif /* _COMMON_H_ */
