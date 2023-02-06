#pragma once

#include <cstdlib>
#include <time.h>

namespace Saddle {

class UUID {
public:
    UUID() { m_UUID = ++id; }
    UUID(uint64_t uuid) : m_UUID(uuid) { }

    operator uint64_t() const { return m_UUID; }

private:
    uint64_t m_UUID;

private:
    inline static uint64_t id = 0;
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