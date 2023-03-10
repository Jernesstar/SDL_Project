#pragma once

#include <random>

namespace Saddle {

class Random {
public:
    static int32_t RantInt();
    static int32_t RantInt(int32_t low, int32_t high);

private:
    static std::mt19937 s_RNG;
}

}