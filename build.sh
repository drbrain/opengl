#!/bin/bash

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

# Dunno how to make rake do this, and this simple script seems to work
# ok on GNU/Linux for now. ---John

echo 'Cleaning up previous build products ...'
# Note, mkrf_conf.rb should always generate a new Rakefile,
# so we don't clean out old ones (also, recall that ext/common
# contains a hand-written Rakefile which you wouldn't want to
# remove).
rm ext/common/rbogl.o
rm ext/gl/gl.o
rm ext/glu/glu.o
rm ext/glut/glut.o

cd ext/common
echo "Building common/rbogl.o ..."
rake

echo ""
cd ../gl
echo "Making Rakefile for gl ..."
ruby mkrf_conf.rb
echo "Building gl ..."
rake
cp gl.so ../../lib

echo ""
cd ../glu
echo "Making Rakefile for glu ..."
ruby mkrf_conf.rb
echo "Building glu ..."
rake
cp glu.so ../../lib

echo ""
cd ../glut
echo "Making Rakefile for glut ..."
ruby mkrf_conf.rb
echo "Building glut ..."
rake
cp glut.so ../../lib

echo ""
echo "Done. Extension modules built and copied to ./lib."
