#include "MusicDemo.h"

MusicDemo::MusicDemo()
    : m_Window(Saddle::Application::Get().GetWindow()) { }

MusicDemo::~MusicDemo() { }

void MusicDemo::Run()
{   
    MusicBlock kick_drum("Sandbox/asstes/Kick-Drum.wav", 50, 50);
    MusicBlock snare_drum("Sandbox/assets/Snare-Drum.wav", 50, 50);
}