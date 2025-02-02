#include <iostream>
#include <scr/Log.hpp>

void scr::Error(const std::string &message)
{
    std::cerr << "[Error] " << message << std::endl;
    exit(1);
}

void scr::Warning(const std::string &message)
{
    std::cerr << "[Warning] " << message << std::endl;
}

void scr::Info(const std::string &message)
{
    std::cout << "[Info] " << message << std::endl;
}
