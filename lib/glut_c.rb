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


# This module provides access to the GLUT methods and constants in the
# customary C way.
#
# Thanks to Ilmari Heikkinen for this code, and to Bill Kelly for a
# previous version.

#require 'glut'

module GLUT
    extend self
    include GLUT
    
    GLUT.methods( false ).each do |mn|
        puts mn
        alias_method( "glut#{mn}", mn )
        public( "glut#{mn}" )
    end
    
    GLUT.constants.each do |cn|
        const_set( "GLUT_#{cn}", GLUT.const_get( cn ) )
    end
end

## Usage:
# require 'glut_c'
# Glut.glutFooBar( Glut::GLUT_FOO_BAR )
# include Glut
# glutFooBar( GLUT_FOO_BAR )
