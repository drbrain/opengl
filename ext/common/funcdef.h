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
gl_##_name_(obj ARGLIST##_numparams_) \
VALUE obj ARGLIST##_numparams_; \
{ \
	gl##_name_(FUNCPARAMS##_numparams_(_ctype_,_conversion_)); \
	CHECK_GLERROR \
	return Qnil; \
} 

#define GL_SIMPLE_FUNC_LOAD(_name_,_numparams_,_ctype_,_conversion_,_ver_) \
static void (APIENTRY * fptr_gl##_name_)( TYPELIST##_numparams_(_ctype_) ); \
static VALUE \
gl_##_name_(obj ARGLIST##_numparams_) \
VALUE obj ARGLIST##_numparams_; \
{ \
	LOAD_GL_FUNC(gl##_name_,_ver_) \
	fptr_gl##_name_(FUNCPARAMS##_numparams_(_ctype_,_conversion_)); \
	CHECK_GLERROR \
	return Qnil; \
} 
