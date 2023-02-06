#pragma once

#include <stdio.h>
#include <string>

namespace Saddle {
class Log { 
public:
    template<typename... Args>
    static void Info(const std::string& format_string, Args&&... args)
    {
        printf("[Info]: ");
        printf(format_string.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }

    template<typename... Args>
    static void Warning(const std::string& format_string, Args&&... args)
    {
        printf("[Warning]: ");
        printf(format_string.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }

    template<typename... Args>
    static void Error(const std::string& format_string, Args&&... args)
    {
        printf("[Error]: ");
        printf(format_string.c_str(), std::forward<Args>(args)...);
        printf("\n");
    }

private:
    Log() = delete;
    ~Log() = delete; 
};

}

#define SADDLE_CORE_LOG_INFO(message, ...) Saddle::Log::Info(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_WARNING(message, ...) Saddle::Log::Warning(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_ERROR(message, ...) Saddle::Log::Error(message, ## __VA_ARGS__)