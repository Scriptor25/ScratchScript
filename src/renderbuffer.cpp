#include <scr/GL.hpp>

scr::RenderBuffer::RenderBuffer(const GLenum target)
    : m_Target(target)
{
    glGenRenderbuffers(1, &m_Handle);
}

scr::RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &m_Handle);
}

GLuint scr::RenderBuffer::Handle() const
{
    return m_Handle;
}

GLenum scr::RenderBuffer::Target() const
{
    return m_Target;
}

scr::RenderBuffer::operator bool() const
{
    return m_Handle != 0;
}

scr::RenderBuffer *scr::RenderBuffer::Bind()
{
    glBindRenderbuffer(m_Target, m_Handle);
    return this;
}

scr::RenderBuffer *scr::RenderBuffer::Storage(const GLenum internal_format, const GLsizei width, const GLsizei height)
{
    glRenderbufferStorage(m_Target, internal_format, width, height);
    return this;
}

void scr::RenderBuffer::Unbind() const
{
    glBindRenderbuffer(m_Target, 0);
}
