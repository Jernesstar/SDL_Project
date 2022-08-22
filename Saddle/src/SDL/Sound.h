#pragma once

#include <iostream>

#include "Audio.h"

namespace Saddle {

class Sound {
public:
    const std::string Path;

public:
    Sound(const std::string& path);
    ~Sound();

    // loops = 0: Play the sound once
    // channel = -1: First available sound channel
    void Play(int loops = 0, int channel = -1);

    void SetVolume(Uint8 volume);
    void IncreaseVolume(Uint8 delta);
    void DecreaseVolume(Uint8 delta);

private:
    Mix_Chunk* m_Sound;
    Uint8 m_Volume;

    friend class SoundSystem;
};

}