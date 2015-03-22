#pragma once
#include "MGlfw.h"

class TransformerTest : public MGlfw
{
public:
	TransformerTest();
	~TransformerTest();

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
