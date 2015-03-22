#pragma once
#include "XVector.h"

//Mat4x4f class declaration===============================
class Mat4x4f
{
public:
	float m[4][4];

	Mat4x4f();
	~Mat4x4f();

	inline void initIdentity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	Mat4x4f operator*(const Mat4x4f &r) const;

	//make *this Mat4x4f as a scaling matrix
	void scale(float xScale, float yScale, float zScale);

	//rotate around x, y, z about any angle respectly.
	void rotate(float xAngle, float yAngle, float zAngle);

	//translate for x, y, z direction respectly
	void translate(float xDist, float yDist, float zDist);

	//make *this Mat4x4f as a camera transformation matrix, translate to camera space
	void camera(const Vector3f& target, const Vector3f& up);

	//make *this Mat4x4f as a pespective projection matrix
	void persProj(float FOV, float width, float height, float zNear, float zFar);
};//=======================================================