/*
 * A Sample .h file to test mkwrap.rb on.  This has some test cases that
 * have given trouble in the past.
 */

/* This one is an easy one and is just here to test the test code... */
extern void APIENTRY glutCopyColormap(int win);

/*
 * The following are from the mac glut.h
 *   glutSetColor:   missing var name for first parameter
 *   glutCreateMenu: void (*) in param list
 */
extern void APIENTRY glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);
extern int APIENTRY glutCreateMenu(void (*)(int));
