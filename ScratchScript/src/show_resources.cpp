#include <scr/Gui.hpp>
#include <scr/Sprite.hpp>

#include <imgui/imgui.h>

#include <format>

const float ICON_SIZE = 80.0f;
const float COLUMN_WIDTH = ICON_SIZE + 80.0f;

void scr::ShowResources(Sprite& sprite, TextEditor& editor)
{
	if (ImGui::Begin("Resources"))
	{
		if (ImGui::BeginTabBar("##bar"))
		{
			if (ImGui::BeginTabItem("Script"))
			{
				editor.Render("Editor");
				if (editor.IsTextChanged())
					sprite.Script.Changed = true;

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Costumes"))
			{
				const auto column_height = ICON_SIZE + ImGui::CalcTextSize("Costume").y * 2;
				const auto column_width = COLUMN_WIDTH + ImGui::GetStyle().ItemSpacing.x;

				if (ImGui::BeginChild("##selectcostume", { column_width, 0 }));
				{
					size_t moveSrc = 0;
					size_t moveDst = 0;
					bool moved = false;

					size_t i = 0;
					for (auto& costume : sprite.Costumes)
					{
						ImGui::PushID(i);

						bool sel = sprite.CurrentCostume == i;

						auto pos = ImGui::GetCursorPos();
						ImGui::SetNextItemAllowOverlap();
						if (ImGui::Selectable("##selectable", &sel, 0, { COLUMN_WIDTH, column_height }))
						{
							sprite.CurrentCostume = i;
							sprite.ApplyModel();
						}

						if (ImGui::BeginDragDropSource())
						{
							ImGui::TextUnformatted(costume.Name.c_str());
							ImGui::SetDragDropPayload("COSTUME_INDEX", &i, sizeof(size_t));
							ImGui::EndDragDropSource();
						}

						if (ImGui::BeginDragDropTarget())
						{
							if (const auto payload = ImGui::AcceptDragDropPayload("COSTUME_INDEX"))
							{
								moveSrc = *(const size_t*)payload->Data;
								moveDst = i;
								moved = true;
							}

							ImGui::EndDragDropTarget();
						}

						auto scale = std::min(ICON_SIZE / costume.Width(), ICON_SIZE / costume.Height());
						auto w = scale * costume.Width();
						auto h = scale * costume.Height();
						ImGui::SetCursorPosX(pos.x + (COLUMN_WIDTH - w) * 0.5f);
						ImGui::SetCursorPosY(pos.y);
						ImGui::Image((void*)(intptr_t)costume.TexID(), { w, h }, { 0, 1 }, { 1, 0 });

						auto ts = ImGui::CalcTextSize(costume.Name.c_str());
						ImGui::SetCursorPosX(pos.x + (COLUMN_WIDTH - ts.x) * 0.5f);
						ImGui::SetCursorPosY(pos.y + ICON_SIZE);
						ImGui::TextUnformatted(costume.Name.c_str());

						auto sizeText = std::format("{}x{}", costume.Width(), costume.Height());
						auto dy = ts.y;
						ts = ImGui::CalcTextSize(sizeText.c_str());
						ImGui::SetCursorPosX(pos.x + (COLUMN_WIDTH - ts.x) * 0.5f);
						ImGui::SetCursorPosY(pos.y + ICON_SIZE + dy);
						ImGui::TextUnformatted(sizeText.c_str());

						ImGui::PopID();

						ImGui::NextColumn();
						i++;
					}

					if (moved && moveSrc != moveDst)
					{
						if (moveDst > moveSrc)
						{
							auto costume = sprite.Costumes[moveSrc];
							for (size_t i = moveSrc; i < moveDst; i++)
								sprite.Costumes[i] = sprite.Costumes[i + 1];
							sprite.Costumes[moveDst] = costume;
						}
						else
						{
							auto costume = sprite.Costumes[moveSrc];
							for (size_t i = moveSrc; i > moveDst; i--)
								sprite.Costumes[i] = sprite.Costumes[i - 1];
							sprite.Costumes[moveDst] = costume;
						}
						sprite.CurrentCostume = moveDst;
						sprite.ApplyModel();
					}

					ImGui::EndChild();
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Sounds"))
			{
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}
