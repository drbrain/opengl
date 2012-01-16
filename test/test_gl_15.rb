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

class TestGl15 < OpenGL::TestCase

  def setup
    super

    supported? 1.5
  end

  def test_query
    queries = glGenQueries 2
    assert_equal 2, queries.length

    glBeginQuery GL_SAMPLES_PASSED, queries[1]
    assert glIsQuery(queries[1])

    glBegin GL_TRIANGLES do
      glVertex2i 0, 0
      glVertex2i 1, 0
      glVertex2i 1, 1
    end

    assert_equal queries[1], glGetQueryiv(GL_SAMPLES_PASSED, GL_CURRENT_QUERY)

    glEndQuery GL_SAMPLES_PASSED

    r = glGetQueryObjectiv queries[1], GL_QUERY_RESULT_AVAILABLE
    assert(r == GL_TRUE || r == GL_FALSE)

    if r == GL_TRUE
      assert_operator 0, :<=, glGetQueryObjectiv(queries[1], GL_QUERY_RESULT)[0]
      assert_operator 0, :<=, glGetQueryObjectuiv(queries[1], GL_QUERY_RESULT)[0]
    end

    glDeleteQueries queries
    refute glIsQuery queries[1]
  end

  def test_buffers
    buffers = glGenBuffers(2)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    assert glIsBuffer buffers[0]

    data = [0, 1, 2, 3].pack("C*")
    data2 = [4, 5, 6, 7].pack("C*")

    glBufferData(GL_ARRAY_BUFFER, 4, data, GL_STREAM_READ)
    assert_equal data, glGetBufferSubData(GL_ARRAY_BUFFER, 0, 4)

    assert_equal GL_STREAM_READ, glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE)

    glBufferSubData(GL_ARRAY_BUFFER, 0, 4, data2)
    assert_equal data2, glGetBufferSubData(GL_ARRAY_BUFFER, 0, 4)

    assert_equal data2, glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY)
    r = glUnmapBuffer(GL_ARRAY_BUFFER)
    assert(r == true || r == false)

    glDeleteBuffers(buffers)		
    refute glIsBuffer(buffers[0])

    # FIXME: GetBufferPointerv not yet implemented
  end

  def test_buffer_binding_element_array
    glEnableClientState(GL_VERTEX_ARRAY)
    va = [0, 0, 0, 1, 1, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    #
    data = [0, 1, 2].pack("C*")
    buffers = glGenBuffers(1)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3, data, GL_DYNAMIC_DRAW)

    #
    feedback = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0)
    glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_BYTE, 0)

    count = glRenderMode(GL_RENDER)
    assert_equal 22, count

    glDisableClientState(GL_VERTEX_ARRAY)
    glDeleteBuffers(buffers)
  end

  def test_buffer_binding_array_1
    glEnableClientState(GL_VERTEX_ARRAY)
    va = [0, 0, 0, 1, 1, 1].pack("f*")

    #
    buffers = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ARRAY_BUFFER, 6*4, va, GL_DYNAMIC_DRAW)

    glVertexPointer(2, GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_VERTEX_ARRAY_POINTER)
    #
    feedback = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("f*"))

    count = glRenderMode(GL_RENDER)
    assert_equal 11, count

    glDeleteBuffers(buffers)
    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_buffer_binding_array_2
    efa = [0].pack("C*")
    na = [0, 1, 0].pack("f*")
    ca = [1, 0, 1, 0].pack("f*")
    ta = [1, 0, 1, 0].pack("f*")

    buffers = glGenBuffers(4)
    # load data into buffers
    buffer_efa, buffer_na, buffer_ca, buffer_ta = buffers

    glBindBuffer(GL_ARRAY_BUFFER, buffer_efa)
    glBufferData(GL_ARRAY_BUFFER, 1, efa, GL_DYNAMIC_DRAW)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_na)
    glBufferData(GL_ARRAY_BUFFER, 3*4, na, GL_DYNAMIC_DRAW)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_ca)
    glBufferData(GL_ARRAY_BUFFER, 4*4, ca, GL_DYNAMIC_DRAW)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_ta)
    glBufferData(GL_ARRAY_BUFFER, 4*4, ta, GL_DYNAMIC_DRAW)

    # load buffers into arrays
    glBindBuffer(GL_ARRAY_BUFFER, buffer_na)
    glEdgeFlagPointer(0, 0)
    assert_equal 0, glGetPointerv(GL_EDGE_FLAG_ARRAY_POINTER)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_na)
    glNormalPointer(GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_NORMAL_ARRAY_POINTER)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_ca)
    glColorPointer(4, GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_COLOR_ARRAY_POINTER)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_ta)
    glTexCoordPointer(4, GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER)

    # not really testing index
    glIndexPointer(GL_INT, 2, 0)
    assert_equal 0, glGetPointerv(GL_INDEX_ARRAY_POINTER)

    # draw arrays
    glEnableClientState(GL_NORMAL_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glEnableClientState(GL_TEXTURE_COORD_ARRAY)
    glEnableClientState(GL_EDGE_FLAG_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd()

    assert_equal [0, 1, 0],    glGetDoublev(GL_CURRENT_NORMAL)
    assert_equal [1, 0, 1, 0], glGetDoublev(GL_CURRENT_COLOR)
    assert_equal [1, 0, 1, 0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS)

    assert_equal GL_FALSE, glGetBooleanv(GL_EDGE_FLAG)

    glDisableClientState(GL_EDGE_FLAG_ARRAY)
    glDisableClientState(GL_TEXTURE_COORD_ARRAY)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_NORMAL_ARRAY)

    glDeleteBuffers(buffers)
  end

  def test_buffer_binding_array_3
    sc = [0, 1, 0].pack("f*")
    fc = [1].pack("f*")

    buffers = glGenBuffers(2)
    # load data into buffers
    buffer_sc, buffer_fc = buffers

    glBindBuffer(GL_ARRAY_BUFFER, buffer_sc)
    glBufferData(GL_ARRAY_BUFFER, 3*4, sc, GL_DYNAMIC_DRAW)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_fc)
    glBufferData(GL_ARRAY_BUFFER, 1*4, fc, GL_DYNAMIC_DRAW)

    # load buffers into arrays
    glBindBuffer(GL_ARRAY_BUFFER, buffer_sc)
    glSecondaryColorPointer(3, GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER)

    glBindBuffer(GL_ARRAY_BUFFER, buffer_fc)
    glFogCoordPointer(GL_FLOAT, 0, 0)
    assert_equal 0, glGetPointerv(GL_FOG_COORD_ARRAY_POINTER)

    # draw arrays
    glEnableClientState(GL_SECONDARY_COLOR_ARRAY)
    glEnableClientState(GL_FOG_COORD_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd()

    assert_equal [0, 1, 0, 1], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)
    assert_equal 1, glGetDoublev(GL_CURRENT_FOG_COORD)

    glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
    glDisableClientState(GL_FOG_COORD_ARRAY)

    glDeleteBuffers(buffers)
  end

  def test_buffer_binding_array_4
    va = [0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    glEnableClientState(GL_VERTEX_ARRAY)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    data = [0, 1, 2, 3, 4, 5]
    buffers = glGenBuffers(3)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6, data.pack("C*"), GL_DYNAMIC_DRAW)

    glMultiDrawElements(GL_TRIANGLES, GL_UNSIGNED_BYTE, [3, 3], [0, 3])

    count = glRenderMode(GL_RENDER)
    assert_equal 2 * (3 * 3 + 2), count

    glDisableClientState(GL_VERTEX_ARRAY)
    glDeleteBuffers(buffers)
  end

end
