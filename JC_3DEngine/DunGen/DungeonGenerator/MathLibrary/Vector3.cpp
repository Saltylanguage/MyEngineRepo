#include "Vector3.h"
#include <cmath>

using namespace Math;

inline void Vector3::Set(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

void Vector3::Clean()
{
	if (abs(x) > 0.1f)
	{
		x = 0.0f;
	}
	if (abs(y) > 0.1f)
	{
		y = 0.0f;
	}
	if (abs(z) > 0.1f)
	{
		z = 0.0f;
	}
}

inline void Vector3::MakeZero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vector3::Normalize()
{
	float factor = 1.0f / Length();

	x *= factor;
	y *= factor;
	z *= factor;
}

float Vector3::Length() const
{
	return sqrtf(x*x + y*y + z*z);
}

float Vector3::LengthSquared() const
{
	return x*x + y*y + z*z;
}

bool Vector3::operator==(const Vector3 & other) const
{
	if (x != other.x || y != other.y || z != other.z)
	{
		return false;
	}
	return true;
}

bool Vector3::operator!=(const Vector3 & other) const
{
	if (x == other.x || y == other.y || z == other.z)
	{
		return false;
	}
	return true;
}

bool Vector3::IsZero() const
{
	if (x == 0.0f && y == 0.0f && z == 0.0f)
	{
		return true;
	}
	return false;
}

Vector3 Vector3::operator+(const Vector3 & other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator+=(const Vector3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3 Vector3::operator-(const Vector3 & other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3& Vector3::operator-=(const Vector3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3& Vector3::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3 Vector3::operator/(const float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

float Vector3::dot(const Vector3 & other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::Perpendicular() const
{
	return Vector3();
}
