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

class TestGl20 < OpenGL::TestCase

  def setup
    super
    supported? 2.0
  end

  def test_glblendequationseparate
    glBlendEquationSeparate(GL_MIN, GL_MAX)
    assert_equal(GL_MIN, glGetIntegerv(GL_BLEND_EQUATION_RGB))
    assert_equal(GL_MAX, glGetIntegerv(GL_BLEND_EQUATION_ALPHA))
    glBlendEquationSeparate(GL_MAX, GL_MIN)
    assert_equal(GL_MAX, glGetIntegerv(GL_BLEND_EQUATION_RGB))
    assert_equal(GL_MIN, glGetIntegerv(GL_BLEND_EQUATION_ALPHA))
  end

  def test_stencilops
    glStencilOpSeparate(GL_FRONT, GL_ZERO, GL_INCR, GL_DECR)
    assert_equal(GL_ZERO, glGetIntegerv(GL_STENCIL_FAIL))
    assert_equal(GL_INCR, glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL))
    assert_equal(GL_DECR, glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS))
    glStencilOpSeparate(GL_FRONT, GL_INCR, GL_DECR, GL_ZERO)
    assert_equal(GL_INCR, glGetIntegerv(GL_STENCIL_FAIL))
    assert_equal(GL_DECR, glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL))
    assert_equal(GL_ZERO, glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS))

    glStencilFuncSeparate(GL_FRONT, GL_LEQUAL, 1, 0)
    assert_equal(GL_LEQUAL, glGetIntegerv(GL_STENCIL_FUNC))
    assert_equal(1, glGetIntegerv(GL_STENCIL_REF))
    assert_equal(0, glGetIntegerv(GL_STENCIL_VALUE_MASK))
    glStencilFuncSeparate(GL_FRONT, GL_GEQUAL, 0, 1)
    assert_equal(GL_GEQUAL, glGetIntegerv(GL_STENCIL_FUNC))
    assert_equal(0, glGetIntegerv(GL_STENCIL_REF))
    assert_equal(1, glGetIntegerv(GL_STENCIL_VALUE_MASK))

    glStencilMaskSeparate(GL_FRONT, 1)
    assert_equal(1, glGetIntegerv( GL_STENCIL_WRITEMASK))
    glStencilMaskSeparate(GL_FRONT, 0)
    assert_equal(0, glGetIntegerv(GL_STENCIL_WRITEMASK))
  end

  def test_gldrawbuf
    glDrawBuffers([GL_FRONT_LEFT, GL_BACK_LEFT])
    assert_equal(GL_FRONT_LEFT, glGetIntegerv(GL_DRAW_BUFFER0))
    assert_equal(GL_BACK_LEFT, glGetIntegerv(GL_DRAW_BUFFER1))
  end

  def test_glvertexattrib
    # 1
    glVertexAttrib1d(1, 2.0)
    assert_equal([2.0, 0.0, 0.0, 1.0], glGetVertexAttribdv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib1dv(1, [3.0])
    assert_equal([3.0, 0.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib1f(1, 2.0)
    assert_equal([2, 0, 0, 1], glGetVertexAttribiv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib1fv(1, [3.0])
    assert_equal([3.0, 0.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib1s(1, 2)
    assert_equal([2.0, 0.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib1sv(1, [3])
    assert_equal([3.0, 0.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    # 2
    glVertexAttrib2d(1, 2.0, 2.0)
    assert_equal([2.0, 2.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib2dv(1, [3.0, 3.0])
    assert_equal([3.0, 3.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib2f(1, 2.0, 2.0)
    assert_equal([2.0, 2.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib2fv(1, [3.0, 3.0])
    assert_equal([3.0, 3.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib2s(1, 2, 2)
    assert_equal([2.0, 2.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib2sv(1, [3, 3])
    assert_equal([3.0, 3.0, 0.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    # 3
    glVertexAttrib3d(1, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib3dv(1, [3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib3f(1, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib3fv(1, [3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib3s(1, 2, 2, 2)
    assert_equal([2.0, 2.0, 2.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib3sv(1, [3, 3, 3])
    assert_equal([3.0, 3.0, 3.0, 1.0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    # 4N
    glVertexAttrib4Nbv(1, [2**7-1, 2**7-1, 2**7-1, 2**7-1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Niv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Nsv(1, [2**15-1, 2**15-1, 2**15-1, 2**15-1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Nub(1, 0, 0, 0, 0)
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Nubv(1, [2**8-1, 2**8-1, 2**8-1, 2**8-1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Nuiv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4Nusv(1, [2**16-1, 2**16-1, 2**16-1, 2**16-1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    # 4
    glVertexAttrib4bv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4d(1, 1, 1, 1, 1)
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4dv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4f(1, 1, 1, 1, 1)
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4fv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4iv(1, [1, 1, 1, 1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4s(1, 0, 0, 0, 0)
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4sv(1, [1, 1, 1, 1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4ubv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4uiv(1, [1, 1, 1, 1])
    assert_each_in_delta([1, 1, 1, 1], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
    glVertexAttrib4usv(1, [0, 0, 0, 0])
    assert_each_in_delta([0, 0, 0, 0], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))
  end

  def test_vertexattribpointer
    vaa = [1, 1, 1, 1, 2, 2, 2, 2].pack("f*")
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vaa)
    assert_equal(glGetVertexAttribPointerv(1), vaa)

    glEnableVertexAttribArray(1)

    glBegin(GL_POINTS)
    glArrayElement(1)
    glEnd()
    assert_equal([2, 2, 2, 2], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))

    glDisableVertexAttribArray(1)
  end

  def test_shaders
    vertex_shader_source = <<-SHADER
#version 110

void main() {
  gl_Position = ftransform();
}
    SHADER

    program = glCreateProgram
    assert glIsProgram program

    vs = glCreateShader GL_VERTEX_SHADER
    assert glIsShader vs

    glShaderSource vs, vertex_shader_source
    assert_equal vertex_shader_source, glGetShaderSource(vs)
    assert_equal GL_VERTEX_SHADER, glGetShaderiv(vs, GL_SHADER_TYPE)

    glCompileShader vs
    assert glGetShaderiv(vs, GL_COMPILE_STATUS)

    vslog = glGetShaderInfoLog vs
    assert_equal '', vslog

    glAttachShader program, vs
    assert_equal vs, glGetAttachedShaders(program)

    glDetachShader program, vs
    assert_nil glGetAttachedShaders program

    glAttachShader program, vs

    glLinkProgram program
    assert glGetProgramiv(program, GL_LINK_STATUS)

    glValidateProgram program
    assert(glGetProgramiv(program, GL_VALIDATE_STATUS),
           glGetProgramInfoLog(program))

    prlog = glGetProgramInfoLog program
    assert_equal '', prlog

    glUseProgram program
    assert_equal program, glGetIntegerv(GL_CURRENT_PROGRAM)

    glUseProgram 0

    glDetachShader program, vs
    glDeleteShader vs
    refute glIsShader vs

    glDeleteProgram program
    refute glIsProgram(program)
  end

  def test_shaders_2
    vertex_shader_source = <<-SHADER
#version 110
attribute vec4 test;

uniform float testvec1;
uniform vec2 testvec2;
uniform vec3 testvec3;
uniform vec4 testvec4;

uniform int testivec1;
uniform ivec2 testivec2;
uniform ivec3 testivec3;
uniform ivec4 testivec4;

void main() {
  testvec1;
  testvec2;
  testvec3;
  testvec4;
  testivec1;
  testivec2;
  testivec3;
  testivec4;
  gl_Position = ftransform();
}
    SHADER

    program = glCreateProgram

    vs = glCreateShader GL_VERTEX_SHADER

    glShaderSource vs, vertex_shader_source
    glCompileShader vs

    assert glGetShaderiv(vs, GL_COMPILE_STATUS), glGetShaderInfoLog(vs)

    glAttachShader program, vs

    glBindAttribLocation program, 2, "test"
    glLinkProgram program

    glValidateProgram program
    assert(glGetProgramiv(program, GL_VALIDATE_STATUS),
           glGetProgramInfoLog(program))

    assert glGetProgramiv(program, GL_LINK_STATUS)

    glUseProgram program

    test = glGetAttribLocation program, "test"
    assert_equal(-1, test)

    tv1l = glGetUniformLocation program, "testvec1"
    refute_equal(-1, tv1l, "testvec1 missing!")

    tv2l = glGetUniformLocation program, "testvec2"
    refute_equal(-1, tv2l, "testvec2 missing!")

    tv3l = glGetUniformLocation program, "testvec3"
    refute_equal(-1, tv3l, "testvec3 missing!")

    tv4l = glGetUniformLocation program, "testvec4"
    refute_equal(-1, tv4l, "testvec4 missing!")

    tv1il = glGetUniformLocation program, "testivec1"
    refute_equal(-1, tv1il, "testivec1 missing!")

    tv2il = glGetUniformLocation program, "testivec2"
    refute_equal(-1, tv2il, "testivec2 missing!")

    tv3il = glGetUniformLocation program, "testivec3"
    refute_equal(-1, tv3il, "testivec3 missing!")

    tv4il = glGetUniformLocation program, "testivec4"
    refute_equal(-1, tv4il, "testivec4 missing!")

    assert_equal [1, GL_FLOAT_VEC4, "gl_Vertex"], glGetActiveAttrib(program, 0)
    assert_equal [1, GL_INT, "testivec1"], glGetActiveUniform(program, tv1il)

    # f
    glUniform1f(tv1l, 2.0)
    assert_equal(2.0, glGetUniformfv(program, tv1l))
    glUniform2f(tv2l, 2.0, 2.0)
    assert_equal([2.0, 2.0], glGetUniformfv(program, tv2l))
    glUniform3f(tv3l, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0], glGetUniformfv(program, tv3l))
    glUniform4f(tv4l, 2.0, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0, 2.0], glGetUniformfv(program, tv4l))
    # i
    glUniform1i(tv1il, 3)
    assert_equal(3, glGetUniformiv(program, tv1il))
    glUniform2i(tv2il, 3, 3)
    assert_equal([3, 3], glGetUniformiv(program, tv2il))
    glUniform3i(tv3il, 3, 3, 3)
    assert_equal([3, 3, 3], glGetUniformiv(program, tv3il))
    glUniform4i(tv4il, 3, 3, 3, 3)
    assert_equal([3, 3, 3, 3], glGetUniformiv(program, tv4il))
    # fv
    glUniform1fv(tv1l, [3.0])
    assert_equal(3.0, glGetUniformfv(program, tv1l))
    glUniform2fv(tv2l, [3.0, 3.0])
    assert_equal([3.0, 3.0], glGetUniformfv(program, tv2l))
    glUniform3fv(tv3l, [3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0], glGetUniformfv(program, tv3l))
    glUniform4fv(tv4l, [3.0, 3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0, 3.0], glGetUniformfv(program, tv4l))
    # iv
    glUniform1iv(tv1il, [2])
    assert_equal(2, glGetUniformiv(program, tv1il))
    glUniform2iv(tv2il, [2, 2])
    assert_equal([2, 2], glGetUniformiv(program, tv2il))
    glUniform3iv(tv3il, [2, 2, 2])
    assert_equal([2, 2, 2], glGetUniformiv(program, tv3il))
    glUniform4iv(tv4il, [2, 2, 2, 2])
    assert_equal([2, 2, 2, 2], glGetUniformiv(program, tv4il))

    glDeleteShader(vs)
    glDeleteProgram(program)
  end

  def test_shaders_3
    vertex_shader_source = <<-SHADER
#version 110

uniform mat2 testmat2;
uniform mat3 testmat3;
uniform mat4 testmat4;

void main() {
  gl_Position = ftransform() * testmat2[0][0] * testmat3[0][0] * testmat4[0][0];
}
    SHADER

    program = glCreateProgram
    vs = glCreateShader GL_VERTEX_SHADER

    glShaderSource vs, vertex_shader_source
    glCompileShader vs

    assert glGetShaderiv(vs, GL_COMPILE_STATUS), glGetShaderInfoLog(vs)

    glAttachShader program, vs

    glLinkProgram program
    assert glGetProgramiv(program, GL_LINK_STATUS)

    glValidateProgram program
    assert(glGetProgramiv(program, GL_VALIDATE_STATUS),
           glGetProgramInfoLog(program))

    glUseProgram program

    refute_equal(-1, glGetUniformLocation(program, "testmat2"),
                 "testmat2 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat3"),
                 "testmat3 missing!")
    refute_equal(-1, glGetUniformLocation(program, "testmat4"),
                 "testmat4 missing!")

    uniforms = Hash.new do |_, k| raise "invalid uniform #{k}" end
    (0...glGetProgramiv(program, GL_ACTIVE_UNIFORMS)).each do |i|
      uniform = glGetActiveUniform program, i
      uniforms[uniform.last] = i
    end

    glUniformMatrix2fv(uniforms['testmat2'], GL_TRUE, [0, 1, 2, 3])

    assert_each_in_delta([0, 2, 1, 3],
                         glGetUniformfv(program, uniforms['testmat2']))

    glUniformMatrix3fv(uniforms['testmat3'], GL_TRUE,
                       [0, 1, 2, 3, 4, 5, 6, 7, 8])

    assert_each_in_delta([0, 3, 6, 1, 4, 7, 2, 5, 8],
                         glGetUniformfv(program, uniforms['testmat3']))

    glUniformMatrix4fv(uniforms['testmat4'], GL_TRUE,
                       [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])

    assert_each_in_delta([0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15],
                         glGetUniformfv(program, uniforms['testmat4']))
  ensure
    glDeleteProgram program
  end

  def test_buffered_vertexattribpointer
    vaa = [1, 1, 1, 1, 2, 2, 2, 2].pack("f*")

    buffers = glGenBuffers(1)

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ARRAY_BUFFER, 8*4, vaa, GL_DYNAMIC_DRAW)

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0)
    assert_equal(0, glGetVertexAttribPointerv(1))

    glEnableVertexAttribArray(1)

    glBegin(GL_POINTS)
    glArrayElement(1)
    glEnd()
    assert_equal([2, 2, 2, 2], glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB))

    glDisableVertexAttribArray(1)
    glDeleteBuffers(buffers)
  end
end
