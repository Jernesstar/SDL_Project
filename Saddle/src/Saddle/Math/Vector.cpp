#include "Vector.h"

#include <cmath>

namespace Saddle {

// Vector2D math operators

float operator *(const Saddle::Vector2D& vec1, const Vector2D& vec2) { return (vec1.x * vec2.x) + (vec1.y * vec2.y); }
float operator /(const Vector2D& vec1, const Vector2D& vec2) { return (vec1.x / vec2.x) + (vec1.y / vec2.y); }

Vector2D operator +(const Vector2D& vec1, const Vector2D& vec2) { return { vec1.x + vec2.x, vec1.y + vec2.y }; }
Vector2D operator -(const Vector2D& vec1, const Vector2D& vec2) { return { vec1.x - vec2.x, vec1.y - vec2.y }; }
Vector2D operator *(const Vector2D& vec, float scalar) { return {vec.x * scalar, vec.y * scalar}; }
Vector2D operator /(const Vector2D& vec, float scalar) { return {vec.x / scalar, vec.y / scalar}; }

// Vector3D math operators

float operator *(const Vector3D& vec1, const Vector3D& vec2) { return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);  }
float operator /(const Vector3D& vec1, const Vector3D& vec2) { return (vec1.x / vec2.x) + (vec1.y / vec2.y) + (vec1.z / vec2.z);  }

Vector3D operator +(const Vector3D& vec1, const Vector3D& vec2) { return { vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z }; }
Vector3D operator -(const Vector3D& vec1, const Vector3D& vec2) { return { vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z }; }
Vector3D operator *(const Vector3D& vec, float scalar) { return { vec.x * scalar, vec.y * scalar, vec.z * scalar }; }
Vector3D operator /(const Vector3D& vec, float scalar) { return { vec.x / scalar, vec.y / scalar, vec.z / scalar }; }

// Assigment operators

// Vector2D

void operator +=(Vector2D& vec1, const Vector2D& vec2) { vec1 = vec1 + vec2; }
void operator -=(Vector2D& vec1, const Vector2D& vec2) { vec1 = vec1 - vec2; }
void operator *=(Vector2D& vec1, float scalar) { vec1 = vec1 * scalar; }
void operator /=(Vector2D& vec1, float scalar) { vec1 = vec1 / scalar; }

// Vector3D

void operator +=(Vector3D& vec1, const Vector3D& vec2) { vec1 = vec1 + vec2; }
void operator -=(Vector3D& vec1, const Vector3D& vec2) { vec1 = vec1 - vec2; }
void operator *=(Vector3D& vec1, float scalar) { vec1 = vec1 * scalar; }
void operator /=(Vector3D& vec1, float scalar) { vec1 = vec1 / scalar; }

// Functions

// ||a|| = sqrt(a.x^2 + a.y^2) => ||a|| = sqrt(a · a)
// ||a|| = sqrt(a.x^2 + a.y^2 + a.z^2) => ||a|| = sqrt(a · a)
float Magnitude(const Vector2D& vec) { return sqrtf(vec * vec); }
float Magnitude(const Vector3D& vec) { return sqrtf(vec * vec); }

// If ϴ is angle between vectors a and b, then
// ϴ = arccos((a · b) / ||a|| · ||b||) 
float AngleBetweenVectors(const Vector2D& vec1, const Vector2D& vec2) { return std::acos((vec1 * vec2) / (Magnitude(vec1) * Magnitude(vec2))); }
float AngleBetweenVectors(const Vector3D& vec1, const Vector3D& vec2) { return std::acos((vec1 * vec2) / (Magnitude(vec1) * Magnitude(vec2))); }

// a × b
Vector3D CrossProduct(const Vector3D& vec1, const Vector3D& vec2)
{
    Vector3D î = { 1, 0, 0 };
    Vector3D ĵ = { 0, 1, 0 };
    Vector3D k̂ = { 0, 0, 1 };

    return { Magnitude(vec1) * Magnitude(vec2) * AngleBetweenVectors(vec1, vec2) * k̂ };
}

// Debugging
std::ostream& operator <<(std::ostream& os, const Vector2D& vec3) { return os << "{ " << vec3.x << ", " << vec3.y << " }"; }
std::ostream& operator <<(std::ostream& os, const Vector3D& vec3) { return os << "{ " << vec3.x << ", " << vec3.y << ", " << vec3.z << " }"; }

}