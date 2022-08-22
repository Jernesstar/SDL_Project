#include "MusicDemo.h"

#include <Saddle/Core/Input.h>
#include <Saddle/Scene/Scene.h>
#include <Saddle/Core/Image.h>

MusicDemo::MusicDemo()
    : m_Scene() { }

MusicDemo::~MusicDemo() { }

void MusicDemo::Run()
{   
    MusicBlock kick_drum("Sandbox/assets/sounds/Kick-Drum.wav", 70, 70);
    MusicBlock snare_drum("Sandbox/assets/sounds/Snare-Drum.wav", 70, 70);
    kick_drum.AddComponent<Coordinate2DComponent>(100, 100);
    snare_drum.AddComponent<Coordinate2DComponent>(240, 100);

    Entity background;
    background.AddComponent<Coordinate2DComponent>(0,0);
    auto& component = background.AddComponent<TextureComponent>();
    component.Texture = Image::Load("Sandbox/assets/graphics/start_bg.png");
    component.Texture.Width = 100;
    component.Texture.Height = 100;

    m_Scene.AddEntity(background);
    m_Scene.AddEntity(kick_drum);
    m_Scene.AddEntity(snare_drum);

    bool running = true;
    while(running)
    {
        if(Input::IsKeyPressed(Key::Escape)) running = false;
        
        EventDispatcher::DispatchEvents();
        
        m_Scene.OnSceneRender();
    }
}