#include "Utils.h"

#include <fstream>

#include <stb_image/stb_image.h>

#include "Saddle/Core/Assert.h"

namespace Saddle {

std::string Utils::ReadFile(const std::string& file_path)
{
    std::ifstream in(file_path, std::ios::in | std::ios::binary);

    SADDLE_CORE_ASSERT_ARGS(in, "Could not open file: %s", file_path)

    in.seekg(0, std::ios::end); // Sets the read position at the end of the file;

    // Gets current read position. Since read position is at the end of the file
    // this operation returns the size of the file
    size_t size = in.tellg();

    SADDLE_CORE_ASSERT(size != -1, "Could not read from file: " + file_path);

    std::string result;
    result.resize(size); // Resize the resulting string
    in.seekg(0, std::ios::beg); // Set the read position to the beginning of the file
    in.read(result.data(), size); // Read the entire file and output the contents to the string

    return result;
}

unsigned char* Utils::ReadImage(const std::string& path, int& width, int& height,
    int& bits_per_pixel, int desired_channels, bool flip)
{
    stbi_set_flip_vertically_on_load((int)flip);
    unsigned char* pixel_data = stbi_load(path.c_str(), &width, &height, &bits_per_pixel, desired_channels);
    SADDLE_CORE_ASSERT(pixel_data);

    return pixel_data;
}

unsigned char* Utils::ReadImage(const std::string& path, int& width, int& height, int desired_channels, bool flip)
{
    int bits_per_pixel;
    return Utils::ReadImage(path, width, height, bits_per_pixel, desired_channels, flip);
}

unsigned char* Utils::ReadImage(const std::string& path, int desired_channels, bool flip)
{
    int width, height, bits_per_pixel;
    return Utils::ReadImage(path, width, height, bits_per_pixel, desired_channels, flip);
}

}