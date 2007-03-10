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
require 'rake/clean'
require 'rake/gempackagetask'
require 'rake/testtask'

require 'mkrf/rakehelper'

WEBSITE_MKDN = FileList['./doc/*.txt'] << 'README.txt'
NICE_HTML_DOCS = WEBSITE_MKDN.ext('html')

CLEAN.include("ext/gl*/Rakefile", "ext/*/mkrf.log", "ext/*/*.so", 
              "ext/**/*.bundle", "lib/*.so", "lib/*.bundle", "ext/*/*.o", 
              "pkg")
CLOBBER.include("*.plain", "doc/*.plain", "doc/*.snip", "*.html",
                "doc/*.html", "website/*.html")

setup_extension('gl', 'gl')
setup_extension('glu', 'glu')
setup_extension('glut', 'glut')

desc 'Does a full compile'
task :default => [:build_rbogl, :gl, :glu, :glut]

task :extension => :default

desc 'Builds common OpenGL object file.  Necessary for building GL bindings'
task :build_rbogl do
    puts "Building common rbogl object file"
    sh "cd ext/common && rake"
end

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

# Create a task for running unit tests
desc 'Runs unit tests.'
Rake::TestTask.new do |t|
    t.libs << "test"
    t.test_files = FileList['test/tc_*.rb']
    t.verbose = true
end

# Create a task for running unit tests
desc 'Runs interactive tests.'
Rake::TestTask.new(:test_interactive) do |t|
    t.libs << "test"
    t.libs << "test/interactive"
    t.test_files = FileList['test/interactive/tc_base.rb']
    t.verbose = true
end

# Define the files that will go into the gem
gem_files = FileList["{lib,ext,doc,examples,test}/**/*"]
gem_files = gem_files.exclude("**/*.so", "**/*.o", "ext/**/*.log", "ext/gl*/Rakefile")

spec = Gem::Specification.new do |s|
    s.name              = "ruby-opengl"
    s.version           = "0.33.0"
    s.authors           = [ "John Gabriele", "Minh Thu Vo" ]
    s.homepage          = "http://opengl-ruby.rubyforge.org"
    s.platform          = Gem::Platform::RUBY
    s.summary           = "OpenGL Interface for Ruby"
    s.files             = gem_files
    s.extensions        << 'Rakefile'
#    s.extensions        << 'ext/common/Rakefile', 'ext/gl/mkrf_conf.rb', 
#                           'ext/glu/mkrf_conf.rb', 'ext/glut/mkrf_conf.rb']
    s.require_path      = "lib"
    s.autorequire       = "gl"
    s.has_rdoc          = false
    s.add_dependency("mkrf", ">=0.2.0")
end

