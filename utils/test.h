/*
 * A Sample .h file to test mkwrap.rb on.  This has some test cases that
 * have given trouble in the past.
 */

/* These are easy ones */
extern void APIENTRY glutCopyColormap(int win);
extern int APIENTRY glutFoo(void (* foo)(int));

/*
 * The following are from the mac glut.h
 *   glutSetColor:   missing var name for first parameter
 *   glutCreateMenu: void (*) in param list
 */
extern void APIENTRY glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);
extern int APIENTRY glutCreateMenu(void (*)(int));
