/*
 * Copyright (C) 2006 Peter McLain
 * All rights reserved.
 * See MIT-LICENSE for permissions.
 */
%module GLUT

%module GL
#ifdef SWIGMAC
%header %{
#include "/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
%}
#else
%header %{
#include <GL/glut.h>
%}
#endif

%include "glut_init.i"
%include "glut_callbacks.i"

#ifdef SWIGMAC
%include "/System/Library/Frameworks/GLUT.framework/Headers/glut.h"
#else
%include <GL/glut.h>
#endif

