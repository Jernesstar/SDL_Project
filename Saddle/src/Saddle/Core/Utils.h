#pragma once

#include <string>

namespace Saddle {

namespace Utils {
    std::string ReadFile(const std::string& file_path);

    unsigned char* LoadImage(const std::string& path, int& width, int& height,
        int& bits_per_pixel, int desired_channels = 4, bool flip = 0);

    unsigned char* LoadImage(const std::string& path, int desired_channels = 4, bool flip = 0);
};

}