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
require 'test/unit'
require '../ext/gl/GL'
include GL

# Test that an include of GL forces makes the OpenGL namespace available in
# the current module.
#   include GL
#   ...
#   GL::GL_VERSION_1_1 --> 1
#   GL_VERSION_1_1     --> 1
class GlIncludeTest < Test::Unit::TestCase
    def test_require_of_gl
        assert_equal 1, GL::GL_VERSION_1_1
        assert_equal 1, GL_VERSION_1_1
    end
end
