#pragma once

#include <iostream>
#include <cmath>

namespace Saddle {

struct Vector2D {
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) { }

    Vector2D operator +(const Vector2D& other)
    {
        return {x + other.x, y + other.y};
    }

    void operator +=(const Vector2D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y;
    }

    // Subtraction here

    Vector2D operator *(float scalar)
    {
        return {x * scalar, y * scalar};
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y;
    }

    float operator *(const Vector2D& other)
    {
        return (x * other.x) + (y * other.y); 
    }

    float Magnitude()
    {
        return sqrtf((*this) * (*this));
    }
};

inline std::ostream& operator <<(std::ostream& os, const Vector2D& vec2)
{
    return os << "{ " << vec2.x << ", " << vec2.y << " }";
}

struct Vector3D {
    float x, y, z;

    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }

    Vector3D operator +(const Vector3D& other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    void operator +=(const Vector3D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y; z = vec.z;
    }

    // Subtraction here

    Vector3D operator *(float scalar)
    {
        return {x * scalar, y * scalar, z * scalar};
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y; z = vec.z;
    }

    float operator *(const Vector3D& other)
    {
        return (x * other.x) + (y * other.y) + (z * other.x); 
    }

    float Magnitude()
    {
        return sqrtf((*this) * (*this));
    }
};

inline std::ostream& operator <<(std::ostream& os, const Vector3D& vec3)
{
    return os << "{ " << vec3.x << ", " << vec3.y << ", " << vec3.z << " }";
}

}