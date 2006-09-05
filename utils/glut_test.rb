require 'test/unit'

class GlutTest < Test::Unit::TestCase
  def test_arg_count
    counts = {
      'glutSolidSphere' => 3,
      'glutSolidCube'   => 1,
#      'glutMainLoop'    => 0
    }
    File.open( 'glut.c' ) do |f|
      f.each do |l|
        case l
        when /rb_define_module_function \(module, "(\w+)", \w+, (\d+)/
          name, count = $1, $2
          if counts.has_key?(name)
            assert_equal counts[name], count.to_i, "#{name} Expected #{counts[name]} Actual #{count}"
          else
 #           puts "skipping #{name}"
          end
          puts "#{$1}  #{$2}"
        end
      end
    end
  end
end
