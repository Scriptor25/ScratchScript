#include <scr/Window.hpp>

void glfw_error_callback(int error_code, const char* description)
{
	fprintf(stderr, "[GLFW 0x%08X] %s\n", error_code, description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool scr::Window::Init()
{
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
	{
		fprintf(stderr, "[ScratchScript] Failed to init GLFW\n");
		return false;
	}

	return true;
}

void scr::Window::Terminate()
{
	glfwTerminate();
}

scr::Window::Window(const std::string& title, int width, int height)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	m_Handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_Handle)
	{
		fprintf(stderr, "[ScratchScript] Failed to create GLFW window\n");
		return;
	}

	glfwSetKeyCallback(m_Handle, glfw_key_callback);

	glfwMakeContextCurrent(m_Handle);
	glfwSwapInterval(1); // v-sync
}

scr::Window::~Window()
{
	Destroy();
}

scr::Window::operator bool() const
{
	return m_Handle;
}

GLFWwindow* scr::Window::operator*() const
{
	return m_Handle;
}

void scr::Window::SetTitle(const std::string& title)
{
	glfwSetWindowTitle(m_Handle, title.c_str());
}

void scr::Window::GetFramebufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(m_Handle, width, height);
}

bool scr::Window::Update()
{
	glfwSwapBuffers(m_Handle);
	glfwPollEvents();

	return !glfwWindowShouldClose(m_Handle);
}

void scr::Window::Destroy()
{
	if (m_Destroyed) return;
	m_Destroyed = true;
	glfwDestroyWindow(m_Handle);
	m_Handle = NULL;
}
