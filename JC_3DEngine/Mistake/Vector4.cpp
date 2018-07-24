#include "Precompiled.h"
#include "Vector4.h"

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

	X = other.X;
	Y = other.Y;
	Z = other.Z;
	W = other.W;

	return *this;
}

float Vector4::Length() const
{
	return sqrtf(X*X + Y*Y + Z*Z + W*W);
}

float Vector4::LengthSquared() const
{
	return (X*X + Y*Y + Z*Z + W*W);
}

bool Vector4::operator==(Vector4 other) const
{
	if (X == other.X &&
		Y == other.Y &&
		Z == other.Z &&
		W == other.W)
	{
		return true;
	}
	return false;
}

bool Vector4::operator!=(Vector4 other) const
{
	if (X != other.X ||
		Y != other.Y ||
		Z != other.Z ||
		W != other.W)
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
	if (X < 0.005f) { X = 0.0f; }
	if (Y < 0.005f) { Y = 0.0f; }
	if (Z < 0.005f) { Z = 0.0f; }
	if (W < 0.005f) { W = 0.0f; }
}

void Vector4::Normalize()
{
	float lengthSq = X*X + Y*Y + Z*Z + W*W;

	if (lengthSq == 0.0f)
	{
		Zero();
	}
	else
	{
		float factor = 1.0f / sqrtf(lengthSq);
		X *= factor;
		Y *= factor;
		Z *= factor;
		W *= factor;
	}
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	Vector4 ret;
	ret.X = X + other.X;
	ret.Y = Y + other.Y;
	ret.Z = Z + other.Z;
	ret.W = W + other.W;
	return ret;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	W += other.W;

	return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	Vector4 ret;
	ret.X = X - other.X;
	ret.Y = Y - other.Y;
	ret.Z = Z - other.Z;
	ret.W = W - other.W;
	return ret;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	W -= other.W;

	return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
	return Vector4(X*scalar, Y*scalar, Z*scalar, W*scalar);
}

Vector4& Vector4::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	W *= scalar;
	return *this;
}

Vector4 Vector4::operator/(float scalar) const
{
	return Vector4(X / scalar, Y / scalar, Z / scalar, W / scalar);
}

Vector4& Vector4::operator/=(float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
	W /= scalar;
	return *this;
}

float Vector4::Dot(const Vector4& other)const
{
	return (X * other.X) + (Y * other.Y) + (Z * other.Z);
}

void Vector4::SetVector(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

void Vector4::SetZero()
{
	*this = origin;
}

