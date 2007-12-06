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

class Test_EXT_EXT < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		if Gl.is_available?("GL_EXT_framebuffer_object")
			glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0)
			glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0)
		end
		common_teardown()
	end

	def test_gl_ext_polygon_offset
		return if not supported?("GL_EXT_polygon_offset")

		glPolygonOffsetEXT(1.0,2.0)
		assert_equal(glGetIntegerv(GL_POLYGON_OFFSET_FACTOR_EXT),1.0)
		assert_equal(glGetIntegerv(GL_POLYGON_OFFSET_BIAS_EXT),2.0)
	end

	def test_gl_ext_framebuffer_object
		return if not supported?("GL_EXT_framebuffer_object")
		t = glGenTextures(3)
		glBindTexture(GL_TEXTURE_2D, t[0])
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,$window_size,$window_size,0,GL_RGBA,GL_UNSIGNED_BYTE,nil)

		glBindTexture(GL_TEXTURE_1D, t[1])
		glTexImage1D(GL_TEXTURE_1D,0,GL_RGBA8,$window_size,0,GL_RGBA,GL_UNSIGNED_BYTE,nil)

		glBindTexture(GL_TEXTURE_3D, t[2])
		glTexImage3D(GL_TEXTURE_3D,0,GL_RGBA8,$window_size,$window_size,1,0,GL_RGBA,GL_UNSIGNED_BYTE,nil)

		fb = glGenFramebuffersEXT(1)
		assert(fb.size==1)
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fb[0])
		assert_equal(glIsFramebufferEXT(fb[0]),GL_TRUE)

		rb = glGenRenderbuffersEXT(1)
		assert(rb.size==1)
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,rb[0])
		assert_equal(glIsRenderbufferEXT(rb[0]),GL_TRUE)

		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, $window_size, $window_size)

		assert_equal(glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_WIDTH_EXT),$window_size)
		assert_equal(glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_HEIGHT_EXT),$window_size)
		assert_equal(glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_INTERNAL_FORMAT_EXT),GL_DEPTH_COMPONENT)


		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rb[0]);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, t[0], 0)

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)
		assert(status == GL_FRAMEBUFFER_COMPLETE_EXT || status == GL_FRAMEBUFFER_UNSUPPORTED_EXT)

		assert_equal(glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT),GL_TEXTURE)

		glGenerateMipmapEXT(GL_TEXTURE_2D)

		glFramebufferTexture1DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_1D, t[1], 0)
		glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_3D, t[2], 0, 0)
	
		glDeleteRenderbuffersEXT(rb)
		glDeleteFramebuffersEXT(fb)
		glDeleteTextures(t)
	end

	def test_gl_ext_gpu_program_parameters		
		return if not supported?("GL_EXT_gpu_program_parameters")

		glProgramEnvParameters4fvEXT(GL_VERTEX_PROGRAM_ARB,1, [1,2,3,4,5,6,7,8])
		assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB,1),[1,2,3,4])
		assert_equal(glGetProgramEnvParameterdvARB(GL_VERTEX_PROGRAM_ARB,2),[5,6,7,8])
	end

	def test_gl_ext_framebuffer_blit
		return if not supported?("GL_EXT_framebuffer_blit")
		fbo = glGenFramebuffersEXT(2)
		texture = glGenTextures(2)
		data = [1,1,1,1, 0,0,0,0, 1,1,1,1, 0,0,0,0]

		glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, fbo[0])
		glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fbo[1])

		glBindTexture(GL_TEXTURE_2D, texture[0])
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,data.pack("C*"))
		glGenerateMipmapEXT(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture[1])
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,nil)
		glGenerateMipmapEXT(GL_TEXTURE_2D);

		glFramebufferTexture2DEXT(GL_READ_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture[0], 0)
		glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture[1], 0)

		status = glCheckFramebufferStatusEXT(GL_READ_FRAMEBUFFER_EXT)
		assert_equal(status,GL_FRAMEBUFFER_COMPLETE_EXT)
		status = glCheckFramebufferStatusEXT(GL_DRAW_FRAMEBUFFER_EXT)
		assert_equal(status,GL_FRAMEBUFFER_COMPLETE_EXT)

		glBlitFramebufferEXT(0, 0, 2, 2,
											   0, 0, 2, 2,
											   GL_COLOR_BUFFER_BIT,
											   GL_NEAREST)

		glBindTexture(GL_TEXTURE_2D, texture[1])
		tex = glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE).unpack("C*")
		assert_equal(tex,data)
		
		glDeleteTextures(texture)
		glDeleteFramebuffersEXT(fbo)
	end

	def test_gl_ext_framebuffer_multisample
		return if not supported?("GL_EXT_framebuffer_multisample")
		rb = glGenRenderbuffersEXT(1)[0]

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,rb)
		glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT,4,GL_RGBA,2,2)
		samples = glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT,GL_RENDERBUFFER_SAMPLES_EXT)
		assert_equal(samples,4)

		glDeleteRenderbuffersEXT(rb)
	end

	def test_gl_ext_pointparameter
		return if not supported?("GL_EXT_point_parameters")
		glPointParameterfEXT(GL_POINT_SIZE_MIN,1.0)
		assert_equal(glGetDoublev(GL_POINT_SIZE_MIN),1.0)

		glPointParameterfvEXT(GL_POINT_DISTANCE_ATTENUATION,[1,0,1])
		assert_equal(glGetDoublev(GL_POINT_DISTANCE_ATTENUATION),[1,0,1])
	end

	def test_gl_ext_stencil_two_side
		return if not supported?("GL_EXT_stencil_two_side")
		glActiveStencilFaceEXT(GL_FRONT)
		assert_equal(glGetIntegerv(GL_ACTIVE_STENCIL_FACE_EXT),GL_FRONT)
		glActiveStencilFaceEXT(GL_BACK)
		assert_equal(glGetIntegerv(GL_ACTIVE_STENCIL_FACE_EXT),GL_BACK)
	end

	def test_gl_ext_stencil_clear_tag
		return if not supported?("GL_EXT_stencil_clear_tag")
		glStencilClearTagEXT(1,2)
		assert_equal(glGetIntegerv(GL_STENCIL_TAG_BITS_EXT),1)
		assert_equal(glGetIntegerv(GL_STENCIL_CLEAR_TAG_VALUE_EXT),2)
	end

	def test_gl_ext_secondary_color
		return if not supported?("GL_EXT_secondary_color")

		glSecondaryColor3bEXT(2**7-1,0,2**7-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3bvEXT([0,2**7-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3dEXT(1.0,0.0,1.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3dvEXT([0.0,1.0,0.0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3fEXT(1.0,0.0,1.0)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3fvEXT([0.0,1.0,0.0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3iEXT(2**31-1,0,2**31-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3ivEXT([0,2**31-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3sEXT(2**15-1,0,2**15-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3svEXT([0,2**15-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3ubEXT(2**8-1,0,2**8-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3ubvEXT([0,2**8-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3uiEXT(2**32-1,0,2**32-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3uivEXT([0,2**32-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))
		glSecondaryColor3usEXT(2**16-1,0,2**16-1)
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1.0,0.0,1.0,1.0]))
		glSecondaryColor3usvEXT([0,2**16-1,0])
		assert(approx_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0.0,1.0,0.0,1.0]))

		sc = [0,1,0, 1,0,1].pack("f*")

		glSecondaryColorPointerEXT(3,GL_FLOAT,0,sc)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_SIZE),3)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_TYPE),GL_FLOAT)
		assert_equal(glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_STRIDE),0)
		assert_equal(glGetPointerv(GL_SECONDARY_COLOR_ARRAY_POINTER),sc)
		glEnableClientState(GL_SECONDARY_COLOR_ARRAY)

		glBegin(GL_TRIANGLES)
		glArrayElement(0)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[0,1,0,1])

		glBegin(GL_TRIANGLES)
		glArrayElement(1)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_SECONDARY_COLOR),[1,0,1,1])

		glDisableClientState(GL_SECONDARY_COLOR_ARRAY)
	end

	def test_gl_ext_blend_color
		return if not supported?("GL_EXT_blend_color")
		glBlendColorEXT(1.0,0.0,1.0,0.0)
		assert_equal(glGetFloatv(GL_BLEND_COLOR_EXT),[1,0,1,0])
		glBlendColorEXT(0.0,1.0,0.0,1.0)
		assert_equal(glGetFloatv(GL_BLEND_COLOR_EXT),[0,1,0,1])
	end

	def test_gl_ext_blend_minmax
		return if not supported?("GL_EXT_blend_minmax")
		glBlendEquationEXT(GL_MIN_EXT)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_EXT),GL_MIN_EXT)
		glBlendEquationEXT(GL_MAX_EXT)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_EXT),GL_MAX_EXT)
	end

	def test_gl_ext_blend_func_separate
		return if not supported?("GL_EXT_blend_func_separate")
		glBlendFuncSeparateEXT(GL_ZERO,GL_ONE,GL_ZERO,GL_ONE)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB_EXT),GL_ZERO)
		assert_equal(glGetIntegerv(GL_BLEND_DST_RGB_EXT),GL_ONE)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA_EXT),GL_ZERO)
		assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA_EXT),GL_ONE)
		glBlendFuncSeparateEXT(GL_ONE,GL_ZERO,GL_ONE,GL_ZERO)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_RGB_EXT),GL_ONE)
		assert_equal(glGetIntegerv(GL_BLEND_DST_RGB_EXT),GL_ZERO)
		assert_equal(glGetIntegerv(GL_BLEND_SRC_ALPHA_EXT),GL_ONE)
		assert_equal(glGetIntegerv(GL_BLEND_DST_ALPHA_EXT),GL_ZERO)
	end

	def test_gl_ext_blend_equation_separate
		return if not supported?("GL_EXT_blend_equation_separate")
		glBlendEquationSeparateEXT(GL_FUNC_ADD,GL_FUNC_SUBTRACT)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB_EXT),GL_FUNC_ADD)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA_EXT),GL_FUNC_SUBTRACT)
		glBlendEquationSeparateEXT(GL_FUNC_SUBTRACT,GL_FUNC_ADD)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_RGB_EXT),GL_FUNC_SUBTRACT)
		assert_equal(glGetIntegerv(GL_BLEND_EQUATION_ALPHA_EXT),GL_FUNC_ADD)
	end

	def test_gl_ext_depth_bounds_test
		return if not supported?("GL_EXT_depth_bounds_test")
		glDepthBoundsEXT(0.2,0.8)
		assert(approx_equal(glGetDoublev(GL_DEPTH_BOUNDS_EXT),[0.2,0.8]))
	end

	def test_gl_ext_timer_query
		return if not supported?("GL_EXT_timer_query")
		queries = glGenQueries(2)
		glBeginQuery(GL_TIME_ELAPSED_EXT,queries[0])
		glBegin(GL_QUADS)
			glVertex2i(0,0)
			glVertex2i(0,1)
			glVertex2i(1,1)
			glVertex2i(1,0)
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
		return if not supported?("GL_EXT_texture_object")
		textures = glGenTexturesEXT(2)
		glBindTextureEXT(GL_TEXTURE_1D,textures[0])
		glBindTextureEXT(GL_TEXTURE_2D,textures[1])
		assert_equal(glIsTextureEXT(textures[0]),GL_TRUE)
		assert_equal(glAreTexturesResidentEXT(textures).size,2)

		glPrioritizeTexturesEXT(textures,[0.5,1.0])
		assert_equal(glGetTexParameterfv(GL_TEXTURE_1D,GL_TEXTURE_PRIORITY),[0.5])
		assert_equal(glGetTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_PRIORITY),[1.0])

		glDeleteTexturesEXT(textures)
		assert_equal(glIsTextureEXT(textures[0]),GL_FALSE)
	end

	def test_gl_ext_compiled_vertex_array
		return if not supported?("GL_EXT_compiled_vertex_array")
		glLockArraysEXT(1,2)
		assert_equal(glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_FIRST_EXT),1)
		assert_equal(glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_COUNT_EXT),2)
		glUnlockArraysEXT()
	end

	def test_gl_ext_fogcoord
		return if not supported?("GL_EXT_fog_coord")

		glFogCoordfEXT(2.0)
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),2.0)
		glFogCoordfvEXT([3.0])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),3.0)

		glFogCoorddEXT(2.0)
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),2.0)
		glFogCoorddvEXT([3.0])
		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),3.0)

		fc = [1, 0].pack("f*")
		glFogCoordPointerEXT(GL_FLOAT,0,fc)
		assert_equal(glGetIntegerv(GL_FOG_COORD_ARRAY_TYPE),GL_FLOAT)
		assert_equal(glGetIntegerv(GL_FOG_COORD_ARRAY_STRIDE),0)
		assert_equal(glGetPointerv(GL_FOG_COORD_ARRAY_POINTER),fc)

		glEnableClientState(GL_FOG_COORD_ARRAY)

		glBegin(GL_TRIANGLES)
		glArrayElement(0)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),1)

		glBegin(GL_TRIANGLES)
		glArrayElement(1)
		glEnd()

		assert_equal(glGetDoublev(GL_CURRENT_FOG_COORD),0)

		glDisableClientState(GL_FOG_COORD_ARRAY)
	end

	def test_gl_ext_multi_draw_arrays
		return if not supported?("GL_EXT_multi_draw_arrays")
		va = [0,0, 1,0, 1,1, 0,0, 1,0, 0,1].pack("f*")
		glVertexPointer(2,GL_FLOAT,0,va)
		
		glEnable(GL_VERTEX_ARRAY)

		buf = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		glMultiDrawArraysEXT(GL_POLYGON, [0,3], [3,3])

		i1 = [0,1,2].pack("C*")
		i2 = [3,4,5].pack("C*")
		glMultiDrawElementsEXT(GL_TRIANGLES,GL_UNSIGNED_BYTE,[i1,i2])

		count = glRenderMode(GL_RENDER)
		assert_equal(count,(3*3+2)*4)
		glDisable(GL_VERTEX_ARRAY)
	end

	def test_gl_ext_drawrangeelements
		return if not supported?("GL_EXT_draw_range_elements")
		va = [0,0, 0,1, 1,1].pack("f*")
		glVertexPointer(2,GL_FLOAT,0,va)

		buf = glFeedbackBuffer(256,GL_3D)
		glRenderMode(GL_FEEDBACK)

		glEnable(GL_VERTEX_ARRAY)

		glDrawRangeElementsEXT(GL_POINTS,0,2,3,GL_UNSIGNED_BYTE,[0,1,2].pack("C*"))
		count = glRenderMode(GL_RENDER)
		assert_equal(count,12)

		glDisable(GL_VERTEX_ARRAY)
	end

	def test_gl_ext_geometry_shader4
		return if not supported?("GL_EXT_geometry_shader4")
		program = glCreateProgramObjectARB()

		glProgramParameteriEXT(program,GL_GEOMETRY_INPUT_TYPE_EXT ,GL_LINES_ADJACENCY_EXT)
		assert_equal(glGetObjectParameterivARB(program,GL_GEOMETRY_INPUT_TYPE_EXT),GL_LINES_ADJACENCY_EXT)

		glDeleteObjectARB(program)
	end
end
