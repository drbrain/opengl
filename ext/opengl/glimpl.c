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

VALUE rb_cGlimpl;
VALUE g_default_glimpl;

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

static void
rb_glimpl_mark( struct glimpl *this )
{
  int i;
  rb_gc_mark(this->current_sel_buffer);
  rb_gc_mark(this->current_feed_buffer);
  rb_gc_mark(this->Vertex_ptr);
  rb_gc_mark(this->Normal_ptr);
  rb_gc_mark(this->Color_ptr);
  rb_gc_mark(this->Index_ptr);
  rb_gc_mark(this->TexCoord_ptr);
  rb_gc_mark(this->EdgeFlag_ptr);
  rb_gc_mark(this->FogCoord_ptr);
  rb_gc_mark(this->SecondaryColor_ptr);
  rb_gc_mark(this->error_checking);
  rb_gc_mark(this->inside_begin_end);

  for (i=0;i<_MAX_VERTEX_ATTRIBS;i++){
    rb_gc_mark(this->VertexAttrib_ptr[i]);
  }
}

static VALUE rb_glimpl_s_open(VALUE klass)
{
  VALUE self;
  struct glimpl *this;

  self = Data_Make_Struct( klass, struct glimpl, rb_glimpl_mark, -1, this );

  this->error_checking = Qtrue;
  this->inside_begin_end = Qfalse;

  return self;
}

static VALUE rb_glimpl_close(VALUE self)
{
  return self;
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

void gl_init_glimpl(VALUE module)
{
  rb_cGlimpl = rb_define_class_under(module, "Implementation", rb_cObject);

  rb_undef_alloc_func(rb_cGlimpl);
  rb_define_singleton_method(rb_cGlimpl, "open", rb_glimpl_s_open, 0);
  rb_define_method(rb_cGlimpl, "close", rb_glimpl_close, 0);


  rb_define_module_function(module, "default_implementation", rb_gl_s_get_default_implementation, 0);
  rb_define_module_function(module, "default_implementation=", rb_gl_s_set_default_implementation, 1);

  g_default_glimpl = rb_funcall(rb_cGlimpl, rb_intern("open"), 0);
  rb_global_variable(&g_default_glimpl);
}
