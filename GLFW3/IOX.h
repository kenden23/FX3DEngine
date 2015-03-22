#pragma once
#include <vector>
using std::vector;
#include <GL\glfw3.h>

class IOX
{
	vector<void (*)(GLFWwindow *, int, int, int, int)> keyCallBackVec;
	vector<void (*)(GLFWwindow *, double, double)> mouseMovesCBVec;
	unsigned cbidx;

	IOX() : keyCallBackVec(), mouseMovesCBVec(), cbidx(0)
	{

	}
public:
	void registerKeyCBFuncs(void (*CB)(GLFWwindow* , int , int , int , int))
	{//如果写void CB(GLFWwindow*, int, int, int, int)和vector一起使用那么就会出错，原因应该是因为函数名和函数指针还是有区别的,把名字副本保存进vector里面是不对的。
		keyCallBackVec.push_back(CB);
	}

	void registerMouseMoveFuncs(void (*CB)(GLFWwindow *, double , double))
	{
		mouseMovesCBVec.push_back(CB);
	}	 

	static IOX *getInstance()
	{
		static IOX iox;
		return &iox;
	}

	void keyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (unsigned i = 0; i < keyCallBackVec.size(); i++)
		{
			(*keyCallBackVec[i])(window, key, scancode, action, mods);
		}
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		IOX *iox = IOX::getInstance();
		iox->keyCB(window, key, scancode, action, mods);
	}

	static void mouseMoveCallBack(GLFWwindow *w, double x, double y)
	{
		IOX *iox = IOX::getInstance();
		iox->mouseMoveCB(w, x, y);
	}

	void mouseMoveCB(GLFWwindow *w, double x, double y)
	{
		for (unsigned i = 0; i < mouseMovesCBVec.size(); i++)
			mouseMovesCBVec[i](w, x, y);
	}
};