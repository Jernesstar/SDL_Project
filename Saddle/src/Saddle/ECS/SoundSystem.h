// #pragma once

// #include "Entity.h"

// namespace Saddle {

// struct SoundSystemDependencies {
//     SoundComponent* sound_component;
// };

// class SoundSystem {
// public:
//     // loops = 0: Play the sound once
//     // channel = -1: First available sound channel
//     static void PlaySound(Entity& entity, int loops = 0, int channel = -1);
//     static void SetSoundVolume(Entity& entity, Uint8 volume);
//     static void IncreaseVolume(Entity& entity, Uint8 delta);
//     static void DecreaseVolume(Entity& entity, Uint8 delta);

//     static bool HasDependencies(Entity& entity)
//     {
//         return entity.HasComponent<SoundComponent>();
//     }

// private:
//     SoundSystem() = delete;
//     ~SoundSystem() = delete;

//     static SoundSystemDependencies GetDependencies(Entity& entity)
//     {
//         return { &entity.GetComponent<SoundComponent>() };
//     }
// };

// }