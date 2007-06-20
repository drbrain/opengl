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

class GLtest_6_textureops_2
	FUNCTIONS_TESTED = [
"glTexSubImage1D","glTexSubImage2D",
"glCopyTexImage1D","glCopyTexImage2D",
"glCopyTexSubImage1D","glCopyTexSubImage2D",
"glDrawPixels","glReadPixels", "glCopyPixels",
"glGetTexLevelParameterfv","glGetTexLevelParameteriv",
"glPrioritizeTextures","glAreTexturesResident",
"glGetTexImage",
	]

	def base_tex_params(target)
		glTexParameterf(target,GL_TEXTURE_MIN_FILTER, GL_LINEAR )
		glTexParameterf(target,GL_TEXTURE_MAG_FILTER, GL_LINEAR )
        glTexParameteri(target,GL_TEXTURE_WRAP_S, GL_CLAMP)
        glTexParameteri(target,GL_TEXTURE_WRAP_T, GL_CLAMP)
	end

	def initialize
		bitmap_1D = (0..255).collect.pack("c*") # uncolored byte gradient 0..255
		bitmap_2D = checker_texture_bitmap(64,8,[255,255,255],[0,0,0]) # checker texture
		bitmap_2D_small = checker_texture_bitmap(32,8,[0,0,255],[0,0,0]) # checker texture
		bitmap_random = random_rgb_texture(512)

		@textures = glGenTextures(7)

		glPixelStorei(GL_UNPACK_ALIGNMENT,1)

		# random background
		projection_ortho_window
		clear_screen_and_depth_buffer
		reset_modelview
		glRasterPos2i(0,0)
		glDrawPixels(512,512,GL_RGB,GL_UNSIGNED_BYTE,bitmap_random)
		projection_ortho_box(5)		

		# 1D
		glEnable(GL_TEXTURE_1D)

		# texture which half is replaced with subimage
		glBindTexture(GL_TEXTURE_1D,@textures[0])
		base_tex_params(GL_TEXTURE_1D)
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap_1D)
		glTexSubImage1D(GL_TEXTURE_1D, 0, 0, 128, GL_GREEN, GL_UNSIGNED_BYTE, bitmap_1D)

		return if glGetTexLevelParameteriv(GL_TEXTURE_1D,0,GL_TEXTURE_WIDTH) != [256]
		return if glGetTexLevelParameterfv(GL_TEXTURE_1D,0,GL_TEXTURE_WIDTH) != [256]

		# random texture
		glBindTexture(GL_TEXTURE_1D,@textures[1])
		base_tex_params(GL_TEXTURE_1D)
		glCopyTexImage1D(GL_TEXTURE_1D,0,GL_RGB,0,0,256,0)

		# random subimage
		glBindTexture(GL_TEXTURE_1D,@textures[2])
		base_tex_params(GL_TEXTURE_1D)
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap_1D)
		glCopyTexSubImage1D(GL_TEXTURE_1D,0,0,0,0,128)
		
		# </1D>
		glDisable(GL_TEXTURE_1D)

		# 2D
		glEnable(GL_TEXTURE_2D)

		# texture which half is replaced with subimage
		glBindTexture(GL_TEXTURE_2D,@textures[3])
		base_tex_params(GL_TEXTURE_2D)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,64, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_2D)
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0,32, 32,32, GL_RGB, GL_UNSIGNED_BYTE, bitmap_2D_small)
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, 32,32, GL_RGB, GL_UNSIGNED_BYTE, bitmap_2D_small)

		# random texture
		glBindTexture(GL_TEXTURE_2D,@textures[4])
		base_tex_params(GL_TEXTURE_2D)
		glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,64,64,0)

		# random subimage
		glBindTexture(GL_TEXTURE_2D,@textures[5])
		base_tex_params(GL_TEXTURE_2D)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,64, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_2D)
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0,0, 0,0, 32,32)
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0,32,32,32, 32,32)

		# image for getteximage
		glBindTexture(GL_TEXTURE_2D,@textures[6])
		base_tex_params(GL_TEXTURE_2D)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,64, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_2D)

		x = glGetTexImage(GL_TEXTURE_2D,0, GL_RGBA, GL_UNSIGNED_BYTE)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,64, 0, GL_RGB, GL_UNSIGNED_BYTE, x)

		glPrioritizeTextures(@textures,[0.0,1.0,0.0,1.0,0.0,1.0,1.0])

		# </2D>
		glDisable(GL_TEXTURE_2D)
	end
	def draw_quad
		glBegin(GL_QUADS)
		glTexCoord2i(0,0)
		glVertex2i(-1,-1)
		glTexCoord2i(1,0)
		glVertex2i( 1,-1)
		glTexCoord2i(1,1)
		glVertex2i( 1, 1)
		glTexCoord2i(0,1)
		glVertex2i(-1, 1)
		glEnd()
	end
	def loop	
		projection_ortho_box(5)

		clear_screen_and_depth_buffer

		res = glAreTexturesResident(@textures) # residences are implementation defined
		return if res.size != @textures.size

		# top row
		reset_modelview
		glEnable(GL_TEXTURE_1D)
		glBindTexture(GL_TEXTURE_1D,@textures[0])
		glTranslatef(-3,3,0)		
		draw_quad

		return if glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_PRIORITY) != [0.0]

		glBindTexture(GL_TEXTURE_1D,@textures[1])
		glTranslatef(3,0,0)
		draw_quad

		return if glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_PRIORITY) != [1.0]

		glBindTexture(GL_TEXTURE_1D,@textures[2])
		glTranslatef(3,0,0)
		draw_quad

		return if glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_PRIORITY) != [0.0]

		glDisable(GL_TEXTURE_1D)

		# middle row
		reset_modelview

		glEnable(GL_TEXTURE_2D)

		glBindTexture(GL_TEXTURE_2D,@textures[3])
		glTranslatef(-3,0,0)
		draw_quad

		glBindTexture(GL_TEXTURE_2D,@textures[4])
		glTranslatef(3,0,0)	
		draw_quad

		glBindTexture(GL_TEXTURE_2D,@textures[5])
		glTranslatef(3,0,0)	
		draw_quad

		# bottom row
		reset_modelview
		glBindTexture(GL_TEXTURE_2D,@textures[6])
		glTranslatef(0,-3,0)
		draw_quad

		reset_modelview

		glDisable(GL_TEXTURE_2D)

		x = glReadPixels(0,0,512,512,GL_RGB,GL_UNSIGNED_BYTE)

		clear_screen_and_depth_buffer
		projection_ortho_window
		glRasterPos2i(0,0)

		glDrawPixels(512,512,GL_RGB,GL_UNSIGNED_BYTE,x)

		glRasterPos2i(38,40)
		glCopyPixels(192,40,128,128,GL_COLOR)

		glRasterPos2i(344,40)
		glCopyPixels(192,40,128,128,GL_COLOR)
	end
	def destroy
		glDeleteTextures(@textures)	
	end
