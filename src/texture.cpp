#include <vector>
#include <nothings/stb_image.h>
#include <scr/GL.hpp>
#include <scr/Log.hpp>
#include <scr/ScratchScript.hpp>

std::shared_ptr<scr::Texture> scr::Texture::Load(const std::string &filename)
{
    auto stream = Open(filename, std::ios::in | std::ios::ate | std::ios::binary);

    const std::streamsize length = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<stbi_uc> source(length);
    stream.read(reinterpret_cast<char *>(source.data()), length);

    int width, height;

    stbi_set_flip_vertically_on_load(true);
    const auto pixels = stbi_load_from_memory(source.data(), static_cast<int>(length), &width, &height, nullptr, 4);

    if (!pixels)
    {
        const auto message = stbi_failure_reason();
        Error("failed to load image from '{}': {}", filename, message);
    }

    auto texture = std::make_shared<Texture>(GL_TEXTURE_2D);
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

scr::Texture::Texture(const GLenum target)
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

int scr::Texture::Width() const
{
    return m_Width;
}

int scr::Texture::Height() const
{
    return m_Height;
}

scr::Texture::operator bool() const
{
    return m_Handle != 0;
}

scr::Texture *scr::Texture::Bind()
{
    glBindTexture(m_Target, m_Handle);
    return this;
}

scr::Texture *scr::Texture::Parameter(const GLenum name, const GLint param)
{
    glTexParameteri(m_Target, name, param);
    return this;
}

scr::Texture *scr::Texture::Image2D(
    const GLint level,
    const GLint internal_format,
    const GLsizei width,
    const GLsizei height,
    const GLint border,
    const GLenum format,
    const GLenum type,
    const void *pixels)
{
    glTexImage2D(m_Target, level, internal_format, width, height, border, format, type, pixels);
    m_Width = width;
    m_Height = height;
    return this;
}

void scr::Texture::Unbind() const
{
    glBindTexture(m_Target, 0);
}
