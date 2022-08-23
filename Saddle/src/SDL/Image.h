#include <iostream>

#include "SDL/Texture2D.h"

namespace Saddle {

class Image {
public:
    static void Init(Uint32 init_flags);
    static void Shutdown();

    static Texture2D Load(const std::string& file_path);
    static Texture2D Load(const std::string& file_path, int width, int height);

private:
    Image() = delete;
    ~Image() = delete;
};

}