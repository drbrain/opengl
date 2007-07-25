#!/usr/bin/env ruby -rubygems
require 'opengl'
require 'rational'
include Gl,Glu,Glut


RAMPSIZE=16
RAMP1START=32
RAMP2START=48

STDOUT.sync = TRUE
$rotAngle = 0

# Initialize antialiasing for color index mode,
# including loading a green color ramp starting
# at RAMP1START, and a blue color ramp starting
# at RAMP2START. The ramps must be a multiple of 16.
def myinit
	for i in (0..RAMPSIZE)
		shade = i.to_f/RAMPSIZE.to_f
		glutSetColor(RAMP1START+i, 0, shade, 0.0)
		glutSetColor(RAMP2START+i, 0, 0, shade)
	end
	
	glEnable(GL_LINE_SMOOTH)
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE)
	glLineWidth(1.5)
	
	glClearIndex(RAMP1START)
end

display = Proc.new do
	glClear(GL_COLOR_BUFFER_BIT)
	
	glIndexi(RAMP1START)
	glPushMatrix()
	glRotate(-$rotAngle, 0.0, 0.0, 0.1)
	glBegin(GL_LINES)
	glVertex(-0.5, 0.5)
	glVertex(0.5, -0.5)
	glEnd
	glPopMatrix()
	
	# glIndexi(RAMP2START)
	glPushMatrix()
	glRotate($rotAngle, 0.0, 0.0, 0.1)
	glBegin(GL_LINES)
	glVertex(0.5, 0.5)
	glVertex(-0.5, -0.5)
	glEnd
	glPopMatrix()
	
	glutSwapBuffers()
end

reshape = Proc.new do |w, h|
	glViewport(0, 0,  w,  h)
	glMatrixMode(GL_PROJECTION)
	glLoadIdentity()
	if (w <= h)
		gluOrtho2D(-1.0, 1.0, -h.to_f/w.to_f, h.to_f/w.to_f)
	else
		gluOrtho2D(w.to_f/h.to_f, w.to_f/h.to_f, -1.0, 1.0)
	end
	glMatrixMode(GL_MODELVIEW)
	glLoadIdentity()
end

keyboard = Proc.new do |key, x, y|
	case (key)
	when 'r'[0]
		$rotAngle += 20
		$rotAngle = 0 if ($rotAngle >= 360)
		glutPostRedisplay()
	when 'R'[0]
		$rotAngle -= 20
		$rotAngle = 360 if ($rotAngle <= 0)
		glutPostRedisplay()
	when 27
		exit(0)
	end
end

#  Main Loop
#  Open window with initial window size, title bar,
#  color index display mode, and handle input events.
#
glutInit
glutInitDisplayMode(GLUT_DOUBLE | GLUT_INDEX)
glutInitWindowSize(500, 500)
glutInitWindowPosition(100, 100)
glutCreateWindow($0)
myinit
glutReshapeFunc(reshape)
glutKeyboardFunc(keyboard)
glutDisplayFunc(display)
glutMainLoop
