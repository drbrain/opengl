require 'mkmf'

def have_framework(fw, &b)
  checking_for fw do
    src = cpp_include("#{fw}/#{fw}.h") << "\n" "int main(void){return 0;}"
    if try_link(src, opt = "-ObjC -framework #{fw}", &b)
      $defs.push(format("-DHAVE_FRAMEWORK_%s", fw.tr_cpp))
      $LDFLAGS << " " << opt
      true
    else
      false
    end
  end
end unless respond_to? :have_framework

if ENV['CROSS_COMPILING']
  dir_config("installed")
end

ok =
  (have_framework('OpenGL') && have_framework('Cocoa')) ||
  have_library('opengl32.lib', 'glVertex3d') ||
  have_library('opengl32') ||
  have_library('GL',   'glVertex3d')

ok &&=
  have_header('GL/gl.h') ||
  have_header('OpenGL/gl.h') # OS X

have_header 'GL/glx.h'  # *NIX only?
have_header 'dlfcn.h'   # OS X dynamic loader
have_header 'windows.h'

have_header 'stdint.h'
have_header 'inttypes.h'

have_func 'wglGetProcAddress', 'wingdi.h' # Windows extension loader

have_struct_member 'struct RFloat', 'float_value'

have_type 'int64_t', 'stdint.h'
have_type 'uint64_t', 'stdint.h'

if ok then
  create_header
  create_makefile 'opengl/opengl'
end
