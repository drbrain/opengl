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
#/*  checker.c
# *  This program texture maps a checkerboard image onto
# *  two rectangles.  This program clamps the texture, if
# *  the texture coordinates fall outside 0.0 and 1.0.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

#/*	Create checkerboard texture	*/
CheckImageWidth=64
CheckImageHeight=64
$checkImage = []

def makeCheckImage
    for i in 0..CheckImageWidth-1
        for j in 0..CheckImageHeight-1
	    c = if ((i&0x8==0) != (j&0x8==0)) then 255; else 0; end;
	    $checkImage[(i+CheckImageWidth*j)*3+0] = c;
	    $checkImage[(i+CheckImageWidth*j)*3+1] = c;
	    $checkImage[(i+CheckImageWidth*j)*3+2] = c;
	end
    end
end

def myinit
    GL.ClearColor(0.0, 0.0, 0.0, 0.0);
    GL.Enable(GL::DEPTH_TEST);
    GL.DepthFunc(GL::LESS);

    makeCheckImage();
    GL.PixelStore(GL::UNPACK_ALIGNMENT, 1);
    GL.TexImage2D(GL::TEXTURE_2D, 0, 3, CheckImageWidth, 
	CheckImageHeight, 0, GL::RGB, GL::UNSIGNED_BYTE, 
	$checkImage.pack("C*"));
    GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::CLAMP);
    GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::CLAMP);
    GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MAG_FILTER, GL::LINEAR);
    GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MIN_FILTER, GL::LINEAR);
    GL.TexEnv(GL::TEXTURE_ENV, GL::TEXTURE_ENV_MODE, GL::DECAL);
    GL.Enable(GL::TEXTURE_2D);
    GL.ShadeModel(GL::FLAT);
end

display = Proc.new {
    GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
    GL.Begin(GL::QUADS);
    GL.TexCoord(0.0, 0.0); GL.Vertex(-2.0, -1.0, 0.0);
    GL.TexCoord(0.0, 1.0); GL.Vertex(-2.0, 1.0, 0.0);
    GL.TexCoord(1.0, 1.0); GL.Vertex(0.0, 1.0, 0.0);
    GL.TexCoord(1.0, 0.0); GL.Vertex(0.0, -1.0, 0.0);

    GL.TexCoord(0.0, 0.0); GL.Vertex(1.0, -1.0, 0.0);
    GL.TexCoord(0.0, 1.0); GL.Vertex(1.0, 1.0, 0.0);
    GL.TexCoord(1.0, 1.0); GL.Vertex(2.41421, 1.0, -1.41421);
    GL.TexCoord(1.0, 0.0); GL.Vertex(2.41421, -1.0, -1.41421);
    GL.End();
    GLUT.SwapBuffers();
}

myReshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GLU.Perspective(60.0, 1.0*w/h, 1.0, 30.0);
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
    GL.Translate(0.0, 0.0, -3.6);
}

#int
#main(int argc, char** argv)
#{
    GLUT.Init
    GLUT.InitDisplayMode(GLUT::DOUBLE | GLUT::RGB | GLUT::DEPTH);
    GLUT.CreateWindow("checker");
    myinit();
    GLUT.ReshapeFunc (myReshape);
    GLUT.DisplayFunc(display);
    GLUT.MainLoop();
