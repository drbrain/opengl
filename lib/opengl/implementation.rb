
module Gl
  if RUBY_PLATFORM =~ /mingw|mswin/i
    class ImplementationWindows < Implementation
      DLPATH = "opengl32.dll"
      def self.open
        super(DLPATH, "wglGetProcAddress")
      end
    end

    Gl::DEFAULT_IMPLEMENTATION = ImplementationWindows

  elsif RUBY_PLATFORM =~ /darwin/i
    class ImplementationOSX < Implementation
      DLPATH = "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
      def self.open
        super(DLPATH)
      end
    end

    Gl::DEFAULT_IMPLEMENTATION = ImplementationOSX

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

    Gl::DEFAULT_IMPLEMENTATION = ImplementationGLX

  end
end
