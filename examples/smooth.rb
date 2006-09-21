require "../ext/gl/gl"
require "../ext/glut/glut"

STDOUT.sync=TRUE
disp = Proc.new {
  Gl.glClear(Gl::GL_COLOR_BUFFER_BIT)
  Gl.glBegin(Gl::GL_TRIANGLES)
    Gl.glColor(0.0, 0.0, 1.0)
    Gl.glVertex(0, 0)
    Gl.glColor(0.0, 1.0, 0.0)
    Gl.glVertex(200, 200)
    Gl.glColor(1.0, 0.0, 0.0)
    Gl.glVertex(20, 200)
  Gl.glEnd
  Gl.glFlush
}

reshape = Proc.new {|w, h|
  Gl.glViewport(0, 0, w, h)
  Gl.glMatrixMode(Gl::GL_PROJECTION)
  Gl.glLoadIdentity
  Gl.glOrtho(0, w, 0, h, -1, 1)
  Gl.glScale(1, -1, 1)
  Gl.glTranslate(0, -h, 0)
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
