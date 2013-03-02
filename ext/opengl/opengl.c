#include "common.h"

void Init_gl(void);
void Init_glut(void);
void Init_glut_callbacks(void);
void Init_glut_ext(void);

DLLEXPORT void Init_opengl() {
	Init_gl();
	Init_glut();
	Init_glut_callbacks();
	Init_glut_ext();

}
