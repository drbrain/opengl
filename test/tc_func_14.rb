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

class Test_14 < Test::Unit::TestCase
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

	def test_arrays_2
		return if not supported?(["glSecondaryColorPointer","glFogCoordPointer"])
		sc = [0,1,0, 1,0,1].pack("f*")
		fc = [1, 0].pack("f*")

		glSecondaryColorPointer(3,GL_FLOAT,0,sc)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_SIZE),3)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_TYPE),GL_FLOAT)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_STRIDE),0)
		assert_equal(glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER),sc)
		glFogCoordPointer(GL_FLOAT,0,fc)
		assert_equal(glGetIntegerv(GL_FOG_COORD_ARRAY_TYPE),GL_FLOAT)
		assert_equal(glGetIntegerv(GL_FOG_COORD_ARRAY_STRIDE),0)
		assert_equal(glGetPointerv(GL_FOG_COORD_ARRAY_POINTER),fc)

		glEnableClientState(GL_SECONDARY_COLOR_ARRAY)
		glEnableClientState(GL_FOG_COORD_ARRAY)

		glBegin(GL_TRIANGLES)
		glArrayElement(0)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0,1,0,1])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),1)

		glBegin(GL_TRIANGLES)
		glArrayElement(1)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1,0,1,1])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),0)

		glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
		glDisableClientState(GL_FOG_COORD_ARRAY)
	end

	def test_arrays_3
		return if not supported?(["glMultiDrawArrays","glMultiDrawElements"])
		va = [0,0, 1,0, 1,1, 0,0, 1,0, 0,1].pack("f*")
		glVertexPointer(2,GL_FLOAT,0,va)
		
		glEnable(GL_VERTEX_ARRAY)

		buf = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		glMultiDrawArrays(GL_POLYGON, [0,3], [3,3], 2)		

		i1 = [0,1,2].pack("C*")
		i2 = [3,4,5].pack("C*")
		glMultiDrawElements(GL_TRIANGLES,GL_UNSIGNED_BYTE,[i1,i2])

		count = glRenderMode(GL_RENDER)
		assert_equal(count,(3*3+2)*4)
		glDisable(GL_VERTEX_ARRAY)
	end

	def test_glblendfuncseparate
		return if not supported?(["glBlendFuncSeparate"])
		glBlendFuncSeparate(GL_SRC_COLOR,GL_SRC_COLOR,GL_SRC_COLOR,GL_SRC_COLOR)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB),GL_SRC_COLOR)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA),GL_SRC_COLOR)
		assert_equal(glGetIntegerv(GL_BLEND_DST_RGB),GL_SRC_COLOR)
		assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA),GL_SRC_COLOR)
	end

	def test_glpointparameter
		return if not supported?(["glPointParameterf","glPointParameterfv","glPointParameteri","glPointParameteriv"])
		glPointParameterf(GL_POINT_SIZE_MIN,2.0)
		assert_equal(glGetDoublev(GL_POINT_SIZE_MIN),2.0)

		glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION,[0,1,0])
		assert_equal(glGetDoublev(GL_POINT_DISTANCE_ATTENUATION),[0,1,0])

		glPointParameteri(GL_POINT_SIZE_MAX,4)
		assert_equal(glGetDoublev(GL_POINT_SIZE_MAX),4)

		glPointParameteriv(GL_POINT_DISTANCE_ATTENUATION,[1,0,1])
		assert_equal(glGetDoublev(GL_POINT_DISTANCE_ATTENUATION),[1,0,1])
	end

	def test_glfogcoord
		return if not supported?(["glFogCoordf","glFogCoordd","glFogCoordfv","glFogCoorddv",])

		glFogCoordf(2.0)
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),2.0)
		glFogCoordfv([3.0])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),3.0)

		glFogCoordd(2.0)
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),2.0)
		glFogCoorddv([3.0])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),3.0)
	end

	def test_glsecondarycolor
		return if not supported?(["glSecondaryColor3b"])

		glSecondaryColor3b(2**7-1,0,2**7-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3bv([0,2**7-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3d(1.0,0.0,1.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3dv(0.0,1.0,0.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3f(1.0,0.0,1.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3fv(0.0,1.0,0.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3i(2**31-1,0,2**31-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3iv([0,2**31-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3s(2**15-1,0,2**15-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3sv([0,2**15-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3ub(2**8-1,0,2**8-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3ubv([0,2**8-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3ui(2**32-1,0,2**32-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3uiv([0,2**32-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3us(2**16-1,0,2**16-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3usv([0,2**16-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
	end

	def test_glwindowpos
		return if not supported?(["glWindowPos2d"])
		# 2
		glWindowPos2d(1.0,2.0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2dv([2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2f(1.0,2.0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2fv([2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2i(1,2)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2iv([2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])
		glWindowPos2s(1,2)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos2sv([2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[2,1,0,1])

		# 3
		glWindowPos3d(1.0,2.0,0.5)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0.5,1])
		glWindowPos3dv([3.0,2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3f(1.0,2.0,0.5)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0.5,1])
		glWindowPos3fv([3.0,2.0,1.0])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3i(1,2,0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos3iv([3,2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
		glWindowPos3s(1,2,0)
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[1,2,0,1])
		glWindowPos3sv([3,2,1])
		assert_equal(glGetDoublev(GL_CURRENT_RASTER_POSITION),[3,2,1,1])
	end
end
