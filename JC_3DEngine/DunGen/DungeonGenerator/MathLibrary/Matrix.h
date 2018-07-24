#pragma once
#include "Vector3.h"

namespace Math
{
	class Matrix
	{
	public:
		float data[16];

		Matrix()
		{
			data[16] = { 0 };
		};

		Matrix(float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33)
		{
			data[0] = _00;		data[1] = _01;		data[2] = _02;		data[3] = _03;
			data[4] = _10;		data[5] = _11;		data[6] = _12;		data[7] = _13;
			data[8] = _20;		data[9] = _21;		data[10] = _22;		data[11] = _23;
			data[12] = _30;		data[13] = _31;		data[14] = _32;		data[15] = _33;
		}

		//Copy Constructor and Assignment
		Matrix(const Matrix& other);
		Matrix& operator=(const Matrix& other);

		//Setting and Resetting
		void Set(float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33);
		void Clean();
		void MakeZero();

		//Comparison
		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;
		bool IsZero() const;
		bool IsIdentity() const;

		//Math Operators
		Matrix operator+(const Matrix& other) const;
		Matrix& operator+=(const Matrix& other);
		Matrix operator-(const Matrix& other) const;
		Matrix& operator-=(const Matrix& other);

		//Matrix Multiplication
		Matrix operator*(const Matrix& other) const;
		Matrix& operator*=(const Matrix& other);

		// Scalar Multiplication
		Matrix operator*(const float scalar) const;
		Matrix operator*=(const float scalar);


		//Static Declarations
		static Matrix Zero();
		static Matrix Identity();
		
		static Matrix Translation(const float x, const float y, const float z);
		static Matrix Translation(const Vector3& vec);
		
		static Matrix RotationX(const Vector3& axis, const float rad);
		static Matrix RotationY(const Vector3& axis, const float rad);
		static Matrix RotationZ(const Vector3& axis, const float rad);
		static Matrix RotationAxis(const Vector3& axis, float rad);
		//static Matrix RotationQuaternion(const Quaternion& qaut);
		
		static Matrix Scaling(const float scaleFactor);
		static Matrix Scaling(const float x, const float y, const float z);
		static Matrix Scaling(const Vector3& scaleValues);
		static Matrix MakeScaleMatrix(const Vector3& scale);
		
		static Matrix Transpose(const Matrix& mat);
		static Matrix Adjoint(const Matrix& mat);
		static Matrix Inverse(const Matrix& mat);

		//Matrix Math

		Matrix Scale(const Vector3& scale);
		//void GetFixedAngles(float& xRotation, float& yRotation, float& zRotation);
		//void GetAxisAngle(Vector3& axis, float& angle);
		float Determinant() const;
		Vector3 TransformPoint(const Vector3& point) const;
	};
}