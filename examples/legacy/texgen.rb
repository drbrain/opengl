#
# Copyright (c) 1993-1997, Silicon Graphics, Inc.
# ALL RIGHTS RESERVED 
# Permission to use, copy, modify, and distribute this software for 
# any purpose and without fee is hereby granted, provided that the above
# copyright notice appear in all copies and that both the copyright notice
# and this permission notice appear in supporting documentation, and that 
# the name of Silicon Graphics, Inc. not be used in advertising
# or publicity pertaining to distribution of the software without specific,
# written prior permission. 
#
# THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
# AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
# INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
# FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
# GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
# SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
# KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
# LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
# THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
# ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
# POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
# 
# US Government Users Restricted Rights 
# Use, duplication, or disclosure by the Government is subject to
# restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
# (c)(1)(ii) of the Rights in Technical Data and Computer Software
# clause at DFARS 252.227-7013 and/or in similar or successor
# clauses in the FAR or the DOD or NASA FAR Supplement.
# Unpublished-- rights reserved under the copyright laws of the
# United States.  Contractor/manufacturer is Silicon Graphics,
# Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
#
# OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
#/

#  texgen.c
#  This program draws a texture mapped teapot with 
#  automatically generated texture coordinates.  The
#  texture is rendered as stripes on the teapot.
#  Initially, the object is drawn with texture coordinates
#  based upon the object coordinates of the vertex
#  and distance from the plane x = 0.  Pressing the 'e'
#  key changes the coordinate generation to eye coordinates
#  of the vertex.  Pressing the 'o' key switches it back
#  to the object coordinates.  Pressing the 's' key 
#  changes the plane to a slanted one (x + y + z = 0).
#  Pressing the 'x' key switches it back to x = 0.
#/

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"
StripeImageWidth =  32
$stripeImage = []

$texName;

def makeStripeImage
   for j in (0..StripeImageWidth-1)
      $stripeImage[4*j] = if (j<=4) then 255; else 0; end;
      $stripeImage[4*j+1] = if (j>4) then 255 else 0; end;
      $stripeImage[4*j+2] = 0;
      $stripeImage[4*j+3] = 255;
   end
end

#*  planes for texture coordinate generation  */
$xequalzero = [1.0, 0.0, 0.0, 0.0];
$slanted = [1.0, 1.0, 1.0, 0.0];
$currentCoeff = nil;
$currentPlane = nil;
$currentGenMode = nil;

def init
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.Enable(GL::DEPTH_TEST);
   GL.ShadeModel(GL::SMOOTH);

   makeStripeImage();
   GL.PixelStorei(GL::UNPACK_ALIGNMENT, 1);

   $texName = GL.GenTextures(1);
   GL.BindTexture(GL::TEXTURE_2D, $texName[0]);
   GL.TexParameteri(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::REPEAT);
   GL.TexParameteri(GL::TEXTURE_2D, GL::TEXTURE_MAG_FILTER, GL::LINEAR);
   GL.TexParameteri(GL::TEXTURE_2D, GL::TEXTURE_MIN_FILTER, GL::LINEAR);
   GL.TexImage2D(GL::TEXTURE_2D, 0, GL::RGBA, StripeImageWidth, 1, 0,
                GL::RGBA, GL::UNSIGNED_BYTE, $stripeImage.pack("C*"));
   GL.TexEnvf(GL::TEXTURE_ENV, GL::TEXTURE_ENV_MODE, GL::MODULATE);
   $currentCoeff = $xequalzero;
   $currentGenMode = GL::OBJECT_LINEAR;
   $currentPlane = GL::OBJECT_PLANE;
   GL.TexGen(GL::S, GL::TEXTURE_GEN_MODE, $currentGenMode);
   GL.TexGen(GL::S, $currentPlane, $currentCoeff);

   GL.Enable(GL::TEXTURE_GEN_S);
   GL.Enable(GL::TEXTURE_2D);
   GL.Enable(GL::CULL_FACE);
   GL.Enable(GL::LIGHTING);
   GL.Enable(GL::LIGHT0);
   GL.Enable(GL::AUTO_NORMAL);
   GL.Enable(GL::NORMALIZE);
   GL.FrontFace(GL::CW);
   GL.CullFace(GL::BACK);
   GL.Material(GL::FRONT, GL::SHININESS, 64.0);
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   GL.PushMatrix();
   GL.Rotate(45.0, 0.0, 0.0, 1.0);
   GL.BindTexture(GL::TEXTURE_2D, $texName[0]);
   GLUT.SolidTeapot(2.0);
   GL.PopMatrix();
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0, w, h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   if (w <= h)
      GL.Ortho(-3.5, 3.5, -3.5*h/w,3.5*h/w, -3.5, 3.5);
   else
      GL.Ortho(-3.5*w/h, 3.5*w/h, -3.5, 3.5, -3.5, 3.5);
   end
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

#* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 'e'[0],'E'[0]
         $currentGenMode = GL::EYE_LINEAR;
         $currentPlane = GL::EYE_PLANE;
         GL.TexGen(GL::S, GL::TEXTURE_GEN_MODE, $currentGenMode);
         GL.TexGen(GL::S, $currentPlane, $currentCoeff);
         GLUT.PostRedisplay();
      when 'o'[0], 'O'[0]
         $currentGenMode = GL::OBJECT_LINEAR;
         $currentPlane = GL::OBJECT_PLANE;
         GL.TexGen(GL::S, GL::TEXTURE_GEN_MODE, $currentGenMode);
         GL.TexGen(GL::S, $currentPlane, $currentCoeff);
         GLUT.PostRedisplay();
      when 's'[0],'S'[0]
         $currentCoeff = $slanted;
         GL.TexGen(GL::S, $currentPlane, $currentCoeff);
         GLUT.PostRedisplay();
      when 'x'[0],'X'[0]
         $currentCoeff = $xequalzero;
         GL.TexGen(GL::S, $currentPlane, $currentCoeff);
         GLUT.PostRedisplay();
      when 27
         exit(0);
   end
}

   GLUT.Init
   GLUT.InitDisplayMode (GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT.InitWindowSize(256, 256);
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow ($0);
   init();
   GLUT.DisplayFunc(display);
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
