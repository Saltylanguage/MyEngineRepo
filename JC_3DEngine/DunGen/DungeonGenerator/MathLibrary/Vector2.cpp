#include "Vector2.h"

#include <cmath>
#include <algorithm>

using namespace Math;

Vector2 Vector2::xAxis(1.0f, 0.0f);
Vector2 Vector2::yAxis(0.0f, 1.0f);
Vector2 Vector2::unit(1.0f, 1.0f);
Vector2 Vector2::zero(0.0f, 0.0f);

bool Vector2::operator==(const Vector2 & other) const
{
	if (x != other.x || y != other.y)
	{
		return false;
	}
	return true;
}

bool Vector2::operator!=(const Vector2 & other) const
{
	if (x == other.x || y == other.y)
	{
		return false;
	}
	return true;
}

bool Vector2::IsZero() const
{
	if (x == 0.0f && y == 0.0f)
	{
		return true;
	}
	return false;
}

Vector2 Vector2::operator+(const Vector2 & other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2 & other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2 & other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2 & other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 &Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

Vector2& Vector2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

float Vector2::dot(const Vector2 & other) const
{
	return x*other.x + y*other.y;
}

float Vector2::Length()const
{
	return sqrtf(x*x + y*y);
}

float Vector2::LengthSquared() const
{
	return x*x + y*y;
}

inline void Vector2::Set(float X, float Y)
{
	x = X;
	y = Y;
}

void Vector2::Clean()
{
	if (abs(x) < 0.1f)
	{
		x = 0.0f;
	}
	if (abs(y) < 0.1f)
	{
		y = 0.0f;
	}
}

inline void Vector2::MakeZero()
{
	x = 0.0f;
	y = 0.0f;
}

void Vector2::Normalize()
{
	float factor = 1.0f / Length();

	x *= factor;
	y *= factor;
}


