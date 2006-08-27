# This is based on the ruby-opengl code from the old ruby-opengl project:
#
# This module provides access to the GL and GLU methods and constants
# in the customary C way.
#
# Thanks to Ilmari Heikkinen for this code, and to Bill Kelly for a
# previous version.

require '../ext/glut/GLUT'

module GLUT
    extend self
    include GLUT

    GLUT.constants.each do |cn|
        n = cn.sub(/^GLUT_/,'')
        begin
            const_set( n, GLUT.const_get( cn ) )
        rescue
            puts "=== #{__FILE__} FAILED on Constant: #{cn} --> #{n}"
        end
    end

    GLUT.methods( false ).each do |mn|
        n = mn.sub(/^glut/,'')
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
