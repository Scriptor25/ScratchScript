#include <scr/GL.hpp>

scr::Renderbuffer::Renderbuffer(GLenum target)
	: m_Target(target)
{
	glGenRenderbuffers(1, &m_Handle);
}

scr::Renderbuffer::~Renderbuffer()
{
	glDeleteRenderbuffers(1, &m_Handle);
}

GLuint scr::Renderbuffer::Handle() const
{
	return m_Handle;
}

GLenum scr::Renderbuffer::Target() const
{
	return m_Target;
}

scr::Renderbuffer::operator bool() const
{
	return m_Handle != 0;
}

scr::Renderbuffer* scr::Renderbuffer::Bind()
{
	glBindRenderbuffer(m_Target, m_Handle);
	return this;
}

scr::Renderbuffer* scr::Renderbuffer::Storage(GLenum internalformat, GLsizei width, GLsizei height)
{
	glRenderbufferStorage(m_Target, internalformat, width, height);
	return this;
}

void scr::Renderbuffer::Unbind()
{
	glBindRenderbuffer(m_Target, 0);
}
