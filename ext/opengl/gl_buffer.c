#include "common.h"

static GLvoid * (APIENTRY * fptr_glMapBuffer)(GLenum,GLenum);
static GLboolean (APIENTRY * fptr_glUnmapBuffer)(GLenum);

struct buffer {
  GLenum target;
  void *ptr;
  GLsizeiptr len;
};

static void
buffer_free(void *ptr) {
  struct buffer *buf = ptr;
  LOAD_GL_FUNC(glUnmapBuffer, "1.5");

  if (buf->ptr != NULL)
    fptr_glUnmapBuffer(buf->target);
}

static size_t
buffer_memsize(const void *ptr) {
  const struct buffer *buf = ptr;
  return sizeof(struct buffer) + (size_t)buf->len;
}

static const rb_data_type_t buffer_type = {
  "OpenGL/buffer",
  { NULL, buffer_free, buffer_memsize, },
};

VALUE
rb_gl_buffer_s_map(VALUE klass, VALUE _target, VALUE _access) {
  struct buffer *buf = ALLOC(struct buffer);
  LOAD_GL_FUNC(glMapBuffer, "1.5");

  buf->target = RUBY2GLENUM(_target);
  buf->len    = 0;

  buf->ptr = fptr_glMapBuffer(buf->target, RUBY2GLENUM(_access));

  if (buf->ptr == NULL) {
    xfree(buf);
    CHECK_GLERROR_FROM("glMapBuffer");
  }

  return TypedData_Wrap_Struct(klass, &buffer_type, buf);
}

static VALUE
rb_gl_buffer_addr(VALUE self) {
  struct buffer *buf;

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  return ULONG2NUM((unsigned long)buf->ptr);
}

static VALUE
rb_gl_buffer_length(VALUE self) {
  struct buffer *buf;

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  return RETCONV_GLsizeiptr(buf->len);
}

static VALUE
rb_gl_buffer_read(int argc, VALUE *argv, VALUE self) {
  struct buffer *buf;
  VALUE _length, _offset;
  GLsizeiptr offset, length;

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  rb_scan_args(argc, argv, "02", &_length, &_offset);

  if (buf->len == 0 && NIL_P(_length))
    rb_raise(rb_eArgError, "length must be provided for unbounded buffer");

  length = NUM2ULONG(_length);

  if (NIL_P(_offset)) {
    offset = 0;
  } else {
    offset = NUM2ULONG(_offset);
  }

  if (buf->len != 0 && length + offset > buf->len)
    rb_raise(rb_eArgError, "read to %ld past end of buffer %ld",
        length + offset, buf->len);

  return rb_str_new((char *)buf->ptr + offset, length);
}

static VALUE
rb_gl_buffer_target(VALUE self) {
  struct buffer *buf;

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  return RETCONV_GLenum(buf->target);
}

static VALUE
rb_gl_buffer_unmap(VALUE self) {
  struct buffer *buf;
  LOAD_GL_FUNC(glUnmapBuffer, "1.5");

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  if (!buf->ptr)
    return self;

  fptr_glUnmapBuffer(buf->target);

  CHECK_GLERROR_FROM("glUnmapBuffer");

  buf->ptr = NULL;
  buf->len = 0;
  buf->target = 0;

  return self;
}

static VALUE
rb_gl_buffer_write(int argc, VALUE *argv, VALUE self) {
  struct buffer *buf;
  VALUE _data, _offset;
  GLsizeiptr offset;
  long length;

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);

  if (!buf->ptr)
    rb_raise(rb_eArgError, "write to unmapped buffer");

  rb_scan_args(argc, argv, "11", &_data, &_offset);

  if (NIL_P(_data))
    rb_raise(rb_eArgError, "cannot write nil to buffer");

  _data = rb_String(_data);

  length = RSTRING_LEN(_data);

  if (NIL_P(_offset)) {
    offset = 0;
  } else {
    offset = NUM2ULONG(_offset);
  }

  if (buf->len != 0 && length + offset > buf->len)
    rb_raise(rb_eArgError, "write to %ld past end of buffer %ld",
        length + offset, buf->len);

  memcpy((char *)buf->ptr + offset, RSTRING_PTR(_data), RSTRING_LEN(_data));

  return self;
}

void
gl_init_buffer(void) {
  VALUE mOpenGL = rb_path2class("OpenGL");
  VALUE cBuffer = rb_define_class_under(mOpenGL, "Buffer", rb_cObject);

  rb_undef_alloc_func(cBuffer);
  rb_define_singleton_method(cBuffer, "map", rb_gl_buffer_s_map, 2);

  rb_define_method(cBuffer, "addr", rb_gl_buffer_addr, 0);
  rb_define_method(cBuffer, "length", rb_gl_buffer_length, 0);
  rb_define_method(cBuffer, "read", rb_gl_buffer_read, -1);
  rb_define_method(cBuffer, "target", rb_gl_buffer_target, 0);
  rb_define_method(cBuffer, "unmap", rb_gl_buffer_unmap, 0);
  rb_define_method(cBuffer, "write", rb_gl_buffer_write, -1);
}

