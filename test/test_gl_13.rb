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

require 'opengl/test_case'

class TestGl13 < OpenGL::TestCase

  def setup
    super
    supported? 1.3
  end

  def test_glsamplecoverage
    glSampleCoverage(0.0, GL_TRUE)
    assert_equal(0.0, glGetDoublev(GL_SAMPLE_COVERAGE_VALUE))
    assert_equal(GL_TRUE, glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT))
    glSampleCoverage(1.0, GL_FALSE)
    assert_equal(1.0, glGetDoublev(GL_SAMPLE_COVERAGE_VALUE))
    assert_equal(GL_FALSE, glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT))
  end

  def test_multitexture
    glActiveTexture(GL_TEXTURE1)
    glClientActiveTexture(GL_TEXTURE2)
    assert_equal(GL_TEXTURE1, glGetIntegerv(GL_ACTIVE_TEXTURE))
    assert_equal(GL_TEXTURE2, glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE))
  end

  def test_transposematrix
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
    assert_equal(m_a, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX))

    glLoadTransposeMatrixd(m_b)
    assert_equal(m_b, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX))

    glLoadIdentity()
    glMultTransposeMatrixf(m_a)
    assert_equal(m_a, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX))

    glLoadIdentity()
    glMultTransposeMatrixd(m_b)
    assert_equal(m_b, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX))

    # 2
    m = Matrix.rows([[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]])
    glMatrixMode(GL_MODELVIEW)
    glLoadTransposeMatrixf(m)
    assert_equal(m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glLoadTransposeMatrixd(m)
    assert_equal(m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glMultTransposeMatrixf(m)
    assert_equal(m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX))
    glLoadIdentity()
    glMultTransposeMatrixd(m)
    assert_equal(m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX))

    assert_raises ArgumentError do glLoadTransposeMatrixf([1,2,3,4]) end
    assert_raises ArgumentError do glLoadTransposeMatrixd([1,2,3,4]) end
    assert_raises ArgumentError do glMultTransposeMatrixf([1,2,3,4]) end
    assert_raises ArgumentError do glMultTransposeMatrixd([1,2,3,4]) end
  end

  def test_texturecompression
    supported?("GL_EXT_texture_compression_s3tc")

    # S3TC/DXT5 compressed 2x2 pixels stipple patterns [w,b,b,w] and [b,w,w,b]
    image_1 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x01,0x54,0x5C,0x5C].pack("C*")
    image_2 = [0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x54,0x01,0x0D,0x0D].pack("C*")

    textures = glGenTextures(3)
    glBindTexture(GL_TEXTURE_1D,textures[0])
    glBindTexture(GL_TEXTURE_2D,textures[1])
    glBindTexture(GL_TEXTURE_3D,textures[2])

    # Note: 1D and 3D compressed textures are not supported by S3TC/DXTn, and usually not supported at all

    # 1D
    begin
      glCompressedTexImage1D(GL_TEXTURE_1D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,4,0,16,image_1)
      assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_1D,0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    begin
      glCompressedTexSubImage1D(GL_TEXTURE_1D,0,0,4,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,image_2)
      assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_1D,0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    # 2D
    glCompressedTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,0,16,image_1)
    assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_2D,0))

    glCompressedTexSubImage2D(GL_TEXTURE_2D,0,0,0,2,2,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,16,image_2)
    assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_2D,0))

    # 3D
    begin
      glCompressedTexImage3D(GL_TEXTURE_3D,0,GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,2,2,1,0,16,image_1)
      assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_3D,0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    begin
      glCompressedTexSubImage3D(GL_TEXTURE_3D,0, 0,0,0, 2,2,1, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, image_2)
      assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_3D,0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    glDeleteTextures(textures)

    n = glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS)
    if (n>0)
      assert_equal(n, glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS).size)
    end
  end

  def test_glmultitexcoord
    glActiveTexture(GL_TEXTURE1)

    # 1
    glMultiTexCoord1d(GL_TEXTURE1, 1.0)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1dv(GL_TEXTURE1, [0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1f(GL_TEXTURE1, 1.0)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1fv(GL_TEXTURE1, [0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1i(GL_TEXTURE1, 1)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1iv(GL_TEXTURE1, [0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1s(GL_TEXTURE1, 1)
    assert_equal([1,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord1sv(GL_TEXTURE1, [0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    # 2
    glMultiTexCoord2d(GL_TEXTURE1, 1.0,1.0)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2dv(GL_TEXTURE1, [0.0,0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2f(GL_TEXTURE1, 1.0,1.0)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2fv(GL_TEXTURE1, [0.0,0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2i(GL_TEXTURE1, 1,1)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2iv(GL_TEXTURE1, [0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2s(GL_TEXTURE1, 1,1)
    assert_equal([1,1,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord2sv(GL_TEXTURE1, [0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    # 3
    glMultiTexCoord3d(GL_TEXTURE1, 1.0,1.0,1.0)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3dv(GL_TEXTURE1, [0.0,0.0,0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3f(GL_TEXTURE1, 1.0,1.0,1.0)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3fv(GL_TEXTURE1, [0.0,0.0,0.0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3i(GL_TEXTURE1, 1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3iv(GL_TEXTURE1, [0,0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3s(GL_TEXTURE1, 1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord3sv(GL_TEXTURE1, [0,0,0])
    assert_equal([0,0,0,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    # 4
    glMultiTexCoord4d(GL_TEXTURE1, 1.0,1.0,1.0,1.0)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4dv(GL_TEXTURE1, [0.0,0.0,0.0,0.0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4f(GL_TEXTURE1, 1.0,1.0,1.0,1.0)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4fv(GL_TEXTURE1, [0.0,0.0,0.0,0.0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4i(GL_TEXTURE1, 1,1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4iv(GL_TEXTURE1, [0,0,0,0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4s(GL_TEXTURE1, 1,1,1,1)
    assert_equal([1,1,1,1], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))
    glMultiTexCoord4sv(GL_TEXTURE1, [0,0,0,0])
    assert_equal([0,0,0,0], glGetDoublev(GL_CURRENT_TEXTURE_COORDS))

    glActiveTexture(GL_TEXTURE0)
  end
end
