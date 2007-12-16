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

/* These macros are for simplification of function definition, as passing
  arguments from/to OpenGL usually follows the same few patterns. It would
  be probably wise to adapt the whole bindings to C++ (templates, overloaded
  functions, etc.), but for now supporting ruby extension for Windows means
  MSVC6, and that in turn means unspeakable horrors and pains for everyone
  attempting to merely write, much less debug or maintain any template-based
  code.
*/

/* Will load function pointer for function _NAME_ on first call to the
  function, or raise if the OpenGL version is less then required or the
  required extension is not supported */
#define LOAD_GL_FUNC(_NAME_,_VEREXT_) \
if (fptr_##_NAME_==NULL) { \
	if (CheckVersionExtension(_VEREXT_)==GL_FALSE) { \
		if (isdigit(_VEREXT_[0])) \
			rb_raise(rb_eNotImpError,"OpenGL version %s is not available on this system",_VEREXT_); \
		else \
			rb_raise(rb_eNotImpError,"Extension %s is not available on this system",_VEREXT_); \
	} \
	fptr_##_NAME_ = load_gl_function(#_NAME_, 1); \
}

/* Macroset for defining simple functions, i.e. functions that take n arguments and
  pass them to GL API function without any additional processing.

  Some checking is implicit in _conversion_ argument - e.g. NUM2INT makes sure that
  user is really passing type that can be converted to INT, otherwire raises.
  
  *_LOAD version of macros are for defining functions where we load function pointer
  instead of direct call - that means all functions above OpenGL 1.1 (including all extensions)
*/

#define ARGLIST0 
#define ARGLIST1 ,arg1
#define ARGLIST2 ,arg1,arg2
#define ARGLIST3 ,arg1,arg2,arg3
#define ARGLIST4 ,arg1,arg2,arg3,arg4
#define ARGLIST5 ,arg1,arg2,arg3,arg4,arg5
#define ARGLIST6 ,arg1,arg2,arg3,arg4,arg5,arg6
#define ARGLIST7 ,arg1,arg2,arg3,arg4,arg5,arg6,arg7
#define ARGLIST8 ,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8
#define ARGLIST9 ,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9
#define ARGLIST10 ,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10

#define CONV_GLenum (GLenum)NUM2UINT
#define CONV_GLboolean (GLboolean)NUM2UINT
#define CONV_GLbitfield (GLbitfield)NUM2UINT
#define CONV_GLbyte (GLbyte)NUM2INT
#define CONV_GLshort (GLshort)NUM2INT
#define CONV_GLint (GLint)NUM2INT
#define CONV_GLubyte (GLubyte)NUM2UINT
#define CONV_GLushort (GLushort)NUM2UINT
#define CONV_GLuint (GLuint)NUM2UINT
#define CONV_GLsizei (GLsizei)NUM2INT
#define CONV_GLfloat (GLfloat)NUM2DBL
#define CONV_GLclampf (GLclampf)NUM2DBL
#define CONV_GLdouble (GLdouble)NUM2DBL
#define CONV_GLclampd (GLclampd)NUM2DBL

#define RETDECL_BASE(_t_) _t_ ret = (_t_) 0;
#define RETDECL_GLvoid
#define RETDECL_void
#define RETDECL_GLenum RETDECL_BASE(GLenum)
#define RETDECL_GLboolean RETDECL_BASE(GLboolean)
#define RETDECL_GLbitfield RETDECL_BASE(GLbitfield)
#define RETDECL_GLbyte RETDECL_BASE(GLbyte)
#define RETDECL_GLshort RETDECL_BASE(GLshort)
#define RETDECL_GLint RETDECL_BASE(GLint)
#define RETDECL_GLubyte RETDECL_BASE(GLubyte)
#define RETDECL_GLushort RETDECL_BASE(GLushort)
#define RETDECL_GLuint RETDECL_BASE(GLuint)
#define RETDECL_GLsizei RETDECL_BASE(GLsizei)
#define RETDECL_GLfloat RETDECL_BASE(GLfloat)
#define RETDECL_GLclampf RETDECL_BASE(GLclampf)
#define RETDECL_GLdouble RETDECL_BASE(GLdouble)
#define RETDECL_GLclampd RETDECL_BASE(GLclampd)

#define RETSTAT_GLvoid
#define RETSTAT_void
#define RETSTAT_GLenum ret=
#define RETSTAT_GLboolean ret=
#define RETSTAT_GLbitfield ret=
#define RETSTAT_GLbyte ret=
#define RETSTAT_GLshort ret=
#define RETSTAT_GLint ret=
#define RETSTAT_GLubyte ret=
#define RETSTAT_GLushort ret=
#define RETSTAT_GLuint ret=
#define RETSTAT_GLsizei ret=
#define RETSTAT_GLfloat ret=
#define RETSTAT_GLclampf ret=
#define RETSTAT_GLdouble ret=
#define RETSTAT_GLclampd ret=

