#include "Precompiled.h"
#include "Math\Inc\Vector4.h"
#include <math.h>
#include "Graphics/Inc/Color.h"

using namespace Math;

//static members

//AXES
Vector4 Vector4::xAxis(1.0f, 0.0f, 0.0f, 0.0f);
Vector4 Vector4::yAxis(0.0f, 1.0f, 0.0f, 0.0f);
Vector4 Vector4::zAxis(0.0f, 0.0f, 1.0f, 0.0f);
Vector4 Vector4::wAxis(0.0f, 0.0f, 0.0f, 1.0f);
Vector4 Vector4::origin(0.0f, 0.0f, 0.0f, 0.0f);

//COLORS


Vector4& Vector4::operator=(const Vector4& other)
{
	if (this == &other)
	{
		return *this;
	}

	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	return *this;
}

//Vector4& Vector4::operator=(const Graphics::Color& other)
//{
//	x = other.r;
//	y = other.g;
//	z = other.b;
//	w = other.a;
//
//	return *this;
//}


float Vector4::Length() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

float Vector4::LengthSquared() const
{
	return (x*x + y*y + z*z + w*w);
}

bool Vector4::operator==(Vector4 other) const
{
	if (x == other.x &&
		y == other.y &&
		z == other.z &&
		w == other.w)
	{
		return true;
	}
	return false;
}

bool Vector4::operator!=(Vector4 other) const
{
	if (x != other.x ||
		y != other.y ||
		z != other.z ||
		w != other.w)
	{
		return true;
	}
	return false;
}

bool Vector4::IsZero() const
{
	if (*this == origin)
	{
		return true;
	}
	return false;
}

void Vector4::Clean()
{
	if (x < 0.005f) { x = 0.0f; }
	if (y < 0.005f) { y = 0.0f; }
	if (z < 0.005f) { z = 0.0f; }
	if (w < 0.005f) { w = 0.0f; }
}

void Vector4::Normalize()
{
	float lengthSq = x*x + y*y + z*z + w*w;

	if (lengthSq == 0.0f)
	{
		Zero();
	}
	else
	{
		float factor = 1.0f / sqrtf(lengthSq);
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
	}
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	Vector4 ret;
	ret.x = x + other.x;
	ret.y = y + other.y;
	ret.z = z + other.z;
	ret.w = w + other.w;
	return ret;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	Vector4 ret;
	ret.x = x - other.x;
	ret.y = y - other.y;
	ret.z = z - other.z;
	ret.w = w - other.w;
	return ret;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
	return Vector4(x*scalar, y*scalar, z*scalar, w*scalar);
}

Vector4& Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4 Vector4::operator/(float scalar) const
{
	return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

Vector4& Vector4::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}




float Vector4::Dot(const Vector4& other)const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

void Vector4::SetVector(float x, float y, float z, float w)
{
	x = x;
	y = y;
	z = z;
	w = w;
}

void Vector4::SetZero()
{
	*this = origin;
}

