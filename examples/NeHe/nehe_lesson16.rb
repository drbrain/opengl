require 'opengl'
require 'png'
require 'png/reader'

class Lesson16
  include Gl
  include Glu
  include Glut

  def initialize
    @textures = nil
    @xrot = 0.0
    @yrot = 0.0
    @zrot = 0.0
    @fullscreen = true
    @filter = 0

    @fog_mode = [
      GL_EXP,
      GL_EXP2,
      GL_LINEAR
    ]

    @fog_filter = 0
    @fog_color = [0.5, 0.5, 0.5, 1.0]

    glutInit

    glutInitDisplayMode GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH
    glutInitWindowSize 640, 480
    glutInitWindowPosition 0, 0

    @window = glutCreateWindow "NeHe Lesson 16 - ruby-opengl version"

    glutDisplayFunc :draw_gl_scene
    glutReshapeFunc :reshape
    glutIdleFunc :idle
    glutKeyboardFunc :keyboard

    reshape 640, 480
    load_texture
    init_gl

    glutMainLoop
  end

  def init_gl
    glEnable GL_TEXTURE_2D
    glShadeModel GL_SMOOTH
    glClearColor 0.5, 0.5, 0.5, 1.0

    glFogi GL_FOG_MODE, @fog_mode[@fog_filter]
    glFogfv GL_FOG_COLOR, @fog_color
    glFogf GL_FOG_DENSITY, 0.35
    glHint GL_FOG_HINT, GL_DONT_CARE
    glFogf GL_FOG_START, 2.0
    glFogf GL_FOG_END, 8.0
    glEnable GL_FOG

    glClearDepth 1.0
    glEnable GL_DEPTH_TEST
    glDepthFunc GL_LEQUAL
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST
  end

  def reshape width, height
    width   = width.to_f
    height = height.to_f
    height = 1.0 if height.zero?

    glViewport 0, 0, width, height

    glMatrixMode GL_PROJECTION
    glLoadIdentity

    gluPerspective 45.0, width / height, 0.1, 100.0

    glMatrixMode GL_MODELVIEW
    glLoadIdentity
  end

  def draw_gl_scene
    glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
    glMatrixMode GL_MODELVIEW
    glLoadIdentity
    glTranslatef 0.0, 0.0, -7.0

    glRotatef @xrot, 1.0, 0.0, 0.0
    glRotatef @yrot, 0.0, 1.0, 0.0
    glRotatef @zrot, 0.0, 0.0, 1.0

    glBindTexture GL_TEXTURE_2D, @textures[0]

    glBegin GL_QUADS do
      # front face
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f( 1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f(-1.0,  1.0,  1.0)

      # back face
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0, -1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)

      # top face
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0,  1.0, -1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)

      # bottom face
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0, -1.0,  1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)

      # right face
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f( 1.0, -1.0,  1.0)

      # left face
      glTexCoord2f(0.0, 0.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f(-1.0,  1.0, -1.0)
    end

    @xrot += 0.03
    @yrot += 0.02
    @zrot += 0.04

    glutSwapBuffers
  end

  def idle
    glutPostRedisplay
  end

  def keyboard key, x, y
    case key
    when ?\e
      glutDestroyWindow @window
      exit 0
    when 'F' then 
      @fullscreen = !@fullscreen

      if @fullscreen then
        glutFullScreen
      else
        glutPositionWindow 0, 0
      end
    when 'f' then
      @fog_filter += 1
      @fog_filter %= 3

      glFogi GL_FOG_MODE, @fog_mode[@fog_filter]
      puts "fog #{@fog_filter}"
    end

    glutPostRedisplay
  end

  def load_texture
    png = PNG.load_file File.expand_path('../crate.png', __FILE__)
    height = png.height
    width = png.width

    image = png.data.flatten.map { |c| c.values }.join

    @textures = glGenTextures 1
    glBindTexture GL_TEXTURE_2D, @textures[0]
    glTexImage2D GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
  end

end

Lesson16.new

