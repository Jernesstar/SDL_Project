#pragma once

#include <Saddle/Renderer/OrthographicCamera.h>

#include "GameModes.h"
#include "Sprites.h"

using namespace Saddle;

class Game : public Application {
public:
    Game();
    ~Game() = default;

    void OnUpdate(TimeStep ts) override;

private:
    OrthographicCamera camera{ 0.0f, 0.0f, -1.0f, 1.0f };

    GameMode* m_GameMode;
};