#include <iostream>
#include "Log.h"

void Log::Error(std::string message)
{
    std::cout << "[Error]: " << message << "\n";
}
void Log::Warning(std::string message)
{
    std::cout << "[Warning]: " << message << "\n";
}
void Log::Info(std::string message)
{
    std::cout << "[Info]: " << message << "\n";
}