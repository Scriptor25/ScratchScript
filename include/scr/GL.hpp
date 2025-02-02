#pragma once

#include <memory>
#include <string>
#include <GL/glew.h>

namespace scr
{
    class Buffer;

    class VertexArray;

    class FrameBuffer;

    class RenderBuffer;

    class Texture;

    class Program;

    class Buffer
    {
    public:
        Buffer(GLenum target, GLenum usage);

        ~Buffer();

        explicit operator bool() const;

        Buffer *Bind();

        Buffer *Data(GLsizeiptr size, const void *data);

        void Unbind() const;

    private:
        GLuint m_Handle{};
        GLenum m_Target;
        GLenum m_Usage;
    };

    class VertexArray
    {
    public:
        VertexArray();

        ~VertexArray();

        explicit operator bool() const;

        VertexArray *Bind();

        void Unbind();

    private:
        GLuint m_Handle{};
    };

    class FrameBuffer
    {
    public:
        explicit FrameBuffer(GLenum target);

        ~FrameBuffer();

        explicit operator bool() const;

        FrameBuffer *Bind();

        FrameBuffer *AddTexture2D(GLenum attachment, const Texture *texture, GLint level);

        FrameBuffer *AddRenderBuffer(GLenum attachment, const RenderBuffer *render_buffer);

        void Unbind() const;

    private:
        GLuint m_Handle{};
        GLenum m_Target;
    };

    class RenderBuffer
    {
    public:
        explicit RenderBuffer(GLenum target);

        ~RenderBuffer();

        [[nodiscard]] GLuint Handle() const;

        [[nodiscard]] GLenum Target() const;

        explicit operator bool() const;

        RenderBuffer *Bind();

        RenderBuffer *Storage(GLenum internal_format, GLsizei width, GLsizei height);

        void Unbind() const;

    private:
        GLuint m_Handle{};
        GLenum m_Target;
    };

    class Texture
    {
    public:
        static std::shared_ptr<Texture> Load(const std::string &filename);

        explicit Texture(GLenum target);

        ~Texture();

        [[nodiscard]] GLuint Handle() const;

        [[nodiscard]] GLenum Target() const;

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        explicit operator bool() const;

        Texture *Bind();

        Texture *Parameter(GLenum name, GLint param);

        Texture *Image2D(
            GLint level,
            GLint internal_format,
            GLsizei width,
            GLsizei height,
            GLint border,
            GLenum format,
            GLenum type,
            const void *pixels);

        void Unbind() const;

    private:
        GLuint m_Handle{};
        GLenum m_Target;

        int m_Width{}, m_Height{};
    };

    class Program
    {
    public:
        Program(const std::string &vertex, const std::string &fragment);

        ~Program();

        explicit operator bool() const;

        GLint Uniform(const char *name) const;

        Program *Bind();

        void Unbind();

    private:
        GLuint m_Handle;
    };
}