end

class GLtest_7_light_material
	FUNCTIONS_TESTED = [
"glLightfv","glLightiv","glLightf","glLighti","glGetLightfv","glGetLightiv",
"glMaterialfv","glMaterialiv","glMaterialf","glMateriali","glGetMaterialfv","glGetMaterialiv",
"glNormal3d","glNormal3dv","glNormal3f","glNormal3fv","glNormal3i","glNormal3iv","glNormal3s",
"glNormal3sv","glNormal3b","glNormal3bv",
"glColorMaterial","glLightModelfv","glLightModeliv","glLightModelf","glLightModeli"
	]

	def initialize
		projection_ortho_box(5)

		glEnable(GL_LIGHTING)
		# red light
		glLightfv(GL_LIGHT0,GL_AMBIENT, [0.2,0.2,0.2,1.0])
		glLightiv(GL_LIGHT0,GL_DIFFUSE, [2**31-1,0,0,2**31-1])
		glLightfv(GL_LIGHT0,GL_POSITION, [0.0,0.0,5.0,1.0])
		# green light	
		glLightfv(GL_LIGHT1,GL_AMBIENT, [0.2,0.2,0.2,1.0])
		glLightfv(GL_LIGHT1,GL_DIFFUSE, [0.0,1.0,0.0,1.0])
		glLightfv(GL_LIGHT1,GL_POSITION, [0.0,0.0,5.0,1.0])
		# blue light
		glLightfv(GL_LIGHT2,GL_AMBIENT, [0.2,0.2,0.2,1.0])
		glLightfv(GL_LIGHT2,GL_DIFFUSE, [0.0,0.0,1.0,1.0])
		glLightfv(GL_LIGHT2,GL_POSITION, [0.0,0.0,5.0,1.0])
	end

	def draw_quad
		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i( 1,-1)
		glVertex2i( 1, 1)
		glVertex2i(-1, 1)
		glEnd()
	end
	def draw_quad_rev
		glBegin(GL_QUADS)
		glVertex2i(-1,-1)
		glVertex2i(-1, 1)
		glVertex2i( 1, 1)
		glVertex2i( 1,-1)
		glEnd()
	end
	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		glMaterialfv(GL_FRONT,GL_AMBIENT,[0.3,0.3,0.3,1.0])

		glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,45.0)
		return if glGetLightfv(GL_LIGHT0,GL_SPOT_CUTOFF) != [45.0]
		glLighti(GL_LIGHT0,GL_SPOT_CUTOFF,90)
		return if glGetLightiv(GL_LIGHT0,GL_SPOT_CUTOFF) != [90]

		glMaterialf(GL_FRONT,GL_SHININESS,96)
		return if glGetMaterialfv(GL_FRONT,GL_SHININESS) != [96.0]
		glMateriali(GL_FRONT,GL_SHININESS,64)
		return if glGetMaterialiv(GL_FRONT,GL_SHININESS) != [64]

		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1)
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,1.0)
		
		glNormal3b(0,0,-127)
		# top row
		imax = 2**31-1
		glMaterialiv(GL_FRONT,GL_DIFFUSE,[imax,imax,imax,imax])
		glTranslatef(-3,3,0)
		glEnable(GL_LIGHT0)
		glNormal3f(0,0,1)
		draw_quad
		glNormal3f(0,0,-1)
		glDisable(GL_LIGHT0)
	
		glTranslatef(3,0,0)
		glEnable(GL_LIGHT1)
		glNormal3fv([0,0,1])
		draw_quad
		glNormal3fv([0,0,-1])
		glDisable(GL_LIGHT1)

		glTranslatef(3,0,0)
		glEnable(GL_LIGHT2)
		glNormal3d(0,0,-1)
		draw_quad_rev
		glNormal3d(0,0,-1)
		glDisable(GL_LIGHT2)

		# middle row
		reset_modelview
		glMaterialfv(GL_FRONT,GL_DIFFUSE,[0.4,0.4,0.4,1.0])
		glTranslatef(-3,0,0)
		glEnable(GL_LIGHT0)
		glNormal3dv([0,0,1])
		draw_quad
		glNormal3dv([0,0,-1])
		glDisable(GL_LIGHT0)

		glLightModeliv(GL_LIGHT_MODEL_AMBIENT,[2**31-1,2**31-1,2**31-1,2**31-1])
	
		glTranslatef(3,0,0)
		glEnable(GL_LIGHT1)
		glNormal3i(0,0,2**30)
		draw_quad
		glNormal3i(0,0,-2**30)
		glDisable(GL_LIGHT1)

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,[0.2,0.2,0.2,1.0])

		glTranslatef(3,0,0)
		glEnable(GL_LIGHT2)
		glNormal3iv([0,0,2**30])
		draw_quad
		glNormal3iv([0,0,-2**30])
		glDisable(GL_LIGHT2)

		glEnable(GL_COLOR_MATERIAL)

		glColor(1.0,1.0,1.0)
		glColorMaterial(GL_FRONT,GL_DIFFUSE)
		# bottom row
		reset_modelview
		glTranslatef(-3,-3,0)
		glEnable(GL_LIGHT0)
		glNormal3s(0,0,2**15-1)
		draw_quad
		glNormal3s(0,0,-2**15-1)
		glDisable(GL_LIGHT0)
	
		glTranslatef(3,0,0)
		glEnable(GL_LIGHT1)
		glNormal3sv([0,0,2**15-1])
		draw_quad
		glNormal3sv([0,0,-2**15-1])
		glDisable(GL_LIGHT1)

		glTranslatef(3,0,0)
		glEnable(GL_LIGHT2)
		glNormal3bv([0,0,127])
		draw_quad
		glNormal3bv([0,0,-127])
		glDisable(GL_LIGHT2)

		glDisable(GL_COLOR_MATERIAL)

	end

	def destroy
		glDisable(GL_LIGHTING)
		glDisable(GL_COLOR_MATERIAL)
	end
