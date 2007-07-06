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

class Test_15 < Test::Unit::TestCase
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

	def test_query
		return if not supported?(["glGenQueries","glDeleteQueries","glIsQuery","glBeginQuery","glGetQueryiv","glGetQueryObjectiv","glGetQueryObjectuiv"])
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
		
		r = [GL_FALSE]
		100.times do 
			r = glGetQueryObjectiv(queries[1],GL_QUERY_RESULT_AVAILABLE)
			break if (r[0]==GL_FALSE)
			sleep(10)
		end

		assert(glGetQueryObjectiv(queries[1],GL_QUERY_RESULT)[0] > 0)
		assert(glGetQueryObjectuiv(queries[1],GL_QUERY_RESULT)[0] > 0)

		glDeleteQueries(queries)
		assert_equal(glIsQuery(queries[1]),GL_FALSE)
	end
	
	def test_buffers
		return if not supported?(["glGenBuffers","glDeleteBuffers","glIsBuffer","glBindBuffer","glBufferData","glBufferSubData","glGetBufferSubData","glMapBuffer","glUnmapBuffer","glGetBufferParameteriv","glGetBufferPointerv"])
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
