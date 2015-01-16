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

#include "common.h"

void gl_init_enums(VALUE);
void gl_init_functions_1_0__1_1(VALUE);
void gl_init_functions_1_2(VALUE);
void gl_init_functions_1_3(VALUE);
void gl_init_functions_1_4(VALUE);
void gl_init_functions_1_5(VALUE);
void gl_init_functions_2_0(VALUE);
void gl_init_functions_2_1(VALUE);
void gl_init_functions_3_0(VALUE);
void gl_init_functions_ext_3dfx(VALUE);
void gl_init_functions_ext_arb(VALUE);
void gl_init_functions_ext_ati(VALUE);
void gl_init_functions_ext_ext(VALUE);
void gl_init_functions_ext_gremedy(VALUE);
void gl_init_functions_ext_nv(VALUE);
void gl_init_buffer(VALUE);
void gl_init_glimpl(VALUE);

VALUE g_default_glimpl;

/* Returns current OpenGL version as major, minor or 0,0 if
 * unknown (context not yet initialised etc.) The version is
 * cached for subsequent calls.
 */
const int *GetOpenglVersion(VALUE obj)
{
  int *opengl_version = GET_GLIMPL_VARIABLE(opengl_version);
  DECL_GL_FUNC_PTR(const GLubyte *,glGetString,(GLenum name));

  LOAD_GL_FUNC(glGetString, NULL);
  if (opengl_version[0]==0) { /* not cached, query */
    const char *vstr = (const char *) fptr_glGetString(GL_VERSION);
    CHECK_GLERROR_FROM("glGetString");
    if (vstr){
      int v0, v1;
      sscanf( vstr, "%d.%d", &v0, &v1 );
      SET_GLIMPL_VARIABLE(opengl_version[0], v0);
      SET_GLIMPL_VARIABLE(opengl_version[1], v1);
    }
  }
  return opengl_version;
}

/* Checks if OpenGL version is at least the same or higher than
 * major.minor
 */
GLboolean CheckOpenglVersion(VALUE obj, int major, int minor)
{
	const int *version;

	version = GetOpenglVersion(obj);

	if (version[0]>major || (version[0]==major && version[1] >=minor))
		return GL_TRUE;
	else
		return GL_FALSE;
}

/* Returns supported OpenGL extensions as char* or NULL
 * if unknown (context not yet initialised etc.) The list is
 * cached for subsequent calls.
 */
const char *GetOpenglExtensions(VALUE obj)
{
  char *opengl_extensions = GET_GLIMPL_VARIABLE(opengl_extensions);
  DECL_GL_FUNC_PTR(const GLubyte *,glGetString,(GLenum name));

  LOAD_GL_FUNC(glGetString, NULL);
  if (opengl_extensions == NULL) {
    const char *estr = (const char *) fptr_glGetString(GL_EXTENSIONS);
    CHECK_GLERROR_FROM("glGetString");
    if (estr) {
      long len = strlen(estr);
      opengl_extensions = ALLOC_N(GLchar,len+1+1); /* terminating null and added space */
      strcpy(opengl_extensions,estr);
      opengl_extensions[len] = ' '; /* add space char for easy searchs */
      opengl_extensions[len+1] = '\0';
      SET_GLIMPL_VARIABLE(opengl_extensions, opengl_extensions);
    }
  }
  return opengl_extensions;
}

/* Checks if extension is supported by the current OpenGL implementation
 */
GLboolean CheckExtension(VALUE obj, const char *name)
{
	const char *extensions;
	char *name_tmp;
	long name_len;
	GLboolean res;

	extensions = GetOpenglExtensions(obj);

	if(extensions==NULL)
		return GL_FALSE;

	/* add trailing space */
	name_len = strlen(name);
	name_tmp = ALLOC_N(GLchar,name_len+1+1); /* terminating null and added space */
	strcpy(name_tmp,name);
	name_tmp[name_len] = ' '; /* add space char for search */
	name_tmp[name_len+1] = '\0';

	if (strstr(extensions,name_tmp))
		res = GL_TRUE;
	else
		res = GL_FALSE;

	xfree(name_tmp);
	return res;
}

/* wrapper for CheckOpenglVersion and CheckExtension, also used by macros
 */
GLboolean CheckVersionExtension(VALUE obj, const char *name)
{
	if (name && name[0] && name[0]>='0' && name[0]<='9') { /* GL version query */
		int major,minor;

		if (sscanf( name, "%d.%d", &major, &minor ) != 2)
				return GL_FALSE;

		return (CheckOpenglVersion(obj, major,minor));
	} else {
		return (CheckExtension(obj, name));
	}
}

