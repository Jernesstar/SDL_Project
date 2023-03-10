#pragma once

#include "Saddle/Core/Random.h"

namespace Saddle {

class UUID {
public:
    UUID() : m_ID(Random::RandInt()) { }
    UUID(uint64_t uuid) : m_ID(uuid) { }

    operator uint64_t() const { return m_ID; }

private:
    uint64_t m_ID;
};

}

namespace std {

template<typename T>
struct hash;

template<>
struct hash<Saddle::UUID>
{
    std::size_t operator()(const Saddle::UUID& uuid) const
    {
        return (uint64_t)uuid;
    }
};

}