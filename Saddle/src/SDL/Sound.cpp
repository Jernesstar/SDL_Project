#include "Sound.h"

namespace Saddle {

Sound::Sound(const std::string& path) : Path(path) { m_Sound = Mix_LoadWAV(path.c_str()); }
Sound::~Sound() { if(m_Sound) Mix_FreeChunk(m_Sound); }

void Sound::Play(int loops, int channel) { Mix_PlayChannel(channel, m_Sound, loops); }

void Sound::SetVolume(Uint8 volume)
{
    m_Volume = volume;
    if(volume > AUDIO_MAX_VOLUME)
        m_Volume = AUDIO_MAX_VOLUME;
    else if(volume < AUDIO_MIN_VOLUME)
        m_Volume = AUDIO_MIN_VOLUME;
    
    Mix_VolumeChunk(m_Sound, m_Volume);
}

void Sound::IncreaseVolume(Uint8 delta) { SetVolume(m_Volume + delta); }
void Sound::DecreaseVolume(Uint8 delta) { SetVolume(m_Volume - delta); }

}