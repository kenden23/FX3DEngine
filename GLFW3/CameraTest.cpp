#include "CameraTest.h"
#include "Geometries.h"
#include "ShaderManager.h"
#include "GeoPipeline.h"
#include "Camera.h"

namespace CameraTestName
{
	const char* pVS = "ShaderFiles/shaderTutorial13.vs";
	const char* pFS = "ShaderFiles/shaderTutorial10.fs";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 768;
}

CameraTest::CameraTest()
{
	mGlfwInit();
	genGeometry();
	initShader();
}

CameraTest::~CameraTest()
{
}

void CameraTest::initShader()
{
	using namespace CameraTestName;
	ShaderManager *shm = ShaderManager::getInstance();
	shm->addVertexShader(pVS);
	shm->addFragmentShader(pFS);
	shm->createShaderProgram();
	shm->mapToShaderStringName(gWorldLoc, "gWVP");
}

void CameraTest::genGeometry()
{
	using namespace GEO_PUBLIC_PARA;
	GeometryFactory *geo = GeometryFactory::getInstance();
	Vector3f *vers = geo->genGeometry(GEOMATRIES::HEART_1);
	gSegments = segments;
	//genHeart_2(vers, 0, segments, 0.f, 0.f, 0.02);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//如果使用Vector3f vers[360]；这样分配内存，那么下面就可以使用sizeof(vers), vers这样设置参数，但是如果使用动态内存，那么下面就不能使用sizeof(vers)，只能使用segments*sizeof(Vector3f)，这样手动设置好大小。
	glBufferData(GL_ARRAY_BUFFER, segments*sizeof(Vector3f), vers, GL_STATIC_DRAW);
}

void CameraTest::run()
{
	while (!glfwWindowShouldClose(window))
	{
		//viewProject();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	terminate();
}

void CameraTest::transformation()
{
	static float Scale = 0.0f;

	Scale += 0.1f;

	GeoPipeline p;
	//p.setScale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
	//p.setWorldPos(sinf(Scale), 0.0f, 0.0f);
	//p.setRotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	Camera *camera = Camera::getInstance();
	
	p.setRotate(0.0f, Scale, 0.0f);
	p.setWorldPos(0.0f, 0.0f, 3.0f);//This is for the initialized pos of object
	p.setCamera(camera);
	p.setPerspectiveProj(50.0f, (float)width, (float)height, 1.0f, 100.0f);

	camera->onEdgesMover();	

	ShaderManager *shm = ShaderManager::getInstance();
	shm->setUniformMat4x4ToShader(gWorldLoc, (float **)p.getCombineTransMat()->m);
}

void CameraTest::draw()
{
	transformation();

	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glDrawArrays(GL_POLYGON, 0, gSegments);
	
	/*
	//When change win's size, change viewport
	//viewport 1
	glViewport(0, 0, width/2, height/2);
	glDrawArrays(GL_POLYGON, 0, gSegments);
	
	
	//viewport 2
	glViewport(width/2, 0, width/2, height/2);
	glDrawArrays(GL_POLYGON, 0, gSegments);

	//viewport 3
	glViewport(0, height/2, width/2, height/2);
	glDrawArrays(GL_POLYGON, 0, gSegments);

	//viewport 4
	glViewport(width/2, height/2, width/2, height/2);
	glDrawArrays(GL_POLYGON, 0, gSegments);
	*/

	glDisableVertexAttribArray(0);
}