#include "common.h"

struct buffer {
  VALUE glimpl;
  void *ptr;
  GLsizeiptr len;
  GLenum target;
};

static void
buffer_mark(void *ptr)
{
  struct buffer *this = ptr;
  rb_gc_mark(this->glimpl);
}

static void
buffer_free(void *ptr) {
  struct buffer *buf = ptr;
  VALUE obj = buf->glimpl;
  DECL_GL_FUNC_PTR(GLboolean,glUnmapBuffer,(GLenum));
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
	{ buffer_mark, buffer_free, buffer_memsize, },
};

VALUE
rb_gl_buffer_s_map(int argc, VALUE *argv, VALUE klass)
{
  VALUE _target;
  VALUE _access;
  VALUE obj;
  struct buffer *buf;
  DECL_GL_FUNC_PTR(GLvoid *,glMapBuffer,(GLenum,GLenum));

  rb_scan_args(argc, argv, "21", &_target, &_access, &obj);
  if(NIL_P(obj)){
    obj = g_default_glimpl;
  } else if(!rb_obj_is_kind_of(obj, rb_cGlimpl)){
    rb_raise(rb_eArgError, "wrong argument type %s (expected kind of Gl::Implementation)", rb_obj_classname(obj));
  }

	buf = ALLOC(struct buffer);
	LOAD_GL_FUNC(glMapBuffer, "1.5");

	buf->target = RUBY2GLENUM(_target);
	buf->len = 0;
  buf->glimpl = obj;

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

	return SIZET2NUM((size_t)buf->ptr);
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

	length = NUM2SIZET(_length);

	if (NIL_P(_offset)) {
		offset = 0;
	} else {
		offset = NUM2SIZET(_offset);
	}

	if (buf->len != 0 && length + offset > buf->len)
		rb_raise(rb_eArgError, "read to %lu past end of buffer %lu",
				(unsigned long)(length + offset), (unsigned long)buf->len);

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
  VALUE obj;
  DECL_GL_FUNC_PTR(GLboolean,glUnmapBuffer,(GLenum));

  TypedData_Get_Struct(self, struct buffer, &buffer_type, buf);
  obj = buf->glimpl;

  LOAD_GL_FUNC(glUnmapBuffer, "1.5");

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
		offset = NUM2SIZET(_offset);
	}

	if (buf->len != 0 && length + offset > buf->len)
		rb_raise(rb_eArgError, "write to %lu past end of buffer %lu",
				(unsigned long)(length + offset), (unsigned long)buf->len);

	memcpy((char *)buf->ptr + offset, RSTRING_PTR(_data), RSTRING_LEN(_data));

	return self;
}

void
gl_init_buffer(VALUE module) {
	VALUE cBuffer = rb_define_class_under(module, "Buffer", rb_cObject);

	rb_undef_alloc_func(cBuffer);
	rb_define_singleton_method(cBuffer, "map", rb_gl_buffer_s_map, -1);

	rb_define_method(cBuffer, "addr", rb_gl_buffer_addr, 0);
	rb_define_method(cBuffer, "length", rb_gl_buffer_length, 0);
	rb_define_method(cBuffer, "read", rb_gl_buffer_read, -1);
	rb_define_method(cBuffer, "target", rb_gl_buffer_target, 0);
	rb_define_method(cBuffer, "unmap", rb_gl_buffer_unmap, 0);
	rb_define_method(cBuffer, "write", rb_gl_buffer_write, -1);
}

