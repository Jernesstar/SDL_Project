#pragma once

#include "Components.h"
#include "Entity.h"

namespace Saddle {

class SoundSystem {

public:
    static void PlaySound(Entity& entity, int loops = 0, int channel = -1)
    {
        SoundComponent& sound_component = entity.GetComponent<SoundComponent>();
        // loops = 0: Play the sound once
        // channel = -1: First available sound channel
        Mix_PlayChannel(channel, sound_component.Sound, loops);
    }

    static void SetSoundVolume(Entity& entity, Uint8 volume)
    {
        SoundComponent& sound_component = entity.GetComponent<SoundComponent>();
        sound_component.Volume = volume;
        if(volume > AUDIO_MAX_VOLUME)
            sound_component.Volume = AUDIO_MAX_VOLUME;
        else if(volume < AUDIO_MIN_VOLUME)
            sound_component.Volume = AUDIO_MIN_VOLUME;
        
        Mix_VolumeChunk(sound_component.Sound, sound_component.Volume);
    }

    static void IncreaseVolume(Entity& entity, Uint8 delta)
    { 
        SetSoundVolume(entity, entity.GetComponent<SoundComponent>().Volume + delta); 
    }

    static void DecreaseVolume(Entity& entity, Uint8 delta)
    { 
        SetSoundVolume(entity, entity.GetComponent<SoundComponent>().Volume - delta); 
    }
};

}