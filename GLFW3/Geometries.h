#pragma once
#include <memory>
#include <vector>
#include "XMatrix.h"

//使用一个变量就可以记住所有需要创建的Shapes的变量，这是使用enum的优势，而一般API都没有利用上这一点
enum GEOMATRIES
{
	HEART_1, HEART_2, CIRCLE, SQURE, RECTANGLE, ELLIPSE, POLYGON, PENTAGON,
	BOX, SHPERE, ELLIPSE3D
};

namespace GEO_PUBLIC_PARA
{
	extern int segments, offset;
	extern float centerX, centerY, radius;
}

void genHeart(Vector3f *vers, int offset, int segments,
		    float ox, float oy, float R = 0.2);

void genHeart_2(Vector3f *&vers, int offset, int segments,
			 float ox, float oy, float R = 0.05);

//base class
class Shape
{
public:
	Shape();
	virtual ~Shape();
};

class Heart_1 : public Shape
{
public:
	Heart_1();
	~Heart_1();
};

class Heart_2 : public Shape
{
public:
	Heart_2();
	~Heart_2();
};

class GeometryFactory
{
	std::vector<std::unique_ptr<Shape> > vpShape;//暂时不用
	//自动管理内存，无需手动释放
	std::vector<std::unique_ptr<Vector3f[]> > vpGeoShape;
	GeometryFactory();
public:
	virtual ~GeometryFactory();
	static GeometryFactory *getInstance()
	{
		static GeometryFactory instance;
		return &instance;
	}

	virtual Vector3f *genGeometry(GEOMATRIES geo);

	void genHeart();

	void genHeart_2(Vector3f *vers, int offset, int segments,
		float ox, float oy, float R = 0.05);
};

