/*
 * Copyright (C) 2006 Peter McLain
 * All rights reserved.
 * See MIT-LICENSE for permissions.
 */
%wrapper %{

/*
 * This set of code adds untyped wrappers in addition to the type-specific
 * calls.  E.g., we add a glMaterial(...) as a nice convenience beyond the
 * type-specific functions glMaterialiv(...), glMaterialfv(...).
 */
static VALUE gl_Material(obj, arg1, arg2, arg3)
    VALUE obj, arg1, arg2, arg3;
{
    GLenum face;
    GLenum pname;
    GLfloat params[4];

    memset(params, 0x0, sizeof(GLfloat[4]));
    face = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if (TYPE(arg3) == T_ARRAY) {
        ary2cflt(arg3,params,4);
        glMaterialfv(face,pname,params);
    } else {
        params[0] = (GLfloat)NUM2DBL(arg3);
        glMaterialf(face,pname,params[0]);
    }
    return Qnil;
}

static VALUE gl_Light(obj, arg1, arg2, arg3)
    VALUE obj, arg1, arg2, arg3;
{
    GLenum light;
    GLenum pname;
    GLfloat params[4];
    memset(params, 0x0, sizeof(GLfloat[4]));
    light = (GLenum)NUM2INT(arg1);
    pname = (GLenum)NUM2INT(arg2);
    if (TYPE(arg3) == T_ARRAY) {
        ary2cflt(arg3,params,4);
        glLightfv(light,pname,params);
    } else {
        params[0] = (GLfloat)NUM2DBL(arg3);
        glLightf(light,pname,params[0]);
    }
    return Qnil;
}

/* RxINC: Why is one VALUE VALUE VALUE rather than the std? */
static VALUE gl_LightModel(obj, arg1, arg2)
    VALUE obj, arg1, arg2;
{
    GLenum pname;
    GLfloat params[4];
    memset(params, 0x0, sizeof(GLfloat[4]));
    pname = (GLenum)NUM2INT(arg1);
    if (TYPE(arg2) == T_ARRAY) {
        ary2cflt(arg2,params,4);
        glLightModelfv(pname,params);
    } else {
        params[0] = (GLfloat)NUM2DBL(arg2);
        glLightModelf(pname,params[0]);
    }
    return Qnil;
}

/*
 * Generic untyped method exposed in ruby.  Translates to the appropriate
 * glVertex2d() form and calls into the appropriate SWIG wraper.
 */
static VALUE gl_Vertex(argc, argv, obj)
    int argc; VALUE *argv; VALUE obj;
{
    VALUE args[4];
    struct RArray *ary;
    switch (rb_scan_args(argc, argv, "13", &args[0], &args[1], &args[2], &args[3])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
            ary = RARRAY(args[0]);
            switch (ary->len) {
            case 2:
                _wrap_glVertex2d(argc, argv, obj);
                break;
            case 3:
                _wrap_glVertex3d(argc, argv, obj);
                break;
            case 4:
                _wrap_glVertex4d(argc, argv, obj);
                break;
            default:
                rb_raise(rb_eRuntimeError, "glVertex vertex num error!:%d", ary->len);
            }
      } else
          rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
      break;

    case 2:
        _wrap_glVertex2d(argc, argv, obj);
        break;
    case 3:
        _wrap_glVertex3d(argc, argv, obj);
        break;
    case 4:
        _wrap_glVertex4d(argc, argv, obj);
        break;
    }
    return Qnil;
}

VALUE gl_Normal(argc, argv, obj)
    int argc; VALUE *argv; VALUE obj;
{
    int num;
    VALUE args[3];
    struct RArray* ary;
    switch (num = rb_scan_args(argc, argv, "12", &args[0], &args[1], &args[2])) {
    case 1:
        if (TYPE(args[0]) == T_ARRAY) {
            ary = RARRAY(args[0]);
            switch (ary->len) {
            case 3:
                _wrap_glNormal3d(argc, argv, obj);
                break;
            default:
                rb_raise(rb_eArgError, "array length:%d", ary->len);
            }
        } else
            rb_raise(rb_eTypeError, "type mismatch:%s", rb_class2name(CLASS_OF(args[0])));
        break;
    case 3:
        _wrap_glNormal3d(argc, argv, obj);
        break;
    default:
        rb_raise(rb_eArgError, "arg length:%d",num);
    }
    return Qnil;
}

%}

%init %{
/*
 * Should we rename gl_Vertex et. al. to _wrap_glVertex?  gl_Vertex
 * is Yoshi style names and _wrap_glVertex is swig style names.  Perhaps it
 * is best to keep the names different, so we can tell them apart?
 *
 * RxInc: need to document this in any case...
 */
rb_define_module_function(mGL, "glMaterial", gl_Material, 3);
rb_define_module_function(mGL, "glLight", gl_Light, 3);
rb_define_module_function(mGL, "glLightModel", gl_LightModel, 2);
rb_define_module_function(mGL, "glLightModel", gl_LightModel, 2);
rb_define_module_function(mGL, "glVertex", gl_Vertex, -1);
rb_define_module_function(mGL, "glNormal", gl_Normal, -1);

/* This is just an alias so that we get nice ruby behavior */
/* RxINC: can we use a swig %alias? */
/* rb_define_module_function(mGL, "Translated", gl_Translated, 3);*/
rb_define_module_function(mGL, "glTranslate", _wrap_glTranslated, -1);
rb_define_module_function(mGL, "glScale", _wrap_glScaled, -1);
rb_define_module_function(mGL, "glColor", _wrap_glColor3d, -1);
%}
