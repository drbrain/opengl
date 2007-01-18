#!/bin/sh
# A quick hack to run all the tests in the test/ directory

for i in *.rb
do
    ruby -rubygems $i
done
