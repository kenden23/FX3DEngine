#include "Geometries.h"
#include "XMath.h"

//设置默认参数
namespace GEO_PUBLIC_PARA
{
	int segments = 360, offset = 0;
	float centerX = 0.f, centerY = 0.f, radius = 0.2f;
}

void genHeart(Vector3f *vers, int offset, int segments,
		    float ox, float oy, float R)
{
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * (float)XMConst::PI * float(i) / float(segments);

		float y = R * (2*cos(theta)-cos(2*theta));
		float x = R * (2*sin(theta)-sin(2*theta));

		vers[offset+i] = Vector3f(ox+x, oy+y, 0.0f);
	}
}

void genHeart_2(Vector3f *&vers, int offset, int segments,
			 float ox, float oy, float R)
{
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * (float)XMConst::PI * float(i) / float(segments);

		float x = R * 16 * pow(sin(theta), 3);
		float y = R * (13 * cos(theta) - 5*cos(2*theta)
			- 2*cos(3*theta) - cos(4*theta));

		vers[offset+i] = Vector3f(ox+x, oy+y, 0.0f);
	}
}

GeometryFactory::GeometryFactory():vpGeoShape()
{

}

GeometryFactory::~GeometryFactory()
{

}

Vector3f *GeometryFactory::genGeometry(GEOMATRIES geo)
{
	switch (geo)
	{
	case HEART_1:
		{
		genHeart();
		return vpGeoShape.back().get();
		}
		break;
		
	case HEART_2:
		{

		}
		break;
	case CIRCLE:
		break;
	case SQURE:
		break;
	case RECTANGLE:
		break;
	case ELLIPSE:
		break;
	case POLYGON:
		break;
	case PENTAGON:
		break;
	case BOX:
		break;
	case SHPERE:
		break;
	case ELLIPSE3D:
		break;
	}
	return NULL;
}

void GeometryFactory::genHeart()
{
	using namespace GEO_PUBLIC_PARA;
	vpGeoShape.push_back(std::unique_ptr<Vector3f[]>(new Vector3f[segments]));
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * (float)XMConst::PI * float(i) / float(segments);

		float y = radius * (2*cos(theta)-cos(2*theta));
		float x = radius * (2*sin(theta)-sin(2*theta));

		vpGeoShape.back()[offset+i] = Vector3f(centerX+x, centerY+y, 0.0f);
	}
}