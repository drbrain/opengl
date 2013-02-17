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

class TestGlExtExt < OpenGL::TestCase

  def teardown
    if Gl.is_available?("GL_EXT_framebuffer_object")
      glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0)
      glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0)
    end

    super
  end

  def test_gl_ext_polygon_offset
    supported?("GL_EXT_polygon_offset")

    glPolygonOffsetEXT(1.0, 2.0)
    assert_equal(glGetIntegerv(GL_POLYGON_OFFSET_FACTOR_EXT), 1.0)
    assert_equal(glGetIntegerv(GL_POLYGON_OFFSET_BIAS_EXT), 2.0)
  end

  def test_gl_ext_framebuffer_object
    supported?("GL_EXT_framebuffer_object")
    t = glGenTextures(3)
    glBindTexture(GL_TEXTURE_2D, t[0])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WINDOW_SIZE, WINDOW_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, nil)

    glBindTexture(GL_TEXTURE_1D, t[1])
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8, WINDOW_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, nil)

    glBindTexture(GL_TEXTURE_3D, t[2])
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, WINDOW_SIZE, WINDOW_SIZE, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nil)

    fb = glGenFramebuffersEXT(1)
    assert(fb.size==1)
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb[0])
    assert_equal(glIsFramebufferEXT(fb[0]), true)

    rb = glGenRenderbuffersEXT(1)
    assert(rb.size==1)
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb[0])
    assert_equal(glIsRenderbufferEXT(rb[0]), true)

    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, WINDOW_SIZE, WINDOW_SIZE)

    assert_equal WINDOW_SIZE, glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_WIDTH_EXT)
    assert_equal WINDOW_SIZE, glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_HEIGHT_EXT)
    assert_equal GL_DEPTH_COMPONENT24, glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_INTERNAL_FORMAT_EXT)


    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rb[0]);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, t[0], 0)

    status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)
    assert(status == GL_FRAMEBUFFER_COMPLETE_EXT || status == GL_FRAMEBUFFER_UNSUPPORTED_EXT)

    assert_equal GL_TEXTURE, glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT)

    glGenerateMipmapEXT(GL_TEXTURE_2D)

    glFramebufferTexture1DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_1D, t[1], 0)
    glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_3D, t[2], 0, 0)

    glDeleteRenderbuffersEXT(rb)
    glDeleteFramebuffersEXT(fb)
    glDeleteTextures(t)
  end

  def test_gl_ext_gpu_program_parameters		
    supported?("GL_EXT_gpu_program_parameters")

    glProgramEnvParameters4fvEXT(GL_VERTEX_PROGRAM_ARB, 1, [1, 2, 3, 4, 5, 6, 7, 8])
    assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB, 1), [1, 2, 3, 4])
    assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB, 2), [5, 6, 7, 8])
  end

  def test_gl_ext_framebuffer_blit
    supported?("GL_EXT_framebuffer_blit")
    fbo = glGenFramebuffersEXT(2)
    texture = glGenTextures(2)
    data = [1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0]

    glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, fbo[0])
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fbo[1])

    glBindTexture(GL_TEXTURE_2D, texture[0])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.pack("C*"))
    glGenerateMipmapEXT(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[1])
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, nil)
    glGenerateMipmapEXT(GL_TEXTURE_2D);

    glFramebufferTexture2DEXT(GL_READ_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture[0], 0)
    glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture[1], 0)

    status = glCheckFramebufferStatusEXT(GL_READ_FRAMEBUFFER_EXT)
    assert_equal(status, GL_FRAMEBUFFER_COMPLETE_EXT)
    status = glCheckFramebufferStatusEXT(GL_DRAW_FRAMEBUFFER_EXT)
    assert_equal(status, GL_FRAMEBUFFER_COMPLETE_EXT)

    glBlitFramebufferEXT(0, 0, 2, 2,
                         0, 0, 2, 2,
                         GL_COLOR_BUFFER_BIT,
                         GL_NEAREST)

    glBindTexture(GL_TEXTURE_2D, texture[1])
    tex = glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE).unpack("C*")
    assert_equal(tex, data)

    glDeleteTextures(texture)
    glDeleteFramebuffersEXT(fbo)
  end

  def test_gl_ext_framebuffer_multisample
    supported?("GL_EXT_framebuffer_multisample")
    rb = glGenRenderbuffersEXT(1)[0]

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb)
    glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, 4, GL_RGBA, 2, 2)
    samples = glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_SAMPLES_EXT)
    assert_equal(samples, 4)

    glDeleteRenderbuffersEXT(rb)
  end

  def test_gl_ext_pointparameter
    supported?("GL_EXT_point_parameters")
    glPointParameterfEXT(GL_POINT_SIZE_MIN, 1.0)
    assert_equal(glGetDoublev(GL_POINT_SIZE_MIN), 1.0)

    glPointParameterfvEXT(GL_POINT_DISTANCE_ATTENUATION, [1, 0, 1])
    assert_equal(glGetDoublev(GL_POINT_DISTANCE_ATTENUATION), [1, 0, 1])
  end

  def test_gl_ext_stencil_two_side
    supported?("GL_EXT_stencil_two_side")
    glActiveStencilFaceEXT(GL_FRONT)
    assert_equal(glGetIntegerv(GL_ACTIVE_STENCIL_FACE_EXT), GL_FRONT)
    glActiveStencilFaceEXT(GL_BACK)
    assert_equal(glGetIntegerv(GL_ACTIVE_STENCIL_FACE_EXT), GL_BACK)
  end

  def test_gl_ext_stencil_clear_tag
    supported?("GL_EXT_stencil_clear_tag")
    glStencilClearTagEXT(1, 2)
    assert_equal(glGetIntegerv(GL_STENCIL_TAG_BITS_EXT), 1)
    assert_equal(glGetIntegerv(GL_STENCIL_CLEAR_TAG_VALUE_EXT), 2)
  end

  def test_gl_ext_secondary_color
    supported?("GL_EXT_secondary_color")

    glSecondaryColor3bEXT(2**7-1, 0, 2**7-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3bvEXT([0, 2**7-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3dEXT(1.0, 0.0, 1.0)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3dvEXT([0.0, 1.0, 0.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3fEXT(1.0, 0.0, 1.0)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3fvEXT([0.0, 1.0, 0.0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3iEXT(2**31-1, 0, 2**31-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3ivEXT([0, 2**31-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3sEXT(2**15-1, 0, 2**15-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3svEXT([0, 2**15-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3ubEXT(2**8-1, 0, 2**8-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3ubvEXT([0, 2**8-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3uiEXT(2**32-1, 0, 2**32-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3uivEXT([0, 2**32-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3usEXT(2**16-1, 0, 2**16-1)
    assert_each_in_delta [1.0, 0.0, 1.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    glSecondaryColor3usvEXT([0, 2**16-1, 0])
    assert_each_in_delta [0.0, 1.0, 0.0, 1.0], glGetDoublev(GL_CURRENT_SECONDARY_COLOR)

    sc = [0, 1, 0, 1, 0, 1].pack("f*")

    glSecondaryColorPointerEXT(3, GL_FLOAT, 12, sc)
    assert_equal 3,        glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_SIZE)
    assert_equal GL_FLOAT, glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_TYPE)
    assert_equal 12,       glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_STRIDE)
    assert_equal sc,       glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER)
    glEnableClientState(GL_SECONDARY_COLOR_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd()

    assert_equal([0, 1, 0, 1], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glBegin(GL_TRIANGLES)
    glArrayElement(1)
    glEnd()

    assert_equal([1, 0, 1, 1], glGetDoublev(GL_CURRENT_SECONDARY_COLOR))

    glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
  end

  def test_gl_ext_blend_color
    supported?("GL_EXT_blend_color")
    glBlendColorEXT(1.0, 0.0, 1.0, 0.0)
    assert_equal([1, 0, 1, 0], glGetFloatv(GL_BLEND_COLOR_EXT))
    glBlendColorEXT(0.0, 1.0, 0.0, 1.0)
    assert_equal([0, 1, 0, 1], glGetFloatv(GL_BLEND_COLOR_EXT))
  end

  def test_gl_ext_blend_minmax
    supported?("GL_EXT_blend_minmax")
    glBlendEquationEXT(GL_MIN_EXT)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_EXT), GL_MIN_EXT)
    glBlendEquationEXT(GL_MAX_EXT)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_EXT), GL_MAX_EXT)
  end

  def test_gl_ext_blend_func_separate
    supported?("GL_EXT_blend_func_separate")
    glBlendFuncSeparateEXT(GL_ZERO, GL_ONE, GL_ZERO, GL_ONE)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB_EXT), GL_ZERO)
    assert_equal(glGetIntegerv(GL_BLEND_DST_RGB_EXT), GL_ONE)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA_EXT), GL_ZERO)
    assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA_EXT), GL_ONE)
    glBlendFuncSeparateEXT(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB_EXT), GL_ONE)
    assert_equal(glGetIntegerv(GL_BLEND_DST_RGB_EXT), GL_ZERO)
    assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA_EXT), GL_ONE)
    assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA_EXT), GL_ZERO)
  end

  def test_gl_ext_blend_equation_separate
    supported?("GL_EXT_blend_equation_separate")
    glBlendEquationSeparateEXT(GL_FUNC_ADD, GL_FUNC_SUBTRACT)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB_EXT), GL_FUNC_ADD)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA_EXT), GL_FUNC_SUBTRACT)
    glBlendEquationSeparateEXT(GL_FUNC_SUBTRACT, GL_FUNC_ADD)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB_EXT), GL_FUNC_SUBTRACT)
    assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA_EXT), GL_FUNC_ADD)
  end

  def test_gl_ext_depth_bounds_test
    supported?("GL_EXT_depth_bounds_test")
    glDepthBoundsEXT(0.2, 0.8)
    assert_each_in_delta [0.2, 0.8], glGetDoublev(GL_DEPTH_BOUNDS_EXT)
  end

  def test_gl_ext_timer_query
    supported?("GL_EXT_timer_query")
    queries = glGenQueries(2)
    glBeginQuery(GL_TIME_ELAPSED_EXT, queries[0])
    glBegin(GL_QUADS)
    glVertex2i(0, 0)
    glVertex2i(0, 1)
    glVertex2i(1, 1)
    glVertex2i(1, 0)
    glEnd
    glEndQuery(GL_TIME_ELAPSED_EXT)

    while glGetQueryObjectiv(queries[0], GL_QUERY_RESULT_AVAILABLE)==GL_FALSE
      #
    end
    assert(glGetQueryObjecti64vEXT(queries[0], GL_QUERY_RESULT)>0)
    assert(glGetQueryObjectui64vEXT(queries[0], GL_QUERY_RESULT)>0)

    glDeleteQueries(queries)
  end

  def test_gl_ext_texture_object
    supported?("GL_EXT_texture_object")
    textures = glGenTexturesEXT(2)
    glBindTextureEXT(GL_TEXTURE_1D, textures[0])
    glBindTextureEXT(GL_TEXTURE_2D, textures[1])
    assert_equal(glIsTextureEXT(textures[0]), true)
    assert_equal(glAreTexturesResidentEXT(textures).size, 2)

    glPrioritizeTexturesEXT(textures, [0.5, 1.0])
    assert_equal(glGetTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_PRIORITY), 0.5)
    assert_equal(glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY), 1.0)

    glDeleteTexturesEXT(textures)
    assert_equal(glIsTextureEXT(textures[0]), false)
  end

  def test_gl_ext_compiled_vertex_array
    supported?("GL_EXT_compiled_vertex_array")
    glLockArraysEXT(1, 2)
    assert_equal(glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_FIRST_EXT), 1)
    assert_equal(glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_COUNT_EXT), 2)
    glUnlockArraysEXT()
  end

  def test_gl_ext_fogcoord
    supported?("GL_EXT_fog_coord")

    glFogCoordfEXT(2.0)
    assert_equal 2.0, glGetDoublev(GL_CURRENT_FOG_COORD)
    glFogCoordfvEXT([3.0])
    assert_equal 3.0, glGetDoublev(GL_CURRENT_FOG_COORD)

    glFogCoorddEXT(2.0)
    assert_equal 2.0, glGetDoublev(GL_CURRENT_FOG_COORD)
    glFogCoorddvEXT([3.0])
    assert_equal 3.0, glGetDoublev(GL_CURRENT_FOG_COORD)

    fc = [1, 0].pack("f*")
    glFogCoordPointerEXT(GL_FLOAT, 4, fc)
    assert_equal GL_FLOAT, glGetIntegerv(GL_FOG_COORD_ARRAY_TYPE)
    assert_equal 4, glGetIntegerv(GL_FOG_COORD_ARRAY_STRIDE)
    assert_equal fc, glGetPointerv(GL_FOG_COORD_ARRAY_POINTER)

    glEnableClientState(GL_FOG_COORD_ARRAY)

    glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glEnd()

    assert_equal 1, glGetDoublev(GL_CURRENT_FOG_COORD)

    glBegin(GL_TRIANGLES)
    glArrayElement(1)
    glEnd()

    assert_equal 0, glGetDoublev(GL_CURRENT_FOG_COORD)

    glDisableClientState(GL_FOG_COORD_ARRAY)
  end

  def test_gl_ext_multi_draw_arrays
    supported?("GL_EXT_multi_draw_arrays")
    va = [0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    glEnableClientState(GL_VERTEX_ARRAY)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glMultiDrawArraysEXT(GL_POLYGON, [0, 3], [3, 3])

    i1 = [0, 1, 2].pack("C*")
    i2 = [3, 4, 5].pack("C*")
    glMultiDrawElementsEXT(GL_TRIANGLES, GL_UNSIGNED_BYTE, [i1, i2])

    count = glRenderMode(GL_RENDER)
    assert_equal(count, (3*3+2)*4)
    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_gl_ext_drawrangeelements
    supported?("GL_EXT_draw_range_elements")
    va = [0, 0, 0, 1, 1, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glEnableClientState(GL_VERTEX_ARRAY)

    glDrawRangeElementsEXT(GL_POINTS, 0, 2, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("C*"))
    count = glRenderMode(GL_RENDER)
    assert_equal(count, 12)

    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_gl_ext_geometry_shader4
    supported?("GL_EXT_geometry_shader4")
    program = glCreateProgramObjectARB()

    glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT , GL_LINES_ADJACENCY_EXT)
    assert_equal(glGetObjectParameterivARB(program, GL_GEOMETRY_INPUT_TYPE_EXT), GL_LINES_ADJACENCY_EXT)

    glDeleteObjectARB(program)
  end

  def test_gl_ext_gpu_shader4
    supported?(["GL_EXT_gpu_shader4", "GL_ARB_vertex_program"])

    programs = glGenProgramsARB(1)
    program = "!!ARBvp1.0\nTEMP vv;\nEND"

    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, programs[0])
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, program)

    glVertexAttribI1iEXT(1, 1)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 1)
    glVertexAttribI1uiEXT(1, 2)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 2)
    glVertexAttribI1ivEXT(1, [3])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 3)
    glVertexAttribI1uivEXT(1, [4])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0], 4)

    glVertexAttribI2iEXT(1, 1, 2)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2], [1, 2])
    glVertexAttribI2uiEXT(1, 2, 3)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2], [2, 3])
    glVertexAttribI2ivEXT(1, [3, 4])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2], [3, 4])
    glVertexAttribI2uivEXT(1, [4, 5])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 2], [4, 5])

    glVertexAttribI3iEXT(1, 1, 2, 3)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3], [1, 2, 3])
    glVertexAttribI3uiEXT(1, 2, 3, 4)
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3], [2, 3, 4])
    glVertexAttribI3ivEXT(1, [3, 4, 5])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3], [3, 4, 5])
    glVertexAttribI3uivEXT(1, [4, 5, 6])
    assert_equal(glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)[0, 3], [4, 5, 6])

    glVertexAttribI4iEXT(1, 1, 2, 3, 4)
    assert_equal [1, 2, 3, 4], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4uiEXT(1, 2, 3, 4, 5)
    assert_equal [2, 3, 4, 5], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4ivEXT(1, [3, 4, 5, 6])
    assert_equal [3, 4, 5, 6], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4uivEXT(1, [4, 5, 6, 7])
    assert_equal [4, 5, 6, 7], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)

    glVertexAttribI4bvEXT(1, [1, 2, 3, 4])
    assert_equal [1, 2, 3, 4], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4svEXT(1, [2, 3, 4, 5])
    assert_equal [2, 3, 4, 5], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4ubvEXT(1, [1, 2, 3, 4])
    assert_equal [1, 2, 3, 4], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)
    glVertexAttribI4usvEXT(1, [2, 3, 4, 5])
    assert_equal [2, 3, 4, 5], glGetVertexAttribIivEXT(1, GL_CURRENT_VERTEX_ATTRIB_ARB)

    glVertexAttribIPointerEXT(1, 2, GL_INT, 0, [1, 1].pack("i*"))
    assert_equal [1, 1].pack("i*"), glGetVertexAttribPointervARB(1)

    glDeleteProgramsARB(programs)
  end

  def test_gl_ext_gpu_shader4_2
    supported?(["GL_EXT_gpu_shader4", "GL_ARB_shader_objects"])

    vertex_shader_source = <<-SHADER
