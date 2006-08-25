require 'mkmf'
$objs = %w( rbogl.o gl_wrap.o )
create_makefile('gl')
