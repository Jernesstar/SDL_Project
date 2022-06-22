#pragma once
class Log {
public:
    static void Error(std::string message);
    static void Warning(std::string message);
    static void Info(std::string message);
};