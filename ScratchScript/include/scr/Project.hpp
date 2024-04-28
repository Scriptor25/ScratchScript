#pragma once

#include <scr/ScratchScript.hpp>

#include <string>
#include <vector>

namespace scr
{
	struct Project
	{
		std::string Name;
		uint32_t Version;
		std::vector<Sprite> Sprites;
	};
}
