#pragma once

#include <stdio.h>
#include <string>

namespace Saddle {
class Log { 
public:
    static void Info(const std::string& message)
    {
        printf("[Info]: %s\n", message.c_str());
    }

    static void Warning(const std::string& message)
    {
        printf("[Warning]: %s\n", message.c_str());
    }

    static void Error(const std::string& message)
    {
        printf("[Error]: %s\n", message.c_str());
    }

    template<typename... Args, typename = 
        std::enable_if<std::is_same<Args..., const char*>::value || std::is_same<Args..., std::string>::value, bool>>
    static void Info(const std::string& format_string, Args&&... args)
    {
        printf(format_string.c_str(), std::string(args).c_str()...);
    }

    template<typename... Args, typename = 
        std::enable_if<!std::is_same<Args..., const char*>::value && !std::is_same<Args..., std::string>::value, bool>>
    static void Info(const std::string& format_string, Args&&... args)
    {
        printf(format_string.c_str(), std::to_string(args).c_str()...);
    }

private:
    Log() = delete;
    ~Log() = delete; 
};

}

#define SADDLE_CORE_LOG_INFO(message, ...) Saddle::Log::Info(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_WARNING(message, ...) Saddle::Log::Warning(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_ERROR(message, ...) Saddle::Log::Error(message, ## __VA_ARGS__)