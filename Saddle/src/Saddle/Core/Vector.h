#pragma once

#include <iostream>

namespace Saddle {

struct Vector2D {
    float x, y;

    Vector2D() : x(0), y(0) { }
    Vector2D(float x, float y) : x(x), y(y) { }

    Vector2D(const Vector2D& other) = default;
    Vector2D(Vector2D&& other) = default;
    Vector2D& operator =(Vector2D&& other) = default;

    Vector2D operator *(float scalar)
    {
        return {x * scalar, y * scalar};
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y;
    }

    Vector2D operator +(const Vector2D& other)
    {
        return {x + other.x, y + other.y};
    }

    void operator +=(const Vector2D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y;
    }
};

inline std::ostream& operator <<(std::ostream& os, const Vector2D& vec2)
{
    return os << "{ " << vec2.x << ", " << vec2.y << " }";
}

struct Vector3D {
    float x, y, z;

    Vector3D() : x(0), y(0), z(0) { }
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) { }
    Vector3D(const Vector3D& other) = default;
    Vector3D(Vector3D&& other) = default;
    Vector3D& operator=(Vector3D&& other) = default;
    
    Vector3D operator *(float scalar)
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y; z = vec.z;
    }

    Vector3D operator +(const Vector3D& other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    void operator +=(const Vector3D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y; z = vec.z;
    }
};

inline std::ostream& operator <<(std::ostream& os, const Vector3D& vec3)
{
    return os << "{ " << vec3.x << ", " << vec3.y << ", " << vec3.z << " }";
}

}