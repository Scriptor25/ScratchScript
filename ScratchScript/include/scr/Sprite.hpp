#pragma once

#include <scr/Costume.hpp>
#include <scr/ScratchScript.hpp>
#include <scr/Script.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace scr
{
	struct Sprite
	{
		Costume GetCostume();
		void ApplyModel();

		std::string Name;

		bool IsStage = false;
		bool Show = true;

		float Position[2]{ 0.0f, 0.0f };
		float Size = 100.0f;
		float Direction = 90.0f;

		Script Script;

		size_t CurrentCostume = 0;
		std::vector<Costume> Costumes;

		glm::mat4 Model;
	};
}