#define RETCONV_GLvoid(x) Qnil
#define RETCONV_void(x) Qnil
#define RETCONV_GLenum(x) UINT2NUM(x)
#define RETCONV_GLboolean(x) GLBOOL2RUBY(x)
#define RETCONV_GLbitfield(x) UINT2NUM(x)
#define RETCONV_GLbyte(x) INT2NUM(x)
#define RETCONV_GLshort(x) INT2NUM(x)
#define RETCONV_GLint(x) INT2NUM(x)
#define RETCONV_GLubyte(x) UINT2NUM(x)
#define RETCONV_GLushort(x) UINT2NUM(x)
#define RETCONV_GLuint(x) UINT2NUM(x)
#define RETCONV_GLsizei(x) INT2NUM(x)
#define RETCONV_GLfloat(x) rb_float_new(x)
#define RETCONV_GLclampf(x) rb_float_new(x)
#define RETCONV_GLdouble(x) rb_float_new(x)
#define RETCONV_GLclampd(x) rb_float_new(x)

#define PROTOPARAM0(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) void
#define PROTOPARAM1(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1
#define PROTOPARAM2(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2
#define PROTOPARAM3(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3
#define PROTOPARAM4(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4
#define PROTOPARAM5(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5
#define PROTOPARAM6(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5,p6
#define PROTOPARAM7(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5,p6,p7
#define PROTOPARAM8(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5,p6,p7,p8
#define PROTOPARAM9(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5,p6,p7,p8,p9
#define PROTOPARAM10(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) p1,p2,p3,p4,p5,p6,p7,p8,p9,p10

#define CALLCONV0(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) 
#define CALLCONV1(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1)
#define CALLCONV2(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2)
#define CALLCONV3(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3)
#define CALLCONV4(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4)
#define CALLCONV5(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5)
#define CALLCONV6(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5),CONV_##cv6(arg6)
#define CALLCONV7(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5),CONV_##cv6(arg6),CONV_##cv7(arg7)
#define CALLCONV8(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5),CONV_##cv6(arg6),CONV_##cv7(arg7),CONV_##cv8(arg8)
#define CALLCONV9(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5),CONV_##cv6(arg6),CONV_##cv7(arg7),CONV_##cv8(arg8),CONV_##cv9(arg9)
#define CALLCONV10(cv1,cv2,cv3,cv4,cv5,cv6,cv7,cv8,cv9,cv10) CONV_##cv1(arg1),CONV_##cv2(arg2),CONV_##cv3(arg3),CONV_##cv4(arg4),CONV_##cv5(arg5),CONV_##cv6(arg6),CONV_##cv7(arg7),CONV_##cv8(arg8),CONV_##cv9(arg9),CONV_##cv10(arg10)

