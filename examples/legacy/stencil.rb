
# Copyright (c) Mark J. Kilgard, 1994. */

#
# (c) Copyright 1993, Silicon Graphics, Inc.
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
# OpenGL(TM) is a trademark of Silicon Graphics, Inc.
#/
#  stencil.c
#  This program draws two rotated tori in a window.  
#  A diamond in the center of the window masks out part 
#  of the scene.  Within this mask, a different model 
#  (a sphere) is drawn in a different color.
#/
require "gl_prev"
require "glu_prev"
require "glut_prev"
require "rational"

YELLOWMAT=1
BLUEMAT=2

def myinit
    yellow_diffuse = [ 0.7, 0.7, 0.0, 1.0 ];
    yellow_specular = [ 1.0, 1.0, 1.0, 1.0 ];

    blue_diffuse = [ 0.1, 0.1, 0.7, 1.0 ];
    blue_specular = [ 0.1, 1.0, 1.0, 1.0 ];

    position_one = [ 1.0, 1.0, 1.0, 0.0 ];

    GL.NewList(YELLOWMAT, GL::COMPILE);
    GL.Material(GL::FRONT, GL::DIFFUSE, yellow_diffuse);
    GL.Material(GL::FRONT, GL::SPECULAR, yellow_specular);
    GL.Material(GL::FRONT, GL::SHININESS, 64.0);
    GL.EndList();

    GL.NewList(BLUEMAT, GL::COMPILE);
    GL.Material(GL::FRONT, GL::DIFFUSE, blue_diffuse);
    GL.Material(GL::FRONT, GL::SPECULAR, blue_specular);
    GL.Material(GL::FRONT, GL::SHININESS, 45.0);
    GL.EndList();

    GL.Light(GL::LIGHT0, GL::POSITION, position_one);

    GL.Enable(GL::LIGHT0);
    GL.Enable(GL::LIGHTING);
    GL.DepthFunc(GL::LESS);
    GL.Enable(GL::DEPTH_TEST);

    GL.ClearStencil(0x0);
    GL.Enable(GL::STENCIL_TEST);
end

#  Draw a sphere in a diamond-shaped section in the
#  middle of a window with 2 tori.
#/
display = Proc.new {
    GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);

# draw blue sphere where the stencil is 1 */
    GL.StencilFunc(GL::EQUAL, 0x1, 0x1);
    GL.CallList(BLUEMAT);
    GLUT.SolidSphere(0.5, 15, 15);

# draw the tori where the stencil is not 1 */
    GL.StencilFunc(GL::NOTEQUAL, 0x1, 0x1);
    GL.StencilOp(GL::KEEP, GL::KEEP, GL::KEEP);
    GL.PushMatrix();
	GL.Rotate(45.0, 0.0, 0.0, 1.0);
	GL.Rotate(45.0, 0.0, 1.0, 0.0);
	GL.CallList(YELLOWMAT);
	GLUT.SolidTorus(0.275, 0.85, 15, 15);
	GL.PushMatrix();
	    GL.Rotate(90.0, 1.0, 0.0, 0.0);
	    GLUT.SolidTorus(0.275, 0.85, 15, 15);
	GL.PopMatrix();
    GL.PopMatrix();
}

#  Whenever the window is reshaped, redefine the 
#  coordinate system and redraw the stencil area.
#/
myReshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);

    GL.Clear(GL::STENCIL_BUFFER_BIT);
# create a diamond shaped stencil area */
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GL.Ortho(-3.0, 3.0, -3.0, 3.0, -1.0, 1.0);
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();

    GL.StencilFunc(GL::ALWAYS, 0x1, 0x1);
    GL.StencilOp(GL::REPLACE, GL::REPLACE, GL::REPLACE);
    GL.Begin(GL::QUADS);
	GL.Vertex(-1.0, 0.0, 0.0);
	GL.Vertex(0.0, 1.0, 0.0);
	GL.Vertex(1.0, 0.0, 0.0);
	GL.Vertex(0.0, -1.0, 0.0);
    GL.End();

    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GLU.Perspective(45.0,  w.to_f/h.to_f, 3.0, 7.0);
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
    GL.Translate(0.0, 0.0, -5.0);
}

#  Main Loop
#  Open window with initial window size, title bar, 
#  RGBA display mode, and handle input events.
#/
    GLUT.Init()
    GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH | GLUT::STENCIL);
    GLUT.InitWindowSize(400, 400);
    GLUT.CreateWindow($0);
    myinit
    GLUT.ReshapeFunc(myReshape);
    GLUT.DisplayFunc(display);
    GLUT.MainLoop();
