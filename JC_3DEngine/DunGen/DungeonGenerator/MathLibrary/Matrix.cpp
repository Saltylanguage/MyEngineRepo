#include "Matrix.h"
#include "SimpleMath.h"
#include <cmath>

using namespace Math;

enum MatrixIndex { _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33, _40, _41, _42, _43, matrixMax };

Matrix::Matrix(const Matrix & other)
{
}

Matrix& Matrix::operator=(const Matrix & other)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = other.data[i];
	}
	return *this;
}

void Matrix::Set(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33)
{
	data[0] = _00;  data[1] = _01; data[2] = _02;  data[3] = _03;
	data[4] = _10;  data[5] = _11; data[6] = _12;  data[7] = _13;
	data[8] = _20;  data[9] = _21; data[10] = _22;  data[11] = _23;
	data[12] = _30;  data[13] = _31; data[14] = _32;  data[15] = _33;
}

void Matrix::Clean()
{
	for (int i = 0; i < 16; i++)
	{
		if (abs(data[i]) < epsilon)
		{
			data[i] = 0.0f;
		}
	}
}

void Matrix::MakeZero()
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = 0.0f;
	}
}

bool Matrix::operator==(const Matrix & other) const
{
	for (int i = 0; i < 16; i++)
	{
		if (data[i] != other.data[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix & other) const
{
	for (int i = 0; i < 16; i++)
	{
		if (data[i] == other.data[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsZero() const
{
	for (int i = 0; i < 16; i++)
	{
		if (data[i] != 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsIdentity() const
{
	for (int i = 0; i < 16; i++)
	{
		if (i % 5 == 0 && data[i] != 1)
		{
			return false;
		}
	}
	return true;
}

Matrix Matrix::operator+(const Matrix & other) const
{
	return Matrix
	(
		data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2], data[3] + other.data[3],
		data[4] + other.data[4], data[5] + other.data[6], data[6] + other.data[6], data[7] + other.data[7],
		data[8] + other.data[8], data[9] + other.data[9], data[10] + other.data[10], data[11] + other.data[11],
		data[12] + other.data[12], data[13] + other.data[13], data[14] + other.data[14], data[15] + other.data[15]
	);
}

Matrix & Matrix::operator+=(const Matrix & other)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] += other.data[i];
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix & other) const
{
	return Matrix
	(
		data[0] - other.data[0], data[1] - other.data[1], data[2] - other.data[2], data[3] - other.data[3],
		data[4] - other.data[4], data[5] - other.data[6], data[6] - other.data[6], data[7] - other.data[7],
		data[8] - other.data[8], data[9] - other.data[9], data[10] - other.data[10], data[11] - other.data[11],
		data[12] - other.data[12], data[13] - other.data[13], data[14] - other.data[14], data[15] - other.data[15]
	);
}

Matrix & Matrix::operator-=(const Matrix & other)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] -= other.data[i];
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix & other) const
{
	Matrix ret;

	ret.data[_00] = (data[_00] * other.data[_00]) + (data[_01] * other.data[_10]) + (data[_02] * other.data[_20]) + (data[_03] * other.data[_30]);
	ret.data[_01] = (data[_00] * other.data[_01]) + (data[_01] * other.data[_11]) + (data[_02] * other.data[_21]) + (data[_03] * other.data[_31]);
	ret.data[_02] = (data[_00] * other.data[_02]) + (data[_01] * other.data[_12]) + (data[_02] * other.data[_22]) + (data[_03] * other.data[_32]);
	ret.data[_03] = (data[_00] * other.data[_03]) + (data[_01] * other.data[_13]) + (data[_02] * other.data[_23]) + (data[_03] * other.data[_33]);

	ret.data[_10] = (data[_10] * other.data[_00]) + (data[_11] * other.data[_10]) + (data[_12] * other.data[_20]) + (data[_13] * other.data[_30]);
	ret.data[_11] = (data[_10] * other.data[_01]) + (data[_11] * other.data[_11]) + (data[_12] * other.data[_21]) + (data[_13] * other.data[_31]);
	ret.data[_12] = (data[_10] * other.data[_02]) + (data[_11] * other.data[_12]) + (data[_12] * other.data[_22]) + (data[_13] * other.data[_32]);
	ret.data[_13] = (data[_10] * other.data[_03]) + (data[_11] * other.data[_13]) + (data[_12] * other.data[_23]) + (data[_13] * other.data[_33]);

	ret.data[_20] = (data[_20] * other.data[_00]) + (data[_21] * other.data[_10]) + (data[_22] * other.data[_20]) + (data[_23] * other.data[_30]);
	ret.data[_21] = (data[_20] * other.data[_01]) + (data[_21] * other.data[_11]) + (data[_22] * other.data[_21]) + (data[_23] * other.data[_31]);
	ret.data[_22] = (data[_20] * other.data[_02]) + (data[_21] * other.data[_12]) + (data[_22] * other.data[_22]) + (data[_23] * other.data[_32]);
	ret.data[_23] = (data[_20] * other.data[_03]) + (data[_21] * other.data[_13]) + (data[_22] * other.data[_23]) + (data[_23] * other.data[_33]);

	ret.data[_30] = (data[_30] * other.data[_00]) + (data[_31] * other.data[_10]) + (data[_32] * other.data[_20]) + (data[_33] * other.data[_30]);
	ret.data[_31] = (data[_30] * other.data[_01]) + (data[_31] * other.data[_11]) + (data[_32] * other.data[_21]) + (data[_33] * other.data[_31]);
	ret.data[_32] = (data[_30] * other.data[_02]) + (data[_31] * other.data[_12]) + (data[_32] * other.data[_22]) + (data[_33] * other.data[_32]);
	ret.data[_33] = (data[_30] * other.data[_03]) + (data[_31] * other.data[_13]) + (data[_32] * other.data[_23]) + (data[_33] * other.data[_33]);


	return ret;
}

Matrix & Matrix::operator*=(const Matrix & other)
{
	data[_00] = (data[_00] * other.data[_00]) + (data[_01] * other.data[_10]) + (data[_02] * other.data[_20]) + (data[_03] * other.data[_30]);
	data[_01] = (data[_00] * other.data[_01]) + (data[_01] * other.data[_11]) + (data[_02] * other.data[_21]) + (data[_03] * other.data[_31]);
	data[_02] = (data[_00] * other.data[_02]) + (data[_01] * other.data[_12]) + (data[_02] * other.data[_22]) + (data[_03] * other.data[_32]);
	data[_03] = (data[_00] * other.data[_03]) + (data[_01] * other.data[_13]) + (data[_02] * other.data[_23]) + (data[_03] * other.data[_33]);

	data[_10] = (data[_10] * other.data[_00]) + (data[_11] * other.data[_10]) + (data[_12] * other.data[_20]) + (data[_13] * other.data[_30]);
	data[_11] = (data[_10] * other.data[_01]) + (data[_11] * other.data[_11]) + (data[_12] * other.data[_21]) + (data[_13] * other.data[_31]);
	data[_12] = (data[_10] * other.data[_02]) + (data[_11] * other.data[_12]) + (data[_12] * other.data[_22]) + (data[_13] * other.data[_32]);
	data[_13] = (data[_10] * other.data[_03]) + (data[_11] * other.data[_13]) + (data[_12] * other.data[_23]) + (data[_13] * other.data[_33]);

	data[_20] = (data[_20] * other.data[_00]) + (data[_21] * other.data[_10]) + (data[_22] * other.data[_20]) + (data[_23] * other.data[_30]);
	data[_21] = (data[_20] * other.data[_01]) + (data[_21] * other.data[_11]) + (data[_22] * other.data[_21]) + (data[_23] * other.data[_31]);
	data[_22] = (data[_20] * other.data[_02]) + (data[_21] * other.data[_12]) + (data[_22] * other.data[_22]) + (data[_23] * other.data[_32]);
	data[_23] = (data[_20] * other.data[_03]) + (data[_21] * other.data[_13]) + (data[_22] * other.data[_23]) + (data[_23] * other.data[_33]);

	data[_30] = (data[_30] * other.data[_00]) + (data[_31] * other.data[_10]) + (data[_32] * other.data[_20]) + (data[_33] * other.data[_30]);
	data[_31] = (data[_30] * other.data[_01]) + (data[_31] * other.data[_11]) + (data[_32] * other.data[_21]) + (data[_33] * other.data[_31]);
	data[_32] = (data[_30] * other.data[_02]) + (data[_31] * other.data[_12]) + (data[_32] * other.data[_22]) + (data[_33] * other.data[_32]);
	data[_33] = (data[_30] * other.data[_03]) + (data[_31] * other.data[_13]) + (data[_32] * other.data[_23]) + (data[_33] * other.data[_33]);

	return *this;
}

Matrix Matrix::operator*(const float scalar) const
{
	return Matrix
	(
		data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar,
		data[4] * scalar, data[5] * scalar, data[6] * scalar, data[7] * scalar,
		data[8] * scalar, data[9] * scalar, data[10] * scalar, data[11] * scalar,
		data[12] * scalar, data[13] * scalar, data[14] * scalar, data[15] * scalar
	);
}

Matrix Matrix::operator*=(const float scalar)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] *= scalar;
	}
	return *this;
}

Matrix Matrix::Zero()
{
	return Matrix
	(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f

	);
}

Matrix Matrix::Identity()
{
	return Matrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f

	);
}

Matrix Matrix::Translation(const float x, const float y, const float z)
{
	return Matrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f
	);

}

