#include "Precompiled.h"
#include "Quaternion.h"

using namespace Math;

Quaternion Math::Quaternion::QuaternionRotationAxis(const Vector3 & axis, float rad)
{
	const float c = cos(rad * 0.5f);
	const float s = sin(rad * 0.5f);
	const Math::Vector3 a = Math::Vector3::Normalize(axis);
	return Quaternion(a.X * s, a.Y * s, a.Z * s, c);
}

Matrix Quaternion::QuaternionToMatrix()
{
	return Math::Matrix(
	{
		1 - 2 * (y*y),		(2 * x*y) - (2 * w*z),		(2 * x*z) + (2 * w*y),			0,

		(2 * x*y) + (2 * w*z),	1 - (2 * x*x) - (2 * z*z),	(2 * y*z) - (2 * w*x),		0,

		(2 * x*z) - (2 * w*y), (2 * y*z) + (2 * w*x),		1 - (2 * x*x) - (2 * y*y),  0,

		0,					0,						0,									1
	}
	);
}

Quaternion Quaternion::AxisAngleToQuaternion(Math::Vector3 axis, float theta)
{
	Quaternion ret;
	ret.w = cosf(theta * 0.5f);
	ret.x = axis.X * sin(theta * 0.5f);
	ret.y = axis.Y * sin(theta * 0.5f);
	ret.z = axis.Z * sin(theta * 0.5f);

	return ret;
}

Quaternion Quaternion::Slerp(Quaternion q0, Quaternion q1, float t)
{
	float dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

	if (dot < 0.0f)
	{
		dot = -dot;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
		q1.w = -q1.w;
	}
	else if (dot > 0.999f)
	{
		return Normalize(Lerp(q0, q1, t));
	}
	float theta = acosf(dot);
	float sintheta = sinf(theta);
	float scale0 = sinf(theta * (1.0f - t)) / sintheta;
	float scale1 = sinf(theta * t) / sintheta;

	//actually slerping
	return Quaternion(

		(q0.x * scale0) + (q1.x * scale1),
		(q0.y * scale0) + (q1.y * scale1),
		(q0.z * scale0) + (q1.z * scale1),
		(q0.w * scale0) + (q1.w * scale1)
	);
}

