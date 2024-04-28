#pragma once

#include <scr/ScratchScript.hpp>

#include <string>
#include <vector>

namespace scr
{
	struct Script
	{
		std::string Source;

		std::vector<std::string> Lines;
		bool Changed = false;
	};
}
