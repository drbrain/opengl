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
#/*  image.c
# *  This program demonstrates drawing pixels and shows the effect
# *  of glDrawPixels(), glCopyPixels(), and glPixelZoom().
# *  Interaction: moving the mouse while pressing the mouse button
# *  will copy the image in the lower-left corner of the window
# *  to the mouse position, using the current pixel zoom factors.
# *  There is no attempt to prevent you from drawing over the original
# *  image.  If you press the 'r' key, the original image and zoom
# *  factors are reset.  If you press the 'z' or 'Z' keys, you change
# *  the zoom factors.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

# /*	Create checkerboard image	*/
CheckImageWidth=64
CheckImageHeight=64
$checkImage=[]

$zoomFactor = 1.0;
$height = 0.0;

def makeCheckImage
    for i in 0..CheckImageWidth-1
        for j in 0..CheckImageHeight-1
	    c = if ((i&0x8==0) != (j&0x8==0)) then 255; else 0; end;
	    $checkImage[(i+CheckImageWidth*j)*3+0] = c;
	    $checkImage[(i+CheckImageWidth*j)*3+1] = c;
	    $checkImage[(i+CheckImageWidth*j)*3+2] = c;
	end
    end
end

def init
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.ShadeModel(GL::FLAT);
   makeCheckImage();
   GL.PixelStorei(GL::UNPACK_ALIGNMENT, 1);
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT);
   GL.RasterPos(0, 0);
   GL.DrawPixels(CheckImageWidth, CheckImageHeight, GL::RGB, GL::UNSIGNED_BYTE, $checkImage.pack("C*"));
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   $height = h;
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   GLU.Ortho2D(0.0,  w, 0.0, h);
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

$screeny = 0.0
motion = Proc.new {|x, y|

   $screeny = $height - y;
   GL.RasterPos(x, $screeny);
   GL.PixelZoom($zoomFactor, $zoomFactor);
   GL.CopyPixels(0, 0, CheckImageWidth, CheckImageHeight, GL::COLOR);
   GL.PixelZoom(1.0, 1.0);
   GL.Flush();
}

# /* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 'r'[0],'R'[0]
         $zoomFactor = 1.0;
         GLUT.PostRedisplay();
         printf("zoomFactor reset to 1.0\n");
      when 'z'[0]
         $zoomFactor = $zoomFactor + 0.5;
         if ($zoomFactor >= 3.0) 
            $zoomFactor = 3.0;
	 end
         printf("zoomFactor is now %4.1f\n", $zoomFactor);
      when 'Z'[0]
         $zoomFactor = $zoomFactor - 0.5;
         if ($zoomFactor <= 0.5) 
            $zoomFactor = 0.5;
	 end
         printf("zoomFactor is now %4.1f\n", $zoomFactor);
      when 27
         exit(0);
   end
}

#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT.InitWindowSize(250, 250);
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display);
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MotionFunc(motion);
   GLUT.MainLoop();
