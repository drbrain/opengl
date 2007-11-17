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
require 'matrix'
include Gl
include Glut

Gl.enable_error_checking

$window_size = 512

def glut_init()
	display_func = lambda do
		raise
	end

	glutInit
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_ACCUM | GLUT_ALPHA)
	glutInitWindowPosition(1, 1)
	glutInitWindowSize($window_size, $window_size)
	glutCreateWindow("test")
	glutDisplayFunc(display_func)
	# hack the need to call glutMainLoop on some implementations
	begin
		glutMainLoop()
	rescue
		# continue
	end
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
	
	# in case there is an GL error that escaped error checking routines ...
	error = glGetError()
	p gluErrorString(error)	if (error!=0)
	assert_equal(error,0)
end

def supported?(funcs)
	Array(funcs).each do |name| # convert to array if it isn't already
		if !Gl.is_available?(name)
			puts ""				
			puts "#{name} not supported, test skipped"
			return false
		end
	end
	return true
end
