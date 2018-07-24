#pragma once
#include "Matrix.h"
#include "Vector3.h"



namespace Math
{
	class Quaternion
	{
	public:

		float x;
		float y;
		float z;
		float w;

		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		static Quaternion Quaternion::Zero() { return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); }
		static Quaternion Quaternion::Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

		Quaternion operator+(const Quaternion& rhs) const { return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
		Quaternion operator*(float s) const { return Quaternion(x * s, y * s, z * s, w * s); }
		Quaternion operator/(float s) const { return Quaternion(x / s, y / s, z / s, w / s); };

		static float Length(const Quaternion& q) { return sqrtf((q.x * q.x) + (q.y*q.y) + (q.z * q.z) + (q.w * q.w)); }
		static float LengthSquared(const Quaternion& q) { return (q.x * q.x) + (q.y*q.y) + (q.z * q.z) + (q.w * q.w); }
		static Quaternion Normalize(const Quaternion& q) { return q / Length(q); }

		static Quaternion QuaternionRotationAxis(const Vector3& axis, float rad);
		
		Matrix QuaternionToMatrix();
		
		static Quaternion AxisAngleToQuaternion(Math::Vector3 axis, float theta);
		
		static Quaternion Lerp(Quaternion q0, Quaternion q1, float t) { return q0 * (1.0f - t) + (q1 * t); }
		static Quaternion Slerp(Quaternion q0, Quaternion q1, float t);

	};
}
