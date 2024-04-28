#include <scr/Gui.hpp>

#include <imgui.h>

void scr::ShowViewport(ViewportCallback callback)
{
    if (ImGui::Begin("Viewport"))
    {
        const auto size = ImGui::GetContentRegionAvail();
        const auto texId = callback(static_cast<int>(size.x), static_cast<int>(size.y), false);
        ImGui::Image(texId, size, {0, 1}, {1, 0});
    }
    ImGui::End();
}
