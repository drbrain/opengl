#ifndef _GLIMPL_H_
#define _GLIMPL_H_

#ifndef GLFUNC_MAGIC_START
#include "fptr_struct.h"
#endif

#define GET_GLIMPL_VARIABLE(_name_) \
  (((struct glimpl *)DATA_PTR(obj))->_name_)

#define SET_GLIMPL_VARIABLE(_name_,_val_) \
  ((struct glimpl *)DATA_PTR(obj))->_name_ = (_val_)

/* at least GL_MAX_VERTEX_ATTRIBS - usually 16 or 32 on today's high-end cards */
#define _MAX_VERTEX_ATTRIBS 64

extern VALUE g_default_glimpl;

struct glimpl {
  struct glfunc_ptrs glfuncs;

  int opengl_version[2]; /* major, minor */
  char *opengl_extensions;

  void * (* load_gl_function)(VALUE self, const char *name,int raise);

  VALUE current_feed_buffer;
  VALUE current_sel_buffer;
  VALUE Vertex_ptr;
  VALUE Normal_ptr;
  VALUE Color_ptr;
  VALUE Index_ptr;
  VALUE TexCoord_ptr;
  VALUE EdgeFlag_ptr;
  VALUE FogCoord_ptr; /* OpenGL 1.4 */
  VALUE SecondaryColor_ptr; /* OpenGL 1.4 */
  VALUE VertexAttrib_ptr[_MAX_VERTEX_ATTRIBS];

  VALUE error_checking;
  VALUE inside_begin_end;

  void *dl;
  void * (APIENTRY * fptr_GetProcAddress)(const char *name);
};


#endif /* _GLIMPL_H_ */
