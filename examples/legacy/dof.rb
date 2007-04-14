#
#/* Copyright (c) Mark J. Kilgard, 1994. */
#
#/*
# * (c) Copyright 1993, Silicon Graphics, Inc.
# * ALL RIGHTS RESERVED 
# * Permission to use, copy, modify, and distribute this software for 
# * any purpose and without fee is hereby granted, provided that the above
# * copyright notice appear in all copies and that both the copyright notice
# * and this permission notice appear in supporting documentation, and that 
# * the name of Silicon Graphics, Inc. not be used in advertising
# * or publicity pertaining to distribution of the software without specific,
# * written prior permission. 
# *
# * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
# * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
# * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
# * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
# * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
# * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
# * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
# * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
# * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
# * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
# * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
# * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
# * 
# * US Government Users Restricted Rights 
# * Use, duplication, or disclosure by the Government is subject to
# * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
# * (c)(1)(ii) of the Rights in Technical Data and Computer Software
# * clause at DFARS 252.227-7013 and/or in similar or successor
# * clauses in the FAR or the DOD or NASA FAR Supplement.
# * Unpublished-- rights reserved under the copyright laws of the
# * United States.  Contractor/manufacturer is Silicon Graphics,
# * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
# *
# * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
# */
#/*
# *  dof.c
# *  This program demonstrates use of the accumulation buffer to
# *  create an out-of-focus depth-of-field effect.  The teapots
# *  are drawn several times into the accumulation buffer.  The
# *  viewing volume is jittered, except at the focal point, where
# *  the viewing volume is at the same position, each time.  In
# *  this case, the gold teapot remains in focus.
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"
require "jitter"

PI_=3.14159265358979323846

#/* accFrustum()
# * The first 6 arguments are identical to the glFrustum() call.
# *  
# * pixdx and pixdy are anti-alias jitter in pixels. 
# * Set both equal to 0.0 for no anti-alias jitter.
# * eyedx and eyedy are depth-of field jitter in pixels. 
# * Set both equal to 0.0 for no depth of field effects.
# *
# * focus is distance from eye to plane in focus. 
# * focus must be greater than, but not equal to 0.0.
# *
# * Note that accFrustum() calls glTranslatef().  You will 
# * probably want to insure that your ModelView matrix has been 
# * initialized to identity before calling accFrustum().
# */
def accFrustum(left, right, bottom, top, nnear, ffar, pixdx, pixdy, eyedx, eyedy, focus)

   viewport = GL::GetDoublev(GL::VIEWPORT);
	
   xwsize = right - left;
   ywsize = top - bottom;
	
   dx = -(pixdx*xwsize/viewport[2] + eyedx*nnear/focus);
   dy = -(pixdy*ywsize/viewport[3] + eyedy*nnear/focus);
	
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GL::Frustum(left + dx, right + dx, bottom + dy, top + dy, nnear, ffar);
   GL::MatrixMode(GL::MODELVIEW);
   GL::LoadIdentity();
   GL::Translate(-eyedx, -eyedy, 0.0);
end

#/* accPerspective()
# * 
# * The first 4 arguments are identical to the gluPerspective() call.
# * pixdx and pixdy are anti-alias jitter in pixels. 
# * Set both equal to 0.0 for no anti-alias jitter.
# * eyedx and eyedy are depth-of field jitter in pixels. 
# * Set both equal to 0.0 for no depth of field effects.
# *
# * focus is distance from eye to plane in focus. 
# * focus must be greater than, but not equal to 0.0.
# *
# * Note that accPerspective() calls accFrustum().
# */
def  accPerspective(fovy, aspect, nnear, ffar, pixdx, pixdy, eyedx, eyedy, focus)
   fov2 = ((fovy*PI_) / 180.0) / 2.0;

   top = nnear / (Math::cos(fov2) / Math::sin(fov2));
   bottom = -top;

   right = top * aspect;
   left = -right;

   accFrustum(left, right, bottom, top, nnear, ffar,
               pixdx, pixdy, eyedx, eyedy, focus);
end


