#!/usr/bin/env ruby -w
#
# Try to figure out which functions in a header file are not in a
# corresponding wrapper file.

require 'rbconfig'

$INCLUDES = "-I#{Config::CONFIG['archdir']}"
case RUBY_PLATFORM
when /darwin/
  $INCLUDES << ' -F/System/Library/Frameworks'
else
end

# Regular expression to match a function definition, e.g.,
#
#  extern void APIENTRY glutBitmapCharacter(void *font, int character);
#  extern GLvoid * glMapBuffer (GLenum target, GLenum access);
#  extern GLvoid *glMapBufferARB(GLenum target, GLenum access);
#  extern const GLubyte * glGetString (GLenum name);
#  extern GLvoid * glMapBuffer (GLenum target, GLenum access);
#
#  The optional '*' between the return type and the func name is tricky
#  with the optional spaces, and the APIENTRY etc.  This may not be
#  optimal, but seems to work on the gl.h, glut.h and glu.h on my machine.
$func_regexp = /^extern         # Match a begining extern
  (?:\s+const)?                 # optional ' const' (don't consume $n)
  \s+                           # followed by whitespace
  (\w+)                         # followed by type ($1)
  \*?                           # optional '*'
  \s+                           # followed by whitespace
  (?:\*\s*)?                    # Optional '* ' (don't consume $n)
  (?:APIENTRY\s+)?              # with an optional "APIENTRY " (don't consume $n)
  (gl\w+)                       # followed by the function name ($2)
  \s*\(                         # optional whitespace between func name and open paren
  (.*)                          # Capture all the params ($3)
  \);                           # and the closing paren
  /x

class Stats
  attr_accessor :constants
  attr_accessor :functions
  attr_accessor :name

  def initialize(name)
    @name = name
    @constants = Array.new
    @functions = Array.new
  end

  def dump(dest=STDOUT)
    @functions.each {|fn| dest.puts "#{@name}: func: #{fn}"}
    @constants.each {|cn| dest.puts "#{@name}: const: #{cn}"}
  end
end

class Differ
  def initialize(h_file, c_file)
    @h_file = h_file
    @c_file = c_file
    @name = File.basename( @c_file, '.c')
  end

  def gather_from_h
    stats = Stats.new(File.basename(@h_file))
    `cat #{@h_file}`.each do |l|
      case l
      when /#define (GL\w*)\s+(.*)/
          stats.constants << $1
      when $func_regexp
        stats.functions << $2
      else
        #puts "SKIPPING #{l}"
      end
    end
    return stats
  end

  def gather_from_c
    c_pre = @name.upcase + "_"
    stats = Stats.new(@name)
    `cpp -dD -P #{$INCLUDES} #{@c_file}`.each do |l|
      case l
      when /rb_define_const\(mGLUT, "(.*)"/
        c_name = c_pre + $1
        stats.constants << c_name
        #puts "CONSTANT: #{c_name}"
      when /^#{@name}_(.*)\(/
          full_name = @name + $1
        stats.functions << full_name
        #puts "FUNCTION #{full_name}"
      else
        #puts "SKIP: #{l}"
      end
    end
    return stats
  end

  def dump
    c_stats = gather_from_c
    h_stats = gather_from_h
    h_stats.dump(File.open( "#{@name}_h.dump", 'w') )
    c_stats.dump(File.open( "#{@name}_c.dump", 'w') )
    File.open( "#{@name}_missing.dump", "w" ) do |f|
      f.puts((h_stats.functions - c_stats.functions).join("\n"))
      f.puts((h_stats.constants - c_stats.constants).join("\n"))
    end
  end
end

if $0 == __FILE__
  gl_h = '/System/Library/Frameworks/OpenGL.framework/Headers/gl.h'
  gl_c = '/Users/pbm/projects/ruby-opengl-trunk/ext/gl.c'
  gl_diff = Differ.new( gl_h, gl_c )
  gl_diff.dump

  glut_h = '/System/Library/Frameworks/GLUT.framework/Headers/glut.h'
  glut_c = '/Users/pbm/projects/ruby-opengl-trunk/ext/glut.c'
  glut_diff = Differ.new( glut_h, glut_c )
  glut_diff.dump
end
