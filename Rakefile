#-*-ruby-*-
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

# This Rakefile currently only deals with generating docs and uploading
# the web site. The actual modules are build using mkrf and, for now,
# the top-level build.sh script.

#====================================================================
# Generate html docs from the markdown source and upload to the site.
# All doc files that are destined for the website have filenames that
# end in .txt.

begin
    require 'rubygems'
rescue LoadError
    nil
end

require 'rake'
require 'rake/gempackagetask'

WEBSITE_MKDN = FileList['./doc/*.txt'] << 'README.txt'
NICE_HTML_DOCS = WEBSITE_MKDN.ext('html')

desc 'Show contents of some variables related to website doc generation.'
task :explain_website do
    puts "WEBSITE_MKDN:"
    WEBSITE_MKDN.each do |doc|
        puts "\t#{doc}"
    end
    puts "NICE_HTML_DOCS:"
    NICE_HTML_DOCS.each do |doc|
        puts "\t#{doc}"
    end
end

desc 'Generate website html.'
task :gen_website => NICE_HTML_DOCS do
    # Now that the website docs have been generated, copy them to ./website.
    puts
    sh "cp README.html website/index.html"
    sh "cp doc/*.html website"
end

desc 'Delete all generated website files.'
task :clean_website do
    sh "rm *.plain doc/*.plain"
    sh "rm doc/*.snip"
    sh "rm *.html doc/*.html website/*.html"
end

# You'll see some intermediate .plain files get generated. These are html,
# but don't yet have their code snippets syntax highlighted.
rule '.html' => '.plain' do |t|
    puts "Turning #{t.source} into #{t.name} ..."
    sh "./utils/post-mkdn2html.rb #{t.source} #{t.name}"
end

# Process the markdown docs into plain html.
rule '.plain' => '.txt' do |t|
    puts
    puts "Turning #{t.source} into #{t.name} ..."
    sh "./utils/mkdn2html.rb #{t.source} #{t.name}"
end

desc 'Upload the newly-built site to RubyForge.'
task :upload_website => [:gen_website] do
    sh "scp website/*.html hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
end

desc 'Upload entire site, including stylesheet and the images directory.'
task :upload_entire_website => [:gen_website] do
    sh "scp website/*.html hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp website/*.css hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp -r website/images hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
end


spec = Gem::Specification.new do |s|
    s.name              = "opengl"
    s.version           = "0.33.0"
    s.authors           = [ "John Gabriele", "Minh Thu Vo" ]
    s.homepage          = "http://opengl-ruby.rubyforge.org"
    s.platform          = Gem::Platform::RUBY
    s.summary           = "OpenGL Interface for Ruby"
    s.files             = FileList["lib/*"]
    s.require_path      = "lib"
    s.autorequire       = "gl"
    s.has_rdoc          = false
end

# Create a task for creating a ruby gem
Rake::GemPackageTask.new(spec) do |pkg|
    pkg.need_tar = true
end
