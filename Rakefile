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

require 'bundler/gem_tasks'
require 'rake/extensiontask'

spec = Gem::Specification.load('opengl.gemspec')

Rake::ExtensionTask.new 'opengl', spec do |ext|
  ext.lib_dir = 'lib/opengl'

  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw32']
end

task :gem => :build
task :test => :compile do
  sh "ruby -w -W2 -I. -Ilib -e \"#{Dir["test/test_*.rb"].map{|f| "require '#{f}';"}.join}\" -- -v"
end


# defines columns in the HTML extension list
GLEXT_VERSIONS = %w[svn 0.60 0.50]

desc 'Generate supported extension list.'
task :gen_glext_list do
  sh "./utils/extlistgen.rb", "doc/extensions.txt.in", "doc/extensions.txt", *GLEXT_VERSIONS
end

cfiles = Dir["ext/opengl/*.c"]
file "ext/opengl/fptr_struct.h" => (cfiles + ["ext/opengl/funcdef.h"]) do |t|

  funcs = cfiles.map do |cfile|
    args = RbConfig::CONFIG['CC'], "-E", cfile,
        "-DGLFUNC_MAGIC_START=glfunc-", "-DGLFUNC_MAGIC_END=-glfunc",
        "-I#{RbConfig::CONFIG['rubyhdrdir']}", "-I#{RbConfig::CONFIG['rubyarchhdrdir']}",
        "-Iext/opengl"

    puts args.join(" ")

    IO.popen(args) do |i|
      i.read.scan(/glfunc- (.*?) -glfunc/).map{|m| "#{m[0]};\n" }
    end
  end

  out = <<-EOT
    #ifndef _FPTR_STRUCT_H_
    #define _FPTR_STRUCT_H_
    struct glfunc_ptrs {
  EOT
  funcs.flatten.uniq.each do |func|
    out << func
  end
  out << <<-EOT
    };
    #endif
  EOT

  File.write(t.name, out) unless File.exist?(t.name) && File.read(t.name) == out
end

task "ext/opengl/extconf.rb" => "ext/opengl/fptr_struct.h"
task :build => "ext/opengl/extconf.rb"

CLEAN.include "ext/opengl/fptr_struct.h"

ENV['RUBY_CC_VERSION'] ||= '2.3.0:2.2.2:2.1.6:2.0.0:1.9.3'

# To reduce the gem file size strip mingw32 dlls before packaging
ENV['RUBY_CC_VERSION'].to_s.split(':').each do |ruby_version|
  task "tmp/x86-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so" do |t|
    sh "i686-w64-mingw32-strip -S tmp/x86-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so"
  end

  task "tmp/x64-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so" do |t|
    sh "x86_64-w64-mingw32-strip -S tmp/x64-mingw32/stage/lib/opengl/#{ruby_version[/^\d+\.\d+/]}/opengl.so"
  end
end

desc "Build windows binary gems per rake-compiler-dock."
task "gem:windows" do
  require "rake_compiler_dock"
  RakeCompilerDock.sh "rake cross native gem MAKE='nice make -j`nproc`' RUBY_CC_VERSION=#{ENV['RUBY_CC_VERSION']}"
end
