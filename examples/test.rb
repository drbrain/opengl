# Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
#
# This program is distributed under the terms of the MIT license.
# See the included MIT-LICENSE file for the terms of this license.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

require '../ext/glut/glut'
require '../ext/gl/gl'

class GlutTest

  def initialize
    puts "=== GlutTest.initialize ==="
    # Setup the GLUT display loop callback
    @display = lambda do
      puts "=== In display routine"
      Gl.glClear( Gl::GL_COLOR_BUFFER_BIT | Gl::GL_DEPTH_BUFFER_BIT )
      Gl.glColor3f( 1.0, 1.0, 1.0 )

      Gl.glBegin( Gl::GL_POLYGON )

      Gl.glVertex2f( -0.5, -0.5 )
      Gl.glVertex2f( -0.5,  0.5 )
      Gl.glVertex2f(  0.5,  0.5 )
      Gl.glVertex2f(  0.5, -0.5 )

      Gl.glEnd

      Gl.glFlush
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
    Glut.glutInit
    Glut.glutInitDisplayMode( Glut::GLUT_DOUBLE | Glut::GLUT_RGB | Glut::GLUT_DEPTH )
    Glut.glutCreateWindow( 'pbm' )
    Glut.glutDisplayFunc( @display )
    #Glut.glutReshapeFunc( @reshape )
    Glut.glutKeyboardFunc( @keyboard ) if @keyboard
    Glut.glutMainLoop
  end
end

if __FILE__ == $0
  gt = GlutTest.new
  gt.show
end

