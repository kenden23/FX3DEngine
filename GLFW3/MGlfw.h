#pragma once
#include <GL\glew.h>
#include <GL/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Geometries.h"

class MGlfw
{
public:
	MGlfw();
	virtual ~MGlfw();

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);

	virtual void mGlfwInit();
	virtual void genGeometry() = 0;
	virtual void run() = 0;
	virtual void draw() = 0;
	virtual void viewProject();
	virtual void terminate();

	GLFWwindow* window;
};