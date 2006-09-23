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

# Don't use -w for now -- too many warning re. the BlueCloth module.

# Converts the named text file (containing plain text marked up with Markdown
# markup) into a corresponding html file. The user must specify both filenames.
# If the outfile already exists, it will be written over.

require 'rubygems'
require 'bluecloth'

if ARGV.size != 2
    puts "Error: please pass exactly two args: the name of the file"
    puts "you want converted to html, and the name of the file:"
    puts "mkdn2html.rb infile.txt outfile.html"
    exit 1
end

infile_name = ARGV[0]
outfile_name = ARGV[1]

# Strip the last filename extension so we can use the basename in the
# title of the page.
base_filename = File.basename( infile_name, ".*" )
puts "base_filename = #{base_filename}"
#base_filename.sub!( %r{\./docs/}, '' ).sub!( /\.txt$/, '' )
if base_filename == 'README'
    base_filename = 'Home'
end
puts "base_filename = #{base_filename}"

raw_markdown_text = IO.read( infile_name )
bc = BlueCloth.new( raw_markdown_text )
html_content = bc.to_html

puts "outfile is #{File.expand_path( outfile_name )}"

template_content = IO.read( './docs/supplies/page_template.html' )
template_content.sub!( /\{\{content\}\}/, html_content )
template_content.sub!( /\{\{title\}\}/, base_filename )


File.open( outfile_name, 'w' ) do |file|
    file.write template_content
end

puts "Done creating plain #{base_filename} html file."
