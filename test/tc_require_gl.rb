#--
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
#++

if __FILE__ == $0
    # If we are being called from the command line, e.g., ruby foo.rb, then
    # fixup the load path so we can find the OpenGL extension libs
    $: << File.join(File.dirname(__FILE__), '..', 'ext')
end

require 'test/unit'
require 'gl/GL'

# Test that a require but not include of GL forces the use of the full
# namespace qualifiers:
#   require GL
#   ...
#   GL::GL_VERSION_1_1 --> 1
#   GL_VERSION_1_1     --> error
class GLRequireTest < Test::Unit::TestCase
    def test_require_of_gl
        assert_equal 1, GL::GL_VERSION_1_1
        assert_raise(NameError) { GL_VERSION_1_1 }
    end
end
