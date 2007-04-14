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
# *  tess.c
# *  This program demonstrates polygon tessellation.
# *  Two tesselated objects are drawn.  The first is a
# *  rectangle with a triangular hole.  The second is a
# *  smooth shaded, self-intersecting star.
# *
# *  Note the exterior rectangle is drawn with its vertices
# *  in counter-clockwise order, but its interior clockwise.
# *  Note the combineCallback is needed for the self-intersecting
# *  star.  Also note that removing the TessProperty for the 
# *  star will make the interior unshaded (WINDING_ODD).
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"

$startList = nil;

 display = proc {
   GL::Clear(GL::COLOR_BUFFER_BIT);
   GL::Color(1.0, 1.0, 1.0);
   GL::CallList($startList);
   GL::CallList($startList + 1);
   GL::Flush();
}

$beginCallback = proc {|which|
   GL::Begin(which);
}

$errorCallback = proc {|errorCode|
   print "Tessellation Error: #{GLU::ErrorString(errorCode)}";
   exit(0);
}

$endCallback = proc {
   GL::End();
}

$vertexCallback = proc {|vertex|
   GL::Color(vertex[3], vertex[4], vertex[5]);
   GL::Vertex(vertex[0], vertex[1], vertex[2]);
}

#/*  combineCallback is used to create a new vertex when edges
# *  intersect.  coordinate location is trivial to calculate,
# *  but weight[4] may be used to average color, normal, or texture
# *  coordinate data.  In this program, color is weighted.
# */
$combineCallback = proc {|coords, vertex_data, weight|
   vertex = []
   vertex[0] = coords[0];
   vertex[1] = coords[1];
   vertex[2] = coords[2];
   for i in 3...6
      vertex[i] = weight[0] * vertex_data[0][i] + weight[1] * vertex_data[1][i] + weight[2] * vertex_data[2][i] + weight[3] * vertex_data[3][i];
   end
   vertex
}

def init
   rect = [[50.0, 50.0, 0.0],
          [200.0, 50.0, 0.0],
          [200.0, 200.0, 0.0],
          [50.0, 200.0, 0.0]];
   tri = [[75.0, 75.0, 0.0],
         [125.0, 175.0, 0.0],
         [175.0, 75.0, 0.0]];
   star= [[250.0, 50.0, 0.0, 1.0, 0.0, 1.0],
         [325.0, 200.0, 0.0, 1.0, 1.0, 0.0],
         [400.0, 50.0, 0.0, 0.0, 1.0, 1.0],
         [250.0, 150.0, 0.0, 1.0, 0.0, 0.0],
         [400.0, 150.0, 0.0, 0.0, 1.0, 0.0]];

   GL::ClearColor(0.0, 0.0, 0.0, 0.0);

   $startList = GL::GenLists(2);

   tobj = GLU::NewTess();
   p "1"
   GLU::TessCallback(tobj, GLU::TESS_VERTEX, 
                   proc {|v| GL::Vertex(v)})
   p "2"
   GLU::TessCallback(tobj, GLU::TESS_BEGIN, 
                   $beginCallback);
   p "3"
   GLU::TessCallback(tobj, GLU::TESS_END, 
                   $endCallback);
   p "4"
   GLU::TessCallback(tobj, GLU::TESS_ERROR, 
                   $errorCallback);

#   /*  rectangle with triangular hole inside  */
   p "5"
   GL::NewList($startList, GL::COMPILE);
   GL::ShadeModel(GL::FLAT);    
   GLU::TessBeginPolygon(tobj, nil);
   p "5.1"
      GLU::TessBeginContour(tobj);
         GLU::TessVertex(tobj, rect[0], rect[0]);
         GLU::TessVertex(tobj, rect[1], rect[1]);
         GLU::TessVertex(tobj, rect[2], rect[2]);
         GLU::TessVertex(tobj, rect[3], rect[3]);
      GLU::TessEndContour(tobj);
   GLU::TessEndPolygon(tobj);
   p "5.2"
   GLU::TessBeginPolygon(tobj, nil);
      GLU::TessBeginContour(tobj);
         GLU::TessVertex(tobj, tri[0], tri[0]);
         GLU::TessVertex(tobj, tri[1], tri[1]);
         GLU::TessVertex(tobj, tri[2], tri[2]);
      GLU::TessEndContour(tobj);
   p "5.3"
   GLU::TessEndPolygon(tobj);
   p "5.4"
   GL::EndList();
   p "6"

   GLU::TessCallback(tobj, GLU::TESS_VERTEX, 
                   $vertexCallback);
   p "7"
   GLU::TessCallback(tobj, GLU::TESS_BEGIN, 
                   $beginCallback);
   p "8"
   GLU::TessCallback(tobj, GLU::TESS_END, 
                   $endCallback);
   p "9"
   GLU::TessCallback(tobj, GLU::TESS_ERROR, 
                   $errorCallback);
   p "10"
   GLU::TessCallback(tobj, GLU::TESS_COMBINE, 
                   $combineCallback);
   p "11"

#   /*  smooth shaded, self-intersecting star  */
   GL::NewList($startList + 1, GL::COMPILE);
   GL::ShadeModel(GL::SMOOTH);    
   p "12"
   GLU::TessProperty(tobj, GLU::TESS_WINDING_RULE,
                   GLU::TESS_WINDING_POSITIVE);
   p "13"
      GLU::TessBeginPolygon(tobj, nil);
   p "13.1"
      GLU::TessBeginContour(tobj);
         GLU::TessVertex(tobj, star[0], star[0]);
         GLU::TessVertex(tobj, star[1], star[1]);
         GLU::TessVertex(tobj, star[2], star[2]);
         GLU::TessVertex(tobj, star[3], star[3]);
         GLU::TessVertex(tobj, star[4], star[4]);
      GLU::TessEndContour(tobj);
   p "13.2"
   #GLU::TessEndPolygon(tobj);
   p "14"
   GL::EndList();
   p "15"
   GLU::DeleteTess(tobj);
   p "16"
end

reshape = proc {|w, h|
   GL::Viewport(0, 0, w, h);
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GLU::Ortho2D(0.0, w, 0.0, h);
}

#/* ARGSUSED1 */
keyboard = proc {|key, x, y|
   case (key)
      when 27
         exit(0);
   end
}

   GLUT::Init();
   GLUT::InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT::InitWindowSize(500, 500);
   GLUT::CreateWindow();
   init();
   GLUT::DisplayFunc(display);
   GLUT::ReshapeFunc(reshape);
   GLUT::KeyboardFunc(keyboard);
   GLUT::MainLoop();
