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
#/*  accanti.c
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"

$LOAD_PATH.push(File.dirname($0))  # Find jitter in script directory

#/*  Initialize lighting and other values.
# */
def myinit
    mat_ambient = [ 1.0, 1.0, 1.0, 1.0 ];
    mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
    light_position = [ 0.0, 0.0, 10.0, 1.0 ];
    lm_ambient = [ 0.2, 0.2, 0.2, 1.0 ];

    GL::Material(GL::FRONT, GL::AMBIENT, mat_ambient);
    GL::Material(GL::FRONT, GL::SPECULAR, mat_specular);
    GL::Material(GL::FRONT, GL::SHININESS, 50.0);
    GL::Light(GL::LIGHT0, GL::POSITION, light_position);
    GL::LightModel(GL::LIGHT_MODEL_AMBIENT, lm_ambient);
    
    GL::Enable(GL::LIGHTING);
    GL::Enable(GL::LIGHT0);
    GL::DepthFunc(GL::LESS);
    GL::Enable(GL::DEPTH_TEST);
    GL::ShadeModel(GL::FLAT);

    GL::ClearColor(0.0, 0.0, 0.0, 0.0);
    GL::ClearAccum(0.0, 0.0, 0.0, 0.0);
end

def displayObjects
    torus_diffuse = [ 0.7, 0.7, 0.0, 1.0 ];
    cube_diffuse = [ 0.0, 0.7, 0.7, 1.0 ];
    sphere_diffuse = [ 0.7, 0.0, 0.7, 1.0 ];
    octa_diffuse = [ 0.7, 0.4, 0.4, 1.0 ];
    
    GL::PushMatrix();
    GL::Rotate(30.0, 1.0, 0.0, 0.0);

    GL::PushMatrix();
    GL::Translate(-0.80, 0.35, 0.0); 
    GL::Rotate(100.0, 1.0, 0.0, 0.0);
    GL::Material(GL::FRONT, GL::DIFFUSE, torus_diffuse);
    GLUT::SolidTorus(0.275, 0.85, 16, 16);
    GL::PopMatrix();

    GL::PushMatrix();
    GL::Translate(-0.75, -0.50, 0.0); 
    GL::Rotate(45.0, 0.0, 0.0, 1.0);
    GL::Rotate(45.0, 1.0, 0.0, 0.0);
    GL::Material(GL::FRONT, GL::DIFFUSE, cube_diffuse);
    GLUT::SolidCube(1.5);
    GL::PopMatrix();

    GL::PushMatrix();
    GL::Translate(0.75, 0.60, 0.0); 
    GL::Rotate(30.0, 1.0, 0.0, 0.0);
    GL::Material(GL::FRONT, GL::DIFFUSE, sphere_diffuse);
    GLUT::SolidSphere(1.0, 16, 16);
    GL::PopMatrix();

    GL::PushMatrix();
    GL::Translate(0.70, -0.90, 0.25); 
    GL::Material(GL::FRONT, GL::DIFFUSE, octa_diffuse);
    GLUT::SolidOctahedron();
    GL::PopMatrix();

    GL::PopMatrix();
end

ACSIZE=8

display = proc {
    viewport = GL::GetDoublev(GL::VIEWPORT);

    GL::Clear(GL::ACCUM_BUFFER_BIT);
    for jitter in 0...ACSIZE
	GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
	GL::PushMatrix();
#/*	Note that 4.5 is the distance in world space between
# *	left and right and bottom and top.
# *	This formula converts fractional pixel movement to 
# *	world coordinates.
# */
	GL::Translate($j8[jitter][0]*4.5/viewport[2],
	    $j8[jitter][1]*4.5/viewport[3], 0.0);
	displayObjects();
	GL::PopMatrix();
	GL::Accum(GL::ACCUM, 1.0/ACSIZE);
    end
    GL::Accum(GL::RETURN, 1.0);
    GL::Flush();
}

myReshape = proc {|w, h|
    GL::Viewport(0, 0, w, h);
    GL::MatrixMode(GL::PROJECTION);
    GL::LoadIdentity();
    if (w <= h) 
	GL::Ortho(-2.25, 2.25, -2.25*h/w, 2.25*h/w, -10.0, 10.0);
    else 
	GL::Ortho(-2.25*w/h, 2.25*w/h, -2.25, 2.25, -10.0, 10.0);
    end
    GL::MatrixMode(GL::MODELVIEW);
}

# /*  Main Loop
#  *  Open window with initial window size, title bar, 
#  *  RGBA display mode, and handle input events.
#  */
    GLUT.Init
    GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::ACCUM | GLUT::DEPTH);
    GLUT::InitWindowSize(250, 250);
    GLUT::CreateWindow($0)
    myinit();
    GLUT::ReshapeFunc(myReshape);
    GLUT::DisplayFunc(display);
    GLUT::MainLoop();
