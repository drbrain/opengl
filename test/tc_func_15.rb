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
		assert_equal(glIsQuery(queries[1]),GL_TRUE)
		
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
		assert_equal(glIsQuery(queries[1]),GL_FALSE)
	end
	
	def test_buffers
		return if not supported?(1.5)
		buffers = glGenBuffers(2)
		glBindBuffer(GL_ARRAY_BUFFER,buffers[0])
		assert_equal(glIsBuffer(buffers[0]),GL_TRUE)		

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
		assert_equal(glIsBuffer(buffers[0]),GL_FALSE)

		# FIXME: GetBufferPointerv not yet implemented
	end
end