void EnsureVersionExtension(VALUE obj, const char *verext)
{
  if (CheckVersionExtension(obj, verext) == GL_FALSE) {
    if (isdigit(verext[0])) {
      rb_raise(rb_eNotImpError,
        "OpenGL version %s is not available on this system",verext);
    } else {
      rb_raise(rb_eNotImpError,
        "Extension %s is not available on this system",verext);
    }
  }
}

/* Checks if given OpenGL version or extension is available
 */
static VALUE
IsAvailable(VALUE obj, VALUE arg1)
{
	char *name = NULL;
	VALUE s;
	GLboolean res;

	s = rb_funcall(arg1, rb_intern("to_s"), 0);
	name = RSTRING_PTR(s);

	res = CheckVersionExtension(obj, name);

	return GLBOOL2RUBY(res);
}

/* Checks whether non-zero buffer of type $buffer is bound
 * - this affects several functions that pass data from/to OpenGL.
 */
GLint CheckBufferBinding(VALUE obj, GLint buffer)
{
	GLint result = 0;
  DECL_GL_FUNC_PTR(void,glGetIntegerv,(GLenum pname, GLint *params));

  LOAD_GL_FUNC(glGetIntegerv, NULL);

	/* check if the buffer functionality is supported */
	switch(buffer) {
		case GL_ARRAY_BUFFER_BINDING:
		case GL_ELEMENT_ARRAY_BUFFER_BINDING:
			if (!CheckOpenglVersion(obj, 1,5))
				return 0;
			break;
		case GL_PIXEL_PACK_BUFFER_BINDING:
		case GL_PIXEL_UNPACK_BUFFER_BINDING:
			if (!CheckOpenglVersion(obj, 2,1))
				return 0;
			break;
		default:
			rb_raise(rb_eRuntimeError,"Internal Error: buffer type '%i' does not exist", buffer);
			break;
	}
	fptr_glGetIntegerv(buffer,&result);
	CHECK_GLERROR_FROM("glGetIntegerv");
	return result;
}

static VALUE
rb_gl_s_get_default_implementation( VALUE module )
{
  return g_default_glimpl;
}

static VALUE
rb_gl_s_set_default_implementation( VALUE module, VALUE glimpl )
{
  if(!rb_obj_is_kind_of(glimpl, rb_cGlimpl)){
    rb_raise(rb_eArgError, "wrong argument type %s (expected kind of Gl::Implementation)", rb_obj_classname(glimpl));
  }
  g_default_glimpl = glimpl;
  return glimpl;
}

void Init_gl(VALUE module)
{
  gl_init_glimpl(module);
	gl_init_error(rb_cGlimpl, module);
	gl_init_enums(module);
	gl_init_functions_1_0__1_1(rb_cGlimpl);
	gl_init_functions_1_2(rb_cGlimpl);
	gl_init_functions_1_3(rb_cGlimpl);
	gl_init_functions_1_4(rb_cGlimpl);
	gl_init_functions_1_5(rb_cGlimpl);
	gl_init_functions_2_0(rb_cGlimpl);
	gl_init_functions_2_1(rb_cGlimpl);
	gl_init_functions_3_0(rb_cGlimpl);
	gl_init_functions_ext_3dfx(rb_cGlimpl);
	gl_init_functions_ext_arb(rb_cGlimpl);
	gl_init_functions_ext_ati(rb_cGlimpl);
	gl_init_functions_ext_ext(rb_cGlimpl);
	gl_init_functions_ext_gremedy(rb_cGlimpl);
	gl_init_functions_ext_nv(rb_cGlimpl);
	gl_init_buffer(module);


	rb_define_method(rb_cGlimpl, "is_available?", IsAvailable, 1);
	rb_define_method(rb_cGlimpl, "is_supported?", IsAvailable, 1);
	rb_define_method(rb_cGlimpl, "extension_available?", IsAvailable, 1);
	rb_define_method(rb_cGlimpl, "extension_supported?", IsAvailable, 1);
	rb_define_method(rb_cGlimpl, "version_available?", IsAvailable, 1);
	rb_define_method(rb_cGlimpl, "version_supported?", IsAvailable, 1);


  rb_define_module_function(module, "default_implementation", rb_gl_s_get_default_implementation, 0);
  rb_define_module_function(module, "default_implementation=", rb_gl_s_set_default_implementation, 1);

  g_default_glimpl = Qnil;
  rb_global_variable(&g_default_glimpl);
}
