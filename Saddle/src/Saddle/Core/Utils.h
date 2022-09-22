#pragma once

#include <string>

namespace Saddle {

class Utils {
public:
    static std::string LoadFile(const std::string& file_path);

private:
    Utils() = delete;
    ~Utils() = delete;
};

}