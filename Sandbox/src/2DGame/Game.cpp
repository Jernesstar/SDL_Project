#include "Game.h"

#include <Saddle/Events/EventSystem.h>
#include <Saddle/Core/Input.h>

#include <Saddle/Renderer/Renderer2D.h>

Game::Game()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event) {
        if(event.Key == Key::Escape)
            Application::Close();
    });

    EventSystem::RegisterEventListener<ApplicationUpdatedEvent>(
    [this](const ApplicationUpdatedEvent& event) {
        this->OnUpdate(event.DeltaTime);
    });

    Kick_Drum.AddComponent<TextureComponent>("Sandbox/assets/images/kick_drum.png");
    Snare_Drum.AddComponent<TextureComponent>("Sandbox/assets/images/snare_drum.jpg");

    Kick_Drum.AddComponent<TransformComponent>(
        TransformComponent
        {
            glm::vec3{ 0.f, 0.f, 0.f }, 
            glm::vec3{ 0.0f, 0.0f, 0.0f }, 
            glm::vec3{ 0.25f, 0.25f, 0.25f }
        }
    );

    Snare_Drum.AddComponent<TransformComponent>(
        TransformComponent
        {
            glm::vec3{ -0.5f, 0.f, 0.f }, 
            glm::vec3{ 0.0f, 0.0f, 0.0f }, 
            glm::vec3{ 0.25f, 0.25f, 0.25f }
        }
    );
}

void Game::OnUpdate(TimeStep ts)
{
    auto& translation1 = Kick_Drum.GetComponent<TransformComponent>().Translation;
    auto& translation2 = Snare_Drum.GetComponent<TransformComponent>().Translation;
    float speed = 0.0025f;

    if(Input::KeyPressed(Key::Left))
        translation1.x -= speed * ts;
    if(Input::KeyPressed(Key::Right))
        translation1.x += speed * ts;
    if(Input::KeyPressed(Key::Up))
        translation1.y += speed * ts;
    if(Input::KeyPressed(Key::Down))
        translation1.y -= speed * ts;

    if(Input::KeyPressed(Key::A))
        translation2.x -= speed * ts;
    if(Input::KeyPressed(Key::D))
        translation2.x += speed * ts;
    if(Input::KeyPressed(Key::W))
        translation2.y += speed * ts;
    if(Input::KeyPressed(Key::S))
        translation2.y -= speed * ts;

    Renderer::Clear({ 1.0f, 0.0f, 0.0f, 1.0f });

    Renderer2D::BeginScene(camera);

    Renderer2D::DrawEntity(Kick_Drum);
    Renderer2D::DrawEntity(Snare_Drum);

    Renderer2D::EndScene();
}
