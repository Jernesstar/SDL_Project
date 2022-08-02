#include "Sound.h"

namespace Saddle {

Sound::Sound(const std::string& file_path)
{
    std::string path = "Sandbox/";
    path.append(file_path);
    m_Sound = Mix_LoadWAV(path.c_str());
    m_Volume = MAX_VOLUME;
}

Sound::~Sound()
{
    if(m_Sound)
        Mix_FreeChunk(m_Sound);
}

Mix_Chunk* Sound::GetSound()
{
    return m_Sound;
}

void Sound::Play(int loops, int channel)
{
    // loops = 0: Play the sound once
    // channel = -1: First available sound channel
    Mix_PlayChannel(channel, m_Sound, loops);
}

void Sound::SetVolume(Uint8 volume)
{
    m_Volume = volume;
    if(volume > MAX_VOLUME)
        m_Volume = MAX_VOLUME;
    else if(volume < MIN_VOLUME)
        m_Volume = MIN_VOLUME;
        
    Mix_VolumeChunk(m_Sound, m_Volume);
}

void Sound::IncreaseVolume(Uint8 delta)
{
    SetVolume(m_Volume + delta);
}

void Sound::DecreaseVolume(Uint8 delta)
{
    SetVolume(m_Volume - delta);
}

void Sound::SetChannelVolume(int channel, Uint8 volume)
{
    m_Channels[channel] = volume;
    if(volume > MAX_VOLUME)
        m_Channels[channel] = MAX_VOLUME;
    else if(volume < MIN_VOLUME)
        m_Channels[channel] = MIN_VOLUME;

    Mix_Volume(channel, m_Channels[channel]);
}

void Sound::IncreaseChannelVolume(int channel, Uint8 delta)
{
    if(m_Channels.find(channel) == m_Channels.end()) // Channel is not yet in the map
        m_Channels[channel] = MAX_VOLUME;

    SetChannelVolume(channel, m_Channels[channel] + delta);
}

void Sound::DecreaseChannelVolume(int channel, Uint8 delta)
{
    if(m_Channels.find(channel) == m_Channels.end()) // Channel is not yet in the map
        m_Channels[channel] = MAX_VOLUME;

    SetChannelVolume(channel, m_Channels[channel] - delta);
}

}