end

class GLtest_8_evaluators
	FUNCTIONS_TESTED = [
"glMap1f","glMap1d",
"glEvalCoord1f","glEvalCoord1d","glEvalCoord1dv","glEvalCoord1fv",
"glGetMapdv","glGetMapfv","glGetMapiv","glMap2f","glMap2d",
"glEvalCoord2d","glEvalCoord2dv","glEvalCoord2f","glEvalCoord2fv",
"glMapGrid1d","glMapGrid1f","glEvalMesh1","glEvalMesh2",
"glMapGrid2d","glMapGrid2f","glEvalPoint1","glEvalPoint2"
	]
	def initialize
		projection_ortho_box(1.1)		

		@control_points = [
			0.25, 0.5, 0.0,
			1.0, 1.0, 0.0,
			0.0, 1.0, 0.0,
			0.75, 0.5, 0.0
		]
		
		@control_points_2d = [
			-0.5, -0.5, 0.0,
			-0.25, -0.25, 0.0,
			0.25, -0.25, 0.0,
			0.5, -0.5, 0.0,

			-0.25, -0.25, 0.0,
			-0.25, -0.25, 0.0,
			0.25, -0.25, 0.0,
			0.25, -0.25, 0.0,

			-0.25, 0.25, 0.0,
			-0.25, 0.25, 0.0,
			0.25, 0.25, 0.0,
			0.25, 0.25, 0.0,

			-0.5, 0.5, 0.0,
			-0.25, 0.25, 0.0,
			0.25, 0.25, 0.0,
			0.5, 0.5, 0.0
		]
	end
	
	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		# red loop
		glEnable(GL_MAP1_VERTEX_3);

		glTranslatef(-1.25,-0.25,0.0)
		glColor3f(1.0,0.0,0.0)

		glMap1f(GL_MAP1_VERTEX_3, 1.0, 100.0, 3, 4, @control_points)

		return unless glGetMapfv(GL_MAP1_VERTEX_3, GL_COEFF) == @control_points
		return unless glGetMapdv(GL_MAP1_VERTEX_3, GL_COEFF) == @control_points
		return unless glGetMapiv(GL_MAP1_VERTEX_3,GL_DOMAIN) == [1,100]

		glBegin(GL_LINE_STRIP)
		1.upto(50) { |i| glEvalCoord1f(i) }
		51.upto(100) { |i| glEvalCoord1d(i) }
		glEnd()

		# green loop
		glTranslatef(0.5,0.0,0.0)
		glColor3f(0.0,1.0,0.0)

		glMap1d(GL_MAP1_VERTEX_3, 1.0, 200.0, 3, 4, @control_points)

		glBegin(GL_LINE_STRIP)
		0.upto(25) { |i| glEvalPoint1(i)}
		50.upto(150) { |i| glEvalCoord1fv( [i] ) }
		151.upto(200) { |i| glEvalCoord1dv( [i] ) }
		glEnd()

		# blue loop
		glTranslatef(0.5,0.0,0.0)
		glColor3f(0.0,0.0,1.0)

		glMapGrid1f(100, 1.0, 200.0);
		glEvalMesh1(GL_LINE, 0.0, 100);

		# white loop
		glTranslatef(0.5,0.0,0.0)
		glColor3f(1.0,1.0,1.0)

		glMapGrid1d(100, 1.0, 200.0);
		glEvalMesh1(GL_LINE, 0.0, 100);


		glDisable(GL_MAP1_VERTEX_3)

		# red points
		glEnable(GL_MAP2_VERTEX_3)

		glTranslatef(-1.0,0.0,0.0)
		glScalef(0.5,0.5,0.5)
		glColor3f(1.0,0.0,0.0)

    glMap2f(GL_MAP2_VERTEX_3, 0, 10, 3, 4,
            0, 10, 12, 4, @control_points_2d)

		glBegin(GL_POINTS)
		1.upto(9) do |x|
			1.upto(3) do |y| glEvalPoint2(x,y) end
			4.upto(6) do |y| glEvalCoord2f(x,y) end
			7.upto(9) do |y| glEvalCoord2fv([x,y]) end
		end
    glEnd()

		# green points
		glTranslatef(1,0.0,0.0)
		glColor3f(0.0,1.0,0.0)

    glMap2d(GL_MAP2_VERTEX_3, 0, 10, 3, 4,
            0, 10, 12, 4, @control_points_2d)

		glBegin(GL_POINTS)
		1.upto(9) do |x|
			1.upto(4) do |y| glEvalCoord2d(x, y) end
			5.upto(9) do |y| glEvalCoord2dv([x, y]) end
		end
    glEnd()

		# blue points
		glTranslatef(1,0.0,0.0)
		glColor3f(0.0,0.0,1.0)

    glMapGrid2f(10, 0.0, 10.0, 10, 0.0, 10.0)
    glEvalMesh2(GL_POINT, 1, 9, 1, 9)

		# white points
		glTranslatef(1,0.0,0.0)
		glColor3f(1.0,1.0,1.0)

    glMapGrid2d(10, 0.0, 10.0, 10, 0.0, 10.0)
    glEvalMesh2(GL_POINT, 1, 9, 1, 9)

		glDisable(GL_MAP2_VERTEX_3)
	end

	def destroy
	end
