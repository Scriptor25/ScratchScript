#include <scr/GL.hpp>
#include <scr/ScratchScript.hpp>

#include <nothings/stb_image.h>

scr::Texture* scr::Texture::Load(const std::string& filename)
{
	auto texture = new Texture(GL_TEXTURE_2D);

	auto stream = Open(filename, std::ios::in | std::ios::ate | std::ios::binary);

	int length = stream.tellg();
	stream.seekg(0, std::ios::beg);
	stbi_uc* source = new stbi_uc[length];
	stream.read(reinterpret_cast<char*>(source), length);

	int width, height;

	stbi_set_flip_vertically_on_load(true);
	auto pixels = stbi_load_from_memory(source, length, &width, &height, 0, 4);

	delete[] source;

	if (!pixels)
	{
		const char* message = stbi_failure_reason();
		fprintf(stderr, "Failed to load image from '%s':\n%s\n", filename.c_str(), message);
		return nullptr;
	}

	texture
		->Bind()
		->Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
		->Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
		->Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
		->Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
		->Image2D(0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels)
		->Unbind();

	stbi_image_free(pixels);

	return texture;
}

scr::Texture::Texture(GLenum target)
	: m_Target(target)
{
	glGenTextures(1, &m_Handle);
}

scr::Texture::~Texture()
{
	glDeleteTextures(1, &m_Handle);
}

GLuint scr::Texture::Handle() const
{
	return m_Handle;
}

GLenum scr::Texture::Target() const
{
	return m_Target;
}

int scr::Texture::Width()
{
	return m_Width;
}

int scr::Texture::Height()
{
	return m_Height;
}

scr::Texture::operator bool() const
{
	return m_Handle != 0;
}

scr::Texture* scr::Texture::Bind()
{
	glBindTexture(m_Target, m_Handle);
	return this;
}

scr::Texture* scr::Texture::Parameter(GLenum pname, GLint param)
{
	glTexParameteri(m_Target, pname, param);
	return this;
}

scr::Texture* scr::Texture::Image2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels)
{
	glTexImage2D(m_Target, level, internalformat, width, height, border, format, type, pixels);
	m_Width = width;
	m_Height = height;
	return this;
}

void scr::Texture::Unbind()
{
	glBindTexture(m_Target, 0);
}
