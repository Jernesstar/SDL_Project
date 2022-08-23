#pragma once

#include <SDL.h>

namespace Saddle {

class TimeStep {
public:
    TimeStep(float time = 0.0f) : m_Time(time) { }

    operator float() const { return m_Time; }

    static float GetTime()
    {
        return (float)SDL_GetTicks();
    }

private:
    float m_Time;
};

}