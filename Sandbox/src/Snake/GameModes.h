#pragma once

#include <memory>

#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Events/EventSystem.h>

#include "Sprites.h"

class GameMode {
public:
    float BlockSize;
    bool GameOver = false;

protected:
    std::unique_ptr<Snake> Player1;

    OrthographicCamera Camera;

public:
    GameMode() : Camera(0.0f, 0.0f, 0.0f, 0.0f) { }
    ~GameMode() = default;

    virtual void Update(TimeStep ts) = 0;
    virtual void Run() = 0;
    virtual void CheckGameOver() = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, float block_size);

    void Update(TimeStep ts) override;
    void Run() override;
    void CheckGameOver() override;
};