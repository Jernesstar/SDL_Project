#include "Sound.h"

#include "Audio.h"

namespace Saddle {

SoundComponent::SoundComponent(const std::string& file_path)
    : IComponent()
{
    std::string path = "Sandbox/";
    path.append(file_path);
    m_Sound = Mix_LoadWAV(path.c_str());
    m_Volume = AUDIO_MAX_VOLUME;
}

SoundComponent::~SoundComponent()
{
    if(m_Sound)
        Mix_FreeChunk(m_Sound);
}

void SoundComponent::OnUpdate() { }

Mix_Chunk* SoundComponent::GetSound()
{
    return m_Sound;
}

void SoundComponent::Play(int loops, int channel)
{
    // loops = 0: Play the sound once
    // channel = -1: First available sound channel
    Mix_PlayChannel(channel, m_Sound, loops);
}

void SoundComponent::SetVolume(Uint8 volume)
{
    m_Volume = volume;
    if(volume > AUDIO_MAX_VOLUME)
        m_Volume = AUDIO_MAX_VOLUME;
    else if(volume < AUDIO_MIN_VOLUME)
        m_Volume = AUDIO_MIN_VOLUME;
        
    Mix_VolumeChunk(m_Sound, m_Volume);
}

void SoundComponent::IncreaseVolume(Uint8 delta)
{
    SetVolume(m_Volume + delta);
}

void SoundComponent::DecreaseVolume(Uint8 delta)
{
    SetVolume(m_Volume - delta);
}

}