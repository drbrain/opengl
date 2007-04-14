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
#/*
# *  alpha3D.c
# *  This program demonstrates how to intermix opaque and
# *  alpha blended polygons in the same scene, by using 
# *  glDepthMask.  Press the 'a' key to animate moving the 
# *  transparent object through the opaque object.  Press 
# *  the 'r' key to reset the scene.
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"


MAXZ=8.0
MINZ=-8.0
ZINC=0.4

$solidZ = MAXZ;
$transparentZ = MINZ;
$sphereList=nil
$cubeList=nil

def init
   mat_specular = [ 1.0, 1.0, 1.0, 0.15 ];
   mat_shininess = [ 100.0 ];
   position = [ 0.5, 0.5, 1.0, 0.0 ];

   GL::Material(GL::FRONT, GL::SPECULAR, mat_specular);
   GL::Material(GL::FRONT, GL::SHININESS, mat_shininess);
   GL::Light(GL::LIGHT0, GL::POSITION, position);

   GL::Enable(GL::LIGHTING);
   GL::Enable(GL::LIGHT0);
   GL::Enable(GL::DEPTH_TEST);

   $sphereList = GL::GenLists(1);
   GL::NewList($sphereList, GL::COMPILE);
      GLUT::SolidSphere(0.4, 16, 16);
   GL::EndList();

   $cubeList = GL::GenLists(1);
   GL::NewList($cubeList, GL::COMPILE);
      GLUT::SolidCube(0.6);
   GL::EndList();
end

display = proc {
   mat_solid = [ 0.75, 0.75, 0.0, 1.0 ];
   mat_zero = [ 0.0, 0.0, 0.0, 1.0 ];
   mat_transparent = [ 0.0, 0.8, 0.8, 0.6 ];
   mat_emission = [ 0.0, 0.3, 0.3, 0.6 ];

   GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);

   GL::PushMatrix();
      GL::Translate(-0.15, -0.15, $solidZ);
      GL::Material(GL::FRONT, GL::EMISSION, mat_zero);
      GL::Material(GL::FRONT, GL::DIFFUSE, mat_solid);
      GL::CallList($sphereList);
   GL::PopMatrix();

   GL::PushMatrix();
      GL::Translate(0.15, 0.15, $transparentZ);
      GL::Rotate(15.0, 1.0, 1.0, 0.0);
      GL::Rotate(30.0, 0.0, 1.0, 0.0);
      GL::Material(GL::FRONT, GL::EMISSION, mat_emission);
      GL::Material(GL::FRONT, GL::DIFFUSE, mat_transparent);
      GL::Enable(GL::BLEND);
      GL::DepthMask(GL::FALSE);
      GL::BlendFunc(GL::SRC_ALPHA, GL::ONE);
      GL::CallList($cubeList);
      GL::DepthMask(GL::TRUE);
      GL::Disable(GL::BLEND);
   GL::PopMatrix();

   GL::Flush();
}

reshape = proc {|w, h|
   GL::Viewport(0, 0,  w,  h);
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   if (w <= h)
      GL::Ortho(-1.5, 1.5, -1.5*h.to_f/w,
               1.5*h.to_f/w, -10.0, 10.0);
   else
      GL::Ortho(-1.5*w.to_f/h,
               1.5*w.to_f/h, -1.5, 1.5, -10.0, 10.0);
   end
   GL::MatrixMode(GL::MODELVIEW);
   GL::LoadIdentity();
}

animate = proc {
   if ($solidZ <= MINZ || $transparentZ >= MAXZ)
      GLUT::IdleFunc(nil);
   else
      $solidZ -= ZINC;
      $transparentZ += ZINC;
      GLUT::PostRedisplay();
   end
}

# /* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
      when ?a,?A
         $solidZ = MAXZ;
         $transparentZ = MINZ;
         GLUT::IdleFunc(animate);
      when ?r, ?R
         $solidZ = MAXZ;
         $transparentZ = MINZ;
         GLUT::PostRedisplay();
      when 27
        exit(0);
    end
}

   GLUT::Init()
   GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT::InitWindowSize(500, 500);
   GLUT::CreateWindow($0)
   init();
   GLUT::ReshapeFunc(reshape);
   GLUT::KeyboardFunc(keyboard);
   GLUT::DisplayFunc(display);
   GLUT::MainLoop();
