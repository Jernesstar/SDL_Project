#include "Sound.h"

namespace Saddle {

Sound::Sound(const std::string& file_path)
{
    m_Sound = Mix_LoadWAV(file_path.c_str());
}

Sound::~Sound()
{
    if(m_Sound)
        Mix_FreeChunk(m_Sound);
}

void Sound::Play(int channel, int loops)
{
    // channel = -1: First available sound channel
    // loops = 0: Play the sound once
    Mix_PlayChannel(channel, m_Sound, loops);
}

}