#pragma once

#include <string>
#include <vector>
#include <scr/ScratchScript.hpp>

namespace scr
{
    struct Script
    {
        std::string Source;
        std::vector<std::string> Lines;
        bool Changed = false;
    };
}
