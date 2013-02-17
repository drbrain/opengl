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

class TestGl10_11 < OpenGL::TestCase
  def test_glhint
    glHint(GL_FOG_HINT,GL_NICEST)
    assert_equal(glGetIntegerv(GL_FOG_HINT), GL_NICEST)
    glHint(GL_FOG_HINT,GL_FASTEST)
    assert_equal(glGetIntegerv(GL_FOG_HINT), GL_FASTEST)
  end

  def test_glindex
    glIndexd(2.0)
    assert_in_delta(2.0, glGetDoublev(GL_CURRENT_INDEX), 0.001)
    glIndexdv([3.0])
    assert_in_delta(3.0, glGetDoublev(GL_CURRENT_INDEX), 0.001)

    glIndexf(4.0)
    assert_in_delta(4.0, glGetFloatv(GL_CURRENT_INDEX), 0.001)
    glIndexfv([5.0])
    assert_in_delta(5.0, glGetFloatv(GL_CURRENT_INDEX), 0.001)

    glIndexi(6)
    assert_in_delta(6, glGetIntegerv(GL_CURRENT_INDEX), 0.001)
    glIndexiv([7])
    assert_in_delta(7, glGetIntegerv(GL_CURRENT_INDEX), 0.001)

    glIndexs(8)
    assert_in_delta(8, glGetIntegerv(GL_CURRENT_INDEX), 0.001)
    glIndexsv([9])
    assert_in_delta(9, glGetIntegerv(GL_CURRENT_INDEX), 0.001)

    glIndexub(10)
    assert_in_delta(10, glGetIntegerv(GL_CURRENT_INDEX), 0.001)
    glIndexubv([11])
    assert_in_delta(11, glGetIntegerv(GL_CURRENT_INDEX), 0.001)

    # index pointer
    glIndexPointer(GL_INT, 2, "")
    assert_equal(2, glGetIntegerv(GL_INDEX_ARRAY_STRIDE))
    assert_equal(GL_INT, glGetIntegerv(GL_INDEX_ARRAY_TYPE))
  end

  def test_glclear
    glClearColor(1,0,1,0)
    assert_equal([1,0,1,0], glGetDoublev(GL_COLOR_CLEAR_VALUE))

    glClearIndex(2)
    assert_equal(2, glGetDoublev(GL_INDEX_CLEAR_VALUE))

    glClearAccum(0.5,0.5,0.5,0.5)
    assert_equal([0.5,0.5,0.5,0.5], glGetDoublev(GL_ACCUM_CLEAR_VALUE))

    glClearStencil(1)
    assert_equal(1, glGetIntegerv(GL_STENCIL_CLEAR_VALUE))

    glClearDepth(0.5)
    assert_equal(0.5, glGetDoublev(GL_DEPTH_CLEAR_VALUE))
  end

  def test_glclientattrib
    glPixelStorei(GL_PACK_ALIGNMENT,2)
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT)
    glPixelStorei(GL_PACK_ALIGNMENT,4)
    assert_equal(4, glGetIntegerv(GL_PACK_ALIGNMENT))
    glPopClientAttrib()
    assert_equal(2, glGetIntegerv(GL_PACK_ALIGNMENT))
  end

  def test_matrix
    m_a = [[2.0,0.0,0.0,0.0],
      [0.0,2.0,0.0,0.0],
      [0.0,0.0,2.0,0.0],
      [0.0,0.0,0.0,2.0]]

    m_b = [[3.0,0.0,0.0,0.0],
      [0.0,3.0,0.0,0.0],
      [0.0,0.0,3.0,0.0],
      [0.0,0.0,0.0,3.0]]

    m_ident = [[1.0,0.0,0.0,0.0],
      [0.0,1.0,0.0,0.0],
      [0.0,0.0,1.0,0.0],
      [0.0,0.0,0.0,1.0]]

    # 1
    glMatrixMode(GL_MODELVIEW)
    glLoadMatrixf(m_a)
    assert_equal(m_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadMatrixd(m_b)
    assert_equal(m_b, glGetDoublev(GL_MODELVIEW_MATRIX))

    glLoadIdentity()
    assert_equal( m_ident, glGetDoublev(GL_MODELVIEW_MATRIX))

    glMultMatrixf(m_a)
    assert_equal(m_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glMultMatrixd(m_b)
    assert_equal(m_b, glGetDoublev(GL_MODELVIEW_MATRIX))

    # 2
    glMatrixMode(GL_MODELVIEW)
    glLoadMatrixf(m_a)
    glMatrixMode(GL_PROJECTION)
    glLoadMatrixf(m_b)

    assert_equal(m_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    assert_equal(m_b, glGetDoublev(GL_PROJECTION_MATRIX))

    glMatrixMode(GL_MODELVIEW)
    glLoadMatrixf(m_a)
    glPushMatrix()
    glLoadMatrixf(m_b)
    assert_equal(m_b, glGetDoublev(GL_MODELVIEW_MATRIX))
    glPopMatrix()
    assert_equal(m_a, glGetDoublev(GL_MODELVIEW_MATRIX))

    # 3
    m = Matrix.rows([[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]])
    glMatrixMode(GL_MODELVIEW)
    glLoadMatrixf(m)
    assert_equal(m.to_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glLoadMatrixd(m)
    assert_equal(m.to_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glMultMatrixf(m)
    assert_equal(m.to_a, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glMultMatrixd(m)
    assert_equal(m.to_a, glGetDoublev(GL_MODELVIEW_MATRIX))

    assert_raises ArgumentError do glLoadMatrixf([1,2,3,4]) end
    assert_raises ArgumentError do glLoadMatrixd([1,2,3,4]) end
    assert_raises ArgumentError do glMultMatrixf([1,2,3,4]) end
    assert_raises ArgumentError do glMultMatrixd([1,2,3,4]) end
  end

  def test_gledge
    glEdgeFlag(GL_FALSE)
    assert_equal(false, glGetBooleanv(GL_EDGE_FLAG))

    glEdgeFlag(GL_TRUE)
    assert(glGetBooleanv(GL_EDGE_FLAG))

    glEdgeFlagv([GL_FALSE])
    assert_equal(false, glGetBooleanv(GL_EDGE_FLAG))
  end

  def test_clientstate
    glEnableClientState(GL_COLOR_ARRAY)
    assert_equal(true, glIsEnabled(GL_COLOR_ARRAY))
    glDisableClientState(GL_COLOR_ARRAY)
    assert_equal(false, glIsEnabled(GL_COLOR_ARRAY))
  end

  def test_glshademodel
    glShadeModel(GL_FLAT)
    assert_equal(GL_FLAT, glGetIntegerv(GL_SHADE_MODEL))
    glShadeModel(GL_SMOOTH)
    assert_equal(GL_SMOOTH, glGetIntegerv(GL_SHADE_MODEL))
  end

  def test_glclipplane
    glClipPlane(GL_CLIP_PLANE0,[1,2,3,4])
    assert_equal([1,2,3,4], glGetClipPlane(GL_CLIP_PLANE0))
  end

  def test_polygonoffset
    glPolygonOffset(2.0,3.0)
    assert_equal(2.0, glGetDoublev(GL_POLYGON_OFFSET_FACTOR))
    assert_equal(3.0, glGetDoublev(GL_POLYGON_OFFSET_UNITS))
  end

  def test_glviewport
    glViewport(1,2,3,4)
    assert_equal([1,2,3,4], glGetIntegerv(GL_VIEWPORT))
  end

  def test_mask
    glStencilMask(2)
    assert_equal( 2, glGetIntegerv(GL_STENCIL_WRITEMASK))
    glStencilMask(1)
    assert_equal( 1, glGetIntegerv(GL_STENCIL_BACK_WRITEMASK))

    glColorMask(GL_TRUE,GL_FALSE,GL_TRUE,GL_FALSE)
    assert_equal([true,false,true,false], glGetBooleanv(GL_COLOR_WRITEMASK))

    glDepthMask(GL_TRUE)
    assert(glGetBooleanv(GL_DEPTH_WRITEMASK))
    glDepthMask(GL_FALSE)
    assert_equal(false, glGetBooleanv(GL_DEPTH_WRITEMASK))

    glIndexMask(2)
    assert_equal(2, glGetIntegerv(GL_INDEX_WRITEMASK))
    glIndexMask(1)
    assert_equal(1, glGetIntegerv(GL_INDEX_WRITEMASK))
  end

  def test_glflush
    begin
      glBegin(GL_POINTS)
      glFlush()
      glEnd
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_OPERATION)
    end
  end

  def test_glfinish
    begin
      glBegin(GL_POINTS)
      glFinish()
      glEnd
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_OPERATION)
    end
  end

  def test_glgetstring
    assert(glGetString(GL_VERSION).size > 0)
  end

  def test_glscissor
    glScissor(1,2,3,4)
    assert_equal([1,2,3,4], glGetIntegerv(GL_SCISSOR_BOX))
  end

  def test_glstencilfunc
    glStencilFunc(GL_LEQUAL,2,3)
    assert_equal(GL_LEQUAL, glGetIntegerv(GL_STENCIL_FUNC))
    assert_equal(2, glGetIntegerv(GL_STENCIL_REF))
    assert_equal(3, glGetIntegerv(GL_STENCIL_VALUE_MASK))
  end

  def test_glstencilop
    glStencilOp(GL_ZERO,GL_REPLACE,GL_INCR)
    assert_equal(GL_ZERO, glGetIntegerv(GL_STENCIL_FAIL))
    assert_equal(GL_REPLACE, glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL))
    assert_equal(GL_INCR, glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS))
  end

  def test_gllogicop
    glLogicOp(GL_NAND)
    assert_equal(GL_NAND, glGetIntegerv(GL_LOGIC_OP_MODE))
  end

  def test_glfrustum
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    glFrustum(1,2,3,4,5,6)
    assert_equal([[10.0, 0.0, 0.0, 0.0], [0.0, 10.0, 0.0, 0.0], [3.0, 7.0, -11.0, -1.0], [0.0, 0.0, -60.0, 0.0]], glGetDoublev(GL_PROJECTION_MATRIX))
  end

  def test_gldepthrange
    glDepthRange(0.5,0.5)
    assert_equal([0.5,0.5], glGetDoublev(GL_DEPTH_RANGE))
  end

  def test_func
    glAlphaFunc(GL_GREATER, 0.5)
    assert_equal(GL_GREATER, glGetIntegerv(GL_ALPHA_TEST_FUNC))
    assert_equal(0.5, glGetDoublev(GL_ALPHA_TEST_REF))

    glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_DST_COLOR)
    assert_equal(GL_CONSTANT_ALPHA, glGetIntegerv(GL_BLEND_SRC))
    assert_equal(GL_ONE_MINUS_DST_COLOR, glGetIntegerv(GL_BLEND_DST))

    glDepthFunc(GL_LEQUAL)
    assert_equal(GL_LEQUAL, glGetIntegerv(GL_DEPTH_FUNC))
  end

  def test_glpixelzoom
    glPixelZoom(0.5,0.5)
    assert_equal(0.5, glGetDoublev(GL_ZOOM_X))
    assert_equal(0.5, glGetDoublev(GL_ZOOM_Y))
  end

  def test_glpixelstore
    glPixelStoref(GL_PACK_IMAGE_HEIGHT,5)
    assert_equal(5, glGetIntegerv(GL_PACK_IMAGE_HEIGHT))
    glPixelStorei(GL_PACK_IMAGE_HEIGHT,6)
    assert_equal(6, glGetIntegerv(GL_PACK_IMAGE_HEIGHT))
  end

  def test_glpixeltransfer
    glPixelTransferf(GL_RED_SCALE,2)
    assert_equal(2, glGetIntegerv(GL_RED_SCALE))
    glPixelTransferi(GL_RED_SCALE,3)
    assert_equal(3, glGetIntegerv(GL_RED_SCALE))
  end

  def test_pixelmap
    glPixelMapfv(GL_PIXEL_MAP_I_TO_I,[1,2,3,4])
    assert_equal([1,2,3,4], glGetPixelMapfv(GL_PIXEL_MAP_I_TO_I))

    glPixelMapuiv(GL_PIXEL_MAP_I_TO_I,[5,6,7,8])
    assert_equal([5,6,7,8], glGetPixelMapuiv(GL_PIXEL_MAP_I_TO_I))

    glPixelMapusv(GL_PIXEL_MAP_I_TO_I,[9,10,11,12])
    assert_equal([9,10,11,12], glGetPixelMapusv(GL_PIXEL_MAP_I_TO_I))
  end

  def test_buffers
    glDrawBuffer(GL_FRONT)
    assert_equal(GL_FRONT, glGetIntegerv(GL_DRAW_BUFFER))
    glDrawBuffer(GL_BACK)
    assert_equal(GL_BACK, glGetIntegerv(GL_DRAW_BUFFER))

    glReadBuffer(GL_FRONT)
    assert_equal(GL_FRONT, glGetIntegerv(GL_READ_BUFFER))
    glReadBuffer(GL_BACK)
    assert_equal(GL_BACK, glGetIntegerv(GL_READ_BUFFER))
  end

  def test__selection_buffer
    buf = glSelectBuffer(32)

    glRenderMode(GL_SELECT)
    glInitNames()
    glPushName(6)
    glPushName(3)
    glLoadName(5)
    glPopName()

    glBegin(GL_QUADS)
    glVertex2i(-1,-1)
    glVertex2i( 1,-1)
    glVertex2i( 1, 1)
    glVertex2i(-1, 1)
    glEnd()

    count = glRenderMode(GL_RENDER)
    data = buf.unpack("i*")
    assert(count==1) # number of records
    assert(data[0]==1) # number of hits in this record
    #		assert(data[1]>0) # zbuffer near
    #		assert(data[2]>0) # zbuffer far
    assert(data[3]==6) # name of hit
  end

  def test__feedback_buffer
    buf = glFeedbackBuffer(32,GL_2D)

    glRenderMode(GL_FEEDBACK)

    glBegin(GL_TRIANGLES)
    glVertex2i(-1,-1)
    glVertex2i( 1,-1)
    glVertex2i( 1, 1)
    glEnd()

    glPassThrough(2.0)

    count = glRenderMode(GL_RENDER)
    data = buf.unpack("f*")
    assert_equal(10, count) # (1 + 1 + 3x2) + (1 + 1)
    assert_equal(GL_POLYGON_TOKEN, data[0])
    assert_equal(3, data[1]) # 3 vertices
    # skip rasterized vertex data
    assert_equal(GL_PASS_THROUGH_TOKEN, data[8])
    assert_equal(2.0, data[9])
  end

  def test_glrasterposv
    glOrtho 0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1

    glRasterPos3dv Vector[1, 1, 1]

    assert_each_in_delta [1, 1, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION)
  end

  def test_glrasterpos_2
    glOrtho 0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1

    glRasterPos2d(1.0,2.0)
    assert_equal([1.0,2.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos2dv([3.0,4.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos2f(1.0,2.0)
    assert_equal([1.0,2.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos2fv([3.0,4.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos2i(1,2)
    assert_equal([1.0,2.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos2iv([3,4])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos2s(1,2)
    assert_equal([1.0,2.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos2sv([3,4])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
  end

  def test_glrasterpos_3
    glOrtho 0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1

    glRasterPos3d(1.0,2.0,1.0)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos3dv([3.0,4.0,0.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos3f(1.0,2.0,1.0)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos3fv([3.0,4.0,0.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos3i(1,2,1)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos3iv([3,4,0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos3s(1,2,1)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos3sv([3,4,0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    # 4
    glRasterPos4d(1.0,2.0,1.0,1.0)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos4dv([3.0,4.0,0.0,1.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos4f(1.0,2.0,1.0,1.0)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos4fv([3.0,4.0,0.0,1.0])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos4i(1,2,1,1)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos4iv([3,4,0,1])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    glRasterPos4s(1,2,1,1)
    assert_equal([1.0,2.0,1.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glRasterPos4sv([3,4,0,1])
    assert_equal([3.0,4.0,0.0,1.0], glGetDoublev(GL_CURRENT_RASTER_POSITION))
  end

  def test_glbitmap
    glOrtho(0,WINDOW_SIZE,0,WINDOW_SIZE,0,-1)

    bitmap = [ 0x55 ] * 8 # 64 bits (8x8 bitmap), stipple pattern

    glPixelStorei(GL_PACK_ALIGNMENT,1)
    glPixelStorei(GL_UNPACK_ALIGNMENT,1)

    glBitmap(8,8,0,0,0,0,bitmap.pack("c*"))
    data = glReadPixels(0,0,8,8,GL_RED,GL_UNSIGNED_BYTE)
    assert_equal([0,255] * 32, data.unpack("C*"))
  end

  def test_glfog
    glFogfv(GL_FOG_COLOR,[0.0,1.0,0.0,1.0])
    assert_equal(glGetDoublev(GL_FOG_COLOR),[0.0,1.0,0.0,1.0])
    glFogf(GL_FOG_DENSITY,0.5)
    assert_equal(glGetDoublev(GL_FOG_DENSITY),0.5)
    glFogi(GL_FOG_MODE,GL_LINEAR)
    assert_equal(glGetIntegerv(GL_FOG_MODE),GL_LINEAR)
    glFogi(GL_FOG_MODE,GL_EXP)
    assert_equal(glGetIntegerv(GL_FOG_MODE),GL_EXP)
    glFogiv(GL_FOG_MODE,[GL_EXP2])
    assert_equal(GL_EXP2, glGetIntegerv(GL_FOG_MODE))
  end

  def test_glcolorv
    glColor3fv Vector[1, 1, 1]

    assert_each_in_delta [1, 1, 1, 1], glGetDoublev(GL_CURRENT_COLOR)
  end

  def test_glcolor_3
    glColor3b(2**7-1, 0, 2**7-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3bv([0, 2**7-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3d(1.0, 0.0, 1.0)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3dv([0.0, 1.0, 0.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3f(1.0, 0.0, 1.0)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3fv([0.0, 1.0, 0.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3i(2**31-1, 0, 2**31-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3iv([0, 2**31-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3s(2**15-1, 0, 2**15-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3sv([0, 2**15-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3ub(2**8-1, 0, 2**8-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3ubv([0, 2**8-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3ui(2**32-1, 0, 2**32-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3uiv([0, 2**32-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3us(2**16-1, 0, 2**16-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor3usv([0, 2**16-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01
  end

  def test_glcolor_4
    glColor4b(2**7-1, 0, 2**7-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4bv([0, 2**7-1, 0, 2**7-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4d(1.0, 0.0, 1.0, 0.0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4dv([0.0, 1.0, 0.0, 1.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4fv([0.0, 1.0, 0.0, 1.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4i(2**31-1, 0, 2**31-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4iv([0, 2**31-1, 0, 2**31-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4s(2**15-1, 0, 2**15-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4sv([0, 2**15-1, 0, 2**15-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4ub(2**8-1, 0, 2**8-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4ubv([0, 2**8-1, 0, 2**8-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4ui(2**32-1, 0, 2**32-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4uiv([0, 2**32-1, 0, 2**32-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4us(2**16-1, 0, 2**16-1, 0)
    assert_each_in_delta [1.0, 0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_COLOR), 0.01

    glColor4usv([0, 2**16-1, 0, 2**16-1])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_COLOR), 0.01
  end

  def test_glortho
    res = [ [2.0/WINDOW_SIZE, 0, 0, 0],
      [0, 2.0/WINDOW_SIZE, 0, 0],
      [0, 0, 2, 0],
      [-1,-1,-1,1] ]

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0,WINDOW_SIZE,0,WINDOW_SIZE,0,-1)
    assert_equal(res, glGetDoublev(GL_PROJECTION_MATRIX))
  end

  def test_glnormal
    glNormal3d(1.0, 2.0, 3.0)
    assert_equal([1.0, 2.0, 3.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3dv([4.0, 5.0, 6.0])
    assert_equal([4.0, 5.0, 6.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3f(1.0, 2.0, 3.0)
    assert_equal([1.0, 2.0, 3.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3fv([4.0, 5.0, 6.0])
    assert_equal([4.0, 5.0, 6.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3i(1, 2, 3)
    assert_equal([1, 2, 3], glGetIntegerv(GL_CURRENT_NORMAL))

    glNormal3iv([4, 5, 6])
    assert_equal([4, 5, 6], glGetIntegerv(GL_CURRENT_NORMAL))

    glNormal3b(2**7-1, 0, 2**7-1)
    assert_each_in_delta([1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3bv(0, 2**7-1, 0)
    assert_each_in_delta([0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3s(2**15-1, 0, 2**15-1)
    assert_each_in_delta([1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_NORMAL))

    glNormal3sv(0, 2**15-1, 0)
    assert_each_in_delta([0.0, 1.0, 0.0], glGetDoublev(GL_CURRENT_NORMAL))
  end

  def test_gllight
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,80.0)
    assert_equal(80.0, glGetLightfv(GL_LIGHT0,GL_SPOT_CUTOFF))
    glLighti(GL_LIGHT0,GL_SPOT_CUTOFF,75)
    assert_equal(75, glGetLightiv(GL_LIGHT0,GL_SPOT_CUTOFF))
    glLightfv(GL_LIGHT0,GL_AMBIENT,[0.5,0.5,0.5,1.0])
    assert_equal([0.5,0.5,0.5,1.0], glGetLightfv(GL_LIGHT0,GL_AMBIENT))
    glLightiv(GL_LIGHT0,GL_CONSTANT_ATTENUATION,[32])
    assert_equal(32, glGetLightiv(GL_LIGHT0,GL_CONSTANT_ATTENUATION))
  end

  def test_glmaterial
    glMaterialfv(GL_FRONT,GL_AMBIENT,[0.0,1.0,0.0,1.0])
    assert_equal([0.0,1.0,0.0,1.0], glGetMaterialfv(GL_FRONT,GL_AMBIENT))

    glMaterialiv(GL_FRONT,GL_SHININESS,[50])
    assert_equal(50, glGetMaterialiv(GL_FRONT,GL_SHININESS))

    glMaterialf(GL_FRONT,GL_SHININESS,49.0)
    assert_equal(49.0, glGetMaterialfv(GL_FRONT,GL_SHININESS))

    glMateriali(GL_FRONT,GL_SHININESS,48)
    assert_equal(48, glGetMaterialiv(GL_FRONT,GL_SHININESS))

  end

  def test_glcolormaterial
    glColorMaterial(GL_FRONT,GL_EMISSION)
    assert_equal(GL_FRONT, glGetIntegerv(GL_COLOR_MATERIAL_FACE))
    assert_equal(GL_EMISSION, glGetIntegerv(GL_COLOR_MATERIAL_PARAMETER))

    glColorMaterial(GL_BACK,GL_SPECULAR)
    assert_equal(GL_BACK, glGetIntegerv(GL_COLOR_MATERIAL_FACE))
    assert_equal(GL_SPECULAR, glGetIntegerv(GL_COLOR_MATERIAL_PARAMETER))
  end

  def test_gllightmodel
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1)
    assert_equal(GL_TRUE, glGetBooleanv(GL_LIGHT_MODEL_TWO_SIDE))

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0)
    assert_equal(GL_FALSE, glGetBooleanv(GL_LIGHT_MODEL_TWO_SIDE))

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [0.5, 0.5, 0.5, 1.0])
    assert_equal([0.5, 0.5, 0.5, 1.0], glGetDoublev(GL_LIGHT_MODEL_AMBIENT))

    glLightModeliv(GL_LIGHT_MODEL_AMBIENT, [2, 0, 2, 0])
    assert_equal([2, 0, 2, 0], glGetIntegerv(GL_LIGHT_MODEL_AMBIENT))
  end

  def test_gltexcoordv
    glTexCoord2dv [1, 1]

    assert_each_in_delta [1, 1, 0, 1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS)
  end

  def test_gltexcoord_1
    glTexCoord1d(1.5)
    assert_equal([1.5,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1dv([0.5])
    assert_equal([0.5,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1f(1.5)
    assert_equal([1.5,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1fv([0.5])
    assert_equal([0.5,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1i(1)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1iv([0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1s(1)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord1sv([0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
  end

  def test_gltexcoord_2
    glTexCoord2d(1.5,1.5)
    assert_equal([1.5,1.5,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2dv([0.5,0.5])
    assert_equal([0.5,0.5,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2f(1.5,1.5)
    assert_equal([1.5,1.5,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2fv([0.5,0.5])
    assert_equal([0.5,0.5,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2i(1,1)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2iv([0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2s(1,1)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord2sv([0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
  end

  def test_gltexcoord_3
    glTexCoord3d(1.5,1.5,1.5)
    assert_equal([1.5,1.5,1.5,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3dv([0.5,0.5,0.5])
    assert_equal([0.5,0.5,0.5,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3f(1.5,1.5,1.5)
    assert_equal([1.5,1.5,1.5,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3fv([0.5,0.5,0.5])
    assert_equal([0.5,0.5,0.5,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3i(1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3iv([0,0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3s(1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord3sv([0,0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
  end

  def test_gltexcoord_4
    glTexCoord4d(1.5,1.5,1.5,1.5)
    assert_equal([1.5,1.5,1.5,1.5], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4dv([0.5,0.5,0.5,0.5])
    assert_equal([0.5,0.5,0.5,0.5], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4f(1.5,1.5,1.5,1.5)
    assert_equal([1.5,1.5,1.5,1.5], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4fv([0.5,0.5,0.5,0.5])
    assert_equal([0.5,0.5,0.5,0.5], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4i(1,1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4iv([0,0,0,0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4s(1,1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glTexCoord4sv([0,0,0,0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
  end

  def test_glenable_disable
    glEnable(GL_FOG)
    assert_equal(true, glIsEnabled(GL_FOG))
    glDisable(GL_FOG)
    assert_equal(false, glIsEnabled(GL_FOG))
  end

  def test_gltexparameter
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP)
    assert_equal(GL_CLAMP, glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S))

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT)
    assert_equal(GL_MIRRORED_REPEAT, glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S))

    glTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,[GL_CLAMP])
    assert_equal(GL_CLAMP, glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S))

    glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,[GL_MIRRORED_REPEAT])
    assert_equal(GL_MIRRORED_REPEAT, glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S))

    assert_equal(0.0, glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH))
    assert_equal(0, glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH))
  end

  def test_glcullface
    glCullFace(GL_FRONT)
    assert_equal(GL_FRONT, glGetIntegerv(GL_CULL_FACE_MODE))
    glCullFace(GL_BACK)
    assert_equal(GL_BACK, glGetIntegerv(GL_CULL_FACE_MODE))
  end

  def test_glfrontface
    glFrontFace(GL_CW)
    assert_equal(GL_CW, glGetIntegerv(GL_FRONT_FACE))
    glFrontFace(GL_CCW)
    assert_equal(GL_CCW, glGetIntegerv(GL_FRONT_FACE))
  end

  def test_glpointsize
    glPointSize(2.0)
    assert_equal(2.0, glGetDoublev(GL_POINT_SIZE))
    glPointSize(3.0)
    assert_equal(3.0, glGetDoublev(GL_POINT_SIZE))
  end

  def test_glpolygonmode
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE)
    assert_equal([GL_LINE,GL_LINE], glGetIntegerv(GL_POLYGON_MODE))
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL)
    assert_equal([GL_FILL,GL_FILL], glGetIntegerv(GL_POLYGON_MODE))
  end

  def test_gllinewidth
    glLineWidth(2.0)
    assert_equal(2.0, glGetDoublev(GL_LINE_WIDTH))
    glLineWidth(3.0)
    assert_equal(3.0, glGetDoublev(GL_LINE_WIDTH))
  end

  def test_gllinestipple
    glLineStipple(3,0x1234)
    assert_equal(3, glGetIntegerv(GL_LINE_STIPPLE_REPEAT))
    assert_equal(0x1234, glGetIntegerv(GL_LINE_STIPPLE_PATTERN))
  end

  def test_glpolygonstipple
    stipple = [0x12] * 128
    glPolygonStipple(stipple.pack("c*"))
    assert_equal(stipple.pack("c*"), glGetPolygonStipple())
  end

  def parse_feedback_data(data,count)
    c = count / 11
    ret = []
    (0...c).each do |x|
      i = x * 11
      type = data[0+i]

      v1 = [data[2+i], data[3+i], data[4+i]]
      v2 = [data[5+i], data[6+i], data[7+i]]
      v3 = [data[8+i], data[9+i], data[10+i]]
      vertex = [v1,v2,v3].sort
      ret << [type,vertex]
    end
    ret
  end

  def test_glvertex
    glMatrixMode(GL_PROJECTION)
    glOrtho(0,WINDOW_SIZE,0,WINDOW_SIZE,0,-1)

    buf = glFeedbackBuffer(256,GL_3D)

    glRenderMode(GL_FEEDBACK)

    glBegin(GL_TRIANGLES)
    glVertex2d( 1, 0)
    glVertex2dv([0,0])
    glVertex2f( 1,1)

    glVertex2fv([ 1, 0])
    glVertex2i(  0,0)
    glVertex2iv([1,1])

    glVertex2s( 1, 0)
    glVertex2sv([0,0])
    glVertex3d( 1,1,0)

    glVertex3dv([ 1, 0,0])
    glVertex3f(  0,0,0)
    glVertex3fv([1,1,0])

    glVertex3i( 1, 0,0)
    glVertex3iv([0,0,0])
    glVertex3s( 1,1,0)

    glVertex3sv([ 1, 0,0])
    glVertex4d(  0,0,0,1)
    glVertex4dv([1,1,0,1])

    glVertex4f( 1, 0,0,1)
    glVertex4fv([0,0,0,1])
    glVertex4i( 1,1,0,1)

    glVertex4iv([ 1, 0,0,1])
    glVertex4s(  0,0,0,1)
    glVertex4sv([1,1,0,1])

    glEnd()

    count = glRenderMode(GL_RENDER)
    data = buf.unpack("f*")

    ref = [[GL_POLYGON_TOKEN,[[0,0,0],[1,0,0],[1,1,0]]]] * 8

    assert_equal(ref, parse_feedback_data(data,count))
  end

  def test_glrect
    glMatrixMode GL_PROJECTION
    glOrtho 0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1

    buf = glFeedbackBuffer 256, GL_3D

    glRenderMode GL_FEEDBACK

    glRectd(0, 0, 1, 1)
    glRectdv([0, 0], [1, 1])

    glRectf(0, 0, 1, 1)
    glRectfv([0, 0], [1, 1])

    glRecti(0, 0, 1, 1)
    glRectiv([0, 0], [1, 1])

    glRects(0, 0, 1, 1)
    glRectsv([0, 0], [1, 1])

    count = glRenderMode GL_RENDER
    data = buf.unpack("f*")

    # eight 3d polygons with four points
    assert_equal 8 * (4 * 3 + 2), count
  end

  def test_glrectv
    glMatrixMode GL_PROJECTION
    glOrtho 0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1

    buf = glFeedbackBuffer 256, GL_3D

    glRenderMode GL_FEEDBACK

    glRectdv Vector[0, 0], Vector[1, 1]

    refute_equal 0, glRenderMode(GL_RENDER)
  end

  def test_glclear
    glClearColor(1.0,1.0,1.0,1.0)
    glClear(GL_COLOR_BUFFER_BIT)

    data = glReadPixels(0,0,1,1,GL_RGB,GL_FLOAT)
    assert_equal([1.0,1.0, 1.0], data.unpack("f*"))

    glClearColor(0.0,0.0,0.0,0.0)
    glClear(GL_COLOR_BUFFER_BIT)

    data = glReadPixels(0,0,1,1,GL_RGB,GL_FLOAT)
    assert_equal([0.0,0.0,0.0], data.unpack("f*"))
  end

  def test_gltexenv
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_ADD)
    assert_equal(GL_ADD, glGetTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE))
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE)
    assert_equal(GL_MODULATE, glGetTexEnviv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE))

    glTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,[GL_ADD])
    assert_equal(GL_ADD, glGetTexEnvfv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE))
    glTexEnviv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,[GL_MODULATE])
    assert_equal(GL_MODULATE, glGetTexEnviv(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE))
  end

  def test_gltexgen
    glTexGend(GL_S,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP)
    assert_equal(GL_REFLECTION_MAP, glGetTexGendv(GL_S,GL_TEXTURE_GEN_MODE))
    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR)
    assert_equal(GL_EYE_LINEAR, glGetTexGenfv(GL_S,GL_TEXTURE_GEN_MODE))
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP)
    assert_equal(GL_SPHERE_MAP, glGetTexGeniv(GL_S,GL_TEXTURE_GEN_MODE))

    glTexGendv(GL_S,GL_TEXTURE_GEN_MODE,[GL_REFLECTION_MAP])
    assert_equal(GL_REFLECTION_MAP, glGetTexGendv(GL_S,GL_TEXTURE_GEN_MODE))
    glTexGenfv(GL_S,GL_TEXTURE_GEN_MODE,[GL_EYE_LINEAR])
    assert_equal(GL_EYE_LINEAR, glGetTexGenfv(GL_S,GL_TEXTURE_GEN_MODE))
    glTexGeniv(GL_S,GL_TEXTURE_GEN_MODE,[GL_SPHERE_MAP])
    assert_equal(GL_SPHERE_MAP, glGetTexGeniv(GL_S,GL_TEXTURE_GEN_MODE))
  end

  def test_textures
    textures = glGenTextures(2)
    assert_equal(2, textures.size)
    assert_equal(false, glIsTexture(textures[0]))
    glBindTexture(GL_TEXTURE_2D,textures[0])
    assert_equal(true, glIsTexture(textures[0]))

    image = ([0,0,0,1,1,1] * 8).pack("f*") # 16 RGB pixels

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8, 4, 4, 0, GL_RGB, GL_FLOAT, image)
    assert_equal(image, glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT))

    glBindTexture(GL_TEXTURE_1D,textures[1])

    glTexImage1D(GL_TEXTURE_1D,0,GL_RGB8, 16, 0, GL_RGB, GL_FLOAT, image)
    assert_equal(image, glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT))

    glDeleteTextures(textures)
    assert_equal(false, glIsTexture(textures[0]))
  end

  def test_pixels
    glClearColor(0,0,0,0)
    glClear(GL_COLOR_BUFFER_BIT)

    data = glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT)
    assert_equal([0] * 3 * 16, data.unpack("f*"))

    image = ([1.0] * 3 * 16).pack("f*")
    glDrawPixels(4,4,GL_RGB,GL_FLOAT,image)

    data = glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT)
    assert_equal(image, data)

    #
    glClearColor(0,0,0,0)
    glClear(GL_COLOR_BUFFER_BIT)

    image = (([0.0] * 3 * 8) + ([1.0] * 3 * 8)).pack("f*")
    glDrawPixels(4,4,GL_RGB,GL_FLOAT,image)

    data = glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT)
    assert_equal(image, data)

    glCopyPixels(0,2,4,2,GL_COLOR)

    data = glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT)
    assert_equal(([1.0] * 3 * 16).pack("f*"), data)
  end

  def test_gltranslate
    m = [[1,0,0,0],[0,1,0,0],[0,0,1,0],[1,2,3,1]]
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslated(1.0,2.0,3.0)
    assert_equal(m, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glTranslatef(1.0,2.0,3.0)
    assert_equal(m, glGetDoublev(GL_MODELVIEW_MATRIX))
  end

  def test_glscale
    m = [[1,0,0,0],[0,2,0,0],[0,0,3,0],[0,0,0,1]]
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glScaled(1.0,2.0,3.0)
    assert_equal(m, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glScalef(1.0,2.0,3.0)
    assert_equal(m, glGetDoublev(GL_MODELVIEW_MATRIX))
  end

  def test_glrotate
    m1 = [[0, 0, -1, 0], [0, 1, 0, 0], [1, 0, 0, 0], [0, 0, 0, 1]]
    m2 = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glRotated(90, 0, 1, 0)

    assert_each_in_delta m1, glGetDoublev(GL_MODELVIEW_MATRIX)

    glRotated(-90, 0, 1, 0)

    assert_each_in_delta m2, glGetDoublev(GL_MODELVIEW_MATRIX)
  end

  def test_textures_2
    textures = glGenTextures(2)
    glBindTexture(GL_TEXTURE_1D,textures[0])
    glBindTexture(GL_TEXTURE_2D,textures[1])
    assert_equal(2, glAreTexturesResident(textures).size)
    glPrioritizeTextures(textures,[0.5,1.0])
    assert_equal(0.5, glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_PRIORITY))
    assert_equal(1.0, glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_PRIORITY))

    tex = ([0,0,0,1,1,1] * 2).pack("f*")
    tex2 = ([1] * 3 * 4).pack("f*")

    # 1d
    glDrawPixels(4,1,GL_RGB,GL_FLOAT,tex)
    glCopyTexImage1D(GL_TEXTURE_1D,0,GL_RGB8,0,0,4,0)
    assert_equal(tex, glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT))

    glDrawPixels(4,1,GL_RGB,GL_FLOAT,tex2)
    glCopyTexSubImage1D(GL_TEXTURE_1D,0,0,0,0,4)
    assert_equal(tex2, glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT))

    glTexSubImage1D(GL_TEXTURE_1D,0,0,4,GL_RGB,GL_FLOAT,tex)
    assert_equal(tex, glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT))

    # 2d
    glDrawPixels(2,2,GL_RGB,GL_FLOAT,tex)
    glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,0,0,2,2,0)
    assert_equal(tex, glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT))

    glDrawPixels(2,2,GL_RGB,GL_FLOAT,tex2)
    glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,2,2)
    assert_equal(tex2, glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT))

    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,2,2,GL_RGB,GL_FLOAT,tex)
    assert_equal(tex, glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT))

    glDeleteTextures(textures)
  end

  def test_glmap
    control_points = [
      0.25, 0.5, 0.0,
      1.0, 1.0, 0.0
    ]

    control_points_2 = [
      1.25, 1.5, 1.0,
      0.0, 0.0, 1.0
    ]

    glMap1f(GL_MAP1_VERTEX_3,0,100,3,2,control_points)
    assert_equal(control_points, glGetMapfv(GL_MAP1_VERTEX_3,GL_COEFF))

    glMap1d(GL_MAP1_VERTEX_3,0,100,3,2,control_points_2)
    assert_equal(control_points_2, glGetMapdv(GL_MAP1_VERTEX_3,GL_COEFF))

    assert_equal(2, glGetMapiv(GL_MAP1_VERTEX_3,GL_ORDER))

    glMap2f(GL_MAP2_VERTEX_3,0,100,3,1,0,100,3,2,control_points)
    assert_equal(control_points,glGetMapfv(GL_MAP2_VERTEX_3,GL_COEFF))

    glMap2d(GL_MAP2_VERTEX_3,0,100,3,1,0,100,3,2,control_points_2)
    assert_equal(control_points_2, glGetMapdv(GL_MAP2_VERTEX_3,GL_COEFF))
  end

  def test_glmapgrid
    glMapGrid1d(2,1,100)
    assert_equal(2, glGetIntegerv(GL_MAP1_GRID_SEGMENTS))
    assert_equal([1,100], glGetIntegerv(GL_MAP1_GRID_DOMAIN))
    glMapGrid1f(3,2,99)
    assert_equal(3, glGetIntegerv(GL_MAP1_GRID_SEGMENTS))
    assert_equal([2,99], glGetIntegerv(GL_MAP1_GRID_DOMAIN))
    #
    glMapGrid2d(2,1,100,3,2,99)
    assert_equal([2,3], glGetIntegerv(GL_MAP2_GRID_SEGMENTS))
    assert_equal([1,100,2,99], glGetIntegerv(GL_MAP2_GRID_DOMAIN))

    glMapGrid2f(3,2,99,4,3,98)
    assert_equal([3,4], glGetIntegerv(GL_MAP2_GRID_SEGMENTS))
    assert_equal([2,99,3,98], glGetIntegerv(GL_MAP2_GRID_DOMAIN))
  end

  def test_gleval
    control_points = [0,0,0,1,1,1]
    glMap1f(GL_MAP1_VERTEX_3,0,1,3,2,control_points)
    glMap2f(GL_MAP2_VERTEX_3,0,1,3,1,0,1,3,2,control_points)
    glEnable(GL_MAP1_VERTEX_3)
    glEnable(GL_MAP2_VERTEX_3)

    buf = glFeedbackBuffer(256,GL_3D)
    glRenderMode(GL_FEEDBACK)

    glBegin(GL_TRIANGLES)
    glEvalCoord1d(1.0)
    glEvalCoord1dv([1.0])
    glEvalCoord1f(1.0)

    glEvalCoord1fv([1.0])
    glEvalCoord1fv([1.0])
    glEvalCoord1fv([1.0])

    glEvalCoord2d(1.0,1.0)
    glEvalCoord2dv([1.0,1.0])
    glEvalCoord2f(1.0,1.0)

    glEvalCoord2fv([1.0,1.0])
    glEvalCoord2fv([1.0,1.0])
    glEvalCoord2fv([1.0,1.0])

    glEvalPoint1(0.0)
    glEvalPoint1(0.0)
    glEvalPoint1(0.0)

    glEvalPoint2(0.0,1.0)
    glEvalPoint2(0.0,1.0)
    glEvalPoint2(0.0,1.0)

    glEnd

    count = glRenderMode(GL_RENDER)
    assert_equal(count,(3*3+2)*6)

    glDisable(GL_MAP2_VERTEX_3)
    glDisable(GL_MAP1_VERTEX_3)
  end

  def test_glevalmesh
    control_points = [0,0,0,1,1,1]
    glMap1f(GL_MAP1_VERTEX_3,0,1,3,2,control_points)
    glMap2f(GL_MAP2_VERTEX_3,0,1,3,1,0,1,3,2,control_points)
    glEnable(GL_MAP1_VERTEX_3)
    glEnable(GL_MAP2_VERTEX_3)

    buf = glFeedbackBuffer(256,GL_3D)
    glRenderMode(GL_FEEDBACK)

    glEvalMesh1(GL_POINT,0,1)
    glEvalMesh2(GL_POINT,0,1,0,1)

    count = glRenderMode(GL_RENDER)
    assert_equal(count,((3+1)*(2+2*2)))

    glDisable(GL_MAP2_VERTEX_3)
    glDisable(GL_MAP1_VERTEX_3)
  end

  def test_glaccum
    return if glGetIntegerv(GL_ACCUM_RED_BITS) <= 0 # no accumulation buffer ?

    i1 = ([0.0] * 3 + [1.0] * 3 ).pack("f*")
    i2 = ([1.0] * 3 + [0.0] * 3 ).pack("f*")

    # init
    glClearColor(0,0,0,0)
    glClear(GL_ACCUM_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
    # left
    glDrawPixels(2,1,GL_RGB,GL_FLOAT,i1)
    glAccum(GL_ACCUM,1.0)
    # right
    glClear(GL_COLOR_BUFFER_BIT)
    glDrawPixels(2,1,GL_RGB,GL_FLOAT,i2)
    glAccum(GL_ACCUM,1.0)
    # combine
    glAccum(GL_RETURN,1.0)

    data = glReadPixels(0,0,2,1,GL_RGB,GL_FLOAT)
    assert_each_in_delta [1.0] * 2 * 3, data.unpack("f*"), 0.01
  end

  def test_displaylists
    base = glGenLists(2)
    assert(base>0)
    glListBase(1)
    assert_equal(1, glGetIntegerv(GL_LIST_BASE))
    glListBase(0)
    assert_equal(0, glGetIntegerv(GL_LIST_BASE))

    glNewList(base+0, GL_COMPILE)
    glBegin(GL_TRIANGLES)
    glVertex2f(0,0)
    glVertex2f(1,0)
    glVertex2f(1,1)
    glEnd()
    glEndList()

    glNewList(base+1, GL_COMPILE)
    glBegin(GL_TRIANGLES)
    glVertex2f(0,0)
    glVertex2f(1,0)
    glVertex2f(1,1)
    glEnd()
    glEndList()

    assert_equal(true, glIsList(base+0))
    assert_equal(true, glIsList(base+1))
    assert_equal(false, glIsList(base+2))

    #
    buf = glFeedbackBuffer(256,GL_3D)
    glRenderMode(GL_FEEDBACK)

    glCallList(base+0)
    glCallLists(GL_INT,[base+0,base+1])

    count = glRenderMode(GL_RENDER)
    assert_equal((3*3+2) * 3, count) # 3 triangles
    #

    glDeleteLists(base,2)

    assert_equal(false, glIsList(base+0))
    assert_equal(false, glIsList(base+1))
  end

  def test_arrays
    glEnableClientState(GL_VERTEX_ARRAY)

    va = [0, 0, 0, 1, 1, 1].pack("f*")

    glVertexPointer 2, GL_FLOAT, 8, va
    assert_equal va,       glGetPointerv(GL_VERTEX_ARRAY_POINTER)
    assert_equal 2,        glGetIntegerv(GL_VERTEX_ARRAY_SIZE)
    assert_equal GL_FLOAT, glGetIntegerv(GL_VERTEX_ARRAY_TYPE)
    assert_equal 8,        glGetIntegerv(GL_VERTEX_ARRAY_STRIDE)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glDrawArrays(GL_TRIANGLES, 0, 3)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glArrayElement(1)
    glArrayElement(2)
    glEnd

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("C*"))

    glInterleavedArrays(GL_V2F, 0, va)

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("C*"))

    count = glRenderMode(GL_RENDER)
    assert_equal(44, count)

    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_arrays_2
    na = [0, 1, 0].pack("f*")
    ta = [1, 0, 1, 0].pack("f*")
    ea = [0].pack("C*")
    ca = [1, 0, 1, 0].pack("f*")

    glNormalPointer(GL_FLOAT, 12, na)
    assert_equal(GL_FLOAT, glGetIntegerv(GL_NORMAL_ARRAY_TYPE))
    assert_equal(12, glGetIntegerv(GL_NORMAL_ARRAY_STRIDE))
    assert_equal(na, glGetPointerv(GL_NORMAL_ARRAY_POINTER))

    glTexCoordPointer(4, GL_FLOAT, 16, ta)
    assert_equal(4, glGetIntegerv(GL_TEXTURE_COORD_ARRAY_SIZE))
    assert_equal(GL_FLOAT, glGetIntegerv(GL_TEXTURE_COORD_ARRAY_TYPE))
    assert_equal(16, glGetIntegerv(GL_TEXTURE_COORD_ARRAY_STRIDE))
    assert_equal(ta, glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER))

    glEdgeFlagPointer(1, ea)
    assert_equal(1, glGetIntegerv(GL_EDGE_FLAG_ARRAY_STRIDE))
    assert_equal(ea, glGetPointerv(GL_EDGE_FLAG_ARRAY_POINTER))

    glColorPointer(4, GL_FLOAT, 16, ca)
    assert_equal(4, glGetIntegerv(GL_COLOR_ARRAY_SIZE))
    assert_equal(GL_FLOAT, glGetIntegerv(GL_COLOR_ARRAY_TYPE))
    assert_equal(16, glGetIntegerv(GL_COLOR_ARRAY_STRIDE))
    assert_equal(ca, glGetPointerv(GL_COLOR_ARRAY_POINTER))

    glEnableClientState(GL_COLOR_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glEnableClientState(GL_TEXTURE_COORD_ARRAY)
    glEnableClientState(GL_EDGE_FLAG_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd

    assert_each_in_delta([1, 0, 1, 0], glGetDoublev(GL_CURRENT_COLOR))
    assert_equal([0, 1, 0], glGetDoublev(GL_CURRENT_NORMAL))
    assert_equal([1, 0, 1, 0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    assert_equal(false, glGetBooleanv(GL_EDGE_FLAG))

    glDisableClientState(GL_EDGE_FLAG_ARRAY)
    glDisableClientState(GL_TEXTURE_COORD_ARRAY)
    glDisableClientState(GL_NORMAL_ARRAY)
    glDisableClientState(GL_COLOR_ARRAY)
  end
end
