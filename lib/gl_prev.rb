# Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
#
# This program is distributed under the terms of the MIT license.
# See the included MIT-LICENSE file for the terms of this license.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# This module provides access to the GL and GLU methods and constants
# in the way that they were available in previous versions of ruby-opengl.
#
# Thanks to Ilmari Heikkinen for this code, and to Bill Kelly for a
# previous version.

require '../ext/gl/gl'

module GL
    extend self
    include Gl

    Gl.constants.each do |cn|
        n = cn.sub(/^GL_/,'')
        begin
            const_set( n, Gl.const_get( cn ) )
        rescue
            puts "=== #{__FILE__} FAILED on Constant: #{cn} --> #{n}"
        end
    end

    Gl.methods( false ).each do |mn|
        n = mn.sub(/^gl/,'')
        begin
            alias_method( n, mn )
            public( n )
        rescue
            puts "=== #{__FILE__} FAILED on Method: #{mn} --> #{n}"
        end
    end
end
