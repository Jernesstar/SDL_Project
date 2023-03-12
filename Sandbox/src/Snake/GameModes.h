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

public:
    GameMode() = default;
    ~GameMode() = default;

    virtual void Run() = 0;
    virtual void Render(TimeStep ts) = 0;
    virtual void CheckGameOver(glm::vec2 bound) = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, float block_size);

    void Run() override;
    void Render(TimeStep ts) override;
    void CheckGameOver(glm::vec2 bound) override;
};