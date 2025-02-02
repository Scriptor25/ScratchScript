#include <scr/Log.hpp>
#include <scr/Window.hpp>

static void glfw_error_callback(const int error_code, const char *description)
{
    scr::Warning("[GLFW 0x{:08X}] {}", error_code, description);
}

static void glfw_key_callback(GLFWwindow *window, const int key, int /*scancode*/, const int action, int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void scr::Window::Initialize()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        Error("failed to initialize glfw");
}

void scr::Window::Terminate()
{
    glfwTerminate();
}

scr::Window::Window(const std::string &title, const int width, const int height)
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    m_Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Handle)
        Error("failed to create glfw window");

    glfwSetKeyCallback(m_Handle, glfw_key_callback);

    glfwMakeContextCurrent(m_Handle);
    glfwSwapInterval(1);
}

scr::Window::~Window()
{
    Destroy();
}

scr::Window::operator bool() const
{
    return m_Handle;
}

GLFWwindow *scr::Window::operator*() const
{
    return m_Handle;
}

void scr::Window::SetTitle(const std::string &title) const
{
    glfwSetWindowTitle(m_Handle, title.c_str());
}

void scr::Window::GetFrameBufferSize(int &width, int &height) const
{
    glfwGetFramebufferSize(m_Handle, &width, &height);
}

bool scr::Window::Update() const
{
    glfwSwapBuffers(m_Handle);
    glfwPollEvents();

    return !glfwWindowShouldClose(m_Handle);
}

void scr::Window::Destroy()
{
    if (m_Destroyed)
        return;

    m_Destroyed = true;
    glfwDestroyWindow(m_Handle);
    m_Handle = nullptr;
}
