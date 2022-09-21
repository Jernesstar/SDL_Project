#pragma once

#include <iostream>
#include <vector>

namespace Saddle {
class Log { 
public:
    template<typename... Args>
    static void Info(const std::string& message, const Args&&... args)
    {
        printf("[Info]: %s\n", message.c_str(), args...);
    }

    template<typename... Args>
    static void Warning(const std::string& message, const Args&&... args)
    {
        printf("[Warning]: %s\n", message.c_str(), args...);
    }

    template<typename... Args>
    static void Error(const std::string& message, const Args&&... args)
    {
        printf("[Error]: %s\n", message.c_str(), args...);
    }

private:
    Log() = delete;
    ~Log() = delete; 
};

}

#define SADDLE_CORE_LOG_INFO(message, ...) Saddle::Log::Info(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_WARNING(message, ...) Saddle::Log::Warning(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_ERROR(message, ...) Saddle::Log::Error(message, ## __VA_ARGS__)