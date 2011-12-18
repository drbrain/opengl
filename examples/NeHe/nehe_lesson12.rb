require 'opengl'
require 'png'
require 'png/reader'

class Lesson12
  include Gl
  include Glu
  include Glut

  def initialize
    @textures = nil
    @box = nil
    @top = nil
    @xrot = 0
    @yrot = 0

    @box_color = [
      [1.0, 0.0, 0.0],
      [1.0, 0.5, 0.0],
      [1.0, 1.0, 0.0],
      [0.0, 1.0, 0.0],
      [0.0, 1.0, 1.0],
    ]

    @top_color = [
      [0.5, 0.0, 0.0],
      [0.5, 0.25, 0.0],
      [0.5, 0.5, 0.0],
      [0.0, 0.5, 0.0],
      [0.0, 0.5, 0.5],
    ]

    glutInit

    glutInitDisplayMode GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH
    glutInitWindowSize 640, 480
    glutInitWindowPosition 0, 0

    @window = glutCreateWindow "NeHe Lesson 12 - ruby-opengl version"

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
    build_lists

    glEnable GL_TEXTURE_2D
    glShadeModel GL_SMOOTH
    glClearColor 0.0, 0.0, 0.0, 0.5
    glClearDepth 1.0
    glEnable GL_DEPTH_TEST
    glDepthFunc GL_LEQUAL

    glEnable GL_LIGHT0
    glEnable GL_LIGHTING
    glEnable GL_COLOR_MATERIAL

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

    true
  end

  def build_lists
    @box = glGenLists 2
    @top = @box + 1

    glNewList @box, GL_COMPILE do
      glBegin GL_QUADS do
        # Bottom Face
        glTexCoord2f(1, 1); glVertex3f(-1, -1, -1)
        glTexCoord2f(0, 1); glVertex3f( 1, -1, -1)
        glTexCoord2f(0, 0); glVertex3f( 1, -1,  1)
        glTexCoord2f(1, 0); glVertex3f(-1, -1,  1)
        # Front Face
        glTexCoord2f(0, 0); glVertex3f(-1, -1,  1)
        glTexCoord2f(1, 0); glVertex3f( 1, -1,  1)
        glTexCoord2f(1, 1); glVertex3f( 1,  1,  1)
        glTexCoord2f(0, 1); glVertex3f(-1,  1,  1)
        # Back Face
        glTexCoord2f(1, 0); glVertex3f(-1, -1, -1)
        glTexCoord2f(1, 1); glVertex3f(-1,  1, -1)
        glTexCoord2f(0, 1); glVertex3f( 1,  1, -1)
        glTexCoord2f(0, 0); glVertex3f( 1, -1, -1)
        # Right face
        glTexCoord2f(1, 0); glVertex3f( 1, -1, -1)
        glTexCoord2f(1, 1); glVertex3f( 1,  1, -1)
        glTexCoord2f(0, 1); glVertex3f( 1,  1,  1)
        glTexCoord2f(0, 0); glVertex3f( 1, -1,  1)
        # Left Face
        glTexCoord2f(0, 0); glVertex3f(-1, -1, -1)
        glTexCoord2f(1, 0); glVertex3f(-1, -1,  1)
        glTexCoord2f(1, 1); glVertex3f(-1,  1,  1)
        glTexCoord2f(0, 1); glVertex3f(-1,  1, -1)
      end
    end

    glNewList @top, GL_COMPILE do
      glBegin GL_QUADS do
        # Top Face
        glTexCoord2f(0, 1); glVertex3f(-1,  1, -1)
        glTexCoord2f(0, 0); glVertex3f(-1,  1,  1)
        glTexCoord2f(1, 0); glVertex3f( 1,  1,  1)
        glTexCoord2f(1, 1); glVertex3f( 1,  1, -1)
      end
    end
  end

  def draw_gl_scene
    glClear GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT

    glBindTexture GL_TEXTURE_2D, @textures[0]

    (1..5).each do |y|
      (0..y).each do |x|
        glLoadIdentity
        glTranslate 1.4 + x * 2.8 - y * 1.4, (6 - y) * 2.4 - 7, -20

        glRotatef (45 - 2.0 * y) + @xrot, 1, 0, 0
        glRotatef 45 + @yrot,             0, 1, 0

        glColor3fv @box_color[y - 1]
        glCallList @box

        glColor3fv @top_color[y - 1]
        glCallList @top
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
    when 'X' then @xrot += 0.5
    when 'x' then @xrot -= 0.5
    when 'Y' then @yrot += 0.5
    when 'y' then @yrot -= 0.5
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

Lesson12.new

