#include "Precompiled.h"
#include <math.h>
#include "Matrix3.h"
#include "Vector3.h"

using namespace Math;

enum MatrixIndex { _11, _12, _13, _21, _22, _23, _31, _32, _33, matrixMax };

//copy constructor
Matrix3::Matrix3(const Matrix3& other)
{
	matrix[0] = other.matrix[0];
	matrix[1] = other.matrix[1];
	matrix[2] = other.matrix[2];
	matrix[3] = other.matrix[3];
	matrix[4] = other.matrix[4];
	matrix[5] = other.matrix[5];
	matrix[6] = other.matrix[6];
	matrix[7] = other.matrix[7];
	matrix[8] = other.matrix[8];

}

Matrix3& Matrix3::operator=(const Matrix3& other)
{

	if (this == &other)
	{
		return *this;
	}

	matrix[0] = other.matrix[0];
	matrix[1] = other.matrix[1];
	matrix[2] = other.matrix[2];
	matrix[3] = other.matrix[3];
	matrix[4] = other.matrix[4];
	matrix[5] = other.matrix[5];
	matrix[6] = other.matrix[6];
	matrix[7] = other.matrix[7];
	matrix[8] = other.matrix[8];

	return *this;
}

bool Matrix3::operator==(const Matrix3& other)const
{

	for (size_t i = 0; i < matrixMax; i++)
	{
		if (!(matrix[i] == other.matrix[i]))
		{
			return false;
		}
	}
	return true;
}

