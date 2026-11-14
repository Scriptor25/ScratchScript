#pragma once

#include <scr/costume.hpp>
#include <scr/scr.hpp>
#include <scr/script.hpp>

#include <nlohmann/json.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace scr
{
    struct Sprite
    {
        [[nodiscard]] const Costume *GetCostume() const;

        void ApplyModel();

        std::string Name;

        bool IsStage = false;
        bool Show = true;

        float Position[2]{ 0.0f, 0.0f };
        float Size = 100.0f;
        float Direction = 90.0f;

        Script Script_;

        size_t CurrentCostume = 0;
        std::vector<Costume> Costumes;

        glm::mat4 Model;
    };

    void to_json(nlohmann::json &json, const Sprite &sprite);

    void from_json(const nlohmann::json &json, Sprite &sprite);
}
