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

#*
#*  drawf.c
#*  Draws the bitmapped letter F on the screen (several times).
#*  This demonstrates use of the glBitmap() call.
#*/

require "gl_prev"
require "glu_prev"
require "glut_prev"


$rasters = [
   0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
   0xff, 0xc0, 0xff, 0xc0].pack("C*");

def init
   GL.PixelStorei(GL::UNPACK_ALIGNMENT, 1);
   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT);
   GL.Color(1.0, 1.0, 1.0);
   GL.RasterPos2i(20, 20);
   GL.Bitmap(10, 12, 0.0, 0.0, 11.0, 0.0, $rasters);
   GL.Bitmap(10, 12, 0.0, 0.0, 11.0, 0.0, $rasters);
   GL.Bitmap(10, 12, 0.0, 0.0, 11.0, 0.0, $rasters);
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0, w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   GL.Ortho(0, w, 0, h, -1.0, 1.0);
   GL.MatrixMode(GL::MODELVIEW);
}

#* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 27
         exit(0);
   end
}

#*  Main Loop
#*  Open window with initial window size, title bar, 
#*  RGBA display mode, and handle input events.
#*/
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT.InitWindowSize(100, 100);
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop();
