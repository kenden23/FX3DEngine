#pragma once
#ifndef _XVECTOR_H
#define _XVECTOR_H
#include <stdio.h>

struct Vector2i
{
    int x;
    int y;
};//===============================Vector2i

//=================================Vector2f
struct Vector2f
{
    float x;
    float y;

    explicit Vector2f(float x1 = 0.f, float y1 = 0.f) : x(x1), y(y1) {}
};//===========================Vector2f

struct Vector2d
{
    double x;
    double y;

    explicit Vector2d(double x1 = 0.0, double y1 = 0.0) : x(x1), y(y1) {}
};//===========================Vector2f

//=============================Vector3f
struct Vector3f
{
    float x;
    float y;
    float z;

    explicit Vector3f(float x1 = 0.f, float y1 = 0.f, float z1 = 0.f)
	    : x(x1), y(y1), z(z1) {}

    Vector3f& operator+=(const Vector3f& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }

    Vector3f& operator-=(const Vector3f& r)
    {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }

    Vector3f& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3f cross(const Vector3f& v) const;

    Vector3f& normalize();

    //axis can be any axis, not just x, y, z axis, meaning rotate around any axis
    void rotate(float angle, const Vector3f& axis);

    void print() const
    {
        printf("(%.02f, %.02f, %.02f", x, y, z);
    }
};

//============================================
inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
    return Vector3f(l.x + r.x, l.y + r.y, l.z + r.z);
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
    return Vector3f(l.x - r.x, l.y - r.y, l.z - r.z);
}

inline Vector3f operator*(const Vector3f& l, float f)
{
    return Vector3f(l.x * f, l.y * f, l.z * f);
}

#endif