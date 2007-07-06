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

if __FILE__ == $0
    # If we are being called from the command line, e.g., ruby foo.rb, then
    # fixup the load path so we can find the OpenGL extension libs
    $: << File.join(File.dirname(__FILE__), '..', 'ext')
end

require 'test/unit'
require 'gl'
require 'glut'
include Gl
include Glut

class Test_20 < Test::Unit::TestCase
	def setup
		if $glut_initialized == nil
			glut_init()
			$glut_initialized = true
		end

		glPushAttrib(GL_ALL_ATTRIB_BITS)
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS)
		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()
		glMatrixMode(GL_PROJECTION)
		glLoadIdentity()

		glClearColor(0,0,0,0)
		glClear(GL_COLOR_BUFFER_BIT)
	end

	def teardown
		glPopAttrib()
		glPopClientAttrib()
		assert_equal(glGetError(),0) # all expected GL errors must be handled by the method itself
	end

	def test_glblendequationseparate
		return if not supported?("glBlendEquationSeparate")
		glBlendEquationSeparate(GL_MIN,GL_MAX)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB),GL_MIN)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA),GL_MAX)
		glBlendEquationSeparate(GL_MAX,GL_MIN)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB),GL_MAX)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA),GL_MIN)
	end

	def test_stencilops
		return if not supported?(["glStencilOpSeparate","glStencilFuncSeparate","glStencilMaskSeparate"])

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
		return if not supported?("glDrawBuffers")
		glDrawBuffers([GL_NONE])
		assert_equal(glGetIntegerv(GL_DRAW_BUFFER0),GL_NONE)
	end

	def test_glvertexattrib
		return if not supported?(["glVertexAttrib1f","glGetVertexAttribdv"])
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
		return if not supported?(["glVertexAttribPointer","glGetVertexAttribPointerv","glEnableVertexAttribArray","glDisableVertexAttribArray"])
		
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

end
