#include "common.h"

void Init_gl(VALUE);

void Init_opengl() {
	VALUE module = rb_define_module("Gl");

	Init_gl(module);
}
