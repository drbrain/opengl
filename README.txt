ruby-opengl
===========

[ruby-opengl][] consists of Ruby extension modules that are bindings for
the [OpenGL][], GLU, and [GLUT][] libraries. It is intended to be a
replacement for -- and uses the code from -- [Yoshi's ruby-opengl][].

It's licensed under the MIT license. Please see the included MIT-LICENSE
file for the terms of the license.


[ruby-opengl]: http://rubyforge.org/projects/ruby-opengl/
[OpenGL]: http://www.opengl.org/
[GLUT]: http://www.opengl.org/documentation/specs/glut/spec3/spec3.html


[Yoshi's ruby-opengl]: http://www2.giganet.net/~yoshi/


Latest release: 0.50.0 (October 23, 2007)
-----------------
Changes in this release:

* GLU and GLUT cleanup, bugfixes, some missing functions added - version 3.7
  of GLUT API is now requirement (previously 3.0)
* We added support for number of OpenGL extensions
* Some new examples and code cleanup
* Support for OpenGL 2.1 (that includes pixelpack/unpack buffer)
* Some code refactoring to remove duplicity
* Documentation update (still no API doc though)
* Lots of bugfixes.


Previous release: 0.40.1 (July 19, 2007)
-----------------
Changes in this release:

* Fixed build problems on Mac OS X


Current project status (SVN):
-----------------

* Supports OpenGL 2.0 and 2.1
* Compiles and runs on GNU/Linux, Mac OS X and Windows
* Some extensions are supported
* No useful documentation yet
