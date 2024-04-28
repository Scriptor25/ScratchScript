#pragma once

#include <scr/ScratchScript.hpp>

#include <nlohmann/json.hpp>

namespace scr
{
    void to_json(nlohmann::json &json, const Project &project);

    void from_json(const nlohmann::json &json, Project &project);

    void to_json(nlohmann::json &json, const Sprite &sprite);

    void from_json(const nlohmann::json &json, Sprite &sprite);

    void to_json(nlohmann::json &json, const Costume &costume);

    void from_json(const nlohmann::json &json, Costume &costume);
}
