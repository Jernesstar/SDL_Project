#pragma once

#include <iostream>
#include <cmath>

namespace Saddle {

struct Vector2D {
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) { }

    void operator +=(const Vector2D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y;
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y;
    }
};

struct Vector3D {
    float x, y, z;

    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }

    void operator +=(const Vector3D& other)
    {
        auto vec = *this + other;
        x = vec.x; y = vec.y; z = vec.z;
    }

    void operator *=(float scalar)
    {
        auto vec = *this * scalar;
        x = vec.x; y = vec.y; z = vec.z;
    }
};

// Vector2D operators

inline float operator *(const Vector2D& vec, const Vector2D& vec2) { return (vec.x * vec2.x) + (vec.y * vec2.y); }
inline float operator /(const Vector2D& vec, const Vector2D& vec2) { return (vec.x / vec2.x) + (vec.y / vec2.y); }

inline Vector2D operator +(const Vector2D& vec, const Vector2D& vec2) { return {vec.x + vec2.x, vec.y + vec2.y}; }
inline Vector2D operator -(const Vector2D& vec, const Vector2D& vec2) { return {vec.x - vec2.x, vec.y - vec2.y}; }
inline Vector2D operator *(const Vector2D& vec, float scalar) { return {vec.x * scalar, vec.y * scalar}; }
inline Vector2D operator /(const Vector2D& vec, float scalar) { return {vec.x / scalar, vec.y / scalar}; }

// Vector3D operators

inline float operator *(const Vector3D& vec, const Vector3D& vec2) { return (vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z);  }
inline float operator /(const Vector3D& vec, const Vector3D& vec2) { return (vec.x / vec2.x) + (vec.y / vec2.y) + (vec.z / vec2.z);  }

inline Vector3D operator +(const Vector3D& vec, const Vector3D& vec2) { return {vec.x + vec2.x, vec.y + vec2.y, vec.z + vec2.z}; }
inline Vector3D operator -(const Vector3D& vec, const Vector3D& vec2) { return {vec.x - vec2.x, vec.y - vec2.y, vec.z - vec2.z}; }
inline Vector3D operator *(const Vector3D& vec, float scalar) { return {vec.x * scalar, vec.y * scalar, vec.z * scalar}; }
inline Vector3D operator /(const Vector3D& vec, float scalar) { return {vec.x / scalar, vec.y / scalar, vec.z / scalar}; }

inline float Magnitude(const Vector2D& vec) { return sqrtf(vec * vec); }
inline float Magnitude(const Vector3D& vec) { return sqrtf(vec * vec); }

// Note: Implement these methods
inline Vector2D CrossProduct(const Vector2D& vec, const Vector2D& vec2) { return {}; }
inline Vector3D CrossProduct(const Vector3D& vec, const Vector3D& vec2) { return {}; }

// For Debugging
inline std::ostream& operator <<(std::ostream& os, const Vector2D& vec3)
{
    return os << "{ " << vec3.x << ", " << vec3.y << " }";
}

inline std::ostream& operator <<(std::ostream& os, const Vector3D& vec3)
{
    return os << "{ " << vec3.x << ", " << vec3.y << ", " << vec3.z << " }";
}

}