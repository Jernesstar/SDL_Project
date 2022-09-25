#pragma once

namespace Saddle {

class UUID {
public:
    const float ID;

public:
    // Note: Implement random number generation for this
    UUID() : ID(0) { }
    ~UUID() {};

    operator float() const { return ID; }
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