#include <scr/Costume.hpp>
#include <scr/Json.hpp>

void scr::to_json(nlohmann::json& json, const Costume& costume)
{
	json["name"] = costume.Name;
	json["source"] = costume.Source;
}

void scr::from_json(const nlohmann::json& json, Costume& costume)
{
	costume.Name = json["name"];
	costume.Source = json["source"];
}

void scr::Costume::Load()
{
	if (Tex)
		delete Tex;
	Tex = scr::Texture::Load("test/" + Source);
}

int scr::Costume::Width()
{
	if (!Tex)
		return 1;
	return Tex->Width();
}

int scr::Costume::Height()
{
	if (!Tex)
		return 1;
	return Tex->Height();
}

GLuint scr::Costume::TexID()
{
	if (!Tex)
		return 0;
	return Tex->Handle();
}
