#include "MusicDemo.h"

MusicDemo::MusicDemo()
    : m_Window(Saddle::Application::Get().GetWindow()) { }

MusicDemo::~MusicDemo() { }

void MusicDemo::Run()
{   
    MusicBlock kick_drum("Sandbox/resources/Kick-Drum.wav", 50, 50);
    MusicBlock snare_drum("Sandbox/resources/Snare-Drum.wav", 50, 50);
}