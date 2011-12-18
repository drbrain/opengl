# This example comes from the Red Book chapter 5, example 5-1 light.c

require 'opengl'

def init
  mat_specular = [1, 1, 1, 1]
  mat_shininess = [50]
  light_position = [1, 1, 1, 0]
  glClearColor 0, 0, 0, 0
  glShadeModel GL_SMOOTH

  glMaterialfv GL_FRONT, GL_DIFFUSE, mat_specular
  glMaterialfv GL_FRONT, GL_SPECULAR, mat_specular
  glMaterialfv GL_FRONT, GL_SHININESS, mat_shininess
  glLightfv GL_LIGHT0, GL_POSITION, light_position

  glEnable GL_LIGHTING
  glEnable GL_LIGHT0
  glEnable GL_DEPTH_TEST
end

def display
  glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
  glutSolidSphere 1.0, 20, 16
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
    glutDestroyWindow @window
    exit 0
  end

  glutPostRedisplay
end

glutInit
glutInitDisplayMode GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH
glutInitWindowSize 500, 500
glutInitWindowPosition 100, 100
glutCreateWindow 'example 5-1: light'
init
glutDisplayFunc :display
glutReshapeFunc :reshape
glutKeyboardFunc :keyboard
glutMainLoop

