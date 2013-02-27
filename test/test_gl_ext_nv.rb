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

class TestGlExtNv < OpenGL::TestCase

  def test_gl_nv_vertex_program
    supported?("GL_NV_vertex_program")

    assert_equal(false, glIsProgramNV(0))
    programs = glGenProgramsNV(2)
    assert_equal(2, programs.size)

    program = "!!VSP1.0\nEND"

    glBindProgramNV(GL_VERTEX_PROGRAM_NV, programs[1])
    glLoadProgramNV(GL_VERTEX_STATE_PROGRAM_NV, programs[0], program)
    assert_equal(program, glGetProgramStringNV(programs[0], GL_PROGRAM_STRING_NV))
    assert_equal(true, glIsProgramNV(programs[0]))

    assert_equal(program.size, glGetProgramivNV(programs[0],GL_PROGRAM_LENGTH_NV))

    glVertexAttribPointerNV(1,2,GL_FLOAT,0,[1,1].pack("f*"))
    assert_equal([1,1].pack("f*"), glGetVertexAttribPointervNV(1))

    glExecuteProgramNV(GL_VERTEX_STATE_PROGRAM_NV,programs[0],[1,1,1,1])

    glProgramParameter4dNV(GL_VERTEX_PROGRAM_NV,1, 1,2,3,4)
    assert_equal([1,2,3,4], glGetProgramParameterdvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))
    glProgramParameter4fNV(GL_VERTEX_PROGRAM_NV,1, 5,6,7,8)
    assert_equal([5,6,7,8], glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))
    glProgramParameter4dvNV(GL_VERTEX_PROGRAM_NV,1, [1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramParameterdvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))
    glProgramParameter4fvNV(GL_VERTEX_PROGRAM_NV,1, [5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))

    glProgramParameters4fvNV(GL_VERTEX_PROGRAM_NV,1, [1,2,3,4,5,6,7,8])
    assert_equal([1,2,3,4], glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))
    assert_equal([5,6,7,8], glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV,2,GL_PROGRAM_PARAMETER_NV))

    glProgramParameters4dvNV(GL_VERTEX_PROGRAM_NV,1, [8,7,6,5,4,3,2,1])
    assert_equal([8,7,6,5], glGetProgramParameterdvNV(GL_VERTEX_PROGRAM_NV,1,GL_PROGRAM_PARAMETER_NV))
    assert_equal([4,3,2,1], glGetProgramParameterdvNV(GL_VERTEX_PROGRAM_NV,2,GL_PROGRAM_PARAMETER_NV))


    glVertexAttrib1dNV(1,1)
    assert_equal(1, glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttrib1fNV(1,2)
    assert_equal(2, glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttrib1sNV(1,3)
    assert_equal(3, glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttrib1dvNV(1,[1])
    assert_equal(1, glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttrib1fvNV(1,[2])
    assert_equal(2, glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttrib1svNV(1,[3])
    assert_equal(3, glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0])

    glVertexAttrib2dNV(1,1,2)
    assert_equal([1,2], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttrib2fNV(1,2,3)
    assert_equal([2,3], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttrib2sNV(1,3,4)
    assert_equal([3,4], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttrib2dvNV(1,[1,2])
    assert_equal([1,2], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttrib2fvNV(1,[2,3])
    assert_equal([2,3], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttrib2svNV(1,[3,4])
    assert_equal([3,4], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,2])

    glVertexAttrib3dNV(1,1,2,3)
    assert_equal([1,2,3], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttrib3fNV(1,2,3,4)
    assert_equal([2,3,4], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttrib3sNV(1,3,4,5)
    assert_equal([3,4,5], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttrib3dvNV(1,[1,2,3])
    assert_equal([1,2,3], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttrib3fvNV(1,[2,3,4])
    assert_equal([2,3,4], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttrib3svNV(1,[3,4,5])
    assert_equal([3,4,5], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,3])

    glVertexAttrib4dNV(1,1,2,3,4)
    assert_equal([1,2,3,4], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4fNV(1,2,3,4,5)
    assert_equal([2,3,4,5], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4sNV(1,3,4,5,6)
    assert_equal([3,4,5,6], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4dvNV(1,[1,2,3,4])
    assert_equal([1,2,3,4], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4fvNV(1,[2,3,4,5])
    assert_equal([2,3,4,5], glGetVertexAttribfvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4svNV(1,[3,4,5,6])
    assert_equal([3,4,5,6], glGetVertexAttribivNV(1,GL_CURRENT_ATTRIB_NV)[0,4])

    glVertexAttrib4ubNV(1,2**8-1,0,2**8-1,0)
    assert_equal([1,0,1,0], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttrib4ubvNV(1,[0,2**8-1,0,2**8-1])
    assert_equal([0,1,0,1], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])

    glVertexAttribs1dvNV(1,[1,2])
    assert_equal(1, glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    assert_equal(2, glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttribs1fvNV(1,[3,4])
    assert_equal(3, glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    assert_equal(4, glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0])
    glVertexAttribs1svNV(1,[5,6])
    assert_equal(5, glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0])
    assert_equal(6, glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0])

    glVertexAttribs2dvNV(1,[1,2,3,4])
    assert_equal([1,2], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    assert_equal([3,4], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttribs2fvNV(1,[3,4,5,6])
    assert_equal([3,4], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    assert_equal([5,6], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,2])
    glVertexAttribs2svNV(1,[5,6,7,8])
    assert_equal([5,6], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,2])
    assert_equal([7,8], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,2])

    glVertexAttribs3dvNV(1,[1,2,3,4,5,6])
    assert_equal([1,2,3], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    assert_equal([4,5,6], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttribs3fvNV(1,[3,4,5,6,7,8])
    assert_equal([3,4,5], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    assert_equal([6,7,8], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,3])
    glVertexAttribs3svNV(1,[5,6,7,8,9,10])
    assert_equal([5,6,7], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,3])
    assert_equal([8,9,10], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,3])

    glVertexAttribs4dvNV(1,[1,2,3,4,5,6,7,8])
    assert_equal([1,2,3,4], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    assert_equal([5,6,7,8], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttribs4fvNV(1,[3,4,5,6,7,8,9,10])
    assert_equal([3,4,5,6], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    assert_equal([7,8,9,10], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttribs4svNV(1,[5,6,7,8,9,10,11,12])
    assert_equal([5,6,7,8], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    assert_equal([9,10,11,12], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,4])
    glVertexAttribs4ubvNV(1,[2**8-1,0,2**8-1,0,2**8-1,0,2**8-1,0])
    assert_equal([1,0,1,0], glGetVertexAttribdvNV(1,GL_CURRENT_ATTRIB_NV)[0,4])
    assert_equal([1,0,1,0], glGetVertexAttribdvNV(2,GL_CURRENT_ATTRIB_NV)[0,4])

    glTrackMatrixNV(GL_VERTEX_PROGRAM_NV, 4, GL_MATRIX0_NV, GL_IDENTITY_NV);
    assert_equal(GL_MATRIX0_NV, glGetTrackMatrixivNV(GL_VERTEX_PROGRAM_NV, 4, GL_TRACK_MATRIX_NV))

    glRequestResidentProgramsNV(programs[0])
    res = glAreProgramsResidentNV(programs[0])
    assert_equal(res.size,1)

    glDeleteProgramsNV(programs)
  end

  def test_gl_nv_fragment_program
    supported?("GL_NV_fragment_program")
    programs = glGenProgramsNV(1)
    program = "!!FP1.0\nDECLARE test = {0,0,0,0};\nEND"
    glBindProgramNV(GL_FRAGMENT_PROGRAM_NV, programs[0])
    glLoadProgramNV(GL_FRAGMENT_PROGRAM_NV, programs[0], program)

    glProgramNamedParameter4fNV(programs[0],"test",1,2,3,4)
    assert_equal([1,2,3,4], glGetProgramNamedParameterfvNV(programs[0],"test"))
    glProgramNamedParameter4dNV(programs[0],"test",5,6,7,8)
    assert_equal([5,6,7,8], glGetProgramNamedParameterdvNV(programs[0],"test"))
    glProgramNamedParameter4fvNV(programs[0],"test",[1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramNamedParameterfvNV(programs[0],"test"))
    glProgramNamedParameter4dvNV(programs[0],"test",[5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramNamedParameterdvNV(programs[0],"test"))

    glDeleteProgramsNV(programs)
  end

  def test_gl_nv_framebuffer_multisample_coverage
    supported?("GL_NV_framebuffer_multisample_coverage")
    rb = glGenRenderbuffersEXT(1)[0]

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,rb)
    glRenderbufferStorageMultisampleCoverageNV(GL_RENDERBUFFER_EXT,4,4, GL_RGBA,2,2)
    samples = glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_COVERAGE_SAMPLES_NV)
    assert_equal(4, samples)
    samples = glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_COLOR_SAMPLES_NV)
    assert_equal(4, samples)

    glDeleteRenderbuffersEXT(rb)
  end

  def test_gl_nv_fence
    supported?("GL_NV_fence")
    fences = glGenFencesNV(2)
    assert_equal(fences.size,2)

    glSetFenceNV(fences[0],GL_ALL_COMPLETED_NV)
    assert_equal(GL_ALL_COMPLETED_NV, glGetFenceivNV(fences[0],GL_FENCE_CONDITION_NV))
    assert_equal(true, glIsFenceNV(fences[0]))

    glFinishFenceNV(fences[0])
    assert_equal(true, glTestFenceNV(fences[0]))

    glDeleteFencesNV(fences)
  end

  def test_gl_nv_depth_buffer_float
    supported?("GL_NV_depth_buffer_float")
    glDepthRangedNV(0.1,0.2)
    assert_in_delta([0.1,0.2], glGetFloatv(GL_DEPTH_RANGE))
    glDepthBoundsdNV(0.1,0.2)
    assert_in_delta([0.1,0.2], glGetFloatv(GL_DEPTH_BOUNDS_EXT))
    glClearDepthdNV(0.3)
    assert_in_delta([0.3], [glGetDoublev(GL_DEPTH_CLEAR_VALUE)])
  end

  def test_gl_nv_occlusion_query
    supported?("GL_NV_occlusion_query")

    queries = glGenOcclusionQueriesNV(2)
    assert_equal(queries.size,2)

    glBeginOcclusionQueryNV(queries[0])
    assert_equal(true, glIsOcclusionQueryNV(queries[0]))

    glEndOcclusionQueryNV()
    r = glGetOcclusionQueryivNV(queries[0],GL_PIXEL_COUNT_AVAILABLE_NV)
    assert(r==GL_TRUE || r==GL_FALSE)
    assert(glGetOcclusionQueryuivNV(queries[0],GL_PIXEL_COUNT_NV)>=0)

    glDeleteOcclusionQueriesNV(queries)
    assert_equal(false, glIsOcclusionQueryNV(queries[1]))
  end

  def test_gl_nv_gpu_program4
    supported?(["GL_NV_gpu_program4","GL_ARB_vertex_program"])

    programs = glGenProgramsARB(1)
    program = "!!ARBvp1.0\nTEMP vv;\nEND"

    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, programs[0])
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, program)

    glProgramLocalParameterI4iNV(GL_VERTEX_PROGRAM_ARB,1, 1,2,3,4)
    assert_equal([1,2,3,4], glGetProgramLocalParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramLocalParameterI4uiNV(GL_VERTEX_PROGRAM_ARB,1, 5,6,7,8)
    assert_equal([5,6,7,8], glGetProgramLocalParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramLocalParameterI4ivNV(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramLocalParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramLocalParameterI4uivNV(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramLocalParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramLocalParametersI4ivNV(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramLocalParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramLocalParametersI4uivNV(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramLocalParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))

    glProgramEnvParameterI4iNV(GL_VERTEX_PROGRAM_ARB,1, 1,2,3,4)
    assert_equal([1,2,3,4], glGetProgramEnvParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramEnvParameterI4uiNV(GL_VERTEX_PROGRAM_ARB,1, 5,6,7,8)
    assert_equal([5,6,7,8], glGetProgramEnvParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramEnvParameterI4ivNV(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramEnvParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramEnvParameterI4uivNV(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramEnvParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramEnvParametersI4ivNV(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4])
    assert_equal([1,2,3,4], glGetProgramEnvParameterIivNV(GL_VERTEX_PROGRAM_ARB,1))
    glProgramEnvParametersI4uivNV(GL_VERTEX_PROGRAM_ARB,1, [5,6,7,8])
    assert_equal([5,6,7,8], glGetProgramEnvParameterIuivNV(GL_VERTEX_PROGRAM_ARB,1))

    glDeleteProgramsARB(programs)
  end

  def test_gl_nv_gpu_program4
    supported?(["GL_NV_gpu_program4","GL_EXT_framebuffer_object"])
    geometry_program = <<-EOP
!!NVgp4.0
PRIMITIVE_IN TRIANGLES;
PRIMITIVE_OUT TRIANGLE_STRIP;
VERTICES_OUT 1;
END
    EOP

    program_id = glGenProgramsARB(1)[0]
    glBindProgramARB(GL_GEOMETRY_PROGRAM_NV, program_id)
    glProgramStringARB(GL_GEOMETRY_PROGRAM_NV, GL_PROGRAM_FORMAT_ASCII_ARB, geometry_program);

    assert_equal(1, glGetProgramivARB(GL_GEOMETRY_PROGRAM_NV,GL_GEOMETRY_VERTICES_OUT_EXT))
    glProgramVertexLimitNV(GL_GEOMETRY_PROGRAM_NV, 2)
    assert_equal(2, glGetProgramivARB(GL_GEOMETRY_PROGRAM_NV,GL_GEOMETRY_VERTICES_OUT_EXT))

    #

    fbo = glGenFramebuffersEXT(1)[0]
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo)

    texture2d,texture3d,texture_cube = glGenTextures(3)
    glBindTexture(GL_TEXTURE_2D, texture2d)
    glBindTexture(GL_TEXTURE_3D, texture3d)
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cube)

    glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,texture2d, 0)
    assert_equal(texture2d, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT))
    assert_equal(0, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT))
    glFramebufferTextureLayerEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,texture3d, 0,1)
    assert_equal(texture3d, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT))
    assert_equal(0, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT))
    assert_equal(1, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER_EXT))

    glFramebufferTextureFaceEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,texture_cube,0,GL_TEXTURE_CUBE_MAP_POSITIVE_X)
    assert_equal(texture_cube, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT))
    assert_equal(0, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT))
    assert_equal(GL_TEXTURE_CUBE_MAP_POSITIVE_X, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT))

    glDeleteTextures([texture2d,texture3d])
    glDeleteFramebuffersEXT(fbo)
    glDeleteProgramsARB(program_id)
  end

  def test_gl_nv_primitive_restart
    supported?("GL_NV_primitive_restart")
    glBegin(GL_TRIANGLES)
    glPrimitiveRestartNV()
    glEnd
    glPrimitiveRestartIndexNV(2)
    assert_equal(glGetIntegerv(GL_PRIMITIVE_RESTART_INDEX_NV),2)
  end

  def test_gl_nv_point_sprite
    supported?("GL_NV_point_sprite")
    glPointParameteriNV(GL_POINT_SPRITE_R_MODE_NV, GL_ZERO)
    assert_equal(GL_ZERO, glGetIntegerv(GL_POINT_SPRITE_R_MODE_NV))
    glPointParameteriNV(GL_POINT_SPRITE_R_MODE_NV, GL_S)
    assert_equal(GL_S, glGetIntegerv(GL_POINT_SPRITE_R_MODE_NV))

    glPointParameterivNV(GL_POINT_SPRITE_R_MODE_NV, [GL_ZERO])
    assert_equal(GL_ZERO, glGetIntegerv(GL_POINT_SPRITE_R_MODE_NV))
    glPointParameterivNV(GL_POINT_SPRITE_R_MODE_NV, [GL_S])
    assert_equal(GL_S, glGetIntegerv(GL_POINT_SPRITE_R_MODE_NV))
  end
end
