# -*- coding: UTF-8 -*-
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

require 'hoe'
require 'rake/extensiontask'

hoe = Hoe.spec 'opengl' do
  developer 'Eric Hodel', 'drbrain@segment7.net'
  developer 'Lars Kanis',  'lars@greiz-reinsdorf.de'
  developer 'Blaž Hrastnik', 'speed.the.bboy@gmail.com'
  developer 'Alain Hoang', ''
  developer 'Jan Dvorak',  ''
  developer 'Minh Thu Vo', ''
  developer 'James Adam',  ''

  self.readme_file = 'README.rdoc'
  self.history_file = 'History.rdoc'
  self.extra_rdoc_files = FileList['*.rdoc']

  extra_dev_deps << ['rake-compiler', '~> 0.9', '>= 0.9.1']
  extra_dev_deps << ['glu', '~> 8.1']
  extra_dev_deps << ['glut', '~> 8.1']

  self.spec_extras = {
    :extensions            => %w[ext/opengl/extconf.rb],
    :required_ruby_version => '>= 1.9.2',
  }
end

Rake::ExtensionTask.new 'opengl', hoe.spec do |ext|
  ext.lib_dir = 'lib/opengl'

  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw32']
end

task :test => :compile

# defines columns in the HTML extension list
GLEXT_VERSIONS = %w[svn 0.60 0.50]

desc 'Generate supported extension list.'
task :gen_glext_list do
	sh "./utils/extlistgen.rb", "doc/extensions.txt.in", "doc/extensions.txt", *GLEXT_VERSIONS
end

# To reduce the gem file size strip mingw32 dlls before packaging
ENV['RUBY_CC_VERSION'].to_s.split(':').each do |ruby_version|
  task "copy:opengl:x86-mingw32:#{ruby_version}" do |t|
    sh "i686-w64-mingw32-strip -S tmp/x86-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so"
  end

  task "copy:opengl:x64-mingw32:#{ruby_version}" do |t|
    sh "x86_64-w64-mingw32-strip -S tmp/x64-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so"
  end
end
