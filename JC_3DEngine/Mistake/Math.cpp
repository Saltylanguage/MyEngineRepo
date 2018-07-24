#include "Precompiled.h"
#include "Math.h"

using namespace Math;

const float Math::kPi = 3.14159265358979f;
const float Math::kTwoPi = 6.28318530717958f;
const float Math::kPiByTwo = 1.57079632679489f;
const float Math::kRootTwo = 1.41421356237309f;
const float Math::kRootThree = 1.73205080756887f;
const float Math::kDegToRad = kPi / 180.0f;
const float Math::kRadToDeg = 180.0f / kPi;

float nearZeroValue = 0.000000001f;

Vector3 Math::GetTranslation(Matrix matrix)
{
	return Vector3(matrix.matrix[12], matrix.matrix[13], matrix.matrix[14]);
}

Vector3 Math::GetRight(Matrix matrix)
{
	return Vector3(matrix.matrix[0], matrix.matrix[1], matrix.matrix[2]);
}

Vector3 Math::GetUp(Matrix matrix)
{
	return Vector3(matrix.matrix[4], matrix.matrix[5], matrix.matrix[6]);
}

Vector3 Math::GetForward(Matrix matrix)
{
	return Vector3(matrix.matrix[8], matrix.matrix[9], matrix.matrix[10]);
}

Vector3 Math::RandomVector3()
{
	return Vector3
	(
		RandomFloat(),
		RandomFloat(),
		RandomFloat()
	);

}

Vector3 Math::RandomVector3(const Vector3 & min, const Vector3 & max)
{
	return Vector3
	(
		RandomFloat(min.X, max.X),
		RandomFloat(min.Y, max.Y),
		RandomFloat(min.Z, max.Z)
	);
}

bool Math::Intersect(const Ray& ray, const Vector3& a, const Vector3& b, const Vector3& c, float& distance)
{
	// Reference: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

	// Find vectors for two edges sharing V1
	Vector3 e1 = b - a;
	Vector3 e2 = c - a;

	// Begin calculating determinant - also used to calculate u parameter	
	Vector3 P = Math::Vector3::Cross(ray.dir, e2);

	// If determinant is near zero, ray lies in plane of triangle
	float det = Math::Vector3::Dot(e1, P);
	// NOT CULLING

	if (det < nearZeroValue) //TODO:: Replace with IsZero() function
	{
		return false;
	}

	float inv_det = 1.0f / det;

	// Calculate distance from V1 to ray origin
	Vector3 T = ray.org - a;

	// Calculate u parameter and test bound
	float u = Math::Vector3::Dot(T, P) * inv_det;

	// The intersection lies outside of the triangle
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}

	// Prepare to test v parameter
	Vector3 Q = Math::Vector3::Cross(T, e1);

	// Calculate V parameter and test bound
	float v = Math::Vector3::Dot(ray.dir, Q) * inv_det;

	// The intersection lies outside of the triangle
	if (v < 0.0f || u + v  > 1.0f)
	{
		return false;
	}

	// Ray intersection
	float t = Math::Vector3::Dot(e2, Q) * inv_det;
	if (t <= 0.0f)
	{
		// No hit, no win
		return false;
	}

	distance = t;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
	const float orgDotN = Math::Vector3::Dot(ray.org, plane.n);
	const float dirDotN = Math::Vector3::Dot(ray.dir, plane.n);

	// Check if ray is parallel to the plane
	if (dirDotN < nearZeroValue && dirDotN > -nearZeroValue)
	{
		if ((orgDotN - plane.d) < nearZeroValue)
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.d - orgDotN) / dirDotN;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const AABB& aabb, float& distEntry, float& distExit)
{
	// https://truesculpt.googlecode.com/hg-history/Release%25200.8/Doc/ray_box_intersect.pdf

	// Returns true if ray intersects bounding box
	// Sets d1 to entry distance, d2 to exit distance (along ray.dir)

	Vector3 boxMin = aabb.center - aabb.extend;
	Vector3 boxMax = aabb.center + aabb.extend;
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	float divx = 1.0f / ray.dir.X;
	float divy = 1.0f / ray.dir.Y;
	float divz = 1.0f / ray.dir.Z;

	if (divx >= 0.0f)
	{
		tmin = (boxMin.X - ray.org.X) * divx;
		tmax = (boxMax.X - ray.org.X) * divx;
	}
	else
	{
		tmin = (boxMax.X - ray.org.X) * divx;
		tmax = (boxMin.X - ray.org.X) * divx;
	}
	if (divy >= 0.0f)
	{
		tymin = (boxMin.Y - ray.org.Y) * divy;
		tymax = (boxMax.Y - ray.org.Y) * divy;
	}
	else
	{
		tymin = (boxMax.Y - ray.org.Y) * divy;
		tymax = (boxMin.Y - ray.org.Y) * divy;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	if (divz >= 0.0f)
	{
		tzmin = (boxMin.Z - ray.org.Z) * divz;
		tzmax = (boxMax.Z - ray.org.Z) * divz;
	}
	else
	{
		tzmin = (boxMax.Z - ray.org.Z) * divz;
		tzmax = (boxMin.Z - ray.org.Z) * divz;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	distEntry = tmin;
	distExit = tmax;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Ray& ray, const OBB& obb, float& distEntry, float& distExit)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix matTrans = Matrix::Translation(obb.center.X, obb.center.Y, obb.center.Z);
	Matrix matRot = Matrix::RotationQuaternion(obb.orientation);
	Matrix matWorld = matRot * matTrans;
	Matrix matWorldInv = Matrix::Inverse(matWorld);

	// Transform the ray into the OBB's local space
	Vector3 org = Vector3::TransformCoord(ray.org, matWorldInv);
	Vector3 dir = Vector3::TransformNormal(ray.dir, matWorldInv);

	AABB aabb(Vector3::Zero(), obb.extend);
	return Math::Intersect(Ray(org, dir), aabb, distEntry, distExit);
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Vector3& point, const AABB& aabb)
{
	const Vector3 test = point - aabb.center;
	if (abs(test.X) > aabb.extend.X) return false;
	if (abs(test.Y) > aabb.extend.Y) return false;
	if (abs(test.Z) > aabb.extend.Z) return false;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Math::Intersect(const Vector3& point, const OBB& obb)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix matTrans = Matrix::Translation(obb.center.X, obb.center.Y, obb.center.Z);
	Matrix matRot = Matrix::RotationQuaternion(obb.orientation);
	Matrix matWorld = matRot * matTrans;
	Matrix matWorldInv = Matrix::Inverse(matWorld);

	// Transform the point into the OBB's local space
	Vector3 localPoint = Vector3::TransformCoord(point, matWorldInv);
	AABB aabb(Vector3::Zero(), obb.extend);

	// Test against local AABB
	return Math::Intersect(localPoint, aabb);
}

float Math::RandomFloat()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Math::RandomFloat(float min, float max)
{
	return min + (max - min) * RandomFloat();
}
