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

class TestGl21 < OpenGL::TestCase

  def setup
    super
    supported? 2.1
  end

  def test_gluniformmatrix21
    vertex_shader_source = <<-SHADER
#version 120

uniform mat2x3 testmat23;
uniform mat3x2 testmat32;
uniform mat2x4 testmat24;
uniform mat4x2 testmat42;
uniform mat3x4 testmat34;
uniform mat4x3 testmat43;

void main() {
  gl_Position = gl_Vertex *
    testmat23[0].x * testmat32[0].x *
    testmat24[0].x * testmat42[0].x *
    testmat34[0].x * testmat43[0].x;
}
    SHADER

    program = glCreateProgram
    vs = glCreateShader(GL_VERTEX_SHADER)

    glShaderSource(vs, vertex_shader_source)
    glCompileShader(vs)

    assert_equal(GL_TRUE, glGetShaderiv(vs, GL_COMPILE_STATUS))
    glAttachShader(program, vs)

    glLinkProgram(program)
    assert_equal(GL_TRUE, glGetProgramiv(program, GL_LINK_STATUS))
    glUseProgram(program)

    tm23l = glGetUniformLocation(program, "testmat23")
    refute_equal(-1, tm23l, "testmat23 missing!")
    tm32l = glGetUniformLocation(program, "testmat32")
    refute_equal(-1, tm32l, "testmat32 missing!")
    tm24l = glGetUniformLocation(program, "testmat24")
    refute_equal(-1, tm24l, "testmat24 missing!")
    tm42l = glGetUniformLocation(program, "testmat42")
    refute_equal(-1, tm42l, "testmat42 missing!")
    tm34l = glGetUniformLocation(program, "testmat34")
    refute_equal(-1, tm34l, "testmat34 missing!")
    tm43l = glGetUniformLocation(program, "testmat43")
    refute_equal(-1, tm43l, "testmat43 missing!")

    refute_equal(-1, glGetUniformLocation(program, "testmat23"),
                 "testmat23 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat32"),
                 "testmat32 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat24"),
                 "testmat24 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat42"),
                 "testmat42 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat34"),
                 "testmat34 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat43"),
                 "testmat43 missing!")

    uniforms = Hash.new { |_, k| raise "invalid uniform #{k}" }
    (0...glGetProgramiv(program, GL_ACTIVE_UNIFORMS)).each do |i|
      uniform = glGetActiveUniform program, i
      uniforms[uniform.last] = i
    end

    glUniformMatrix2x3fv(uniforms["testmat23"], GL_FALSE, [0, 1, 1, 0, 0, 1])
    assert_equal([0, 1, 1, 0, 0, 1], glGetUniformfv(program, uniforms["testmat23"]))
    glUniformMatrix3x2fv(uniforms["testmat32"], GL_FALSE, [1, 0, 0, 1, 1, 0])
    assert_equal([1, 0, 0, 1, 1, 0], glGetUniformfv(program, uniforms["testmat32"]))

    glUniformMatrix2x4fv(uniforms["testmat24"], GL_FALSE, [0, 1, 1, 0, 0, 1, 1, 0])
    assert_equal([0, 1, 1, 0, 0, 1, 1, 0], glGetUniformfv(program, uniforms["testmat24"]))
    glUniformMatrix4x2fv(uniforms["testmat42"], GL_FALSE, [1, 0, 0, 1, 1, 0, 0, 1])
    assert_equal([1, 0, 0, 1, 1, 0, 0, 1], glGetUniformfv(program, uniforms["testmat42"]))

    glUniformMatrix3x4fv(uniforms["testmat34"], GL_FALSE, [0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1])
    assert_equal([0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1], glGetUniformfv(program, uniforms["testmat34"]))
    glUniformMatrix4x3fv(uniforms["testmat43"], GL_FALSE, [1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0])
    assert_equal([1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0], glGetUniformfv(program, uniforms["testmat43"]))

    # 2
    m = Matrix.rows([[0, 1], [1, 0], [0, 1]])
    glUniformMatrix2x3fv(uniforms["testmat23"], GL_FALSE, m)
    assert_equal([0, 1, 1, 0, 0, 1], glGetUniformfv(program, uniforms["testmat23"]))
    m = Matrix.rows([[0, 1, 1], [0, 0, 1]])
    glUniformMatrix3x2fv(uniforms["testmat32"], GL_FALSE, m)
    assert_equal([0, 1, 1, 0, 0, 1], glGetUniformfv(program, uniforms["testmat32"]))

    m = Matrix.rows([[0, 1], [1, 0], [0, 1], [1, 0]])
    glUniformMatrix2x4fv(uniforms["testmat24"], GL_FALSE, m)
    assert_equal([0, 1, 1, 0, 0, 1, 1, 0], glGetUniformfv(program, uniforms["testmat24"]))
    m = Matrix.rows([[0, 1, 1, 1], [0, 0, 1, 1]])
    glUniformMatrix4x2fv(uniforms["testmat42"], GL_FALSE, m)
    assert_equal([0, 1, 1, 1, 0, 0, 1, 1], glGetUniformfv(program, uniforms["testmat42"]))

    m = Matrix.rows([[0, 1, 0], [1, 0, 1], [0, 1, 0], [1, 0, 1]])
    glUniformMatrix3x4fv(uniforms["testmat34"], GL_FALSE, m)
    assert_equal([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1], glGetUniformfv(program, uniforms["testmat34"]))

    m = Matrix.rows([[0, 1, 1, 1], [0, 0, 1, 1], [1, 1, 0, 0]])
    glUniformMatrix4x3fv(uniforms["testmat43"], GL_FALSE, m)
    assert_equal([0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0], glGetUniformfv(program, uniforms["testmat43"]))

    # 3
    assert_raises ArgumentError do glUniformMatrix2x3fv(uniforms["testmat23"], GL_FALSE, [1, 2, 3, 4]) end
    assert_raises ArgumentError do glUniformMatrix3x2fv(uniforms["testmat32"], GL_FALSE, [1, 2, 3, 4]) end
    assert_raises ArgumentError do glUniformMatrix2x4fv(uniforms["testmat24"], GL_FALSE, [1, 2, 3, 4]) end
    assert_raises ArgumentError do glUniformMatrix4x2fv(uniforms["testmat42"], GL_FALSE, [1, 2, 3, 4]) end
    assert_raises ArgumentError do glUniformMatrix3x4fv(uniforms["testmat34"], GL_FALSE, [1, 2, 3, 4]) end
    assert_raises ArgumentError do glUniformMatrix4x3fv(uniforms["testmat43"], GL_FALSE, [1, 2, 3, 4]) end
  end

  def test_pixelunpack_bitmap
    skip("Segfaults on Mesa before 10") if glGetString(GL::VERSION)=~/Mesa (\d+)\.(\d+)\.(\d+)/ && $1.to_i<10
    glOrtho(0, WINDOW_SIZE, 0, WINDOW_SIZE, 0, -1)

    bitmap = [ 0x55 ] * 8 # 64 bits (8x8 bitmap), stipple pattern
    glPixelStorei(GL_PACK_ALIGNMENT, 1)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 8, bitmap.pack("C*"), GL_DYNAMIC_DRAW)

    glBitmap(8, 8, 0, 0, 0, 0, 0)
    data = glReadPixels(0, 0, 8, 8, GL_RED, GL_UNSIGNED_BYTE)
    assert_equal([0, 255] * 32, data.unpack("C*"))

    glDeleteBuffers(buffers)
  end

  def test_pixelunpack_drawpixels
    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT)

    image = ([1.0] * 3 * 16).pack("f*")

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 3*16*4, image, GL_DYNAMIC_DRAW)

    glDrawPixels(4, 4, GL_RGB, GL_FLOAT, 0)

    data = glReadPixels(0, 0, 4, 4, GL_RGB, GL_FLOAT)
    assert_equal(image, data)

    glDeleteBuffers(buffers)
  end

  def test_pixelunpack_polygonstipple
    stipple = ([0x12] * 128).pack("c*")
    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 128, stipple, GL_DYNAMIC_DRAW)

    glPolygonStipple(0)
    assert_equal(stipple, glGetPolygonStipple())
    glDeleteBuffers(buffers)
  end

  def test_pixelunpack_texturecompression
    supported?("GL_EXT_texture_compression_s3tc")

    # S3TC/DXT5 compressed 2x2 pixels stipple patterns [w, b, b, w] and [b, w, w, b]
    image_1 = [0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x54, 0x5C, 0x5C].pack("C*")
    image_2 = [0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x54, 0x01, 0x0D, 0x0D].pack("C*")

    textures = glGenTextures(3)
    glBindTexture(GL_TEXTURE_1D, textures[0])
    glBindTexture(GL_TEXTURE_2D, textures[1])
    glBindTexture(GL_TEXTURE_3D, textures[2])

    buffers = glGenBuffers(2)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 16, image_1, GL_DYNAMIC_DRAW)

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 16, image_2, GL_DYNAMIC_DRAW)

    # Note: 1D and 3D compressed textures are not supported by S3TC/DXTn, and usually not supported at all

    # 1D
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    begin
      glCompressedTexImage1D(GL_TEXTURE_1D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 4, 0, 16, 0)
      assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_1D, 0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    begin
      glCompressedTexSubImage1D(GL_TEXTURE_1D, 0, 0, 4, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, 0)
      assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_1D, 0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    # 2D
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 2, 2, 0, 16, 0)
    assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_2D, 0))

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2, 2, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, 0)
    assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_2D, 0))

    # 3D
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    begin
      glCompressedTexImage3D(GL_TEXTURE_3D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 2, 2, 1, 0, 16, 0)
      assert_equal(image_1, glGetCompressedTexImage(GL_TEXTURE_3D, 0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    begin
      glCompressedTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 2, 2, 1, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 16, 0)
      assert_equal(image_2, glGetCompressedTexImage(GL_TEXTURE_3D, 0))
    rescue Gl::Error => err
      assert(err.id == GL_INVALID_ENUM || err.id == GL_INVALID_OPERATION)
    end

    glDeleteBuffers(buffers)
    glDeleteTextures(textures)
  end

  def test_pixelunpack_texture
    textures = glGenTextures(3)
    image_1 = ([0, 0, 0, 1, 1, 1] * 8).pack("f*") # 16 RGB pixels
    image_2 = ([1, 1, 1, 0, 0, 0] * 8).pack("f*") # 16 RGB pixels

    buffers = glGenBuffers(2)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 6*8*4, image_1, GL_DYNAMIC_DRAW)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 6*8*4, image_2, GL_DYNAMIC_DRAW)

    # 3D
    glBindTexture(GL_TEXTURE_3D, textures[0])

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, 2, 2, 4, 0, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_1, glGetTexImage(GL_TEXTURE_3D, 0, GL_RGB, GL_FLOAT))

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 2, 2, 4, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_2, glGetTexImage(GL_TEXTURE_3D, 0, GL_RGB, GL_FLOAT))

    # 2D
    glBindTexture(GL_TEXTURE_2D, textures[1])

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 4, 4, 0, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_1, glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT))

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 4, 4, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_2, glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT))

    # 1D
    glBindTexture(GL_TEXTURE_1D, textures[2])

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])

    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB8, 16, 0, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_1, glGetTexImage(GL_TEXTURE_1D, 0, GL_RGB, GL_FLOAT))

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[1])
    glTexSubImage1D(GL_TEXTURE_1D, 0, 0, 16, GL_RGB, GL_FLOAT, 0)
    assert_equal(image_2, glGetTexImage(GL_TEXTURE_1D, 0, GL_RGB, GL_FLOAT))

    glDeleteBuffers(buffers)
    glDeleteTextures(textures)
  end

  def test_pixelunpack_pixelmap
    data_1 = [1, 2, 3, 4].pack("f*")
    data_2 = [5, 6, 7, 8].pack("I*")
    data_3 = [9, 10, 11, 12].pack("S*")

    buffers = glGenBuffers(3)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 4*4+4*4+4*2, data_1+data_2+data_3, GL_DYNAMIC_DRAW)

    glPixelMapfv(GL_PIXEL_MAP_I_TO_I, 4, 0)
    assert_equal([1, 2, 3, 4], glGetPixelMapfv(GL_PIXEL_MAP_I_TO_I))

    glPixelMapuiv(GL_PIXEL_MAP_I_TO_I, 4, 4*4)
    assert_equal([5, 6, 7, 8], glGetPixelMapuiv(GL_PIXEL_MAP_I_TO_I))

    glPixelMapusv(GL_PIXEL_MAP_I_TO_I, 4, 4*4+4*4)
    assert_equal([9, 10, 11, 12], glGetPixelMapusv(GL_PIXEL_MAP_I_TO_I))

    glDeleteBuffers(buffers)
  end

  def test_pixelpack_readpixels
    glClearColor(0, 0, 0, 0)
    glClear(GL_COLOR_BUFFER_BIT)

    image = ([1.0] * 3 * 16).pack("f*")
    glDrawPixels(4, 4, GL_RGB, GL_FLOAT, image)

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_PACK_BUFFER, 4*4*4*3, nil, GL_STREAM_READ)
    glReadPixels(0, 0, 4, 4, GL_RGB, GL_FLOAT, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal(image, data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    glDeleteBuffers(buffers)
  end

  def test_pixelpack_pixelmap
    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_PACK_BUFFER, 4*4, nil, GL_STREAM_READ)

    # fv
    glPixelMapfv(GL_PIXEL_MAP_I_TO_I, [1, 2, 3, 4])
    glGetPixelMapfv(GL_PIXEL_MAP_I_TO_I, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal([1, 2, 3, 4].pack("f*"), data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    # uiv
    glPixelMapuiv(GL_PIXEL_MAP_I_TO_I, [5, 6, 7, 8])
    glGetPixelMapuiv(GL_PIXEL_MAP_I_TO_I, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal([5, 6, 7, 8].pack("I*"), data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    # usv
    glBufferData(GL_PIXEL_PACK_BUFFER, 4*2, nil, GL_STREAM_READ)

    glPixelMapusv(GL_PIXEL_MAP_I_TO_I, [9, 10, 11, 12])
    glGetPixelMapusv(GL_PIXEL_MAP_I_TO_I, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal([9, 10, 11, 12].pack("S*"), data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    glDeleteBuffers(buffers)
  end

  def test_pixelpack_polygonstipple
    stipple = [0x12] * 128

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_PACK_BUFFER, 128, nil, GL_STREAM_READ)

    glPolygonStipple(stipple.pack("c*"))
    glGetPolygonStipple(0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal(stipple.pack("c*"), data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    glDeleteBuffers(buffers)
  end

  def test_pixelpack_teximage
    textures = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, textures[0])

    image = ([0, 0, 0, 1, 1, 1] * 8).pack("f*") # 16 RGB pixels

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_PACK_BUFFER, 16*3*4, nil, GL_STREAM_READ)

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 4, 4, 0, GL_RGB, GL_FLOAT, image)
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal(image, data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    glDeleteBuffers(buffers)
    glDeleteTextures(textures)
  end

  def test_pixelpack_compressedteximage
    supported?("GL_EXT_texture_compression_s3tc")

    # S3TC/DXT5 compressed 2x2 pixels stipple pattern [w, b, b, w]
    image = [0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0x54, 0x5C, 0x5C].pack("C*")

    textures = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, textures[0])

    buffers = glGenBuffers(1)
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffers[0])
    glBufferData(GL_PIXEL_PACK_BUFFER, image.size, nil, GL_STREAM_READ)

    glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 2, 2, 0, 16, image)
    glGetCompressedTexImage(GL_TEXTURE_2D, 0, 0)

    data = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY)
    assert_equal(image, data)
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER)

    glDeleteBuffers(buffers)
    glDeleteTextures(textures)
  end
end
