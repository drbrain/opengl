# $Date: 2006/07/13 06:27:12 $
# $Author: john $

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


# This module provides access to the GL and GLU methods and constants
# in the customary C way.
#
# Thanks to Ilmari Heikkinen for this code, and to Bill Kelly for a
# previous version.

#require 'opengl'

module GL
    extend self
    include GL
#    include GLU
    
    GL.methods( false ).each do |mn|
        alias_method( "gl#{mn}", mn )
        public( "gl#{mn}" )
    end
    
#     GLU.methods( false ).each do |mn|
#         alias_method( "glu#{mn}", mn )
#         public( "glu#{mn}" )
#     end
    
    GL.constants.each do |cn|
        const_set( "GL_#{cn}", GL.const_get( cn ) )
    end
    
#     GLU.constants.each do |cn|
#         const_set( "GLU_#{cn}", GLU.const_get( cn ) )
#     end
end

## Usage:
# require 'opengl_c'
# OpenGL.glFooBar( OpenGL::GL_FOO_BAR )
# include OpenGL
# glFooBar( GL_FOO_BAR )
