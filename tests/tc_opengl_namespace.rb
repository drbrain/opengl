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
require 'test/unit'
require '../lib/opengl'

# Test that a require of the opengl convenience lib requires and includes
# the proper OpenGL, GLU and GLUT namespaces.
class OpenglTest < Test::Unit::TestCase

    def test_gl_constant
        assert_equal 1, GL::GL_VERSION_1_1
        assert_equal 1, GL_VERSION_1_1
    end

    def test_glut_constant
        assert_equal 5, GLUT::GLUT_API_VERSION
        assert_equal 5, GLUT_API_VERSION
    end

    def test_glu_constant
        fail "GLU not implemented yet"        
    end
end
