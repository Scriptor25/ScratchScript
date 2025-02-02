#pragma once

#define GLFW_INCLUDE_NONE

#include <string>
#include <GLFW/glfw3.h>

namespace scr
{
    class Window
    {
    public:
        static void Initialize();
        static void Terminate();

        Window(const std::string &title, int width, int height);

        ~Window();

        explicit operator bool() const;

        GLFWwindow *operator*() const;

        void SetTitle(const std::string &title) const;

        void GetFrameBufferSize(int &width, int &height) const;

        [[nodiscard]] bool Update() const;

        void Destroy();

    private:
        bool m_Destroyed = false;

        GLFWwindow *m_Handle;
    };
}
