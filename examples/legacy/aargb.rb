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
# *  aargb.c
# *  This program draws shows how to draw anti-aliased lines. It draws
# *  two diagonal lines to form an X; when 'r' is typed in the window, 
# *  the lines are rotated in opposite directions.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

$rotAngle = 0.0;

#/*  Initialize antialiasing for RGBA mode, including alpha
# *  blending, hint, and line width.  Print out implementation
# *  specific info on line width granularity and width.
# */
def init
#   GLfloat values[2];
#   glGetFloatv (GL_LINE_WIDTH_GRANULARITY, values);
#   printf ("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n", values[0]);

#   glGetFloatv (GL_LINE_WIDTH_RANGE, values);
#   printf ("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n",
#      values[0], values[1]);

   GL.Enable(GL::LINE_SMOOTH);
   GL.Enable(GL::BLEND);
   GL.BlendFunc(GL::SRC_ALPHA, GL::ONE_MINUS_SRC_ALPHA);
   GL.Hint(GL::LINE_SMOOTH_HINT, GL::DONT_CARE);
   GL.LineWidth(1.5);

   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
end

#/* Draw 2 diagonal lines to form an X
# */
display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT);

   GL.Color(0.0, 1.0, 0.0);
   GL.PushMatrix();
   GL.Rotate(-$rotAngle, 0.0, 0.0, 0.1);
   GL.Begin(GL::LINES);
      GL.Vertex(-0.5, 0.5);
      GL.Vertex(0.5, -0.5);
   GL.End();
   GL.PopMatrix();

   GL.Color(0.0, 0.0, 1.0);
   GL.PushMatrix();
   GL.Rotate($rotAngle, 0.0, 0.0, 0.1);
   GL.Begin(GL::LINES);
      GL.Vertex(0.5, 0.5);
      GL.Vertex(-0.5, -0.5);
   GL.End();
   GL.PopMatrix();

   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0, w, h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   if (w <= h) 
      GLU.Ortho2D(-1.0, 1.0, -1.0*h/w, 1.0*h/w);
   else 
      GLU.Ortho2D(-1.0*w/h, 1.0*w/h, -1.0, 1.0);
   end
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

# /* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 'r'[0],'R'[0]
         $rotAngle = $rotAngle + 20.0;
         $rotAngle = 0.0 if ($rotAngle >= 360.0) 
         GLUT.PostRedisplay();
      when 27  #/*  Escape Key  */
         exit(0);
    end
}

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, and handle input events.
# */
#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT.InitWindowSize(200, 200);
   GLUT.CreateWindow($0);
   init();
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop();
