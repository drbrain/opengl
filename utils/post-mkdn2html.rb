#!/opt/ruby/bin/ruby
#
# Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
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


# This script will modify the contents of the first html file you
# pass it, and save the modifications in the 2nd file.
#
# What it does:
#
# It looks in the first file for patterns like this:
#
#     <pre><code>{{name}}\nstuff</code></pre>
#
# and replaces "stuff" with "stuff" processed to include color syntax
# highlighting, assuming it is code written in language "name".
#
# Prerequisites:
# * This script expects that you have GNU source-highlight installed.

if ARGV.size != 2
    puts "Please don't trifle with me."
    exit 1
end

infile_name = ARGV[0]
outfile_name = ARGV[1]

# Open the file, slurp the whole thing into one long string.
infile_content = IO.read( infile_name )
outfile_content = infile_content.clone
temp_content = infile_content.clone

# Make sure we find all of them -- there could be more than 1 in
# the given file. XXX (Just finding the first one here.)

snippet_num = 0

while true
    # If we get a match, process that snippet.
    if outfile_content =~ %r{<pre><code>\{\{(\w+)\}\}\n(.+?)</code></pre>}m
        pre_stuff = $`
        language = $1
        code_to_convert = $2
        post_stuff = $'

        # Quick usage note on source-highlight:
        # 
        #     source-highlight -s ruby -i $filename -o $filename
        #
        # where, if you omit -o filename, output goes to stdout.

        base_name = File.basename( outfile_name, '.*' )
        File.open( "doc/#{base_name}_#{snippet_num}.snip", 'w' ) do |file|
            file.write code_to_convert
        end

        highlighted_code =
            `source-highlight -s #{language} -i doc/#{base_name}_#{snippet_num}.snip -f html`

        temp_content = pre_stuff + highlighted_code + post_stuff
        snippet_num += 1
        outfile_content = temp_content.clone
    else
        break
    end
end

File.open( outfile_name, 'w' ) do |file|
    file.write outfile_content
end

puts "Done syntax highlighting #{snippet_num} snippets for #{infile_name}. Wrote #{outfile_name}."
