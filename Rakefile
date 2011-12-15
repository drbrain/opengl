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

require 'rubygems'

require 'rake'
require 'rake/extensiontask'
require 'rake/clean'
require 'rubygems/package_task'
require 'rake/testtask'

# Generate html docs from the markdown source and upload to the site.
# All doc files that are destined for the website have filenames that
# end in .txt.

WEBSITE_MKDN = FileList['./doc/*.txt'] << 'README.txt'
NICE_HTML_DOCS = WEBSITE_MKDN.ext('html')

# defines columns in the HTML extension list
GLEXT_VERSIONS = ["svn","0.60","0.50"]

CLEAN.include("ext/gl*/Rakefile", "ext/*/mkrf.log", "ext/*/*.so", 
              "ext/**/*.bundle", "lib/*.so", "lib/*.bundle", "ext/*/*.o{,bj}", 
              "ext/*/*.lib", "ext/*/*.exp", "ext/*/*.pdb",
              "pkg")
CLOBBER.include("*.plain", "doc/*.plain", "doc/*.snip", "*.html",
                "doc/*.html", "website/*.html", "website/images/*")
# Make sure these files aren't deleted in a clobber op
CLOBBER.exclude("website/images/tab_bottom.gif")
CLOBBER.exclude("website/images/*.jpg")

desc 'Does a full compile'
task :default => [:compile, :fixpermissions]

task :fixpermissions do
	# fix wrong lib permissions (mkrf bug ?)
	Dir["lib/*.so","lib/*.bundle"].each do |fname|
		File.chmod(0755,fname)
	end
end

task :extension => :default

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

desc 'Generate supported extension list.'
task :gen_glext_list do
	sh "./utils/extlistgen.rb doc/extensions.txt.in doc/extensions.txt " + GLEXT_VERSIONS.join(" ")
end

desc 'Generate website html.'
task :gen_website => [:gen_glext_list] + NICE_HTML_DOCS do
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
    sh "scp website/images/* hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl/images/"
end

desc 'Upload entire site, including stylesheet and the images directory.'
task :upload_entire_website => [:gen_website] do
    sh "scp website/*.html hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp website/*.css hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp -r website/images hoanga@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
end

desc 'Runs unit tests.'
Rake::TestTask.new do |t|
    t.libs << "test"
    t.test_files = FileList['test/tc_*.rb']
    t.verbose = true
end

desc 'Runs unit tests.'
task :test_all => [:test]




############# gems #############

# common specification for source and binary gems
spec = Gem::Specification.new do |s|
    s.name              = "ruby-opengl"
    s.version           = "0.60.1"
    s.authors           = [ "Alain Hoang", "Jan Dvorak", "Minh Thu Vo", "James Adam" ]
    s.homepage          = "http://ruby-opengl.rubyforge.org"
    s.email             = "ruby-opengl-devel@rubyforge.org"
    s.rubyforge_project = 'ruby-opengl'
    s.platform          = Gem::Platform::RUBY
    s.summary           = "OpenGL Interface for Ruby"
    s.require_path      = "lib"
    s.autorequire       = "gl"
    s.has_rdoc          = false
    s.extensions     = []
end

Rake::ExtensionTask.new 'gl', spec
Rake::ExtensionTask.new 'glu', spec
Rake::ExtensionTask.new 'glut', spec

desc "builds binary gem on any platform"
task :binary_gem => [:default] do

  binary_gem_files = FileList["{lib,examples}/**/*"] + FileList["doc/*.txt"] + ["MIT-LICENSE","README.txt"]
  binary_spec = spec.dup
  binary_spec.files = binary_gem_files
  binary_spec.platform = Config::CONFIG['arch']

  gem_fname_ext = ".gem"
  if (RUBY_VERSION.split(".").join < "190")
    binary_spec.required_ruby_version = '~> 1.8.0'
  else
    binary_spec.required_ruby_version = '>= 1.9.0'
    gem_fname_ext = "-ruby19.gem"
  end

  Gem::Builder.new( binary_spec ).build

  Dir.mkdir("pkg") rescue {}
  unless (fname = Dir["ruby-opengl*.gem"]).empty?
    fname = fname.first
    newfname = fname[0..-5] + gem_fname_ext
    mv fname, "pkg/#{newfname}"
  end
end

# Create a task for creating a ruby source gem
Gem::PackageTask.new(spec) do |pkg|
  # Define the files that will go into the source gem
  gem_files = FileList["{lib,ext,doc,examples,test}/**/*"]
  gem_files = gem_files.exclude("**/*.so", "**/*.o{,bj}", "ext/**/*.log", "ext/gl*/Rakefile", "lib/*.bundle")

  spec.files = gem_files
  spec.extensions << 'ext/gl/extconf.rb'
  spec.extensions << 'ext/glu/extconf.rb'
  spec.extensions << 'ext/glut/extconf.rb'
  spec.add_development_dependency("rake")
  spec.add_development_dependency("rake-compiler", "~> 0.7", ">= 0.7.9")
  pkg.gem_spec = spec
  pkg.need_tar = true
end
