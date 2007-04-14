#
# Copyright (c) 1993-1997, Silicon Graphics, Inc.
# ALL RIGHTS RESERVED 
# Permission to use, copy, modify, and distribute this software for 
# any purpose and without fee is hereby granted, provided that the above
# copyright notice appear in all copies and that both the copyright notice
# and this permission notice appear in supporting documentation, and that 
# the name of Silicon Graphics, Inc. not be used in advertising
# or publicity pertaining to distribution of the software without specific,
# written prior permission. 
#
# THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
# AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
# INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
# FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
# GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
# SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
# KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
# LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
# THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
# ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
# POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
# 
# US Government Users Restricted Rights 
# Use, duplication, or disclosure by the Government is subject to
# restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
# (c)(1)(ii) of the Rights in Technical Data and Computer Software
# clause at DFARS 252.227-7013 and/or in similar or successor
# clauses in the FAR or the DOD or NASA FAR Supplement.
# Unpublished-- rights reserved under the copyright laws of the
# United States.  Contractor/manufacturer is Silicon Graphics,
# Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
#
# OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
#/

#
#  movelight.c
#  This program demonstrates when to issue lighting and
#  transformation commands to render a model with a light
#  which is moved by a modeling transformation (rotate or
#  translate).  The light position is reset after the modeling
#  transformation is called.  The eye position does not change.
#
#  A sphere is drawn using a grey material characteristic.
#  A single light source illuminates the object.
#
#  Interaction:  pressing the left mouse button alters
#  the modeling transformation (x rotation) by 30 degrees.
#  The scene is then redrawn with the light in a new position.
#/

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "rational"
require "mathn"

$spin = 0;

#  Initialize material property, light source, lighting model,
#  and depth buffer.
#/
def init
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.ShadeModel(GL::SMOOTH);
   GL.Enable(GL::LIGHTING);
   GL.Enable(GL::LIGHT0);
   GL.Enable(GL::DEPTH_TEST);
end

#  Here is where the light position is reset after the modeling
#  transformation (glRotated) is called.  This places the
#  light at a new position in world coordinates.  The cube
#  represents the position of the light.
#/
display = Proc.new {
   position = [ 0.0, 0.0, 1.5, 1.0 ];

   GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   GL.PushMatrix();
   GLU.LookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   GL.PushMatrix();
   GL.Rotate($spin, 1.0, 0.0, 0.0);
   GL.Light(GL::LIGHT0, GL::POSITION, position);

   GL.Translate(0.0, 0.0, 1.5);
   GL.Disable(GL::LIGHTING);
   GL.Color(0.0, 1.0, 1.0);
   GLUT.WireCube(0.1);
   GL.Enable(GL::LIGHTING);
   GL.PopMatrix();

   GLUT.SolidTorus(0.275, 0.85, 8, 15);
   GL.PopMatrix();
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
#   GLU.Perspective(40.0,  Rational(w,h), 1.0, 20.0);
   GLU.Perspective(40.0,  w/h, 1.0, 20.0);
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

# ARGSUSED2 */
mouse = Proc.new {|button, state, x, y|
   case button
      when GLUT::LEFT_BUTTON
         if (state == GLUT::DOWN)
            $spin = ($spin + 30) % 360;
            GLUT.PostRedisplay();
         end
   end
}

# ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case key
      when 27
         exit(0);
   end
}

   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT.InitWindowSize(500, 500); 
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display); 
   GLUT.ReshapeFunc(reshape);
   GLUT.MouseFunc(mouse);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
