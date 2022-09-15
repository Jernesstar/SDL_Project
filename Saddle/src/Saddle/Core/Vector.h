#pragma once

#include <iostream>

namespace Saddle {

struct Vector2D {
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) { }
};

struct Vector3D {
    float x, y, z;

    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }
};

// Vector2D math operators

float operator *(const Vector2D& vec1, const Vector2D& vec2);
float operator /(const Vector2D& vec1, const Vector2D& vec2);

Vector2D operator +(const Vector2D& vec1, const Vector2D& vec2);
Vector2D operator -(const Vector2D& vec1, const Vector2D& vec2);
Vector2D operator *(const Vector2D& vec, float scalar);
Vector2D operator /(const Vector2D& vec, float scalar);

// Vector3D math operators

float operator *(const Vector3D& vec1, const Vector3D& vec2);
float operator /(const Vector3D& vec1, const Vector3D& vec2);

Vector3D operator +(const Vector3D& vec1, const Vector3D& vec2);
Vector3D operator -(const Vector3D& vec1, const Vector3D& vec2);
Vector3D operator *(const Vector3D& vec, float scalar);
Vector3D operator /(const Vector3D& vec, float scalar);

// Assigment operators

// Vector2D
void operator +=(Vector2D& vec1, const Vector2D& vec2);
void operator -=(Vector2D& vec1, const Vector2D& vec2);
void operator *=(Vector2D& vec1, float scalar);
void operator /=(Vector2D& vec1, float scalar);

// Vector3D
void operator +=(Vector3D& vec1, const Vector3D& vec2);
void operator -=(Vector3D& vec1, const Vector3D& vec2);
void operator *=(Vector3D& vec1, float scalar);
void operator /=(Vector3D& vec1, float scalar);

// Functions

float Magnitude(const Vector2D& vec);
float Magnitude(const Vector3D& vec);

// Note: Implement these methods
Vector2D CrossProduct(const Vector2D& vec1, const Vector2D& vec2);
Vector3D CrossProduct(const Vector3D& vec1, const Vector3D& vec2);

// Debugging
std::ostream& operator <<(std::ostream& os, const Vector2D& vec3);
std::ostream& operator <<(std::ostream& os, const Vector3D& vec3);

}