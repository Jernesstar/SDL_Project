#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

namespace Saddle {

class Sound {

public:
    Sound(const std::string& file_path);
    ~Sound();
    void Play(int channel = -1, int loops = 0);

private:
    Mix_Chunk* sound;
};

}