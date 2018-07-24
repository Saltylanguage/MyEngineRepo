#pragma once

namespace Math
{
	class Quaternion;
	class Vector3;
	class Matrix
	{
	public:

		float matrix[16];

		//custom constructor
		Matrix() {};
		Matrix(float values[16]);

		Matrix(float element11, float element12, float element13, float element14,
			float element21, float element22, float element23, float element24,
			float element31, float element32, float element33, float element34,
			float element41, float element42, float element43, float element44
		);
		~Matrix() {}

		static Matrix Zero();
		static Matrix Identity();
		static Matrix Translation(float x, float y, float z);
		static Matrix Translation(const Vector3& v);
		static Matrix RotationX(const Vector3& axis, float rad);
		static Matrix RotationY(float rad);
		static Matrix RotationZ(float rad);
		static Matrix Scaling(float s);
		static Matrix Scaling(float sx, float sy, float sz);
		static Matrix Scaling(const Vector3& s);

		//copy and assignment
		Matrix(const Matrix& other);
		Matrix& operator=(const Matrix& other);

		//comparison
		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;

		bool IsZero() const;
		bool IsIdentity() const;

		void Clean();


		//Matrix& AffineInverse();

		static Matrix Transpose(const Matrix& mat);
		Matrix MakeTranspose(const Matrix& mat);

		float Determinant() const;
		static Matrix Adjoint(const Matrix& mat);
		static Matrix Inverse(const Matrix& mat);

		//Rotation
		static Matrix RotationAxis(const Vector3& axis, float rad);

		static Matrix RotationQuaternion(const Quaternion& q);

		static Matrix RotateX(const float angle);
		static Matrix RotateY(const float angle);
		static Matrix RotateZ(const float angle);

		//Make a Scale matrix from a Vector3
		static Matrix MakeScaleMatrix(const Vector3& scale);

		Matrix Scale(const Vector3& scale);

		void GetFixedAngles(float& xRotation, float& yRotation, float& zRotation);
		void GetAxisAngle(Vector3& axis, float& angle);

		//OPERATORS:
		//addition and subtraction
		Matrix operator+(const Matrix& other) const;
		Matrix operator+=(const Matrix& other);
		Matrix operator-(const Matrix& other) const;
		Matrix operator-=(const Matrix& other);

		Matrix operator-() const;

		//matrix multiplication
		Matrix operator*(const Matrix& other) const;
		Matrix operator*=(const Matrix& other);

		//scalar multiplication
		Matrix operator*(const float scalar);
		Matrix operator*=(const float scalar);

		//point ops
		Vector3 TransformPoint(const Vector3& point) const;



	};
}