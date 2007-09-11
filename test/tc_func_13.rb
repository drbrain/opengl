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

class Test_13 < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_glsamplecoverage
		return if not supported?(1.3)
		glSampleCoverage(0.0,GL_TRUE)
		assert_equal(glGetDoublev(GL_SAMPLE_COVERAGE_VALUE),0.0)
		assert_equal(glGetDoublev(GL_SAMPLE_COVERAGE_INVERT),GL_TRUE)
		glSampleCoverage(1.0,GL_FALSE)
		assert_equal(glGetDoublev(GL_SAMPLE_COVERAGE_VALUE),1.0)
		assert_equal(glGetDoublev(GL_SAMPLE_COVERAGE_INVERT),GL_FALSE)
	end

	def test_multitexture
		return if not supported?(1.3)
		glActiveTexture(GL_TEXTURE1)
		glClientActiveTexture(GL_TEXTURE2)
		assert_equal(glGetIntegerv(GL_ACTIVE_TEXTURE),GL_TEXTURE1)
		assert_equal(glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE),GL_TEXTURE2)
	end

	def test_transposematrix
		return if not supported?(1.3)
		m_a = [[1.0,2.0,3.0,4.0],
					 [0.0,2.0,0.0,0.0],
					 [0.0,0.0,2.0,0.0],
					 [0.0,0.0,0.0,2.0]]

		m_b = [[1.0,2.0,3.0,4.0],
					 [0.0,3.0,0.0,0.0],
					 [0.0,0.0,3.0,0.0],
					 [0.0,0.0,0.0,3.0]]

		glMatrixMode(GL_MODELVIEW)
		glLoadTransposeMatrixf(m_a)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX), m_a)

		glLoadTransposeMatrixd(m_b)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX), m_b)

		glLoadIdentity()
		glMultTransposeMatrixf(m_a)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX), m_a)

		glLoadIdentity()
		glMultTransposeMatrixd(m_b)
		assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX), m_b)
	end
	
	def test_texturecompression
		return if not supported?(1.3)
		return if not supported?("GL_EXT_texture_compression_s3tc")

		# S3TC/DXT5 compressed 2x2 pixels stipple patterns [w,b,b,w] and [b,w,w,b]
		image_1 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x01,0x54,0x5C,0x5C].pack("C*")
		image_2 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x54,0x01,0x0D,0x0D].pack("C*")

		textures = glGenTextures(3)
		glBindTexture(GL_TEXTURE_1D,textures[0])
		glBindTexture(GL_TEXTURE_2D,textures[1])
		glBindTexture(GL_TEXTURE_3D,textures[2])

		# Note: 1D and 3D compressed textures are not supported by S3TC/DXTn, and usually not supported at all

		# 1D
		glCompressedTexImage1D(GL_TEXTURE_1D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,4,0,16,image_1)
		err = glGetError()
		assert(err == 0 || err == GL_INVALID_ENUM || err == GL_INVALID_OPERATION)
		if (err == 0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_1D,0), image_1)
		end

		glCompressedTexSubImage1D(GL_TEXTURE_1D,0,0,4,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,image_2)
		err = glGetError()
		assert(err == 0 || err == GL_INVALID_ENUM || err == GL_INVALID_OPERATION)
		if (err == 0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_1D,0), image_2)
		end

		# 2D
		glCompressedTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,0,16,image_1)
		assert_equal(glGetCompressedTexImage(GL_TEXTURE_2D,0), image_1)

		glCompressedTexSubImage2D(GL_TEXTURE_2D,0,0,0,2,2,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,image_2)
		assert_equal(glGetCompressedTexImage(GL_TEXTURE_2D,0), image_2)

		# 3D
		glCompressedTexImage3D(GL_TEXTURE_3D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,1,0,16,image_1)
		err = glGetError()
		assert(err == 0 || err == GL_INVALID_ENUM || err == GL_INVALID_OPERATION)
		if (err == 0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_3D,0), image_1)
		end

		glCompressedTexSubImage3D(GL_TEXTURE_3D,0, 0,0,0, 2,2,1, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, image_2)
		err = glGetError()
		assert(err == 0 || err == GL_INVALID_ENUM || err == GL_INVALID_OPERATION)
		if (err == 0)
			assert_equal(glGetCompressedTexImage(GL_TEXTURE_3D,0), image_2)
		end
		
		glDeleteTextures(textures)

		n = glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
		if (n>0)
			assert_equal(glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS).size,n)
		end
	end
	
	def test_glmultitexcoord
		return if not supported?(1.3)
	
		glActiveTexture(GL_TEXTURE1)

		# 1
		glMultiTexCoord1d(GL_TEXTURE1, 1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,0,0,1])
		glMultiTexCoord1dv(GL_TEXTURE1, [0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord1f(GL_TEXTURE1, 1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,0,0,1])
		glMultiTexCoord1fv(GL_TEXTURE1, [0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord1i(GL_TEXTURE1, 1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,0,0,1])
		glMultiTexCoord1iv(GL_TEXTURE1, [0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord1s(GL_TEXTURE1, 1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,0,0,1])
		glMultiTexCoord1sv(GL_TEXTURE1, [0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		# 2
		glMultiTexCoord2d(GL_TEXTURE1, 1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,0,1])
		glMultiTexCoord2dv(GL_TEXTURE1, [0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord2f(GL_TEXTURE1, 1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,0,1])
		glMultiTexCoord2fv(GL_TEXTURE1, [0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord2i(GL_TEXTURE1, 1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,0,1])
		glMultiTexCoord2iv(GL_TEXTURE1, [0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord2s(GL_TEXTURE1, 1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,0,1])
		glMultiTexCoord2sv(GL_TEXTURE1, [0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		# 3
		glMultiTexCoord3d(GL_TEXTURE1, 1.0,1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord3dv(GL_TEXTURE1, [0.0,0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord3f(GL_TEXTURE1, 1.0,1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord3fv(GL_TEXTURE1, [0.0,0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord3i(GL_TEXTURE1, 1,1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord3iv(GL_TEXTURE1, [0,0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		glMultiTexCoord3s(GL_TEXTURE1, 1,1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord3sv(GL_TEXTURE1, [0,0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,1])
		# 4
		glMultiTexCoord4d(GL_TEXTURE1, 1.0,1.0,1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord4dv(GL_TEXTURE1, [0.0,0.0,0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,0])
		glMultiTexCoord4f(GL_TEXTURE1, 1.0,1.0,1.0,1.0)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord4fv(GL_TEXTURE1, [0.0,0.0,0.0,0.0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,0])
		glMultiTexCoord4i(GL_TEXTURE1, 1,1,1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord4iv(GL_TEXTURE1, [0,0,0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,0])
		glMultiTexCoord4s(GL_TEXTURE1, 1,1,1,1)
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [1,1,1,1])
		glMultiTexCoord4sv(GL_TEXTURE1, [0,0,0,0])
		assert_equal(glGetDoublev(GL_CURRENT_TEXTURE_COORDS), [0,0,0,0])

		glActiveTexture(GL_TEXTURE0)
	end
end
