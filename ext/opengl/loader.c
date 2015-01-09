#include "common.h"

#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#ifdef HAVE_WINDOWS_H
#include <windows.h>
#endif

#ifdef HAVE_GL_GLX_H
#include <GL/glx.h>
#endif

void *load_gl_function(const char *name,int raise)
{
        void *func_ptr = NULL;

#if defined(__APPLE__)
        void *library = NULL;
        library = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY | RTLD_LOCAL | RTLD_FIRST);

        if (library == NULL)
                rb_raise(rb_eRuntimeError,"Can't load OpenGL library for dynamic loading");

        func_ptr = dlsym(library, name);

        if(func_ptr == NULL)
        {
                /* prepend a '_' for the Unix C symbol mangling convention */
                char *symbol_name = ALLOC_N(char, strlen(name) + 2);
                symbol_name[0] = '_';
                strcpy(symbol_name + 1, name);
                func_ptr = dlsym(library, symbol_name);
                xfree(symbol_name);
        }

        dlclose(library);

#elif HAVE_WGLGETPROCADDRESS
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
