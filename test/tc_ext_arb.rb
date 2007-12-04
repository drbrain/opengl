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

class Test_EXT_ARB < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_gl_arb_transpose_matrix
		return if not supported?("GL_ARB_transpose_matrix")
		m_a = [[1.0,2.0,3.0,4.0],
					 [0.0,2.0,0.0,0.0],
					 [0.0,0.0,2.0,0.0],
					 [0.0,0.0,0.0,2.0]]

		m_b = [[1.0,2.0,3.0,4.0],
					 [0.0,3.0,0.0,0.0],
					 [0.0,0.0,3.0,0.0],
					 [0.0,0.0,0.0,3.0]]

		glMatrixMode(GL_MODELVIEW)
		glLoadTransposeMatrixfARB(m_a)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_a)

		glLoadTransposeMatrixdARB(m_b)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_b)

		glLoadIdentity()
		glMultTransposeMatrixfARB(m_a)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_a)

		glLoadIdentity()
		glMultTransposeMatrixdARB(m_b)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_b)

		# 2
		m = Matrix.rows([[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]])
		glMatrixMode(GL_MODELVIEW)
		glLoadTransposeMatrixfARB(m)
		assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
		glLoadIdentity()
		glLoadTransposeMatrixdARB(m)
		assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
		glLoadIdentity()
		glMultTransposeMatrixfARB(m)
		assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
		glLoadIdentity()
		glMultTransposeMatrixdARB(m)
		assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)

		assert_raise ArgumentError do glLoadTransposeMatrixfARB([1,2,3,4]) end
		assert_raise ArgumentError do glLoadTransposeMatrixdARB([1,2,3,4]) end
		assert_raise ArgumentError do glMultTransposeMatrixfARB([1,2,3,4]) end
		assert_raise ArgumentError do glMultTransposeMatrixdARB([1,2,3,4]) end
	end

	def test_gl_arb_multisample
		return if not supported?("GL_ARB_multisample")
		glSampleCoverageARB(0.5,GL_FALSE)
		assert_equal(glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB),0.5)
		assert_equal(glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB),GL_FALSE)
		glSampleCoverageARB(1.0,GL_TRUE)
		assert_equal(glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB),1.0)
		assert_equal(glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB),GL_TRUE)
	end

	def test_gl_arb_color_buffer_float
		return if not supported?("GL_ARB_color_buffer_float")
		glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB,GL_FIXED_ONLY_ARB)
		assert_equal(glGetIntegerv(GL_CLAMP_VERTEX_COLOR_ARB),GL_FIXED_ONLY_ARB)

		glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB,GL_TRUE)
		assert_equal(glGetIntegerv(GL_CLAMP_VERTEX_COLOR_ARB),GL_TRUE)
	end

	def test_gl_arb_vertex_program
		return if not supported?("GL_ARB_vertex_program")

		assert_equal(glIsProgram(0),GL_FALSE)
		programs = glGenProgramsARB(1)
		assert_equal(programs.size,1)
		
		program = "!!ARBvp1.0\nTEMP vv;\nEND"
	
	  glBindProgramARB(GL_VERTEX_PROGRAM_ARB, programs[0])
		glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, program)
		assert_equal(glGetProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_STRING_ARB), program)
		assert_equal(glIsProgramARB(programs[0]),GL_TRUE)	

		assert_equal(glGetProgramivARB(GL_VERTEX_PROGRAM_ARB,GL_PROGRAM_LENGTH_ARB),program.size)
		assert_equal(glGetProgramivARB(GL_VERTEX_PROGRAM_ARB,GL_PROGRAM_BINDING_ARB),programs[0])

		glEnableVertexAttribArrayARB(1)
		assert_equal(glGetVertexAttribivARB(1,GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB),[GL_TRUE])
		glDisableVertexAttribArrayARB(1)
		assert_equal(glGetVertexAttribivARB(1,GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB),[GL_FALSE])

		glVertexAttribPointerARB(1,2,GL_FLOAT,GL_FALSE,0,[1,1].pack("f*"))
		assert_equal(glGetVertexAttribPointervARB(1),[1,1].pack("f*"))


		glProgramEnvParameter4dARB(GL_VERTEX_PROGRAM_ARB,1, 1,2,3,4)
		assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB,1),[1,2,3,4])
		glProgramEnvParameter4fARB(GL_VERTEX_PROGRAM_ARB,1, 5,6,7,8)
		assert_equal(glGetProgramEnvParameterfvARB(GL_VERTEX_PROGRAM_ARB,1),[5,6,7,8])
		glProgramEnvParameter4dvARB(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
		assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB,1),[1,2,3,4])
		glProgramEnvParameter4fvARB(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
		assert_equal(glGetProgramEnvParameterfvARB(GL_VERTEX_PROGRAM_ARB,1),[5,6,7,8])

		glProgramLocalParameter4dARB(GL_VERTEX_PROGRAM_ARB,1, 1,2,3,4)
		assert_equal(glGetProgramLocalParameterdvARB(GL_VERTEX_PROGRAM_ARB,1),[1,2,3,4])
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,1, 5,6,7,8)
		assert_equal(glGetProgramLocalParameterfvARB(GL_VERTEX_PROGRAM_ARB,1),[5,6,7,8])
		glProgramLocalParameter4dvARB(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
		assert_equal(glGetProgramLocalParameterdvARB(GL_VERTEX_PROGRAM_ARB,1),[1,2,3,4])
		glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
		assert_equal(glGetProgramLocalParameterfvARB(GL_VERTEX_PROGRAM_ARB,1),[5,6,7,8])

		glVertexAttrib1dARB(1,1)
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],1)
		glVertexAttrib1fARB(1,2)
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],2)
		glVertexAttrib1sARB(1,3)
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],3)
		glVertexAttrib1dvARB(1,[1])
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],1)
		glVertexAttrib1fvARB(1,[2])
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],2)
		glVertexAttrib1svARB(1,[3])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0],3)

		glVertexAttrib2dARB(1,1,2)
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[1,2])
		glVertexAttrib2fARB(1,2,3)
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[2,3])
		glVertexAttrib2sARB(1,3,4)
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[3,4])
		glVertexAttrib2dvARB(1,[1,2])
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[1,2])
		glVertexAttrib2fvARB(1,[2,3])
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[2,3])
		glVertexAttrib2svARB(1,[3,4])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,2],[3,4])

		glVertexAttrib3dARB(1,1,2,3)
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[1,2,3])
		glVertexAttrib3fARB(1,2,3,4)
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[2,3,4])
		glVertexAttrib3sARB(1,3,4,5)
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[3,4,5])
		glVertexAttrib3dvARB(1,[1,2,3])
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[1,2,3])
		glVertexAttrib3fvARB(1,[2,3,4])
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[2,3,4])
		glVertexAttrib3svARB(1,[3,4,5])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,3],[3,4,5])

		glVertexAttrib4dARB(1,1,2,3,4)
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,2,3,4])
		glVertexAttrib4fARB(1,2,3,4,5)
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[2,3,4,5])
		glVertexAttrib4sARB(1,3,4,5,6)
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[3,4,5,6])
		glVertexAttrib4dvARB(1,[1,2,3,4])
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,2,3,4])
		glVertexAttrib4fvARB(1,[2,3,4,5])
		assert_equal(glGetVertexAttribfvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[2,3,4,5])
		glVertexAttrib4svARB(1,[3,4,5,6])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[3,4,5,6])


		glVertexAttrib4bvARB(1,[1,2,3,4])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,2,3,4])
		glVertexAttrib4ivARB(1,[2,3,4,5])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[2,3,4,5])
		glVertexAttrib4ubvARB(1,[3,4,5,6])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[3,4,5,6])
		glVertexAttrib4uivARB(1,[1,2,3,4])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,2,3,4])
		glVertexAttrib4usvARB(1,[2,3,4,5])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[2,3,4,5])

		glVertexAttrib4NbvARB(1,[0,2**7-1,0,2**7-1])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[0,1,0,1])
		glVertexAttrib4NivARB(1,[2**31-1,0,2**31-1,0])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,0,1,0])
		glVertexAttrib4NsvARB(1,[0,2**15-1,0,2**15-1])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[0,1,0,1])

		glVertexAttrib4NubARB(1,2**8-1,0,2**8-1,0)
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,0,1,0])

		glVertexAttrib4NubvARB(1,[0,2**8-1,0,2**8-1])
		assert_equal(glGetVertexAttribdvARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[0,1,0,1])
		glVertexAttrib4NuivARB(1,[2**32-1,0,2**32-1,0])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[1,0,1,0])
		glVertexAttrib4NusvARB(1,[0,2**16-1,0,2**16-1])
		assert_equal(glGetVertexAttribivARB(1,GL_CURRENT_VERTEX_ATTRIB_ARB)[0,4],[0,1,0,1])

		glDeleteProgramsARB(programs)
	end

	def test_gl_arb_windowpos
		return if not supported?("GL_ARB_window_pos")
		# 2
		glWindowPos2dARB(1.0,2.0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2dvARB([2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2fARB(1.0,2.0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2fvARB([2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2iARB(1,2)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2ivARB([2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2sARB(1,2)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2svARB([2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])

		# 3
		glWindowPos3dARB(1.0,2.0,0.5)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0.5,1])
		glWindowPos3dvARB([3.0,2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3fARB(1.0,2.0,0.5)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0.5,1])
		glWindowPos3fvARB([3.0,2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3iARB(1,2,0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos3ivARB([3,2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3sARB(1,2,0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos3svARB([3,2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
	end

	def test_gl_arb_pointparameter
		return if not supported?("GL_ARB_point_parameters")
		glPointParameterfARB(GL_POINT_SIZE_MIN,1.0)
		assert_equal(glGetDoublev(GL_POINT_SIZE_MIN),1.0)

		glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION,[1,0,1])
		assert_equal(glGetDoublev(GL_POINT_DISTANCE_ATTENUATION),[1,0,1])
	end

	def test_gl_arb_occlusion_query
		return if not supported?("GL_ARB_occlusion_query")

		queries = glGenQueriesARB(2)
		assert_equal(queries.size,2)

		glBeginQueryARB(GL_SAMPLES_PASSED,queries[1])
		assert_equal(glIsQueryARB(queries[1]),GL_TRUE)

		glEndQueryARB(GL_SAMPLES_PASSED)
		r = glGetQueryObjectivARB(queries[1],GL_QUERY_RESULT_AVAILABLE)
		assert(r==GL_TRUE || r==GL_FALSE)
		assert(glGetQueryObjectuivARB(queries[1],GL_QUERY_RESULT)>=0)

		glDeleteQueriesARB(queries)
		assert_equal(glIsQueryARB(queries[1]),GL_FALSE)
	end

	def test_gl_arb_shader_objects
		return if not supported?("GL_ARB_shader_objects")

		vertex_shader_source = "void main() { gl_Position = ftransform();}"
		
		program = glCreateProgramObjectARB()

		vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)

		glShaderSourceARB(vs,vertex_shader_source)
		assert_equal(glGetShaderSourceARB(vs),vertex_shader_source)

		assert_equal(glGetObjectParameterivARB(vs,GL_OBJECT_TYPE_ARB),GL_SHADER_OBJECT_ARB)
		assert_equal(glGetObjectParameterfvARB(vs,GL_OBJECT_TYPE_ARB),GL_SHADER_OBJECT_ARB)
		assert_equal(glGetObjectParameterfvARB(vs,GL_OBJECT_SUBTYPE_ARB),GL_VERTEX_SHADER)
		glCompileShaderARB(vs)
		assert_equal(glGetObjectParameterivARB(vs,GL_OBJECT_COMPILE_STATUS_ARB),GL_TRUE)
		
		vslog = glGetInfoLogARB(vs)
		assert_equal(vslog.class,String)
		
		glAttachObjectARB(program,vs)
		assert_equal(glGetAttachedObjectsARB(program),[vs])

		glValidateProgramARB(program)
		assert_equal(glGetObjectParameterivARB(program,GL_OBJECT_VALIDATE_STATUS_ARB),GL_TRUE)

		glLinkProgramARB(program)
		assert_equal(glGetObjectParameterivARB(program,GL_OBJECT_LINK_STATUS_ARB),GL_TRUE)

		glUseProgramObjectARB(program)
		assert_equal(glGetIntegerv(GL_CURRENT_PROGRAM),program)

		assert_equal(glGetHandleARB(GL_PROGRAM_OBJECT_ARB),program)

		glUseProgramObjectARB(0)

		glDetachObjectARB(program,vs)

		glDeleteObjectARB(vs)
		glDeleteObjectARB(program)
	end

	def test_gl_arb_shader_objects_2
		return if not supported?("GL_ARB_shader_objects")

		vertex_shader_source = "attribute vec4 test; uniform float testvec1; uniform vec2 testvec2; uniform vec3 testvec3; uniform vec4 testvec4; uniform int testivec1; uniform ivec2 testivec2; uniform ivec3 testivec3; uniform ivec4 testivec4; void main() { gl_Position = testvec1 * test * testvec2.x * testvec3.x * testivec1 * testivec2.x * testivec3.x * testivec4.x + testvec4;}"

		program = glCreateProgramObjectARB()
		vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
		glShaderSourceARB(vs,vertex_shader_source)

		glCompileShaderARB(vs)
		assert_equal(glGetObjectParameterivARB(vs,GL_OBJECT_COMPILE_STATUS_ARB),GL_TRUE)

		glAttachObjectARB(program,vs)

		glLinkProgramARB(program)
		assert_equal(glGetObjectParameterivARB(program,GL_OBJECT_LINK_STATUS_ARB),GL_TRUE)

		glUseProgramObjectARB(program)

		assert((tv1l = glGetUniformLocationARB(program,"testvec1"))>=0)
		assert((tv2l = glGetUniformLocationARB(program,"testvec2"))>=0)
		assert((tv3l = glGetUniformLocationARB(program,"testvec3"))>=0)
		assert((tv4l = glGetUniformLocationARB(program,"testvec4"))>=0)
		assert((tv1il = glGetUniformLocationARB(program,"testivec1"))>=0)
		assert((tv2il = glGetUniformLocationARB(program,"testivec2"))>=0)
		assert((tv3il = glGetUniformLocationARB(program,"testivec3"))>=0)
		assert((tv4il = glGetUniformLocationARB(program,"testivec4"))>=0)

		##

		assert_equal(glGetActiveUniformARB(program,tv1il),[1,GL_INT,"testivec1"])

		## f
		glUniform1fARB(tv1l,2.0)
		assert_equal(glGetUniformfvARB(program,tv1l),[2.0])
		glUniform2fARB(tv2l,2.0,2.0)
		assert_equal(glGetUniformfvARB(program,tv2l),[2.0,2.0])
		glUniform3fARB(tv3l,2.0,2.0,2.0)
		assert_equal(glGetUniformfvARB(program,tv3l),[2.0,2.0,2.0])
		glUniform4fARB(tv4l,2.0,2.0,2.0,2.0)
		assert_equal(glGetUniformfvARB(program,tv4l),[2.0,2.0,2.0,2.0])
		# i 
		glUniform1iARB(tv1il,3)
		assert_equal(glGetUniformivARB(program,tv1il),[3])
		glUniform2iARB(tv2il,3,3)
		assert_equal(glGetUniformivARB(program,tv2il),[3,3])
		glUniform3iARB(tv3il,3,3,3)
		assert_equal(glGetUniformivARB(program,tv3il),[3,3,3])
		glUniform4iARB(tv4il,3,3,3,3)
		assert_equal(glGetUniformivARB(program,tv4il),[3,3,3,3])
		# fv
		glUniform1fvARB(tv1l,1,[3.0])
		assert_equal(glGetUniformfvARB(program,tv1l),[3.0])
		glUniform2fvARB(tv2l,1,[3.0,3.0])
		assert_equal(glGetUniformfvARB(program,tv2l),[3.0,3.0])
		glUniform3fvARB(tv3l,1,[3.0,3.0,3.0])
		assert_equal(glGetUniformfvARB(program,tv3l),[3.0,3.0,3.0])
		glUniform4fvARB(tv4l,1,[3.0,3.0,3.0,3.0])
		assert_equal(glGetUniformfvARB(program,tv4l),[3.0,3.0,3.0,3.0])
		# iv
		glUniform1ivARB(tv1il,1,[2])
		assert_equal(glGetUniformivARB(program,tv1il),[2])
		glUniform2ivARB(tv2il,1,[2,2])
		assert_equal(glGetUniformivARB(program,tv2il),[2,2])
		glUniform3ivARB(tv3il,1,[2,2,2])
		assert_equal(glGetUniformivARB(program,tv3il),[2,2,2])
		glUniform4ivARB(tv4il,1,[2,2,2,2])
		assert_equal(glGetUniformivARB(program,tv4il),[2,2,2,2])

		glDeleteObjectARB(vs)
		glDeleteObjectARB(program)
	end

	def test_gl_arb_shader_objects_3
		return if not supported?("GL_ARB_shader_objects")

		vertex_shader_source = "uniform mat2 testmat2; uniform mat3 testmat3; uniform mat4 testmat4; void main() { gl_Position = gl_Vertex * testmat4[0].x * testmat3[0].x * testmat2[0].x;}"

		program = glCreateProgramObjectARB()
		vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
		glShaderSourceARB(vs,vertex_shader_source)

		glCompileShaderARB(vs)
		assert_equal(glGetObjectParameterivARB(vs,GL_OBJECT_COMPILE_STATUS_ARB),GL_TRUE)

		glAttachObjectARB(program,vs)

		glLinkProgramARB(program)
		assert_equal(glGetObjectParameterivARB(program,GL_OBJECT_LINK_STATUS_ARB),GL_TRUE)

		glUseProgramObjectARB(program)
		#
		assert((tm2l = glGetUniformLocationARB(program,"testmat2"))>=0)
		assert((tm3l = glGetUniformLocationARB(program,"testmat3"))>=0)
		assert((tm4l = glGetUniformLocationARB(program,"testmat4"))>=0)

		glUniformMatrix2fvARB(tm2l, 1, GL_TRUE, [0,1, 1,0])
		assert_equal(glGetUniformfvARB(program,tm2l),[0,1,1,0])
		
		glUniformMatrix3fvARB(tm3l, 1, GL_TRUE, [0,1,0, 1,0,1, 0,1,0])
		assert_equal(glGetUniformfvARB(program,tm3l),[0,1,0, 1,0,1, 0,1,0])
		
		glUniformMatrix4fvARB(tm4l, 1, GL_TRUE, [0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0])
		assert_equal(glGetUniformfvARB(program,tm4l),[0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0])

		glDeleteObjectARB(vs)
		glDeleteObjectARB(program)
	end

	def test_gl_arb_vertex_shader
		return if not supported?("GL_ARB_vertex_shader")

		vertex_shader_source = "attribute vec4 test; uniform float testvec1; uniform vec2 testvec2; uniform vec3 testvec3; uniform vec4 testvec4; uniform int testivec1; uniform ivec2 testivec2; uniform ivec3 testivec3; uniform ivec4 testivec4; void main() { gl_Position = testvec1 * test * testvec2.x * testvec3.x * testivec1 * testivec2.x * testivec3.x * testivec4.x + testvec4;}"

		program = glCreateProgramObjectARB()
		vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
		glShaderSourceARB(vs,vertex_shader_source)

		glCompileShaderARB(vs)
		assert_equal(glGetObjectParameterivARB(vs,GL_OBJECT_COMPILE_STATUS_ARB),GL_TRUE)

		glAttachObjectARB(program,vs)

		glBindAttribLocationARB(program,2,"test")

		glLinkProgramARB(program)
		assert_equal(glGetObjectParameterivARB(program,GL_OBJECT_LINK_STATUS_ARB),GL_TRUE)

		glUseProgramObjectARB(program)

		assert_equal(glGetAttribLocationARB(program,"test"),2)
		assert_equal(glGetActiveAttribARB(program,0),[1,GL_FLOAT_VEC4,"test"])

		glDeleteObjectARB(vs)
		glDeleteObjectARB(program)
	end
end