bool Matrix3::operator!=(const Matrix3& other) const
{
	for (size_t i = 0; i < matrixMax; i++)
	{
		if (matrix[i] == other.matrix[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix3::IsZero() const
{
	for (size_t i = 0; i < matrixMax; i++)
	{
		if (matrix[i] != 0)
		{
			return false;
		}
	}
	return true;
}

void Matrix3::SetRows(const Vector3& row1, const Vector3& row2, const Vector3& row3)
{
	matrix[_11] = row1.X;
	matrix[_12] = row1.Y;
	matrix[_13] = row1.Z;

	matrix[_21] = row1.X;
	matrix[_22] = row1.Y;
	matrix[_23] = row1.Z;

	matrix[_31] = row1.X;
	matrix[_32] = row1.Y;
	matrix[_32] = row1.Z;
}

void Matrix3::GetRows(Vector3& row1, Vector3& row2, Vector3& row3) const
{
	row1.X = matrix[_11];
	row1.Y = matrix[_12];
	row1.Z = matrix[_13];

	row2.X = matrix[_21];
	row2.Y = matrix[_22];
	row2.Z = matrix[_23];

	row3.X = matrix[_31];
	row3.Y = matrix[_32];
	row3.Z = matrix[_32];
}

Vector3 Matrix3::GetRow(size_t i) const
{
	return Vector3(matrix[3 * i], matrix[3 * i + 1], matrix[3 * i + 2]);
}


void Matrix3::SetColumns(const Vector3& column1, const Vector3& column2, const Vector3& column3)
{
	matrix[_11] = column1.X;
	matrix[_21] = column1.Y;
	matrix[_31] = column1.Z;

	matrix[_12] = column2.X;
	matrix[_22] = column2.Y;
	matrix[_32] = column2.Z;

	matrix[_13] = column3.X;
	matrix[_23] = column3.Y;
	matrix[_33] = column3.Z;
}

void Matrix3::GetColumns(Vector3& column1, Vector3& column2, Vector3& column3) const
{
	column1.X = matrix[_11];
	column1.Y = matrix[_21];
	column1.Z = matrix[_31];

	column2.X = matrix[_12];
	column2.Y = matrix[_22];
	column2.Z = matrix[_32];

	column3.X = matrix[_13];
	column3.Y = matrix[_23];
	column3.Z = matrix[_33];
}

Vector3 Matrix3::GetColumn(size_t i) const
{
	return Vector3(matrix[i], matrix[i + 3], matrix[i + 6]);
}

void Matrix3::Clean()
{
	for (size_t i = 0; i < matrixMax; i++)
	{
		if (matrix[i] < 0.1f)
		{
			matrix[i] = 0;
		}
	}
}

bool Matrix3::IsIdentityMatrix() const
{
	return (matrix[_11] == 1 && matrix[_12] == 0 && matrix[_13] == 0 &&
		matrix[_21] == 0 && matrix[_22] == 1 && matrix[_23] == 0 &&
		matrix[_31] == 0 && matrix[_32] == 0 && matrix[_33] == 1);
}

void Matrix3::Identity()
{
	matrix[_11] = 1; matrix[_12] = 0; matrix[_13] = 0;
	matrix[_21] = 0; matrix[_22] = 1; matrix[_23] = 0;
	matrix[_31] = 0; matrix[_32] = 0; matrix[_33] = 1;
}

Matrix3& Matrix3::Transpose()
{
	float temp;
	temp = matrix[_12]; matrix[_12] = matrix[_21]; matrix[_21] = temp;
	temp = matrix[_13]; matrix[_13] = matrix[_31]; matrix[_31] = temp;
	temp = matrix[_23]; matrix[_23] = matrix[_32]; matrix[_32] = temp;

	return *this;
}

//Transformations
Matrix3& Matrix3::Rotation(float xRotation, float yRotation, float zRotation)
{
	float cosX = cosf(xRotation);
	float sinX = sinf(xRotation);
	float cosY = cosf(yRotation);
	float sinY = sinf(yRotation);
	float cosZ = cosf(zRotation);
	float sinZ = sinf(zRotation);

	matrix[_11] = (cosY * cosZ);								matrix[_12] = -(cosY * sinZ);									matrix[_13] = -(sinY);
	matrix[_21] = -(sinX * sinY * cosZ) + (cosX * sinZ);		matrix[_22] = (sinX * sinY * sinZ) + (cosX * cosZ); 			matrix[_23] = -(sinX * cosY);
	matrix[_31] = (cosX * sinY * cosZ) + (sinX * sinZ);			matrix[_32] = -(cosX * sinY * sinZ) + (sinX * cosZ); 			matrix[_33] = (cosX * cosY);

	return *this;
}

Matrix3& Matrix3::Scaling(const Vector3& scale)
{
	matrix[_11] = scale.X;		matrix[_12] = 0;			matrix[_13] = 0;
	matrix[_21] = 0;			matrix[_22] = scale.Y;		matrix[_23] = 0;
	matrix[_31] = 0;			matrix[_32] = 0;			matrix[_33] = scale.Z;

	return *this;
}

Matrix3& Matrix3::Translation(float translateX, float translateY)
{
	matrix[_11] = 1;			matrix[_12] = 0;			matrix[_13] = translateX;
	matrix[_21] = 0;			matrix[_22] = 1;			matrix[_23] = translateY;
	matrix[_31] = 0;			matrix[_32] = 0;			matrix[_33] = 1;

	return *this;
}

Matrix3& Matrix3::Shear(float shearX, float shearY)
{
	matrix[_11] = 1;			matrix[_12] = shearX;		matrix[_13] = 0;
	matrix[_21] = shearY;		matrix[_22] = 1;			matrix[_23] = 0;
	matrix[_31] = 0;			matrix[_32] = 0;			matrix[_33] = 1;

	return *this;
}

Matrix3& Matrix3::RotationX(float angle)
{
	matrix[_11] = 1;			matrix[_12] = 0;				matrix[_13] = 0;
	matrix[_21] = 0;			matrix[_22] = cosf(angle);		matrix[_23] = (sinf(angle));
	matrix[_31] = 0;			matrix[_32] = -sinf(angle);		matrix[_33] = cosf(angle);

	return *this;
}

Matrix3& Matrix3::RotationY(float angle)
{
	matrix[_11] = cosf(angle);		matrix[_12] = 0;			matrix[_13] = -(sinf(angle));
	matrix[_21] = 0;				matrix[_22] = 1;			matrix[_23] = 0;
	matrix[_31] = sinf(angle);		matrix[_32] = 0;			matrix[_33] = cosf(angle);

	return *this;
}

Matrix3& Matrix3::RotationZ(float angle)
{
	matrix[_11] = cosf(angle);			matrix[_12] = sinf(angle);		matrix[_13] = 0;
	matrix[_21] = -(sinf(angle));		matrix[_22] = cosf(angle);		matrix[_23] = 0;
	matrix[_31] = 0;					matrix[_32] = 0;				matrix[_33] = 1;

	return *this;
}
//end of Transformations

//Operators
Matrix3 Matrix3::operator+(const Matrix3& other) const
{
	Matrix3 ret;

	for (size_t i = 0; i < matrixMax; i++)
	{
		ret.matrix[i] = matrix[i] + other.matrix[i];
	}
	return ret;
}

Matrix3& Matrix3::operator+=(const Matrix3& other)
{
	for (size_t i = 0; i < matrixMax; i++)
	{
		matrix[i] += other.matrix[i];
	}
	return *this;
}

Matrix3 Matrix3::operator-(const Matrix3& other) const
{
	Matrix3 ret;

	for (size_t i = 0; i < matrixMax; i++)
	{
		ret.matrix[i] = matrix[i] - other.matrix[i];
	}
	return ret;
}

Matrix3& Matrix3::operator-=(const Matrix3& other)
{
	for (size_t i = 0; i < matrixMax; i++)
	{
		matrix[i] -= other.matrix[i];
	}
	return *this;
}

Matrix3 Matrix3::operator-() const
{
	Matrix3 ret;

	for (size_t i = 0; i < matrixMax; i++)
	{
		ret.matrix[i] = -matrix[i];
	}
	return ret;
}

Matrix3& Matrix3::operator*=(const Matrix3& other)
{
	Matrix3 tempMatrix = *this;

	tempMatrix.matrix[_11] = (matrix[_11] * other.matrix[_11]) + (matrix[_12] * other.matrix[_21]) + (matrix[_13] * other.matrix[_31]);
	tempMatrix.matrix[_12] = (matrix[_11] * other.matrix[_12]) + (matrix[_12] * other.matrix[_22]) + (matrix[_13] * other.matrix[_32]);
	tempMatrix.matrix[_13] = (matrix[_11] * other.matrix[_13]) + (matrix[_12] * other.matrix[_23]) + (matrix[_13] * other.matrix[_33]);

	tempMatrix.matrix[_21] = (matrix[_21] * other.matrix[_11]) + (matrix[_22] * other.matrix[_21]) + (matrix[_23] * other.matrix[_31]);
	tempMatrix.matrix[_22] = (matrix[_21] * other.matrix[_12]) + (matrix[_22] * other.matrix[_22]) + (matrix[_23] * other.matrix[_32]);
	tempMatrix.matrix[_23] = (matrix[_21] * other.matrix[_13]) + (matrix[_22] * other.matrix[_23]) + (matrix[_23] * other.matrix[_33]);

	tempMatrix.matrix[_31] = (matrix[_31] * other.matrix[_11]) + (matrix[_32] * other.matrix[_21]) + (matrix[_33] * other.matrix[_31]);
	tempMatrix.matrix[_32] = (matrix[_31] * other.matrix[_12]) + (matrix[_32] * other.matrix[_22]) + (matrix[_33] * other.matrix[_32]);
	tempMatrix.matrix[_33] = (matrix[_31] * other.matrix[_13]) + (matrix[_32] * other.matrix[_23]) + (matrix[_33] * other.matrix[_33]);

	return *this;

}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	Matrix3 tempMatrix;

	tempMatrix.matrix[_11] = (matrix[_11] * other.matrix[_11]) + (matrix[_12] * other.matrix[_21]) + (matrix[_13] * other.matrix[_31]);
	tempMatrix.matrix[_12] = (matrix[_11] * other.matrix[_12]) + (matrix[_12] * other.matrix[_22]) + (matrix[_13] * other.matrix[_32]);
	tempMatrix.matrix[_13] = (matrix[_11] * other.matrix[_13]) + (matrix[_12] * other.matrix[_23]) + (matrix[_13] * other.matrix[_33]);

	tempMatrix.matrix[_21] = (matrix[_21] * other.matrix[_11]) + (matrix[_22] * other.matrix[_21]) + (matrix[_23] * other.matrix[_31]);
	tempMatrix.matrix[_22] = (matrix[_21] * other.matrix[_12]) + (matrix[_22] * other.matrix[_22]) + (matrix[_23] * other.matrix[_32]);
	tempMatrix.matrix[_23] = (matrix[_21] * other.matrix[_13]) + (matrix[_22] * other.matrix[_23]) + (matrix[_23] * other.matrix[_33]);

	tempMatrix.matrix[_31] = (matrix[_31] * other.matrix[_11]) + (matrix[_32] * other.matrix[_21]) + (matrix[_33] * other.matrix[_31]);
	tempMatrix.matrix[_32] = (matrix[_31] * other.matrix[_12]) + (matrix[_32] * other.matrix[_22]) + (matrix[_33] * other.matrix[_32]);
	tempMatrix.matrix[_33] = (matrix[_31] * other.matrix[_13]) + (matrix[_32] * other.matrix[_23]) + (matrix[_33] * other.matrix[_33]);

	return tempMatrix;

}

//1X3 * 3X3  
Vector3 Matrix3::operator*(const Vector3& other) const
{
	Vector3 ret;

	ret.X = (matrix[_11] * other.X) + (matrix[_12] * other.Y) + (matrix[_13] * other.Z);
	ret.Y = (matrix[_21] * other.X) + (matrix[_22] * other.Y) + (matrix[_23] * other.Z);
	ret.Z = (matrix[_31] * other.X) + (matrix[_32] * other.Y) + (matrix[_33] * other.Z);

	return ret;
}

Matrix3 Matrix3::operator*(const float scalar) const
{
	Matrix3 ret;

	for (size_t i = 0; i < matrixMax; i++)
	{
		ret.matrix[i] = matrix[i] * scalar;
	}
	return ret;
}

Matrix3& Matrix3::operator*=(const float scalar)
{

	for (size_t i = 0; i < matrixMax; i++)
	{
		matrix[i] *= scalar;
	}
	return *this;
}
