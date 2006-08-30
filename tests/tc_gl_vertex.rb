#--
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
#++

if __FILE__ == $0
    # If we are being called from the command line, e.g., ruby foo.rb, then
    # fixup the load path so we can find the OpenGL extension libs
    $: << File.join(File.dirname(__FILE__), '..', 'ext')
end

require 'test/unit'
require 'gl/GL'
require 'glut/GLUT'
include GL
include GLUT

class GlVertexTest < Test::Unit::TestCase

    # Test the glVertex2{dfs} calls
    def test_gl_vertex2x
        one_time_glut_init
        %w( glVertex2d glVertex2f glVertex2s ).each do |s|
            begin
                puts "\n=== Running with: #{s}"
                run_with(s)
            rescue StopGlutMain
                # Ignore
            end
        end
    end

    def one_time_glut_init
        puts "=== one_time_glut_init"
        glutInit
        glutInitWindowSize(600, 600)
    end

    def init
        puts "=== init"
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity
        # Give us a 20x20x20 cube to display in centered on the origin
        glOrtho(-10, 10, -10, 10, -10, 10)
    end

    def run_with(gl_vertex_method)
        display = lambda do
            glColor3f( 1.0, 1.0, 1.0 )

            glBegin( GL_POLYGON )
                send(gl_vertex_method, -1.5, -1.5 )
                send(gl_vertex_method, -1.5,  1.5 )
                send(gl_vertex_method,  1.5,  1.5 )
                send(gl_vertex_method,  1.5, -1.5 )
            glEnd
            glFlush
        end

        keyboard = lambda do |key, x, y|
            case(key)
            when 27
                raise StopGlutMain.new
            end
        end
        glutCreateWindow("#{__FILE__} : #{gl_vertex_method}");
        init
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard)
        glutMainLoop;
    end
end

class StopGlutMain < RuntimeError
    # This Exception is just used to break out of the glutMainLoop.
    #
    # The Mac OS X version of glut has the glutCheckLoop/glutWMCloseFunc
    # pair, but in general, we can't rely on something beyond the really
    # old 98 version of GLUT being installed.
end

