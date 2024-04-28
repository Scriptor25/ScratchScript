#include <scr/Costume.hpp>
#include <scr/Json.hpp>
#include <scr/Sprite.hpp>

#include <glm/ext.hpp>

void scr::to_json(nlohmann::json &json, const Sprite &sprite)
{
    json["name"] = sprite.Name;
    json["isStage"] = sprite.IsStage;
    json["script"] = sprite.Script.Source;

    if (!sprite.IsStage)
    {
        json["show"] = sprite.Show;
        json["position"] = sprite.Position;
        json["size"] = sprite.Size;
        json["direction"] = sprite.Direction;
        json["currentCostume"] = sprite.CurrentCostume;
        json["costumes"] = sprite.Costumes;
    }
}

void scr::from_json(const nlohmann::json &json, Sprite &sprite)
{
    sprite.Name = json["name"];
    sprite.IsStage = json["isStage"];
    sprite.Script.Source = json["script"];

    if (!sprite.IsStage)
    {
        sprite.Show = json["show"];
        sprite.Position[0] = json["position"][0];
        sprite.Position[1] = json["position"][1];
        sprite.Size = json["size"];
        sprite.Direction = json["direction"];
        sprite.CurrentCostume = json["currentCostume"];
        sprite.Costumes = json["costumes"];
    }
}

scr::Costume scr::Sprite::GetCostume()
{
    if (Costumes.empty() || CurrentCostume > (Costumes.size() - 1))
        return {};
    return Costumes[CurrentCostume];
}

void scr::Sprite::ApplyModel()
{
    auto width = GetCostume().Width();
    auto height = GetCostume().Height();

    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, {Position[0], Position[1], 0.0f});
    Model = glm::scale(Model, {Size / 100.0f, Size / 100.0f, 1.0f});
    Model = glm::rotate(Model, glm::radians(Direction - 90.0f), {0.0f, 0.0f, 1.0f});
    Model = glm::scale(Model, {width, height, 1.0f});
}
