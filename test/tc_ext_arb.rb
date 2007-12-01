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

end
