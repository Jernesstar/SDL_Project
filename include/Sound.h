#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

class Sound {

public:
    Mix_Chunk* sound;

public:
    Sound(const std::string& file_path);
    ~Sound();

    void Play(int channel, int loops);
};