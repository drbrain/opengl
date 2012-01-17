require 'opengl/test_case'

class TestOpenGLBuffer < OpenGL::TestCase

  def test_class_map
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_ONLY

    assert_equal 'hello', buf.read(5)

  ensure
    buf.unmap
  end

  def test_read_length
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_ONLY

    assert_equal 'he', buf.read(2)
  ensure
    buf.unmap
  end

  def test_read_offset
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_ONLY

    assert_equal 'el', buf.read(2, 1)
  ensure
    buf.unmap
  end

  def test_read_unbounded
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_ONLY

    e = assert_raises ArgumentError do
      buf.read
    end

    assert_equal 'length must be provided for unbounded buffer', e.message
  ensure
    buf.unmap
  end

  def test_write
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_WRITE

    buf.write 'world'

    assert_equal 'world', buf.read(5)

    buf.unmap

    assert_equal 'world', glGetBufferSubData(GL_ARRAY_BUFFER, 0, 5)

  ensure
    buf.unmap
  end

  def test_write_nil
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_WRITE

    e = assert_raises ArgumentError do
      buf.write nil
    end

    assert_equal 'cannot write nil to buffer', e.message

  ensure
    buf.unmap
  end

  def test_write_offset
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    glBufferData GL_ARRAY_BUFFER, 5, 'hello', GL_STREAM_READ

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_WRITE

    buf.write 'O', 4

    assert_equal 'hellO', buf.read(5)
  ensure
    buf.unmap
  end

  def test_write_unmapped
    buffer, = glGenBuffers 1

    glBindBuffer GL_ARRAY_BUFFER, buffer

    buf = OpenGL::Buffer.map GL_ARRAY_BUFFER, GL_READ_WRITE

    e = assert_raises ArgumentError do
      buf.write 'hello'
    end

    assert_equal 'write to unmapped buffer', e.message
  end

end

