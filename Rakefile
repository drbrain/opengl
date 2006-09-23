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

$INCLUDES = "-I#{Config::CONFIG['archdir']}"
$CFLAGS   = "#{Config::CONFIG['CFLAGS']}"
$LDFLAGS  = "-l#{Config::CONFIG["RUBY_SO_NAME"]}"
$LDCMD    = "#{Config::CONFIG['LDSHARED']}"

case RUBY_PLATFORM
when /darwin/
    $INCLUDES << ' -F/System/Library/Frameworks'
    $LDFLAGS  << ' -framework GLUT -framework OpenGL'
    $LDCMD = 'cc -bundle'
else
    $INCLUDES << ' -L/usr/lib'
    $LDFLAGS  << ' -lglut -lGLU -lGL' # must not be for all targets
end

GL_LIB   = "ext/gl/gl.#{Config::CONFIG['DLEXT']}"
GLU_LIB  = "ext/glu/glu.#{Config::CONFIG['DLEXT']}"
GLUT_LIB = "ext/glut/glut.#{Config::CONFIG['DLEXT']}"
LIBS     = [ GL_LIB, GLU_LIB, GLUT_LIB ]

CLEAN.include( 'ext/**/*.o' )
CLOBBER.include( LIBS )

desc "Create #{LIBS}"
task :default => LIBS

rule '.o' => '.c' do |t|
    cmd = "cc #{$INCLUDES} #{$CFLAGS} -c -o #{t.name} #{t.source}"
    puts "============== #{cmd}"
    sh cmd
end

desc "Create the OpenGL library (#{GL_LIB})"
file GL_LIB => [ 'ext/gl/gl.o', 'ext/common/rbogl.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} #{$CFLAGS} -o #{t.name} #{t.prerequisites.join(' ')}"
    puts "============== #{cmd}"
    sh cmd
end


# TODO: This is a cut-n-paste of the GL_LIB target.  Need to define a rule
# to build them
desc "Create the GLU library (#{GLU_LIB})"
file GLU_LIB => [ 'ext/glu/glu.o', 'ext/common/rbogl.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} #{$CFLAGS} -o #{t.name} #{t.prerequisites.join(' ')}"
    puts "============== #{cmd}"
    sh cmd
end

    
# TODO: This is a cut-n-paste of the GL_LIB target.  Need to define a rule
# to build them
desc "Create the GLUT library (#{GLUT_LIB})"
file GLUT_LIB => [ 'ext/glut/glut.o' ] do |t|
    cmd = "#{$LDCMD} #{$LDFLAGS} #{$CFLAGS} -o #{t.name} #{t.prerequisites.join(' ')}"
    puts "============== #{cmd}"
    sh cmd
end

file 'ext/common/rbogl.o' => [ 'ext/common/rbogl.h', 'ext/common/rbogl.c' ]


#====================================================================
# Generate html docs from the markdown source and upload to the site.
# All doc files that are destined for the website have filenames that
# end in .mkdn.

WEBSITE_MKDN = FileList['./docs/*.txt'] << 'README.txt'
#PLAIN_HTML = WEBSITE_MKDN.ext('plain')
NICE_HTML_DOCS = WEBSITE_MKDN.ext('html')

desc 'Show contents of some variables related to website doc generation.'
task :explain_website_docs do
  puts "WEBSITE_MKDN   == #{WEBSITE_MKDN}"
  #p "PLAIN_HTML     == #{PLAIN_HTML}"
  puts "NICE_HTML_DOCS == #{NICE_HTML_DOCS}"
end

desc 'Generate website html (with syntax-highlighted code snippets).'
task :gen_website => NICE_HTML_DOCS do
    # Now that the website docs have been generated, copy them to ./website.
    puts
    sh "cp README.html website/index.html"
    sh "cp docs/*.html website"
end

desc 'Delete generated site files'
task :clean_website do
    sh "rm docs/*.plain docs/*.html *.plain *.html website/*.html"
end

# You'll see some intermediate .plain files get generated. These don't have
# their code snippets syntax highlighted yet.
rule '.html' => '.plain' do |t|
    # Syntax highlight the snippets in the plain, newly generated html.
    puts "Turning #{t.source} into #{t.name} ..."
    #sh "cp #{t.source} #{t.name}" # Just for now. XXX
    sh "./utils/hlight_snippets.rb #{t.source} #{t.name}"
end

rule '.plain' => '.txt' do |t|
    # Process the markdown docs into plain html.
    puts
    puts "Turning #{t.source} into #{t.name} ..."
    sh "./utils/mkdn2html.rb #{t.source} #{t.name}"
    #sh "touch #{t.name}"
end
