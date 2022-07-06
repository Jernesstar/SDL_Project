#include <iostream>

#include "Log.h"

void Log::Info(std::string message, const char* file, const char* function, int line)
{
    std::string info_message = "";
    info_message.append("In file: " + std::string(file) + ", ");
    info_message.append("function: " + std::string(function) + ", ");
    info_message.append("line: " + std::to_string(line) + "\n\t");
    info_message.append("[Info]: " + message);
    std::cout << info_message << "\n";
}

void Log::Info(std::string message)
{
    std::string info_message = "";
    info_message.append("[Info]: " + message);
    std::cout << info_message << "\n";
}

void Log::Warning(std::string message, const char* file, const char* function, int line)
{
    std::string warning_message = "";
    warning_message.append("In file: " + std::string(file) + ", ");
    warning_message.append("function: " + std::string(function) + ", ");
    warning_message.append("line: " + std::to_string(line) + "\n\t");
    warning_message.append("[Warning]: " + message);
    std::cout << warning_message << "\n";
}

void Log::Warning(std::string message)
{
    std::string warning_message = "";
    warning_message.append("[Warning]: " + message);
    std::cout << warning_message << "\n";
}

void Log::Error(std::string message, const char* file, const char* function, int line)
{
    std::string error_message = "";
    error_message.append("In file: " + std::string(file) + ", ");
    error_message.append("function: " + std::string(function) + ", ");
    error_message.append("line: " + std::to_string(line) + "\n\t");
    error_message.append("[Error]: " + message);
    std::cout << error_message << "\n";
}

void Log::Error(std::string message)
{
    std::string error_message = "";
    error_message.append("[Error]: " + message);
    std::cout << error_message << "\n";
}