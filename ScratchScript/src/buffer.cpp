#include <scr/GL.hpp>

scr::Buffer::Buffer(GLenum target, GLenum usage)
        : m_Target(target), m_Usage(usage)
{
    glGenBuffers(1, &m_Handle);
}

scr::Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_Handle);
}

scr::Buffer::operator bool() const
{
    return m_Handle != 0;
}

scr::Buffer *scr::Buffer::Bind()
{
    glBindBuffer(m_Target, m_Handle);
    return this;
}

scr::Buffer *scr::Buffer::Data(GLsizeiptr size, const void *data)
{
    glBufferData(m_Target, size, data, m_Usage);
    return this;
}

void scr::Buffer::Unbind() const
{
    glBindBuffer(m_Target, 0);
}
