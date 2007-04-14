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
# *  quadric.c
# *  This program demonstrates the use of some of the gluQuadric*
# *  routines. Quadric objects are created with some quadric
# *  properties and the callback routine to handle errors.
# *  Note that the cylinder has no top or bottom and the circle
# *  has a hole in it.
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

$startList = nil;

#void CALLBACK errorCallback(GLenum errorCode)
#{
#   const GLubyte *estring;
#
#   estring = gluErrorString(errorCode);
#   fprintf(stderr, "Quadric Error: %s\n", estring);
#   exit(0);
#}

def init
   mat_ambient = [ 0.5, 0.5, 0.5, 1.0 ];
   mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
   mat_shininess = [ 50.0 ];
   light_position = [ 1.0, 1.0, 1.0, 0.0 ];
   model_ambient = [ 0.5, 0.5, 0.5, 1.0 ];

   GL.ClearColor(0.0, 0.0, 0.0, 0.0);

   GL.Material(GL::FRONT, GL::AMBIENT, mat_ambient);
   GL.Material(GL::FRONT, GL::SPECULAR, mat_specular);
   GL.Material(GL::FRONT, GL::SHININESS, mat_shininess);
   GL.Light(GL::LIGHT0, GL::POSITION, light_position);
   GL.LightModel(GL::LIGHT_MODEL_AMBIENT, model_ambient);

   GL.Enable(GL::LIGHTING);
   GL.Enable(GL::LIGHT0);
   GL.Enable(GL::DEPTH_TEST);

#/*  Create 4 display lists, each with a different quadric object.
# *  Different drawing styles and surface normal specifications
# *  are demonstrated.
# */
   $startList = GL.GenLists(4);
   qobj = GLU.NewQuadric();
#   gluQuadricCallback(qobj, GLU_ERROR, 
#                      (GLvoid (CALLBACK*) ()) errorCallback);

   GLU.QuadricDrawStyle(qobj, GLU::FILL); #/* smooth shaded */
   GLU.QuadricNormals(qobj, GLU::SMOOTH);
   GL.NewList($startList, GL::COMPILE);
      GLU.Sphere(qobj, 0.75, 15, 10);
   GL.EndList();

   GLU.QuadricDrawStyle(qobj, GLU::FILL); #/* flat shaded */
   GLU.QuadricNormals(qobj, GLU::FLAT);
   GL.NewList($startList+1, GL::COMPILE);
      GLU.Cylinder(qobj, 0.5, 0.3, 1.0, 15, 5);
   GL.EndList();

   GLU.QuadricDrawStyle(qobj, GLU::LINE); #/* all polygons wireframe */
   GLU.QuadricNormals(qobj, GLU::NONE);
   GL.NewList($startList+2, GL::COMPILE);
      GLU.Disk(qobj, 0.25, 1.0, 20, 4);
   GL.EndList();

   GLU.QuadricDrawStyle(qobj, GLU::SILHOUETTE); #/* boundary only  */
   GLU.QuadricNormals(qobj, GLU::NONE);
   GL.NewList($startList+3, GL::COMPILE);
      GLU.PartialDisk(qobj, 0.0, 1.0, 20, 4, 0.0, 225.0);
   GL.EndList();
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   GL.PushMatrix();

   GL.Enable(GL::LIGHTING);
   GL.ShadeModel(GL::SMOOTH);
   GL.Translate(-1.0, -1.0, 0.0);
   GL.CallList($startList);

   GL.ShadeModel(GL::FLAT);
   GL.Translate(0.0, 2.0, 0.0);
   GL.PushMatrix();
   GL.Rotate(300.0, 1.0, 0.0, 0.0);
   GL.CallList($startList+1);
   GL.PopMatrix();

   GL.Disable(GL::LIGHTING);
   GL.Color(0.0, 1.0, 1.0);
   GL.Translate(2.0, -2.0, 0.0);
   GL.CallList($startList+2);

   GL.Color(1.0, 1.0, 0.0);
   GL.Translate(0.0, 2.0, 0.0);
   GL.CallList($startList+3);

   GL.PopMatrix();
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   if (w <= h)
      GL.Ortho(-2.5, 2.5, -2.5*h/w,
         2.5*h/w, -10.0, 10.0);
   else
      GL.Ortho(-2.5*w/h,
         2.5*w/h, -2.5, 2.5, -10.0, 10.0);
   end
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

#/* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 27
         exit(0);
   end
}

#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT.InitWindowSize(500, 500); 
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display); 
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
#   return 0;
#}
