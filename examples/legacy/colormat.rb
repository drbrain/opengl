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
# *  colormat.c
# *  After initialization, the program will be in
# *  ColorMaterial mode.  Interaction:  pressing the 
# *  mouse buttons will change the diffuse reflection values.
# */

require "gl_prev"
require "glu_prev"
require "glut_prev"
require "mathn"

$diffuseMaterial = [0.5,0.5,0.5,1.0];

#/*  Initialize material property, light source, lighting model,
# *  and depth buffer.
# */
def init
   mat_specular = [ 1.0, 1.0, 1.0, 1.0 ];
   light_position = [ 1.0, 1.0, 1.0, 0.0 ];

   GL.ClearColor(0.0, 0.0, 0.0, 0.0);
   GL.ShadeModel(GL::SMOOTH);
   GL.Enable(GL::DEPTH_TEST);
   GL.Material(GL::FRONT, GL::DIFFUSE, $diffuseMaterial);
   GL.Material(GL::FRONT, GL::SPECULAR, mat_specular);
   GL.Material(GL::FRONT, GL::SHININESS, 25.0);
   GL.Light(GL::LIGHT0, GL::POSITION, light_position);
   GL.Enable(GL::LIGHTING);
   GL.Enable(GL::LIGHT0);

   GL.ColorMaterial(GL::FRONT, GL::DIFFUSE);
   GL.Enable(GL::COLOR_MATERIAL);
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
   GLUT.SolidSphere(1.0, 20, 16);
   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode (GL::PROJECTION);
   GL.LoadIdentity();
   if (w <= h)
      GL.Ortho(-1.5, 1.5, -1.5*h/w, 1.5*h/w, -10.0, 10.0);
   else
      GL.Ortho(-1.5*w/h, 1.5*w/h, -1.5, 1.5, -10.0, 10.0);
   end
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

# /* ARGSUSED2 */
mouse = Proc.new {|button, state, x, y|
   case (button)
      when GLUT::LEFT_BUTTON
         if (state == GLUT::DOWN)
            $diffuseMaterial[0] = $diffuseMaterial[0] + 0.1;
            if ($diffuseMaterial[0] > 1.0)
               $diffuseMaterial[0] = 0.0;
	    end
            GL.Color($diffuseMaterial);
            GLUT.PostRedisplay();
         end
      when GLUT::MIDDLE_BUTTON
         if (state == GLUT::DOWN)
            $diffuseMaterial[1] = $diffuseMaterial[1] + 0.1;
            if ($diffuseMaterial[1] > 1.0)
               $diffuseMaterial[1] = 0.0;
	    end
            GL.Color($diffuseMaterial);
            GLUT.PostRedisplay();
         end
      when GLUT::RIGHT_BUTTON
         if (state == GLUT::DOWN)
            $diffuseMaterial[2] = $diffuseMaterial[2] + 0.1;
            if ($diffuseMaterial[2] > 1.0)
               $diffuseMaterial[2] = 0.0;
	    end
            GL.Color($diffuseMaterial);
            GLUT.PostRedisplay();
         end
   end
}

# /* ARGSUSED1 */
keyboard = Proc.new {|key, x, y|
   case (key)
      when 27
         exit(0);
   end
}

#int main(int argc, char** argv)
#{
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::DEPTH);
   GLUT.InitWindowSize(500, 500); 
   GLUT.InitWindowPosition(100, 100);
   GLUT.CreateWindow($0);
   init();
   GLUT.DisplayFunc(display); 
   GLUT.ReshapeFunc(reshape);
   GLUT.MouseFunc(mouse);
   GLUT.KeyboardFunc(keyboard);
   GLUT.MainLoop();
