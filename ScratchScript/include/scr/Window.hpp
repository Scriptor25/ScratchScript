#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace scr
{
	class Window
	{
	public:
		static bool Init();
		static void Terminate();

		Window(const std::string& title, int width, int height);
		~Window();

		operator bool() const;
		GLFWwindow* operator*() const;

		void SetTitle(const std::string& title);

		void GetFramebufferSize(int* width, int* height);

		bool Update();
		void Destroy();

	private:
		bool m_Destroyed = false;

		GLFWwindow* m_Handle;
	};
}
