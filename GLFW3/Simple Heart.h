#pragma once
#include "MGlfw.h"

class SimpleHeart : public MGlfw
{
public:
	SimpleHeart();
	~SimpleHeart();

	void genGeometry();
	void run();
	void draw();

	int gSegments;
	GLuint VBO;
};