#pragma once

#include <iostream>
#include <unordered_map>

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
    static const Uint8 MAX_VOLUME = 128;
    static const Uint8 MIN_VOLUME = 0;

public:
    Sound(const std::string& file_path);
    ~Sound();

    Mix_Chunk* GetSound();

    void Play(int loops = 0, int channel = -1);

    void SetVolume(Uint8 volume);
    void IncreaseVolume(Uint8 delta);
    void DecreaseVolume(Uint8 delta);

    static void SetChannelVolume(int channel, Uint8 volume);
    static void IncreaseChannelVolume(int channel, Uint8 delta);
    static void DecreaseChannelVolume(int channel, Uint8 delta);

private:
    Mix_Chunk* m_Sound;
    Uint8 m_Volume;

    inline static std::unordered_map<int, Uint8> m_Channels;
};

}