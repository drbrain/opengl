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

static VALUE module;

void gl_init_enums(VALUE);
void gl_init_functions_1_0__1_1(VALUE);
void gl_init_functions_1_2(VALUE);
void gl_init_functions_1_3(VALUE);
void gl_init_functions_1_4(VALUE);
void gl_init_functions_1_5(VALUE);
void gl_init_functions_2_0(VALUE);
void gl_init_functions_2_1(VALUE);
void gl_init_functions_ext_arb(VALUE);
void gl_init_functions_ext_ati(VALUE);
void gl_init_functions_ext_ext(VALUE);
void gl_init_functions_ext_gremedy(VALUE);
void gl_init_functions_ext_nv(VALUE);


static int opengl_version[2]; /* major, minor */
static char *opengl_extensions = NULL;

/* Returns current OpenGL version as major, minor or 0,0 if
 * unknown (context not yet initialised etc.) The version is
 * cached for subsequent calls.
 */
const int *GetOpenglVersion(void)
{
	if (opengl_version[0]==0) { /* not cached, query */
		const char *vstr = (const char *) glGetString(GL_VERSION);
		CHECK_GLERROR
    if (vstr)
			sscanf( vstr, "%d.%d", &opengl_version[0], &opengl_version[1] );
	}
	return opengl_version;
}

/* Checks if OpenGL version is at least the same or higher than
 * major.minor
 */
GLboolean CheckOpenglVersion(int major, int minor)
{
	const int *version;

	version = GetOpenglVersion();

	if (version[0]>major || (version[0]==major && version[1] >=minor))
		return GL_TRUE;
	else
		return GL_FALSE;
}

/* Returns supported OpenGL extensions as char* or NULL
 * if unknown (context not yet initialised etc.) The list is
 * cached for subsequent calls.
 */
const char *GetOpenglExtensions(void)
{
	if (opengl_extensions == NULL) {
		const char *estr = (const char *) glGetString(GL_EXTENSIONS);
		CHECK_GLERROR
    if (estr) {
			int len = strlen(estr);
			opengl_extensions = ALLOC_N(GLchar,len+1+1); /* terminating null and added space */
			strcpy(opengl_extensions,estr);
			opengl_extensions[len] = ' '; /* add space char for easy searchs */
			opengl_extensions[len+1] = '\0';
		}
	}
	return opengl_extensions;	
}

/* Checks if extension is supported by the current OpenGL implementation
 */
GLboolean CheckExtension(const char *name)
{
	const char *extensions;
	char *name_tmp;
	int name_len;
	GLboolean res;
	
	extensions = GetOpenglExtensions();
	
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

/* Checks if given OpenGL version or extension is available
 */
static VALUE
IsAvailable(obj,arg1)
VALUE obj,arg1;
{
	char *name = NULL;
	VALUE s;

	s = rb_funcall(arg1, rb_intern("to_s"),0);
	name = RSTRING(s)->ptr;

	if (name && name[0] && name[0]>='0' && name[0]<='9') { /* GL version query */
		int major,minor;

		if (sscanf( name, "%d.%d", &major, &minor ) != 2)
				return Qfalse;
	
		if (CheckOpenglVersion(major,minor)==1)
			return Qtrue;
		else
			return Qfalse;
	} else {
		GLboolean res;
		
		res = CheckExtension(name);
		if (res==GL_TRUE)
			return Qtrue;
		else
			return Qfalse;
	}
}

/* Checks whether non-zero buffer of type $buffer is bound
 * - this affects several functions that pass data from/to OpenGL.
 */
GLint CheckBufferBinding(GLint buffer)
{
	GLint result = 0;
	
	/* check if the buffer functionality is supported */
	switch(buffer) {
		case GL_ARRAY_BUFFER_BINDING:
		case GL_ELEMENT_ARRAY_BUFFER_BINDING:
			if (!CheckOpenglVersion(1,5))
				return 0;
			break;
		case GL_PIXEL_PACK_BUFFER_BINDING:
		case GL_PIXEL_UNPACK_BUFFER_BINDING:
			if (!CheckOpenglVersion(2,1))
				return 0;
			break;
		default:
			rb_raise(rb_eRuntimeError,"Internal Error: buffer type '%i' does not exist", buffer);
			break;
	}
	glGetIntegerv(buffer,&result);
	CHECK_GLERROR
	return result;
}

DLLEXPORT void Init_gl()
{
	module = rb_define_module("Gl");
	gl_init_error(module);
	gl_init_enums(module);
	gl_init_functions_1_0__1_1(module);
	gl_init_functions_1_2(module);
	gl_init_functions_1_3(module);
	gl_init_functions_1_4(module);
	gl_init_functions_1_5(module);
	gl_init_functions_2_0(module);
	gl_init_functions_2_1(module);
	gl_init_functions_ext_arb(module);
	gl_init_functions_ext_ati(module);
	gl_init_functions_ext_ext(module);
	gl_init_functions_ext_gremedy(module);
	gl_init_functions_ext_nv(module);

	rb_define_module_function(module, "is_available?", IsAvailable, 1);
}
