#pragma once

namespace Math
{
	class Vector2
	{
	public:

		Vector2() : x(0), y(0)
		{}
		Vector2(float a, float b) : x(a), y(b)
		{}

		float x;
		float y;

		static Vector2 xAxis;
		static Vector2 yAxis;
		static Vector2 zero;
		static Vector2 unit;

		inline void Set(float X, float Y);
		void Clean();
		inline void MakeZero();
		void Normalize();

		float Length() const;
		float LengthSquared() const;

		//Comparison
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		bool IsZero() const;

		//Math Operators
		Vector2 operator+(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2 operator-(const Vector2& other) const;
		Vector2& operator-=(const Vector2& other);
		Vector2 operator*(const float scalar) const;
		Vector2& operator*=(const float scalar);
		Vector2 operator/(const float scalar) const;;
		Vector2& operator/=(const float scalar);

		float dot(const Vector2& other) const;

		Vector2 Perpendicular() const { return Vector2(-y, x); }
		float Cross(const Vector2& vector) const;

		//static Vector2 CalculateUV(Vector3 pos);

	};
}