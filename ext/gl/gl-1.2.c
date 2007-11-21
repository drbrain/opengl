/*
 * Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
 * Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
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

/* OpenGL 1.2 functions */

GL_SIMPLE_FUNC_LOAD(BlendColor,4,GLclampf,NUM2DBL, 1,2)
GL_SIMPLE_FUNC_LOAD(BlendEquation,1,GLenum,NUM2INT, 1,2)

static void (APIENTRY * fptr_glDrawRangeElements)(GLenum,GLuint,GLuint,GLsizei,GLenum,GLvoid*);
static VALUE
gl_DrawRangeElements(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum mode;
	GLuint start;
	GLuint end;
	GLsizei count;
	GLenum type;
	LOAD_GL_FUNC(glDrawRangeElements,1,2)
	mode = (GLenum)NUM2INT(arg1);
	start = (GLuint)NUM2UINT(arg2);
	end = (GLuint)NUM2UINT(arg3);
	count = (GLsizei)NUM2UINT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CheckBufferBinding(GL_ELEMENT_ARRAY_BUFFER_BINDING)) {
		fptr_glDrawRangeElements(mode, start, end, count, type, (GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6, T_STRING);
		fptr_glDrawRangeElements(mode, start, end, count, type, RSTRING(arg6)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glColorTable)(GLenum,GLenum,GLsizei,GLenum,GLenum,GLvoid*);
static VALUE
gl_ColorTable(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glColorTable,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	width = (GLsizei)NUM2UINT(arg3);
	format = (GLenum)NUM2INT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glColorTable(target,internalformat,width,format,type,(GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6,T_STRING);
		CheckDataSize(type,format,width,arg6);
		fptr_glColorTable(target,internalformat,width,format,type,RSTRING(arg6)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glColorTableParameterfv)(GLenum,GLenum,const GLfloat*);
static VALUE
gl_ColorTableParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {0.0,0.0,0.0,0.0};
	LOAD_GL_FUNC(glColorTableParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cflt(arg3,params,4);
	fptr_glColorTableParameterfv(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glColorTableParameteriv)(GLenum,GLenum,const GLint*);
static VALUE
gl_ColorTableParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	LOAD_GL_FUNC(glColorTableParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cint(arg3,params,4);
	fptr_glColorTableParameteriv(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCopyColorTable)(GLenum,GLenum,GLint,GLint,GLsizei);
static VALUE
gl_CopyColorTable(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
	GLenum target;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	LOAD_GL_FUNC(glCopyColorTable,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	x = (GLint)NUM2INT(arg3);
	y = (GLint)NUM2INT(arg4);
	width = (GLsizei)NUM2INT(arg5);
	fptr_glCopyColorTable(target,internalformat,x,y,width);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetColorTableParameterfv)(GLenum,GLenum,GLfloat *);
static VALUE
gl_GetColorTableParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {0.0,0.0,0.0,0.0};
	GLsizei size;
	VALUE retary;
	int i;
	LOAD_GL_FUNC(glGetColorTableParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch (pname) {
		case GL_COLOR_TABLE_SCALE:
		case GL_COLOR_TABLE_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetColorTableParameterfv(target,pname,params);
	retary = rb_ary_new2(size);
	for(i=0;i<size;i++)
		rb_ary_push(retary, rb_float_new(params[i]));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetColorTableParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetColorTableParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	GLsizei size;
	VALUE retary;
	int i;
	LOAD_GL_FUNC(glGetColorTableParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch (pname) {
		case GL_COLOR_TABLE_SCALE:
		case GL_COLOR_TABLE_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetColorTableParameteriv(target,pname,params);
	retary = rb_ary_new2(size);
	for(i=0;i<size;i++)
		rb_ary_push(retary, INT2NUM(params[i]));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetColorTable)(GLenum,GLenum,GLenum,GLvoid *);
static VALUE
gl_GetColorTable(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum format;
	GLenum type;
	GLsizei width = 0;
	VALUE data;
	LOAD_GL_FUNC(glGetColorTable,1,2)
	LOAD_GL_FUNC(glGetColorTableParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	format = (GLenum)NUM2INT(arg2);
	type = (GLenum)NUM2INT(arg3);
	fptr_glGetColorTableParameteriv(target,GL_COLOR_TABLE_WIDTH,&width);
	CHECK_GLERROR
	data = allocate_buffer_with_string(GetDataSize(type,format,width));
	FORCE_PIXEL_STORE_MODE
	fptr_glGetColorTable(target,format,type,(GLvoid*)RSTRING(data)->ptr);	
	RESTORE_PIXEL_STORE_MODE
	CHECK_GLERROR
	return data;
}

static void (APIENTRY * fptr_glColorSubTable)(GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid *data);
static VALUE
gl_ColorSubTable(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLsizei start;
	GLsizei count;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glColorSubTable,1,2)
	target = (GLenum)NUM2INT(arg1);	
	start = (GLsizei)NUM2UINT(arg2);	
	count = (GLsizei)NUM2UINT(arg3);	
	format = (GLenum)NUM2INT(arg4);	
	type = (GLenum)NUM2INT(arg5);	
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glColorSubTable(target,start,count,format,type,(GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6,T_STRING);
		CheckDataSize(type,format,count,arg6);
		fptr_glColorSubTable(target,start,count,format,type,RSTRING(arg6)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCopyColorSubTable)(GLenum,GLsizei,GLint,GLint,GLsizei);
static VALUE
gl_CopyColorSubTable(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
	GLenum target;
	GLsizei start;
	GLint x;
	GLint y;
	GLsizei width;
	LOAD_GL_FUNC(glCopyColorSubTable,1,2)
	target = (GLenum)NUM2INT(arg1);
	start = (GLsizei)NUM2UINT(arg2);
	x = (GLint)NUM2INT(arg3);
	y = (GLint)NUM2INT(arg4);
	width = (GLsizei)NUM2UINT(arg5);
	fptr_glCopyColorSubTable(target,start,x,y,width);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionFilter1D)(GLenum,GLenum,GLsizei,GLenum,GLenum,const GLvoid *);
static VALUE
gl_ConvolutionFilter1D(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glConvolutionFilter1D,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	width = (GLsizei)NUM2UINT(arg3);
	format = (GLenum)NUM2INT(arg4);
	type = (GLenum)NUM2INT(arg5);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glConvolutionFilter1D(target,internalformat,width,format,type,(GLvoid *)NUM2INT(arg6));
	} else {
		Check_Type(arg6,T_STRING);
		CheckDataSize(type,format,width,arg6);
		fptr_glConvolutionFilter1D(target,internalformat,width,format,type,RSTRING(arg6)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionFilter2D)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid *);
static VALUE
gl_ConvolutionFilter2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7;
{
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glConvolutionFilter2D,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	width = (GLsizei)NUM2UINT(arg3);
	height = (GLsizei)NUM2UINT(arg4);
	format = (GLenum)NUM2INT(arg5);
	type = (GLenum)NUM2INT(arg6);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glConvolutionFilter2D(target,internalformat,width,height,format,type,(GLvoid *)NUM2INT(arg7));
	} else {
		Check_Type(arg7,T_STRING);
		CheckDataSize(type,format,width*height,arg7);
		fptr_glConvolutionFilter2D(target,internalformat,width,height,format,type,RSTRING(arg7)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionParameterf)(GLenum,GLenum,GLfloat);
static VALUE
gl_ConvolutionParameterf(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLfloat params;
	LOAD_GL_FUNC(glConvolutionParameterf,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	params = (GLfloat)NUM2INT(arg3);
	fptr_glConvolutionParameterf(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionParameterfv)(GLenum,GLenum,const GLfloat *);
static VALUE
gl_ConvolutionParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {0.0,0.0,0.0,0.0};
	LOAD_GL_FUNC(glConvolutionParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cflt(arg3,params,4);
	fptr_glConvolutionParameterfv(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionParameteri)(GLenum,GLenum,GLint);
static VALUE
gl_ConvolutionParameteri(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLint params;
	LOAD_GL_FUNC(glConvolutionParameteri,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	params = (GLint)NUM2INT(arg3);
	fptr_glConvolutionParameteri(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glConvolutionParameteriv)(GLenum,GLenum,const GLint *);
static VALUE
gl_ConvolutionParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	LOAD_GL_FUNC(glConvolutionParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	Check_Type(arg3,T_ARRAY);
	ary2cint(arg3,params,4);
	fptr_glConvolutionParameteriv(target,pname,params);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCopyConvolutionFilter1D)(GLenum,GLenum,GLint,GLint,GLsizei);
static VALUE
gl_CopyConvolutionFilter1D(obj,arg1,arg2,arg3,arg4,arg5)
VALUE obj,arg1,arg2,arg3,arg4,arg5;
{
	GLenum target;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	LOAD_GL_FUNC(glCopyConvolutionFilter1D,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	x = (GLint)NUM2INT(arg3);
	y = (GLint)NUM2INT(arg4);
	width = (GLsizei)NUM2UINT(arg5);
	fptr_glCopyConvolutionFilter1D(target,internalformat,x,y,width);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCopyConvolutionFilter2D)(GLenum,GLenum,GLint,GLint,GLsizei,GLsizei);
static VALUE
gl_CopyConvolutionFilter2D(obj,arg1,arg2,arg3,arg4,arg5,arg6)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6;
{
	GLenum target;
	GLenum internalformat;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	LOAD_GL_FUNC(glCopyConvolutionFilter2D,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	x = (GLint)NUM2INT(arg3);
	y = (GLint)NUM2INT(arg4);
	width = (GLsizei)NUM2UINT(arg5);
	height = (GLsizei)NUM2UINT(arg6);
	fptr_glCopyConvolutionFilter2D(target,internalformat,x,y,width,height);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetConvolutionParameterfv)(GLenum,GLenum,GLfloat *);
static VALUE
gl_GetConvolutionParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLfloat params[4] = {0.0,0.0,0.0,0.0};
	GLsizei size;
	int i;
	VALUE retary;	
	LOAD_GL_FUNC(glGetConvolutionParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch(pname) {
		case GL_CONVOLUTION_BORDER_COLOR:
		case GL_CONVOLUTION_FILTER_SCALE:
		case GL_CONVOLUTION_FILTER_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetConvolutionParameterfv(target,pname,params);
	retary = rb_ary_new2(size);
	for(i=0;i<size;i++)
		rb_ary_push(retary, rb_float_new(params[i]));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetConvolutionParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetConvolutionParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLint params[4] = {0,0,0,0};
	GLsizei size;
	int i;
	VALUE retary;	
	LOAD_GL_FUNC(glGetConvolutionParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	switch(pname) {
		case GL_CONVOLUTION_BORDER_COLOR:
		case GL_CONVOLUTION_FILTER_SCALE:
		case GL_CONVOLUTION_FILTER_BIAS:
			size = 4;
			break;
		default:
			size = 1;
			break;
	}
	fptr_glGetConvolutionParameteriv(target,pname,params);
	retary = rb_ary_new2(size);
	for(i=0;i<size;i++)
		rb_ary_push(retary, INT2NUM(params[i]));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetConvolutionFilter)(GLenum,GLenum,GLenum,GLvoid *);
static VALUE
gl_GetConvolutionFilter(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum target;
	GLenum format;
	GLenum type;
	GLint size = 0;
	VALUE data;
	VALUE args[4];
	int numargs;
	LOAD_GL_FUNC(glGetConvolutionFilter,1,2)
	LOAD_GL_FUNC(glGetConvolutionParameteriv,1,2)
	numargs = rb_scan_args(argc, argv, "31", &args[0], &args[1], &args[2], &args[3]);
	target = (GLenum)NUM2INT(args[0]);
	format = (GLenum)NUM2INT(args[1]);
	type = (GLenum)NUM2INT(args[2]);

	switch(numargs) {
		default:
		case 3:
			if (CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
			rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");
	
			if (target==GL_CONVOLUTION_1D) {
				fptr_glGetConvolutionParameteriv(target,GL_CONVOLUTION_WIDTH,&size);
			} else {
				GLint tmp = 0;
				fptr_glGetConvolutionParameteriv(target,GL_CONVOLUTION_WIDTH,&tmp);
				fptr_glGetConvolutionParameteriv(target,GL_CONVOLUTION_HEIGHT,&size);
				size *=tmp;
			}
			CHECK_GLERROR
			data = allocate_buffer_with_string(GetDataSize(type,format,size));
			FORCE_PIXEL_STORE_MODE
			fptr_glGetConvolutionFilter(target,format,type,(GLvoid*)RSTRING(data)->ptr);
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return data;
		case 4:
			if (!CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer not bound");

			FORCE_PIXEL_STORE_MODE
			fptr_glGetConvolutionFilter(target,format,type,(GLvoid*)NUM2INT(args[3]));
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return Qnil;
	}
}

static void (APIENTRY * fptr_glGetSeparableFilter)(GLenum,GLenum,GLenum,GLvoid*,GLvoid*,GLvoid*);
static VALUE
gl_GetSeparableFilter(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum target;
	GLenum format;
	GLenum type;
	GLint size_row = 0;
	GLint size_column = 0;
	VALUE data_row;
	VALUE data_column;
	VALUE retary;
	VALUE args[6];
	int numargs;
	LOAD_GL_FUNC(glGetSeparableFilter,1,2)
	LOAD_GL_FUNC(glGetConvolutionParameteriv,1,2)
	numargs = rb_scan_args(argc, argv, "33", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5]);
	target = (GLenum)NUM2INT(args[0]);
	format = (GLenum)NUM2INT(args[1]);
	type = (GLenum)NUM2INT(args[2]);

	switch(numargs) {
		default:
		case 3:
			if (CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset arguments missing");

			fptr_glGetConvolutionParameteriv(target,GL_CONVOLUTION_WIDTH,&size_row);
			fptr_glGetConvolutionParameteriv(target,GL_CONVOLUTION_HEIGHT,&size_column);
			CHECK_GLERROR
			data_row = allocate_buffer_with_string(GetDataSize(type,format,size_row));
			data_column = allocate_buffer_with_string(GetDataSize(type,format,size_column));
			FORCE_PIXEL_STORE_MODE
			fptr_glGetSeparableFilter(target,format,type,(GLvoid*)RSTRING(data_row)->ptr,(GLvoid*)RSTRING(data_column)->ptr,0);
			RESTORE_PIXEL_STORE_MODE
			retary = rb_ary_new2(2);
			rb_ary_push(retary, data_row);
			rb_ary_push(retary, data_column);
			CHECK_GLERROR
			return retary;
			break;
		case 6:
			if (!CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer not bound");
			FORCE_PIXEL_STORE_MODE
			fptr_glGetSeparableFilter(target,format,type,(GLvoid*)NUM2INT(args[3]),(GLvoid*)NUM2INT(args[4]),(GLvoid*)NUM2INT(args[5]));
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return Qnil;		
		}
}

static void (APIENTRY * fptr_glSeparableFilter2D)(GLenum,GLenum,GLsizei,GLsizei,GLenum,GLenum,const GLvoid *,const GLvoid *);
static VALUE
gl_SeparableFilter2D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8;
{
	GLenum target;
	GLenum internalformat;
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLenum type;
	LOAD_GL_FUNC(glSeparableFilter2D,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	width = (GLsizei)NUM2UINT(arg3);
	height = (GLsizei)NUM2UINT(arg4);
	format = (GLenum)NUM2INT(arg5);
	type = (GLenum)NUM2INT(arg6);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glSeparableFilter2D(target,internalformat,width,height,format,type,(GLvoid *)NUM2INT(arg7),(GLvoid *)NUM2INT(arg8));
	} else {
		Check_Type(arg7,T_STRING);
		Check_Type(arg8,T_STRING);
		CheckDataSize(type,format,width,arg7);
		CheckDataSize(type,format,height,arg8);
		fptr_glSeparableFilter2D(target,internalformat,width,height,format,type,RSTRING(arg7)->ptr,RSTRING(arg8)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glGetHistogramParameterfv)(GLenum,GLenum,GLfloat *);
static VALUE
gl_GetHistogramParameterfv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLfloat params = 0.0;
	VALUE retary;	
	LOAD_GL_FUNC(glGetHistogramParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetHistogramParameterfv(target,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary, rb_float_new(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetHistogramParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetHistogramParameteriv(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum pname;
	GLint params = 0;
	VALUE retary;	
	LOAD_GL_FUNC(glGetHistogramParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetHistogramParameteriv(target,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary, INT2NUM(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetHistogram)(GLenum,GLboolean,GLenum,GLenum,GLvoid*);
static VALUE
gl_GetHistogram(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum target;
	GLboolean reset;
	GLenum format;
	GLenum type;
	GLint size = 0;
	VALUE data;
	VALUE args[5];
	int numargs;
	LOAD_GL_FUNC(glGetHistogram,1,2)
	LOAD_GL_FUNC(glGetHistogramParameteriv,1,2)
	numargs = rb_scan_args(argc, argv, "41", &args[0], &args[1], &args[2], &args[3], &args[4]);
	target = (GLenum)NUM2INT(args[0]);
	reset = (GLboolean)NUM2INT(args[1]);
	format = (GLenum)NUM2INT(args[2]);
	type = (GLenum)NUM2INT(args[3]);

	switch(numargs) {
		default:
		case 4:
			if (CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");

			fptr_glGetHistogramParameteriv(target,GL_HISTOGRAM_WIDTH,&size);
			CHECK_GLERROR
			data = allocate_buffer_with_string(GetDataSize(type,format,size));
			FORCE_PIXEL_STORE_MODE
			fptr_glGetHistogram(target,reset,format,type,(GLvoid*)RSTRING(data)->ptr);
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return data;
			break;
		case 5:
			if (!CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer not bound");

			FORCE_PIXEL_STORE_MODE
			fptr_glGetHistogram(target,reset,format,type,(GLvoid*)NUM2INT(args[4]));
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return Qnil;
	}
}

static void (APIENTRY * fptr_glGetMinmax)(GLenum,GLboolean,GLenum,GLenum,GLvoid *);
static VALUE
gl_GetMinmax(argc,argv,obj)
int argc;
VALUE *argv;
VALUE obj;
{
	GLenum target;
	GLboolean reset;
	GLenum format;
	GLenum type;
	VALUE data;
	VALUE args[5];
	int numargs;
	LOAD_GL_FUNC(glGetMinmax,1,2)
	numargs = rb_scan_args(argc, argv, "41", &args[0], &args[1], &args[2], &args[3], &args[4]);
	target = (GLenum)NUM2INT(args[0]);
	reset = (GLboolean)NUM2INT(args[1]);
	format = (GLenum)NUM2INT(args[2]);
	type = (GLenum)NUM2INT(args[3]);

	switch(numargs) {
		default:
		case 4:
			if (CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer bound, but offset argument missing");

			data = allocate_buffer_with_string(GetDataSize(type,format,2));
			FORCE_PIXEL_STORE_MODE
			fptr_glGetMinmax(target,reset,format,type,(GLvoid*)RSTRING(data)->ptr);
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return data;
			break;
		case 5:
			if (!CheckBufferBinding(GL_PIXEL_PACK_BUFFER_BINDING))
				rb_raise(rb_eArgError, "Pixel pack buffer not bound");

			FORCE_PIXEL_STORE_MODE
			fptr_glGetMinmax(target,reset,format,type,(GLvoid*)NUM2INT(args[4]));
			RESTORE_PIXEL_STORE_MODE
			CHECK_GLERROR
			return Qnil;
	}
}

static void (APIENTRY * fptr_glGetMinmaxParameterfv)(GLenum,GLenum,GLfloat *);
static VALUE
gl_GetMinmaxParameterfv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLfloat params = 0.0;
	VALUE retary;	
	LOAD_GL_FUNC(glGetMinmaxParameterfv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetMinmaxParameterfv(target,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary, rb_float_new(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glGetMinmaxParameteriv)(GLenum,GLenum,GLint *);
static VALUE
gl_GetMinmaxParameteriv(obj,arg1,arg2)
VALUE obj,arg1,arg2;
{
	GLenum target;
	GLenum pname;
	GLint params = 0;
	VALUE retary;	
	LOAD_GL_FUNC(glGetMinmaxParameteriv,1,2)
	target = (GLenum)NUM2INT(arg1);
	pname = (GLenum)NUM2INT(arg2);
	fptr_glGetMinmaxParameteriv(target,pname,&params);
	retary = rb_ary_new2(1);
	rb_ary_push(retary, INT2NUM(params));
	CHECK_GLERROR
	return retary;
}

static void (APIENTRY * fptr_glHistogram)(GLenum,GLsizei,GLenum,GLboolean);
static VALUE
gl_Histogram(obj,arg1,arg2,arg3,arg4)
VALUE obj,arg1,arg2,arg3,arg4;
{
	GLenum target;
	GLsizei width;
	GLenum internalformat;
	GLboolean sink;
	LOAD_GL_FUNC(glHistogram,1,2)
	target = (GLenum)NUM2INT(arg1);
	width = (GLsizei)NUM2UINT(arg2);
	internalformat = (GLenum)NUM2INT(arg3);
	sink = (GLboolean)NUM2INT(arg4);
	fptr_glHistogram(target,width,internalformat,sink);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glMinmax)(GLenum,GLenum,GLboolean);
static VALUE
gl_Minmax(obj,arg1,arg2,arg3)
VALUE obj,arg1,arg2,arg3;
{
	GLenum target;
	GLenum internalformat;
	GLboolean sink;
	LOAD_GL_FUNC(glMinmax,1,2)
	target = (GLenum)NUM2INT(arg1);
	internalformat = (GLenum)NUM2INT(arg2);
	sink = (GLboolean)NUM2INT(arg3);
	fptr_glMinmax(target,internalformat,sink);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glResetHistogram)(GLenum);
static VALUE
gl_ResetHistogram(obj,arg1)
VALUE obj,arg1;
{
	GLenum target;
	LOAD_GL_FUNC(glResetHistogram,1,2)
	target = (GLenum)NUM2INT(arg1);
	fptr_glResetHistogram(target);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glResetMinmax)(GLenum);
static VALUE
gl_ResetMinmax(obj,arg1)
VALUE obj,arg1;
{
	GLenum target;
	LOAD_GL_FUNC(glResetMinmax,1,2)
	target = (GLenum)NUM2INT(arg1);
	fptr_glResetMinmax(target);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glTexImage3D)(GLenum,GLint,GLint,GLsizei,GLsizei,GLsizei,GLint,GLenum,GLenum,const GLvoid*);
static VALUE
gl_TexImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10;
{
	GLenum target;
	GLint level;
	GLint internalFormat;
	GLsizei width;
	GLsizei height;
	GLsizei depth;
	GLint border;
	GLenum format;
	GLenum type;
	const char *pixels;
	LOAD_GL_FUNC(glTexImage3D,1,2)
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	internalFormat = (GLint)NUM2INT(arg3);
	width = (GLsizei)NUM2UINT(arg4);
	height = (GLsizei)NUM2UINT(arg5);
	depth = (GLsizei)NUM2UINT(arg6);
	border = (GLint)NUM2INT(arg7);
	format = (GLenum)NUM2INT(arg8);
	type = (GLenum)NUM2INT(arg9);

	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexImage3D( target, level, internalFormat, width, height,
					  depth, border, format, type,(GLvoid *)NUM2INT(arg10));
		CHECK_GLERROR
		return Qnil;
	}

	if (target == GL_PROXY_TEXTURE_3D  ||
			target == GL_PROXY_TEXTURE_1D_STACK_MESAX ||
			target == GL_PROXY_TEXTURE_2D_STACK_MESAX ||
			target == GL_PROXY_TEXTURE_2D_ARRAY_EXT ||
			NIL_P(arg10)) { /* proxy texture, no data read */
		pixels = NULL;
	} else {
		Check_Type(arg10,T_STRING);
		CheckDataSize(type,format,width*height*depth,arg10);
		pixels = RSTRING(arg10)->ptr;
	}
	fptr_glTexImage3D( target, level, internalFormat, width, height,
				  depth, border, format, type,pixels);
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glTexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLsizei,GLsizei,GLsizei,GLenum,GLenum,const GLvoid*);
static VALUE
gl_TexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11)
VALUE arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11;
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
	GLenum type;
	LOAD_GL_FUNC(glTexSubImage3D,1,2)
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	yoffset = (GLint)NUM2INT(arg4);
	zoffset = (GLint)NUM2INT(arg5);
	width = (GLsizei)NUM2UINT(arg6);
	height = (GLsizei)NUM2UINT(arg7);
	depth = (GLsizei)NUM2UINT(arg8);
	format = (GLenum)NUM2INT(arg9);
	type = (GLenum)NUM2INT(arg10);
	if (CheckBufferBinding(GL_PIXEL_UNPACK_BUFFER_BINDING)) {
		fptr_glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
				width, height, depth,
				format, type, (GLvoid *)NUM2INT(arg11));
	} else {
		Check_Type(arg11, T_STRING);
		CheckDataSize(type,format,height*width*depth,arg11);
		fptr_glTexSubImage3D( target, level, xoffset, yoffset, zoffset,
			width, height, depth,
			format, type, RSTRING(arg11)->ptr);
	}
	CHECK_GLERROR
	return Qnil;
}

static void (APIENTRY * fptr_glCopyTexSubImage3D)(GLenum,GLint,GLint,GLint,GLint,GLint,GLint,GLsizei,GLsizei);
static VALUE
gl_CopyTexSubImage3D(obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
VALUE obj,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9;
{
	GLenum target;
	GLint level;
	GLint xoffset;
	GLint yoffset;
	GLint zoffset;
	GLint x;
	GLint y;
	GLsizei width;
	GLsizei height;
	LOAD_GL_FUNC(glCopyTexSubImage3D,1,2)
	target = (GLenum)NUM2INT(arg1);
	level = (GLint)NUM2INT(arg2);
	xoffset = (GLint)NUM2INT(arg3);
	yoffset = (GLint)NUM2INT(arg4);
	zoffset = (GLint)NUM2INT(arg5);
	x = (GLint)NUM2INT(arg6);
	y = (GLint)NUM2INT(arg7);
	width = (GLsizei)NUM2UINT(arg8);
	height = (GLsizei)NUM2UINT(arg9);
	fptr_glCopyTexSubImage3D( target, level,
			xoffset, yoffset, zoffset,
			x, y, width, height );
	CHECK_GLERROR
	return Qnil;
}

void gl_init_functions_1_2(VALUE module)
{
	rb_define_module_function(module, "glBlendColor", gl_BlendColor, 4);
	rb_define_module_function(module, "glBlendEquation", gl_BlendEquation, 1);
	rb_define_module_function(module, "glDrawRangeElements", gl_DrawRangeElements, 6);
	rb_define_module_function(module, "glColorTable", gl_ColorTable, 6);
	rb_define_module_function(module, "glColorTableParameterfv", gl_ColorTableParameterfv, 3);
	rb_define_module_function(module, "glColorTableParameteriv", gl_ColorTableParameteriv, 3);
	rb_define_module_function(module, "glCopyColorTable", gl_CopyColorTable, 5);
	rb_define_module_function(module, "glGetColorTable", gl_GetColorTable, 3);
	rb_define_module_function(module, "glGetColorTableParameterfv", gl_GetColorTableParameterfv, 2);
	rb_define_module_function(module, "glGetColorTableParameteriv", gl_GetColorTableParameteriv, 2);
	rb_define_module_function(module, "glColorSubTable", gl_ColorSubTable, 6);
	rb_define_module_function(module, "glCopyColorSubTable", gl_CopyColorSubTable, 5);
	rb_define_module_function(module, "glConvolutionFilter1D", gl_ConvolutionFilter1D, 6);
	rb_define_module_function(module, "glConvolutionFilter2D", gl_ConvolutionFilter2D, 7);
	rb_define_module_function(module, "glConvolutionParameterf", gl_ConvolutionParameterf, 3);
	rb_define_module_function(module, "glConvolutionParameterfv", gl_ConvolutionParameterfv, 3);
	rb_define_module_function(module, "glConvolutionParameteri", gl_ConvolutionParameteri, 3);
	rb_define_module_function(module, "glConvolutionParameteriv", gl_ConvolutionParameteriv, 3);
	rb_define_module_function(module, "glCopyConvolutionFilter1D", gl_CopyConvolutionFilter1D, 5);
	rb_define_module_function(module, "glCopyConvolutionFilter2D", gl_CopyConvolutionFilter2D, 6);
	rb_define_module_function(module, "glGetConvolutionFilter", gl_GetConvolutionFilter, -1);
	rb_define_module_function(module, "glGetConvolutionParameterfv", gl_GetConvolutionParameterfv, 2);
	rb_define_module_function(module, "glGetConvolutionParameteriv", gl_GetConvolutionParameteriv, 2);
	rb_define_module_function(module, "glGetSeparableFilter", gl_GetSeparableFilter, -1);
	rb_define_module_function(module, "glSeparableFilter2D", gl_SeparableFilter2D, 8);
	rb_define_module_function(module, "glGetHistogram", gl_GetHistogram, -1);
	rb_define_module_function(module, "glGetHistogramParameterfv", gl_GetHistogramParameterfv, 2);
	rb_define_module_function(module, "glGetHistogramParameteriv", gl_GetHistogramParameteriv, 2);
	rb_define_module_function(module, "glGetMinmax", gl_GetMinmax, -1);
	rb_define_module_function(module, "glGetMinmaxParameterfv", gl_GetMinmaxParameterfv, 2);
	rb_define_module_function(module, "glGetMinmaxParameteriv", gl_GetMinmaxParameteriv, 2);
	rb_define_module_function(module, "glHistogram", gl_Histogram, 4);
	rb_define_module_function(module, "glMinmax", gl_Minmax, 3);
	rb_define_module_function(module, "glResetHistogram", gl_ResetHistogram, 1);
	rb_define_module_function(module, "glResetMinmax", gl_ResetMinmax, 1);
	rb_define_module_function(module, "glTexImage3D", gl_TexImage3D, 10);
	rb_define_module_function(module, "glTexSubImage3D", gl_TexSubImage3D, 11);
	rb_define_module_function(module, "glCopyTexSubImage3D", gl_CopyTexSubImage3D, 9);
}
