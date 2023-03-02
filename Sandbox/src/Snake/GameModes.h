#pragma once

#include <Saddle/Renderer/OrthographicCamera.h>

#include "Sprites.h"
#include "Input.h"

class GameMode {
protected:
    uint32_t BlockSize;
    Snake* Player1;
    Snake* Player2;
    Scene* Scene;

    OrthographicCamera Camera;

public:
    GameMode() : Camera(0.0f, 0.0f, 0.0f, 0.0f) { Scene = new Saddle::Scene(); }

    virtual void Update(TimeStep ts)
    {
        Player1->Update(ts);
        Player2->Update(ts);
    }

    virtual void Run() = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, uint32_t block_size);

    void Run() override;
};