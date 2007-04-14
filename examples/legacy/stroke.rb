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
# *  stroke.c 
# *  This program demonstrates some characters of a 
# *  stroke (vector) font.  The characters are represented
# *  by display lists, which are given numbers which 
# *  correspond to the ASCII values of the characters.
# *  Use of glCallLists() is demonstrated.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

PT=1
STROKE=2
END_=3

Adata = [
    [[0, 0], PT], [[0, 9], PT], [[1, 10], PT], [[4, 10], PT], 
    [[5, 9], PT], [[5, 0], STROKE], [[0, 5], PT], [[5, 5], END_]
];

Edata = [
    [[5, 0], PT], [[0, 0], PT], [[0, 10], PT], [[5, 10], STROKE],
    [[0, 5], PT], [[4, 5], END_]
];

Pdata = [
    [[0, 0], PT], [[0, 10], PT],  [[4, 10], PT], [[5, 9], PT], [[5, 6], PT], 
    [[4, 5], PT], [[0, 5], END_]
];

Rdata = [
    [[0, 0], PT], [[0, 10], PT],  [[4, 10], PT], [[5, 9], PT], [[5, 6], PT], 
    [[4, 5], PT], [[0, 5], STROKE], [[3, 5], PT], [[5, 0], END_]
];

Sdata = [
    [[0, 1], PT], [[1, 0], PT], [[4, 0], PT], [[5, 1], PT], [[5, 4], PT], 
    [[4, 5], PT], [[1, 5], PT], [[0, 6], PT], [[0, 9], PT], [[1, 10], PT], 
    [[4, 10], PT], [[5, 9], END_]
];

#/*  drawLetter() interprets the instructions from the array
# *  for that letter and renders the letter with line segments.
# */
def drawLetter(l)
    i = 0
    GL.Begin(GL::LINE_STRIP);
    while (1) 
	case (l[i][1])
	    when PT
		GL.Vertex(l[i][0]);
	    when STROKE
		GL.Vertex(l[i][0]);
		GL.End();
		GL.Begin(GL::LINE_STRIP);
	    when END_
		GL.Vertex(l[i][0]);
		GL.End();
		GL.Translate(8.0, 0.0, 0.0);
		return
	end
	i = i + 1
    end
end

# /*  Create a display list for each of 6 characters	*/
def myinit
    GL.ShadeModel (GL::FLAT);

    base = GL.GenLists(128);
    GL.ListBase(base);
    GL.NewList(base+'A'[0], GL::COMPILE); drawLetter(Adata); GL.EndList();
    GL.NewList(base+'E'[0], GL::COMPILE); drawLetter(Edata); GL.EndList();
    GL.NewList(base+'P'[0], GL::COMPILE); drawLetter(Pdata); GL.EndList();
    GL.NewList(base+'R'[0], GL::COMPILE); drawLetter(Rdata); GL.EndList();
    GL.NewList(base+'S'[0], GL::COMPILE); drawLetter(Sdata); GL.EndList();
    GL.NewList(base+' '[0], GL::COMPILE); GL.Translate(8.0, 0.0, 0.0); GL.EndList();
end

$test1 = "A SPARE SERAPE APPEARS AS";
$test2 = "APES PREPARE RARE PEPPERS";

def printStrokedString(s)
#    GL.CallLists(s.size, GL::BYTE, s);
    GL.CallLists( s);
end

display = Proc.new {
    GL.Clear(GL::COLOR_BUFFER_BIT);
    GL.Color(1.0, 1.0, 1.0);
    GL.PushMatrix();
    GL.Scale(2.0, 2.0, 2.0);
    GL.Translate(10.0, 30.0, 0.0);
    printStrokedString($test1);
    GL.PopMatrix();
    GL.PushMatrix();
    GL.Scale(2.0, 2.0, 2.0);
    GL.Translate(10.0, 13.0, 0.0);
    printStrokedString($test2);
    GL.PopMatrix();
    GL.Flush();
}

reshape = Proc.new {|w, h|
    GL.Viewport(0, 0, w, h);
    GL.MatrixMode(GL::PROJECTION);
    GL.LoadIdentity();
    GL.Ortho(0.0, w, 0.0, h, -1.0, 1.0);
    GL.MatrixMode(GL::MODELVIEW);
    GL.LoadIdentity();
}

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, and handle input events.
# */
#int main(int argc, char** argv)
#{
    GLUT.Init
    GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
    GLUT.InitWindowSize(440, 120);
    GLUT.CreateWindow($0);
    myinit();
    GLUT.DisplayFunc(display);
    GLUT.ReshapeFunc(reshape);
    GLUT.MainLoop();
#    return 0;             /* ANSI C requires main to return int. */
#}
