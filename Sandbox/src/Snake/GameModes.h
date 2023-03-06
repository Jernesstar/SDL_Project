#pragma once

#include <memory>

#include <Saddle/Renderer/OrthographicCamera.h>

#include "Sprites.h"
#include "Input.h"

class GameMode {
protected:
    float BlockSize;
    std::unique_ptr<Snake> Player1;

    OrthographicCamera Camera;

public:
    GameMode() : Camera(0.0f, 0.0f, 0.0f, 0.0f) { }
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