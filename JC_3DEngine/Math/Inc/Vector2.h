#pragma once
#include "Vector3.h"

namespace Math
{

	class Vector2
	{
	public:

		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float x, float y) : x(x), y(y) {}
		~Vector2() {};

		// members
		float x;
		float y;
		//static members
		static Vector2 xAxis;
		static Vector2 yAxis;
		static Vector2 origin;
		static Vector2 XY;

		//accessors
		inline float& operator[] (size_t i) { return(&x)[i]; }
		inline float operator[] (size_t i) const { return (&x)[i]; }

		float Length() const;
		float LengthSquared() const;

		//comparison
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		bool isZero() const;

		//manipulator
		inline void Set(float x, float y);
		void Clean();		//sets near-zero elements to zero
		inline void Zero();		//sets all elements to zero
		void Normalize();	// sets to unit vector

							//addition/subtraction
		Vector2 operator+(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2 operator-(const Vector2& other) const;
		Vector2& operator-=(const Vector2& other);

		//scalar multiplication
		Vector2 operator*(const float scalar);
		Vector2& operator*=(const float scalar);
		Vector2 operator/(const float scalar);
		Vector2& operator/=(const float scalar);

		//dot product
		float dot(const Vector2& vector) const;

		//Perpendicular and Cross Product Equivalent
		Vector2 Perpendicular() const { return Vector2(-y, x); }
		float Cross(const Vector2& vector) const;

		//UV
		static Vector2 CalculateUV(Vector3 pos);

	private:

	};
};
