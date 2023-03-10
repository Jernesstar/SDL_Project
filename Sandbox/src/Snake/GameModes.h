#pragma once

#include <memory>

#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Events/EventSystem.h>

#include "Sprites.h"

class GameMode {
protected:
    float BlockSize;
    OrthographicCamera Camera;

    std::unique_ptr<Snake> Player1;

public:
    GameMode() : Camera(0.0f, 0.0f, 0.0f, 0.0f)
    {
        EventSystem::RegisterEventListener<ApplicationUpdatedEvent> (
        [this](const ApplicationUpdatedEvent& event) {
            this->Update(event.DeltaTime);
        });
    }
    ~GameMode() = default;

    virtual void Update(TimeStep ts) = 0;
    virtual void Run() = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, float block_size);

    void Update(TimeStep ts) override;
    void Run() override;
};