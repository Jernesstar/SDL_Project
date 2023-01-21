// #include "SoundSystem.h"
// #include "Components.h"

// namespace Saddle {

// void SoundSystem::PlaySound(Entity& entity, int loops, int channel)
// {
//     SADDLE_CORE_ASSERT(HasDependencies(entity));
//     auto [sound_component] = GetDependencies(entity);
//     sound_component->Sound.Play(loops, channel);
// }

// void SoundSystem::SetSoundVolume(Entity& entity, Uint8 volume)
// {
//     SADDLE_CORE_ASSERT(HasDependencies(entity));
//     auto [sound_component] = GetDependencies(entity);
//     sound_component->Sound.SetVolume(volume);
// }

// void SoundSystem::IncreaseVolume(Entity& entity, Uint8 delta)
// { 
//     SADDLE_CORE_ASSERT(HasDependencies(entity));
//     auto [sound_component] = GetDependencies(entity);
//     sound_component->Sound.IncreaseVolume(delta); 
// }

// void SoundSystem::DecreaseVolume(Entity& entity, Uint8 delta)
// { 
//     SADDLE_CORE_ASSERT(HasDependencies(entity));
//     auto [sound_component] = GetDependencies(entity);
//     sound_component->Sound.IncreaseVolume(delta); 
// }

// }