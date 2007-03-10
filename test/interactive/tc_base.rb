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

require 'gltest_glut'

include GL_func
include Gl
include Glut

# tests glVertex* and glColor* functions
class GLtest_1_vertex_color
	FUNCTIONS_TESTED = [
"glBegin","glEnd",
"glColor3b","glColor3bv","glColor3d","glColor3dv","glColor3f","glColor3fv","glColor3i",
"glColor3iv","glColor3s","glColor3sv","glColor3ub","glColor3ubv","glColor3ui","glColor3uiv",
"glColor3us","glColor3usv","glColor4b","glColor4bv","glColor4d","glColor4dv","glColor4f",
"glColor4fv","glColor4i","glColor4iv","glColor4s","glColor4sv","glColor4ub","glColor4ubv",
"glColor4ui","glColor4uiv","glColor4us","glColor4usv","glVertex2d","glVertex2dv","glVertex2f",
"glVertex2fv","glVertex2i","glVertex2iv","glVertex2s","glVertex2sv","glVertex3d","glVertex3dv",
"glVertex3f","glVertex3fv","glVertex3i","glVertex3iv","glVertex3s","glVertex3sv","glVertex4d",
"glVertex4dv","glVertex4f","glVertex4fv","glVertex4i","glVertex4iv","glVertex4s","glVertex4sv"
	]
	def initialize
		projection_ortho_box(10)
	end
	def advance_down
		glTranslatef(0,@space * -1,0)
	end
	def advance_up
		glTranslatef(0,@space * 1,0)
	end
	def advance_right
		glTranslatef(@space * 1,0,0)
	end
	def plain_quad
		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd
	end
	def loop
		@space = 2.2

		max_byte = 2**7-1
		max_ubyte = 2**8-1
		max_short = 2**15-1
		max_ushort = 2**16-1
		max_int = 2**31-1
		max_uint = 2**32-1

		clear_screen_and_depth_buffer
		reset_modelview

		# 1st column
		glColor3i(0,0,0)
		glTranslated(@space * -4 +1,-1,0)

		glColor3b(max_byte,max_byte,0)

		glBegin(GL_QUADS)
		glVertex2s(-1,-1)
		glVertex2i( 1,-1)
		glVertex2f( 1.0,1.0)
		glVertex2d(-1.0,1.0)
		glEnd

		advance_up

		glColor3s(0,0,max_short)

		glBegin(GL_QUADS)
		glVertex3s(-1,-1,0)
		glVertex3i( 1,-1,0)
		glVertex3f( 1.0,1.0,0.0)
		glVertex3d(-1.0,1.0,0.0)
		glEnd

		advance_up

		glColor3i(0,max_int,0)

		glBegin(GL_QUADS)
		glVertex4s(-1,-1,0,1)
		glVertex4i( 1,-1,0,1)
		glVertex4f( 1.0,1.0,0.0,1.0)
		glVertex4d(-1.0,1.0,0.0,1.0)
		glEnd

		advance_up

		glColor3f(1.0,0.0,0.0)

		glBegin(GL_QUADS)
		glVertex2sv([-1,-1])
		glVertex2iv([ 1,-1])
		glVertex2fv([ 1.0,1.0])
		glVertex2dv([-1.0,1.0])
		glEnd

		# 2nd column
		glColor3i(0,0,0)
		advance_right

		glColor3d(1.0,0.0,0.0)

		glBegin(GL_QUADS)
		glVertex3sv([-1,-1,0])
		glVertex3iv([ 1,-1,0])
		glVertex3fv([ 1.0,1.0,0.0])
		glVertex3dv([-1.0,1.0,0.0])
		glEnd

		advance_down

		glColor3ub(0,max_ubyte,0)

		glBegin(GL_QUADS)
		glVertex4sv([-1,-1,0,1])
		glVertex4iv([ 1,-1,0,1])
		glVertex4fv([ 1.0,1.0,0.0,1.0])
		glVertex4dv([-1.0,1.0,0.0,1.0])
		glEnd

		advance_down
		glColor3us(0,0,max_ushort)
		plain_quad

		advance_down
		glColor3ui(max_uint,max_uint,0)
		plain_quad

		# 3rd column
		glColor3i(0,0,0)
		advance_right
		glColor4b(max_byte,max_byte,0,max_byte)
		plain_quad

		advance_up
		glColor4s(0,0,max_short,max_short)
		plain_quad

		advance_up
		glColor4i(0,max_int,0,max_int)
		plain_quad

		advance_up
		glColor4f(1.0,0,0,1.0)
		plain_quad

		# 4th column
		glColor3i(0,0,0)
		advance_right
		glColor4d(1.0,0,0,1.0)
		plain_quad

		advance_down
		glColor4ub(0,max_ubyte,0,max_ubyte)
		plain_quad

		advance_down
		glColor4us(0,0,max_ushort,max_ushort)
		plain_quad

		advance_down
		glColor4ui(max_uint,max_uint,0,max_ubyte)
		plain_quad

		# 5th column
		glColor3i(0,0,0)
		advance_right
		glColor3bv([max_byte,max_byte,0])
		plain_quad

		advance_up
		glColor3sv([0,0,max_short])
		plain_quad
	
		advance_up
		glColor3iv([0,max_int,0])
		plain_quad

		advance_up
		glColor3fv([1.0,0.0,0.0])
		plain_quad

		# 6th column
		glColor3i(0,0,0)
		advance_right
		glColor3dv([1.0,0.0,0.0])
		plain_quad

		advance_down
		glColor3ubv([0,max_ubyte,0])
		plain_quad

		advance_down
		glColor3usv([0,0,max_ushort])
		plain_quad

		advance_down
		glColor3uiv([max_uint,max_uint,0])
		plain_quad

		# 7th column
		glColor3i(0,0,0)
		advance_right
		glColor4bv([max_byte,max_byte,0,max_byte])
		plain_quad

		advance_up
		glColor4sv([0,0,max_short,max_short])
		plain_quad

		advance_up
		glColor4iv([0,max_int,0,max_int])
		plain_quad

		advance_up
		glColor4fv([1.0,0.0,0.0,1.0])
		plain_quad

		# 8th column
		glColor3i(0,0,0)
		advance_right
		glColor4dv([1.0,0.0,0.0,1.0])
		plain_quad

		advance_down
		glColor4ubv([0,max_ubyte,0,max_ubyte])
		plain_quad

		advance_down
		glColor4usv([0,0,max_ushort,max_ushort])
		plain_quad

		advance_down
		glColor4uiv([max_uint,max_uint,0,max_uint])
		plain_quad
	end

	def destroy
	end
