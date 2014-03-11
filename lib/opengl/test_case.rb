#
# Copyright (C) 2007 Jan Dvorak <jan.dvorak@kraxnet.cz>
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
#

require 'rubygems'
begin
  gem 'minitest'
rescue Gem::LoadError
end

require 'minitest/autorun'
require 'gl'
require 'glu'
require 'glut'
require 'matrix'

include Gl
include Glu
include Glut

Gl.enable_error_checking

module OpenGL; end

class OpenGL::TestCase < MiniTest::Unit::TestCase

  WINDOW_SIZE = 512

  glutInit
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL |
                      GLUT_ACCUM | GLUT_ALPHA)

  def setup
    glutInitWindowPosition 1, 1
    glutInitWindowSize WINDOW_SIZE, WINDOW_SIZE
    @window = glutCreateWindow "test"

    glPushAttrib GL_ALL_ATTRIB_BITS
    glPushClientAttrib GL_CLIENT_ALL_ATTRIB_BITS
    glMatrixMode GL_MODELVIEW
    glLoadIdentity
    glMatrixMode GL_PROJECTION
    glLoadIdentity

    glClearColor 0, 0, 0, 0
    glClear GL_COLOR_BUFFER_BIT
  end

  def teardown
    glPopAttrib
    glPopClientAttrib
    glRenderMode GL_RENDER

    # in case there is an GL error that escaped error checking routines ...
    error = glGetError
    assert_equal 0, error, gluErrorString(error)

    glutDestroyWindow @window
  end

  def assert_each_in_delta expected, actual, epsilon = 0.01
    assert_equal expected.length, actual.length, 'array lengths do not match'

    expected.flatten.zip(actual.flatten).each_with_index do |(e, a), i|
      assert_in_delta e, a, epsilon, "element #{i}"
    end
  end

  def supported? funcs
    Array(funcs).each do |name| # convert to array if it isn't already
      skip "#{name} is not supported" unless Gl.is_available? name
    end
  end

end
