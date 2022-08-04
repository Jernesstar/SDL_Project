#include "MusicDemo.h"

MusicDemo::MusicDemo()
    : m_Window(Saddle::Application::Get().GetWindow())
{
    
}

MusicDemo::~MusicDemo() { }

void MusicDemo::Run()
{   
    MusicBlock kick_drum("resources/Kick-Drum.wav", 50, 50);
    MusicBlock snare_drum("resources/Snare-Drum.wav", 50, 50);

    kick_drum.OnEventClick = [&kick_drum](SDL_Event& event) {
        kick_drum.Play();
    };
    kick_drum.Play();
}