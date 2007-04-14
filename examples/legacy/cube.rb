#!/usr/bin/env ruby -rubygems
require "gl_prev"
require "glu_prev"
require "glut_prev"


$light_diffuse = [1.0, 0.0, 0.0, 1.0]
$light_position = [1.0, 1.0, 1.0, 0.0]
$n = [ 
  [-1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [1.0, 0.0, 0.0],
  [0.0, -1.0, 0.0], [0.0, 0.0, 1.0], [0.0, 0.0, -1.0] ]
$faces = [
  [0, 1, 2, 3], [3, 2, 6, 7], [7, 6, 5, 4],
  [4, 5, 1, 0], [5, 6, 2, 1], [7, 4, 0, 3] ]
$v = 0

def drawBox
  for i in (0..5)
    GL.Begin(GL::QUADS);
    GL.Normal(*($n[i]));
#    tmp = $v.to_array
#    GL.Vertex3f(*$v[$faces[i][0]]);
#    GL.Vertex3f(*$v[$faces[i][1]]);
#    GL.Vertex3f(*$v[$faces[i][2]]);
#    GL.Vertex3f(*$v[$faces[i][3]]);
    GL.Vertex($v[$faces[i][0]]);
    GL.Vertex($v[$faces[i][1]]);
    GL.Vertex($v[$faces[i][2]]);
    GL.Vertex($v[$faces[i][3]]);
    GL.End()
  end
end

display = Proc.new {
  GL.Clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);
  drawBox
  GLUT.SwapBuffers
}

def myinit
#  $v[0,0] = $v[1,0] = $v[2,0] = $v[3,0] = -1; 
#  $v[4,0] = $v[5,0] = $v[6,0] = $v[7,0] = 1;
#  $v[0,1] = $v[1,1] = $v[4,1] = $v[5,1] = -1; 
#  $v[2,1] = $v[3,1] = $v[6,1] = $v[7,1] = 1;
#  $v[0,2] = $v[3,2] = $v[4,2] = $v[7,2] = 1; 
#  $v[1,2] = $v[2,2] = $v[5,2] = $v[6,2] = -1;

$v = [[-1, -1,1],[-1, -1,-1], [-1,1,-1], [-1,1,1], [1, -1,1],
      [1, -1,-1], [1, 1,-1], [1,1,1]]

  GL.Light(GL::LIGHT0, GL::DIFFUSE, $light_diffuse);
  GL.Light(GL::LIGHT0, GL::POSITION, $light_position);
  GL.Enable(GL::LIGHT0);
  GL.Enable(GL::LIGHTING);

  GL.Enable(GL::DEPTH_TEST);

  GL.MatrixMode(GL::PROJECTION);
  GLU.Perspective(40.0, 1.0, 1.0,  10.0);
  GL.MatrixMode(GL::MODELVIEW);
  GLU.LookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

  GL.Translate(0.0, 0.0, -1.0);
  GL.Rotate(60, 1.0, 0.0, 0.0);
  GL.Rotate(-20, 0.0, 0.0, 1.0);
end

GLUT.Init
GLUT.InitDisplayMode(GLUT::DOUBLE | GLUT::RGB | GLUT::DEPTH);
GLUT.CreateWindow("red 3D lighted cube");
GLUT.DisplayFunc(display);
myinit
GLUT.MainLoop();
