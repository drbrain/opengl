#ifndef _GLIMPL_H_
#define _GLIMPL_H_

#ifndef GLFUNC_MAGIC_START
#include "fptr_struct.h"
#endif

#define GET_GLIMPL_VARIABLE(_name_) \
  glimpl._name_

#define SET_GLIMPL_VARIABLE(_name_,_val_) \
  glimpl._name_ = (_val_)

struct glimpl {
  struct glfunc_ptrs glfuncs;

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
  VALUE VertexAttrib_ptr[];
};

extern struct glimpl glimpl;


#endif /* _GLIMPL_H_ */
