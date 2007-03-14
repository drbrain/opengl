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
"glVertex4dv","glVertex4f","glVertex4fv","glVertex4i","glVertex4iv","glVertex4s","glVertex4sv",
"glClear","glLoadIdentity","glMatrixMode","glPopMatrix","glPushMatrix","glOrtho"
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

# tests display lists and basic matrix operations
class GLtest_3_displaylists_matrixops
	FUNCTIONS_TESTED = [
"glNewList","glEndList","glCallList","glCallLists","glDeleteLists","glGenLists","glListBase","glIsList",
"glScalef","glScaled","glRotatef","glRotated","glTranslated","glTranslatef"
	]
	def initialize
		projection_ortho_box(8)
		@listbase = glGenLists(3)
		@list1 = @listbase
		@list2 = @listbase + 1
		@list3 = @listbase + 2

		glNewList(@list1,GL_COMPILE)
		glBegin(GL_LINES)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd
		glEndList()

		glNewList(@list2,GL_COMPILE)
		glBegin(GL_LINE_STRIP)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glVertex2i(-1,-1)
		glEnd
		glEndList()

		glNewList(@list3,GL_COMPILE)
		glBegin(GL_LINE_STRIP)
		glVertex2f(-0.8,-0.8)
		glVertex2f( 0.8,-0.8)
		glVertex2f( 0.8, 0.8)
		glVertex2f(-0.8, 0.8)
		glVertex2f(-0.8,-0.8)
		glEnd
		glEndList()
	end
	def loop
		return if glIsList(@list1)==GL_FALSE
		return if glIsList(@list2)==GL_FALSE
		return if glIsList(@list3)==GL_FALSE
		clear_screen_and_depth_buffer
		reset_modelview

		# quad
		glScalef(0.8,0.8,0)
		glCallList(@list1)
		glRotatef(90,0,0,1)
		glCallList(@list1)

		glScaled(1.25,1.25,1.25)
		glCallList(@list1)
		glRotated(90,0,0,1)
		glCallList(@list1)

		reset_modelview
		glTranslatef(3,0,0)
		glListBase(0)
		glCallLists([@list3,@list2])
		glTranslated(-6,0,0)
		glListBase(1)
		glCallLists([@list3-1,@list2-1])
	end
	def destroy
		glDeleteLists(@listbase,3)
	end
end

