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

require 'gl'
require 'glut'

#
# Supportive GL functions for tests
#
module GL_func
	def clear_screen
		Gl.glClear(Gl::GL_COLOR_BUFFER_BIT)
	end
	
	def clear_screen_and_depth_buffer
		Gl.glClear(Gl::GL_COLOR_BUFFER_BIT | Gl::GL_DEPTH_BUFFER_BIT)
	end

	def reset_projection
        Gl.glMatrixMode(Gl::GL_PROJECTION)
        Gl.glLoadIdentity
	end

	def reset_modelview
        Gl.glMatrixMode(Gl::GL_MODELVIEW)
        Gl.glLoadIdentity
	end

	def push_projection
        Gl.glMatrixMode(Gl::GL_PROJECTION)
        Gl.glPushMatrix
	end

	def push_modelview
        Gl.glMatrixMode(Gl::GL_MODELVIEW)
        Gl.glPushMatrix
	end

	def pop_projection
        Gl.glMatrixMode(Gl::GL_PROJECTION)
        Gl.glPopMatrix
	end

	def pop_modelview
        Gl.glMatrixMode(Gl::GL_MODELVIEW)
        Gl.glPopMatrix
	end

	def get_window_dims
		x,y,sx,sy = Gl.glGetIntegerv(Gl::GL_VIEWPORT)
		[sx-x, sy-y]
	end
	
	def projection_ortho_box(size=10)
		reset_projection
        Gl.glOrtho(-size, size, -size, size, -size, size)
	end

	def projection_ortho_window
		reset_projection
		x,y = get_window_dims
        Gl.glOrtho(0, x, 0, y, -1, 1)
	end

	def print_text(text,x,y,color=[255,255,255],font = Glut::GLUT_BITMAP_HELVETICA_18)
		# TODO: push/pop attributes (texturing, color etc.)
		push_modelview
		reset_modelview
		push_projection
		projection_ortho_window

		Gl.glColor3ubv(color)
        Gl.glRasterPos2d(x,y)
        text.each_byte {|c| Glut::glutBitmapCharacter(font,c) }

		pop_projection
		pop_modelview
	end

	# creates checker RGB bitmap
	# for RGBA, pass both colors as [r,g,b,a], this applies to other modes as well
	def checker_texture_bitmap(size=64,divide=8,color_a=[255,255,255],color_b=[0,0,0])
		strip_a = color_a.pack("c*") * (size/divide)
		strip_b = color_b.pack("c*") * (size/divide)
		line_strip_a = (strip_a + strip_b) * (size/2)
		line_strip_b = (strip_b + strip_a) * (size/2)
		(line_strip_a + line_strip_b) * (divide/2)
	end

	# creates 'fly' bitmap from OpenGL red book
	def redbook_fly_bitmap
		bitmap = [
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60,
0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20,
0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC,
0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08,
0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
		]
		bitmap.pack("c*")
	end
end

# Test runner - finds all classes matching $prefix, then creates instance of each,
#               calling $class.loop as glut loop for each test, and $class.destroy (if any)
#               for cleanup
class Test_Runner
	include GL_func

	def initialize(prefix = "GLtest_", title = "test_???", width = 512, height = 512, posx = 50, posy = 50)
		@test_list = Class.constants.sort.find_all {|c| c =~ /^#{prefix}/}
		@test_index = nil
		@test_results = Array.new(@test_list.size, nil)

		Glut.glutInit
	    Glut.glutInitDisplayMode(Glut::GLUT_DEPTH | Glut::GLUT_DOUBLE | Glut::GLUT_RGB)
	    Glut.glutInitWindowPosition(posx, posy)
	    Glut.glutInitWindowSize(width, height)
	    Glut.glutCreateWindow(title)

	    Glut.glutDisplayFunc(method(:loop_func).to_proc)
	    Glut.glutIdleFunc(method(:idle_func).to_proc)
	    Glut.glutReshapeFunc(method(:reshape_func).to_proc)
	    Glut.glutKeyboardFunc(method(:keyboard_func).to_proc)

		# set to first test
		next_test

		# start
		Glut.glutMainLoop()
	end

	def print_summary
		puts "Test results:"
		total = pass = fail = skip = 0
		@test_list.size.times do |i|
			total += 1
			case @test_results[i]
			when true:
				pass += 1
			when false:
				fail += 1
				puts "#{@test_list[i]} test failed"
			when nil:
				skip += 1
				puts "#{@test_list[i]} test skipped"
			end
		end
		puts "#{total} tests, #{pass} passed, #{fail} failed, #{skip} unsupported"
	end

	def reset_state
		clear_screen_and_depth_buffer
		reset_modelview
		reset_projection
	end

	def check_functions(c)
		status = true
		c::FUNCTIONS_TESTED.each do |f|
			if Gl.is_available?(f)==false # avaiable on current h/w ?
				puts "Function #{f} not supported on current machine"
				status = false
			end
			if Gl.methods.include?(f)==false # implemented by our bindings ?
				puts "Function #{f} not exported by bindings"
				status = false
			end
		end
		return status
	end

	# advances to next test, if any
	def next_test
		while true
			if (@test_index == nil) # first test
				@test = nil
				@test_index = 0
			else # cleanup after previous test (if any) and advance iterator
				@test.destroy if @test and @test.respond_to? :destroy
				reset_state if @test
				@test_index += 1
			end

			if @test_index >= @test_list.size # beyond last test
				print_summary	
				exit
			end

			cl = eval(@test_list[@test_index]) # String -> class
			if check_functions(cl) # check if tested functions are supported on current machine
				@test = cl.new
				break
			else # not supported, try next test
				@test_results[@test_index] = nil
				@test = nil
			end
		end
	end

	def loop_func
		@test.loop if @test.respond_to? :loop

		print_text("Test: #{@test.class.to_s}",10,30)
		print_text("Does this test look like reference rendering (y/n)?",10,10)

		Glut.glutSwapBuffers()
	end

	def idle_func
		@test.idle if @test.respond_to? :idle
		Glut.glutPostRedisplay()
	end

	def reshape_func(w,h)
		@test.reshape(w,h) if @test.respond_to? :reshape
	end
	
	# test will be marked pass/fail depending on whether user presses 'y' or 'n'
	def keyboard_func(k, x, y)
		case k
		when ?y, ?n
			@test_results[@test_index] = (k==?y ? true : false)
			next_test
		when 27 # Esc
			puts "Aborted!"
	        exit
	    end
	    Glut.glutPostRedisplay()
	end
end
