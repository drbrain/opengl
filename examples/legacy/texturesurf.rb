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
#/*  texturesurf.c
# *  This program uses evaluators to generate a curved
# *  surface and automatically generated texture coordinates.
# */
#
require "gl_prev"
require "glu_prev"
require "glut_prev"

$ctrlpoints = [
    [[ -1.5, -1.5, 4.0], [ -0.5, -1.5, 2.0], 
	[0.5, -1.5, -1.0], [1.5, -1.5, 2.0]], 
    [[ -1.5, -0.5, 1.0], [ -0.5, -0.5, 3.0], 
	[0.5, -0.5, 0.0], [1.5, -0.5, -1.0]], 
    [[ -1.5, 0.5, 4.0], [ -0.5, 0.5, 0.0], 
	[0.5, 0.5, 3.0], [1.5, 0.5, 4.0]], 
    [[ -1.5, 1.5, -2.0], [ -0.5, 1.5, -2.0], 
	[0.5, 1.5, 0.0], [1.5, 1.5, -1.0]]
].flatten;

$texpts = [[[0.0, 0.0], [0.0, 1.0]], [[1.0, 0.0], [1.0, 1.0]]].flatten;

display = proc {
    GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
    GL::Color(1.0, 1.0, 1.0);
    GL::EvalMesh2(GL::FILL, 0, 20, 0, 20);
    GL::Flush();
}

ImageWidth=64
ImageHeight=64
$image = []

def makeImage
    for i in 0...ImageWidth
	ti = 2.0*3.14159265*i/ImageWidth.to_f;
	for j in 0...ImageHeight
	    tj = 2.0*3.14159265*j/ImageHeight.to_f;

	    $image[3*(ImageHeight*i+j)] =  127*(1.0+Math::sin(ti));
	    $image[3*(ImageHeight*i+j)+1] =  127*(1.0+Math::cos(2*tj));
	    $image[3*(ImageHeight*i+j)+2] =  127*(1.0+Math::cos(ti+tj));
	end
    end
end

def myinit
    GL::Map2d(GL::MAP2_VERTEX_3, 0, 1, 3, 4,
	    0, 1, 12, 4, $ctrlpoints);
    GL::Map2d(GL::MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 
	    0, 1, 4, 2, $texpts);
    GL::Enable(GL::MAP2_TEXTURE_COORD_2);
    GL::Enable(GL::MAP2_VERTEX_3);
    GL::MapGrid2d(20, 0.0, 1.0, 20, 0.0, 1.0);
    makeImage();
    GL::TexEnv(GL::TEXTURE_ENV, GL::TEXTURE_ENV_MODE, GL::DECAL);
    GL::TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::REPEAT);
    GL::TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::REPEAT);
    GL::TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MAG_FILTER, GL::NEAREST);
    GL::TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MIN_FILTER, GL::NEAREST);
    GL::TexImage2D(GL::TEXTURE_2D, 0, 3, ImageWidth, ImageHeight, 0,
		 GL::RGB, GL::UNSIGNED_BYTE, $image.pack("C*"));
    GL::Enable(GL::TEXTURE_2D);
    GL::Enable(GL::DEPTH_TEST);
    GL::Enable(GL::NORMALIZE);
    GL::ShadeModel(GL::FLAT);
end

myReshape = proc {|w, h|
    GL::Viewport(0, 0, w, h);
    GL::MatrixMode(GL::PROJECTION);
    GL::LoadIdentity();
    if (w <= h)
	GL::Ortho(-4.0, 4.0, -4.0*h.to_f/w, 4.0*h.to_f/w, -4.0, 4.0);
    else
	GL::Ortho(-4.0*w.to_f/h, 4.0*w.to_f/h, -4.0, 4.0, -4.0, 4.0);
    end
    GL::MatrixMode(GL::MODELVIEW);
    GL::LoadIdentity();
    GL::Rotate(85.0, 1.0, 1.0, 1.0);
}

    GLUT::Init();
    GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
    GLUT::CreateWindow();
    myinit();
    GLUT::ReshapeFunc(myReshape);
    GLUT::DisplayFunc(display);
    GLUT::MainLoop();
