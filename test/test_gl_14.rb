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

class TestGl14 < OpenGL::TestCase

  def setup
    super

    supported? 1.4
  end

  def test_arrays_2
    sc = [0, 1, 0, 1, 0, 1].pack("f*")
    fc = [1, 0].pack("f*")

    glSecondaryColorPointer(3, GL_FLOAT, 0, sc)
    assert_equal 3,        glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_SIZE)
    assert_equal GL_FLOAT, glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_TYPE)
    assert_equal 12,       glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_STRIDE)
    assert_equal sc,       glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER)

    glFogCoordPointer(GL_FLOAT, 0, fc)
    assert_equal GL_FLOAT, glGetIntegerv(GL_FOG_COORD_ARRAY_TYPE)
    assert_equal 4,        glGetIntegerv(GL_FOG_COORD_ARRAY_STRIDE)
    assert_equal fc,       glGetPointerv(GL_FOG_COORD_ARRAY_POINTER)

    glEnableClientState(GL_SECONDARY_COLOR_ARRAY)
    glEnableClientState(GL_FOG_COORD_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd()

    assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR), [0, 1, 0, 1])
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 1)

    glBegin(GL_TRIANGLES)
    glArrayElement(1)
    glEnd()

    assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR), [1, 0, 1, 1])
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 0)

    glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
    glDisableClientState(GL_FOG_COORD_ARRAY)
  end

  def test_arrays_3
    va = [0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    glEnableClientState(GL_VERTEX_ARRAY)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glMultiDrawArrays(GL_POLYGON, [0, 3], [3, 3])

    i1 = [0, 1, 2].pack("C*")
    i2 = [3, 4, 5].pack("C*")
    glMultiDrawElements(GL_TRIANGLES, GL_UNSIGNED_BYTE, [i1, i2])

    count = glRenderMode(GL_RENDER)
    assert_equal(count, (3*3+2)*4)
    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_glblendfuncseparate
    glBlendFuncSeparate(GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR, GL_SRC_COLOR)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB), GL_SRC_COLOR)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA), GL_SRC_COLOR)
    assert_equal(glGetIntegerv(GL_BLEND_DST_RGB), GL_SRC_COLOR)
    assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA), GL_SRC_COLOR)
  end

  def test_glpointparameter
    glPointParameterf(GL_POINT_SIZE_MIN, 2.0)
    assert_equal(glGetDoublev(GL_POINT_SIZE_MIN), 2.0)

    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, [0, 1, 0])
    assert_equal([0, 1, 0], glGetDoublev(GL_POINT_DISTANCE_ATTENUATION))

    glPointParameteri(GL_POINT_SIZE_MAX, 4)
    assert_equal(glGetDoublev(GL_POINT_SIZE_MAX), 4)

    glPointParameteriv(GL_POINT_DISTANCE_ATTENUATION, [1, 0, 1])
    assert_equal([1, 0, 1], glGetDoublev(GL_POINT_DISTANCE_ATTENUATION))
  end

  def test_glfogcoord
    glFogCoordf(2.0)
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 2.0)
    glFogCoordfv([3.0])
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 3.0)

    glFogCoordd(2.0)
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 2.0)
    glFogCoorddv([3.0])
    assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD), 3.0)
  end

  def test_glsecondarycolor
    glSecondaryColor3b(2**7-1, 0, 2**7-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3bv([0, 2**7-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3d(1.0, 0.0, 1.0)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3dv([0.0, 1.0, 0.0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3f(1.0, 0.0, 1.0)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3fv([0.0, 1.0, 0.0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3i(2**31-1, 0, 2**31-1)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3iv([0, 2**31-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3s(2**15-1, 0, 2**15-1)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3sv([0, 2**15-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3ub(2**8-1, 0, 2**8-1)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3ubv([0, 2**8-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3ui(2**32-1, 0, 2**32-1)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3uiv([0, 2**32-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3us(2**16-1, 0, 2**16-1)
    assert_each_in_delta([1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glSecondaryColor3usv([0, 2**16-1, 0])
    assert_each_in_delta([0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))
  end

  def test_glwindowpos_2
    glLoadIdentity

    glWindowPos2d 1.0, 2.0
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2dv [2.0, 1.0]
    assert_each_in_delta [2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2f 1.0, 2.0
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2fv [2.0, 1.0]
    assert_each_in_delta [2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2i 1, 2
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2iv [2, 1]
    assert_each_in_delta [2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2s 1, 2
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos2sv [2, 1]
    assert_each_in_delta [2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)
  end

  def test_glwindowspos_3
    glWindowPos3d 1.0, 2.0, 0.5
    assert_each_in_delta [1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3dv [3.0, 2.0, 1.0]
    assert_each_in_delta [3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3f 1.0, 2.0, 0.5
    assert_each_in_delta [1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3fv [3.0, 2.0, 1.0]
    assert_each_in_delta [3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3i 1, 2, 0
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3iv [3, 2, 1]
    assert_each_in_delta [3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3s 1, 2, 0
    assert_each_in_delta [1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)

    glWindowPos3sv [3, 2, 1]
    assert_each_in_delta [3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)
  end

end

