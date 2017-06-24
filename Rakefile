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

require 'bundler'
require 'bundler/gem_helper'
require 'rake/extensiontask'

class OpenglGemHelper < Bundler::GemHelper
  attr_accessor :cross_platforms

  def install
    super

    task "release:guard_clean" => ["release:update_history"]

    task "release:update_history" do
      update_history
    end

    task "release:rubygem_push" => ["gem:windows"]
  end

  def hfile
    "History.md"
  end

  def headline
    '([^\w]*)(\d+\.\d+\.\d+(?:\.\w+)?)([^\w]+)([2Y][0Y][0-9Y][0-9Y]-[0-1M][0-9M]-[0-3D][0-9D])([^\w]*|$)'
  end

  def reldate
    Time.now.strftime("%Y-%m-%d")
  end

  def update_history
    hin = File.read(hfile)
    hout = hin.sub(/#{headline}/) do
      raise "#{hfile} isn't up-to-date for version #{version}" unless $2==version.to_s
      $1 + $2 + $3 + reldate + $5
    end
    if hout != hin
      Bundler.ui.confirm "Updating #{hfile} for release."
      File.write(hfile, hout)
      Rake::FileUtilsExt.sh "git", "commit", hfile, "-m", "Update release date in #{hfile}"
    end
  end

  def tag_version
    Bundler.ui.confirm "Tag release with annotation:"
    m = File.read(hfile).match(/(?<annotation>#{headline}.*?)#{headline}/m) || raise("Unable to find release notes in #{hfile}")
    Bundler.ui.info(m[:annotation].gsub(/^/, "    "))
    IO.popen(["git", "tag", "--file=-", version_tag], "w") do |fd|
      fd.write m[:annotation]
    end
    yield if block_given?
  rescue
    Bundler.ui.error "Untagging #{version_tag} due to error."
    sh_with_code "git tag -d #{version_tag}"
    raise
  end

  def rubygem_push(path)
    cross_platforms.each do |ruby_platform|
      super(path.gsub(/\.gem\z/, "-#{ruby_platform}.gem"))
    end
    super(path)
  end
end

spec = Gem::Specification.load('opengl.gemspec')

Rake::ExtensionTask.new 'opengl', spec do |ext|
  ext.lib_dir = 'lib/opengl'

  ext.cross_compile = true
  ext.cross_platform = ['x86-mingw32', 'x64-mingw32']

  OpenglGemHelper.install_tasks
  Bundler::GemHelper.instance.cross_platforms = ext.cross_platform
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

cfiles = Dir["ext/opengl/*.c"].sort
fptrfiles = cfiles.map{|cf| [cf, "#{cf}.fptr"] }
fptrfiles.each do |cfile, fptrfile|
  file fptrfile => [cfile, "ext/opengl/funcdef.h"] do |t|
    args = RbConfig::CONFIG['CC'], "-E", cfile,
        "-DGLFUNC_MAGIC_START=glfunc-", "-DGLFUNC_MAGIC_END=-glfunc",
        "-DGLFUNC_MAGIC_APIENTRY=-glfunc-apientry-",
        "-I#{RbConfig::CONFIG['rubyhdrdir']}", "-I#{RbConfig::CONFIG['rubyarchhdrdir']}",
        "-Iext/opengl"

    puts args.join(" ")

    func = IO.popen(args) do |i|
      i.read.scan(/glfunc- (.*?) -glfunc/).map{|m| "#{m[0].gsub("-glfunc-apientry-", "APIENTRY")};\n" }.join
    end
    File.write(t.name, func)
  end
end
CLEAN.include *fptrfiles.map(&:last)

multitask "ext/opengl/fptr_struct.h" => fptrfiles.map(&:last) do |t|
  out = <<-EOT
    #ifndef _FPTR_STRUCT_H_
    #define _FPTR_STRUCT_H_
    struct glfunc_ptrs {
  EOT
  t.prerequisites.map do |f|
    File.readlines(f)
  end.flatten.uniq.each do |func|
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
  RakeCompilerDock.sh "rake cross native gem MAKE='nice make -j`nproc`'"
end
