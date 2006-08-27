#-*-ruby-*-
#--
# Copyright 2006 by Peter McLain
# All rights reserved.
# See MIT-LICENSE for permissions.
#++
require 'mkmf'
$objs = %w( rbogl.o gl_wrap.o )
create_makefile('GL')
