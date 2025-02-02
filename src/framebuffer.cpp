#include <scr/GL.hpp>

scr::FrameBuffer::FrameBuffer(const GLenum target)
    : m_Target(target)
{
    glGenFramebuffers(1, &m_Handle);
}

scr::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_Handle);
}

scr::FrameBuffer::operator bool() const
{
    return m_Handle != 0;
}

scr::FrameBuffer *scr::FrameBuffer::Bind()
{
    glBindFramebuffer(m_Target, m_Handle);
    return this;
}

scr::FrameBuffer *scr::FrameBuffer::AddTexture2D(const GLenum attachment, const Texture *texture, const GLint level)
{
    glFramebufferTexture2D(m_Target, attachment, texture->Target(), texture->Handle(), level);
    return this;
}

scr::FrameBuffer *scr::FrameBuffer::AddRenderBuffer(const GLenum attachment, const RenderBuffer *render_buffer)
{
    glFramebufferRenderbuffer(m_Target, attachment, render_buffer->Target(), render_buffer->Handle());
    return this;
}

void scr::FrameBuffer::Unbind() const
{
    glBindFramebuffer(m_Target, 0);
}
