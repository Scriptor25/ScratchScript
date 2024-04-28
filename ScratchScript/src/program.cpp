#include <scr/GL.hpp>
#include <scr/ScratchScript.hpp>

static std::string readfile(const std::string& name)
{
	auto stream = scr::Open(name, std::ios::in | std::ios::ate);
	std::string source;
	source.reserve(stream.tellg());
	stream.seekg(0, std::ios::beg);
	source.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
	return source;
}

static void checkcompiled(GLuint shader)
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

scr::Program::Program(const std::string& vertex, const std::string& fragment)
{
	m_Handle = glCreateProgram();
	{
		auto source = readfile(vertex);
		auto cstr = source.c_str();

		auto shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader, 1, &cstr, 0);
		glCompileShader(shader);
		checkcompiled(shader);
		glAttachShader(m_Handle, shader);
		glDeleteShader(shader);
	}
	{
		auto source = readfile(fragment);
		auto cstr = source.c_str();

		auto shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader, 1, &cstr, 0);
		glCompileShader(shader);
		checkcompiled(shader);
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

GLint scr::Program::Uniform(const char* name)
{
	return glGetUniformLocation(m_Handle, name);
}

scr::Program* scr::Program::Bind()
{
	glUseProgram(m_Handle);
	return this;
}

void scr::Program::Unbind()
{
	glUseProgram(0);
}