end

# tests glRasterPos* and glBitmap functions
class GLtest_2_rasterpos_bitmap
	FUNCTIONS_TESTED = [
"glBitmap",
"glRasterPos2d","glRasterPos2dv","glRasterPos2f","glRasterPos2fv",
"glRasterPos2i","glRasterPos2iv","glRasterPos2s","glRasterPos2sv",
"glRasterPos3d","glRasterPos3dv","glRasterPos3f","glRasterPos3fv",
"glRasterPos3i","glRasterPos3iv","glRasterPos3s","glRasterPos3sv",
"glRasterPos4d","glRasterPos4dv","glRasterPos4f","glRasterPos4fv",
"glRasterPos4i","glRasterPos4iv","glRasterPos4s","glRasterPos4sv"
	]

	def initialize
		@bitmap = redbook_fly_bitmap * 4
		projection_ortho_window
		@y_pos = 200
		@x_pos = 55
		@bmp_h = 32 * 4
		@bmp_w = 32
	end
	def draw_fly_bitmap
		glBitmap(32,32*4,0,0,0,0,@bitmap)
	end
	def loop
		clear_screen_and_depth_buffer

		glColor3f(1.0,1.0,1.0)

		# 2*

		glRasterPos2d(@x_pos,@y_pos)
		draw_fly_bitmap
		glRasterPos2dv([@x_pos,@y_pos+@bmp_h])
		draw_fly_bitmap

		glRasterPos2f(@x_pos+@bmp_w,@y_pos)
		draw_fly_bitmap
		glRasterPos2fv([@x_pos+@bmp_w,@y_pos+@bmp_h])
		draw_fly_bitmap

		glRasterPos2i(@x_pos+@bmp_w*2,@y_pos)
		draw_fly_bitmap
		glRasterPos2iv([@x_pos+@bmp_w*2,@y_pos+@bmp_h])
		draw_fly_bitmap

		glRasterPos2s(@x_pos+@bmp_w*3,@y_pos)
		draw_fly_bitmap
		glRasterPos2sv([@x_pos+@bmp_w*3,@y_pos+@bmp_h])
		draw_fly_bitmap

		# 3*
		glRasterPos3d(@x_pos+@bmp_w*4,@y_pos,0)
		draw_fly_bitmap
		glRasterPos3dv([@x_pos+@bmp_w*4,@y_pos+@bmp_h,0])
		draw_fly_bitmap

		glRasterPos3f(@x_pos+@bmp_w*5,@y_pos,0)
		draw_fly_bitmap
		glRasterPos3fv([@x_pos+@bmp_w*5,@y_pos+@bmp_h,0])
		draw_fly_bitmap

		glRasterPos3i(@x_pos+@bmp_w*6,@y_pos,0)
		draw_fly_bitmap
		glRasterPos3iv([@x_pos+@bmp_w*6,@y_pos+@bmp_h,0])
		draw_fly_bitmap

		glRasterPos3s(@x_pos+@bmp_w*7,@y_pos,0)
		draw_fly_bitmap
		glRasterPos3sv([@x_pos+@bmp_w*7,@y_pos+@bmp_h,0])
		draw_fly_bitmap

		# 4*
		glRasterPos4d(@x_pos+@bmp_w*8,@y_pos,0,1)
		draw_fly_bitmap
		glRasterPos4dv([@x_pos+@bmp_w*8,@y_pos+@bmp_h,0,1])
		draw_fly_bitmap

		glRasterPos4f(@x_pos+@bmp_w*9,@y_pos,0,1)
		draw_fly_bitmap
		glRasterPos4fv([@x_pos+@bmp_w*9,@y_pos+@bmp_h,0,1])
		draw_fly_bitmap

		glRasterPos4i(@x_pos+@bmp_w*10,@y_pos,0,1)
		draw_fly_bitmap
		glRasterPos4iv([@x_pos+@bmp_w*10,@y_pos+@bmp_h,0,1])
		draw_fly_bitmap

		glRasterPos4s(@x_pos+@bmp_w*11,@y_pos,0,1)
		draw_fly_bitmap
		glRasterPos4sv([@x_pos+@bmp_w*11,@y_pos+@bmp_h,0,1])
		draw_fly_bitmap
	end
	def destroy
	end
end

Test_Runner.new("GLtest_","base tests")
