#pragma once

namespace Math
{
	class Vector3
	{
	public:
		Vector3() : x(0.0f), y(0.0f), z(0.0f)
		{}
		Vector3(float a, float b, float c) : x(a), y(b), z(c)
		{}

		float x;
		float y;
		float z;

		static Vector3 xAxis;
		static Vector3 yAxis;
		static Vector3 zAxis;
		static Vector3 zero;
		static Vector3 unit;

		void inline Set(float a, float b, float c);
		void Clean();
		void inline MakeZero();
		void Normalize();

		float Length() const;
		float LengthSquared() const;

		//Comparison
		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;
		bool IsZero() const;

		//Math Operators
		Vector3 operator+(const Vector3& other) const;
		Vector3& operator+=(const Vector3& other);
		Vector3 operator-(const Vector3& other) const;
		Vector3& operator-=(const Vector3& other);
		Vector3 operator*(const float scalar) const;
		Vector3& operator*=(const float scalar);
		Vector3 operator/(const float scalar) const;
		Vector3& operator/=(const float scalar);

		float dot(const Vector3& other) const;
		Vector3 Perpendicular() const;
	};
}