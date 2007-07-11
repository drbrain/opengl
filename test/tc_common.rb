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
    $: << File.join(File.dirname(__FILE__), '..', 'lib')
end

require 'test/unit'
require 'gl'
require 'glut'
include Gl
include Glut

$window_size = 512

def glut_init()
		glutInit
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_ACCUM | GLUT_ALPHA)
	  glutInitWindowPosition(1, 1)
	  glutInitWindowSize($window_size, $window_size)
	  glutCreateWindow("test")
end

def approx_equal(a,b,epsilon=0.01)
	(0...a.size).each do |i|
		if ((a[i] - b[i]).abs > epsilon)
			return false
		end
	end
	true
end

def common_setup
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

def common_teardown
	glPopAttrib()
	glPopClientAttrib()
	assert_equal(glGetError(),0) # all expected GL errors must be handled by the method itself
end

def supported?(funcs)
	funcs.each do |name|
		if !Gl.is_available?(name)
				puts ""				
				puts "Function/extension #{name} not supported, test skipped"
				return false
		end
	end
	return true
end
