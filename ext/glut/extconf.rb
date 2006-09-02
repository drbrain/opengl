#
# Last edit by previous maintainer:
# 2003/08/17 03:04:32, yoshi
#
# $Date: 2006/07/11 05:04:08 $
# $Author: john $
#
# Copyright (C) 1999 - 2005 Yoshi <yoshi@giganet.net>
# Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
#
# This program is distributed under the terms of the MIT license.
# See the included COPYRIGHT file for the terms of this license.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# The two extension modules being built here are "opengl" and "glut".
# (The one named "opengl" contains GLU as well.)

require "mkmf"

gl_libname = ""
glu_libname = ""
glut_libname = ""

modules = ""
ogl_flg = false
glut_flg = false

File.unlink( "Makefile" )      if ( FileTest.exist? "Makefile" )
File.unlink( "Makefile.ogl" )  if ( FileTest.exist? "Makefile.ogl" )
File.unlink( "Makefile.glut" ) if ( FileTest.exist? "Makefile.glut" )

header = nil

case RUBY_PLATFORM
    when /cygwin/
        $CFLAGS = "-DWIN32"
        gl_libname = "opengl32"
        glu_libname = "glu32"
        glut_libname = "glut32"
        header=[ "GL/gl.h", "GL/glu.h", "GL/glut.h" ]

    when /mswin32/
        $CFLAGS = "-DWIN32"
        gl_libname = "opengl32"
        glu_libname = "glu32"
        glut_libname = "glut32"

    when /darwin/
        $CFLAGS = " -I. -I/System/Library/Frameworks/OpenGL.framework/Headers -I/System/Library/Frameworks/GLUT.framework/Headers"
        $DLDFLAGS = " -framework OpenGL -framework GLUT -framework Foundation"
        $LIBS = " -lruby"

        gl_libname = "GL"
        glu_libname = "GLU"
        glut_libname = "glut"

    else
        # $CPPFLAGS += " -I."  <--- Not sure why that was there since this is a C module (not C++).
        idir, ldir = dir_config( "x11", "/usr/X11R6" )

        have_library( "Xi",   "XAllowDeviceEvents" )
        have_library( "Xext", "XMITMiscGetBugMode" )
        have_library( "Xmu",  "XmuAddCloseDisplayHook" )
        have_library( "X11",  "XOpenDisplay" )

        gl_libname = "GL"
        glu_libname = "GLU"
        glut_libname = "glut"
end

dir_config( "opengl", idir, ldir )
dir_config( "glut", idir, ldir )


def have_ogl_library( lib, func = 'main' )
    have_library( lib, func ) ||
    have_library( "Mesa" + lib, func ) ||
    find_library( lib, func, "/System/Library/Frameworks/OpenGL.framework/Libraries/" )
end

# Briefly tried this for Mac OS X but couldn't get it to work. ---JohnMG
#def have_glut_library( lib, func = 'main' )
#    have_library( lib, func ) ||
#    have_library( "Mesa" + lib, func ) ||
#    #find_library( lib, func, "/System/Library/Frameworks/GLUT.framework/Libraries/" )
#    find_library( lib, func, "/System/Library/Frameworks/GLUT.framework/Versions/Current/Libraries/" )
#end
#
# Ok. This hack is for Mac OS X until mkmf gets support for OS X.
# No idea why the OS X glut bundle gets built even though the have_library
# call doesn't find anything. XXX
def have_glut_library( lib, func = 'main' )
    have_library( lib, func ) ||
    File.exist?("/System/Library/Frameworks/GLUT.framework")
end


# In Yoshi's original readme, he had this to say about the following
# have_library call:
# > Note: if a sample app crashes with an X error, comment out the line
# > with `have_library("pthread","pthread_create")` in extconf.rb,
# > recompile the module, and try again.
#have_library( "pthread", "pthread_create" )


$objs = [ "glu.o", "ogl.o", "rbogl.o" ]
if have_ogl_library( gl_libname ) && have_ogl_library( glu_libname )
    create_makefile( "opengl" )
    File.rename( "Makefile", "Makefile.ogl" )
    modules = modules + "opengl.#{CONFIG['DLEXT']}"
    ogl_flg = true
else
    puts "Can't create OpenGL module!"
    exit 1
end


$objs = [ "glut.o" ]
if have_glut_library( glut_libname )
    create_makefile( "glut" )
    File.rename( "Makefile", "Makefile.glut" )
    modules = "glut.#{CONFIG['DLEXT']} " + modules
    glut_flg = true
end


# Now that the two makefiles that build the actual extension modules
# are ready, we'll need a master makefile to delegate work to them.
open( "Makefile", "w" ) { |f|
    v = $nmake ? '{$(srcdir)}' : ''
    f.write <<EOT
SHELL = /bin/sh
srcdir = #{$srcdir}
VPATH = $(srcdir)

all: #{modules}

opengl.#{CONFIG['DLEXT']}: #{v}rbogl.c #{v}ogl.c #{v}glu.c #{v}rbogl.h
	@echo "Now Making opengl extension module..."
	@$(MAKE) -f Makefile.ogl

glut.#{CONFIG['DLEXT']}: #{v}glut.c
	@echo "Now Making glut extension module..."
	@$(MAKE) -f Makefile.glut

clean:
#{"\t@$(MAKE) -f Makefile.ogl clean" if (ogl_flg)}
#{"\t@$(MAKE) -f Makefile.glut clean" if (glut_flg)}

distclean:
#{"\t@$(MAKE) -f Makefile.ogl distclean" if (ogl_flg)}
#{"\t@$(MAKE) -f Makefile.glut distclean" if (glut_flg)}

install: #{modules}
#{"\t@$(MAKE) -f Makefile.ogl install" if (ogl_flg)}
#{"\t@$(MAKE) -f Makefile.glut install" if (glut_flg)}

site-install: #{modules}
#{"\t@$(MAKE) -f Makefile.ogl site-install" if (ogl_flg)}
#{"\t@$(MAKE) -f Makefile.glut site-install" if (glut_flg)}
EOT
}
