#!/usr/bin/env ruby
#
# Copyright (C) 2006 Vo Minh Thu <noteed@gmail.com>
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
#
# This script is based on mkwrap.rb. The goal is to try, by subclassing
# classes from mkwrap.rb, to handle gl.h instead of glut.h/freeglut.h.
# If the result seems fine, I will do the same for glut.h (and glu.h)

require 'mkwrap'

$debug = true

# FIXME for the moment, I don't handle gl*v functions and some other kinds...
HFunction.matcher = /[^(typedef)]*(void|int).*(gl[A-Z][^(]*)\s*\((.*)\)\s*;/
HFunction.ignore /v$/
HFunction.ignore /ARB$/
HFunction.ignore /MESA$/
HFunction.ignore /ATI$/
HFunction.ignore /TransposeMatrix/

class GlFunc < HFunction

    def write_wrap( file )

        str = "static VALUE\nrbgl_#@function_name (VALUE self#{args_type})\n{\n    "
        str += "return INT2NUM (" if @return_type != :void
        str += "#@function_name (#{args_string})"
        str += ")" if @return_type != :void
        str += ";\n"
        str += "    return Qnil;\n" if @return_type == :void
        str += "}\n\n"

        file << str
    end

    def write_init( file ) # could be in the super-class
        string = <<END
    rb_define_module_function (module, "#@function_name", rbgl_#@function_name, #{num_args});
END
        file << string
    end
end

HConstant.matcher = /#define\s+(GL\w+)\s+(.+)/
HConstant.ignore "GLAPI"
HConstant.ignore "GLAPIENTRYP"

class Wrapper
    def process( line )

        if (function = GlFunc.construct?( line ))
            @functions_count += 1

            function.write_wrap @file_wrap_func
            function.write_init @file_init_func

        elsif (constant = HConstant.construct?( line ))
            @constants_count += 1
            constant.write_init @file_init_func
        end
        @line_count += 1
    end
end

wrapper = Wrapper.new('/usr/include/GL/gl.h', 'gl', '<ruby.h>', '<GL/gl.h>')
wrapper.generate

# Local Variables: ***
# ruby-indent-level: 4 ***
# End: ***
