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
# *  pickdepth.c
# *  Picking is demonstrated in this program.  In 
# *  rendering mode, three overlapping rectangles are 
# *  drawn.  When the left mouse button is pressed, 
# *  selection mode is entered with the picking matrix.  
# *  Rectangles which are drawn under the cursor position
# *  are "picked."  Pay special attention to the depth 
# *  value range, which is returned.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"


def myinit
  GL::ClearColor(0.0, 0.0, 0.0, 0.0);
  GL::DepthFunc(GL::LESS);
  GL::Enable(GL::DEPTH_TEST);
  GL::ShadeModel(GL::FLAT);
  GL::DepthRange(0.0, 1.0);  #/* The default z mapping */
end

#/*  The three rectangles are drawn.  In selection mode, 
# *  each rectangle is given the same name.  Note that 
# *  each rectangle is drawn with a different z value.
# */
def drawRects(mode)
  if (mode == GL::SELECT)
    GL::LoadName(1);
  end
  GL::Begin(GL::QUADS);
  GL::Color(1.0, 1.0, 0.0);
  GL::Vertex(2, 0, 0);
  GL::Vertex(2, 6, 0);
  GL::Vertex(6, 6, 0);
  GL::Vertex(6, 0, 0);
  GL::End();
  if (mode == GL::SELECT)
    GL::LoadName(2);
  end
  GL::Begin(GL::QUADS);
  GL::Color(0.0, 1.0, 1.0);
  GL::Vertex(3, 2, -1);
  GL::Vertex(3, 8, -1);
  GL::Vertex(8, 8, -1);
  GL::Vertex(8, 2, -1);
  GL::End();
  if (mode == GL::SELECT)
    GL::LoadName(3);
  end
  GL::Begin(GL::QUADS);
  GL::Color(1.0, 0.0, 1.0);
  GL::Vertex(0, 2, -2);
  GL::Vertex(0, 7, -2);
  GL::Vertex(5, 7, -2);
  GL::Vertex(5, 2, -2);
  GL::End();
end

#/*  processHits() prints out the contents of the 
# *  selection array.
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

#/*  pickRects() sets up selection mode, name stack, 
# *  and projection matrix for picking.  Then the objects 
# *  are drawn.
# */
BUFSIZE=512

pickRects = proc {|button, state, x, y|

  if (button == GLUT::LEFT_BUTTON && state == GLUT::DOWN)
  viewport = GL::GetDoublev(GL::VIEWPORT);

  selectBuf = GL::SelectBuffer(BUFSIZE);
  GL::RenderMode(GL::SELECT);

  GL::InitNames();
  GL::PushName(~0);

  GL::MatrixMode(GL::PROJECTION);
  GL::PushMatrix();
  GL::LoadIdentity();
#/*  create 5x5 pixel picking region near cursor location */
  GLU::PickMatrix( x, viewport[3] - y, 5.0, 5.0, viewport);
  GL::Ortho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5);
  drawRects(GL::SELECT);
  GL::PopMatrix();
  GL::Flush();

  hits = GL::RenderMode(GL::RENDER);
  processHits(hits, selectBuf);
  end
}

display = proc {
  GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
  drawRects(GL::RENDER);
  GLUT::SwapBuffers();
}

myReshape = proc {|w, h|
  GL::Viewport(0, 0, w, h);
  GL::MatrixMode(GL::PROJECTION);
  GL::LoadIdentity();
  GL::Ortho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5);
  GL::MatrixMode(GL::MODELVIEW);
  GL::LoadIdentity();
}

#/*  Main Loop
# *  Open window with initial window size, title bar, 
# *  RGBA display mode, depth buffer, and handle input events.
# */
  GLUT::InitWindowSize(200, 200);
  GLUT::InitDisplayMode(GLUT::DOUBLE | GLUT::RGB | GLUT::DEPTH);
  GLUT::Init();
  GLUT::CreateWindow();
  myinit();
  GLUT::MouseFunc(pickRects);
  GLUT::ReshapeFunc(myReshape);
  GLUT::DisplayFunc(display);
  GLUT::MainLoop();
