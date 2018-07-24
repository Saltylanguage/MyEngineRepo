#pragma once

#include "Common.h"
#include "SimpleMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Matrix3.h"
#include "Quaternion.h"

namespace Math
{
	enum class Direction
	{
		left = 0,
		top,
		right,
		down
	};

	template <typename T> inline T Min(T a, T b) { return (a > b) ? b : a; }
	template <typename T> inline T Max(T a, T b) { return (a < b) ? b : a; }

	Vector3 GetTranslation(Matrix matrix);
	Vector3 GetRight(Matrix matrix);
	Vector3 GetUp(Matrix matrix);
	Vector3 GetForward(Matrix matrix);

	//Vector3 GetScale(Matrix4X4 matrix);
	//Vector3 GetRotation(Matrix4X4 matrix);

	Vector3 RandomVector3();
	Vector3 RandomVector3(const Vector3& min, const Vector3& max);

	struct Rect
	{
		float left, top, right, bottom;

		Rect() : left(0.0f), top(0.0f), right(1.0f), bottom(1.0f) {}
		Rect(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) {}
	};

	//bool Intersect(const LineSegment& a, const LineSegment& b);
	//bool Intersect(const Circle& c0, const Circle& c1);
	
	bool Intersect(const Rect& r0, const Rect& r1);


	//bool Intersect(const LineSegment& l, const Circle& c);
	//bool Intersect(const Circle& c, const LineSegment& l);

	//bool Intersect(const Circle& c, const Rect& r);
	//bool Intersect(const Rect& r, const Circle& c);

	struct LineSegment
	{
		Vector2 from;
		Vector2 to;

		LineSegment() : from(0.0f, 0.0f), to(0.0f, 0.0f) {}
		LineSegment(float x0, float y0, float x1, float y1) : from(x0, y0), to(x1, y1) {}
		LineSegment(const Vector2& v0, const Vector2& v1) : from(v0), to(v1) {}
	};



	struct Circle
	{
		Math::Vector2 center;
		float radius;

		Circle() : center(0.0f, 0.0f), radius(1.0f) {}
		Circle(const Math::Vector2& center, float radius) : center(center), radius(radius) {}
		Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
	};

	struct Sphere
	{
		Vector3 center;
		float radius;

		Sphere() : center{ 0.0f, 0.0f, 0.0f }, radius(1.0f) {}
		Sphere(float x, float y, float z, float radius) : center{ x, y, z }, radius(radius) {}
		Sphere(const Vector3& center, float radius) : center(center), radius(radius) {}
	};

	struct Ray
	{
		Vector3 org;
		Vector3 dir;

		Ray() : org(0.0f, 0.0f, 0.0f), dir(0.0f, 0.0f, 1.0f) {}
		Ray(float x, float y, float z, float dx, float dy, float dz) : org(x, y, z), dir(dx, dy, dz) {}
		Ray(const Vector3& org, const Vector3& dir) : org(org), dir(dir) {}
	};


	struct AABB
	{
		Vector3 center;
		Vector3 extend;

		AABB() : center{ 0.0f, 0.0f, 0.0f }, extend{ 0.0f, 0.0f, 0.0f } {}
		AABB(const Vector3& center, const Vector3& extend) : center(center), extend(extend) {}
	};

	struct OBB
	{
		Vector3 center;
		Vector3 extend;
		Quaternion orientation;

		OBB()
			: center(0.0f, 0.0f, 0.0f)
			, extend(1.0f, 1.0f, 1.0f)
			, orientation(0.0f, 0.0f, 0.0f, 1.0f)
		{}

		OBB(float x, float y, float z, float sx, float sy, float sz)
			: center(x, y, z)
			, extend(sx, sy, sz)
			, orientation(0.0f, 0.0f, 0.0f, 1.0f)
		{}

		OBB(float x, float y, float z, float sx, float sy, float sz, const Quaternion& orientation)
			: center(x, y, z)
			, extend(sx, sy, sz)
			, orientation(orientation)
		{}

		OBB(const Vector3& center, const Vector3& extend, const Quaternion& orientation)
			: center(center)
			, extend(extend)
			, orientation(orientation)
		{}
	};

	struct Plane
	{
		Vector3 n;
		float d;

		Plane() : n(0.0f, 1.0f, 0.0f), d(0.0f) {}
		Plane(float a, float b, float c, float d) : n(a, b, c), d(d) {}
	};


	//----------------------------------------------------------------------------------------------------

	extern const float kPi;
	extern const float kTwoPi;
	extern const float kPiByTwo;
	extern const float kRootTwo;
	extern const float kRootThree;
	extern const float kDegToRad;
	extern const float kRadToDeg;

	//----------------------------------------------------------------------------------------------------


	inline Vector3 GetPoint(const Ray& ray, float distance) { return ray.org + (ray.dir * distance); }

	bool Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance);
	bool Intersect(const Ray& ray, const Plane& plane, float& distance);
	bool Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit);
	bool Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit);
	bool Intersect(const Vector3& point, const AABB& aabb);
	bool Intersect(const Vector3& point, const OBB& obb);


	float RandomFloat();

	//----------------------------------------------------------------------------------------------------

	float RandomFloat(float min, float max);


	inline float Sqr(float num) { return num*num; }

}


