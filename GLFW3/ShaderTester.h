#pragma once
#include "MGlfw.h"

class ShaderTester : public MGlfw
{
public:
	ShaderTester();
	~ShaderTester();

	void genGeometry();
	void run();
	void draw();
	void initShader();

	int gSegments;
	GLuint VBO;
};