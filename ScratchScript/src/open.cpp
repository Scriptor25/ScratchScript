#include <scr/ScratchScript.hpp>

#include <filesystem>

std::fstream scr::Open(const std::string& name, std::fstream::openmode mode)
{
	std::filesystem::path root = "resources";
	auto stream = std::fstream(root / name, mode);
	if (stream.is_open())
		return stream;

	fprintf(stderr, "Failed to open '%s'\n", name.c_str());
	throw;
}
