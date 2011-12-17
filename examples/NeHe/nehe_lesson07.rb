require 'opengl'
require 'png'
require 'png/reader'

class Lesson07
  include Gl
  include Glu
  include Glut

  def initialize
    @textures = nil
    @xrot = 0.0
    @yrot = 0.0
    @x_speed = 0.0
    @y_speed = 0.0
    @z = 0.0
    @ambient = [0.5, 0.5, 0.5, 1.0]
    @diffuse = [1.0, 1.0, 1.0, 1.0]
    @light_position = [0.0, 0.0, 2.0, 1.0]
    @filter = 0
    @keys = []
    @lighting = false
    @fullscreen = false

    glutInit

    glutInitDisplayMode GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH
    glutInitWindowSize 640, 480
    glutInitWindowPosition 0, 0

    @window = glutCreateWindow "NeHe Lesson 07 - ruby-opengl version"

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
    glClearColor 0.0, 0.0, 0.0, 0.5
    glClearDepth 1.0
    glEnable GL_DEPTH_TEST
    glDepthFunc GL_LEQUAL
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST

    glLightfv GL_LIGHT1, GL_AMBIENT, @ambient
    glLightfv GL_LIGHT1, GL_DIFFUSE, @diffuse
    glLightfv GL_LIGHT1, GL_POSITION, @light_position

    glEnable GL_LIGHT1

    true
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

    true
  end

  def draw_gl_scene
    glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
    glLoadIdentity
    glTranslatef 0.0, 0.0, @z

    glRotatef @xrot, 1.0, 0.0, 0.0
    glRotatef @yrot, 0.0, 1.0, 0.0

    glBindTexture GL_TEXTURE_2D, @textures[@filter]

    glBegin GL_QUADS do
      # front face
      glNormal3f( 0.0,  0.0,  1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f( 1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f(-1.0,  1.0,  1.0)

      # back face
      glNormal3f( 0.0,  0.0, -1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0, -1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)

      # top face
      glNormal3f( 0.0,  1.0,  0.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0,  1.0, -1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)

      # bottom face
      glNormal3f( 0.0, -1.0,  0.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0, -1.0,  1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)

      # right face
      glNormal3f( 1.0,  0.0,  0.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f( 1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f( 1.0,  1.0, -1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f( 1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f( 1.0, -1.0,  1.0)

      # left face
      glNormal3f(-1.0,  0.0,  0.0)
      glTexCoord2f(0.0, 0.0)
      glVertex3f(-1.0, -1.0, -1.0)
      glTexCoord2f(0.0, 1.0)
      glVertex3f(-1.0, -1.0,  1.0)
      glTexCoord2f(1.0, 1.0)
      glVertex3f(-1.0,  1.0,  1.0)
      glTexCoord2f(1.0, 0.0)
      glVertex3f(-1.0,  1.0, -1.0)
    end

    @xrot += @x_speed
    @yrot += @y_speed

    glutSwapBuffers
  end

  def idle
    glutPostRedisplay
  end

  def keyboard key, x, y
    case key
    when ?\e then
      glutDestroyWindow @window
      exit 0
    when 'l' then
      @lighting = !@lighting

      if @lighting then
        glEnable GL_LIGHTING
        puts "lights on"
      else
        glDisable GL_LIGHTING
        puts "lights off"
      end
    when 'f' then
      @filter += 1
      @filter %= 3

      puts "texture #{@filter}"
    when 'F' then 
      @fullscreen = !@fullscreen

      if @fullscreen then
        glutFullScreen
      else
        glutPositionWindow 0, 0
      end
    when 'X' then @x_speed += 0.01
    when 'x' then @x_speed -= 0.01
    when 'Y' then @y_speed += 0.01
    when 'y' then @y_speed -= 0.01
    when 'Z' then @z       += 1.0
    when 'z' then @z       -= 1.0
    else
      puts key
    end

    glutPostRedisplay
  end

  def load_texture
    png = PNG.load_file File.expand_path('../crate.png', __FILE__)
    height = png.height
    width = png.width

    image = png.data.flatten.map { |c| c.values }.join

    @textures = glGenTextures 3
    glBindTexture GL_TEXTURE_2D, @textures[0]
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST
    glTexImage2D GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image

    glBindTexture GL_TEXTURE_2D, @textures[1]
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    glTexImage2D GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image

    glBindTexture GL_TEXTURE_2D, @textures[2]
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST
    gluBuild2DMipmaps GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image
  end

end

Lesson07.new

