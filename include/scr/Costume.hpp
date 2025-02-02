#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <scr/GL.hpp>

namespace scr
{
    struct Costume
    {
        void Load();

        [[nodiscard]] int Width() const;

        [[nodiscard]] int Height() const;

        [[nodiscard]] GLuint TexID() const;

        std::string Name;
        std::string Source;
        std::shared_ptr<Texture> Tex;
    };

    void to_json(nlohmann::json &json, const Costume &costume);

    void from_json(const nlohmann::json &json, Costume &costume);
}
