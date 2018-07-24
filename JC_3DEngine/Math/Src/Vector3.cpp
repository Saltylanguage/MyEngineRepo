#include "Precompiled.h"
#include "Math\Inc\Vector3.h"


using namespace Math;


//copy constructor
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
//end of copy constructor

//assignment operator
Vector3& Vector3::operator=(const Vector3& other)
{
	if (this == &other)
	{
		return *this;
	}
	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

//calculate distance functions
float Distance(const Vector3 & point1, const Vector3 & point2)
{
	float x = point1.x - point2.x;
	float y = point1.y - point2.y;
	float z = point1.z - point2.z;

	return sqrtf(x*x + y*y + z*z);
}

float DistanceSquared(const Vector3 & point1, const Vector3 & point2)
{
	float x = point1.x - point2.x;
	float y = point1.y - point2.y;
	float z = point1.z - point2.z;

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
	if (x == other.x && y == other.y && z == other.z)
	{
		return true;
	}
	return false;
}

bool Vector3::operator!=(const Vector3& other) const
{
	if (x != other.x || y != other.y || z != other.z)
	{
		return true;
	}
	return false;
}
bool Math::Vector3::IsZero(Math::Vector3 vec) const
{
	return vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f;
}
bool Math::Vector3::IsUnit() const
{
	return this->x == 1.0f && this->y == 1.0f && this->z == 1.0f;
}
//end of comparison

//negative operator
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

//addition/subtraction
Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x  + other.x, y + other.y, z + other.z);
}
Vector3& Math::operator+=(Vector3& vector, const Vector3& other)
{
	vector.x += other.x;
	vector.y += other.y;
	vector.z += other.z;

	return vector;
}

Vector3 Vector3::operator-(const Vector3& other)const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3& Math::operator-=(Vector3& vector, const Vector3& other)
{
	vector.x -= other.x;
	vector.y -= other.y;
	vector.z -= other.z;

	return vector;
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

//useful vector functions
float Vector3::Length() const
{
	return sqrt(LengthSquared());
}

inline float Vector3::LengthSquared() const
{
	return (x*x) + (y*y) + (z*z);
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
		vec.x / length,
		vec.y / length,
		vec.z / length
	);

}

Vector3 Normalized(Vector3 vec)
{
	Vector3 ret;
	float magnitude = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

	ret.x = vec.x / magnitude;
	ret.y = vec.y / magnitude;
	ret.z = vec.z / magnitude;

	return ret;

}

float Vector3::Dot(const Vector3 & vector) const
{
	return x * vector.x + y*vector.y + z*vector.z;
}

Vector3 Vector3::Cross(const Vector3 & vector) const
{
	Vector3 ret;

	ret.x = (y * vector.z) - (z * vector.y);
	ret.y = (z * vector.x) - (x * vector.z);
	ret.z = (x * vector.y) - (y * vector.x);


	return ret;
}
