/* This file is just an example to see what must
 * be done to handle glut callbacks in mkwrap.rb
 *
 * It may be added as developer documentation ?
 */

/*
 * 1/
 * Follows Yoshi's code (modulo WINDOW_CALLBACK_SETUP preprocessed)
 * for glutDisplayFunc.
 * Note that 'callId' is the same as 'rb_intern("call")'.
 * See 2/ bellow for my 'explanation' and my changes.
 */

static VALUE DisplayFunc = Qnil;

static void glut_DisplayFuncCallback(void)
{
	VALUE func;
	func = rb_ary_entry(DisplayFunc, glutGetWindow());
	if (!NIL_P(func))
		rb_funcall(func, callId, 0);
}

static VALUE
glut_DisplayFunc(obj,arg1)
VALUE obj,arg1;
{
	int win;
	if (!rb_obj_is_kind_of(arg1,rb_cProc) && !((VALUE)(arg1) == Qnil))
		rb_raise(rb_eTypeError, "GLUT.%s:%s","DisplayFunc",
				rb_class2name(rb_class_of((VALUE)(arg1))));
	win = glutGetWindow();
	if (win == 0)
		rb_raise(rb_eRuntimeError,
				"GLUT.%s needs current window",
				"DisplayFunc");
	rb_ary_store(DisplayFunc, win, arg1);
	glutDisplayFunc(glut_DisplayFuncCallback);
	return Qnil;
}

/*
 * 2/
 * Follows my version of Yoshi's code (still for glutDisplayFunc).
 * Other callbacks can be handled in the same way.
 */

/* display_callbacks is a ruby array which maps
 * a window identifier (returned by glutGetWindow) to
 * a (ruby-side) callback, i.e. a Proc object.
 */
static VALUE display_callbacks = Qnil;

/* call_display_callback issues a rb_intern("call")
 * to the _correct_ Proc callback (which has been set
 * by the ruby version of glutDisplayFunc, i.e.
 * rbgl_glutDisplayFunc, see bellow).
 * _correct_ means the one which corresponds to
 * the current window identifier in display_callbacks.
 */
static void
call_display_callback (void)
{
	/* find the approriate callback */
	VALUE callback = rb_ary_entry (display_callbacks, glutGetWindow ());
	/* call it */
	if (!NIL_P (callback)) rb_funcall (callback, callId, 0);
}

/* The following function is exposed in the bindings as
 * glutDisplayCallback.
 * It sets the callback in the display_callbacks array
 * and registers call_display_callback as the c side callback.
 * In Yoshi's code (and thus here), callback is a Proc object.
 * In rubygl, it's a Block which is turned into a Proc.
 * FIXME : I remove the type checking and the check on the
 * return value of glutGetWindow. Is it a good idea ?
 */
static VALUE
rbgl_glutDisplayFunc (VALUE self, VALUE callback)
{
	/* set the ruby callback in the display_callbacks array */
	rb_ary_store ( display_callbacks, glutGetWindow (), callback);
	/* register call_display_callback as the c callback */
	/* FIXME I believe it can be done only once, at initialization
	 *       (with callId).
	glutDisplayFunc (call_display_callback);
	return Qnil;
}

