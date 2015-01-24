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

class TestGlExtArb < OpenGL::TestCase

  def test_gl_arb_transpose_matrix
    supported? "GL_ARB_transpose_matrix"
    m_a = [[1.0, 2.0, 3.0, 4.0],
      [0.0, 2.0, 0.0, 0.0],
      [0.0, 0.0, 2.0, 0.0],
      [0.0, 0.0, 0.0, 2.0]]

    m_b = [[1.0, 2.0, 3.0, 4.0],
      [0.0, 3.0, 0.0, 0.0],
      [0.0, 0.0, 3.0, 0.0],
      [0.0, 0.0, 0.0, 3.0]]

    glMatrixMode(GL_MODELVIEW)
    glLoadTransposeMatrixfARB(m_a)
    assert_each_in_delta m_a, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB)

    glLoadTransposeMatrixdARB(m_b)
    assert_each_in_delta m_b, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB)

    glLoadIdentity()
    glMultTransposeMatrixfARB(m_a)
    assert_each_in_delta m_a, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB)

    glLoadIdentity()
    glMultTransposeMatrixdARB(m_b)
    assert_each_in_delta m_b, glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB)

    # 2
    m = Matrix.rows([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    glMatrixMode(GL_MODELVIEW)
    glLoadTransposeMatrixfARB(m)
    assert_each_in_delta m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX)
    glLoadIdentity()
    glLoadTransposeMatrixdARB(m)
    assert_each_in_delta m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX)
    glLoadIdentity()
    glMultTransposeMatrixfARB(m)
    assert_each_in_delta m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX)
    glLoadIdentity()
    glMultTransposeMatrixdARB(m)
    assert_each_in_delta m.to_a.transpose, glGetDoublev(GL_MODELVIEW_MATRIX)

    assert_raises ArgumentError do glLoadTransposeMatrixfARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glLoadTransposeMatrixdARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glMultTransposeMatrixfARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glMultTransposeMatrixdARB([1, 2, 3, 4]) end
  end

  def test_gl_arb_multisample
    supported? "GL_ARB_multisample"
    glSampleCoverageARB(0.5, GL_FALSE)
    assert_equal 0.5, glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB)
    assert_equal false, glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB)
    glSampleCoverageARB(1.0, GL_TRUE)
    assert_equal 1.0, glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB)
    assert_equal true, glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB)
  end

  def test_gl_arb_color_buffer_float
    supported? "GL_ARB_color_buffer_float"
    glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_FIXED_ONLY_ARB)
    assert_equal GL_FIXED_ONLY_ARB, glGetIntegerv(GL_CLAMP_VERTEX_COLOR_ARB)

    glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_TRUE)
    assert_equal GL_TRUE, glGetBooleanv(GL_CLAMP_VERTEX_COLOR_ARB)
  end

  def test_gl_arb_vertex_program
    supported? "GL_ARB_vertex_program"

    assert_equal(false, glIsProgramARB(0))
    programs = glGenProgramsARB(1)
    assert_equal(1, programs.size)

    program = "!!ARBvp1.0\nTEMP vv;\nEND"

    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, programs[0])
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, program)
    assert_equal program, glGetProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_STRING_ARB)
    assert_equal(glIsProgramARB(programs[0]), true)

    assert_equal program.size, glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_LENGTH_ARB)
    assert_equal programs[0], glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB)

    glEnableVertexAttribArrayARB(1)
    assert_equal GL_TRUE, glGetVertexAttribivARB(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB)
    glDisableVertexAttribArrayARB(1)
    assert_equal GL_FALSE, glGetVertexAttribivARB(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB)

    glVertexAttribPointerARB(1, 2, GL_FLOAT, GL_FALSE, 0, [1, 1].pack("f*"))
    assert_each_in_delta([1, 1], glGetVertexAttribPointervARB(1).unpack("f*"))

    glProgramEnvParameter4dARB(GL_VERTEX_PROGRAM_ARB, 1, 1, 2, 3, 4)
    assert_equal([1, 2, 3, 4], glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramEnvParameter4fARB(GL_VERTEX_PROGRAM_ARB, 1, 5, 6, 7, 8)
    assert_equal([5, 6, 7, 8], glGetProgramEnvParameterfvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramEnvParameter4dvARB(GL_VERTEX_PROGRAM_ARB, 1, [1, 2, 3, 4])
    assert_equal([1, 2, 3, 4], glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramEnvParameter4fvARB(GL_VERTEX_PROGRAM_ARB, 1, [5, 6, 7, 8])
    assert_equal([5, 6, 7, 8], glGetProgramEnvParameterfvARB(GL_VERTEX_PROGRAM_ARB, 1))

    glProgramLocalParameter4dARB(GL_VERTEX_PROGRAM_ARB, 1, 1, 2, 3, 4)
    assert_equal([1, 2, 3, 4], glGetProgramLocalParameterdvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 1, 5, 6, 7, 8)
    assert_equal([5, 6, 7, 8], glGetProgramLocalParameterfvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramLocalParameter4dvARB(GL_VERTEX_PROGRAM_ARB, 1, [1, 2, 3, 4])
    assert_equal([1, 2, 3, 4], glGetProgramLocalParameterdvARB(GL_VERTEX_PROGRAM_ARB, 1))
    glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB, 1, [5, 6, 7, 8])
    assert_equal([5, 6, 7, 8], glGetProgramLocalParameterfvARB(GL_VERTEX_PROGRAM_ARB, 1))

    glVertexAttrib1dARB(1, 1)
    assert_equal(1, glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])
    glVertexAttrib1fARB(1, 2)
    assert_equal(2, glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])
    glVertexAttrib1sARB(1, 3)
    assert_equal(3, glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])
    glVertexAttrib1dvARB(1, [1])
    assert_equal(1, glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])
    glVertexAttrib1fvARB(1, [2])
    assert_equal(2, glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])
    glVertexAttrib1svARB(1, [3])
    assert_equal(3, glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0])

    glVertexAttrib2dARB(1, 1, 2)
    assert_equal([1, 2], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])
    glVertexAttrib2fARB(1, 2, 3)
    assert_equal([2, 3], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])
    glVertexAttrib2sARB(1, 3, 4)
    assert_equal([3, 4], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])
    glVertexAttrib2dvARB(1, [1, 2])
    assert_equal([1, 2], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])
    glVertexAttrib2fvARB(1, [2, 3])
    assert_equal([2, 3], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])
    glVertexAttrib2svARB(1, [3, 4])
    assert_equal([3, 4], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2])

    glVertexAttrib3dARB(1, 1, 2, 3)
    assert_equal([1, 2, 3], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])
    glVertexAttrib3fARB(1, 2, 3, 4)
    assert_equal([2, 3, 4], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])
    glVertexAttrib3sARB(1, 3, 4, 5)
    assert_equal([3, 4, 5], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])
    glVertexAttrib3dvARB(1, [1, 2, 3])
    assert_equal([1, 2, 3], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])
    glVertexAttrib3fvARB(1, [2, 3, 4])
    assert_equal([2, 3, 4], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])
    glVertexAttrib3svARB(1, [3, 4, 5])
    assert_equal([3, 4, 5], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3])

    glVertexAttrib4dARB(1, 1, 2, 3, 4)
    assert_equal([1, 2, 3, 4], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4fARB(1, 2, 3, 4, 5)
    assert_equal([2, 3, 4, 5], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4sARB(1, 3, 4, 5, 6)
    assert_equal([3, 4, 5, 6], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4dvARB(1, [1, 2, 3, 4])
    assert_equal([1, 2, 3, 4], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4fvARB(1, [2, 3, 4, 5])
    assert_equal([2, 3, 4, 5], glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4svARB(1, [3, 4, 5, 6])
    assert_equal([3, 4, 5, 6], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])


    glVertexAttrib4bvARB(1, [1, 2, 3, 4])
    assert_equal([1, 2, 3, 4], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4ivARB(1, [2, 3, 4, 5])
    assert_equal([2, 3, 4, 5], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4ubvARB(1, [3, 4, 5, 6])
    assert_equal([3, 4, 5, 6], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4uivARB(1, [1, 2, 3, 4])
    assert_equal([1, 2, 3, 4], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4usvARB(1, [2, 3, 4, 5])
    assert_equal([2, 3, 4, 5], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])

    glVertexAttrib4NbvARB(1, [0, 2**7-1, 0, 2**7-1])
    assert_equal([0, 1, 0, 1], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4NivARB(1, [2**31-1, 0, 2**31-1, 0])
    assert_equal([1, 0, 1, 0], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4NsvARB(1, [0, 2**15-1, 0, 2**15-1])
    assert_equal([0, 1, 0, 1], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])

    glVertexAttrib4NubARB(1, 2**8-1, 0, 2**8-1, 0)
    assert_equal([1, 0, 1, 0], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])

    glVertexAttrib4NubvARB(1, [0, 2**8-1, 0, 2**8-1])
    assert_equal([0, 1, 0, 1], glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4NuivARB(1, [2**32-1, 0, 2**32-1, 0])
    assert_equal([1, 0, 1, 0], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])
    glVertexAttrib4NusvARB(1, [0, 2**16-1, 0, 2**16-1])
    assert_equal([0, 1, 0, 1], glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 4])

    glDeleteProgramsARB(programs)
  end

  def test_gl_arb_windowpos
    supported? "GL_ARB_window_pos"
    # 2
    glWindowPos2dARB(1.0, 2.0)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2dvARB([2.0, 1.0])
    assert_each_in_delta([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2fARB(1.0, 2.0)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2fvARB([2.0, 1.0])
    assert_each_in_delta([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2iARB(1, 2)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2ivARB([2, 1])
    assert_each_in_delta([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2sARB(1, 2)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2svARB([2, 1])
    assert_each_in_delta([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    # 3
    glWindowPos3dARB(1.0, 2.0, 0.5)
    assert_each_in_delta([1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3dvARB([3.0, 2.0, 1.0])
    assert_each_in_delta([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3fARB(1.0, 2.0, 0.5)
    assert_each_in_delta([1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3fvARB([3.0, 2.0, 1.0])
    assert_each_in_delta([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3iARB(1, 2, 0)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3ivARB([3, 2, 1])
    assert_each_in_delta([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3sARB(1, 2, 0)
    assert_each_in_delta([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3svARB([3, 2, 1])
    assert_each_in_delta([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
  end

  def test_gl_arb_pointparameter
    supported? "GL_ARB_point_parameters"
    glPointParameterfARB(GL_POINT_SIZE_MIN, 1.0)
    assert_in_delta 1.0, glGetDoublev(GL_POINT_SIZE_MIN)

    glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION, [1, 0, 1])
    assert_each_in_delta([1, 0, 1], glGetDoublev(GL_POINT_DISTANCE_ATTENUATION))
  end

  def test_gl_arb_occlusion_query
    supported? "GL_ARB_occlusion_query"

    queries = glGenQueriesARB(2)
    assert_equal(2, queries.size)

    glBeginQueryARB(GL_SAMPLES_PASSED, queries[1])
    assert_equal(true, glIsQueryARB(queries[1]))

    glEndQueryARB(GL_SAMPLES_PASSED)
    r = glGetQueryObjectivARB(queries[1], GL_QUERY_RESULT_AVAILABLE)
    assert(r==GL_TRUE || r==GL_FALSE)
    assert(glGetQueryObjectuivARB(queries[1], GL_QUERY_RESULT)>=0)

    glDeleteQueriesARB(queries)
    assert_equal(false, glIsQueryARB(queries[1]))
  end

  def test_gl_arb_shader_objects
    supported? "GL_ARB_shader_objects"

    vertex_shader_source = "void main() { gl_Position = ftransform();}\n"

    program = glCreateProgramObjectARB()

    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)

    glShaderSourceARB(vs, vertex_shader_source)
    assert_equal vertex_shader_source, glGetShaderSourceARB(vs)

    assert_equal GL_SHADER_OBJECT_ARB, glGetObjectParameterivARB(vs, GL_OBJECT_TYPE_ARB)
    assert_equal GL_SHADER_OBJECT_ARB, glGetObjectParameterfvARB(vs, GL_OBJECT_TYPE_ARB)
    assert_equal GL_VERTEX_SHADER, glGetObjectParameterfvARB(vs, GL_OBJECT_SUBTYPE_ARB)
    glCompileShaderARB(vs)
    assert_equal GL_TRUE, glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB)

    vslog = glGetInfoLogARB(vs)
    assert_equal(String, vslog.class)

    glAttachObjectARB(program, vs)
    assert_equal vs, glGetAttachedObjectsARB(program)

    glLinkProgramARB(program)
    assert glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)

    glValidateProgramARB(program)
    assert glGetObjectParameterivARB(program, GL_OBJECT_VALIDATE_STATUS_ARB)

    glUseProgramObjectARB(program)
    assert_equal program, glGetIntegerv(GL_CURRENT_PROGRAM)

    assert_equal program, glGetHandleARB(GL_PROGRAM_OBJECT_ARB)

    glUseProgramObjectARB(0)

    glDetachObjectARB(program, vs)

    glDeleteObjectARB(vs)
    glDeleteObjectARB(program)
  end

  def test_gl_arb_shader_objects_2
    supported? "GL_ARB_shader_objects"

    vertex_shader_source = <<-SHADER
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
  gl_Position = ftransform() * test[0] *
      testvec1 * testvec2.x * testvec3.x * testvec4.x *
      float(testivec1) * float(testivec2.x) * float(testivec3.x) * float(testivec4.x);
}
    SHADER

    program = glCreateProgramObjectARB()
    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
    glShaderSourceARB(vs, vertex_shader_source)

    glCompileShaderARB(vs)
    assert_equal GL_TRUE, glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB)

    glAttachObjectARB(program, vs)

    glLinkProgramARB(program)
    assert_equal GL_TRUE, glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)

    glUseProgramObjectARB(program)

    assert((tv1l = glGetUniformLocationARB(program, "testvec1"))>=0)
    assert((tv2l = glGetUniformLocationARB(program, "testvec2"))>=0)
    assert((tv3l = glGetUniformLocationARB(program, "testvec3"))>=0)
    assert((tv4l = glGetUniformLocationARB(program, "testvec4"))>=0)
    assert((tv1il = glGetUniformLocationARB(program, "testivec1"))>=0)
    assert((tv2il = glGetUniformLocationARB(program, "testivec2"))>=0)
    assert((tv3il = glGetUniformLocationARB(program, "testivec3"))>=0)
    assert((tv4il = glGetUniformLocationARB(program, "testivec4"))>=0)

    ##

    assert_equal([1, GL_INT, "testivec1"], glGetActiveUniformARB(program, tv1il))

    ## f
    glUniform1fARB(tv1l, 2.0)
    assert_equal 2.0, glGetUniformfvARB(program, tv1l)
    glUniform2fARB(tv2l, 2.0, 2.0)
    assert_equal([2.0, 2.0], glGetUniformfvARB(program, tv2l))
    glUniform3fARB(tv3l, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0], glGetUniformfvARB(program, tv3l))
    glUniform4fARB(tv4l, 2.0, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0, 2.0], glGetUniformfvARB(program, tv4l))
    # i
    glUniform1iARB(tv1il, 3)
    assert_equal 3, glGetUniformivARB(program, tv1il)
    glUniform2iARB(tv2il, 3, 3)
    assert_equal([3, 3], glGetUniformivARB(program, tv2il))
    glUniform3iARB(tv3il, 3, 3, 3)
    assert_equal([3, 3, 3], glGetUniformivARB(program, tv3il))
    glUniform4iARB(tv4il, 3, 3, 3, 3)
    assert_equal([3, 3, 3, 3], glGetUniformivARB(program, tv4il))
    # fv
    glUniform1fvARB(tv1l, [3.0])
    assert_equal 3.0, glGetUniformfvARB(program, tv1l)
    glUniform2fvARB(tv2l, [3.0, 3.0])
    assert_equal([3.0, 3.0], glGetUniformfvARB(program, tv2l))
    glUniform3fvARB(tv3l, [3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0], glGetUniformfvARB(program, tv3l))
    glUniform4fvARB(tv4l, [3.0, 3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0, 3.0], glGetUniformfvARB(program, tv4l))
    # iv
    glUniform1ivARB(tv1il, [2])
    assert_equal 2, glGetUniformivARB(program, tv1il)
    glUniform2ivARB(tv2il, [2, 2])
    assert_equal([2, 2], glGetUniformivARB(program, tv2il))
    glUniform3ivARB(tv3il, [2, 2, 2])
    assert_equal([2, 2, 2], glGetUniformivARB(program, tv3il))
    glUniform4ivARB(tv4il, [2, 2, 2, 2])
    assert_equal([2, 2, 2, 2], glGetUniformivARB(program, tv4il))

    glDeleteObjectARB(vs)
    glDeleteObjectARB(program)
  end

  def test_gl_arb_shader_objects_3
    supported? "GL_ARB_shader_objects"

    vertex_shader_source = "uniform mat2 testmat2; uniform mat3 testmat3; uniform mat4 testmat4; void main() { gl_Position = gl_Vertex * testmat4[0].x * testmat3[0].x * testmat2[0].x;}"

    program = glCreateProgramObjectARB()
    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
    glShaderSourceARB(vs, vertex_shader_source)

    glCompileShaderARB(vs)
    assert_equal GL_TRUE, glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB)

    glAttachObjectARB(program, vs)

    glLinkProgramARB(program)
    assert_equal GL_TRUE, glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)

    glUseProgramObjectARB(program)

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

    glUniformMatrix2fvARB(uniforms['testmat2'], GL_TRUE, [0, 1, 2, 3])
    assert_each_in_delta([0, 2, 1, 3],
                         glGetUniformfvARB(program, uniforms['testmat2']))

    glUniformMatrix3fvARB(uniforms['testmat3'], GL_TRUE,
                          [0, 1, 2, 3, 4, 5, 6, 7, 8])
    assert_each_in_delta([0, 3, 6, 1, 4, 7, 2, 5, 8],
                         glGetUniformfvARB(program, uniforms['testmat3']))

    glUniformMatrix4fvARB(uniforms['testmat4'], GL_TRUE,
                          [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
    assert_each_in_delta([0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15],
                         glGetUniformfvARB(program, uniforms['testmat4']))

    glDeleteObjectARB(vs)
    glDeleteObjectARB(program)
  end

  def test_gl_arb_vertex_shader
    supported? "GL_ARB_vertex_shader"

    vertex_shader_source = <<-SHADER
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
  gl_Position = ftransform() * test[0] *
      testvec1 * testvec2.x * testvec3.x * testvec4.x *
      float(testivec1) * float(testivec2.x) * float(testivec3.x) * float(testivec4.x);
}
    SHADER

    program = glCreateProgramObjectARB()
    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
    glShaderSourceARB(vs, vertex_shader_source)

    glCompileShaderARB(vs)
    assert(glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB),
           glGetInfoLogARB(vs))

    glAttachObjectARB(program, vs)

    glBindAttribLocationARB(program, 2, "test")

    glLinkProgramARB(program)
    assert_equal GL_TRUE, glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)

    glUseProgramObjectARB(program)

    assert_equal 2, glGetAttribLocationARB(program, "test")
    assert_equal [1, GL_FLOAT_VEC4, "gl_Vertex"], glGetActiveAttribARB(program, 0)

    glDeleteObjectARB(vs)
    glDeleteObjectARB(program)
  end
end
