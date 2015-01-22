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

require 'opengl/test_case'

class TestGl < OpenGL::TestCase
  def test_isavailable
    assert_equal(true, is_available?(1.1))
    assert_equal(true, is_available?("GL_ARB_multitexture"))
    assert_equal(false, is_available?("GL_NON_EXISTENT"))
  end

  def test_errorchecking
    Gl.disable_error_checking
    assert_equal(false, Gl.is_error_checking_enabled?)
    Gl.enable_error_checking
    assert_equal(true, Gl.is_error_checking_enabled?)
    begin
      glEnable(0)
    rescue Gl::Error => err
      assert_equal(err.id, GL_INVALID_ENUM)
    else
      assert(false) # error not detected
    end
  end

  def test_implementation
    old_glimpl = Gl.implementation
    Gl.implementation = Gl::DEFAULT_IMPLEMENTATION.open

    refute_equal old_glimpl, Gl.implementation
  end
end
