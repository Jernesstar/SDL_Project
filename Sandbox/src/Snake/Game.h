#pragma once

#include "GameModes.h"

using namespace Saddle;

class Game : public Application {
public:
    Game();
    ~Game() = default;

    void OnUpdate(TimeStep ts) override;

private:
    GameMode* m_GameMode;
};