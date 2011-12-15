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

class TestGlExtAti < OpenGL::TestCase
	def setup
		super()
	end

	def teardown
		super()
	end

	def test_gl_ati_draw_buffers
		supported?("GL_ATI_draw_buffers")
		glDrawBuffersATI([GL_BACK_LEFT,GL_FRONT_LEFT])
		assert_equal(glGetIntegerv(GL_DRAW_BUFFER0),GL_BACK_LEFT)
		assert_equal(glGetIntegerv(GL_DRAW_BUFFER1),GL_FRONT_LEFT)
	end
end
