# This example comes from the Red Book chapter 5, example 5-1 light.c

require 'opengl'
require 'mathn'

def init
  @fullscreen = false
  @xrot = 0
  @yrot = 0
  @zrot = 0

  glClearColor 0, 0, 0, 0
  glShadeModel GL_SMOOTH

  glMaterialfv GL_FRONT, GL_DIFFUSE, [1, 0, 0, 1]
  glMaterialfv GL_FRONT, GL_SPECULAR, [0, 1, 0, 1]
  glMaterialfv GL_FRONT, GL_AMBIENT, [0, 0, 0.75, 1]
  glMaterialfv GL_FRONT, GL_SHININESS, [40]
  glLightfv GL_LIGHT0, GL_POSITION, [0, 1, -0.25]

  glEnable GL_LIGHTING
  glEnable GL_LIGHT0
  glEnable GL_DEPTH_TEST
  glEnable GL_NORMALIZE
end

def cross_product a, b
  Vector[a[1] * b[2] - a[2] * b[1],
         a[2] * b[0] - a[0] * b[2],
         a[0] * b[1] - a[1] * b[0]]
end

def normal v1, v2, v3
  cross_product v1 - v2, v2 - v3
end

def normals_for_triangle_fan vertexes
  center = vertexes.first

  vertex_normals = vertexes[1..-1].each_cons(2).map do |a, b|
    normal center, a, b
  end

  normals = vertex_normals.each_cons(2).map do |a, b|
    a + b
  end

  normals.unshift vertex_normals.first(3).inject :+
  normals.push vertex_normals.first + vertex_normals.last
  normals.push normals[1]

  normals
end

def display
  glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
  glLoadIdentity
  #glutSolidSphere 1.0, 50, 50
  glRotate @xrot, 1, 0, 0
  glRotate @yrot, 0, 1, 0
  glRotate @zrot, 0, 0, 1

  #glBegin GL_POLYGON do
  #  glVertex2f -1,  1
  #  glVertex2f  1,  1
  #  glVertex2f  1, -1
  #  glVertex2f -1, -1
  #end

  glMaterialfv GL_FRONT_AND_BACK, GL_DIFFUSE,  [1, 1, 1, 1]
  glMaterialfv GL_FRONT_AND_BACK, GL_SPECULAR, [1, 1, 1, 1]
  glMaterialfv GL_FRONT_AND_BACK, GL_AMBIENT,  [1, 1, 1, 1]
  glMaterialfv GL_FRONT, GL_SHININESS, [40]
  glBegin GL_LINES do
    glVertex3f 0, 0, 0
    glVertex3f 0, 0, 1
  end

  glMaterialfv GL_FRONT, GL_DIFFUSE, [1, 0, 0, 1]
  glMaterialfv GL_FRONT, GL_SPECULAR, [0, 1, 0, 1]
  glMaterialfv GL_FRONT, GL_AMBIENT, [0, 0, 0.75, 1]
  glMaterialfv GL_FRONT, GL_SHININESS, [40]

  vertices = [
    Vector[ 0.00, -0.4,  0.1],
    Vector[ 0.00,  0.5,  0.0],
    Vector[ 0.24, -0.5,  0.0],
    Vector[-0.24, -0.5,  0.0],
    Vector[ 0.00,  0.5,  0.0],
  ]

  normals = normals_for_triangle_fan vertices

  glBegin GL_TRIANGLE_FAN do
    normals.zip(vertices).each do |normal, vertex|
      glNormal3fv normal
      glVertex3fv vertex
    end
  end
  glFlush
end

def reshape w, h
  glViewport 0, 0, w, h
  glMatrixMode GL_PROJECTION
  glLoadIdentity

  if w <= h then
    glOrtho -1.5, 1.5, -1.5 * h / w, 1.5 * h / w, -10.0, 10.0
  else
    glOrtho -1.5 * w / h, 1.5 * w / h, -1.5, 1.5, -10.0, 10.0
  end

  glMatrixMode GL_MODELVIEW
  glLoadIdentity
end

def keyboard key, x, y
  case key
  when ?\e
    glutDestroyWindow $window
    exit 0
  when 'X' then @xrot += 1
  when 'x' then @xrot -= 1
  when 'Y' then @yrot += 1
  when 'y' then @yrot -= 1
  when 'Z' then @zrot += 1
  when 'z' then @zrot -= 1
  when 'F' then
    @fullscreen = !@fullscreen

    if @fullscreen then
      glutFullScreen
    else
      glutPositionWindow 0, 0
    end
  end

  p key => [@xrot, @yrot, @zrot]

  glutPostRedisplay
end

glutInit
glutInitDisplayMode GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH
glutInitWindowSize 500, 500
glutInitWindowPosition 100, 100
$window = glutCreateWindow 'example 5-1: light'
init
glutDisplayFunc :display
glutReshapeFunc :reshape
glutKeyboardFunc :keyboard
glutMainLoop

