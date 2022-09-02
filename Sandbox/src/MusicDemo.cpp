#include "MusicDemo.h"

#include <Saddle/Core/Input.h>
#include <Saddle/Scene/Scene.h>
#include <SDL/Image.h>

MusicDemo::MusicDemo()
    : m_Scene() { }

MusicDemo::~MusicDemo() { }

void MusicDemo::Run()
{
    Entity background;
    MusicBlock kick_drum("Sandbox/assets/sounds/Kick-Drum.wav", 70.0f, 70.0f);
    MusicBlock snare_drum("Sandbox/assets/sounds/Snare-Drum.wav", 70.0f, 70.0f);
    
    auto& component1 = background.AddComponent<TextureComponent>();
    auto& component2 = kick_drum.GetComponent<TextureComponent>();
    auto& component3 = snare_drum.GetComponent<TextureComponent>();

    int w = Application::Get().GetWindow().Width;
    int h = Application::Get().GetWindow().Height;
    component1.Texture = Image::Load("Sandbox/assets/graphics/start_bg.png", w, h);
    component2.Texture = Image::Load("Sandbox/assets/graphics/kick_drum.png", 70.0f, 70.0f);
    component3.Texture = Image::Load("Sandbox/assets/graphics/snare_drum.jpg", 70.0f, 70.0f);

    background.AddComponent<EventListenerComponent>()
    .OnWindowResized = [&background](WindowResizedEvent& event) {
        auto& texture = background.GetComponent<TextureComponent>();
        texture.Texture.Width = event.Width;
        texture.Texture.Height = event.Height;
    };

    m_Scene.AddEntity(background);
    m_Scene.AddEntity(kick_drum);
    m_Scene.AddEntity(snare_drum);

    bool running = true;
    while(running)
    {
        if(Input::KeyPressed(Key::Escape)) running = false;

        EventSystem::PollEvents();

        m_Scene.OnSceneRender();
    }
}