uniform int testivec1;
uniform ivec2 testivec2;
uniform ivec3 testivec3;
uniform ivec4 testivec4;
void main() {
  testivec1;
  testivec2;
  testivec3;
  testivec4;

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
    glLinkProgramARB(program)
    assert glGetObjectParameterivARB(program, GL_OBJECT_LINK_STATUS_ARB)
    glUseProgramObjectARB(program)

    tv1il = glGetUniformLocation program, "testivec1"
    refute_equal -1, tv1il, "testivec1 missing!"

    tv2il = glGetUniformLocation program, "testivec2"
    refute_equal -1, tv2il, "testivec2 missing!"

    tv3il = glGetUniformLocation program, "testivec3"
    refute_equal -1, tv3il, "testivec3 missing!"

    tv4il = glGetUniformLocation program, "testivec4"
    refute_equal -1, tv4il, "testivec4 missing!"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tv1il).last != "testivec1"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tv2il).last != "testivec2"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tv3il).last != "testivec3"

    skip "glGetUniformLocation is broken" if
      glGetActiveUniform(program, tv4il).last != "testivec4"

    skip "can't find documentation for glUniform1uiEXT"
    glUniform1uiEXT(tv1il, 3)
    assert_equal 3, glGetUniformuivEXT(program, tv1il)

    glUniform1uivEXT(tv1il, [4])
    assert_equal 4, glGetUniformuivEXT(program, tv1il)

    glUniform2uiEXT(tv2il, 1, 2)
    assert_equal [1, 2], glGetUniformuivEXT(program, tv2il)

    glUniform2uivEXT(tv2il, [3, 4])
    assert_equal [3, 4], glGetUniformuivEXT(program, tv2il)

    glUniform3uiEXT(tv3il, 1, 2, 3)
    assert_equal [1, 2, 3], glGetUniformuivEXT(program, tv3il)

    glUniform3uivEXT(tv3il, [3, 4, 5])
    assert_equal [3, 4, 5], glGetUniformuivEXT(program, tv3il)

    glUniform4uiEXT(tv4il, 1, 2, 3, 4)
    assert_equal [1, 2, 3, 4], glGetUniformuivEXT(program, tv4il)

    glUniform4uivEXT(tv4il, [3, 4, 5, 6])
    assert_equal [3, 4, 5, 6], glGetUniformuivEXT(program, tv4il)

    glBindFragDataLocationEXT(program, 1, "test")
    assert_equal -1, glGetFragDataLocationEXT(program, "test")
  end

  def test_gl_ext_draw_instanced
    supported?("GL_EXT_draw_instanced")

    glEnableClientState(GL_VERTEX_ARRAY)

    va = [0, 0, 0, 1, 1, 1].pack("f*")
    glVertexPointer(2, GL_FLOAT, 0, va)

    buf = glFeedbackBuffer(256, GL_3D)
    glRenderMode(GL_FEEDBACK)

    glDrawArraysInstancedEXT(GL_TRIANGLES, 0, 3, 2)

    glDrawElementsInstancedEXT(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, [0, 1, 2].pack("C*"), 2)
    count = glRenderMode(GL_RENDER)
    assert_equal(count, 2*2*11)

    glDisableClientState(GL_VERTEX_ARRAY)
  end

  def test_gl_ext_texture_buffer_object
    supported?("GL_EXT_texture_buffer_object")

    buf = glGenBuffers(1)[0]
    glBindBuffer(GL_TEXTURE_BUFFER_EXT, buf)

    tex = glGenTextures(1)[0]
    glBindTexture(GL_TEXTURE_BUFFER_EXT, tex)
    glTexBufferEXT(GL_TEXTURE_BUFFER_EXT, GL_RGBA32F_ARB, buf)

    assert_equal(glGetIntegerv(GL_TEXTURE_BINDING_BUFFER_EXT), tex)
    assert_equal(glGetIntegerv(GL_TEXTURE_BUFFER_FORMAT_EXT), GL_RGBA32F_ARB)

    glDeleteBuffers(buf)
    glDeleteTextures(tex)
  end

  def test_gl_ext_texture_integer
    supported?("GL_EXT_texture_integer")

    glClearColorIiEXT(1, 2, 3, 4)	
    glClearColorIuiEXT(1, 2, 3, 4)	

    glTexParameterIivEXT(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, [1, 2, 3, 4])
    assert_equal(glGetTexParameterIivEXT(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR), [1, 2, 3, 4])
    glTexParameterIuivEXT(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, [5, 6, 7, 8])
    assert_equal(glGetTexParameterIuivEXT(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR), [5, 6, 7, 8])
  end
end
