#pragma once
#include "MGlfw.h"

class CameraTest : public MGlfw
{
public:
	CameraTest();
	~CameraTest();

	void genGeometry();
	void run();
	void draw();
	void initShader();

	void transformation();

	int gSegments;
	GLuint VBO;
	GLuint IBO;
	GLuint gWorldLoc;
};
