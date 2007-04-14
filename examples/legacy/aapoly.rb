#!/usr/bin/env ruby -rubygems
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
# *  aapoly.c
# *  This program draws filled polygons with antialiased
# *  edges.  The special GL_SRC_ALPHA_SATURATE blending 
# *  function is used.
# *  Pressing the 't' key turns the antialiasing on and off.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"

$polySmooth = true

def init
   GL::CullFace(GL::BACK);
   GL::Enable(GL::CULL_FACE);
   GL::BlendFunc(GL::SRC_ALPHA_SATURATE, GL::ONE);
   GL::ClearColor(0.0, 0.0, 0.0, 0.0);
end

NFACE=6
NVERT=8
$indices = [
  [4, 5, 6, 7], [2, 3, 7, 6], [0, 4, 7, 3],
  [0, 1, 5, 4], [1, 5, 6, 2], [0, 3, 2, 1]
]

def drawCube(x0, x1, y0, y1, z0, z1)
   v = [[],[],[],[],[],[],[],[]]
   c = [
      [0.0, 0.0, 0.0, 1.0], [1.0, 0.0, 0.0, 1.0],
      [0.0, 1.0, 0.0, 1.0], [1.0, 1.0, 0.0, 1.0],
      [0.0, 0.0, 1.0, 1.0], [1.0, 0.0, 1.0, 1.0],
      [0.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]
   ];

#/*  indices of front, top, left, bottom, right, back faces  */

   v[0][0] = v[3][0] = v[4][0] = v[7][0] = x0;
   v[1][0] = v[2][0] = v[5][0] = v[6][0] = x1;
   v[0][1] = v[1][1] = v[4][1] = v[5][1] = y0;
   v[2][1] = v[3][1] = v[6][1] = v[7][1] = y1;
   v[0][2] = v[1][2] = v[2][2] = v[3][2] = z0;
   v[4][2] = v[5][2] = v[6][2] = v[7][2] = z1;

   GL::EnableClientState(GL::VERTEX_ARRAY);
   GL::EnableClientState(GL::COLOR_ARRAY);
   GL::VertexPointer(3, GL::FLOAT, 0, v.flatten!.pack("f*"));
   GL::ColorPointer(4, GL::FLOAT, 0, c.flatten!.pack("f*"));
   GL::DrawElements(GL::QUADS, NFACE*4, GL::UNSIGNED_BYTE, $indices.flatten.pack("C*"));
   GL::DisableClientState(GL::VERTEX_ARRAY);
   GL::DisableClientState(GL::COLOR_ARRAY);
end

#/*  Note:  polygons must be drawn from front to back
# *  for proper blending.
# */
display = proc {
   if ($polySmooth)
      GL::Clear(GL::COLOR_BUFFER_BIT);
      GL::Enable(GL::BLEND);
      GL::Enable(GL::POLYGON_SMOOTH);
      GL::Disable(GL::DEPTH_TEST);
   else
      GL::Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
      GL::Disable(GL::BLEND);
      GL::Disable(GL::POLYGON_SMOOTH);
      GL::Enable(GL::DEPTH_TEST);
   end

   GL::PushMatrix();
      GL::Translate(0.0, 0.0, -8.0);    
      GL::Rotate(30.0, 1.0, 0.0, 0.0);
      GL::Rotate(60.0, 0.0, 1.0, 0.0); 
      drawCube(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
   GL::PopMatrix();

   GL::Flush();
}

reshape = proc {|w, h|
   GL::Viewport(0, 0, w, h);
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GLU::Perspective(30.0,  w.to_f/ h.to_f, 1.0, 20.0);
   GL::MatrixMode(GL::MODELVIEW);
   GL::LoadIdentity();
}

# /* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
   when ?t ,?T
         $polySmooth = !$polySmooth;
         GLUT::PostRedisplay();
   when 27
         exit(0);  #/*  Escape key  */
   end
}

#/*  Main Loop
# */
#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::ALPHA | GLUT::DEPTH);
   GLUT.InitWindowSize(200, 200);
   GLUT.CreateWindow($0)
   init();
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop();

