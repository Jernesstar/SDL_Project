#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

class Music {

public:
    Mix_Chunk* music;

public:
    Music(std::string* file_path);
    ~Music();

    void Play();
};