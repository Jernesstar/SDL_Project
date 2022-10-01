#pragma once

#include <cstdlib>
#include <time.h>

namespace Saddle {

class UUID {
public:
    UUID() { srand(time(nullptr)); m_UUID = rand(); }
    UUID(uint64_t uuid) : m_UUID(uuid) { }

    operator uint64_t() const { return m_UUID; }

private: 
    uint64_t m_UUID;
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