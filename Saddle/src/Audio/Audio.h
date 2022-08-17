#pragma once

#include <unordered_map>

#include <SDL_mixer.h>

#define AUDIO_MAX_VOLUME 128
#define	AUDIO_MIN_VOLUME 0

struct AudioSpecification {

    int Frequency, ChannelCount, ChunckSize;
    Uint16 Format;

    AudioSpecification(
        int frequency = MIX_DEFAULT_FREQUENCY, 
        Uint16 format = MIX_DEFAULT_FORMAT, 
        int channel_count = MIX_DEFAULT_CHANNELS, 
        int chunck_size = 1024
    ) : Frequency(frequency), Format(format),  ChannelCount(channel_count), ChunckSize(chunck_size) { }

};

class Audio {

public:
    static void Init(AudioSpecification specs = AudioSpecification());
    static void Shutdown();

    static void SetChannelVolume(int channel, Uint8 volume);
    static void IncreaseChannelVolume(int channel, Uint8 delta);
    static void DecreaseChannelVolume(int channel, Uint8 delta);
    
private:
    inline static std::unordered_map<int, Uint8> m_Channels;

private:
    Audio() = delete;
    ~Audio() = delete;

};