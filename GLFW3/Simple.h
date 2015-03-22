#pragma once
//#include <GL/glfw3.h>
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL\gl3w.h>
#include <GL\glew.h>
#include <GL/glfw3.h>
#include "Geometries.h"

void RenderSome()
{
	static const GLfloat red[] = {1.f, 0.f, 0.f, 1.f};
	glClearBufferfv(GL_COLOR, 0, red);
}

namespace Simple_1
{
	/*
int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glfwSetKeyCallback(window, key_callback);

	genGeometry();

	while (!glfwWindowShouldClose(window))
	{		
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		

		glClear(GL_COLOR_BUFFER_BIT);
		//render function
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_LINE_LOOP, 0, gSegments);

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
*/

}