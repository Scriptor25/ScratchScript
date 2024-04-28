#include <scr/Gui.hpp>
#include <scr/Sprite.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

void scr::ShowProperties(Sprite& sprite)
{
	if (ImGui::Begin("Properties"))
	{
		if (sprite.IsStage)
		{
			ImGui::Text("Stage");
		}
		else
		{
			bool change = false;

			ImGui::InputText("Name", &sprite.Name);
			change |= ImGui::DragFloat2("Position", sprite.Position);
			ImGui::Checkbox("Show", &sprite.Show);
			change |= ImGui::DragFloat("Size", &sprite.Size);
			change |= ImGui::DragFloat("Direction", &sprite.Direction, 1.0f, -180.0f, 180.0f);

			if (change)
				sprite.ApplyModel();
		}
	}
	ImGui::End();
}
