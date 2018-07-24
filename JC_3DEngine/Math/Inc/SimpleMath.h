#pragma once
#include <cmath>

namespace Math
{
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))

	class Vector3;
	class Matrix4X4;

	namespace General
	{
		float Abs(float value);
	}
}
