#pragma once
#include "Vector3.h"

namespace Math
{

	class Vector2
	{
	public:

		Vector2() : X(0.0f), Y(0.0f) {}
		Vector2(float x, float y) : X(x), Y(y) {}
		~Vector2() {};

		// members
		float X;
		float Y;
		//static members
		static Vector2 xAxis;
		static Vector2 yAxis;
		static Vector2 origin;
		static Vector2 XY;

		//accessors
		inline float& operator[] (size_t i) { return(&X)[i]; }
		inline float operator[] (size_t i) const { return (&X)[i]; }

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
		Vector2 Perpendicular() const { return Vector2(-Y, X); }
		float Cross(const Vector2& vector) const;

		//UV
		static Vector2 CalculateUV(Vector3 pos);

	private:

	};
};
