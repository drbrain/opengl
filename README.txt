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


Status: 0.33.0 Released!
-----------------

Current status:

* Support for OpenGL 2.0 and 2.1 in trunk
* Initial build support for Windows in trunk
* Compiles and runs on GNU/Linux (with Mesa) and Mac OS X.
* First gem release finally available.  Run 'gem install -y ruby-opengl' to try
  it out
* You must require 'gl' before using 'glu'
* REQUIRES mkrf 0.2.0 or higher to build and install properly
* To compile under Mac OS X you MUST install your own version of Ruby
  as the version included with Tiger (1.8.2) has a broken rbconfig
  and will fail to build the project properly.  Try either [MacPorts][],
  [Fink][], or [building your own from source][].
* New project maintainer

[Macports]: http://www.macports.org/
[Fink]: http://finkproject.org/
[building your own from source]: http://www.ruby-lang.org/en/downloads/

<br/>
<br/>
<br/>
<br/>
