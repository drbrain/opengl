
module Gl
  if RUBY_PLATFORM =~ /mingw|mswin/i
    class ImplementationWindows < Implementation
      DLPATH = "opengl32.dll"
      def self.open
        super(DLPATH, "wglGetProcAddress")
      end
    end

    Gl::DefaultImplementation = ImplementationWindows

  elsif RUBY_PLATFORM =~ /darwin/i
    class ImplementationOSX < Implementation
      DLPATH = "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
      def self.open
        super(DLPATH)
      end
    end

    Gl::DefaultImplementation = ImplementationOSX

  else
    class ImplementationGLX < Implementation
      DLPATH = "libGL.so"
      def self.open
        begin
          super(DLPATH, "glXGetProcAddress")
        rescue NotImplementedError
          super(DLPATH, "glXGetProcAddressARB")
        end
      end
    end

    Gl::DefaultImplementation = ImplementationGLX

  end
end
