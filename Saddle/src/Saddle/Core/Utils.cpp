#include "Utils.h"

#include <fstream>

#include "Saddle/Core/Assert.h"

namespace Saddle {

std::string Utils::LoadFile(const std::string& file_path)
{
    std::string result;
    std::ifstream in(file_path, std::ios::in | std::ios::binary);

    SADDLE_CORE_ASSERT(in, "Could not open file: " + file_path)

    in.seekg(0, std::ios::end); // Sets the read position at the end of the file;

    // Gets current read position, since read position is at the end of the file
    // this operation returns the size of the file
    size_t size = in.tellg();

    SADDLE_CORE_ASSERT(size != -1, "Could not read from file: " + file_path);

    result.resize(size); // Resize the resulting string
    in.seekg(0, std::ios::beg); // Set the read position to the beginning of the file
    in.read(result.data(), size); // Read the entire file and output the contents to the string

    return result;
}

}