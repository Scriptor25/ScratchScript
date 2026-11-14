#pragma once

#include <format>
#include <string>

namespace scr
{
    [[noreturn]] void Error(const std::string &message);

    template<typename... Args>
    [[noreturn]] void Error(const std::string &format, Args &&... args)
    {
        const auto message = std::vformat(format, std::make_format_args(args...));
        Error(message);
    }

    void Warning(const std::string &message);

    template<typename... Args>
    void Warning(const std::string &format, Args &&... args)
    {
        const auto message = std::vformat(format, std::make_format_args(args...));
        Warning(message);
    }

    void Info(const std::string &message);

    template<typename... Args>
    void Info(const std::string &format, Args &&... args)
    {
        const auto message = std::vformat(format, std::make_format_args(args...));
        Info(message);
    }
}
