#pragma once

#include <fstream>
#include <memory>
#include <string>

#define MAKE_VERSION(major, minor, patch) ((major & 0b1111111111) << 22 | (minor & 0b1111111111) << 12 | (patch & 0b111111111111))
#define VERSION_MAJOR(version) ((version >> 22) & 0b1111111111)
#define VERSION_MINOR(version) ((version >> 12) & 0b1111111111)
#define VERSION_PATCH(version) (version & 0b111111111111)
#define VERSION_STRING(version) (std::to_string(VERSION_MAJOR(version)) + "." + std::to_string(VERSION_MINOR(version)) + "." + std::to_string(VERSION_PATCH(version)))

namespace scr
{
    // Get the current version
    uint32_t GetVersion();

    // Open a file stream to a resource file
    std::fstream Open(const std::string &name, std::fstream::openmode mode);

    struct Project;
    struct Sprite;
    struct Costume;
    struct Script;
}