#include "Precompiled.h"
#include "Vector2.h"
#include <math.h>

using namespace Math;

Vector2 Vector2::xAxis(1.0f, 0.0f);
Vector2 Vector2::yAxis(0.0f, 1.0f);
Vector2 Vector2::origin(0.0f, 0.0f);
Vector2 Vector2::XY(1.0f, 1.0f);

float Vector2::Length() const
{
	return sqrtf(X*X + Y*Y);
}

float Vector2::LengthSquared() const
{
	return (X*X + Y*Y);
}

//OPERATORS

//comparison
bool Vector2::operator==(const Vector2& other)const
{
	if (X == other.X && Y == other.Y)
	{
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2& other) const
{
	if (X != other.X || Y != other.Y)
	{
		return true;
	}
	return false;
}

bool Vector2::isZero() const
{
	if (X == 0 && Y == 0)
	{
		return true;
	}
	return false;
}

//addition & subtraction
Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(X + other.X, Y + other.Y);
}
Vector2& Vector2::operator+=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;

	return *this;
}
Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(X - other.X, Y - other.Y);
}
Vector2& Vector2::operator-=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;

	return *this;
}

// scalar multiplication & division
Vector2 Vector2::operator*(const float scalar)
{
	return Vector2(scalar*X, scalar*Y);
}
Vector2& Vector2::operator*=(const float scalar)
{
	X *= scalar;
	Y *= scalar;

	return *this;
}
Vector2 Vector2::operator/(const float scalar)
{
	return Vector2(X / scalar, Y / scalar);
}
Vector2& Vector2::operator/=(const float scalar)
{
	X /= scalar;
	Y /= scalar;

	return *this;
}
//end of Operators

//manipulators
inline void Vector2::Set(float x, float y)
{
	X = x;
	Y = y;
}
void Vector2::Clean()
{
	if (abs(X) < 0.1)
	{
		X = 0;
	}
	if (abs(Y) < 0.1)
	{
		Y = 0;
	}
}
void Vector2::Zero()
{
	X = 0.0f;
	Y = 0.0f;
}
void Vector2::Normalize()
{
	float lengthSq = X*X + Y*Y;

	float factor = 1.0f / sqrtf(lengthSq);
	X *= factor;
	Y *= factor;
}
//end of manipulators

//dot product
float Vector2::dot(const Vector2& vector) const
{
	return (X*vector.X + Y*vector.Y);
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













