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

class Test_20 < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_glblendequationseparate
		return if not supported?(2.0)
		glBlendEquationSeparate(GL_MIN,GL_MAX)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB),GL_MIN)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA),GL_MAX)
		glBlendEquationSeparate(GL_MAX,GL_MIN)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB),GL_MAX)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA),GL_MIN)
	end

	def test_stencilops
		return if not supported?(2.0)

		glStencilOpSeparate(GL_FRONT, GL_ZERO, GL_INCR, GL_DECR)
		assert_equal(glGetIntegerv(GL_STENCIL_FAIL), GL_ZERO)
		assert_equal(glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL), GL_INCR)
		assert_equal(glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS), GL_DECR)
		glStencilOpSeparate(GL_FRONT, GL_INCR, GL_DECR, GL_ZERO)
		assert_equal(glGetIntegerv(GL_STENCIL_FAIL), GL_INCR)
		assert_equal(glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL), GL_DECR)
		assert_equal(glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS), GL_ZERO)

		glStencilFuncSeparate(GL_FRONT, GL_LEQUAL, 1, 0)
		assert_equal(glGetIntegerv(GL_STENCIL_FUNC),GL_LEQUAL)
		assert_equal(glGetIntegerv(GL_STENCIL_REF),1)
		assert_equal(glGetIntegerv(GL_STENCIL_VALUE_MASK),0)
		glStencilFuncSeparate(GL_FRONT, GL_GEQUAL, 0, 1)
		assert_equal(glGetIntegerv(GL_STENCIL_FUNC),GL_GEQUAL)
		assert_equal(glGetIntegerv(GL_STENCIL_REF),0)
		assert_equal(glGetIntegerv(GL_STENCIL_VALUE_MASK),1)

		glStencilMaskSeparate(GL_FRONT,1)
		assert_equal(glGetIntegerv( GL_STENCIL_WRITEMASK),1)
		glStencilMaskSeparate(GL_FRONT,0)
		assert_equal(glGetIntegerv(GL_STENCIL_WRITEMASK),0)
	end

	def test_gldrawbuf
		return if not supported?(2.0)
		glDrawBuffers([GL_FRONT_LEFT,GL_BACK_LEFT])
		assert_equal(glGetIntegerv(GL_DRAW_BUFFER0),GL_FRONT_LEFT)
		assert_equal(glGetIntegerv(GL_DRAW_BUFFER1),GL_BACK_LEFT)
	end

	def test_glvertexattrib
		return if not supported?(2.0)
		# 1
		glVertexAttrib1d(1,2.0)
		assert_equal(glGetVertexAttribdv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,0.0,0.0,1.0])
		glVertexAttrib1dv(1,[3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,0.0,0.0,1.0])
		glVertexAttrib1f(1,2.0)
		assert_equal(glGetVertexAttribiv(1,GL_CURRENT_VERTEX_ATTRIB), [2,0,0,1])
		glVertexAttrib1fv(1,[3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,0.0,0.0,1.0])
		glVertexAttrib1s(1,2)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,0.0,0.0,1.0])
		glVertexAttrib1sv(1,[3])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,0.0,0.0,1.0])
		# 2
		glVertexAttrib2d(1,2.0,2.0)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,0.0,1.0])
		glVertexAttrib2dv(1,[3.0,3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,0.0,1.0])
		glVertexAttrib2f(1,2.0,2.0)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,0.0,1.0])
		glVertexAttrib2fv(1,[3.0,3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,0.0,1.0])
		glVertexAttrib2s(1,2,2)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,0.0,1.0])
		glVertexAttrib2sv(1,[3,3])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,0.0,1.0])
		# 3
		glVertexAttrib3d(1,2.0,2.0,2.0)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,2.0,1.0])
		glVertexAttrib3dv(1,[3.0,3.0,3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,3.0,1.0])
		glVertexAttrib3f(1,2.0,2.0,2.0)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,2.0,1.0])
		glVertexAttrib3fv(1,[3.0,3.0,3.0])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,3.0,1.0])
		glVertexAttrib3s(1,2,2,2)
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [2.0,2.0,2.0,1.0])
		glVertexAttrib3sv(1,[3,3,3])
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [3.0,3.0,3.0,1.0])
		# 4N
		glVertexAttrib4Nbv(1,[2**7-1,2**7-1,2**7-1,2**7-1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4Niv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4Nsv(1,[2**15-1,2**15-1,2**15-1,2**15-1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4Nub(1,0,0,0,0)
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4Nubv(1,[2**8-1,2**8-1,2**8-1,2**8-1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4Nuiv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4Nusv(1,[2**16-1,2**16-1,2**16-1,2**16-1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		# 4
		glVertexAttrib4bv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4d(1,1,1,1,1)
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4dv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4f(1,1,1,1,1)
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4fv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4iv(1,[1,1,1,1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4s(1,0,0,0,0)
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4sv(1,[1,1,1,1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4ubv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
		glVertexAttrib4uiv(1,[1,1,1,1])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [1,1,1,1]))
		glVertexAttrib4usv(1,[0,0,0,0])
		assert(approx_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB), [0,0,0,0]))
	end

	def test_vertexattribpointer
		return if not supported?(2.0)
		
		vaa = [1,1,1,1, 2,2,2,2].pack("f*")
		glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,vaa)
		assert_equal(glGetVertexAttribPointerv(1),vaa)

		glEnableVertexAttribArray(1)

		glBegin(GL_POINTS)
		glArrayElement(1)
		glEnd()
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB),[2,2,2,2])
		
		glDisableVertexAttribArray(1)
	end

	def test_shaders
		return if not supported?(2.0)

		vertex_shader_source = "void main() { gl_Position = ftransform();}"
	
		program = glCreateProgram()
		assert_equal(glIsProgram(program),true)

		vs = glCreateShader(GL_VERTEX_SHADER)
		assert_equal(glIsShader(vs),true)

		glShaderSource(vs,vertex_shader_source)
		assert_equal(glGetShaderSource(vs),vertex_shader_source)

		assert_equal(glGetShaderiv(vs, GL_SHADER_TYPE),GL_VERTEX_SHADER)
		glCompileShader(vs)
		assert_equal(glGetShaderiv(vs,GL_COMPILE_STATUS),GL_TRUE)

		vslog = glGetShaderInfoLog(vs)
		assert_equal(vslog.class,String)

		glAttachShader(program,vs)
		assert_equal(glGetAttachedShaders(program),vs)
		glDetachShader(program,vs)
		assert_equal(glGetAttachedShaders(program),nil)
		glAttachShader(program,vs)

		glValidateProgram(program)
		assert_equal(glGetProgramiv(program,GL_VALIDATE_STATUS),GL_TRUE)
		prlog = glGetProgramInfoLog(program)
		assert_equal(prlog.class,String)

		glLinkProgram(program)
		assert_equal(glGetProgramiv(program,GL_LINK_STATUS),GL_TRUE)
	
		glUseProgram(program)
		assert_equal(glGetIntegerv(GL_CURRENT_PROGRAM),program)

		glUseProgram(0)

		glDetachShader(program,vs)
		glDeleteShader(vs)
		assert_equal(glIsShader(vs),false)

		glDeleteProgram(program)
		assert_equal(glIsProgram(program),false)
	end

	def test_shaders_2
		return if not supported?(2.0)

		vertex_shader_source = "attribute vec4 test; uniform float testvec1; uniform vec2 testvec2; uniform vec3 testvec3; uniform vec4 testvec4; uniform int testivec1; uniform ivec2 testivec2; uniform ivec3 testivec3; uniform ivec4 testivec4; void main() { gl_Position = testvec1 * test * testvec2.x * testvec3.x * testivec1 * testivec2.x * testivec3.x * testivec4.x + testvec4;}"
		program = glCreateProgram()
		vs = glCreateShader(GL_VERTEX_SHADER)

		glShaderSource(vs,vertex_shader_source)
		glCompileShader(vs)

		assert_equal(glGetShaderiv(vs,GL_COMPILE_STATUS),GL_TRUE)
		glAttachShader(program,vs)
		
		glBindAttribLocation(program,2,"test")
		glLinkProgram(program)	
		assert_equal(glGetProgramiv(program,GL_LINK_STATUS),GL_TRUE)
		glUseProgram(program)
	
		assert_equal(glGetAttribLocation(program,"test"),2)
		assert((tv1l = glGetUniformLocation(program,"testvec1"))>=0)
		assert((tv2l = glGetUniformLocation(program,"testvec2"))>=0)
		assert((tv3l = glGetUniformLocation(program,"testvec3"))>=0)
		assert((tv4l = glGetUniformLocation(program,"testvec4"))>=0)
		assert((tv1il = glGetUniformLocation(program,"testivec1"))>=0)
		assert((tv2il = glGetUniformLocation(program,"testivec2"))>=0)
		assert((tv3il = glGetUniformLocation(program,"testivec3"))>=0)
		assert((tv4il = glGetUniformLocation(program,"testivec4"))>=0)

		##
		assert_equal(glGetActiveAttrib(program,0),[1,GL_FLOAT_VEC4,"test"])
		assert_equal(glGetActiveUniform(program,tv1il),[1,GL_INT,"testivec1"])

		# f
		glUniform1f(tv1l,2.0)
		assert_equal(glGetUniformfv(program,tv1l),2.0)
		glUniform2f(tv2l,2.0,2.0)
		assert_equal(glGetUniformfv(program,tv2l),[2.0,2.0])
		glUniform3f(tv3l,2.0,2.0,2.0)
		assert_equal(glGetUniformfv(program,tv3l),[2.0,2.0,2.0])
		glUniform4f(tv4l,2.0,2.0,2.0,2.0)
		assert_equal(glGetUniformfv(program,tv4l),[2.0,2.0,2.0,2.0])
		# i 
		glUniform1i(tv1il,3)
		assert_equal(glGetUniformiv(program,tv1il),3)
		glUniform2i(tv2il,3,3)
		assert_equal(glGetUniformiv(program,tv2il),[3,3])
		glUniform3i(tv3il,3,3,3)
		assert_equal(glGetUniformiv(program,tv3il),[3,3,3])
		glUniform4i(tv4il,3,3,3,3)
		assert_equal(glGetUniformiv(program,tv4il),[3,3,3,3])
		# fv
		glUniform1fv(tv1l,[3.0])
		assert_equal(glGetUniformfv(program,tv1l),3.0)
		glUniform2fv(tv2l,[3.0,3.0])
		assert_equal(glGetUniformfv(program,tv2l),[3.0,3.0])
		glUniform3fv(tv3l,[3.0,3.0,3.0])
		assert_equal(glGetUniformfv(program,tv3l),[3.0,3.0,3.0])
		glUniform4fv(tv4l,[3.0,3.0,3.0,3.0])
		assert_equal(glGetUniformfv(program,tv4l),[3.0,3.0,3.0,3.0])
		# iv
		glUniform1iv(tv1il,[2])
		assert_equal(glGetUniformiv(program,tv1il),2)
		glUniform2iv(tv2il,[2,2])
		assert_equal(glGetUniformiv(program,tv2il),[2,2])
		glUniform3iv(tv3il,[2,2,2])
		assert_equal(glGetUniformiv(program,tv3il),[2,2,2])
		glUniform4iv(tv4il,[2,2,2,2])
		assert_equal(glGetUniformiv(program,tv4il),[2,2,2,2])

		glDeleteShader(vs)
		glDeleteProgram(program)
	end

	def test_shaders_3
		return if not supported?(2.0)

		vertex_shader_source = "uniform mat2 testmat2; uniform mat3 testmat3; uniform mat4 testmat4; void main() { gl_Position = gl_Vertex * testmat4[0].x * testmat3[0].x * testmat2[0].x;}"

		program = glCreateProgram()
		vs = glCreateShader(GL_VERTEX_SHADER)

		glShaderSource(vs,vertex_shader_source)
		glCompileShader(vs)

		assert_equal(glGetShaderiv(vs,GL_COMPILE_STATUS),GL_TRUE)
		glAttachShader(program,vs)
	
		glLinkProgram(program)	
		assert_equal(glGetProgramiv(program,GL_LINK_STATUS),GL_TRUE)
		glUseProgram(program)
		#
		assert((tm2l = glGetUniformLocation(program,"testmat2"))>=0)
		assert((tm3l = glGetUniformLocation(program,"testmat3"))>=0)
		assert((tm4l = glGetUniformLocation(program,"testmat4"))>=0)

		glUniformMatrix2fv(tm2l, 1, GL_TRUE, [0,1, 1,0])
		assert_equal(glGetUniformfv(program,tm2l),[0,1,1,0])

		glUniformMatrix3fv(tm3l, 1, GL_TRUE, [0,1,0, 1,0,1, 0,1,0])
		assert_equal(glGetUniformfv(program,tm3l),[0,1,0, 1,0,1, 0,1,0])

		glUniformMatrix4fv(tm4l, 1, GL_TRUE, [0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0])
		assert_equal(glGetUniformfv(program,tm4l),[0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0])
	end


	def test_buffered_vertexattribpointer
		return if not supported?(2.0)

		vaa = [1,1,1,1, 2,2,2,2].pack("f*")

		buffers = glGenBuffers(1)

		glBindBuffer(GL_ARRAY_BUFFER,buffers[0])
		glBufferData(GL_ARRAY_BUFFER,8*4,vaa,GL_DYNAMIC_DRAW)
		
		glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0)
		assert_equal(glGetVertexAttribPointerv(1),0)
		
		glEnableVertexAttribArray(1)
		
		glBegin(GL_POINTS)
		glArrayElement(1)
		glEnd()
		assert_equal(glGetVertexAttribfv(1,GL_CURRENT_VERTEX_ATTRIB),[2,2,2,2])
		
		glDisableVertexAttribArray(1)
		glDeleteBuffers(buffers)
	end
end
