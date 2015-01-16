require 'opengl/test_case'

class TestGlimpl < OpenGL::TestCase
  def test_dl_load_error
    assert_raises(ArgumentError){ Gl::Implementation.open("not exist") }
  end

  def test_GetProcAddress_error
    assert_raises(NotImplementedError){ Gl::Implementation.open(Gl::DEFAULT_IMPLEMENTATION::DLPATH, "not exist") }
  end

  def test_close
    gl = Gl::DEFAULT_IMPLEMENTATION.open
    assert_nil gl.close
    assert_nil gl.close
  end

  def test_instance_methods
    gl = Gl::DEFAULT_IMPLEMENTATION.open
    assert_match(/^\d+\.\d+/, gl.glGetString(GL::VERSION))
    assert_kind_of(Array, gl.glGetIntegerv(GL::VIEWPORT))
  end
end
