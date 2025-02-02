#include <filesystem>
#include <scr/ScratchScript.hpp>

std::fstream scr::Open(const std::string &name, const std::fstream::openmode mode)
{
    const std::filesystem::path root = "resources";
    if (auto stream = std::fstream(root / name, mode); stream.is_open()) return stream;

    fprintf(stderr, "Failed to open '%s'\n", name.c_str());
    throw;
}
