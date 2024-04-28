#include <scr/Gui.hpp>
#include <scr/Project.hpp>
#include <scr/Sprite.hpp>

#include <imgui.h>

const float ICON_SIZE = 80.0f;
const float COLUMN_WIDTH = ICON_SIZE + 80.0f;

void scr::ShowSprites(Project& project, size_t& selected)
{
	if (ImGui::Begin("Sprites"))
	{
		const auto panel_width = ImGui::GetContentRegionAvail().x;
		const auto column_width = COLUMN_WIDTH + ImGui::GetStyle().ItemSpacing.x;
		const auto column_height = ICON_SIZE + ImGui::CalcTextSize("Sprite").y;
		int columns = (int)(panel_width / column_width);
		if (columns < 1) columns = 1;

		ImGui::Columns(columns, 0, false);

		size_t moveSrc = 0;
		size_t moveDst = 0;
		bool moved = false;

		size_t i = 0;
		for (auto& sprite : project.Sprites)
		{
			ImGui::PushID(i);

			bool sel = selected == i;

			auto pos = ImGui::GetCursorPos();
			ImGui::SetNextItemAllowOverlap();
			if (ImGui::Selectable("##selectable", &sel, 0, { COLUMN_WIDTH, column_height }))
				selected = i;

			if (ImGui::BeginDragDropSource())
			{
				ImGui::TextUnformatted(sprite.Name.c_str());
				ImGui::SetDragDropPayload("SPRITE_INDEX", &i, sizeof(size_t));
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const auto payload = ImGui::AcceptDragDropPayload("SPRITE_INDEX"))
				{
					moveSrc = *(const size_t*)payload->Data;
					moveDst = i;
					moved = true;
				}

				ImGui::EndDragDropTarget();
			}

			auto costume = sprite.GetCostume();
			auto scale = std::min(ICON_SIZE / costume.Width(), ICON_SIZE / costume.Height());
			auto w = scale * costume.Width();
			auto h = scale * costume.Height();
			ImGui::SetCursorPosX(pos.x + (COLUMN_WIDTH - w) * 0.5f);
			ImGui::SetCursorPosY(pos.y);
			ImGui::Image((void*)(intptr_t)costume.TexID(), { w, h }, { 0, 1 }, { 1, 0 });

			const auto tw = ImGui::CalcTextSize(sprite.Name.c_str()).x;
			ImGui::SetCursorPosX(pos.x + (COLUMN_WIDTH - tw) * 0.5f);
			ImGui::SetCursorPosY(pos.y + ICON_SIZE);
			ImGui::TextUnformatted(sprite.Name.c_str());

			ImGui::PopID();

			ImGui::NextColumn();
			i++;
		}

		if (moved && moveSrc != moveDst)
		{
			if (moveDst > moveSrc)
			{
				auto sprite = project.Sprites[moveSrc];
				for (size_t i = moveSrc; i < moveDst; i++)
					project.Sprites[i] = project.Sprites[i + 1];
				project.Sprites[moveDst] = sprite;
			}
			else
			{
				auto sprite = project.Sprites[moveSrc];
				for (size_t i = moveSrc; i > moveDst; i--)
					project.Sprites[i] = project.Sprites[i - 1];
				project.Sprites[moveDst] = sprite;
			}
			selected = moveDst;
		}
	}
	ImGui::End();
}
