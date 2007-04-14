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
# *  depthcue.c
# *  This program draws a wireframe model, which uses 
# *  intensity (brightness) to give clues to distance.
# *  Fog is used to achieve this effect.
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

#/*  Initialize linear fog for depth cueing.
# */
def myinit
    fogColor = [0.0, 0.0, 0.0, 1.0];

    GL.Enable(GL::FOG);
    GL.Fog(GL::FOG_MODE, GL::LINEAR);
    GL.Hint(GL::FOG_HINT, GL::NICEST);  #/*  per pixel   */
    GL.Fog(GL::FOG_START, 3.0);
    GL.Fog(GL::FOG_END, 5.0);
    GL.Fog(GL::FOG_COLOR, fogColor);
    GL.ClearColor(0.0, 0.0, 0.0, 1.0);

    GL.DepthFunc(GL::LESS);
    GL.Enable(GL::DEPTH_TEST);
    GL.ShadeModel(GL::FLAT);
end

#/*  display() draws an icosahedron.
# */
display = Proc.new {
    GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
    GL.Color(1.0, 1.0, 1.0);
    GLUT.WireIcosahedron();
    GL.Flush();
}

myReshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GLU.Perspective(45.0,  w/h, 3.0, 5.0);
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
    GL.Translate(0.0, 0.0, -4.0);  #/*  move object into view   */
}

#/*  Main Loop
# */
#int main(int argc, char** argv)
#{
    GLUT.Init
    GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
    GLUT.CreateWindow($0);
    myinit();
    GLUT.ReshapeFunc(myReshape);
    GLUT.DisplayFunc(display);
    GLUT.MainLoop();
#    return 0;             /* ANSI C requires main to return int. */
#}

