require "../ext/gl/GL"
require "../ext/glut/GLUT"
require "rational"

require "../lib/gl_prev"
require "../lib/glut_prev"

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
      shade = i.to_f/RAMPSIZE.to_f;
      GLUT.SetColor(RAMP1START+i, 0, shade, 0.0);
      GLUT.SetColor(RAMP2START+i, 0, 0, shade);
   end

   GL.Enable(GL::LINE_SMOOTH);
   GL.Hint(GL::LINE_SMOOTH_HINT, GL::DONT_CARE);
   GL.LineWidth(1.5);

   GL.ClearIndex(RAMP1START);
end

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT);

   GL.Indexi(RAMP1START);
   GL.PushMatrix();
   GL.Rotate(-$rotAngle, 0.0, 0.0, 0.1);
   GL.Begin(GL::LINES);
      GL.Vertex(-0.5, 0.5);
      GL.Vertex(0.5, -0.5);
   GL.End
   GL.PopMatrix();

   GL.Indexi(RAMP2START);
   GL.PushMatrix();
   GL.Rotate($rotAngle, 0.0, 0.0, 0.1);
   GL.Begin(GL::LINES);
      GL.Vertex(0.5, 0.5);
      GL.Vertex(-0.5, -0.5);
   GL.End
   GL.PopMatrix();

   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL.Viewport(0, 0,  w,  h);
   GL.MatrixMode(GL::PROJECTION);
   GL.LoadIdentity();
   if (w <= h)
      GLU.Ortho2D(-1.0, 1.0, -h.to_f/w.to_f, h.to_f/w.to_f);
   else
      GLU.Ortho2D(w.to_f/h.to_f, w.to_f/h.to_f, -1.0, 1.0);
   end
   GL.MatrixMode(GL::MODELVIEW);
   GL.LoadIdentity();
}

keyboard = Proc.new {|key, x, y|
   case (key)
      when 'r'[0]
         $rotAngle += 20
         $rotAngle = 0 if ($rotAngle >= 360)
         GLUT.PostRedisplay();
      when 'R'[0]
         $rotAngle -= 20
         $rotAngle = 360 if ($rotAngle <= 0)
         GLUT.PostRedisplay();
      when 27
         exit(0);
   end
}

#  Main Loop
#  Open window with initial window size, title bar,
#  color index display mode, and handle input events.
#
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::INDEX);
   GLUT.InitWindowSize(200, 200);
   GLUT.CreateWindow($0);
   myinit
   GLUT.ReshapeFunc(reshape);
   GLUT.KeyboardFunc(keyboard);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop
