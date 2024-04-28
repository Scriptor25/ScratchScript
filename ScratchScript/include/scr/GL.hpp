#pragma once

#include <GL/glew.h>

#include <string>

namespace scr
{
    class Buffer;

    class VertexArray;

    class Framebuffer;

    class Renderbuffer;

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
        GLuint m_Handle = 0;
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
        GLuint m_Handle;
    };

    class Framebuffer
    {
    public:
        explicit Framebuffer(GLenum target);

        ~Framebuffer();

        explicit operator bool() const;

        Framebuffer *Bind();

        Framebuffer *AddTexture2D(GLenum attachment, const Texture *texture, GLint level);

        Framebuffer *AddRenderbuffer(GLenum attachment, const Renderbuffer *renderbuffer);

        void Unbind() const;

    private:
        GLuint m_Handle = 0;
        GLenum m_Target;
    };

    class Renderbuffer
    {
    public:
        explicit Renderbuffer(GLenum target);

        ~Renderbuffer();

        [[nodiscard]] GLuint Handle() const;

        [[nodiscard]] GLenum Target() const;

        explicit operator bool() const;

        Renderbuffer *Bind();

        Renderbuffer *Storage(GLenum internalformat, GLsizei width, GLsizei height);

        void Unbind() const;

    private:
        GLuint m_Handle = 0;
        GLenum m_Target;
    };

    class Texture
    {
    public:
        static Texture *Load(const std::string &filename);

        explicit Texture(GLenum target);

        ~Texture();

        [[nodiscard]] GLuint Handle() const;

        [[nodiscard]] GLenum Target() const;

        int Width();

        int Height();

        explicit operator bool() const;

        Texture *Bind();

        Texture *Parameter(GLenum name, GLint param);

        Texture *Image2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format,
                         GLenum type, const void *pixels);

        void Unbind();

    private:
        GLuint m_Handle;
        GLenum m_Target;

        int m_Width = 0, m_Height = 0;
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
