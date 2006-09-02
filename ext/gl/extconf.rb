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

# This is the extconf.rb file for creating the gl module.

require "mkmf"

gl_libname = ""

File.unlink( "Makefile" ) if ( FileTest.exist? "Makefile" )

case RUBY_PLATFORM
    when /cygwin/
        $CFLAGS = "-DWIN32"
        gl_libname = "opengl32"

    when /mswin32/
        $CFLAGS = "-DWIN32"
        gl_libname = "opengl32"

    when /darwin/
        $CFLAGS = " -I. -I/System/Library/Frameworks/OpenGL.framework/Headers -I/System/Library/Frameworks/GLUT.framework/Headers"
        $DLDFLAGS = " -framework OpenGL -framework GLUT -framework Foundation"
        $LIBS = " -lruby"
        gl_libname = "GL"

    else
        idir, ldir = dir_config( "x11", "/usr/X11R6" )

        have_library( "Xi",   "XAllowDeviceEvents" )
        have_library( "Xext", "XMITMiscGetBugMode" )
        have_library( "Xmu",  "XmuAddCloseDisplayHook" )
        have_library( "X11",  "XOpenDisplay" )

        gl_libname = "GL"
end

dir_config( "gl", idir, ldir )

def have_gl_library( lib, func = 'main' )
    have_library( lib, func ) ||
    have_library( "Mesa" + lib, func ) ||
    find_library( lib, func, "/System/Library/Frameworks/OpenGL.framework/Libraries/" )
end


# In Yoshi's original readme, he had this to say about the following
# have_library call:
# > Note: if a sample app crashes with an X error, comment out the line
# > with `have_library("pthread","pthread_create")` in extconf.rb,
# > recompile the module, and try again.
#have_library( "pthread", "pthread_create" )


if have_gl_library( gl_libname )
    create_makefile( "gl" )
else
    puts "Error: Couldn't create the makefile for the GL module."
    exit 1
end
