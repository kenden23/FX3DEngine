#include "XMatrix.h"
#include "XMath.h"
#include <malloc.h>
#include <math.h>

Mat4x4f::Mat4x4f()
{
	initIdentity();
}

Mat4x4f::~Mat4x4f()
{

}

Mat4x4f Mat4x4f::operator*(const Mat4x4f &r) const
{
	Mat4x4f rs;
	for (unsigned i = 0 ; i < 4 ; i++)
	{
		for (unsigned j = 0 ; j < 4 ; j++)
		{
			rs.m[i][j] = m[i][0] * r.m[0][j] + m[i][1] * r.m[1][j]
			+ m[i][2] * r.m[2][j] + m[i][3] * r.m[3][j];
		}
	}
	return rs;
}

void Mat4x4f::scale(float xScale, float yScale, float zScale)
{
	m[0][0] = xScale; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
	m[1][0] = 0.0f;   m[1][1] = yScale; m[1][2] = 0.0f;   m[1][3] = 0.0f;
	m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = zScale; m[2][3] = 0.0f;
	m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
}

void Mat4x4f::rotate(float xAngle, float yAngle, float zAngle)
{
	Mat4x4f rx, ry, rz;

	const float x = XMUtil::toRadian(xAngle);
	const float y = XMUtil::toRadian(yAngle);
	const float z = XMUtil::toRadian(zAngle);

	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f   ; rx.m[0][2] = 0.0f    ; rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x) ; rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f   ; rx.m[3][2] = 0.0f    ; rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f   ; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f    ; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y) ; ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f   ; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f    ; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z) ; rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f   ; rz.m[2][1] = 0.0f    ; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f   ; rz.m[3][1] = 0.0f    ; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	*this = rz * ry * rx;
}

void Mat4x4f::translate(float xDist, float yDist, float zDist)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = xDist;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = yDist;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = zDist;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Mat4x4f::camera(const Vector3f& target, const Vector3f& up)
{
	Vector3f N = target;
	N.normalize();
	Vector3f U = up;
	U.normalize();
	U = U.cross(N);
	Vector3f V = N.cross(U);

	m[0][0] = U.x;   m[0][1] = U.y;   m[0][2] = U.z;   m[0][3] = 0.0f;
	m[1][0] = V.x;   m[1][1] = V.y;   m[1][2] = V.z;   m[1][3] = 0.0f;
	m[2][0] = N.x;   m[2][1] = N.y;   m[2][2] = N.z;   m[2][3] = 0.0f;
	m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;
}

void Mat4x4f::persProj(float FOV, float Width, float Height, float zNear, float zFar)
{
	const float ar         = Width / Height;
	const float zRange     = zNear - zFar;
	const float t1 = tanf(XMUtil::toRadian(FOV / 2.0f));
	const float t2 = (-zNear - zFar) / zRange;
	const float t3 = 2.0f * zFar * zNear / zRange;

	m[0][0] = 1.0f/(t1 * ar);	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0;
	m[1][0] = 0.0f;			m[1][1] = 1.0f/t1;	m[1][2] = 0.0f;	m[1][3] = 0.0;
	m[2][0] = 0.0f;			m[2][1] = 0.0f;	m[2][2] = t2;		m[2][3] = t3;
	m[3][0] = 0.0f;			m[3][1] = 0.0f;	m[3][2] = 1.0f;	m[3][3] = 0.0;
}