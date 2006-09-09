#require "../ext/gl"
#require '../lib/opengl_c'

require "./gl"
require "./glut"
#require '../lib/glut_c'

STDOUT.sync=TRUE
disp = Proc.new {
  Gl.glClear(Gl::GL_COLOR_BUFFER_BIT)
  Gl.glBegin(Gl::GL_TRIANGLES)
    Gl.glColor3f(0.0, 0.0, 1.0)
    Gl.glVertex2f(0, 0)
    Gl.glColor3f(0.0, 1.0, 0.0)
    Gl.glVertex2f(200, 200)
    Gl.glColor3f(1.0, 0.0, 0.0)
    Gl.glVertex2f(20, 200)
  Gl.glEnd
  Gl.glFlush
}

reshape = Proc.new {|w, h|
  Gl.glViewport(0, 0, w, h)
  Gl.glMatrixMode(Gl::GL_PROJECTION)
  Gl.glLoadIdentity
  Gl.glOrtho(0, w, 0, h, -1, 1)
  Gl.glScalef(1, -1, 1)
  Gl.glTranslatef(0, -h, 0)
}

# Keyboard handler to exit when ESC is typed
keyboard = lambda do |key, x, y|
    case(key)
    when 27
        exit(0)
    end
end

Glut.glutInit
a =  Glut.glutCreateWindow("single triangle");
Glut.glutDisplayFunc(disp);
Glut.glutReshapeFunc(reshape);
Glut.glutKeyboardFunc( keyboard )
Glut.glutMainLoop;