end

class GLtest_9_fog
	FUNCTIONS_TESTED = [
"glFogfv","glFogiv","glFogf","glFogi"
	]

	def initialize
		projection_ortho_box(2)
	end

	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		glEnable(GL_FOG)

		glFogfv(GL_FOG_COLOR,[0.0,0.0,1.0,0.0])
		glFogiv(GL_FOG_MODE,[GL_LINEAR])
		glFogf(GL_FOG_START,-1)
		glFogi(GL_FOG_END,2)

		# red quad
		glColor3f(1.0,0.0,0.0)
		glBegin(GL_QUADS)
		glVertex3f(-1.0,-1.0,0.0)
		glVertex3f(1.0,-1.0,0.0)
		glVertex3f(1.0,1.0,-1.0)
		glVertex3f(-1.0,1.0,-1.0)
		glEnd()

		glDisable(GL_FOG)
	end

	def destroy
	end
end

class GLtest__10_arrays
	FUNCTIONS_TESTED = [
"glVertexPointer","glColorPointer","glEdgeFlagPointer","glTexCoordPointer","glNormalPointer",
"glGetPointerv",
"glDrawArrays","glArrayElement","glDrawElements","glInterleavedArrays"
	]

	def initialize
		projection_ortho_box(5)

		@vertex_data = [ -1.0,-1.0,0.0,
									   1.0,-1.0,0.0,
									   1.0,1.0,0.0,
									  -1.0,1.0,0.0 ]

		@vertex_data_2 = [ -1.0,-1.0,0.0,
									   -1.0,1.0,0.0,
									   1.0,1.0,0.0,
									  1.0,-1.0,0.0 ]

		@color_data = [ 1.0,0.0,0.0,0.0,
									 1.0,0.0,0.0,0.0,
									 0.0,0.0,1.0,0.0,
									 0.0,0.0,1.0,0.0 ]

		@normal_data = [ 0.0,0.0,-1.0,
										0.0,0.0,-1.0,
										0.0,0.0,-1.0,
										0.0,0.0,-1.0 ]
		
		@texcoord_data = [0.0,0.0,
										 0.0,1.0,
										 1.0,1.0,
										 1.0,0.0]

		@edgeflag_data = [ 0,1,0,1 ]

		# texture setup
		size = 64
		bitmap = checker_texture_bitmap(size,8,[255,255,255],[0,0,0]) # checker texture
		@textures = glGenTextures(1)

		glEnable(GL_TEXTURE_2D)
		glBindTexture(GL_TEXTURE_2D,@textures[0])
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap)
		glDisable(GL_TEXTURE_2D)
	end

	def loop
		clear_screen_and_depth_buffer
		reset_modelview

		glVertexPointer(3,GL_FLOAT,0,@vertex_data.pack("f*"))
		glColorPointer(4,GL_FLOAT,0,@color_data.pack("f*"))
		glEdgeFlagPointer(0,@edgeflag_data.pack("c*"))
		glTexCoordPointer(2,GL_FLOAT,0,@texcoord_data.pack("f*"))

		d = glGetPointerv(GL_VERTEX_ARRAY_POINTER)
    return unless d.unpack("f*") == @vertex_data
                    
		glEnableClientState(GL_VERTEX_ARRAY)

		# first row
		glTranslatef(-3,3,0)
		glDrawArrays(GL_QUADS,0,4)

		glEnableClientState(GL_COLOR_ARRAY)
		glTranslatef(3,0,0)
		glDrawArrays(GL_QUADS,0,4)
		glDisableClientState(GL_COLOR_ARRAY)

		glColor3f(1.0,1.0,1.0)

		glEnableClientState(GL_EDGE_FLAG_ARRAY)
		glPolygonMode(GL_FRONT,GL_LINE)
		glTranslatef(3,0,0)
		glDrawArrays(GL_POLYGON,0,4)
		glPolygonMode(GL_FRONT,GL_FILL)
		glDisableClientState(GL_EDGE_FLAG_ARRAY)

		# second row
		glTranslatef(-6,-3,0)
		glBegin(GL_QUADS)
		0.upto(3) {|i| glArrayElement(i) }
		glEnd()

		glEnable(GL_TEXTURE_2D)
		glEnableClientState(GL_TEXTURE_COORD_ARRAY)
		glTranslatef(3,0,0)
		glDrawArrays(GL_POLYGON,0,4)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY)
		glDisable(GL_TEXTURE_2D)

		glPolygonMode(GL_FRONT,GL_LINE)
		glTranslatef(3,0,0)
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, [0,1,3,2].pack("c*") )


		# third row
		glInterleavedArrays(GL_V3F,0, @vertex_data_2.pack("f*"))

		glTranslatef(-6,-3,0)
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, [0,1,3,2].pack("c*") )

		glPolygonMode(GL_FRONT,GL_FILL)

		glNormalPointer(GL_FLOAT,0,@normal_data.pack("f*"))

		glEnable(GL_LIGHTING)
		glEnableClientState(GL_NORMAL_ARRAY)
		glEnable(GL_LIGHT0)
		glLightfv(GL_LIGHT0,GL_AMBIENT, [0.2,0.2,0.2,1.0])
		glLightfv(GL_LIGHT0,GL_DIFFUSE, [1.0,0,0,1.0])
		glLightfv(GL_LIGHT0,GL_POSITION, [0.0,0.0,5.0,1.0])

		glTranslatef(3,0,0)
		glDrawArrays(GL_QUADS,0,4)

		glDisable(GL_LIGHT0)
		glDisable(GL_LIGHTING)
		glDisableClientState(GL_NORMAL_ARRAY)

		glEnableClientState(GL_EDGE_FLAG_ARRAY)
		glPolygonMode(GL_BACK,GL_LINE)
		glTranslatef(3,0,0)
		glDrawArrays(GL_POLYGON,0,4)
		glPolygonMode(GL_BACK,GL_FILL)
		glDisableClientState(GL_EDGE_FLAG_ARRAY)

		glDisableClientState(GL_VERTEX_ARRAY)
	end

	def destroy
		glDisable(GL_CULL_FACE)
		glDeleteTextures(@textures)
	end
end

class GLtest__11_accum
	FUNCTIONS_TESTED = [
"glAccum"
	]
	def initialize
		projection_ortho_box(4)
	end

	def draw_quad
		glBegin(GL_QUADS)
		glTexCoord2i(0,0)
		glVertex2i(-1,-1)
		glTexCoord2i(1,0)
		glVertex2i( 1,-1)
		glTexCoord2i(1,1)
		glVertex2i( 1, 1)
		glTexCoord2i(0,1)
		glVertex2i(-1, 1)
		glEnd()
	end
	
	def loop
		glClear(GL_ACCUM_BUFFER_BIT)

		# left
		clear_screen_and_depth_buffer
		reset_modelview
		glTranslatef(-2,0,0)
		draw_quad
		
		glAccum(GL_ACCUM,0.5)

		# right
		clear_screen_and_depth_buffer
		reset_modelview
		glTranslatef(2,0,0)
		draw_quad
		glAccum(GL_ACCUM,0.5)

		glAccum(GL_RETURN,1.0)
	end

	def destroy
	end
end

srand(1234)
Test_Runner.new("GLtest_","base tests")
