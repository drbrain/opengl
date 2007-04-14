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
# *  lines.c
# *  This program demonstrates geometric primitives and
# *  their attributes.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

def drawOneLine(x1,y1,x2,y2)
  GL.Begin(GL::LINES);
   GL.Vertex((x1),(y1)); GL.Vertex((x2),(y2)); GL.End();
end

def init
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.ShadeModel(GL::FLAT);
end

display = Proc.new {

   GL.Clear(GL::COLOR_BUFFER_BIT);

#/* select white for all lines  */
   GL.Color(1.0, 1.0, 1.0);

#/* in 1st row, 3 lines, each with a different stipple  */
   GL.Enable(GL::LINE_STIPPLE);
   
   GL.LineStipple(1, 0x0101); # /*  dotted  */
   drawOneLine(50.0, 125.0, 150.0, 125.0);
   GL.LineStipple(1, 0x00FF); # /*  dashed  */
   drawOneLine(150.0, 125.0, 250.0, 125.0);
   GL.LineStipple(1, 0x1C47);  #/*  dash/dot/dash  */
   drawOneLine(250.0, 125.0, 350.0, 125.0);

#/* in 2nd row, 3 wide lines, each with different stipple */
   GL.LineWidth (5.0);
   GL.LineStipple(1, 0x0101); # /*  dotted  */
   drawOneLine(50.0, 100.0, 150.0, 100.0);
   GL.LineStipple(1, 0x00FF); # /*  dashed  */
   drawOneLine(150.0, 100.0, 250.0, 100.0);
   GL.LineStipple(1, 0x1C47); # /*  dash/dot/dash  */
   drawOneLine(250.0, 100.0, 350.0, 100.0);
   GL.LineWidth(1.0);

# /* in 3rd row, 6 lines, with dash/dot/dash stipple  */
# /* as part of a single connected line strip         */
   GL.LineStipple(1, 0x1C47);  # /*  dash/dot/dash  */
   GL.Begin(GL::LINE_STRIP);
   for i in  0..6
      GL.Vertex(50.0 + (i * 50.0), 75.0);
   end
   GL.End();

#/* in 4th row, 6 independent lines with same stipple  */
   for i in 0..5
      drawOneLine(50.0 + (i * 50.0), 50.0, 50.0 + ((i+1) * 50.0), 50.0);
   end

# /* in 5th row, 1 line, with dash/dot/dash stipple    */
# /* and a stipple repeat factor of 5                  */
   GL.LineStipple(5, 0x1C47);  #/*  dash/dot/dash  */
   drawOneLine(50.0, 25.0, 350.0, 25.0);

   GL.Disable(GL::LINE_STIPPLE);
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   GLU.Ortho2D(0.0,  w, 0.0,  h);
}

# /* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 27
         exit(0);
   end
}

# int main(int argc, char** argv)
# {
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT.InitWindowSize(400, 150); 
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display); 
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
