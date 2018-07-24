#pragma once
#include "Matrix.h"
#include <cmath>

namespace Math
{
	enum MatrixIndex { _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44, matrixMax };

	class Vector3
	{
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		//copy constructors
		Vector3(const Vector3& other);
		Vector3& operator=(const Vector3& other);


		static Vector3 Zero() { return Vector3(); }
		static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }
		static Vector3 XAxis() { return Vector3(1.0f, 0.0f, 0.0f); }
		static Vector3 YAxis() { return Vector3(0.0f, 1.0f, 0.0f); }
		static Vector3 ZAxis() { return Vector3(0.0f, 0.0f, 1.0f); }

		inline ~Vector3() {};

		//member variables
		float x;
		float y;
		float z;
		//end of member variables

		float Abs(float value);

		inline float& operator[](size_t i) { return (&x)[i]; }
		inline float operator[](size_t i) const { return (&x)[i]; }

		inline float Sqrt(float value) { return sqrtf(value); }

		inline float MagnitudeSqr(const Vector3& v) { return (v.x * v.x) + (v.y * v.y) + (v.z * v.z); }
		inline float Magnitude(const Vector3& v) { return Sqrt(MagnitudeSqr(v)); }
		static inline float MagnitudeXZSqr(const Vector3& v) { return (v.x * v.x) + (v.z * v.z); } // TODO:: Check with Pchan. Should/Can this be static.
		inline float MagnitudeXZ(const Vector3& v) { return Sqrt(MagnitudeXZSqr(v)); }



		inline float DistanceSqr(const Vector3& a, const Vector3& b) { return MagnitudeSqr(a - b); }
		inline float Distance(const Vector3& a, const Vector3& b) { return Sqrt(DistanceSqr(a, b)); }
		static inline float DistanceXZSqr(const Vector3& a, const Vector3& b) { return MagnitudeXZSqr(a - b); } // TODO:: Check with Pchan. Should/Can this be static.
		inline float DistanceXZ(const Vector3& a, const Vector3& b) { return Sqrt(DistanceXZSqr(a, b)); }

		static inline float Dot(const Vector3& a, const Vector3& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }
		//inline Vector3 Cross(const Vector3& a, const Vector3& b) { return Vector3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)); }
		static inline Vector3 Cross(const Vector3& a, const Vector3& b) { return Vector3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)); }
		inline Vector3 Project(const Vector3& v, const Vector3& n) { return n * (Dot(v, n) / Dot(n, n)); }
		inline Vector3 Reflect(const Vector3& v, const Vector3& normal) { return v - (normal * Dot(v, normal) * 2.0f); }

		//Comparison Operators
		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;
		bool IsZero(Vector3 vec) const;
		bool IsUnit() const;

		//manipulators
		inline void Set(float x, float y, float z);
		void Clean(); //sets near-zero elements to 0
		inline void SetZero() { x = 0; y = 0; z = 0; };

		//Addition/Subtraction Operators
		Vector3 operator+(const Vector3& other) const;
		friend Vector3& operator+=(Vector3& vec, const Vector3& other);
		Vector3 operator-(const Vector3& other) const;
		friend Vector3& operator-=(Vector3& vec, const Vector3& other);

		Vector3 operator-() const; //negative vector

								   //Scalar Mulitplication/Division
		Vector3 operator*(const float scalar) const;
		Vector3& operator*=(const float scalar);
		Vector3 operator/(const float scalar) const;
		Vector3& operator/=(const float scalar);

		//useful defaults (static members)
		static Vector3 origin;

		static inline Vector3 TransformCoord(const Vector3& v, const Matrix& m)
		{
			return Vector3
			(
				v.x * m.matrix[_11] + v.y *  m.matrix[_21] + v.z * m.matrix[_31] + m.matrix[_41],
				v.x * m.matrix[_12] + v.y * m.matrix[_22] + v.z * m.matrix[_32] + m.matrix[_42],
				v.x * m.matrix[_13] + v.y * m.matrix[_23] + v.z * m.matrix[_33] + m.matrix[_43]
			);
		}

		static inline Vector3 TransformNormal(const Vector3& v, const Matrix& m)
		{
			return Vector3
			(
				v.x * m.matrix[_11] + v.y * m.matrix[_21] + v.z * m.matrix[_31],
				v.x * m.matrix[_12] + v.y * m.matrix[_22] + v.z * m.matrix[_32],
				v.x * m.matrix[_13] + v.y * m.matrix[_23] + v.z * m.matrix[_33]
			);
		}

		//Useful Vector Functions
		float Length() const;
		inline float LengthSquared() const;

		static Vector3 Normalize(Vector3 vec);
		Vector3 Normalized(Vector3 vec);

		float Dot(const Vector3& vector) const;
		Vector3 Cross(const Vector3& vector) const;

		static Vector3 Lerp(const Vector3& start, const Vector3& end, float t) { return start + (end - start) * t; }

		//Perpendicular and Cross Product Equivalent
		Vector3 Perpendicular() const { return Vector3(); }
	};



	inline void Vector3::Set(float x, float y, float z)
	{
		x = x;
		y = y;
		z = z;
	}



}