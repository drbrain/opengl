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

class TestGl12 < OpenGL::TestCase

  def setup
    super
    supported? 1.2
  end

  def test_glblend
    glBlendColor(0.0, 1.0, 0.0, 1.0)
    assert_equal(glGetDoublev(GL_BLEND_COLOR), [0, 1, 0, 1])

    glBlendEquation(GL_MIN)
    assert_equal(GL_MIN, glGetIntegerv(GL_BLEND_EQUATION))
    glBlendEquation(GL_MAX)
    assert_equal(GL_MAX, glGetIntegerv(GL_BLEND_EQUATION))
  end

  def test_gldrawrangeelements
    va = [0, 0, 0, 1, 1, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glEnableClientState(GL_VERTEX_ARRAY)

    glDrawRangeElements(GL_POINTS, 0, 2, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("C*"))
    count = glRenderMode(GL_RENDER)
    assert_equal(12, count)

    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_texture_3D
    image = ([0, 0, 0, 1, 1, 1] * 2 * 2).pack("f*")
    image2 = ([1, 1, 1, 0, 0, 0] * 2 * 2).pack("f*")

    textures = glGenTextures(1)
    glBindTexture(GL_TEXTURE_3D, textures[0])

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, 2, 2, 2, 0, GL_RGB, GL_FLOAT, image)
    assert_equal(image, glGetTexImage(GL_TEXTURE_3D, 0, GL_RGB, GL_FLOAT))

    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 2, 2, 2, GL_RGB, GL_FLOAT, image2)
    assert_equal(image2, glGetTexImage(GL_TEXTURE_3D, 0, GL_RGB, GL_FLOAT))

    glDrawPixels(2, 2, GL_RGB, GL_FLOAT, image)
    glCopyTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 0, 0, 2, 2)
    ti = glGetTexImage(GL_TEXTURE_3D, 0, GL_RGB, GL_FLOAT).unpack("f*")
    assert_equal(([0]*3 + [1]*3) * 2 + ([1]*3 + [0]*3) * 2, ti)

    glDeleteTextures(textures)
  end
end
