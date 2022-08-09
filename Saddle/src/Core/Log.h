#pragma once

#include <iostream>
#include <vector>

namespace Saddle {
class Log {
    
public:
    template<typename... Args>
    static void Info(const std::string& message, const Args&&... args)
    {

    }

    template<typename... Args>
    static void Warning(const std::string& message, const Args&&... args)
    {

    }

    template<typename... Args>
    static void Error(const std::string& message, Args&&... args)
    {
        std::cout << message << "\n";
        std::vector<std::string> _args{ args... };
        for(int i = 0; i < _args.size(); i++)
        {
            std::cout << _args[i] << "\n";
        }
    }
};

}

#define SADDLE_CORE_LOG_ERROR(message, ...) Saddle::Log::Error(message, ## __VA_ARGS__)