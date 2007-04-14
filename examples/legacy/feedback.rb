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
# * feedback.c
# * This program demonstrates use of OpenGL feedback.  First,
# * a lighting environment is set up and a few lines are drawn.
# * Then feedback mode is entered, and the same lines are 
# * drawn.  The results in the feedback buffer are printed.
# */
require "gl_prev"
require "glu_prev"
require "glut_prev"


#/*  Initialize lighting.
# */
def init
   GL::Enable(GL::LIGHTING);
   GL::Enable(GL::LIGHT0);
end

#/* Draw a few lines and two points, one of which will 
# * be clipped.  If in feedback mode, a passthrough token 
# * is issued between the each primitive.
# */
def drawGeometry(mode)
   GL::Begin(GL::LINE_STRIP);
   GL::Normal(0.0, 0.0, 1.0);
   GL::Vertex(30.0, 30.0, 0.0);
   GL::Vertex(50.0, 60.0, 0.0);
   GL::Vertex(70.0, 40.0, 0.0);
   GL::End();
   if (mode == GL::FEEDBACK)
      GL::PassThrough(1.0);
   end
   GL::Begin(GL::POINTS);
   GL::Vertex(-100.0, -100.0, -100.0);  # /*  will be clipped  */
   GL::End();
   if (mode == GL::FEEDBACK)
      GL::PassThrough(2.0);
   end
   GL::Begin(GL::POINTS);
   GL::Normal(0.0, 0.0, 1.0);
   GL::Vertex(50.0, 50.0, 0.0);
   GL::End();
end

# /* Write contents of one vertex to stdout.	*/
def print3DcolorVertex(size, count, buffer)
   printf("  ");
   for i in 0...7
      printf("%4.2f ", buffer[size-count]);
      count = count - 1;
   end
   printf("\n");
   return count
end

#/*  Write contents of entire buffer.  (Parse tokens!)	*/
def  printBuffer(size, buffer)

   count = size;
   while (count!=0)
      token = buffer[size-count]; count-=1;
      if (token == GL::PASS_THROUGH_TOKEN)
         printf("GL::PASS_THROUGH_TOKEN\n");
         printf("  %4.2f\n", buffer[size-count]);
         count-=1;
      elsif (token == GL::POINT_TOKEN)
         printf("GL::POINT_TOKEN\n");
         count = print3DcolorVertex(size, count, buffer);
      elsif (token == GL::LINE_TOKEN)
         printf("GL::LINE_TOKEN\n");
         count = print3DcolorVertex(size, count, buffer);
         count = print3DcolorVertex(size, count, buffer);
      elsif (token == GL::LINE_RESET_TOKEN)
         printf("GL::LINE_RESET_TOKEN\n");
         count = print3DcolorVertex(size, count, buffer);
         count = print3DcolorVertex(size, count, buffer);
      end
   end
end

display = proc {
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GL::Ortho(0.0, 100.0, 0.0, 100.0, 0.0, 1.0);

   GL::ClearColor(0.0, 0.0, 0.0, 0.0);
   GL::Clear(GL::COLOR_BUFFER_BIT);
   drawGeometry(GL::RENDER);

   feedBuffer = GL::FeedbackBuffer(1024, GL::GL_3D_COLOR);
   GL::RenderMode(GL::FEEDBACK);
   drawGeometry(GL::FEEDBACK);

   size = GL::RenderMode(GL::RENDER);
   printBuffer(size, feedBuffer.unpack("f#{size}"));
}

#/* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
   when 27
     exit(0);
   end
}

   GLUT::Init()
   GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT::InitWindowSize(100, 100);
   GLUT::InitWindowPosition(100, 100);
   GLUT::CreateWindow()
   init();
   GLUT::DisplayFunc(display);
   GLUT::KeyboardFunc(keyboard);
   GLUT::MainLoop();
