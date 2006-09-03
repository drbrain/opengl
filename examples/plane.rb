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
# *  plane.c
# *  This program demonstrates the use of local versus 
# *  infinite lighting on a flat plane.
# */

#require "opengl"
require "../ext/gl"
require "../ext/glut"
require '../lib/opengl_c'
require '../lib/glut_c'
require "mathn"

# /*  Initialize material property, light source, and lighting model.
# */
def myinit
    mat_ambient = [ 0.0, 0.0, 0.0, 1.0 ];
#/*   mat_specular and mat_shininess are NOT default values	*/
    mat_diffuse = [ 0.4, 0.4, 0.4, 1.0 ];
    mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
    mat_shininess = [ 15.0 ];

    light_ambient = [ 0.0, 0.0, 0.0, 1.0 ];
    light_diffuse = [ 1.0, 1.0, 1.0, 1.0 ];
    light_specular = [ 1.0, 1.0, 1.0, 1.0 ];
    lmodel_ambient = [ 0.2, 0.2, 0.2, 1.0 ];

    GL.glMaterial(GL::GL_FRONT, GL::GL_AMBIENT, mat_ambient);
    GL.glMaterial(GL::GL_FRONT, GL::GL_DIFFUSE, mat_diffuse);
    GL.glMaterial(GL::GL_FRONT, GL::GL_SPECULAR, mat_specular);
    GL.glMaterial(GL::GL_FRONT, GL::GL_SHININESS, *mat_shininess);
    GL.glLight(GL::GL_LIGHT0, GL::GL_AMBIENT, light_ambient);
    GL.glLight(GL::GL_LIGHT0, GL::GL_DIFFUSE, light_diffuse);
    GL.glLight(GL::GL_LIGHT0, GL::GL_SPECULAR, light_specular);
    GL.glLightModel(GL::GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    GL.glEnable(GL::GL_LIGHTING);
    GL.glEnable(GL::GL_LIGHT0);
    GL.glDepthFunc(GL::GL_LESS);
    GL.glEnable(GL::GL_DEPTH_TEST);
end

def drawPlane
    GL.glBegin(GL::GL_QUADS);
    GL.glNormal(0.0, 0.0, 1.0);
    GL.glVertex(-1.0, -1.0, 0.0);
    GL.glVertex(0.0, -1.0, 0.0);
    GL.glVertex(0.0, 0.0, 0.0);
    GL.glVertex(-1.0, 0.0, 0.0);

    GL.glNormal(0.0, 0.0, 1.0);
    GL.glVertex(0.0, -1.0, 0.0);
    GL.glVertex(1.0, -1.0, 0.0);
    GL.glVertex(1.0, 0.0, 0.0);
    GL.glVertex(0.0, 0.0, 0.0);

    GL.glNormal(0.0, 0.0, 1.0);
    GL.glVertex(0.0, 0.0, 0.0);
    GL.glVertex(1.0, 0.0, 0.0);
    GL.glVertex(1.0, 1.0, 0.0);
    GL.glVertex(0.0, 1.0, 0.0);

    GL.glNormal(0.0, 0.0, 1.0);
    GL.glVertex(0.0, 0.0, 0.0);
    GL.glVertex(0.0, 1.0, 0.0);
    GL.glVertex(-1.0, 1.0, 0.0);
    GL.glVertex(-1.0, 0.0, 0.0);
    GL.glEnd();
end

display = Proc.new {
    infinite_light = [ 1.0, 1.0, 1.0, 0.0 ];
    local_light = [ 1.0, 1.0, 1.0, 1.0 ];

    GL.glClear(GL::GL_COLOR_BUFFER_BIT | GL::GL_DEPTH_BUFFER_BIT);

    GL.glPushMatrix();
    GL.glTranslate(-1.5, 0.0, 0.0);
    GL.glLight(GL::GL_LIGHT0, GL::GL_POSITION, infinite_light);
    drawPlane();
    GL.glPopMatrix();

    GL.glPushMatrix();
    GL.glTranslate(1.5, 0.0, 0.0);
    GL.glLight(GL::GL_LIGHT0, GL::GL_POSITION, local_light);
    drawPlane();
    GL.glPopMatrix();
    GL.glFlush();
}

myReshape = Proc.new {|w, h|
    GL.glViewport(0, 0, w, h);
    GL.glMatrixMode(GL::GL_PROJECTION);
    GL.glLoadIdentity();
    if (w <= h) 
	GL.glOrtho(-1.5, 1.5, -1.5*h/w, 1.5*h/w, -10.0, 10.0);
    else 
	GL.glOrtho(-1.5*w/h, 1.5*w/h, -1.5, 1.5, -10.0, 10.0);
    end
    GL.glMatrixMode(GL::GL_MODELVIEW);
}

# Keyboard handler to exit when ESC is typed
keyboard = lambda do |key, x, y|
  case(key)
  when 27
    exit(0)
  end
end

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, and handle input events.
# */
#int main(int argc, char** argv)
#{
    GLUT.glutInit
    GLUT.glutInitDisplayMode(GLUT::GLUT_SINGLE | GLUT::GLUT_RGB | GLUT::GLUT_DEPTH);
    GLUT.glutInitWindowSize(500, 200);
    GLUT.glutCreateWindow($0);
    myinit();
    GLUT.glutReshapeFunc(myReshape);
    GLUT.glutDisplayFunc(display);
    GLUT.glutKeyboardFunc(keyboard);
    GLUT.glutMainLoop();
