require 'opengl'
require 'png'
require 'png/reader'

class Lesson19
  include Gl
  include Glu
  include Glut

  Particle = Struct.new(:active, :life, :fade,
                        :r, :g, :b,
                        :x, :y, :z,
                        :xi, :yi, :zi,
                        :xg, :yg, :zg)

  def initialize
    @fullscreen = true
    @rainbow = true
    @slowdown = 2.0
    @x_speed = 2.0
    @y_speed = 5.0
    @zoom = -100.0
    @textures = nil
    @colors = [
      [1.0,  0.5,  0.5],
      [1.0,  0.75, 0.5],
      [1.0,  1.0,  0.5],
      [0.75, 1.0,  0.5],
      [0.5,  1.0,  0.5],
      [0.5,  1.0,  0.75],
      [0.5,  1.0,  1.0],
      [0.5,  0.75, 1.0],
      [0.5,  0.5,  1.0],
      [0.75, 0.5,  1.0],
      [1.0,  0.5,  1.0],
      [1.0,  0.5,  0.75],
    ]
    @color = 0

    @max_particles = 1_000
    @particles = (0...@max_particles).map do |i|
      Particle.new(true,                       # active
                   1.0,                        # life
                   rand(100) / 1000.0 + 0.003, # fade
                   @colors[i % 12][0],         # red
                   @colors[i % 12][1],         # green
                   @colors[i % 12][2],         # blue
                   0.0, 0.0, 0.0,              # x, y, z
                   (rand * 2 - 1),             # x speed
                   (rand * 2 - 1),             # y speed
                   (rand * 2 - 1),             # z speed
                    0.0,                       # x gravity
                   -0.8,                       # y gravity
                    0.0)                       # z gravity
    end

    glutInit

    glutInitDisplayMode GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH
    glutInitWindowSize 640, 480
    glutInitWindowPosition 0, 0

    @window = glutCreateWindow "NeHe Lesson 19 - ruby-opengl version"

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
    glShadeModel GL_SMOOTH
    glClearColor 0, 0, 0, 0

    glClearDepth 1.0
    glDisable GL_DEPTH_TEST
    glEnable GL_BLEND
    glBlendFunc GL_SRC_ALPHA, GL_ONE
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST
    glHint GL_POINT_SMOOTH_HINT, GL_NICEST
    glEnable GL_TEXTURE_2D
    glBindTexture GL_TEXTURE_2D, @textures[0]
  end

  def reshape width, height
    width  = width.to_f
    height = height.to_f
    height = 1.0 if height.zero?

    glViewport 0, 0, width, height

    glMatrixMode GL_PROJECTION
    glLoadIdentity

    gluPerspective 45, width / height, 0.1, 200

    glMatrixMode GL_MODELVIEW
    glLoadIdentity
  end

  def draw_gl_scene
    glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
    glLoadIdentity

    @particles.each do |particle|
      next unless particle.active
      
      x = particle.x
      y = particle.y
      z = particle.z + @zoom

      glColor4f particle.r, particle.g, particle.b, particle.life

      glBegin GL_TRIANGLE_STRIP do
        glTexCoord2d 1, 1; glVertex3f x + 0.5, y + 0.5, z
        glTexCoord2d 0, 1; glVertex3f x - 0.5, y + 0.5, z
        glTexCoord2d 1, 0; glVertex3f x + 0.5, y - 0.5, z
        glTexCoord2d 0, 0; glVertex3f x - 0.5, y - 0.5, z
      end

      particle.x += particle.xi / @slowdown
      particle.y += particle.yi / @slowdown
      particle.z += particle.zi / @slowdown

      particle.xi += particle.xg
      particle.yi += particle.yg
      particle.zi += particle.zg

      particle.life -= particle.fade

      if particle.life < 0 then
        particle.life = 1.0
        particle.fade = rand(100) / 1000.0 + 0.003

        particle.x = 0.0
        particle.y = 0.0
        particle.z = 0.0

        particle.xi = @x_speed + rand * 2 - 1
        particle.yi = @y_speed + rand * 2 - 1
        particle.zi =            rand * 2 - 1

        particle.r = @colors[@color][0]
        particle.g = @colors[@color][1]
        particle.b = @colors[@color][2]

        @color += 1
        @color %= @colors.length - 1
      end
    end

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
    png = PNG.load_file File.expand_path('../particle.png', __FILE__)
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

Lesson19.new

