#pragma once
class Log {
public:
    static void Info(std::string message, const char* file, const char* function, int line);
    static void Warning(std::string message, const char* file, const char* function, int line);
    static void Error(std::string message, const char* file, const char* function, int line);
};