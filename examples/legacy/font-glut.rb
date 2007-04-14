require "gl_prev"
require "glu_prev"
require "glut_prev"


display = Proc.new {
   GL::Clear(GL::COLOR_BUFFER_BIT);
   GL.LoadIdentity

   GL::RasterPos2d(20,20)
   "Hello Bitmap".each_byte { |x| GLUT.BitmapCharacter(GLUT::BITMAP_9_BY_15, x) }

   GL.Translate(0, 50, 0)
   GL.Scale(0.25, 0.25, 1)
   "Hello Stroke".each_byte { |x| GLUT.StrokeCharacter(GLUT::STROKE_ROMAN, x) }

   GL.Flush();
}

reshape = Proc.new {|w, h|
   GL::Viewport(0, 0,  w,  h);
   GL::MatrixMode(GL::PROJECTION);
   GL::LoadIdentity();
   GL::Ortho(0.0, w, 0.0, h, -1.0, 1.0);
   GL::MatrixMode(GL::MODELVIEW);
}


#  Main Loop
#  Open window with initial window size, title bar, 
#  color index display mode, and handle input events.
#
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB);
   GLUT.InitWindowSize(200, 200);
   GLUT.CreateWindow($0);

   GLUT.ReshapeFunc(reshape);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop

