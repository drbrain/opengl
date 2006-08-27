/*
 * Copyright (C) 2006 Peter McLain
 * All rights reserved.
 * See MIT-LICENSE for permissions.
 */
%module GL
#ifdef SWIGMAC
%header %{
#include "/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
%}
#else
%header %{
#include <GL/gl.h>
%}
#endif

/* This is what SWIG parses to generate the wrapper */
#ifdef SWIGMAC
%include "/System/Library/Frameworks/OpenGL.framework/Headers/gl.h"
#else
%include "GL/gl.h"
#endif

%include "gl_untyped.i"


