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

class Test_15 < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_query
		return if not supported?(1.5)
		queries = glGenQueries(2)
		assert_equal(queries.size,2)

		glBeginQuery(GL_SAMPLES_PASSED,queries[1])
		assert_equal(glIsQuery(queries[1]),true)
		
		glBegin(GL_TRIANGLES)
		glVertex2i(0,0)
		glVertex2i(1,0)
		glVertex2i(1,1)
		glEnd()

		assert_equal(glGetQueryiv(GL_SAMPLES_PASSED,GL_CURRENT_QUERY),[queries[1]])
	
		glEndQuery(GL_SAMPLES_PASSED)
		
		r = glGetQueryObjectiv(queries[1],GL_QUERY_RESULT_AVAILABLE)
		assert((r==[GL_TRUE] || r==[GL_FALSE]))

		if (r==[GL_TRUE])
		assert(glGetQueryObjectiv(queries[1],GL_QUERY_RESULT)[0] > 0)
		assert(glGetQueryObjectuiv(queries[1],GL_QUERY_RESULT)[0] > 0)
		end
		
		glDeleteQueries(queries)
		assert_equal(glIsQuery(queries[1]),false)
	end
	
	def test_buffers
		return if not supported?(1.5)
		buffers = glGenBuffers(2)
		glBindBuffer(GL_ARRAY_BUFFER,buffers[0])
		assert_equal(glIsBuffer(buffers[0]),true)		

		data = [0,1,2,3].pack("C*")
		data2 = [4,5,6,7].pack("C*")

		glBufferData(GL_ARRAY_BUFFER,4,data,GL_STREAM_READ)
		assert_equal(glGetBufferSubData(GL_ARRAY_BUFFER,0,4),data)

		assert_equal(glGetBufferParameteriv(GL_ARRAY_BUFFER,GL_BUFFER_USAGE),[GL_STREAM_READ])

		glBufferSubData(GL_ARRAY_BUFFER,0,4,data2)
		assert_equal(glGetBufferSubData(GL_ARRAY_BUFFER,0,4),data2)

		assert_equal(glMapBuffer(GL_ARRAY_BUFFER,GL_READ_ONLY),data2)
		r = glUnmapBuffer(GL_ARRAY_BUFFER)
		assert(r == GL_TRUE || r == GL_FALSE)
		glDeleteBuffers(buffers)		
		assert_equal(glIsBuffer(buffers[0]),false)

		# FIXME: GetBufferPointerv not yet implemented
	end

	def test_buffer_binding_element_array
		return if not supported?(1.5)

		glEnableClientState(GL_VERTEX_ARRAY)
		va = [0,0, 0,1, 1,1].pack("f*")
		glVertexPointer(2,GL_FLOAT,0,va)

		#
		data = [0,1,2].pack("C*")
		buffers = glGenBuffers(1)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[0])
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,3,data,GL_DYNAMIC_DRAW)

		#
		feedback = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,0)
		glDrawRangeElements(GL_TRIANGLES,0,3,3,GL_UNSIGNED_BYTE,0)

		count = glRenderMode(GL_RENDER)
		assert_equal(count,22)

		glDisableClientState(GL_VERTEX_ARRAY)
		glDeleteBuffers(buffers)
	end

	def test_buffer_binding_array_1
		return if not supported?(1.5)

		glEnableClientState(GL_VERTEX_ARRAY)
		va = [0,0, 0,1, 1,1].pack("f*")

		#
		buffers = glGenBuffers(1)
		glBindBuffer(GL_ARRAY_BUFFER,buffers[0])
		glBufferData(GL_ARRAY_BUFFER,6*4,va,GL_DYNAMIC_DRAW)

		glVertexPointer(2,GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_VERTEX_ARRAY_POINTER),0)
		#
		feedback = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,[0,1,2].pack("f*"))

		count = glRenderMode(GL_RENDER)
		assert_equal(count,11)
		
		glDeleteBuffers(buffers)
		glDisableClientState(GL_VERTEX_ARRAY)
	end

	def test_buffer_binding_array_2
		return if not supported?(1.5)

		efa = [0].pack("C*")
		na = [0,1,0].pack("f*")
		ca = [1,0,1,0].pack("f*")
		ta = [1,0,1,0].pack("f*")

		buffers = glGenBuffers(4)
		# load data into buffers
		buffer_efa,buffer_na,buffer_ca,buffer_ta = buffers

		glBindBuffer(GL_ARRAY_BUFFER,buffer_efa)
		glBufferData(GL_ARRAY_BUFFER,1,efa,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_na)
		glBufferData(GL_ARRAY_BUFFER,3*4,na,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_ca)
		glBufferData(GL_ARRAY_BUFFER,4*4,ca,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_ta)
		glBufferData(GL_ARRAY_BUFFER,4*4,ta,GL_DYNAMIC_DRAW)

		# load buffers into arrays
		glBindBuffer(GL_ARRAY_BUFFER,buffer_na)
		glEdgeFlagPointer(0,0)
		assert_equal(glGetPointerv(GL_EDGE_FLAG_ARRAY_POINTER),0)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_na)
		glNormalPointer(GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_NORMAL_ARRAY_POINTER),0)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_ca)
		glColorPointer(4,GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_COLOR_ARRAY_POINTER),0)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_ta)
		glTexCoordPointer(4,GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER),0)

		# not really testing index
		glIndexPointer(GL_INT,2,0)
		assert_equal(glGetPointerv(GL_INDEX_ARRAY_POINTER),0)

		# draw arrays
		glEnable(GL_NORMAL_ARRAY)
		glEnable(GL_COLOR_ARRAY)
		glEnable(GL_TEXTURE_COORD_ARRAY)
		glEnable(GL_EDGE_FLAG_ARRAY)

		glBegin(GL_TRIANGLES)
		glArrayElement(0)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_NORMAL),[0,1,0])
		assert_equal(glGetDoublev(GL_CURRENT_COLOR),[1,0,1,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS),[1,0,1,0])
		assert_equal(glGetDoublev(GL_EDGE_FLAG),GL_FALSE)

		glDisable(GL_EDGE_FLAG_ARRAY)
		glDisable(GL_TEXTURE_COORD_ARRAY)
		glDisable(GL_COLOR_ARRAY)
		glDisable(GL_NORMAL_ARRAY)

		glDeleteBuffers(buffers)
	end

	def test_buffer_binding_array_3
		return if not supported?(1.5)

		sc = [0,1,0].pack("f*")
		fc = [1].pack("f*")

		buffers = glGenBuffers(2)
		# load data into buffers
		buffer_sc,buffer_fc = buffers

		glBindBuffer(GL_ARRAY_BUFFER,buffer_sc)
		glBufferData(GL_ARRAY_BUFFER,3*4,sc,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_fc)
		glBufferData(GL_ARRAY_BUFFER,1*4,fc,GL_DYNAMIC_DRAW)

		# load buffers into arrays
		glBindBuffer(GL_ARRAY_BUFFER,buffer_sc)
		glSecondaryColorPointer(3,GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER),0)

		glBindBuffer(GL_ARRAY_BUFFER,buffer_fc)
		glFogCoordPointer(GL_FLOAT,0,0)
		assert_equal(glGetPointerv(GL_FOG_COORD_ARRAY_POINTER),0)

		# draw arrays
		glEnableClientState(GL_SECONDARY_COLOR_ARRAY)
		glEnableClientState(GL_FOG_COORD_ARRAY)

		glBegin(GL_TRIANGLES)
		glArrayElement(0)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0,1,0,1])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),1)

		glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
		glDisableClientState(GL_FOG_COORD_ARRAY)
		
		glDeleteBuffers(buffers)
	end

	def test_buffer_binding_array_4
		return if not supported?(1.5)
		va = [0,0, 1,0, 1,1, 0,0, 1,0, 0,1].pack("f*")
		glVertexPointer(2,GL_FLOAT,0,va)
		
		glEnable(GL_VERTEX_ARRAY)

		buf = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		data = [0,1,2,3,4,5]
		buffers = glGenBuffers(3)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[0])
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,6,data.pack("C*"),GL_DYNAMIC_DRAW)

		glMultiDrawElements(GL_TRIANGLES,GL_UNSIGNED_BYTE,[3,3],[0,3])

		count = glRenderMode(GL_RENDER)
		assert_equal(count,(3*3+2)*2)

		glDisable(GL_VERTEX_ARRAY)
		glDeleteBuffers(buffers)
	end

end
