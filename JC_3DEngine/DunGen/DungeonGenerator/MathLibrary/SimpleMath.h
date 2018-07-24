#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

namespace Math
{
	extern const float kPi;
	extern const float kTwoPi;
	extern const float kPiByTwo;
	extern const float kRootTwo;
	extern const float kRootThree;
	extern const float kDegToRad;
	extern const float kRadToDeg;
	extern const float epsilon;



	struct LineSegment
	{
		Vector2 start;
		Vector2 end;

		LineSegment() : start(0.0f, 0.0f), end(0.0f, 0.0f)
		{}
		LineSegment(Vector2 a, Vector2 b) : start(a), end(b)
		{}
		LineSegment(const float x0, const float y0, const float x1, const float y1) :
			start(x0, y0), end(x1, y1)
		{}
	};

	struct Rectangle
	{
		float left, top, right, bottom;

		Rectangle() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f)
		{}
		Rectangle(const float left, const float top, const float right, const float bottom) : left(left), top(top), right(right), bottom(bottom)
		{}
	};

	struct Triangle
	{
		Vector2 pointA;
		Vector2 pointB;
		Vector2 pointC;

		Triangle() : pointA(0.0f, 0.0f), pointB(0.0f, 0.0f), pointC(0.0f, 0.0f)
		{}
		Triangle(Vector2 a, Vector2 b, Vector2 c) : pointA(a), pointB(b), pointC(c)
		{}
		Triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) :
		  pointA(x1, y1)
		, pointB(x2, y2)
		, pointC(x3, y3)
		{}

	};

	struct Circle
	{
		Vector2 center;
		float radius;

		Circle() : center(0.0f,0.0f), radius(0.0f)
		{}
		Circle(Vector2 cen, float rad) : center(cen), radius(rad)
		{}
		Circle(const float x, const float y, const float rad) : center(x, y), radius(rad)
		{}
	};

	struct Sphere
	{
		Vector3 center;
		float radius;

		Sphere() : center{ 0.0f, 0.0f, 0.0f }, radius(1.0f) {}
		Sphere(const float x, const float y, const float z, const float radius) : center{ x, y, z }, radius(radius) {}
		Sphere(const Vector3& center, const float radius) : center(center), radius(radius) {}
	};

	struct Ray
	{
		Vector3 origin;
		Vector3 direction;

		Ray() : origin(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f)
		{}
		Ray(Vector3 org, Vector3 dir) : origin(org), direction(dir)
		{}
		Ray(const float orgX, const float orgY, const float orgZ, const float dirX, const float dirY, const float dirZ) :
		origin(orgX, orgY, orgZ), direction(dirX, dirY, dirZ)
		{}
	};

	struct AABB
	{
		Vector3 center;
		Vector3 extend;

		AABB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f) 
		{}
		AABB(Vector3 cen, Vector3 ext) : center(cen), extend(ext)
		{}
		AABB(const float cenX, const float cenY, const float cenZ, const float extX, const float extY, const float extZ) :
		center(cenX, cenY, cenZ), extend(extX, extY, extZ)
		{}
	};

	struct OBB
	{
		Vector3 center;
		Vector3 extend;
		Vector3 orientation;

		OBB() : center(0.0f, 0.0f, 0.0f), extend(0.0f, 0.0f, 0.0f), orientation(0.0f, 0.0f, 0.0f)
		{}

		OBB(const float x, const float y, const float z, const float sx, const float sy, const float sz) :
		center(x, y, z), extend(sx, sy, sz), orientation(0.0f, 0.0f, 0.0f)
		{}

		OBB(const Vector3 cen, const Vector3 ext, const Vector3 ori) : center(cen), extend(ext), orientation(ori)
		{}

		OBB(const float cenX, const float cenY, const float cenZ, 
			const float extX, const float extY, const float extZ, 
			const float oriX, const float oriY, const float oriZ) :
			center(cenX, cenY, cenZ), extend(extX, extY, extZ)
		{}
		

	};

	struct Plane
	{
		Vector3 normal;
		float extent;

		Plane() : normal(0.0f, 1.0f, 0.0f), extent(0.0f) {}
		Plane(Vector3 n, float ext) : normal(n), extent(ext) {}
		Plane(float a, float b, float c, float d) : normal(a, b, c), extent(d) {}
	};

	inline Vector3 GetPoint(const Ray& ray, float distance) { return ray.origin + (ray.direction * distance); }

	bool Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance);
	bool Intersect(const Ray& ray, const Plane& plane, float& distance);
	bool Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit);
	bool Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit);
	bool Intersect(const Vector3& point, const AABB& aabb);
	bool Intersect(const Vector3& point, const OBB& obb);

	//Common Functions
	inline float Sqr(float num) { return num*num; }

	float RandomFloat();
	float RandomFloat(float min, float max);

}