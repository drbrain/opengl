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

static struct glimpl *
rb_glimpl_struct( VALUE self )
{
  return DATA_PTR(self);
}

static void *load_gl_function(VALUE self, const char *name, int raise)
{
  struct glimpl *this = rb_glimpl_struct(self);
  void *func_ptr;

  if( this->fptr_GetProcAddress ){
    func_ptr = this->fptr_GetProcAddress(name);

  } else {
    func_ptr = dlsym(this->dl, name);

    if(func_ptr == NULL)
    {
            /* prepend a '_' for the Unix C symbol mangling convention */
            char *symbol_name = ALLOC_N(char, strlen(name) + 2);
            symbol_name[0] = '_';
            strcpy(symbol_name + 1, name);
            func_ptr = dlsym(this->dl, symbol_name);
            xfree(symbol_name);
    }
  }

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

static void rb_glimpl_free( struct glimpl *this )
{
  if(this->dl) dlclose(this->dl);
  this->dl = NULL;
  xfree(this);
}

static VALUE
rb_glimpl_s_open(int argc, VALUE *argv, VALUE klass)
{
  VALUE self;
  struct glimpl *this;
  VALUE dl_name;
  VALUE proc_address_function;
  char *p_dl_name;

  rb_scan_args(argc, argv, "11", &dl_name, &proc_address_function);

  p_dl_name = StringValueCStr(dl_name);

  self = Data_Make_Struct( klass, struct glimpl, rb_glimpl_mark, rb_glimpl_free, this );

  this->error_checking = Qtrue;
  this->inside_begin_end = Qfalse;
  this->load_gl_function = load_gl_function;

  this->dl = dlopen(p_dl_name, RTLD_LAZY | RTLD_LOCAL
#if defined(RTLD_FIRST)
    | RTLD_FIRST
#endif
  );
  if (this->dl == NULL)
    rb_raise(rb_eArgError,"Can't load OpenGL library %s", p_dl_name);

  if( NIL_P(proc_address_function) ){
    this->fptr_GetProcAddress = NULL;
  } else {
    char *p_proc_address_function = StringValueCStr(proc_address_function);
    this->fptr_GetProcAddress = dlsym(this->dl, p_proc_address_function);
    if (this->fptr_GetProcAddress == NULL)
      rb_raise(rb_eNotImpError,"Function %s is not available on this system",p_proc_address_function);
  }

  return self;
}

static VALUE rb_glimpl_close(VALUE self)
{
  struct glimpl *this = rb_glimpl_struct(self);
  if(this->dl) dlclose(this->dl);
  this->dl = NULL;
  return Qnil;
}

void gl_init_glimpl(VALUE module)
{
  rb_cGlimpl = rb_define_class_under(module, "Implementation", rb_cObject);

  rb_undef_alloc_func(rb_cGlimpl);
  rb_define_singleton_method(rb_cGlimpl, "open", rb_glimpl_s_open, -1);
  rb_define_method(rb_cGlimpl, "close", rb_glimpl_close, 0);
}
