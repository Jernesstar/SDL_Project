#pragma once

#include "GameModes.h"

#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Text/Text.h>

using namespace Saddle;

class Game : public Application {
public:
    Game(uint32_t width, uint32_t height);
    ~Game() = default;

    void OnUpdate(TimeStep ts) override;
    void ShowGameOver();

private:
    GameMode* m_GameMode;

    OrthographicCamera m_Camera{ 0.0f, 0.0f, 0.0f, 0.0f };
    Font m_Font{ "Sandbox/assets/fonts/pixel_font.ttf", 0, 56 };
    Text m_GameOverText{ "Game Over", m_Font, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f } };
    Text m_ReturnText{ "Press return to play again", m_Font, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f } };
};