Matrix Matrix::Translation(const Vector3 & vec)
{
	return Matrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		vec.x, vec.y, vec.z, 1.0f
	);

}

Matrix Matrix::RotationX(const Vector3 & axis, const float rad)
{
	return Matrix
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosf(rad), sinf(rad), 0.0f,
		0.0f, -sinf(rad), cosf(rad), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::RotationY(const Vector3 & axis, const float rad)
{
	return Matrix
	(
		cosf(rad), 0.0f, -sinf(rad), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinf(rad), 0.0f, cosf(rad), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::RotationZ(const Vector3 & axis, const float rad)
{
	return Matrix
	(
		cosf(rad), sinf(rad), 0.0f, 0.0f,
		-sinf(rad), cosf(rad), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::RotationAxis(const Vector3 & axis, float rad)
{
	return Matrix();
}

Matrix Matrix::Scale(const Vector3 & scale)
{
	Matrix scaleMatrix = MakeScaleMatrix(scale);

	*this *= scaleMatrix;

	return *this;
}

Matrix Matrix::Scaling(const float scaleFactor)
{
	return Matrix
	(
		scaleFactor, 0.0f, 0.0f, 0.0f,
		0.0f, scaleFactor, 0.0f, 0.0f,
		0.0f, 0.0f, scaleFactor, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::Scaling(const float x, const float y, const float z)
{
	return Matrix
	(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::Scaling(const Vector3 & scaleValues)
{
	return Matrix
	(
		scaleValues.x, 0.0f, 0.0f, 0.0f,
		0.0f, scaleValues.y, 0.0f, 0.0f,
		0.0f, 0.0f, scaleValues.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix Matrix::MakeScaleMatrix(const Vector3 & scale)
{
	return Matrix
	(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

}

Matrix Matrix::Transpose(const Matrix & mat)
{
	Matrix ret;

	ret.data[_00] = mat.data[_00];
	ret.data[_01] = mat.data[_10];
	ret.data[_02] = mat.data[_20];
	ret.data[_03] = mat.data[_30];
	ret.data[_10] = mat.data[_01];
	ret.data[_11] = mat.data[_11];
	ret.data[_12] = mat.data[_22];
	ret.data[_13] = mat.data[_31];
	ret.data[_20] = mat.data[_02];
	ret.data[_21] = mat.data[_12];
	ret.data[_22] = mat.data[_22];
	ret.data[_23] = mat.data[_32];
	ret.data[_30] = mat.data[_03];
	ret.data[_31] = mat.data[_13];
	ret.data[_32] = mat.data[_23];
	ret.data[_33] = mat.data[_33];

	return ret;
}

Matrix Matrix::Adjoint(const Matrix & mat)
{
	return{
		(mat.data[_11] * ((mat.data[_22] * mat.data[_33]) - (mat.data[_32] * mat.data[_23])) - mat.data[_12] * ((mat.data[_21] * mat.data[_33]) - (mat.data[_31] * mat.data[_23])) + mat.data[_13] * ((mat.data[_21] * mat.data[_32]) - (mat.data[_31] * mat.data[_22]))),
		-(mat.data[_01] * ((mat.data[_22] * mat.data[_33]) - (mat.data[_32] * mat.data[_23])) - mat.data[_02] * ((mat.data[_21] * mat.data[_33]) - (mat.data[_31] * mat.data[_23])) + mat.data[_03] * ((mat.data[_21] * mat.data[_32]) - (mat.data[_31] * mat.data[_22]))),
		(mat.data[_01] * ((mat.data[_12] * mat.data[_33]) - (mat.data[_32] * mat.data[_13])) - mat.data[_02] * ((mat.data[_11] * mat.data[_33]) - (mat.data[_31] * mat.data[_13])) + mat.data[_03] * ((mat.data[_11] * mat.data[_32]) - (mat.data[_31] * mat.data[_12]))),
		-(mat.data[_01] * ((mat.data[_12] * mat.data[_23]) - (mat.data[_22] * mat.data[_13])) - mat.data[_02] * ((mat.data[_11] * mat.data[_23]) - (mat.data[_21] * mat.data[_13])) + mat.data[_03] * ((mat.data[_11] * mat.data[_22]) - (mat.data[_21] * mat.data[_12]))),

		-(mat.data[_10] * ((mat.data[_22] * mat.data[_33]) - (mat.data[_32] * mat.data[_23])) - mat.data[_20] * ((mat.data[_12] * mat.data[_33]) - (mat.data[_13] * mat.data[_32])) + mat.data[_30] * ((mat.data[_12] * mat.data[_23]) - (mat.data[_13] * mat.data[_22]))),
		(mat.data[_00] * ((mat.data[_22] * mat.data[_33]) - (mat.data[_32] * mat.data[_23])) - mat.data[_02] * ((mat.data[_20] * mat.data[_33]) - (mat.data[_30] * mat.data[_23])) + mat.data[_03] * ((mat.data[_20] * mat.data[_32]) - (mat.data[_30] * mat.data[_22]))),
		-(mat.data[_00] * ((mat.data[_12] * mat.data[_33]) - (mat.data[_32] * mat.data[_13])) - mat.data[_02] * ((mat.data[_10] * mat.data[_33]) - (mat.data[_30] * mat.data[_13])) + mat.data[_03] * ((mat.data[_10] * mat.data[_32]) - (mat.data[_30] * mat.data[_12]))),
		(mat.data[_00] * ((mat.data[_12] * mat.data[_23]) - (mat.data[_22] * mat.data[_13])) - mat.data[_02] * ((mat.data[_10] * mat.data[_23]) - (mat.data[_20] * mat.data[_13])) + mat.data[_03] * ((mat.data[_10] * mat.data[_22]) - (mat.data[_20] * mat.data[_12]))),

		(mat.data[_10] * ((mat.data[_21] * mat.data[_33]) - (mat.data[_31] * mat.data[_23])) - mat.data[_20] * ((mat.data[_11] * mat.data[_33]) - (mat.data[_31] * mat.data[_13])) + mat.data[_30] * ((mat.data[_11] * mat.data[_23]) - (mat.data[_21] * mat.data[_13]))),
		-(mat.data[_00] * ((mat.data[_21] * mat.data[_33]) - (mat.data[_31] * mat.data[_23])) - mat.data[_20] * ((mat.data[_01] * mat.data[_33]) - (mat.data[_31] * mat.data[_03])) + mat.data[_30] * ((mat.data[_01] * mat.data[_23]) - (mat.data[_21] * mat.data[_03]))),
		(mat.data[_00] * ((mat.data[_11] * mat.data[_33]) - (mat.data[_31] * mat.data[_13])) - mat.data[_01] * ((mat.data[_10] * mat.data[_33]) - (mat.data[_30] * mat.data[_13])) + mat.data[_03] * ((mat.data[_10] * mat.data[_31]) - (mat.data[_30] * mat.data[_11]))),
		-(mat.data[_00] * ((mat.data[_11] * mat.data[_23]) - (mat.data[_21] * mat.data[_13])) - mat.data[_10] * ((mat.data[_01] * mat.data[_23]) - (mat.data[_21] * mat.data[_03])) + mat.data[_20] * ((mat.data[_01] * mat.data[_13]) - (mat.data[_11] * mat.data[_03]))),

		-(mat.data[_10] * ((mat.data[_21] * mat.data[_32]) - (mat.data[_31] * mat.data[_22])) - mat.data[_20] * ((mat.data[_11] * mat.data[_32]) - (mat.data[_31] * mat.data[_12])) + mat.data[_30] * ((mat.data[_11] * mat.data[_22]) - (mat.data[_21] * mat.data[_12]))),
		(mat.data[_00] * ((mat.data[_21] * mat.data[_32]) - (mat.data[_31] * mat.data[_22])) - mat.data[_01] * ((mat.data[_20] * mat.data[_32]) - (mat.data[_30] * mat.data[_22])) + mat.data[_02] * ((mat.data[_20] * mat.data[_31]) - (mat.data[_30] * mat.data[_21]))),
		-(mat.data[_00] * ((mat.data[_11] * mat.data[_32]) - (mat.data[_31] * mat.data[_12])) - mat.data[_01] * ((mat.data[_10] * mat.data[_32]) - (mat.data[_30] * mat.data[_12])) + mat.data[_02] * ((mat.data[_10] * mat.data[_31]) - (mat.data[_30] * mat.data[_11]))),
		(mat.data[_00] * ((mat.data[_11] * mat.data[_22]) - (mat.data[_21] * mat.data[_12])) - mat.data[_01] * ((mat.data[_10] * mat.data[_22]) - (mat.data[_20] * mat.data[_12])) + mat.data[_02] * ((mat.data[_10] * mat.data[_21]) - (mat.data[_20] * mat.data[_11])))
	};
}

float Matrix::Determinant() const
{
	float det = 0.0f;
	det = (data[_00] * (data[_11] * (data[_22] * data[_33] - (data[_32] * data[_23])) - data[_12] * (data[_21] * data[_33] - (data[_31] * data[_23])) + data[_13] * (data[_21] * data[_32] - (data[_31] * data[_22]))));
	det -= (data[_01] * (data[_10] * (data[_22] * data[_33] - (data[_32] * data[_23])) - data[_12] * (data[_20] * data[_33] - (data[_30] * data[_23])) + data[_13] * (data[_20] * data[_32] - (data[_30] * data[_22]))));
	det += (data[_02] * (data[_10] * (data[_21] * data[_33] - (data[_31] * data[_23])) - data[_11] * (data[_20] * data[_33] - (data[_30] * data[_23])) + data[_13] * (data[_20] * data[_31] - (data[_30] * data[_21]))));
	det -= (data[_03] * (data[_10] * (data[_21] * data[_32] - (data[_31] * data[_22])) - data[_11] * (data[_20] * data[_32] - (data[_30] * data[_22])) + data[_12] * (data[_20] * data[_31] - (data[_30] * data[_21]))));
	return det;
}

Matrix Matrix::Inverse(const Matrix & mat)
{
	const float determinant = mat.Determinant();
	const float invDet = 1.0f / determinant;
	return Adjoint(mat) * invDet;
}

Vector3 Matrix::TransformPoint(const Vector3 & point) const
{
	Vector3 ret;

	ret.x = data[_00] * point.x + data[_01] * point.y + data[_02] * point.z + data[_03];
	ret.y = data[_10] * point.x + data[_11] * point.y + data[_12] * point.z + data[_13];
	ret.z = data[_20] * point.x + data[_21] * point.y + data[_22] * point.z + data[_23];

	return ret;
}
