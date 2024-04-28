#include <scr/GL.hpp>

scr::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Handle);
}

scr::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Handle);
}

scr::VertexArray::operator bool() const
{
	return m_Handle != 0;
}

scr::VertexArray* scr::VertexArray::Bind()
{
	glBindVertexArray(m_Handle);
	return this;
}

void scr::VertexArray::Unbind()
{
	glBindVertexArray(0);
}
