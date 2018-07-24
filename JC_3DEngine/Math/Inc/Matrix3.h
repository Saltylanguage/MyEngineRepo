#pragma once
#include "Vector3.h"

namespace Math
{

	class Matrix3
	{
	public:

		inline Matrix3() {}
		inline ~Matrix3() {}

		//copy and assignment
		Matrix3(const Matrix3& other);
		Matrix3& operator=(const Matrix3& other);

		//accessor
		inline float& operator()(size_t i, size_t j);
		inline float operator()(size_t i, size_t j) const;

		//comparison
		bool operator==(const Matrix3& other) const;
		bool operator!=(const Matrix3& other) const;
		bool IsZero() const;
		bool IsIdentityMatrix() const;

		Matrix3& Transpose();	//Set self to transpose

								//manipulators
		void SetRows(const Vector3& row1, const Vector3& row2, const Vector3& row3);
		void GetRows(Vector3& row1, Vector3& row2, Vector3& row3) const;
		Vector3 GetRow(size_t i) const;

		void SetColumns(const Vector3& column1, const Vector3& column2, const Vector3& column);
		void GetColumns(Vector3& column1, Vector3& column2, Vector3& column) const;
		Vector3 GetColumn(size_t i) const;

		void Clean();	 //Set near-zero elements to 0
		void Identity(); //Set to identity matrix

						 //transformations
		Matrix3& Rotation(float xRotation, float yRotation, float zRotation);
		Matrix3& Scaling(const Vector3& scale);

		Matrix3& Translation(const float translateX, const float translateY);
		Matrix3& Shear(const float shearX, const float shearY);

		Matrix3& RotationX(float angle);
		Matrix3& RotationY(float angle);
		Matrix3& RotationZ(float angle);

		//operators

		//addition and subtraction
		Matrix3 operator+(const Matrix3& other) const;
		Matrix3& operator+=(const Matrix3& other);
		Matrix3 operator-(const Matrix3& other) const;
		Matrix3& operator-=(const Matrix3& other);

		//Negative
		Matrix3 operator-() const;

		//multiplication
		Matrix3 operator*(const Matrix3& other) const;
		Matrix3& operator*=(const Matrix3& other);

		//column vector multiplier
		Vector3 operator*(const Vector3& vector) const;
		//row vector multiplier
		friend Vector3 operator*(const Vector3& vector, const Matrix3 matrix);

		//scalar
		Matrix3 operator*(const float scalar) const;
		Matrix3& operator*=(const float scalar);

		float matrix[9];
	};

	inline float& Matrix3::operator()(size_t i, size_t j)
	{
		return matrix[i + (3 * j)];
	}
	inline float Matrix3::operator()(size_t i, size_t j) const
	{
		return matrix[i + (3 * j)];
	}


}