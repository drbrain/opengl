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

class Test_21 < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_gluniformmatrix21
		return if not supported?(2.1)

		vertex_shader_source = "#version 120\n uniform mat2x3 testmat23; uniform mat3x2 testmat32; uniform mat2x4 testmat24; uniform mat4x2 testmat42; uniform mat3x4 testmat34; uniform mat4x3 testmat43; void main() { gl_Position = gl_Vertex * testmat23[0].x * testmat32[0].x * testmat24[0].x * testmat42[0].x * testmat34[0].x * testmat43[0].x;}"

		program = glCreateProgram()
		vs = glCreateShader(GL_VERTEX_SHADER)

		glShaderSource(vs,vertex_shader_source)
		glCompileShader(vs)

		assert_equal(glGetShaderiv(vs,GL_COMPILE_STATUS),GL_TRUE)
		glAttachShader(program,vs)
	
		glLinkProgram(program)	
		assert_equal(glGetProgramiv(program,GL_LINK_STATUS),GL_TRUE)
		glUseProgram(program)
		
		assert((tm23l = glGetUniformLocation(program,"testmat23"))>=0)
		assert((tm32l = glGetUniformLocation(program,"testmat32"))>=0)
		assert((tm24l = glGetUniformLocation(program,"testmat24"))>=0)
		assert((tm42l = glGetUniformLocation(program,"testmat42"))>=0)
		assert((tm34l = glGetUniformLocation(program,"testmat34"))>=0)
		assert((tm43l = glGetUniformLocation(program,"testmat43"))>=0)

		glUniformMatrix2x3fv(tm23l, GL_FALSE, [0,1, 1,0, 0,1])
		assert_equal(glGetUniformfv(program,tm23l),[0,1, 1,0, 0,1])
		glUniformMatrix3x2fv(tm32l, GL_FALSE, [1,0, 0,1, 1,0])
		assert_equal(glGetUniformfv(program,tm32l),[1,0, 0,1, 1,0])

		glUniformMatrix2x4fv(tm24l, GL_FALSE, [0,1, 1,0, 0,1, 1,0])
		assert_equal(glGetUniformfv(program,tm24l),[0,1, 1,0, 0,1, 1,0])
		glUniformMatrix4x2fv(tm42l, GL_FALSE, [1,0, 0,1, 1,0, 0,1])
		assert_equal(glGetUniformfv(program,tm42l),[1,0, 0,1, 1,0, 0,1])

		glUniformMatrix3x4fv(tm34l, GL_FALSE, [0,1,1, 1,0,1, 0,1,1, 1,0,1])
		assert_equal(glGetUniformfv(program,tm34l),[0,1,1, 1,0,1, 0,1,1, 1,0,1])
		glUniformMatrix4x3fv(tm43l, GL_FALSE, [1,0,0, 0,1,0, 1,0,0, 0,1,0])
		assert_equal(glGetUniformfv(program,tm43l),[1,0,0, 0,1,0, 1,0,0, 0,1,0])

		# 2
		m = Matrix.rows([[0,1],[1,0],[0,1]])
		glUniformMatrix2x3fv(tm23l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm23l),[0,1, 1,0, 0,1])
		m = Matrix.rows([[0,1,1],[0,0,1]])
		glUniformMatrix3x2fv(tm32l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm32l),[0,1,1, 0,0,1])

		m = Matrix.rows([[0,1],[1,0],[0,1],[1,0]])
		glUniformMatrix2x4fv(tm24l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm24l),[0,1, 1,0, 0,1, 1,0])
		m = Matrix.rows([[0,1,1,1],[0,0,1,1]])
		glUniformMatrix4x2fv(tm42l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm42l),[0,1,1,1, 0,0,1,1])

		m = Matrix.rows([[0,1,0],[1,0,1],[0,1,0],[1,0,1]])
		glUniformMatrix3x4fv(tm34l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm34l),[0,1,0, 1,0,1, 0,1,0, 1,0,1])

		m = Matrix.rows([[0,1,1,1],[0,0,1,1],[1,1,0,0]])
		glUniformMatrix4x3fv(tm43l, GL_FALSE, m)
		assert_equal(glGetUniformfv(program,tm43l),[0,1,1,1, 0,0,1,1, 1,1,0,0])

		# 3
		assert_raise ArgumentError do glUniformMatrix2x3fv(tm23l, GL_FALSE, [1,2,3,4]) end
		assert_raise ArgumentError do glUniformMatrix3x2fv(tm32l, GL_FALSE, [1,2,3,4]) end
		assert_raise ArgumentError do glUniformMatrix2x4fv(tm24l, GL_FALSE, [1,2,3,4]) end
		assert_raise ArgumentError do glUniformMatrix4x2fv(tm42l, GL_FALSE, [1,2,3,4]) end
		assert_raise ArgumentError do glUniformMatrix3x4fv(tm34l, GL_FALSE, [1,2,3,4]) end
		assert_raise ArgumentError do glUniformMatrix4x3fv(tm43l, GL_FALSE, [1,2,3,4]) end
	end

	def test_pixelunpack_bitmap
		return if not supported?(2.1)
		glOrtho(0,$window_size,0,$window_size,0,-1)

		bitmap = [ 0x55 ] * 8 # 64 bits (8x8 bitmap), stipple pattern
		glPixelStorei(GL_PACK_ALIGNMENT,1)
		glPixelStorei(GL_UNPACK_ALIGNMENT,1)

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,8,bitmap.pack("C*"),GL_DYNAMIC_DRAW)

		glBitmap(8,8,0,0,0,0,0)
		data = glReadPixels(0,0,8,8,GL_RED,GL_UNSIGNED_BYTE)
		assert_equal(data.unpack("C*"),[0,255] * 32)
	
		glDeleteBuffers(buffers)
	end

	def test_pixelunpack_color_convolution
		return if not supported?(2.1)

		ct = ([0]*3+[1]*3+[0]*3+[1]*3).pack("f*")
		ct2 = ([1]*3+[0]*3+[1]*3+[0]*3).pack("f*")

		buffers = glGenBuffers(2)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,4*3*4,ct,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,4*3*4,ct2,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glColorTable(GL_COLOR_TABLE,GL_RGB8,4,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetColorTable(GL_COLOR_TABLE,GL_RGB,GL_FLOAT),ct)
		glConvolutionFilter1D(GL_CONVOLUTION_1D, GL_RGB8, 4, GL_RGB, GL_FLOAT,0)
		assert_equal(glGetConvolutionFilter(GL_CONVOLUTION_1D, GL_RGB, GL_FLOAT),ct)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glColorSubTable(GL_COLOR_TABLE,0,4,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetColorTable(GL_COLOR_TABLE,GL_RGB,GL_FLOAT),ct2)
		glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_RGB8, 2,2, GL_RGB, GL_FLOAT,0)
		assert_equal(glGetConvolutionFilter(GL_CONVOLUTION_2D, GL_RGB, GL_FLOAT),ct2)

		glDeleteBuffers(buffers)
	end

	def test_pixelunpack_separable
		return if not supported?(2.1)

		sf_a = ([0]*3+[1]*3).pack("f*")
		sf_b = ([1]*3+[0]*3).pack("f*")

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,2*3*4 *2,sf_a + sf_b,GL_DYNAMIC_DRAW)
		
		glSeparableFilter2D(GL_SEPARABLE_2D,GL_RGB8, 2,2,GL_RGB,GL_FLOAT,0,2*3*4)
		assert_equal(glGetSeparableFilter(GL_SEPARABLE_2D,GL_RGB,GL_FLOAT), [sf_a,sf_b])

		glDeleteBuffers(buffers)
	end

	def test_pixelunpack_drawpixels
		return if not supported?(2.1)

		glClearColor(0,0,0,0)
		glClear(GL_COLOR_BUFFER_BIT)

		image = ([1.0] * 3 * 16).pack("f*")

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,3*16*4,image,GL_DYNAMIC_DRAW)
	
		glDrawPixels(4,4,GL_RGB,GL_FLOAT,0)

		data = glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT)
		assert_equal(data,image)

		glDeleteBuffers(buffers)
	end

	def test_pixelunpack_polygonstipple
		return if not supported?(2.1)

		stipple = ([0x12] * 128).pack("c*")
		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,128,stipple,GL_DYNAMIC_DRAW)

		glPolygonStipple(0)
		assert_equal(glGetPolygonStipple(),stipple)
		glDeleteBuffers(buffers)
	end


	def test_pixelunpack_texturecompression
		return if not supported?(2.1)
		return if not supported?("GL_EXT_texture_compression_s3tc")

		# S3TC/DXT5 compressed 2x2 pixels stipple patterns [w,b,b,w] and [b,w,w,b]
		image_1 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x01,0x54,0x5C,0x5C].pack("C*")
		image_2 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x54,0x01,0x0D,0x0D].pack("C*")

		textures = glGenTextures(3)
		glBindTexture(GL_TEXTURE_1D,textures[0])
		glBindTexture(GL_TEXTURE_2D,textures[1])
		glBindTexture(GL_TEXTURE_3D,textures[2])

		buffers = glGenBuffers(2)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,16,image_1,GL_DYNAMIC_DRAW)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,16,image_2,GL_DYNAMIC_DRAW)

		# Note: 1D and 3D compressed textures are not supported by S3TC/DXTn, and usually not supported at all

		# 1D
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		begin
			glCompressedTexImage1D(GL_TEXTURE_1D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,4,0,16,0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_1D,0), image_1)
		rescue Gl::Error => err
			assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
		end

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		begin
			glCompressedTexSubImage1D(GL_TEXTURE_1D,0,0,4,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_1D,0), image_2)
		rescue Gl::Error => err
			assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
		end
		
		# 2D
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glCompressedTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,0,16,0)
		assert_equal(glGetCompressedTexImage(GL_TEXTURE_2D,0), image_1)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glCompressedTexSubImage2D(GL_TEXTURE_2D,0,0,0,2,2,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,0)
		assert_equal(glGetCompressedTexImage(GL_TEXTURE_2D,0), image_2)
		
		# 3D
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		begin
			glCompressedTexImage3D(GL_TEXTURE_3D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,1,0,16,0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_3D,0), image_1)
		rescue Gl::Error => err
			assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
		end
		
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		begin
			glCompressedTexSubImage3D(GL_TEXTURE_3D,0, 0,0,0, 2,2,1, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, 0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_3D,0), image_2)
		rescue Gl::Error => err
			assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
		end

		glDeleteBuffers(buffers)
		glDeleteTextures(textures)
	end

	def test_pixelunpack_texture
		return if not supported?(2.1)

		textures = glGenTextures(3)
		image_1 = ([0,0,0,1,1,1] * 8).pack("f*") # 16 RGB pixels
		image_2 = ([1,1,1,0,0,0] * 8).pack("f*") # 16 RGB pixels

		buffers = glGenBuffers(2)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,6*8*4,image_1,GL_DYNAMIC_DRAW)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,6*8*4,image_2,GL_DYNAMIC_DRAW)

		# 3D
		glBindTexture(GL_TEXTURE_3D,textures[0])

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glTexImage3D(GL_TEXTURE_3D,0,GL_RGB8,2,2,4,0,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetTexImage(GL_TEXTURE_3D,0,GL_RGB,GL_FLOAT),image_1)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glTexSubImage3D(GL_TEXTURE_3D,0, 0,0,0, 2,2,4,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetTexImage(GL_TEXTURE_3D,0,GL_RGB,GL_FLOAT),image_2)

		# 2D
		glBindTexture(GL_TEXTURE_2D,textures[1])

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8, 4, 4, 0, GL_RGB, GL_FLOAT, 0)
		assert_equal(glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT), image_1)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glTexSubImage2D(GL_TEXTURE_2D,0, 0,0, 4,4,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT),image_2)
	
		# 1D
		glBindTexture(GL_TEXTURE_1D,textures[2])

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])

		glTexImage1D(GL_TEXTURE_1D,0,GL_RGB8, 16, 0, GL_RGB, GL_FLOAT, 0)
		assert_equal(glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT), image_1)

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[1])
		glTexSubImage1D(GL_TEXTURE_1D,0, 0, 16,GL_RGB,GL_FLOAT,0)
		assert_equal(glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT),image_2)

		glDeleteBuffers(buffers)
		glDeleteTextures(textures)
	end

	def test_pixelunpack_pixelmap
		return if not supported?(2.1)
		data_1 = [1,2,3,4].pack("f*")
		data_2 = [5,6,7,8].pack("I*")
		data_3 = [9,10,11,12].pack("S*")

		buffers = glGenBuffers(3)
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_UNPACK_BUFFER,4*4+4*4+4*2,data_1+data_2+data_3,GL_DYNAMIC_DRAW)

		glPixelMapfv(GL_PIXEL_MAP_I_TO_I,4,0)
		assert_equal(glGetPixelMapfv(GL_PIXEL_MAP_I_TO_I), [1,2,3,4])

		glPixelMapuiv(GL_PIXEL_MAP_I_TO_I,4,4*4)
		assert_equal(glGetPixelMapuiv(GL_PIXEL_MAP_I_TO_I),[5,6,7,8])
		
		glPixelMapusv(GL_PIXEL_MAP_I_TO_I,4,4*4+4*4)
		assert_equal(glGetPixelMapusv(GL_PIXEL_MAP_I_TO_I),[9,10,11,12])

		glDeleteBuffers(buffers)
	end

	def test_pixelpack_readpixels
		return if not supported?(2.1)
		glClearColor(0,0,0,0)
		glClear(GL_COLOR_BUFFER_BIT)

		image = ([1.0] * 3 * 16).pack("f*")
		glDrawPixels(4,4,GL_RGB,GL_FLOAT,image)

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,4*4*4*3, nil, GL_STREAM_READ)
		glReadPixels(0,0,4,4,GL_RGB,GL_FLOAT,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data,image)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
	end

	def test_pixelpack_pixelmap
		return if not supported?(2.1)

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,4*4, nil, GL_STREAM_READ)

		# fv	
		glPixelMapfv(GL_PIXEL_MAP_I_TO_I,[1,2,3,4])
		glGetPixelMapfv(GL_PIXEL_MAP_I_TO_I,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal([1,2,3,4].pack("f*"),data)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		# uiv
		glPixelMapuiv(GL_PIXEL_MAP_I_TO_I,[5,6,7,8])
		glGetPixelMapuiv(GL_PIXEL_MAP_I_TO_I,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal([5,6,7,8].pack("I*"),data)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		# usv	
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,4*2, nil, GL_STREAM_READ)

		glPixelMapusv(GL_PIXEL_MAP_I_TO_I,[9,10,11,12])
		glGetPixelMapusv(GL_PIXEL_MAP_I_TO_I,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal([9,10,11,12].pack("S*"),data)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
	end

	def test_pixelpack_polygonstipple
		return if not supported?(2.1)

		stipple = [0x12] * 128

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,128, nil, GL_STREAM_READ)

		glPolygonStipple(stipple.pack("c*"))
		glGetPolygonStipple(0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(stipple.pack("c*"),data)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)
	
		glDeleteBuffers(buffers)
	end
	
	def test_pixelpack_separablefilter
		return if not supported?(2.1)
		sf_a = ([0]*3+[1]*3).pack("f*")
		sf_b = ([1]*3+[0]*3).pack("f*")
	
		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,6*4 + 6*4, nil, GL_STREAM_READ)
	
		glSeparableFilter2D(GL_SEPARABLE_2D,GL_RGB8, 2,2,GL_RGB,GL_FLOAT,sf_a,sf_b)
		glGetSeparableFilter(GL_SEPARABLE_2D,GL_RGB,GL_FLOAT,0,6*4,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data,sf_a + sf_b)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
	end

	def test_pixelpack_convolutionfilter
		return if not supported?(2.1)

		cf = ([0]*3+[1]*3+[0]*3+[1]*3).pack("f*")

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,3*4*4, nil, GL_STREAM_READ)

		glConvolutionFilter1D(GL_CONVOLUTION_1D, GL_RGB8, 4, GL_RGB, GL_FLOAT,cf)

		glGetConvolutionFilter(GL_CONVOLUTION_1D, GL_RGB, GL_FLOAT,0)
		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data,cf)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
	end

	def test_pixelpack_histogram
		return if not supported?(2.1)

		glEnable(GL_HISTOGRAM)

		glHistogram(GL_HISTOGRAM,1,GL_RGB8,GL_FALSE)

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,3*4, nil, GL_STREAM_READ)

		glDrawPixels(2,1,GL_RGB,GL_FLOAT,[1,1,1,1,1,1].pack("f*"))
		glGetHistogram(GL_HISTOGRAM,GL_FALSE,GL_RGB,GL_FLOAT,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data.unpack("f*"),[2,2,2])
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
		glDisable(GL_HISTOGRAM)
	end

	def test_pixelpack_minmax
		return if not supported?(2.1)

		glEnable(GL_MINMAX)		

		glMinmax(GL_MINMAX,GL_RGB8,GL_FALSE)

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,6*4, nil, GL_STREAM_READ)

		glDrawPixels(2,1,GL_RGB,GL_FLOAT,[0,0,0,1,1,1].pack("f*"))
		glGetMinmax(GL_MINMAX,GL_FALSE,GL_RGB,GL_FLOAT,0)
		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data.unpack("f*"),[0,0,0,1,1,1])
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
		glDisable(GL_MINMAX)
	end

	def test_pixelpack_teximage
		return if not supported?(2.1)

		textures = glGenTextures(1)
		glBindTexture(GL_TEXTURE_2D,textures[0])

		image = ([0,0,0,1,1,1] * 8).pack("f*") # 16 RGB pixels

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,16*3*4, nil, GL_STREAM_READ)

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8, 4, 4, 0, GL_RGB, GL_FLOAT, image)
		glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data,image)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
		glDeleteTextures(textures)
	end

	def test_pixelpack_compressedteximage
		return if not supported?(2.1)
		return if not supported?("GL_EXT_texture_compression_s3tc")

		# S3TC/DXT5 compressed 2x2 pixels stipple pattern [w,b,b,w]
		image = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x01,0x54,0x5C,0x5C].pack("C*")

		textures = glGenTextures(1)
		glBindTexture(GL_TEXTURE_2D,textures[0])

		buffers = glGenBuffers(1)
		glBindBuffer(GL_PIXEL_PACK_BUFFER,buffers[0])
		glBufferData(GL_PIXEL_PACK_BUFFER_ARB,image.size, nil, GL_STREAM_READ)

		glCompressedTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,0,16,image)
    glGetCompressedTexImage(GL_TEXTURE_2D,0,0)

		data = glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY)
		assert_equal(data,image)
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER_ARB)

		glDeleteBuffers(buffers)
		glDeleteTextures(textures)
	end
end
