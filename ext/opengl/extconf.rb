require 'mkmf'

have_header('dlfcn.h') || have_header('windows.h')

ok = have_library('dl', 'dlopen', ['dlfcn.h']) ||
  have_library('user32', 'GetProcAddress', ['windows.h'])

have_header 'stdint.h'
have_header 'inttypes.h'

have_struct_member 'struct RFloat', 'float_value'

have_type 'int64_t', 'stdint.h'
have_type 'uint64_t', 'stdint.h'

if ok then
  create_header
  create_makefile 'opengl/opengl'
end
