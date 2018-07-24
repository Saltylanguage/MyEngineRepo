#include "Precompiled.h"
#include "Vector3.h"
#include <math.h>

using namespace Math;


//copy constructor
Vector3::Vector3(const Vector3& other) : X(other.X), Y(other.Y), Z(other.Z) {}
//end of copy constructor

//assignment operator
Vector3& Vector3::operator=(const Vector3& other)
{
	if (this == &other)
	{
		return *this;
	}
	X = other.X;
	Y = other.Y;
	Z = other.Z;

	return *this;
}

//calculate distance functions
float Distance(const Vector3 & point1, const Vector3 & point2)
{
	float x = point1.X - point2.X;
	float y = point1.Y - point2.Y;
	float z = point1.Z - point2.Z;

	return sqrtf(x*x + y*y + z*z);
}

float DistanceSquared(const Vector3 & point1, const Vector3 & point2)
{
	float x = point1.X - point2.X;
	float y = point1.Y - point2.Y;
	float z = point1.Z - point2.Z;

	return (x*x + y*y + z*z);
}
//end of distance functions

float Math::Vector3::Abs(float value)
{
	return value < 0 ? value * -1 : value;
}

//comparison
bool Vector3::operator==(const Vector3& other) const
{
	if (X == other.X && Y == other.Y && Z == other.Z)
	{
		return true;
	}
	return false;
}

bool Vector3::operator!=(const Vector3& other) const
{
	if (X != other.X || Y != other.Y || Z != other.Z)
	{
		return true;
	}
	return false;
}
bool Math::Vector3::IsZero(Math::Vector3 vec) const
{
	return vec.X == 0.0f && vec.Y == 0.0f && vec.Z == 0.0f;
}
bool Math::Vector3::IsUnit() const
{
	return this->X == 1.0f && this->Y == 1.0f && this->Z == 1.0f;
}
//end of comparison

//negative operator
Vector3 Vector3::operator-() const
{
	return Vector3(-X, -Y, -Z);
}

//addition/subtraction
Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}
Vector3& Math::operator+=(Vector3& vector, const Vector3& other)
{
	vector.X += other.X;
	vector.Y += other.Y;
	vector.Z += other.Z;

	return vector;
}

Vector3 Vector3::operator-(const Vector3& other)const
{
	return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}
Vector3& Math::operator-=(Vector3& vector, const Vector3& other)
{
	vector.X -= other.X;
	vector.Y -= other.Y;
	vector.Z -= other.Z;

	return vector;
}

Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(X * scalar, Y * scalar, Z * scalar);
}
Vector3& Vector3::operator*=(const float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;

	return *this;
}

Vector3 Vector3::operator/(const float scalar) const
{
	return Vector3(X / scalar, Y / scalar, Z / scalar);
}
Vector3& Vector3::operator/=(const float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;

	return *this;
}

//useful vector functions
float Vector3::Length() const
{
	return sqrt(LengthSquared());
}

inline float Vector3::LengthSquared() const
{
	return (X*X) + (Y*Y) + (Z*Z);
}

Vector3 Vector3::Normalize(Vector3 vec)
{

	float length = vec.Length();

	if (length == 0.0f)
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}
	return Vector3
	(
		vec.X / length,
		vec.Y / length,
		vec.Z / length
	);

}

Vector3 Normalized(Vector3 vec)
{
	Vector3 ret;
	float magnitude = sqrtf((vec.X * vec.X) + (vec.Y * vec.Y) + (vec.Z * vec.Z));

	ret.X = vec.X / magnitude;
	ret.Y = vec.Y / magnitude;
	ret.Z = vec.Z / magnitude;

	return ret;

}

float Vector3::Dot(const Vector3 & vector) const
{
	return X * vector.X + Y*vector.Y + Z*vector.Z;
}

Vector3 Vector3::Cross(const Vector3 & vector) const
{
	Vector3 ret;

	ret.X = (Y * vector.Z) - (Z * vector.Y);
	ret.Y = (Z * vector.X) - (X * vector.Z);
	ret.Z = (X * vector.Y) - (Y * vector.X);

	return ret;
}
