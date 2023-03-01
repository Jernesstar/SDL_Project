#pragma once

#include "Sprites.h"
#include "Input.h"

class GameMode {
public:
    Snake* Player1;
    Snake* Player2;
    Scene Scene;

public:
    GameMode() = default;
    
    virtual void Update(TimeStep ts)
    {
        Player1->Update(ts);
        Player2->Update(ts);
    }

    virtual void Run() = 0;
};

class OnePlayerClassicSnake : public GameMode {
public:
    OnePlayerClassicSnake(const std::string name, uint32_t block_size)
    {
        Player1 = new Snake(GameMode::Scene, InputMode::Keys, block_size, name);
        Player2 = nullptr;
    }

    void Run() override
    {
        
    }
};