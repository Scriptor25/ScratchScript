#include <scr/GL.hpp>
#include <scr/ScratchScript.hpp>

static std::string read_file(const std::string &name)
{
    auto stream = scr::Open(name, std::ios::in | std::ios::ate);
    std::string source;
    source.reserve(stream.tellg());
    stream.seekg(0, std::ios::beg);
    source.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
    return source;
}

static void check_compiled(GLuint shader)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLsizei length;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &length, message);
        fprintf(stderr, "[OpenGL] Failed to compile shader:\n%s\n", message);
    }
}

scr::Program::Program(const std::string &vertex, const std::string &fragment)
{
    m_Handle = glCreateProgram();
    {
        auto source = read_file(vertex);
        auto c_str = source.c_str();

        auto shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader, 1, &c_str, nullptr);
        glCompileShader(shader);
        check_compiled(shader);
        glAttachShader(m_Handle, shader);
        glDeleteShader(shader);
    }
    {
        auto source = read_file(fragment);
        auto c_str = source.c_str();

        auto shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader, 1, &c_str, nullptr);
        glCompileShader(shader);
        check_compiled(shader);
        glAttachShader(m_Handle, shader);
        glDeleteShader(shader);
    }
    glLinkProgram(m_Handle);
    glValidateProgram(m_Handle);
}

scr::Program::~Program()
{
    glDeleteProgram(m_Handle);
}

scr::Program::operator bool() const
{
    return m_Handle != 0;
}

GLint scr::Program::Uniform(const char *name) const
{
    return glGetUniformLocation(m_Handle, name);
}

scr::Program *scr::Program::Bind()
{
    glUseProgram(m_Handle);
    return this;
}

void scr::Program::Unbind()
{
    glUseProgram(0);
}
