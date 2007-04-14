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
#/*  wrap.c
# *  This program texture maps a checkerboard image onto
# *  two rectangles.  This program demonstrates the wrapping
# *  modes, if the texture coordinates fall outside 0.0 and 1.0.
# *  Interaction: Pressing the 's' and 'S' keys switch the
# *  wrapping between clamping and repeating for the s parameter.
# *  The 't' and 'T' keys control the wrapping for the t parameter.
# *
# *  If running this program on OpenGL 1.0, texture objects are
# *  not used.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

#/*	Create checkerboard texture	*/
CheckImageWidth=64
CheckImageHeight=64
$checkImage = []

$texName = 0;

def makeCheckImage
   for i in 0..CheckImageHeight-1
      for j in 0..CheckImageWidth-1
         c = if (((i&0x8)==0)!=((j&0x8)==0)) then 255; else 0; end;
         $checkImage[(i*CheckImageWidth+j)*4+0] = c;
         $checkImage[(i*CheckImageWidth+j)*4+1] = c;
         $checkImage[(i*CheckImageWidth+j)*4+2] = c;
         $checkImage[(i*CheckImageWidth+j)*4+3] = 255;
      end
   end
end

def init
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.ShadeModel(GL::FLAT);
   GL.Enable(GL::DEPTH_TEST);

   makeCheckImage();
   GL.PixelStore(GL::UNPACK_ALIGNMENT, 1);

   $texName = GL.GenTextures(1);
   GL.BindTexture(GL::TEXTURE_2D, $texName[0]);

   GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::REPEAT);
   GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::REPEAT);
   GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MAG_FILTER, GL::NEAREST);
   GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_MIN_FILTER, GL::NEAREST);
   GL.TexImage2D(GL::TEXTURE_2D, 0, GL::RGBA, CheckImageWidth,
		CheckImageHeight, 
                0, GL::RGBA, GL::UNSIGNED_BYTE, $checkImage.pack("C*"));
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   GL.Enable(GL::TEXTURE_2D);
   GL.TexEnvf(GL::TEXTURE_ENV, GL::TEXTURE_ENV_MODE, GL::DECAL);
   GL.BindTexture(GL::TEXTURE_2D, $texName[0]);

   GL.Begin(GL::QUADS);
   GL.TexCoord(0.0, 0.0); GL.Vertex(-2.0, -1.0, 0.0);
   GL.TexCoord(0.0, 3.0); GL.Vertex(-2.0, 1.0, 0.0);
   GL.TexCoord(3.0, 3.0); GL.Vertex(0.0, 1.0, 0.0);
   GL.TexCoord(3.0, 0.0); GL.Vertex(0.0, -1.0, 0.0);

   GL.TexCoord(0.0, 0.0); GL.Vertex(1.0, -1.0, 0.0);
   GL.TexCoord(0.0, 3.0); GL.Vertex(1.0, 1.0, 0.0);
   GL.TexCoord(3.0, 3.0); GL.Vertex(2.41421, 1.0, -1.41421);
   GL.TexCoord(3.0, 0.0); GL.Vertex(2.41421, -1.0, -1.41421);
   GL.End();
   GL.Flush();
   GL.Disable(GL::TEXTURE_2D);
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   GLU.Perspective(60.0,  w/h, 1.0, 30.0);
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
   GL.Translate(0.0, 0.0, -3.6);
}

#/* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 's'[0]
         GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::CLAMP);
         GLUT.PostRedisplay();
      when 'S'[0]
         GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_S, GL::REPEAT);
         GLUT.PostRedisplay();
      when 't'[0]
         GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::CLAMP);
         GLUT.PostRedisplay();
      when 'T'[0]
         GL.TexParameter(GL::TEXTURE_2D, GL::TEXTURE_WRAP_T, GL::REPEAT);
         GLUT.PostRedisplay();
      when 27
         exit(0);
   end
}

#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT.InitWindowSize(250, 250);
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display);
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
#   return 0;
#}
