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
require 'glu'
include Glu

class Test_GLU < Test::Unit::TestCase
	def setup
		common_setup()
	end

	def teardown
		common_teardown()
	end

	def test_gluortho
		res = [ [2.0/$window_size, 0, 0, 0],
					  [0, 2.0/$window_size, 0, 0],
					  [0, 0, -1, 0],
						[-1,-1,0,1] ]

		glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		gluOrtho2D(0,$window_size,0,$window_size)
		assert_equal(glGetDoublev(GL_PROJECTION_MATRIX),res)
	end

	def test_glugetstring
		ver = gluGetString(GLU_VERSION)
		assert(ver.to_f > 1.1)
	end

	def test_gluerrorstring
		error = gluErrorString(GL_INVALID_VALUE)
		assert(error.class == String)
		assert(error.length > 2)
	end

	def test_glubuild2dmipmaps
		textures = glGenTextures(1)
		glBindTexture(GL_TEXTURE_2D,textures[0])

		image = ([0,0,0,1,1,1] * 8).pack("f*") # 16 RGB pixels

		gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB8,4,4,GL_RGB,GL_FLOAT,image)
		im = glGetTexImage(GL_TEXTURE_2D,0,GL_RGB,GL_FLOAT)
		assert_equal(im,image)
		assert_equal(im.unpack("f*").size,4*4*3)
		im = glGetTexImage(GL_TEXTURE_2D,1,GL_RGB,GL_FLOAT)
		assert_equal(im.unpack("f*").size,2*2*3)
		im = glGetTexImage(GL_TEXTURE_2D,2,GL_RGB,GL_FLOAT)
		assert_equal(im.unpack("f*").size,1*1*3)

		glDeleteTextures(textures)
	end

	def test_glubuild1dmipmaps
		textures = glGenTextures(1)
		glBindTexture(GL_TEXTURE_1D,textures[0])

		image = ([0,0,0,1,1,1] * 2).pack("f*") # 4 RGB pixels

		gluBuild1DMipmaps(GL_TEXTURE_1D,GL_RGB8,4,GL_RGB,GL_FLOAT,image)

		im = glGetTexImage(GL_TEXTURE_1D,0,GL_RGB,GL_FLOAT)
		assert_equal(im,image)
		assert_equal(im.unpack("f*").size,4*3)
		im = glGetTexImage(GL_TEXTURE_1D,1,GL_RGB,GL_FLOAT)
		assert_equal(im.unpack("f*").size,2*3)
		im = glGetTexImage(GL_TEXTURE_1D,2,GL_RGB,GL_FLOAT)
		assert_equal(im.unpack("f*").size,1*3)

		glDeleteTextures(textures)
	end
	
	def test_glulookat
		m = [[0,0,1,0], [0,1,0,0], [-1,0,0,0], [0,0,-1, 1]]
		gluLookAt(1,0,0, 0,0,0, 0,1,0)
		assert_equal(glGetDoublev(GL_PROJECTION_MATRIX),m)
	end

	def test_gluproject
		pos = gluProject(1,1,1)
		assert_equal(pos,[$window_size,$window_size,1])

		mp = glGetDoublev(GL_PROJECTION_MATRIX)
		mm = glGetDoublev(GL_MODELVIEW_MATRIX)
		view = glGetDoublev(GL_VIEWPORT)
		pos = gluProject(1,1,1,mp,mm,view)
		assert_equal(pos,[$window_size,$window_size,1])
	end

	def test_gluunproject
		pos = gluUnProject($window_size,$window_size,1)
		assert_equal(pos,[1,1,1])
		
		mp = glGetDoublev(GL_PROJECTION_MATRIX)
		mm = glGetDoublev(GL_MODELVIEW_MATRIX)
		view = glGetDoublev(GL_VIEWPORT)
		pos = gluUnProject($window_size,$window_size,1,mp,mm,view)
		assert_equal(pos,[1,1,1])
	end

	def test_glupickmatrix
		t = $window_size / 5.0
		m = [[t, 0.0, 0.0, 0.0], [0.0, t, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [t,t, 0.0, 1.0]]
		glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		gluPickMatrix(0,0)
		assert(approx_equal(glGetDoublev(GL_PROJECTION_MATRIX).flatten,m.flatten))
		glLoadIdentity()
		gluPickMatrix(0,0,5,5)
		assert(approx_equal(glGetDoublev(GL_PROJECTION_MATRIX).flatten,m.flatten))
		glLoadIdentity()
		gluPickMatrix(0,0,5,5,glGetDoublev(GL_VIEWPORT))
		assert(approx_equal(glGetDoublev(GL_PROJECTION_MATRIX).flatten,m.flatten))
	end

	def test_gluperspective
		m = [[1,0,0,0], [0,1,0,0], [0,0,-3,-1], [0,0,-4,0]]
		gluPerspective(90,1,1,2)
		assert_equal(glGetDoublev(GL_PROJECTION_MATRIX),m)
	end

	def test_gluscaleimage
		image = ([0,0,0,1,1,1] * 8).pack("f*") # 16 RGB pixels
		scaled = gluScaleImage(GL_RGB,4,4,GL_FLOAT,image, 2,2,GL_FLOAT)
		assert_equal(scaled.unpack("f*").length,2*2*3)
	end

	def test_gluquadrics
#		error_func = lambda do
#		end
	
		q = gluNewQuadric()
		gluQuadricDrawStyle(q,GL_LINE)
		gluQuadricNormals(q,GL_SMOOTH)
		gluQuadricOrientation(q,GLU_OUTSIDE)
		gluQuadricTexture(q,GL_FALSE)
#		gluQuadricCallback(q,GLU_ERROR,error_func) TODO:

		buf = glFeedbackBuffer(1024,GL_3D)
		glRenderMode(GL_FEEDBACK)
		gluSphere(q,1.0,4,3)
		count = glRenderMode(GL_RENDER)
		assert_equal(count,4*(3+1)*11)

		glRenderMode(GL_FEEDBACK)
		gluCylinder(q,1.0,1.0,1.0,4,3)
		count = glRenderMode(GL_RENDER)
		assert_equal(count,4*(3+1+2)*11)

		glRenderMode(GL_FEEDBACK)
		gluDisk(q,1.0,2.0,4,3)
		count = glRenderMode(GL_RENDER)
		assert_equal(count,4*(3+1+2)*11)

		glRenderMode(GL_FEEDBACK)
		gluPartialDisk(q,1.0,2.0,4,3,0,360)
		count = glRenderMode(GL_RENDER)
		assert_equal(count,4*(3+1+2)*11)
		gluDeleteQuadric(q)
	end

	def test_glunurbs
		gluPerspective(90,1,1,2)

		n = gluNewNurbsRenderer()
		gluNurbsProperty(n,GLU_SAMPLING_TOLERANCE,40)
		assert_equal(gluGetNurbsProperty(n,GLU_SAMPLING_TOLERANCE),40)

		knots = [0,0,0,0,1,1,1,1]
		ctlpoints_curve = [[50,50,0],[400,50,0],[400,400,0],[50,400,0]]

		# generate surface control points
		ctlpoints =  Array.new(4).collect { Array.new(4).collect { Array.new(3, nil) } } # 4*4*3 array
		0.upto(3)	do |u|
			0.upto(3) do |v|
				ctlpoints[u][v][0]=2.0*(u-1.5)
				ctlpoints[u][v][1]=2.0*(v-1.5)
			
				if ((u==1 || u==2) && (v==1 || v==2))
						ctlpoints[u][v][2]=6.0
				else
						ctlpoints[u][v][2]=0.0
				end
			end
		end

		buf = glFeedbackBuffer(1024*1024*8,GL_3D) # large enough buffer for tesselated surface
		glRenderMode(GL_FEEDBACK)
		gluBeginCurve(n)
		gluNurbsCurve(n,knots,ctlpoints_curve,4,GL_MAP1_VERTEX_3)
		gluEndCurve(n)

		gluBeginTrim(n)
		gluPwlCurve(n,[[0,0],[1,0],[1,1],[0,1],[0,0]],GLU_MAP1_TRIM_2)
		gluEndTrim(n)
		count = glRenderMode(GL_RENDER)
		assert(count>1)

		glRenderMode(GL_FEEDBACK)
		gluBeginSurface(n)
		gluNurbsSurface(n,knots,knots,ctlpoints,4,4,GL_MAP2_VERTEX_3)
		gluEndSurface(n)
		count = glRenderMode(GL_RENDER)
		assert(count>1)

		gluDeleteNurbsRenderer(n)
	end
end
