#include "Sound.h"

Sound::Sound(const std::string& file_path)
{
    memset(sound, 0, sizeof(Mix_Chunk*));
    sound = Mix_LoadWAV(file_path.c_str());
}

Sound::~Sound()
{
    if(sound)
        Mix_FreeChunk(sound);
}

void Sound::Play(int channel = -1, int loops = 0)
{
    // channel = -1: First available sound channel
    // loops = 0: Play the sound once
    Mix_PlayChannel(channel, sound, loops);
}