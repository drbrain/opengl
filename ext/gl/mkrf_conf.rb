# extconf.rb for ruby-opengl's gl extension module.
#
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

require 'rubygems'
require 'mkrf'
require 'rbconfig'

Mkrf::Generator.new( 'gl' ) do |g|
    g.objects << "../common/rbogl.#{Config::CONFIG['OBJEXT']}"
    case RUBY_PLATFORM
    when /darwin/
        g.ldshared << ' -framework OpenGL'
    when /mswin32/
        g.cflags << ' -DWIN32'
        g.include_library( 'opengl32.lib', 'glVertex3d')
    else
        g.include_library( 'GL', 'glVertex3d')
    end
end
