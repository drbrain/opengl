require 'test/unit'

class MkwrapTest < Test::Unit::TestCase
  def test_mkwrap
    # Run mkwrap on the test file
    system "./mkwrap.rb ./test.h test"

    # Now check the output for certain features
    wrapper = File.open( 'test_wrap.c' ).read
    wrapper.each {|l| puts "=== #{l}"}

    wrapper_expected = [
      'rbgl_glutCopyColormap (VALUE self, VALUE win)',
      'rbgl_glutSetColor (VALUE self, VALUE _a1, VALUE red, VALUE green, VALUE blue)',
      ]
    wrapper_expected.each {|e| assert_in_source( wrapper, e ) }
  end

  def assert_in_source( source, expected, num_expected=1 )
    regex = Regexp.new( Regexp.escape( expected ) )
    matches = source.grep( regex )
    matches.each {|l| puts "+++ #{l}"}
    msg = "Expected #{num_expected} but found #{matches.length}: '#{expected}'"
    matches.each {|m| msg << "\n\t'#{m.chomp}'"}
    assert_equal num_expected, matches.length, msg
  end
end

