#/*
# * Copyright (c) 1993-1997, Silicon Graphics, Inc.
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
# * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
# */
#
#/*  accpersp.c
# *  Use the accumulation buffer to do full-scene antialiasing
# *  on a scene with perspective projection, using the special
# *  routines accFrustum() and accPerspective().
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"


$LOAD_PATH.push(File.dirname($0))  # Find jitter in script directory

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

#/*  Initialize lighting and other values.
# */
def init
   mat_ambient = [ 1.0, 1.0, 1.0, 1.0 ];
   mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
   light_position = [ 0.0, 0.0, 10.0, 1.0 ];
   lm_ambient = [ 0.2, 0.2, 0.2, 1.0 ];

   GL::Material(GL::FRONT, GL::AMBIENT, mat_ambient);
   GL::Material(GL::FRONT, GL::SPECULAR, mat_specular);
   GL::Material(GL::FRONT, GL::SHININESS, 50.0);
   GL::Light(GL::LIGHT0, GL::POSITION, light_position);
   GL::LightModel(GL::LIGHT_MODEL_AMBIENT, lm_ambient);
    
   GL::Enable(GL::LIGHTING);
   GL::Enable(GL::LIGHT0);
   GL::Enable(GL::DEPTH_TEST);
   GL::ShadeModel(GL::FLAT);

   GL::ClearColor(0.0, 0.0, 0.0, 0.0);
   GL::ClearAccum(0.0, 0.0, 0.0, 0.0);
end

def displayObjects
   torus_diffuse = [ 0.7, 0.7, 0.0, 1.0 ];
   cube_diffuse = [ 0.0, 0.7, 0.7, 1.0 ];
   sphere_diffuse = [ 0.7, 0.0, 0.7, 1.0 ];
   octa_diffuse = [ 0.7, 0.4, 0.4, 1.0 ];
    
   GL::PushMatrix();
   GL::Translate(0.0, 0.0, -5.0); 
   GL::Rotate(30.0, 1.0, 0.0, 0.0);

   GL::PushMatrix();
   GL::Translate(-0.80, 0.35, 0.0); 
   GL::Rotate(100.0, 1.0, 0.0, 0.0);
   GL::Material(GL::FRONT, GL::DIFFUSE, torus_diffuse);
   GLUT::SolidTorus(0.275, 0.85, 16, 16);
   GL::PopMatrix();

   GL::PushMatrix();
   GL::Translate(-0.75, -0.50, 0.0); 
   GL::Rotate(45.0, 0.0, 0.0, 1.0);
   GL::Rotate(45.0, 1.0, 0.0, 0.0);
   GL::Material(GL::FRONT, GL::DIFFUSE, cube_diffuse);
   GLUT::SolidCube(1.5);
   GL::PopMatrix();

   GL::PushMatrix();
   GL::Translate(0.75, 0.60, 0.0); 
   GL::Rotate(30.0, 1.0, 0.0, 0.0);
   GL::Material(GL::FRONT, GL::DIFFUSE, sphere_diffuse);
   GLUT::SolidSphere(1.0, 16, 16);
   GL::PopMatrix();

   GL::PushMatrix();
   GL::Translate(0.70, -0.90, 0.25); 
   GL::Material(GL::FRONT, GL::DIFFUSE, octa_diffuse);
   GLUT::SolidOctahedron();
   GL::PopMatrix();

   GL::PopMatrix();
end

ACSIZE=8

display = proc {
   viewport = GL::GetDoublev(GL::VIEWPORT);

   GL::Clear(GL::ACCUM_BUFFER_BIT);
   for jitter in 0...ACSIZE
      GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
      accPerspective(50.0, viewport[2]/ viewport[3],
         1.0, 15.0, $j8[jitter][0], $j8[jitter][1], 0.0, 0.0, 1.0);
      displayObjects();
      GL::Accum(GL::ACCUM, 1.0/ACSIZE);
   end
   GL::Accum(GL::RETURN, 1.0);
   GL::Flush();
}

reshape = proc {|w, h|
   GL::Viewport(0, 0,  w,  h);
}

# /* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
   when 27
     exit(0);
   end
}

#/*  Main Loop
# *  Be certain you request an accumulation buffer.
# */
   GLUT.Init
   GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::ACCUM | GLUT::DEPTH);
   GLUT::InitWindowSize(250, 250);
   GLUT::InitWindowPosition(100, 100);
   GLUT::CreateWindow($0)
   init();
   GLUT::ReshapeFunc(reshape);
   GLUT::DisplayFunc(display);
   GLUT::KeyboardFunc(keyboard);
   GLUT::MainLoop();
