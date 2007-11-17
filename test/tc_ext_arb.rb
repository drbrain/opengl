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
end