def myinit
    ambient = [ 0.0, 0.0, 0.0, 1.0 ];
    diffuse = [ 1.0, 1.0, 1.0, 1.0 ];
    position = [ 0.0, 3.0, 3.0, 0.0 ];
    
    lmodel_ambient = [ 0.2, 0.2, 0.2, 1.0 ];
    local_view = [ 0.0 ];

    GL::Enable(GL::DEPTH_TEST);
    GL::DepthFunc(GL::LESS);

    GL::Light(GL::LIGHT0, GL::AMBIENT, ambient);
    GL::Light(GL::LIGHT0, GL::DIFFUSE, diffuse);
    GL::Light(GL::LIGHT0, GL::POSITION, position);
    
    GL::LightModel(GL::LIGHT_MODEL_AMBIENT, lmodel_ambient);
    GL::LightModel(GL::LIGHT_MODEL_LOCAL_VIEWER, local_view);

    GL::FrontFace(GL::CW);
    GL::Enable(GL::LIGHTING);
    GL::Enable(GL::LIGHT0);
    GL::Enable(GL::AUTO_NORMAL);
    GL::Enable(GL::NORMALIZE);

    GL::MatrixMode(GL::MODELVIEW);
    GL::LoadIdentity();

    GL::ClearColor(0.0, 0.0, 0.0, 0.0);
    GL::ClearAccum(0.0, 0.0, 0.0, 0.0);
end

def renderTeapot (x, y, z, ambr, ambg, ambb, difr, difg, difb, specr, specg, specb, shine)
    GL::PushMatrix();
    GL::Translate(x, y, z);
    mat = []
    mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;	
    GL::Material(GL::FRONT, GL::AMBIENT, mat);
    mat[0] = difr; mat[1] = difg; mat[2] = difb;	
    GL::Material(GL::FRONT, GL::DIFFUSE, mat);
    mat[0] = specr; mat[1] = specg; mat[2] = specb;
    GL::Material(GL::FRONT, GL::SPECULAR, mat);
    GL::Material(GL::FRONT, GL::SHININESS, shine*128.0);
    GLUT::SolidTeapot(0.5);
    GL::PopMatrix();
end

#/*  display() draws 5 teapots into the accumulation buffer 
# *  several times; each time with a jittered perspective.
# *  The focal point is at z = 5.0, so the gold teapot will 
# *  stay in focus.  The amount of jitter is adjusted by the
# *  magnitude of the accPerspective() jitter; in this example, 0.33.
# *  In this example, the teapots are drawn 8 times.  See jitter.h
# */
display = proc {
    viewport = GL::GetDoublev(GL::VIEWPORT);
    GL::Clear(GL::ACCUM_BUFFER_BIT);

    for jitter in 0...8
	GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
	accPerspective(45.0, 
		 viewport[2]/ viewport[3], 
		1.0, 15.0, 0.0, 0.0,
		0.33*$j8[jitter][0], 0.33*$j8[jitter][1], 5.0);
#/*	ruby, gold, silver, emerald, and cyan teapots	*/
	renderTeapot(-1.1, -0.5, -4.5, 0.1745, 0.01175, 0.01175,
	    0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6);
	renderTeapot(-0.5, -0.5, -5.0, 0.24725, 0.1995, 0.0745,
	    0.75164, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 0.4);
	renderTeapot(0.2, -0.5, -5.5, 0.19225, 0.19225, 0.19225,
	    0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4);
	renderTeapot(1.0, -0.5, -6.0, 0.0215, 0.1745, 0.0215, 
	    0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6);
	renderTeapot(1.8, -0.5, -6.5, 0.0, 0.1, 0.06, 0.0, 0.50980392, 
	    0.50980392, 0.50196078, 0.50196078, 0.50196078, 0.25);
	GL::Accum(GL::ACCUM, 0.125);
    end

    GL::Accum(GL::RETURN, 1.0);
    GL::Flush();
}

myReshape = proc {|w, h|
    GL::Viewport(0, 0, w, h);
}

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, depth buffer, and handle input events.
# */
    GLUT::Init();
    GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::ACCUM | GLUT::DEPTH);
    GLUT::CreateWindow()
    myinit();
    GLUT::ReshapeFunc(myReshape);
    GLUT::DisplayFunc(display);
    GLUT::MainLoop();

