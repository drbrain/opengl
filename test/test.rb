#
# Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
require '../ext/glut/GLUT'
require '../ext/gl/GL'

class GlutTest

  def initialize
    puts "=== GlutTest.initialize ==="
    # Setup the GLUT display loop callback
    @display = lambda do
      puts "=== In display routine"
      GL.glClear( GL::GL_COLOR_BUFFER_BIT | GL::GL_DEPTH_BUFFER_BIT )
      GL.glColor3f( 1.0, 1.0, 1.0 )

      GL.glBegin( GL::GL_POLYGON )

      GL.glVertex2f( -0.5, -0.5 )
      GL.glVertex2f( -0.5,  0.5 )
      GL.glVertex2f(  0.5,  0.5 )
      GL.glVertex2f(  0.5, -0.5 )

      GL.glEnd

      GL.glFlush
    end

    # Keyboard handler to exit when ESC is typed
    @keyboard = lambda do |key, x, y|
      case(key)
      when 27
        exit(0)
      end
    end
  end

  def show
    puts "=== GlutTest.show ==="
    GLUT.glutInit
    GLUT.glutInitDisplayMode( GLUT::GLUT_DOUBLE | GLUT::GLUT_RGB | GLUT::GLUT_DEPTH )
    GLUT.glutCreateWindow( 'pbm' )
    GLUT.glutDisplayFunc( @display )
    #GLUT.glutReshapeFunc( @reshape )
    GLUT.glutKeyboardFunc( @keyboard ) if @keyboard
    GLUT.glutMainLoop
  end
end

if __FILE__ == $0
  gt = GlutTest.new
  gt.show
end

