require "gl_prev"
require "glu_prev"
require "glut_prev"

begin
require "RMagick"
rescue Exception
    print "This sample needs RMagick Module.\n"
    exit
end

WIDTH = 200
HEIGHT = 200

display = Proc.new {
   GL.Clear(GL::COLOR_BUFFER_BIT);

   GL.Begin(GL::LINES);
      GL.Vertex(0.5, 0.5);
      GL.Vertex(-0.5, -0.5);
   GL.End

   GL.Flush();

   pixel_str = GL.ReadPixels(0, 0, WIDTH, HEIGHT, GL::RGBA, GL::SHORT)
   pixels = pixel_str.unpack("s*")
    
   image = Magick::Image.new(WIDTH, HEIGHT)
   image.import_pixels(0, 0, WIDTH, HEIGHT, "RGBA", pixels)
   image.flip!
#   image.write("opengl_window.gif")
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


#  Main Loop
#  Open window with initial window size, title bar, 
#  color index display mode, and handle input events.
#
   GLUT.Init
   GLUT.InitDisplayMode(GLUT::SINGLE | GLUT::RGB | GLUT::ALPHA);
   GLUT.InitWindowSize(WIDTH, HEIGHT);
   GLUT.CreateWindow($0);
   GLUT.ReshapeFunc(reshape);
   GLUT.DisplayFunc(display);
   GLUT.MainLoop

