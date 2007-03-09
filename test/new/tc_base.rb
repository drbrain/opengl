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

require 'gltest_glut'

include GL_func

class GLtest_1
	def initialize
		projection_ortho_box(5)
	end
	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		Gl.glColor3f(1,0,0)

		Gl.glBegin(Gl::GL_QUADS)
		Gl.glVertex3f(-1,-1,0)
		Gl.glVertex3d( 1,-1,0)
		Gl.glVertex3f( 1, 1,0)
		Gl.glVertex3f(-1, 1,0)
		Gl.glEnd
	end
	def destroy
	end
end

class GLtest_2
	def initialize
		projection_ortho_box
	end
	def loop
		clear_screen_and_depth_buffer
		print_text("Hello",256,256,[0,255,0],Glut::GLUT_BITMAP_TIMES_ROMAN_24)
	end
	def destroy
	end
end

Test_Runner.new("GLtest_","base tests")
