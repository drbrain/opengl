#
# Last edit by previous maintainer:
# 2003/08/17 03:04:32, yoshi
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

# This is the extconf.rb file for creating the glut module.

require "mkmf"

gl_libname = ""
glu_libname = ""
glut_libname = ""

File.unlink( "Makefile" ) if ( FileTest.exist? "Makefile" )

case RUBY_PLATFORM
    when /cygwin/
        $CFLAGS = "-DWIN32"
        gl_libname = "opengl32"
        glu_libname = "glu32"
        glut_libname = "glut32"

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
        idir, ldir = dir_config( "x11", "/usr/X11R6" )

        have_library( "Xi",   "XAllowDeviceEvents" )
        have_library( "Xext", "XMITMiscGetBugMode" )
        have_library( "Xmu",  "XmuAddCloseDisplayHook" )
        have_library( "X11",  "XOpenDisplay" )

        gl_libname = "GL"
        glu_libname = "GLU"
        glut_libname = "glut"
end

dir_config( "glut", idir, ldir )

def have_gl_library( lib, func = 'main' )
    have_library( lib, func ) ||
    have_library( "Mesa" + lib, func ) ||
    find_library( lib, func, "/System/Library/Frameworks/OpenGL.framework/Libraries/" )
end

def have_glu_library( lib, func = 'main' )
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

# $objs = [ "glu.o", "ogl.o", "rbogl.o" ]
if have_gl_library( gl_libname ) &&
   have_glu_library( glu_libname) &&
   have_glut_library( glut_libname )
    create_makefile( "glut" )
else
    puts "Error: Couldn't create the makefile for the GLUT module."
    exit 1
end
