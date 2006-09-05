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


# Yet to test

# glVertex2dv
# glVertex2fv
# glVertex2iv
# glVertex2sv

# glVertex3dv
# glVertex3fv
# glVertex3iv
# glVertex3sv

# glVertex4dv
# glVertex4fv
# glVertex4iv
# glVertex4sv

class GlVertexTest < Test::Unit::TestCase


    # Test the existence of
    #   glVertex2d
    #   glVertex2f
    #   glVertex2i
    #   glVertex2s
    def test_gl_vertex2x
        one_time_glut_init
        # These parameters define a small box
        params = [
            [-1.5, -1.5],
            [-1.5,  1.5],
            [ 1.5,  1.5],
            [ 1.5, -1.5]
        ]
        run_with(%w( glVertex2d glVertex2f glVertex2i glVertex2s ), params)
    end

    # Test the existence of
    #   glVertex3d
    #   glVertex3f
    #   glVertex3i
    #   glVertex3s
    def test_gl_vertex3x
        one_time_glut_init
        # These parameters define a small box
        params = [
            [-1.5, -1.5, 0],
            [-1.5,  1.5, 0],
            [ 1.5,  1.5, 0],
            [ 1.5, -1.5, 0]
        ]
        run_with(%w( glVertex3d glVertex3f glVertex3i glVertex3s ), params)
    end

    # Test the existence of
    #   glVertex4d
    #   glVertex4f
    #   glVertex4i
    #   glVertex4s
    def test_gl_vertex4x
        one_time_glut_init
        # These parameters define a small box
        params = [
            [-1.5, -1.5, 0, 1],
            [-1.5,  1.5, 0, 1],
            [ 1.5,  1.5, 0, 1],
            [ 1.5, -1.5, 0, 1]
        ]
        run_with(%w( glVertex4d glVertex4f glVertex4i glVertex4s ), params)
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

    # Run several related tests.  gl_vertex_methods, is an array of method
    # names that are appropriate to run against the arity of params.  E.g.,
    # if gl_vertex_methods was ["glVertex2f", "glVertex2d", ... ] and
    # params was [ [-1.5, -1.5], [-1.5, 1.5], [ 1.5, 1.5], [ 1.5, -1.5] ],
    # then calling run_with(gl_vertex_methods, params) would be equivalent
    # to running the following test cases:
    #
    #   glBegin(GL_POLYGON)
    #     glVertex2f(-1.5, -1.5)
    #     glVertex2f(-1.5,  1.5)
    #     glVertex2f( 1.5,  1.5)
    #     glVertex2f( 1.5, -1.5)
    #   glEnd
    #   ...
    #   glBegin(GL_POLYGON)
    #     glVertex2d(-1.5, -1.5)
    #     glVertex2d(-1.5,  1.5)
    #     glVertex2d( 1.5,  1.5)
    #     glVertex2d( 1.5, -1.5)
    #   glEnd
    #
    def run_with(gl_vertex_methods, params)
        gl_vertex_methods.each do |mn|
            display = lambda do
                glColor3f( 1.0, 1.0, 1.0 )

                glBegin(GL_POLYGON)
                # The send(...) basically do something like:
                #   glVertex2d( -1.5, -1.5 )
                # or
                #   glVertex3d( -1.5, -1.5, 0 )
                # or
                #   glVertex4f( -1.5, -1.5, 0, 1 )
                #
                params.each {|p| send(mn, *p)}
                glEnd
                glFlush
            end

            keyboard = lambda do |key, x, y|
                case(key)
                when 27
                    raise StopGlutMain.new
                end
            end
            glutCreateWindow("#{__FILE__} : #{mn}");
            init
            glutDisplayFunc(display);
            glutKeyboardFunc(keyboard)
            begin
                glutMainLoop;
            rescue StopGlutMain
                # Ignore
            end
        end
    end
end

class StopGlutMain < RuntimeError
    # This Exception is just used to break out of the glutMainLoop.
    #
    # The Mac OS X version of glut has the glutCheckLoop/glutWMCloseFunc
    # pair, but in general, we can't rely on something beyond the really
    # old 98 version of GLUT being installed.
end

