#pragma once

#include "IComponent.h"

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

namespace Saddle {

class SoundComponent : public IComponent {

public:
    SoundComponent(const std::string& file_path);
    ~SoundComponent();

    Mix_Chunk* GetSound();

    void OnUpdate() override;
    void Play(int loops = 0, int channel = -1);

    void SetVolume(Uint8 volume);
    void IncreaseVolume(Uint8 delta);
    void DecreaseVolume(Uint8 delta);

private:
    Mix_Chunk* m_Sound;
    Uint8 m_Volume;
};

}