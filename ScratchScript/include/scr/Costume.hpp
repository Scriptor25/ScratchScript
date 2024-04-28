#pragma once

#include <scr/GL.hpp>
#include <scr/ScratchScript.hpp>

#include <string>

namespace scr
{
	struct Costume
	{
		std::string Name;
		std::string Source;

		void Load();
		
		int Width();
		int Height();
		GLuint TexID();

		Texture* Tex = nullptr;
	};
}
