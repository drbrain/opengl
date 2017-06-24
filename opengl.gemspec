# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'opengl/bindings_version'

Gem::Specification.new do |spec|
  spec.name          = "opengl"
  spec.version       = Gl::BINDINGS_VERSION
  spec.authors = ["Eric Hodel", "Lars Kanis", "Bla\u{17e} Hrastnik", "Alain Hoang", "Jan Dvorak", "Minh Thu Vo", "James Adam"]
  spec.email = ["drbrain@segment7.net", "lars@greiz-reinsdorf.de", "blaz@mxxn.io", "", "", "", ""]
  spec.summary = "An OpenGL wrapper for Ruby"
  spec.description = "An OpenGL wrapper for Ruby. opengl contains bindings for OpenGL.\n\nBe sure to check out\n{GLU}[https://github.com/larskanis/glu] and\n{GLUT}[https://github.com/larskanis/glut]\ngems."
  spec.homepage = "https://github.com/larskanis/opengl"
  spec.license       = "MIT"

  spec.files = `git ls-files -z`.split("\x0") +
              ["ext/opengl/fptr_struct.h"]
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]
  spec.extensions = ["ext/opengl/extconf.rb"]
  spec.rdoc_options = ["--main", "README.rdoc"]

  spec.required_ruby_version = Gem::Requirement.new(">= 1.9.2")
  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"
  spec.add_development_dependency 'minitest', '~> 5.3'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
  spec.add_development_dependency 'rake-compiler-dock', '~> 0.6.0'
  spec.add_development_dependency 'glu', '~> 8.1'
  spec.add_development_dependency 'glut', '~> 8.1'
end
