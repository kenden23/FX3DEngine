#include "Camera.h"
#include "XMath.h"
#include "IOX.h"
#include <math.h>

Camera::Camera():keyWalkSpeed(0.1f), margin(5), verticalAxis(0.f, 1.f, 0.f),
	edgeSpeed(0.1f), mouseRotateSpeed(0.05f), pos(), viewInitPos(1.f, 0.f, 0.f)
{
	//indicate whether the mouse is positioned on one of the edges of the screen
	onUpperEdge = false;
	onLowerEdge = false;
	onLeftEdge  = false;
	onRightEdge = false;

	//get current window's size
	GLFWwindow *win = glfwGetCurrentContext();
	//glfwGetCursorPos(win, &mousePos.x, &mousePos.y);//The initialized pos is (0,0)
	int winHeight, winWidth;
	glfwGetFramebufferSize(win, &winWidth, &winHeight);

	//Initialize like this to make the angleV in the middle of camera view
	mousePos.x = double(winWidth>>1);
	mousePos.y = (double)(winHeight>>1);

	//only need angleH and angleV to update camera
	angleH = 270.f;//270 degree make the camera point to z axis
	angleV = 0.f;

	IOX *iox = IOX::getInstance();
	iox->registerKeyCBFuncs(onKeyboardCallBack);
	iox->registerMouseMoveFuncs(onMouseCallBack);

	update();//update first to get target and up
}

//this function is optinal.
void Camera::init()
{
	//We only initialize the target position once, and munipulate angleH and angleV to control camera move consecutively, camera and mouse don't munipulate targe directly, otherwise, it won't be consecutively. And use update() function to change angleV and angleH, and then production new target and up, so that control target and up indirectly, and that make our camera move consecutively
	pos          = Vector3f(0.0f, 0.0f, 0.0f);
	target       = Vector3f(0.0f, 0.0f, 1.0f);
	target.normalize();
	up           = Vector3f(0.0f, 1.0f, 0.0f);

	Vector3f HTarget(target.x, 0.0f, target.z);
	HTarget.normalize();
	//和普通坐标相反，普通坐标是逆时针的，这里是顺时针计算的,just a small algo
	if (HTarget.z >= 0.0f)
	{
		if (HTarget.x >= 0.0f)
		{
			angleH = 360.0f - XMUtil::toDegree(asin(HTarget.z));
		}
		else
		{
			angleH = 180.0f + XMUtil::toDegree(asin(HTarget.z));
		}
	}
	else
	{
		if (HTarget.x >= 0.0f)
		{
			angleH = XMUtil::toDegree(asin(-HTarget.z));
		}
		else
		{
			angleH = 180.0f + XMUtil::toDegree(asin(-HTarget.z));
		}
	}
	angleV = -XMUtil::toDegree(asin(target.y));
}

void Camera::onKeyboardCallBack(GLFWwindow *w, int key, int scancode, int action, int mods)
{
	Camera *camera = Camera::getInstance();
	camera->onKeyboard(w, key, scancode, action, mods);
}

void Camera::onKeyboard(GLFWwindow *w, int key, int scancode, int action, int mods)
{
	switch (key) 
	{
	case GLFW_KEY_W:
		{
			pos += (target * keyWalkSpeed);
		}
		break;

	case GLFW_KEY_S:
		{
			pos -= (target * keyWalkSpeed);
		}
		break;

	case GLFW_KEY_A:
		{
			Vector3f Left = target.cross(up);
			Left.normalize();
			Left *= keyWalkSpeed;
			pos += Left;
		}
		break;

	case GLFW_KEY_D:
		{
			Vector3f Right = up.cross(target);
			Right.normalize();
			Right *= keyWalkSpeed;
			pos += Right;
		}
		break;
	}
}

void Camera::onMouseCallBack(GLFWwindow *w, double x, double y)
{
	Camera::getInstance()->onMouse(x, y);
}

void Camera::onMouse(double x, double y)
{
	const double DeltaX = x - mousePos.x;
	const double DeltaY = y - mousePos.y;

	mousePos.x = x;
	mousePos.y = y;

	angleH += (float) DeltaX * mouseRotateSpeed;
	angleV += (float) DeltaY * mouseRotateSpeed;

	int winWidth, winHeight;
	GLFWwindow *win = glfwGetCurrentContext();
	glfwGetWindowSize(win, &winWidth, &winHeight);

	if (DeltaX == 0.0)
	{
		if (x <= margin)
		{
			onLeftEdge = true;
		}
		else if (x >= (winWidth - margin)) 
		{
			onRightEdge = true;
		}
	}
	else 
	{
		onLeftEdge = false;
		onRightEdge = false;
	}

	if (DeltaY == 0.0)
	{
		if (y <= margin) 
		{
			onUpperEdge = true;
		}
		else if (y >= (winHeight - margin)) 
		{
			onLowerEdge = true;
		}
	}
	else
	{
		onUpperEdge = false;
		onLowerEdge = false;
	}
	update();
}

//Only for easily rotate camera while the curse is at the edge of window
void Camera::onEdgesMover()
{
	bool shouldUpdate = false;

	if (onLeftEdge)
	{
		angleH -= edgeSpeed;
		shouldUpdate = true;
	}
	else if (onRightEdge) 
	{
		angleH += edgeSpeed;
		shouldUpdate = true;
	}

	if (onUpperEdge)
	{
		if (angleV > -90.0f)
		{
			angleV -= edgeSpeed;
			shouldUpdate = true;
		}
	}
	else if (onLowerEdge) 
	{
		if (angleV < 90.0f)
		{
			angleV += edgeSpeed;
			shouldUpdate = true;
		}
	}

	if (shouldUpdate)
	{
		update();
	}
}

void Camera::update()
{
	target = viewInitPos;
	target.rotate(angleH, verticalAxis);
	target.normalize();

	// Rotate the view vector by the vertical angle around the horizontal axis
	Vector3f Haxis = verticalAxis.cross(target);
	Haxis.normalize();
	target.rotate(angleV, Haxis);

	target.normalize();

	up = target.cross(Haxis);
	up.normalize();
}