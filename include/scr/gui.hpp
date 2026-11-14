#pragma once

#include <scr/editor.hpp>
#include <scr/scr.hpp>

#include <imgui.h>

namespace scr
{
    using ViewportCallback = ImTextureID(*)(int width, int height, bool cleanup);

    void ShowViewport(ViewportCallback callback);

    void ShowSprites(Project &project, size_t &selected);

    void ShowResources(Sprite &sprite, TextEditor &editor);

    void ShowProperties(Sprite &sprite);
}
