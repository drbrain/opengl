# This is based on the ruby-opengl code from the old ruby-opengl project:
#
# This module provides access to the GL and GLU methods and constants
# in the customary C way.
#
# Thanks to Ilmari Heikkinen for this code, and to Bill Kelly for a
# previous version.

require '../ext/gl/GL'

module GL
    extend self
    include GL

    GL.constants.each do |cn|
        n = cn.sub(/^GL_/,'')
        begin
            const_set( n, GL.const_get( cn ) )
        rescue
            puts "=== #{__FILE__} FAILED on Constant: #{cn} --> #{n}"
        end
    end

    GL.methods( false ).each do |mn|
        n = mn.sub(/^gl/,'')
        begin
            alias_method( n, mn )
            public( n )
        rescue
            puts "=== #{__FILE__} FAILED on Method: #{mn} --> #{n}"
        end
    end
end

## Usage:
# require 'opengl_c'
# OpenGL.glFooBar( OpenGL::GL_FOO_BAR )
# include OpenGL
# glFooBar( GL_FOO_BAR )
