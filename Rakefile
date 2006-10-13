#-*-ruby-*-
#
# Copyright (C) 2006 Peter McLain <peter.mclain@gmail.com>
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

require 'rake/clean'
require 'rbconfig'

# For one thing, ruby.h is here. Ex.: /opt/ruby-1.8.4/lib/ruby/1.8/i686-linux
$INCLUDES = "-I#{Config::CONFIG['archdir']}"

$CFLAGS   = "#{Config::CONFIG['CFLAGS']}"         # Ex.: -g -O2
$LDFLAGS  = "-l#{Config::CONFIG["RUBY_SO_NAME"]}" # Ex.: ruby

# The link edit command. Ex.: gcc -shared
$LDCMD    = "#{Config::CONFIG['LDSHARED']}"

# Other libs to link in.
$EXTRA_LIBS     = ''
$FOR_GL_LIB = '-lGL'
$FOR_GLU_LIB = '-lGLU -lGL'
$FOR_GLUT_LIB = '-lglut -lGLU -lGL'

case RUBY_PLATFORM
when /darwin/
    $INCLUDES << ' -F/System/Library/Frameworks'
    $LDFLAGS  << ' -framework GLUT -framework OpenGL'
    $LDCMD = 'cc -bundle'
else
    $CFLAGS << " #{Config::CONFIG["CCDLFLAGS"]}" # Ex.: -fPIC

    $LDFLAGS = "-L#{Config::CONFIG["libdir"]}"   # Ex.: /opt/ruby-1.8.4/lib
    $LDFLAGS << " -Wl,-R'#{Config::CONFIG["libdir"]}'"

    $EXTRA_LIBS << " #{Config::CONFIG["LIBS"]}"  # Ex.: -ldl -lcrypt -lm
end


GL_LIB   = "ext/gl/gl.#{Config::CONFIG['DLEXT']}"
GLU_LIB  = "ext/glu/glu.#{Config::CONFIG['DLEXT']}"
GLUT_LIB = "ext/glut/glut.#{Config::CONFIG['DLEXT']}"
LIBS     = [ GL_LIB, GLU_LIB, GLUT_LIB ]

CLEAN.include( 'ext/**/*.o' )
CLOBBER.include( LIBS )


desc "Create: #{LIBS.join(', ')}"
task :default => LIBS

file 'ext/common/rbogl.o' => [ 'ext/common/rbogl.h', 'ext/common/rbogl.c' ]

# I don't think rbogl.c should be compiled with -fPIC like the other source
# files we're building here. I'm using the ext/common/Rakefile to build rbogl.c
# for now... ---John
rule '.o' => '.c' do |t|
    cmd = "cc #{$CFLAGS} #{$INCLUDES} -c -o #{t.name} #{t.source}"
    puts "\n============================== compiling: #{t.source} --> #{t.name}"
    sh cmd
end

desc "Create the OpenGL library (#{GL_LIB})"
file GL_LIB => [ 'ext/gl/gl.o', 'ext/common/rbogl.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} -o #{t.name} #{t.prerequisites.join(' ')} #{$FOR_GL_LIB} #{$EXTRA_LIBS}"
    puts "\n============================== linking #{GL_LIB}"
    sh cmd
    sh "cp #{GL_LIB} lib"
end


# TODO: This is a cut-n-paste of the GL_LIB target.  Need to define a rule
# to build them
desc "Create the GLU library (#{GLU_LIB})"
file GLU_LIB => [ 'ext/glu/glu.o', 'ext/common/rbogl.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} -o #{t.name} #{t.prerequisites.join(' ')} #{$FOR_GLU_LIB} #{$EXTRA_LIBS}"
    puts "\n============================== linking #{GLU_LIB}"
    sh cmd
    sh "cp #{GLU_LIB} lib"
end

    
# TODO: This is a cut-n-paste of the GL_LIB target.  Need to define a rule
# to build them
desc "Create the GLUT library (#{GLUT_LIB})"
file GLUT_LIB => [ 'ext/glut/glut.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} -o #{t.name} #{t.prerequisites.join(' ')} #{$FOR_GLUT_LIB} #{$EXTRA_LIBS}"
    puts "\n============================== linking #{GLUT_LIB}"
    sh cmd
    sh "cp #{GLUT_LIB} lib"
end


#====================================================================
# Generate html docs from the markdown source and upload to the site.
# All doc files that are destined for the website have filenames that
# end in .txt.

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
    sh "scp website/*.html johnmg@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
end

desc 'Upload entire site, including stylesheet and the images directory.'
task :upload_entire_website => [:gen_website] do
    sh "scp website/*.html johnmg@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp website/*.css johnmg@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
    sh "scp -r website/images johnmg@rubyforge.org:/var/www/gforge-projects/ruby-opengl"
end