# tests texturing operations
# top row - basic texturing
# middle row - texture-color interaction
# bottom row - automatic generation of texture coordinates
class GLtest_4_textureops
	FUNCTIONS_TESTED = [
"glPushAttrib","glPopAttrib","glBindTexture","glDeleteTextures","glGenTextures",
"glIsTexture","glDisable","glEnable","glIsEnabled","glTexParameterf",
"glTexParameterfv","glTexParameteri","glTexParameteriv","glTexImage1D",
"glTexImage2D","glGetTexParameterfv","glGetTexParameteriv","glGetTexEnvfv",
"glGetTexEnviv","glTexEnvf","glTexEnvfv","glTexEnvi","glTexEnviv","glTexGenf",
"glTexGenfv","glTexGeni","glTexGeniv","glTexGend","glTexGendv","glGetTexGendv",
"glGetTexGenfv","glGetTexGeniv","glTexCoord1d","glTexCoord1dv","glTexCoord1f",
"glTexCoord1fv","glTexCoord1i","glTexCoord1iv","glTexCoord1s","glTexCoord1sv",
"glTexCoord2d","glTexCoord2dv","glTexCoord2f","glTexCoord2fv","glTexCoord2i",
"glTexCoord2iv","glTexCoord2s","glTexCoord2sv","glTexCoord3d","glTexCoord3dv",
"glTexCoord3f","glTexCoord3fv","glTexCoord3i","glTexCoord3iv","glTexCoord3s",
"glTexCoord3sv","glTexCoord4d","glTexCoord4dv","glTexCoord4f","glTexCoord4fv",
"glTexCoord4i","glTexCoord4iv","glTexCoord4s","glTexCoord4sv"
	]

	def initialize
		size = 64
		projection_ortho_box(5)		
		bitmap = checker_texture_bitmap(size,8,[255,255,255],[0,0,0]) # checker texture
		bitmap_1D = (0..255).collect.pack("c*") # uncolored byte gradient 0..255

		@textures = glGenTextures(3)

		glPixelStorei(GL_UNPACK_ALIGNMENT,1)

		# 2D texture
		glEnable(GL_TEXTURE_2D)

		glBindTexture(GL_TEXTURE_2D,@textures[0])

		glTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, [GL_LINEAR] )
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP)
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP)

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap)

		glDisable(GL_TEXTURE_2D)

		# 1D textures
		glEnable(GL_TEXTURE_1D)

		glBindTexture(GL_TEXTURE_1D,@textures[1])
		glTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER, [GL_LINEAR] )
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap_1D)

		glBindTexture(GL_TEXTURE_1D,@textures[2])
		glTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER, [GL_LINEAR] )
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_BLUE, GL_UNSIGNED_BYTE, bitmap_1D)

		glDisable(GL_TEXTURE_1D)
	end
	
	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		return if glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER) != [GL_LINEAR]
		return if glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER) != [GL_LINEAR]
		return if glIsEnabled(GL_TEXTURE_2D) != GL_FALSE
		return if glIsTexture(@textures[0]) != GL_TRUE

		# color modulation off
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
		glColor3f(0.0,1.0,0.0)
		return if glGetTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE) != [GL_DECAL]
		return if glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE) != [GL_DECAL]

		glTranslatef(0.0,3.0,0.0)

		#2D - top center quad
		glEnable(GL_TEXTURE_2D)

		return if glIsEnabled(GL_TEXTURE_2D) != GL_TRUE

		glBindTexture(GL_TEXTURE_2D,@textures[0])
		
		glBegin(GL_QUADS)
		glTexCoord2f(0.0,0.0)	
		glVertex2i(-1,-1)
		glTexCoord2d(2.0,0.0)
		glVertex2i( 1,-1)
		glTexCoord2fv([2,2])
		glVertex2i( 1, 1)
		glTexCoord2dv([0,2])
		glVertex2i(-1, 1)
		glEnd()
		
		glDisable(GL_TEXTURE_2D)

		# 1D - top right quad
		glTranslatef(3.0,0.0,0.0)

		glEnable(GL_TEXTURE_1D)
		glBindTexture(GL_TEXTURE_1D,@textures[1])

		glBegin(GL_QUADS)
		glTexCoord1f(0.005)	
		glVertex2i(-1,-1)
		glTexCoord1d(1.0)	
		glVertex2i( 1,-1)
		glTexCoord1fv([1.0])	
		glVertex2i( 1, 1)
		glTexCoord1dv([0.005])	
		glVertex2i(-1, 1)
		glEnd()

		# 1D - top left quad
		glTranslatef(-6.0,0.0,0.0)

		glBindTexture(GL_TEXTURE_1D,@textures[2])

		glBegin(GL_QUADS)
		glTexCoord1i(0)
		glVertex2i(-1,-1)
		glTexCoord1s(1)
		glVertex2i( 1,-1)
		glTexCoord1iv([1])
		glVertex2i( 1, 1)
		glTexCoord1sv([0])
		glVertex2i(-1, 1)
		glEnd()

		glDisable(GL_TEXTURE_1D)

		# middle row
		reset_modelview
		glEnable(GL_TEXTURE_2D)
		glBindTexture(GL_TEXTURE_2D,@textures[0])

		# color modulation on
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE)
		glColor3f(0.0,1.0,0.0)

		# center quad
		glBegin(GL_QUADS)
		glTexCoord2i(0,0)
		glVertex2i(-1,-1)
		glTexCoord2s(1,0)
		glVertex2i( 1,-1)
		glTexCoord2iv([1,1])
		glVertex2i( 1, 1)
		glTexCoord2sv([0,1])
		glVertex2i(-1, 1)
		glEnd()

		# middle right quad
		glTranslatef(3.0,0.0,0.0)

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
		glTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, [GL_MODULATE])

		glColor3f(1.0,0.0,0.0)

		glBegin(GL_QUADS)
		glTexCoord3i(0,0,0)
		glVertex2i(-1,-1)
		glTexCoord3f(0.5,0.0,0.0)
		glVertex2i( 0,-1)
		glTexCoord3d(0.5,1.0,0.0)
		glVertex2i( 0, 1)
		glTexCoord3s(0,1,0)
		glVertex2i(-1, 1)

		glTexCoord3fv([0.5,0.0,0.0])
		glVertex2i( 0,-1)
		glTexCoord3iv([1,0,0])
		glVertex2i( 1,-1)
		glTexCoord3sv([1,1,0])
		glVertex2i( 1, 1)
		glTexCoord3dv([0.5,1.0,0.0])
		glVertex2i( 0, 1)
		glEnd()

		# middle left quad
		glTranslatef(-6.0,0.0,0.0)

		glColor3f(0.0,0.0,1.0)

		glBegin(GL_QUADS)
		glTexCoord4i(0,0,0,1)
		glVertex2i(-1,-1)
		glTexCoord4f(0.5,0.0,0.0,1.0)
		glVertex2i( 0,-1)
		glTexCoord4d(0.5,1.0,0.0,1.0)
		glVertex2i( 0, 1)
		glTexCoord4s(0,1,0,1)
		glVertex2i(-1, 1)

		glTexCoord4fv([0.5,0.0,0.0,1.0])
		glVertex2i( 0,-1)
		glTexCoord4iv([1,0,0,1])
		glVertex2i( 1,-1)
		glTexCoord4sv([1,1,0,1])
		glVertex2i( 1, 1)
		glTexCoord4dv([0.5,1.0,0.0,1.0])
		glVertex2i( 0, 1)
		glEnd()

		# color modulation off
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, [GL_DECAL])

		# bottom row
		reset_modelview		
		glTranslatef(0.0,-3.0,0.0)

		glEnable(GL_TEXTURE_GEN_S)
		glEnable(GL_TEXTURE_GEN_T)

		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR)
		glTexGeniv(GL_T,GL_TEXTURE_GEN_MODE, [GL_OBJECT_LINEAR])
		return if glGetTexGeniv(GL_T,GL_TEXTURE_GEN_MODE) != [GL_OBJECT_LINEAR]

		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd()

		# bottom right quad
		glTranslatef(3.0,0.0,0.0)

		glTexGenf(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR)
		glTexGenfv(GL_T,GL_TEXTURE_GEN_MODE, [GL_EYE_LINEAR])

		return if glGetTexGenfv(GL_T,GL_TEXTURE_GEN_MODE) != [GL_EYE_LINEAR]

		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd()

		# bottom left quad
		glTranslatef(-6.0,0.0,0.0)

		glTexGend(GL_S,GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR)
		glTexGendv(GL_T,GL_TEXTURE_GEN_MODE, [GL_OBJECT_LINEAR])
		return if glGetTexGendv(GL_T,GL_TEXTURE_GEN_MODE) != [GL_OBJECT_LINEAR]

		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd()

		glDisable(GL_TEXTURE_GEN_S)
		glDisable(GL_TEXTURE_GEN_T)

		glDisable(GL_TEXTURE_2D)
	end
	
	def destroy
		glDisable(GL_TEXTURE_1D)
		glDisable(GL_TEXTURE_2D)
		glDeleteTextures(@textures)
	end
