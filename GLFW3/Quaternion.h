#pragma once
#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "XVector.h"

struct Quaternion
{
	float x, y, z, w;

	explicit Quaternion(float _x=0.f, float _y=0.f, float _z=0.f, float _w=0.f);

	void normalize();

	Quaternion conjugate();  
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const Vector3f& v);

#endif