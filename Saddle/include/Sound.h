#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

namespace Saddle {

struct SoundSpecification {

    int Frequency, ChannelCount, ChunckSize;
    Uint16 Format;

    SoundSpecification(
        int frequency = MIX_DEFAULT_FREQUENCY, 
        Uint16 format = MIX_DEFAULT_FORMAT, 
        int channel_count = MIX_DEFAULT_CHANNELS, 
        int chunck_size = 1024
    ) : Frequency(frequency), Format(format),  ChannelCount(channel_count), ChunckSize(chunck_size) { }

};

class Sound {

public:
    Sound(const std::string& file_path);
    ~Sound();
    void Play(int loops = 0, int channel = -1);

private:
    Mix_Chunk* m_Sound;
};

}