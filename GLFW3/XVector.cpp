#include "XVector.h"
#include <math.h>
#include "XMath.h"
#include "Quaternion.h"

Vector3f Vector3f::cross(const Vector3f& v) const
{
	return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3f& Vector3f::normalize()
{
	const float Length = sqrtf(x * x + y * y + z * z);
	x /= Length;
	y /= Length;
	z /= Length;
	return *this;
}

void Vector3f::rotate(float angle, const Vector3f& axis)
{
	const float sinHalfAngle = sinf(XMUtil::toRadian(angle/2));
	const float cosHalfAngle = cosf(XMUtil::toRadian(angle/2));

	const float rx = axis.x * sinHalfAngle;
	const float ry = axis.y * sinHalfAngle;
	const float rz = axis.z * sinHalfAngle;
	const float rw = cosHalfAngle;
	Quaternion rotationQ(rx, ry, rz, rw);

	Quaternion conjugateQ = rotationQ.conjugate();
	//  ConjugateQ.Normalize();
	Quaternion W = rotationQ * (*this) * conjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}