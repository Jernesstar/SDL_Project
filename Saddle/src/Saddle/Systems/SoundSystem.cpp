#include "SoundSystem.h"

#include "Saddle/Scene/Components.h"

namespace Saddle {

void SoundSystem::PlaySound(Entity& entity, int loops, int channel)
{
    SoundComponent& sound_component = entity.GetComponent<SoundComponent>();
    Mix_PlayChannel(channel, sound_component.Sound.m_Sound, loops);
}

void SoundSystem::SetSoundVolume(Entity& entity, Uint8 volume)
{
    Sound& sound = entity.GetComponent<SoundComponent>().Sound;
    sound.m_Volume = volume;
    if(volume > AUDIO_MAX_VOLUME)
        sound.m_Volume = AUDIO_MAX_VOLUME;
    else if(volume < AUDIO_MIN_VOLUME)
        sound.m_Volume = AUDIO_MIN_VOLUME;
    
    Mix_VolumeChunk(sound.m_Sound, sound.m_Volume);
}

void SoundSystem::IncreaseVolume(Entity& entity, Uint8 delta)
{ 
    SetSoundVolume(entity, entity.GetComponent<SoundComponent>().Sound.m_Volume + delta); 
}

void SoundSystem::DecreaseVolume(Entity& entity, Uint8 delta)
{ 
    SetSoundVolume(entity, entity.GetComponent<SoundComponent>().Sound.m_Volume - delta); 
}

}