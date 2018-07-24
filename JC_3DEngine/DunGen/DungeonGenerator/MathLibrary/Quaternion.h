#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include <cmath>

namespace Math
{
	class Quaternion
	{

		float x, y, z, w;

		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{}
		Quaternion(const float a, const float b, const float c, const float d) : x(a), y(b), z(c), w(d)
		{}

		//Math Operations
		Quaternion operator+(const Quaternion& other) const 
		{
			return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		Quaternion operator*(const float scalar) const
		{
			return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
		}
		Quaternion operator/(const float scalar) const
		{
			return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		//Static Declarations
		static Quaternion Zero() { return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); }
		static Quaternion Identity() { return Quaternion(0.0f, 0.0f,  0.0f, 1.0f); }

		//Static Functions
		static float Length(const Quaternion& q) { return sqrtf((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w)); }
		static float LengthSquared(const Quaternion& q) { return (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w); }

		static Quaternion Normalize(const Quaternion& q) { return q / Length(q); }

		static Quaternion QuaternionRotationAxis(const Vector3& axis, float rad);

		static Quaternion Lerp(Quaternion q0, Quaternion q1, float t) { return q0 * (1.0f - t) + (q1 * t); }
		static Quaternion Slerp(Quaternion q0, Quaternion q1, float t);

		//Axis Angle -> Quaternion
		static Quaternion AxisAngleToQuaternion(const Vector3& axis, const float theta);

		//Quaternion -> Matrix
		Matrix QuaternionToMatrix();
	};
}