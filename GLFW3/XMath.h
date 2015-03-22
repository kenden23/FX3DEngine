#pragma once


namespace XMConst
{
	const float PI = 3.14159265358979323846f;
}

namespace XMUtil
{
	inline float toRadian(float x) { return x * XMConst::PI / 180.0f; }
	inline float toDegree(float x) { return x * 180.0f / XMConst::PI; }
}