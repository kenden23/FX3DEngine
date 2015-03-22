#include "Simple Heart.h"
#include "Geometries.h"

SimpleHeart::SimpleHeart()
{
	mGlfwInit();
	genGeometry();
}

SimpleHeart::~SimpleHeart()
{

}

void SimpleHeart::genGeometry()
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

void SimpleHeart::run()
{
	while (!glfwWindowShouldClose(window))
	{
		viewProject();

		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	terminate();
}

void SimpleHeart::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//render function
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_LINE_LOOP, 0, gSegments);

	glDisableVertexAttribArray(0);
}