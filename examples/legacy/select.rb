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
# * select.c
# * This is an illustration of the selection mode and 
# * name stack, which detects whether objects which collide 
# * with a viewing volume.  First, four triangles and a 
# * rectangular box representing a viewing volume are drawn 
# * (drawScene routine).  The green triangle and yellow 
# * triangles appear to lie within the viewing volume, but 
# * the red triangle appears to lie outside it.  Then the 
# * selection mode is entered (selectObjects routine).  
# * Drawing to the screen ceases.  To see if any collisions 
# * occur, the four triangles are called.  In this example, 
# * the green triangle causes one hit with the name 1, and 
# * the yellow triangles cause one hit with the name 3.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"


#/* draw a triangle with vertices at (x1, y1), (x2, y2) 
# * and (x3, y3) at z units away from the origin.
# */
def drawTriangle(x1, y1, x2, y2, x3, y3, z)
   GL::Begin(GL::TRIANGLES);
   GL::Vertex(x1, y1, z);
   GL::Vertex(x2, y2, z);
   GL::Vertex(x3, y3, z);
   GL::End();
end

#/* draw a rectangular box with these outer x, y, and z values */
def drawViewVolume(x1, x2, y1, y2, z1, z2)
   GL::Color(1.0, 1.0, 1.0);
   GL::Begin(GL::LINE_LOOP);
   GL::Vertex(x1, y1, -z1);
   GL::Vertex(x2, y1, -z1);
   GL::Vertex(x2, y2, -z1);
   GL::Vertex(x1, y2, -z1);
   GL::End();

   GL::Begin(GL::LINE_LOOP);
   GL::Vertex(x1, y1, -z2);
   GL::Vertex(x2, y1, -z2);
   GL::Vertex(x2, y2, -z2);
   GL::Vertex(x1, y2, -z2);
   GL::End();

   GL::Begin(GL::LINES);#	/*  4 lines	*/
   GL::Vertex(x1, y1, -z1);
   GL::Vertex(x1, y1, -z2);
   GL::Vertex(x1, y2, -z1);
   GL::Vertex(x1, y2, -z2);
   GL::Vertex(x2, y1, -z1);
   GL::Vertex(x2, y1, -z2);
   GL::Vertex(x2, y2, -z1);
   GL::Vertex(x2, y2, -z2);
   GL::End();
end

#/* drawScene draws 4 triangles and a wire frame
# * which represents the viewing volume.
# */
def drawScene()
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GLU::Perspective(40.0, 4.0/3.0, 1.0, 100.0);

   GL::MatrixMode(GL::MODELVIEW);
   GL::LoadIdentity();
   GLU::LookAt(7.5, 7.5, 12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
   GL::Color(0.0, 1.0, 0.0);#	/*  green triangle	*/
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0);
   GL::Color(1.0, 0.0, 0.0);#	/*  red triangle	*/
   drawTriangle(2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0);
   GL::Color(1.0, 1.0, 0.0);#	/*  yellow triangles	*/
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, 0.0);
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -10.0);
   drawViewVolume(0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
end

#/* processHits prints out the contents of the selection array
# */
def processHits(hits, buffer)
   printf("hits = %d\n", hits);
   ptr = buffer.unpack("I*")
   p = 0
   for i in 0...hits 	#/*  for each hit  */
      names = ptr[p]
      printf(" number of names for hit = %d\n", names); p+=1;
      printf("  z1 is %g;",  ptr[p].to_f/0xffffffff); p+=1;
      printf(" z2 is %g\n",  ptr[p].to_f/0xffffffff); p+=1;
      printf("   the name is ");
      for j in 0...names  #	/*  for each name */
         printf("%d ", ptr[p]); p+=1
      end
      printf("\n");
   end
end

#/* selectObjects "draws" the triangles in selection mode, 
# * assigning names for the triangles.  Note that the third
# * and fourth triangles share one name, so that if either 
# * or both triangles intersects the viewing/clipping volume, 
# * only one hit will be registered.
# */

BUFSIZE=512

def selectObjects

   selectBuf = GL::SelectBuffer(BUFSIZE);
   GL::RenderMode(GL::SELECT);

   GL::InitNames();
   GL::PushName(0);

   GL::PushMatrix();
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GL::Ortho(0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
   GL::MatrixMode(GL::MODELVIEW);
   GL::LoadIdentity();
   GL::LoadName(1);
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0);
   GL::LoadName(2);
   drawTriangle(2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0);
   GL::LoadName(3);
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, 0.0);
   drawTriangle(2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -10.0);
   GL::PopMatrix();
   GL::Flush();

   hits = GL::RenderMode(GL::RENDER);
   processHits(hits, selectBuf);
end 

def init
   GL::Enable(GL::DEPTH_TEST);
   GL::ShadeModel(GL::FLAT);
end

display = proc {
   GL::ClearColor(0.0, 0.0, 0.0, 0.0);
   GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   drawScene();
   selectObjects();
   GL::Flush();
}

#/* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
   when 27
      exit(0);
   end
}

#/*  Main Loop  */

   GLUT.Init
   GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT::InitWindowSize(200, 200);
   GLUT::InitWindowPosition(100, 100);
   GLUT::CreateWindow $0
   init();
   GLUT::DisplayFunc(display);
   GLUT::KeyboardFunc(keyboard);
   GLUT::MainLoop();
