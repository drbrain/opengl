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

require 'test/unit'

class Test_21 < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_gluniformmatrix21
		return if not supported?(["glCreateProgram","glUniformMatrix2x3fv"])

		vertex_shader_source = "#version 120\n uniform mat2x3 testmat23; uniform mat3x2 testmat32; uniform mat2x4 testmat24; uniform mat4x2 testmat42; uniform mat3x4 testmat34; uniform mat4x3 testmat43; void main() { gl_Position = gl_Vertex * testmat23[0].x * testmat32[0].x * testmat24[0].x * testmat42[0].x * testmat34[0].x * testmat43[0].x;}"

		program = glCreateProgram()
		vs = glCreateShader(GL_VERTEX_SHADER)

		glShaderSource(vs,vertex_shader_source)
		glCompileShader(vs)

		assert_equal(glGetShaderiv(vs,GL_COMPILE_STATUS),GL_TRUE)
		glAttachShader(program,vs)
	
		glLinkProgram(program)	
		assert_equal(glGetProgramiv(program,GL_LINK_STATUS),GL_TRUE)
		glUseProgram(program)
		
		assert((tm23l = glGetUniformLocation(program,"testmat23"))>=0)
		assert((tm32l = glGetUniformLocation(program,"testmat32"))>=0)
		assert((tm24l = glGetUniformLocation(program,"testmat24"))>=0)
		assert((tm42l = glGetUniformLocation(program,"testmat42"))>=0)
		assert((tm34l = glGetUniformLocation(program,"testmat34"))>=0)
		assert((tm43l = glGetUniformLocation(program,"testmat43"))>=0)

		glUniformMatrix2x3fv(tm23l, 1, GL_FALSE, [0,1, 1,0, 0,1])
		assert_equal(glGetUniformfv(program,tm23l),[0,1, 1,0, 0,1])
		glUniformMatrix3x2fv(tm32l, 1, GL_FALSE, [1,0, 0,1, 1,0])
		assert_equal(glGetUniformfv(program,tm32l),[1,0, 0,1, 1,0])

		glUniformMatrix2x4fv(tm24l, 1, GL_FALSE, [0,1, 1,0, 0,1, 1,0])
		assert_equal(glGetUniformfv(program,tm24l),[0,1, 1,0, 0,1, 1,0])
		glUniformMatrix4x2fv(tm42l, 1, GL_FALSE, [1,0, 0,1, 1,0, 0,1])
		assert_equal(glGetUniformfv(program,tm42l),[1,0, 0,1, 1,0, 0,1])

		glUniformMatrix3x4fv(tm34l, 1, GL_FALSE, [0,1,1, 1,0,1, 0,1,1, 1,0,1])
		assert_equal(glGetUniformfv(program,tm34l),[0,1,1, 1,0,1, 0,1,1, 1,0,1])
		glUniformMatrix4x3fv(tm43l, 1, GL_FALSE, [1,0,0, 0,1,0, 1,0,0, 0,1,0])
		assert_equal(glGetUniformfv(program,tm43l),[1,0,0, 0,1,0, 1,0,0, 0,1,0])
	end
end