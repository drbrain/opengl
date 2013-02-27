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

  def test_colortable
    ct = ([0]*3+[1]*3+[0]*3+[1]*3).pack("f*")
    ct2 = ([1]*3+[0]*3+[1]*3+[0]*3).pack("f*")
    glColorTable(GL_COLOR_TABLE, GL_RGB8, 4, GL_RGB, GL_FLOAT, ct)
    assert_equal(ct, glGetColorTable(GL_COLOR_TABLE, GL_RGB, GL_FLOAT))

    glColorSubTable(GL_COLOR_TABLE, 0, 4, GL_RGB, GL_FLOAT, ct2)
    assert_equal(ct2, glGetColorTable(GL_COLOR_TABLE, GL_RGB, GL_FLOAT))

    glDrawPixels(4, 1, GL_RGB, GL_FLOAT, ct)
    glCopyColorTable(GL_COLOR_TABLE, GL_RGB8, 0, 0, 4)
    assert_equal(ct, glGetColorTable(GL_COLOR_TABLE, GL_RGB, GL_FLOAT))

    glDrawPixels(4, 1, GL_RGB, GL_FLOAT, ct2)
    glCopyColorSubTable(GL_COLOR_TABLE, 0, 0, 0, 4)
    assert_equal(ct2, glGetColorTable(GL_COLOR_TABLE, GL_RGB, GL_FLOAT))

    glColorTableParameterfv(GL_COLOR_TABLE, GL_COLOR_TABLE_BIAS, [0, 1, 0, 1])
    assert_equal([0, 1, 0, 1], glGetColorTableParameterfv(GL_COLOR_TABLE, GL_COLOR_TABLE_BIAS))

    glColorTableParameteriv(GL_COLOR_TABLE, GL_COLOR_TABLE_BIAS, [1, 0, 1, 0])
    assert_equal([1, 0, 1, 0], glGetColorTableParameteriv(GL_COLOR_TABLE, GL_COLOR_TABLE_BIAS))
  end

  def test_convolutionfilter
    cf = ([0]*3+[1]*3+[0]*3+[1]*3).pack("f*")
    cf2 = ([1]*3+[0]*3+[1]*3+[0]*3).pack("f*")
    glConvolutionFilter1D(GL_CONVOLUTION_1D, GL_RGB8, 4, GL_RGB, GL_FLOAT,cf)
    assert_equal(cf, glGetConvolutionFilter(GL_CONVOLUTION_1D, GL_RGB, GL_FLOAT))

    glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_RGB8, 2,2, GL_RGB, GL_FLOAT,cf2)
    assert_equal(cf2 glGetConvolutionFilter(GL_CONVOLUTION_2D, GL_RGB, GL_FLOAT))

    glDrawPixels(4,1,GL_RGB,GL_FLOAT,cf2)
    glCopyConvolutionFilter1D(GL_CONVOLUTION_1D,GL_RGB8,0,0,4)
    assert_equal(cf2, glGetConvolutionFilter(GL_CONVOLUTION_1D, GL_RGB, GL_FLOAT))

    glDrawPixels(2,2,GL_RGB,GL_FLOAT,cf)
    glCopyConvolutionFilter2D(GL_CONVOLUTION_2D,GL_RGB8,0,0,2,2)
    assert_equal(cf, glGetConvolutionFilter(GL_CONVOLUTION_2D, GL_RGB, GL_FLOAT))

    glConvolutionParameterf(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE,GL_CONSTANT_BORDER)
    assert_equal(GL_CONSTANT_BORDER, glGetConvolutionParameterfv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE))

    glConvolutionParameterf(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE,GL_REPLICATE_BORDER)
    assert_equal(GL_CONSTANT_BORDER, glGetConvolutionParameterfv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE))

    glConvolutionParameterfv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE,[GL_CONSTANT_BORDER])
    assert_equal(GL_CONSTANT_BORDER, glGetConvolutionParameterfv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE))

    glConvolutionParameteri(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE,GL_REPLICATE_BORDER)
    assert_equal(GL_CONSTANT_BORDER, glGetConvolutionParameteriv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE))

    glConvolutionParameteriv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE,[GL_CONSTANT_BORDER])
    assert_equal(GL_CONSTANT_BORDER, glGetConvolutionParameteriv(GL_CONVOLUTION_1D,GL_CONVOLUTION_BORDER_MODE))
  end

  def test_separablefilter
    sf_a = ([0]*3+[1]*3).pack("f*")
    sf_b = ([1]*3+[0]*3).pack("f*")

    glSeparableFilter2D(GL_SEPARABLE_2D, GL_RGB8, 2, 2, GL_RGB, GL_FLOAT, sf_a, sf_b)
    assert_equal([sf_a, sf_b], glGetSeparableFilter(GL_SEPARABLE_2D, GL_RGB, GL_FLOAT))
  end

  def test_histogram
    glEnable(GL_HISTOGRAM)

    glHistogram(GL_HISTOGRAM, 1, GL_RGB, GL_FALSE)
    assert_equal(1, glGetHistogramParameterfv(GL_HISTOGRAM, GL_HISTOGRAM_WIDTH))
    assert_equal(GL_RGB, glGetHistogramParameteriv(GL_HISTOGRAM, GL_HISTOGRAM_FORMAT))
    assert_equal(GL_FALSE, glGetHistogramParameteriv(GL_HISTOGRAM, GL_HISTOGRAM_SINK))

    glDrawPixels(2, 1, GL_RGB, GL_FLOAT, [1, 1, 1, 1, 1, 1].pack("f*"))
    h = glGetHistogram(GL_HISTOGRAM, GL_FALSE, GL_RGB, GL_FLOAT)
    assert_equal([2, 2, 2], h.unpack("f*"))
    glResetHistogram(GL_HISTOGRAM)
    h = glGetHistogram(GL_HISTOGRAM, GL_FALSE, GL_RGB, GL_FLOAT)
    assert_equal([0, 0, 0], h.unpack("f*"))

    glDisable(GL_HISTOGRAM)
  end

  def test_minmax
    glEnable(GL_MINMAX)

    glMinmax(GL_MINMAX, GL_RGB, GL_FALSE)
    assert_equal(GL_RGB, glGetMinmaxParameteriv(GL_MINMAX, GL_MINMAX_FORMAT))
    assert_equal(GL_RGB, glGetMinmaxParameterfv(GL_MINMAX, GL_MINMAX_FORMAT))
    assert_equal(GL_FALSE, glGetMinmaxParameteriv(GL_MINMAX, GL_MINMAX_SINK))

    glDrawPixels(2, 1, GL_RGB, GL_FLOAT, [0, 0, 0, 1, 1, 1].pack("f*"))
    mm = glGetMinmax(GL_MINMAX, GL_FALSE, GL_RGB, GL_FLOAT)
    assert_each_in_delta [0, 0, 0, 1, 1, 1], mm.unpack("f*")

    glResetMinmax(GL_MINMAX)
    mm = glGetMinmax(GL_MINMAX, GL_FALSE, GL_RGB, GL_UNSIGNED_BYTE)
    assert_equal [-1, -1, -1, 0, 0, 0], mm.unpack("c*")

    glDisable(GL_MINMAX)
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
