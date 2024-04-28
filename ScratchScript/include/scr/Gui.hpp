#pragma once

#include <scr/ScratchScript.hpp>
#include <scr/TextEditor.h>

#include <imgui.h>

#include <vector>

namespace scr
{
    typedef ImTextureID(*ViewportCallback)(int width, int height, bool cleanup);

    void ShowViewport(ViewportCallback callback);

    void ShowSprites(Project &project, size_t &selected);

    void ShowResources(Sprite &sprite, TextEditor &editor);

    void ShowProperties(Sprite &sprite);
}
