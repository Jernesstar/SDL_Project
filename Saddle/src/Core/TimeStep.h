#pragma once

#include <chrono>

namespace Saddle {

class TimeStep {
public:
    TimeStep(float time = 0.0f) : m_Time(time) { }

    operator float() const { return m_Time; }

    static float GetTime()
    {
        // Note: Implement getting the current time
        return 0;
    }

private:
    float m_Time;
};

}