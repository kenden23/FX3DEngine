#include "MGlfw.h"
#include "IOX.h"

MGlfw::MGlfw()
{

}

MGlfw::~MGlfw()
{

}

void MGlfw::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void MGlfw::key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);	
}

void MGlfw::mGlfwInit()
{	
	glfwSetErrorCallback(MGlfw::error_callback);
	if (!glfwInit()) exit(EXIT_FAILURE);
	//window = glfwCreateWindow(1366, 768, "Simple example", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(1024, 700, "Simplified", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		getchar();
		exit(EXIT_FAILURE);
	}

	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);
	
	glfwSetKeyCallback(window, IOX::keyCallback);
	glfwSetCursorPosCallback(window, IOX::mouseMoveCallBack);

	IOX *iox = IOX::getInstance();
	iox->registerKeyCBFuncs(key_callback);
}

void MGlfw::run()
{

}

//Don't have to use function
void MGlfw::viewProject()
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
}

void MGlfw::terminate()
{
	GLFWwindow *win = glfwGetCurrentContext();
	glfwDestroyWindow(win);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}