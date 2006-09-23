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
# pass it, and save the modifications in the 2nd file. It looks in
# the first file for patterns like this:
#
#     <pre><code><!-- name --> stuff </code></pre>
#
# and replaces "stuff" with "stuff" processed to include color syntax
# highlighting, assuming it is code written in language "name".
#
# This script expects that you have GNU source-highlight installed.

if ARGV.size != 2
    puts "Please don't trifle with me."
    exit 1
end

infile_name = ARGV[0]
outfile_name = ARGV[1]

# Open the file, slurp the whole thing into one long string.
infile_content = IO.read( infile_name )
temp_content = infile_content.clone

# Replace everything between <pre><code>(.*)</code></pre>
# with \1 processed by source-highlight.

# Make sure we find all of them -- there could be more than 1 in
# the given file. XXX (Just finding the first one here.)

# If no match, skip.
if infile_content =~ %r{<pre><code>&lt;!-- (\w+) --&gt;(.*?)</code></pre>}m
    pre_stuff = $`
    language = $1
    code_to_convert = $2
    post_stuff = $'

    # Quick usage note on source-highlight:
    # 
    #     source-highlight -s ruby -i $filename -o $filename
    #
    # where, if you omit -o filename, output goes to stdout.
    highlighted_code = `echo '#{code_to_convert}' | source-highlight -s #{language} -f html`

    temp_content = pre_stuff + highlighted_code + post_stuff
end

File.open( outfile_name, 'w' ) do |file|
    file.write temp_content
end

puts "Done syntax highlighting snippets for #{infile_name}. Wrote #{outfile_name}."
