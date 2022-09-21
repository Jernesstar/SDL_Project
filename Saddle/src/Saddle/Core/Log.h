#pragma once

#include <iostream>
#include <vector>

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

    template<typename... Args>
    static void Info(const std::string& format_string, Args&&... args)
    {
        printf(format_string.c_str(), std::string(args).c_str()...);
    }

    template<typename... Args>
    static void Warning(const std::string& format_string, Args&&... args)
    {
        printf(format_string.c_str(), std::string(args).c_str()...);
    }

    template<typename... Args>
    static void Error(const std::string& format_string, Args&&... args)
    {
        printf(format_string.c_str(), std::string(args).c_str()...);
    }

private:
    Log() = delete;
    ~Log() = delete; 
};

}

#define SADDLE_CORE_LOG_INFO(message, ...) Saddle::Log::Info(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_WARNING(message, ...) Saddle::Log::Warning(message, ## __VA_ARGS__)
#define SADDLE_CORE_LOG_ERROR(message, ...) Saddle::Log::Error(message, ## __VA_ARGS__)