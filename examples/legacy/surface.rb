#/* aux2glut conversion Copyright (c) Mark J. Kilgard, 1994, 1995 */
#
#/**
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
#/**
# *  surface.c
# *  This program draws a NURBS surface in the shape of a 
# *  symmetrical hill.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

$ctlpoints = [];
$showPoints = 0;

$theNurb = nil;

#/*
# *  Initializes the control points of the surface to a small hill.
# *  The control points range from -3 to +3 in x, y, and z
# */
def init_surface
    for u in 0..3
	for v in 0..3
	    $ctlpoints[u*4*3+v*3+0] = 2.0*(u - 1.5);
	    $ctlpoints[u*4*3+v*3+1] = 2.0*(v - 1.5);

	    if ( (u == 1 || u == 2) && (v == 1 || v == 2))
		$ctlpoints[u*4*3+v*3+2] = 7.0;
	    else
		$ctlpoints[u*4*3+v*3+2] = -3.0;
	    end
	end
    end
end			
			
#/*  Initialize material property and depth buffer.
# */
def myinit
    mat_diffuse = [ 0.7, 0.7, 0.7, 1.0 ];
    mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
    mat_shininess = [ 100.0 ];

    GL.ClearColor(0.0, 0.0, 0.0, 1.0);
    GL.Material(GL::FRONT, GL::DIFFUSE, mat_diffuse);
    GL.Material(GL::FRONT, GL::SPECULAR, mat_specular);
    GL.Material(GL::FRONT, GL::SHININESS, mat_shininess);

    GL.Enable(GL::LIGHTING);
    GL.Enable(GL::LIGHT0);
    GL.DepthFunc(GL::LESS);
    GL.Enable(GL::DEPTH_TEST);
    GL.Enable(GL::AUTO_NORMAL);
    GL.Enable(GL::NORMALIZE);

    init_surface();

    $theNurb = GLU.NewNurbsRenderer();
    GLU.NurbsProperty($theNurb, GLU::SAMPLING_TOLERANCE, 25.0);
    GLU.NurbsProperty($theNurb, GLU::DISPLAY_MODE, GLU::FILL);
end

display = Proc.new {
    knots = [0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0];

    GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);

    GL.PushMatrix();
    GL.Rotate(330.0, 1.0,0.0,0.0);
    GL.Scale(0.25, 0.25, 0.25);

    GLU.BeginSurface($theNurb);
    GLU.NurbsSurface($theNurb, 
	    8, knots,
	    8, knots,
	    4 * 3,
	    3,
	    $ctlpoints, 
	    4, 4,
	    GL::MAP2_VERTEX_3);
    GLU.EndSurface($theNurb);

    if($showPoints==1)
    GL.PointSize(5.0);
    GL.Disable(GL::LIGHTING);
    GL.Color(1.0, 1.0, 0.0);
    GL.Begin(GL::POINTS);
    for i in 0..3
      for j in 0..3
	GL.Vertex($ctlpoints[i*4*3+j*3+0], $ctlpoints[i*4*3+j*3+1], $ctlpoints[i*4*3+j*3+2]);
      end
    end
    GL.End();
    GL.Enable(GL::LIGHTING);
    end
        
    GL.PopMatrix();
    GL.Flush();
}

reshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GLU.Perspective(45.0, w/h, 3.0, 8.0);

    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
    GL.Translate(0.0, 0.0, -5.0);
}

menu = Proc.new {|value|
    $showPoints = value;
    GLUT.PostRedisplay();
}

#/* Main Loop */
#int
#main(int argc, char** argv)
#{
    GLUT.Init
    GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
    GLUT.CreateWindow($0);
    myinit();
    GLUT.ReshapeFunc(reshape);
    GLUT.DisplayFunc(display);
    GLUT.CreateMenu(menu);
    GLUT.AddMenuEntry("Show control points", 1);
    GLUT.AddMenuEntry("Hide control points", 0);
    GLUT.AttachMenu(GLUT::RIGHT_BUTTON);
    GLUT.MainLoop();
#    return 0;             /* ANSI C requires main to return int. */
#}
