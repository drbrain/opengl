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

# RxINC: This should really only require/include GL and GLU, but we
# currently have GLUT instead of GLU, so, to test the concept, we'll
# include GLUT.
#
#     Edit: added glu too. ---John
#
# RxINC: The hard-coded ../ext/gl... is ok for dev, but wrong for
# installation.

ext_dir = File.join(File.dirname(__FILE__), '..', 'ext')

require "#{ext_dir}/gl/GL"
require "#{ext_dir}/glu/GLU"
require "#{ext_dir}/glut/GLUT"

include GL
include GLU
include GLUT
