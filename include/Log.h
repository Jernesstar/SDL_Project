#pragma once

#include <iostream>

class Log {
    
public:
    static void Info(const std::string& message, const char* file, const char* function, int line);
    static void Info(const std::string& message);

    static void Warning(const std::string& message, const char* file, const char* function, int line);
    static void Warning(const std::string& message);

    static void Error(const std::string& message, const char* file, const char* function, int line);
    static void Error(const std::string& message);
};