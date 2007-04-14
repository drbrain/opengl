#
#/* Copyright (c) Mark J. Kilgard, 1994. */
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
#/*
# *  fog.c
# *  This program draws 5 red teapots, each at a different 
# *  z distance from the eye, in different types of fog.  
# *  Pressing the left mouse button chooses between 3 types of 
# *  fog:  exponential, exponential squared, and linear.  
# *  In this program, there is a fixed density value, as well 
# *  as fixed start and end values for the linear fog.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

$fogMode = 0;

selectFog = Proc.new {|mode|
    if (mode == GL::LINEAR)
        GL.Fog(GL::FOG_START, 1.0);
        GL.Fog(GL::FOG_END, 5.0);
	#/* falls through */
        GL.Fog(GL::FOG_MODE, mode);
	GLUT.PostRedisplay();
    end
    if (mode == GL::EXP2 || mode == GL::EXP)
        GL.Fog(GL::FOG_MODE, mode);
	GLUT.PostRedisplay();
    end
    exit(0) if (mode == 0)
}

#/*  Initialize z-buffer, projection matrix, light source, 
# *  and lighting model.  Do not specify a material property here.
# */
def myinit
    position = [0.0, 3.0, 3.0, 0.0];
    local_view = [0.0];

    GL.Enable(GL::DEPTH_TEST);
    GL.DepthFunc(GL::LESS);

    GL.Light(GL::LIGHT0, GL::POSITION, position);
    GL.LightModel(GL::LIGHT_MODEL_LOCAL_VIEWER, local_view);

    GL.FrontFace(GL::CW);
    GL.Enable(GL::LIGHTING);
    GL.Enable(GL::LIGHT0);
    GL.Enable(GL::AUTO_NORMAL);
    GL.Enable(GL::NORMALIZE);
    GL.Enable(GL::FOG);
        fogColor = [0.5, 0.5, 0.5, 1.0];

        fogMode = GL::EXP;
        GL.Fog(GL::FOG_MODE, fogMode);
        GL.Fog(GL::FOG_COLOR, fogColor);
        GL.Fog(GL::FOG_DENSITY, 0.35);
        GL.Hint(GL::FOG_HINT, GL::DONT_CARE);
        GL.ClearColor(0.5, 0.5, 0.5, 1.0);
end

def renderRedTeapot(x, y, z)
    mat = []
    GL.PushMatrix();
    GL.Translate(x, y, z);
    mat[0] = 0.1745;
    mat[1] = 0.01175;
    mat[2] = 0.01175;
    mat[3] = 1.0;
    GL.Material(GL::FRONT, GL::AMBIENT, mat);
    mat[0] = 0.61424;
    mat[1] = 0.04136;
    mat[2] = 0.04136;
    GL.Material(GL::FRONT, GL::DIFFUSE, mat);
    mat[0] = 0.727811;
    mat[1] = 0.626959;
    mat[2] = 0.626959;
    GL.Material(GL::FRONT, GL::SPECULAR, mat);
    GL.Material(GL::FRONT, GL::SHININESS, 0.6 * 128.0);
    GLUT.SolidTeapot(1.0);
    GL.PopMatrix();
end

#/*  display() draws 5 teapots at different z positions.
# */
display = Proc.new {
    GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
    renderRedTeapot(-4.0, -0.5, -1.0);
    renderRedTeapot(-2.0, -0.5, -2.0);
    renderRedTeapot(0.0, -0.5, -3.0);
    renderRedTeapot(2.0, -0.5, -4.0);
    renderRedTeapot(4.0, -0.5, -5.0);
    GL.Flush();
}

myReshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    if (w <= (h * 3))
        GL.Ortho(-6.0, 6.0, -2.0 * h * 3 / w,
            2.0 * h * 3 / w, 0.0, 10.0);
    elsif
        GL.Ortho(-6.0 * w / h * 3,
            6.0 * w / h * 3, -2.0, 2.0, 0.0, 10.0);
    end
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
}

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, depth buffer, and handle input events.
# */
#int 
#main(int argc, char **argv)
#{
    GLUT.Init
    GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
    GLUT.InitWindowSize(450, 150);
    GLUT.CreateWindow($0);
    myinit();
    GLUT.ReshapeFunc(myReshape);
    GLUT.DisplayFunc(display);
    GLUT.CreateMenu(selectFog);
    GLUT.AddMenuEntry("Fog EXP", GL::EXP);
    GLUT.AddMenuEntry("Fog EXP2", GL::EXP2);
    GLUT.AddMenuEntry("Fog LINEAR", GL::LINEAR);
    GLUT.AddMenuEntry("Quit", 0);
    GLUT.AttachMenu(GLUT::RIGHT_BUTTON);
    GLUT.MainLoop();
#    return 0;             /* ANSI C requires main to return int. */
#}
