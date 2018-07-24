#include "Precompiled.h"
#include "Math\Inc\Vector2.h"
#include <cmath>



#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))

using namespace Math;

Vector2 Vector2::xAxis(1.0f, 0.0f);
Vector2 Vector2::yAxis(0.0f, 1.0f);
Vector2 Vector2::origin(0.0f, 0.0f);
Vector2 Vector2::XY(1.0f, 1.0f);

float Vector2::Length() const
{
	return sqrtf(x*x + y*y);
}

float Vector2::LengthSquared() const
{
	return (x*x + y*y);
}

//OPERATORS

//comparison
bool Vector2::operator==(const Vector2& other)const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2& other) const
{
	if (x != other.x || y != other.y)
	{
		return true;
	}
	return false;
}

bool Vector2::isZero() const
{
	if (x == 0 && y == 0)
	{
		return true;
	}
	return false;
}

//addition & subtraction
Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}
Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}
Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}
Vector2& Vector2::operator-=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

// scalar multiplication & division
Vector2 Vector2::operator*(const float scalar)
{
	return Vector2(scalar*x, scalar*y);
}
Vector2& Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}
Vector2 Vector2::operator/(const float scalar)
{
	return Vector2(x / scalar, y / scalar);
}
Vector2& Vector2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}
//end of Operators

//manipulators
inline void Vector2::Set(float x, float y)
{
	x = x;
	y = y;
}
void Vector2::Clean()
{
	if (abs(x) < 0.1)
	{
		x = 0;
	}
	if (abs(y) < 0.1)
	{
		y = 0;
	}
}
void Vector2::Zero()
{
	x = 0.0f;
	y = 0.0f;
}
void Vector2::Normalize()
{
	float lengthSq = x*x + y*y;

	float factor = 1.0f / sqrtf(lengthSq);
	x *= factor;
	y *= factor;
}
//end of manipulators

//dot product
float Vector2::dot(const Vector2& vector) const
{
	return (x*vector.x + y*vector.y);
}

//cross product


//UV

Vector2 Vector2::CalculateUV(Vector3 pos)
{

	Vector3 point = Vector3::Normalize(pos);

	// using spherical coords
	// a is the angle from z axis [0, pi]
	// t is the angle from x-axis [0, 2pi]
	float a, t;
	float pi = 3.14159f;

	a = acosf(point[2]);
	float temp = sin(a);

	// check for poles

	if (abs(temp) < 0.001f)
	{
		t = 0.0;
	}
	else
	{
		float temp2 = point[0] / temp;

		// clamp to [-1, 1] - due to small numerical errors
		temp2 = min(max(temp2, -1.0f), 1.0f);
		t = acosf(temp2);

		if (point[1] < 0.0f)
		{
			t = 2.0f * pi - t;
		}
	}
	// convert to [0, 1]
	float v = 1.0f - a / pi;
	float u = t / (2.0f * pi);

	return Vector2(u, v);
}













