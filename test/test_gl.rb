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
require 'gl'
require 'glut'
include Gl
include Glut

class TestGl < OpenGL::TestCase
	def test_isavailable
		assert_equal(is_available?(1.1),true)
		assert_equal(is_available?("GL_ARB_multitexture"),true)
		assert_equal(is_available?("GL_NON_EXISTENT"),false)
	end

	def test_errorchecking
		Gl.disable_error_checking
		assert_equal(Gl.is_error_checking_enabled?,false)
		Gl.enable_error_checking
		assert_equal(Gl.is_error_checking_enabled?,true)
		begin
			glEnable(0)	
		rescue Gl::Error => err
		  assert_equal(err.id,GL_INVALID_ENUM)
		else
			assert(false) # error not detected
		end
	end
end
