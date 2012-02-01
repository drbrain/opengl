#-*-ruby-*-
#
# Copyright (C) 2006 John M. Gabriele <jmg3000@gmail.com>
# Copyright (C) Eric Hodel <drbrain@segment7.net>
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

require 'hoe'
require 'rake/extensiontask'
load 'Rakefile.cross'

hoe = Hoe.spec 'opengl' do
  developer 'Eric Hodel', 'drbrain@segment7.net'
  developer 'Alain Hoang', ''
  developer 'Jan Dvorak',  ''
  developer 'Minh Thu Vo', ''
  developer 'James Adam',  ''

  self.readme_file = 'README.rdoc'
  self.history_file = 'History.rdoc'
  self.extra_rdoc_files = FileList['*.rdoc']

  extra_dev_deps << ['rake-compiler', '~> 0.7', '>= 0.7.9']

  self.spec_extras = {
    :extensions            => %w[ext/opengl/extconf.rb],
    :required_ruby_version => '>= 1.9.2',
  }
end

Rake::ExtensionTask.new 'opengl', hoe.spec do |ext|
  ext.lib_dir = 'lib/opengl'

  ext.cross_compile = true
  ext.cross_platform = ['i386-mingw32']
  ext.cross_config_options += [
    "--with-installed-dir=#{STATIC_INSTALLDIR}",
  ]
end

task :test => :compile

# Generate html docs from the markdown source and upload to the site.
# All doc files that are destined for the website have filenames that
# end in .txt.

WEBSITE_MKDN = FileList['./docs/*.txt'] << 'README.txt'
NICE_HTML_DOCS = WEBSITE_MKDN.ext('html')

# defines columns in the HTML extension list
GLEXT_VERSIONS = %w[svn 0.60 0.50]

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
	sh "./utils/extlistgen.rb", "doc/extensions.txt.in", "doc/extensions.txt", *GLEXT_VERSIONS
end

desc 'Generate website html.'
task :gen_website => [:gen_glext_list] + NICE_HTML_DOCS do
  # Now that the website docs have been generated, copy them to ./website.
  cp "README.html", "website/index.html"
  cp "doc/*.html", "ebsite"
end

# You'll see some intermediate .plain files get generated. These are html,
# but don't yet have their code snippets syntax highlighted.
rule '.html' => '.plain' do |t|
  puts "Turning #{t.source} into #{t.name} ..."
  sh "./utils/post-mkdn2html.rb", t.source, t.name
end

# Process the markdown docs into plain html.
rule '.plain' => '.txt' do |t|
  puts "Turning #{t.source} into #{t.name} ..."
  sh "./utils/mkdn2html.rb", t.source, t.name
end

RUBYFORGE = "rubyforge.org:/var/www/gforge-projects/ruby-opengl"

desc 'Upload the newly-built site to RubyForge.'
task :upload_website => [:gen_website] do
  sh "scp", "website/*.html", RUBYFORGE
  sh "scp", "website/images/*", "#{RUBYFORGE}/images/"
end

desc 'Upload entire site, including stylesheet and the images directory.'
task :upload_entire_website => [:gen_website] do
  sh "scp", "website/*.html", RUBYFORGE
  sh "scp", "website/*.css", RUBYFORGE
  sh "scp", "-r", "website", "images", RUBYFORGE
end

