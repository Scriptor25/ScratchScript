#include <scr/Json.hpp>
#include <scr/Project.hpp>
#include <scr/Sprite.hpp>

void scr::to_json(nlohmann::json& json, const Project& project)
{
	json["name"] = project.Name;
	json["version"] = project.Version;
	json["sprites"] = project.Sprites;
}

void scr::from_json(const nlohmann::json& json, Project& project)
{
	project.Name = json["name"];
	project.Version = json["version"];
	project.Sprites = json["sprites"];
}
