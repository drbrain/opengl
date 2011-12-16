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
    assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_a)

    glLoadTransposeMatrixdARB(m_b)
    assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_b)

    glLoadIdentity()
    glMultTransposeMatrixfARB(m_a)
    assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_a)

    glLoadIdentity()
    glMultTransposeMatrixdARB(m_b)
    assert_equal(glGetDoublev(GL_TRANSPOSE_MODELVIEW_MATRIX_ARB), m_b)

    # 2
    m = Matrix.rows([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
    glMatrixMode(GL_MODELVIEW)
    glLoadTransposeMatrixfARB(m)
    assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
    glLoadIdentity()
    glLoadTransposeMatrixdARB(m)
    assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
    glLoadIdentity()
    glMultTransposeMatrixfARB(m)
    assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)
    glLoadIdentity()
    glMultTransposeMatrixdARB(m)
    assert_equal(glGetDoublev(GL_MODELVIEW_MATRIX), m.to_a.transpose)

    assert_raises ArgumentError do glLoadTransposeMatrixfARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glLoadTransposeMatrixdARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glMultTransposeMatrixfARB([1, 2, 3, 4]) end
    assert_raises ArgumentError do glMultTransposeMatrixdARB([1, 2, 3, 4]) end
  end

  def test_gl_arb_multisample
    supported? "GL_ARB_multisample"
    glSampleCoverageARB(0.5, GL_FALSE)
    assert_equal(glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB), 0.5)
    assert_equal(glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB), false)
    glSampleCoverageARB(1.0, GL_TRUE)
    assert_equal(glGetFloatv(GL_SAMPLE_COVERAGE_VALUE_ARB), 1.0)
    assert_equal(glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT_ARB), true)
  end

  def test_gl_arb_color_buffer_float
    supported? "GL_ARB_color_buffer_float"
    glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_FIXED_ONLY_ARB)
    assert_equal(glGetIntegerv(GL_CLAMP_VERTEX_COLOR_ARB), GL_FIXED_ONLY_ARB)

    glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_TRUE)
    assert_equal(glGetBooleanv(GL_CLAMP_VERTEX_COLOR_ARB), GL_TRUE)
  end

  def test_gl_arb_vertex_program
    supported? "GL_ARB_vertex_program"

    assert_equal(glIsProgramARB(0), false)
    programs = glGenProgramsARB(1)
    assert_equal(programs.size, 1)

    program = "!!ARBvp1.0\nTEMP vv;\nEND"

    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, programs[0])
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, program)
    assert_equal(glGetProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_STRING_ARB), program)
    assert_equal(glIsProgramARB(programs[0]), true)	

    assert_equal(glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_LENGTH_ARB), program.size)
    assert_equal(glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB), programs[0])

    glEnableVertexAttribArrayARB(1)
    assert_equal(glGetVertexAttribivARB(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB), GL_TRUE)
    glDisableVertexAttribArrayARB(1)
    assert_equal(glGetVertexAttribivARB(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB), GL_FALSE)

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
    assert_equal(glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 1)
    glVertexAttrib1fARB(1, 2)
    assert_equal(glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 2)
    glVertexAttrib1sARB(1, 3)
    assert_equal(glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 3)
    glVertexAttrib1dvARB(1, [1])
    assert_equal(glGetVertexAttribdvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 1)
    glVertexAttrib1fvARB(1, [2])
    assert_equal(glGetVertexAttribfvARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 2)
    glVertexAttrib1svARB(1, [3])
    assert_equal(glGetVertexAttribivARB(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 3)

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
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2dvARB([2.0, 1.0])
    assert_equal([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2fARB(1.0, 2.0)
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2fvARB([2.0, 1.0])
    assert_equal([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2iARB(1, 2)
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2ivARB([2, 1])
    assert_equal([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2sARB(1, 2)
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos2svARB([2, 1])
    assert_equal([2, 1, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))

    # 3
    glWindowPos3dARB(1.0, 2.0, 0.5)
    assert_equal([1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3dvARB([3.0, 2.0, 1.0])
    assert_equal([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3fARB(1.0, 2.0, 0.5)
    assert_equal([1, 2, 0.5, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3fvARB([3.0, 2.0, 1.0])
    assert_equal([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3iARB(1, 2, 0)
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3ivARB([3, 2, 1])
    assert_equal([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3sARB(1, 2, 0)
    assert_equal([1, 2, 0, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
    glWindowPos3svARB([3, 2, 1])
    assert_equal([3, 2, 1, 1], glGetDoublev(GL_CURRENT_RASTER_POSITION))
  end

  def test_gl_arb_pointparameter
    supported? "GL_ARB_point_parameters"
    glPointParameterfARB(GL_POINT_SIZE_MIN, 1.0)
    assert_equal(glGetDoublev(GL_POINT_SIZE_MIN), 1.0)

    glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION, [1, 0, 1])
    assert_equal([1, 0, 1], glGetDoublev(GL_POINT_DISTANCE_ATTENUATION))
  end

  def test_gl_arb_occlusion_query
    supported? "GL_ARB_occlusion_query"

    queries = glGenQueriesARB(2)
    assert_equal(queries.size, 2)

    glBeginQueryARB(GL_SAMPLES_PASSED, queries[1])
    assert_equal(glIsQueryARB(queries[1]), true)

    glEndQueryARB(GL_SAMPLES_PASSED)
    r = glGetQueryObjectivARB(queries[1], GL_QUERY_RESULT_AVAILABLE)
    assert(r==GL_TRUE || r==GL_FALSE)
    assert(glGetQueryObjectuivARB(queries[1], GL_QUERY_RESULT)>=0)

    glDeleteQueriesARB(queries)
    assert_equal(glIsQueryARB(queries[1]), false)
  end

  def test_gl_arb_shader_objects
    supported? "GL_ARB_shader_objects"

    vertex_shader_source = "void main() { gl_Position = ftransform();}\n"

    program = glCreateProgramObjectARB()

    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)

    glShaderSourceARB(vs, vertex_shader_source)
    assert_equal(glGetShaderSourceARB(vs), vertex_shader_source)

    assert_equal(glGetObjectParameterivARB(vs, GL_OBJECT_TYPE_ARB), GL_SHADER_OBJECT_ARB)
    assert_equal(glGetObjectParameterfvARB(vs, GL_OBJECT_TYPE_ARB), GL_SHADER_OBJECT_ARB)
    assert_equal(glGetObjectParameterfvARB(vs, GL_OBJECT_SUBTYPE_ARB), GL_VERTEX_SHADER)
    glCompileShaderARB(vs)
    assert_equal(glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB), GL_TRUE)

    vslog = glGetInfoLogARB(vs)
    assert_equal(vslog.class, String)

    glAttachObjectARB(program, vs)
    assert_equal(glGetAttachedObjectsARB(program), vs)

    glLinkProgramARB(program)
    assert glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)

    glValidateProgramARB(program)
    assert glGetObjectParameterivARB(program, GL_OBJECT_VALIDATE_STATUS_ARB)

    glUseProgramObjectARB(program)
    assert_equal(glGetIntegerv(GL_CURRENT_PROGRAM), program)

    assert_equal(glGetHandleARB(GL_PROGRAM_OBJECT_ARB), program)

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
  testvec1;
  test;
  testvec2.x;
  testvec3.x;
  testivec1;
  testivec2.x;
  testivec3.x;
  testivec4.x;
  testvec4;

  gl_Position = ftransform();
}
    SHADER

    program = glCreateProgramObjectARB()
    vs = glCreateShaderObjectARB(GL_VERTEX_SHADER)
    glShaderSourceARB(vs, vertex_shader_source)

    glCompileShaderARB(vs)
    assert_equal(glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB), GL_TRUE)

    glAttachObjectARB(program, vs)

    glLinkProgramARB(program)
    assert_equal(glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB), GL_TRUE)

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
    assert_equal(glGetUniformfvARB(program, tv1l), 2.0)
    glUniform2fARB(tv2l, 2.0, 2.0)
    assert_equal([2.0, 2.0], glGetUniformfvARB(program, tv2l))
    glUniform3fARB(tv3l, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0], glGetUniformfvARB(program, tv3l))
    glUniform4fARB(tv4l, 2.0, 2.0, 2.0, 2.0)
    assert_equal([2.0, 2.0, 2.0, 2.0], glGetUniformfvARB(program, tv4l))
    # i 
    glUniform1iARB(tv1il, 3)
    assert_equal(glGetUniformivARB(program, tv1il), 3)
    glUniform2iARB(tv2il, 3, 3)
    assert_equal([3, 3], glGetUniformivARB(program, tv2il))
    glUniform3iARB(tv3il, 3, 3, 3)
    assert_equal([3, 3, 3], glGetUniformivARB(program, tv3il))
    glUniform4iARB(tv4il, 3, 3, 3, 3)
    assert_equal([3, 3, 3, 3], glGetUniformivARB(program, tv4il))
    # fv
    glUniform1fvARB(tv1l, [3.0])
    assert_equal(glGetUniformfvARB(program, tv1l), 3.0)
    glUniform2fvARB(tv2l, [3.0, 3.0])
    assert_equal([3.0, 3.0], glGetUniformfvARB(program, tv2l))
    glUniform3fvARB(tv3l, [3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0], glGetUniformfvARB(program, tv3l))
    glUniform4fvARB(tv4l, [3.0, 3.0, 3.0, 3.0])
    assert_equal([3.0, 3.0, 3.0, 3.0], glGetUniformfvARB(program, tv4l))
    # iv
    glUniform1ivARB(tv1il, [2])
    assert_equal(glGetUniformivARB(program, tv1il), 2)
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
    assert_equal(glGetObjectParameterivARB(vs, GL_OBJECT_COMPILE_STATUS_ARB), GL_TRUE)

    glAttachObjectARB(program, vs)

    glLinkProgramARB(program)
    assert_equal(glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB), GL_TRUE)

    glUseProgramObjectARB(program)

    tm2l = glGetUniformLocation(program, "testmat2")
    refute_equal -1, tm2l, "testmat2 missing!"
    tm3l = glGetUniformLocation(program, "testmat3")
    refute_equal -1, tm3l, "testmat3 missing!"
    tm4l = glGetUniformLocation(program, "testmat4")
    refute_equal -1, tm4l, "testmat4 missing!"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tm2l).last != "testmat2"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tm3l).last != "testmat3"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tm4l).last != "testmat4"

    glUniformMatrix2fvARB(tm2l, GL_TRUE, [0, 1, 1, 0])
    assert_each_in_delta([0, 1, 1, 0], glGetUniformfvARB(program, tm2l))

    glUniformMatrix3fvARB(tm3l, GL_TRUE, [0, 1, 0, 1, 0, 1, 0, 1, 0])
    assert_each_in_delta([0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
                         glGetUniformfvARB(program, tm3l))

    glUniformMatrix4fvARB(tm4l, GL_TRUE, [0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0])
    assert_each_in_delta([0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0],
                         glGetUniformfvARB(program, tm4l))

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
  testvec1;
  test;
  testvec2.x;
  testvec3.x;
  testivec1;
  testivec2.x;
  testivec3.x;
  testivec4.x;
  testvec4;

  gl_Position = ftransform();
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
    assert_equal(glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB), GL_TRUE)

    glUseProgramObjectARB(program)

    assert_equal 2, glGetAttribLocationARB(program, "test")
    assert_equal [1, GL_FLOAT_VEC4, "gl_Vertex"], glGetActiveAttribARB(program, 0)

    glDeleteObjectARB(vs)
    glDeleteObjectARB(program)
  end

end

