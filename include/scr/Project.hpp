#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <scr/ScratchScript.hpp>

namespace scr
{
    struct Project
    {
        std::string Name;
        uint32_t Version;
        std::vector<Sprite> Sprites;
    };

    void to_json(nlohmann::json &json, const Project &project);

    void from_json(const nlohmann::json &json, Project &project);
}
