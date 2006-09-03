/*
 * A Sample .h file to test mkwrap.rb on.  This has some test cases that
 * have given trouble in the past.
 */

/* This one is an easy one and is just here to test the test code... */
extern void APIENTRY glutCopyColormap(int win);

/* From the mac glut.h...missing var name for first parameter */'
extern void APIENTRY glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);
