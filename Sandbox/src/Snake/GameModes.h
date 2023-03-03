#pragma once

#include <Saddle/Renderer/OrthographicCamera.h>

#include "Sprites.h"
#include "Input.h"

class GameMode {
protected:
    uint32_t BlockSize;
    Snake* Player1;
    Snake* Player2;

    OrthographicCamera Camera;

public:
    GameMode() : Camera(0.0f, 0.0f, 0.0f, 0.0f) { }

    virtual void Update(TimeStep ts) = 0;
    virtual void Run() = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, uint32_t block_size);

    void Update(TimeStep ts) override { };
    void Run() override;
};