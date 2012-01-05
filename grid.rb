require 'opengl'
require 'matrix'
require 'png'
require 'png/reader'

class Hit

  def initialize count, x, y
    @count = count

    @particles = (1..@count).map do
      Particle.new x, y
    end

    @dead = 0
  end

  def draw
    glPointSize 1

    @particles.each do |particle|
      particle.draw

      @dead += 1 if particle.dead?
    end
  end

  def finished?
    @dead >= @count
  end

end

class Display
  include Gl
  include Glu
  include Glut

  def initialize
    @fullscreen = false
    @scroll_x = 0
    @scroll_y = 0
    @now = nil

    @grid = Grid.new 100, 20, 20
    @grid_offset  = @grid.offset
    @grid_size    = @grid.size
    @grid_unscale = @grid.unscale

    @vessel_z = -50

    @hits = []
    @shots = []

    @black = Vector[0, 0, 0]
    @blue  = Vector[0, 0, 1]
    @green = Vector[0, 1, 0]
    @red   = Vector[1, 0, 0]
    @white = Vector[1, 1, 1]

    glutInit

    glutInitDisplayMode GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
    glutInitWindowSize 600, 400
    glutInitWindowPosition 600, 0

    @window = glutCreateWindow 'grid'

    glutDisplayFunc :draw_scene
    glutReshapeFunc :reshape
    glutKeyboardFunc :keyboard
    glutTimerFunc 30, :timer, 0
    #glutVisibilityFunc :visible

    reshape 640, 480

    init_gl

    glutMainLoop
  end

end

Display.new