end

# tests glRect and polygon/line/point operations
class GLtest_5_polygonops
	FUNCTIONS_TESTED = [
"glRectd","glRectdv","glRectf","glRectfv","glRecti","glRectiv","glRects","glRectsv","glCullFace",
"glFrontFace","glPolygonMode","glPolygonStipple","glGetPolygonStipple",
"glLineStipple","glLineWidth","glPointSize"
	]

	def initialize
		projection_ortho_box(6)
		@bitmap = redbook_fly_bitmap()
	end
	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		glEnable(GL_CULL_FACE)
		glCullFace(GL_FRONT)

		glFrontFace(GL_CW)

		reset_modelview

		glPolygonMode(GL_FRONT,GL_LINE)
		glPolygonMode(GL_BACK,GL_LINE)

		# top row
		glTranslatef(-4.5,4.5,0)
		glRectd(0,0,1,1)
		glTranslatef(2,0,0)
		glRectf(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRects(0,0,1,1)
		glTranslatef(2,0,0)

		glBegin(GL_QUADS)
			glVertex2i(0,0)		
			glVertex2i(1,0)		
			glVertex2i(1,1)		
			glVertex2i(0,1)		
		glEnd()

		glDisable(GL_CULL_FACE)

		glFrontFace(GL_CCW)

		glPolygonMode(GL_FRONT,GL_FILL)
		glPolygonMode(GL_BACK,GL_FILL)

		# 2nd row
		glTranslatef(-8,-2,0)
		glRectdv([0,0],[1,1])
		glTranslatef(2,0,0)
		glRectfv([0,0],[1,1])
		glTranslatef(2,0,0)
		glRectiv([0,0],[1,1])
		glTranslatef(2,0,0)
		glRectsv([0,0],[1,1])
		glTranslatef(2,0,0)

		glEnable(GL_CULL_FACE)

		glBegin(GL_QUADS)
			glVertex2i(0,0)		
			glVertex2i(0,1)		
			glVertex2i(1,1)	
			glVertex2i(1,0)		
		glEnd()

		glDisable(GL_CULL_FACE)

		# 3rd row

		glEnable(GL_POLYGON_STIPPLE)
		glPolygonStipple(@bitmap)
		return if glGetPolygonStipple() != @bitmap

		glTranslatef(-8,-2,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glDisable(GL_POLYGON_STIPPLE)

		# 4th row
		glPolygonMode(GL_FRONT,GL_LINE)

		glEnable(GL_LINE_STIPPLE)
		glLineStipple(6,0xAAAA)
		glLineWidth(7)
		glTranslatef(-8,-2,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)

		glLineWidth(1)
		glDisable(GL_LINE_STIPPLE)

		# 5th row
		glPolygonMode(GL_FRONT,GL_POINT)

		glPointSize(10)
	
		glTranslatef(-8,-2,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)
		glTranslatef(2,0,0)
		glRecti(0,0,1,1)

		glPointSize(1)
	end
	def destroy
		glPolygonMode(GL_BACK,GL_FILL)
		glPolygonMode(GL_FRONT,GL_FILL)
		glFrontFace(GL_CCW)
	end
end

Test_Runner.new("GLtest_","base tests")
