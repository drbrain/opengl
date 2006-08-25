#!/bin/bash -x
#
# Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# This is just a place-holder build script until we decide on a full
# make/mkmf based build or a Rake/mkrf

GENERATED_FILES="Makefile gl_wrap.c *.o gl.bundle"

# Clean all the junk out
rm -f $GENERATED_FILES

# This has to come before the extconf line, since mkmf won't make a target
# for glut unless there is a glut_wrap.c file lying around....
swig -ruby gl.i

# Generate the makefile
ruby extconf.rb --with-ldflags='-framework OpenGL'

# Now compile it up into a bundle
make