#define GL_FUNC_LOAD(_num_,_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10,_ver_) \
static _returntype_ (APIENTRY * fptr_gl##_name_)(PROTOPARAM##_num_(targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10)); \
static VALUE \
gl_##_name_(obj ARGLIST##_num_) \
VALUE obj ARGLIST##_num_; \
{ \
	RETDECL_##_returntype_ \
	LOAD_GL_FUNC(gl##_name_,_ver_) \
	RETSTAT_##_returntype_ fptr_gl##_name_(CALLCONV##_num_(targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10)); \
	CHECK_GLERROR \
	return RETCONV_##_returntype_(ret) ; \
}

#define GL_FUNC_STATIC(_num_,_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10) \
static VALUE \
gl_##_name_(obj ARGLIST##_num_) \
VALUE obj ARGLIST##_num_; \
{ \
	RETDECL_##_returntype_ \
	RETSTAT_##_returntype_ gl##_name_(CALLCONV##_num_(targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10)); \
	CHECK_GLERROR \
	return RETCONV_##_returntype_(ret) ; \
}

#define GL_FUNC_LOAD_0(_name_,_returntype_,_ver_) GL_FUNC_LOAD(0, _name_,_returntype_,0,0,0,0,0,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_1(_name_,_returntype_,targ1,_ver_) GL_FUNC_LOAD(1, _name_,_returntype_,targ1,0,0,0,0,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_2(_name_,_returntype_,targ1,targ2,_ver_) GL_FUNC_LOAD(2, _name_,_returntype_,targ1,targ2,0,0,0,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_3(_name_,_returntype_,targ1,targ2,targ3,_ver_) GL_FUNC_LOAD(3, _name_,_returntype_,targ1,targ2,targ3,0,0,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_4(_name_,_returntype_,targ1,targ2,targ3,targ4,_ver_) GL_FUNC_LOAD(4, _name_,_returntype_,targ1,targ2,targ3,targ4,0,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_5(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,_ver_) GL_FUNC_LOAD(5, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,0,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_6(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,_ver_) GL_FUNC_LOAD(6, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,0,0,0,0,_ver_)
#define GL_FUNC_LOAD_7(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,_ver_) GL_FUNC_LOAD(7, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,0,0,0,_ver_)
#define GL_FUNC_LOAD_8(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,_ver_) GL_FUNC_LOAD(8, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,0,0,_ver_)
#define GL_FUNC_LOAD_9(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,_ver_) GL_FUNC_LOAD(9, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,0,_ver_)
#define GL_FUNC_LOAD_10(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10,_ver_) GL_FUNC_LOAD(10, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10,_ver_)

#define GL_FUNC_STATIC_0(_name_,_returntype_) GL_FUNC_STATIC(0, _name_,_returntype_,0,0,0,0,0,0,0,0,0,0)
#define GL_FUNC_STATIC_1(_name_,_returntype_,targ1) GL_FUNC_STATIC(1, _name_,_returntype_,targ1,0,0,0,0,0,0,0,0,0)
#define GL_FUNC_STATIC_2(_name_,_returntype_,targ1,targ2) GL_FUNC_STATIC(2, _name_,_returntype_,targ1,targ2,0,0,0,0,0,0,0,0)
#define GL_FUNC_STATIC_3(_name_,_returntype_,targ1,targ2,targ3) GL_FUNC_STATIC(3, _name_,_returntype_,targ1,targ2,targ3,0,0,0,0,0,0,0)
#define GL_FUNC_STATIC_4(_name_,_returntype_,targ1,targ2,targ3,targ4) GL_FUNC_STATIC(4, _name_,_returntype_,targ1,targ2,targ3,targ4,0,0,0,0,0,0)
#define GL_FUNC_STATIC_5(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5) GL_FUNC_STATIC(5, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,0,0,0,0,0)
#define GL_FUNC_STATIC_6(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6) GL_FUNC_STATIC(6, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,0,0,0,0)
#define GL_FUNC_STATIC_7(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7) GL_FUNC_STATIC(7, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,0,0,0)
#define GL_FUNC_STATIC_8(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8) GL_FUNC_STATIC(8, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,0,0)
#define GL_FUNC_STATIC_9(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9) GL_FUNC_STATIC(9, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,0)
#define GL_FUNC_STATIC_10(_name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10_ver_) GL_FUNC_STATIC(10, _name_,_returntype_,targ1,targ2,targ3,targ4,targ5,targ6,targ7,targ8,targ9,targ10)

/* Templates for glGen* and glDelete* */

#define GL_FUNC_GENOBJECTS_LOAD(_name_,_ver_) \
static void (APIENTRY * fptr_gl##_name_)(GLsizei,GLuint *); \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	GLsizei n; \
	GLuint *objects; \
	VALUE ret; \
	unsigned int i; \
	LOAD_GL_FUNC(gl##_name_,_ver_) \
	n = CONV_GLsizei(arg1); \
	objects = ALLOC_N(GLuint, n); \
	fptr_gl##_name_(n,objects); \
	ret = rb_ary_new2(n); \
	for (i = 0; i < n; i++) \
		rb_ary_push(ret, RETCONV_GLuint(objects[i])); \
	xfree(objects); \
	CHECK_GLERROR \
	return ret; \
}

#define GL_FUNC_GENOBJECTS(_name_) \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	GLsizei n; \
	GLuint *objects; \
	VALUE ret; \
	unsigned int i; \
	n = CONV_GLsizei(arg1); \
	objects = ALLOC_N(GLuint, n); \
	gl##_name_(n,objects); \
	ret = rb_ary_new2(n); \
	for (i = 0; i < n; i++) \
		rb_ary_push(ret, RETCONV_GLuint(objects[i])); \
	xfree(objects); \
	CHECK_GLERROR \
	return ret; \
}

#define GL_FUNC_DELETEOBJECTS_LOAD(_name_,_ver_) \
static void (APIENTRY * fptr_gl##_name_)(GLsizei,const GLuint *); \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	GLsizei n; \
	LOAD_GL_FUNC(gl##_name_,_ver_) \
	if (TYPE(arg1)==T_ARRAY) { \
		GLuint *objects; \
		n = RARRAY(arg1)->len; \
		objects = ALLOC_N(GLuint,n); \
		ary2cuint(arg1,objects,n);  \
		fptr_gl##_name_(n,objects); \
		xfree(objects); \
	} else { \
		GLuint object; \
		object = CONV_GLsizei(arg1); \
		fptr_gl##_name_(1,&object);  \
	} \
	CHECK_GLERROR \
	return Qnil; \
}

#define GL_FUNC_DELETEOBJECTS(_name_) \
static VALUE gl_##_name_(VALUE obj,VALUE arg1) \
{ \
	GLsizei n; \
	if (TYPE(arg1)==T_ARRAY) { \
		GLuint *objects; \
		n = RARRAY(arg1)->len; \
		objects = ALLOC_N(GLuint,n); \
		ary2cuint(arg1,objects,n);  \
		gl##_name_(n,objects); \
		xfree(objects); \
	} else { \
		GLuint object; \
		object = CONV_GLsizei(arg1); \
		gl##_name_(1,&object);  \
	} \
	CHECK_GLERROR \
	return Qnil; \
}
