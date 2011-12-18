require 'opengl'
require 'png'
require 'png/reader'

class Lesson09
  include Gl
  include Glu
  include Glut

  Star = Struct.new :r, :g, :b, :distance, :angle

  def initialize
    @textures = nil
    @filter = 0
    @twinkle = false
    @zoom = -15.0
    @tilt = 90.0
    @spin = 0.0
    @fullscreen = false
    @last_draw = Time.now

    @star_count = 50
    @stars = (0...@star_count).map do |i|
      distance = i.to_f / @star_count * 5.0
      angle = 0.0

      Star.new rand(256), rand(256), rand(256), distance, angle
    end

    glutInit

    glutInitDisplayMode GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH
    glutInitWindowSize 640, 480
    glutInitWindowPosition 0, 0

    @window = glutCreateWindow "NeHe Lesson 09 - ruby-opengl version"

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
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST
    glBlendFunc GL_SRC_ALPHA, GL_ONE
    glEnable GL_BLEND

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
    return if 0.01 > Time.now - @last_draw
    @last_draw = Time.now

    glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
    glBindTexture GL_TEXTURE_2D, @textures[@filter]

    @stars.each_with_index do |star, i|
      glLoadIdentity
      glTranslatef 0.0, 0.0, @zoom
      glRotatef @tilt, 1.0, 0.0, 0.0
      glRotatef star.angle, 0.0, 1.0, 0.0

      glTranslatef star.distance, 0.0, 0.0

      glRotatef star.angle, 0.0, -1.0, 0.0
      glRotatef @tilt, -1.0, 0.0, 0.0

      if @twinkle then
        prev = @stars[i - 1]
        glColor4ub prev.r, prev.g, prev.b, 255

        glBegin GL_QUADS do
          glTexCoord2f 0.0, 0.0; glVertex3f -1.0, -1.0,  0.0
          glTexCoord2f 1.0, 0.0; glVertex3f  1.0, -1.0,  0.0
          glTexCoord2f 1.0, 1.0; glVertex3f  1.0,  1.0,  0.0
          glTexCoord2f 0.0, 1.0; glVertex3f -1.0,  1.0,  0.0
        end
      end

      glRotatef @spin, 0.0, 0.0, 1.0
      glColor4ub star.r, star.g, star.b, 255

      glBegin GL_QUADS do
        glTexCoord2f 0.0, 0.0; glVertex3f -1.0, -1.0,  0.0
        glTexCoord2f 1.0, 0.0; glVertex3f  1.0, -1.0,  0.0
        glTexCoord2f 1.0, 1.0; glVertex3f  1.0,  1.0,  0.0
        glTexCoord2f 0.0, 1.0; glVertex3f -1.0,  1.0,  0.0
      end

      @spin += 0.01
      star.angle += i.to_f / @star_count
      star.distance -= 0.01

      if star.distance < 0 then
        star.distance += 5.0
        star.r = rand 256
        star.g = rand 256
        star.b = rand 256
      end
    end

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
    when 'F' then 
      @fullscreen = !@fullscreen

      if @fullscreen then
        glutFullScreen
      else
        glutPositionWindow 0, 0
      end
    when 'f' then
      @filter += 1
      @filter %= 3

      puts "texture #{@filter}"
    when 'W' then
      @twinkle = !@twinkle

      puts "twinkle #{@twinkle ? 'on' : 'off'}"
    when 'T' then @tilt += 0.5
    when 't' then @tilt -= 0.5
    when 'Z' then @zoom += 0.2
    when 'z' then @zoom -= 0.2
    else
      puts key
    end

    glutPostRedisplay
  end

  def load_texture
    png = PNG.load_file File.expand_path('../star.png', __FILE__)
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

Lesson09.new

