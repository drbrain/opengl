ruby-opengl
===========

ruby-opengl consists of Ruby extension modules that are bindings for
the [OpenGL][], GLU, and [GLUT][] libraries. ruby-opengl is:

* still somewhat experimental at this point,
* intended to be a replacement for [Yoshi's ruby-opengl][],
  and
* a continuation of the now halted recent project of the
  same name ([halted ruby-opengl][]).

It's licensed under the MIT license. Please see the included MIT-LICENSE
file for the terms of the license.


[ruby-opengl]: http://rubyforge.org/projects/ruby-opengl/
[OpenGL]: http://www.opengl.org/
[GLUT]: http://www.opengl.org/documentation/specs/glut/spec3/spec3.html
[SWIG]: http://www.swig.org/

[Yoshi's ruby-opengl]: http://www2.giganet.net/~yoshi/
[halted ruby-opengl]: http://www.simisen.com/cgi-bin/jmg/ruby-opengl.rb


Status: Pre-Alpha
-----------------

As for the status of what we're currently experimenting on:

* Compiles and runs on Mac OS X.
* May compile on GNU/Linux, but doesn't run (yet).
* Very few of the OpenGL calls have been excercised, let alone tested. I
  expect that many of them will run fine.
* No thought has yet been directed toward performance.


Code layout
-----------

The directory structure is:

* `docs/` -- Contains documentation for the project (from which this
  website is generated).
* `ext/` -- Contains the source files needed to compile the extension
  modules.
* `lib/` -- Ruby files that provide glue code to run programs written in
  the naming style of Yoshi's code.
* `test/` -- Contains sample ruby files that make OpenGL and GLUT calls.
  No real tests so far.
* `utils` -- some under-construction utility scripts to help generate
  extension module source from GL header files.
