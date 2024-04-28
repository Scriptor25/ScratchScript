#include <scr/GL.hpp>

scr::Framebuffer::Framebuffer(GLenum target)
	: m_Target(target)
{
	glGenFramebuffers(1, &m_Handle);
}

scr::Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_Handle);
}

scr::Framebuffer::operator bool() const
{
	return m_Handle != 0;
}

scr::Framebuffer* scr::Framebuffer::Bind()
{
	glBindFramebuffer(m_Target, m_Handle);
	return this;
}

scr::Framebuffer* scr::Framebuffer::AddTexture2D(GLenum attachment, const Texture* texture, GLint level)
{
	glFramebufferTexture2D(m_Target, attachment, texture->Target(), texture->Handle(), level);
	return this;
}

scr::Framebuffer* scr::Framebuffer::AddRenderbuffer(GLenum attachment, const Renderbuffer* renderbuffer)
{
	glFramebufferRenderbuffer(m_Target, attachment, renderbuffer->Target(), renderbuffer->Handle());
	return this;
}

void scr::Framebuffer::Unbind()
{
	glBindFramebuffer(m_Target, 0);
}
