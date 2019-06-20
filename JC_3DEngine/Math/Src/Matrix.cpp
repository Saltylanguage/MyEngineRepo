#include "Precompiled.h"
#include "Math\Inc\Quaternion.h"
#include "Math\Inc\Matrix.h"
#include "Math\Inc\Vector3.h"
#include "Math\Inc\Vector4.h"

using namespace Math;

enum MatrixIndex { _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44, matrixMax };

//copy constructor
Matrix::Matrix(const Matrix & m44)
{
	matrix[_11] = m44.matrix[_11]; matrix[_12] = m44.matrix[_12]; matrix[_13] = m44.matrix[_13], matrix[_14] = m44.matrix[_14];
	matrix[_21] = m44.matrix[_21]; matrix[_22] = m44.matrix[_22]; matrix[_23] = m44.matrix[_23], matrix[_24] = m44.matrix[_24];
	matrix[_31] = m44.matrix[_31]; matrix[_32] = m44.matrix[_32]; matrix[_33] = m44.matrix[_33], matrix[_34] = m44.matrix[_34];
	matrix[_41] = m44.matrix[_41]; matrix[_42] = m44.matrix[_42]; matrix[_43] = m44.matrix[_43], matrix[_44] = m44.matrix[_44];
}

Matrix::Matrix(float values[16])
{
	matrix[_11] = values[_11]; matrix[_12] = values[_12]; matrix[_13] = values[_13], matrix[_14] = values[_14];
	matrix[_21] = values[_21]; matrix[_22] = values[_22]; matrix[_23] = values[_23], matrix[_24] = values[_24];
	matrix[_31] = values[_31]; matrix[_32] = values[_32]; matrix[_33] = values[_33], matrix[_34] = values[_34];
	matrix[_41] = values[_41]; matrix[_42] = values[_42]; matrix[_43] = values[_43], matrix[_44] = values[_44];
}


Math::Matrix::Matrix(
	float element11, float element12, float element13, float element14,
	float element21, float element22, float element23, float element24,
	float element31, float element32, float element33, float element34,
	float element41, float element42, float element43, float element44
)
{
	matrix[0] = element11;
	matrix[1] = element12;
	matrix[2] = element13;
	matrix[3] = element14;

	matrix[4] = element21;
	matrix[5] = element22;
	matrix[6] = element23;
	matrix[7] = element24;

	matrix[8] = element31;
	matrix[9] = element32;
	matrix[10] = element33;
	matrix[11] = element34;

	matrix[12] = element41;
	matrix[13] = element42;
	matrix[14] = element43;
	matrix[15] = element44;
}

Matrix Math::Matrix::Zero() { return Matrix(); }

Matrix Math::Matrix::Identity() { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::Translation(float x, float y, float z) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, x, y, z, 1.0f); }

Matrix Math::Matrix::Translation(const Vector3 & v) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, v.x, v.y, v.z, 1.0f); }

Matrix Math::Matrix::RotationX(const Vector3 & axis, float rad) { return Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cosf(rad), sinf(rad), 0.0f, 0.0f, -sinf(rad), cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::RotationY(float rad) { return Matrix(cosf(rad), 0.0f, -sinf(rad), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sinf(rad), 0.0f, cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::RotationZ(float rad) { return Matrix(cosf(rad), sinf(rad), 0.0f, 0.0f, -sinf(rad), cosf(rad), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::Scaling(float s) { return Matrix(s, 0.0f, 0.0f, 0.0f, 0.0f, s, 0.0f, 0.0f, 0.0f, 0.0f, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::Scaling(float sx, float sy, float sz) { return Matrix(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }

Matrix Math::Matrix::Scaling(const Vector3 & s) { return Matrix(s.x, 0.0f, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, 0.0f, s.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f); }


Matrix & Matrix::operator=(const Matrix & other)
{
	//if same oobject
	if (this == &other)
	{
		return *this;
	}

	for (int i = _11; i < matrixMax; i++)
	{
		matrix[i] = other.matrix[i];
	}
	return *this;

}

bool Matrix::operator==(const Matrix & other) const
{
	for (int i = _11; i < matrixMax; i++)
	{
		if (matrix[i] != other.matrix[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix & other) const
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		if (matrix[i] == other.matrix[i])
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsZero() const
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		if (matrix[i] != 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool Matrix::IsIdentity() const
{
	return (matrix[_11] == 1.0f && matrix[_12] == 0.0f && matrix[_13] == 0.0f && matrix[_14] == 0.0f &&
		matrix[_21] == 0.0f && matrix[_22] == 1.0f && matrix[_23] == 0.0f && matrix[_24] == 0.0f &&
		matrix[_31] == 0.0f && matrix[_32] == 0.0f && matrix[_33] == 1.0f && matrix[_34] == 0.0f &&
		matrix[_41] == 0.0f && matrix[_42] == 0.0f && matrix[_43] == 0.0f && matrix[_44] == 1.0f);
}

void Matrix::Clean()
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		if (matrix[i] <= 0.001f)
		{
			matrix[i] = 0.0f;
		}
	}
}

Matrix Matrix::Transpose(const Matrix& mat)
{

	//_11, _12, _13, _14,			_11, _21, _31, _41,
	//_21, _22, _23, _24,	---\	_12, _22, _32, _42,
	//_31, _32, _33, _34,	---/	_13, _23, _33, _43,
	//_41, _42, _43, _44,			_14, _24, _34, _44,

	return Matrix
	(
		mat.matrix[_11],
		mat.matrix[_21],
		mat.matrix[_31],
		mat.matrix[_41],
		mat.matrix[_12],
		mat.matrix[_22],
		mat.matrix[_32],
		mat.matrix[_42],
		mat.matrix[_13],
		mat.matrix[_23],
		mat.matrix[_33],
		mat.matrix[_43],
		mat.matrix[_14],
		mat.matrix[_24],
		mat.matrix[_34],
		mat.matrix[_44]
	);
}

Matrix Matrix::MakeTranspose(const Matrix& mat)
{
	Matrix ret;

	ret.matrix[_11] = mat.matrix[_11];
	ret.matrix[_12] = mat.matrix[_21];
	ret.matrix[_13] = mat.matrix[_31];
	ret.matrix[_14] = mat.matrix[_41];
	ret.matrix[_21] = mat.matrix[_12];
	ret.matrix[_22] = mat.matrix[_22];
	ret.matrix[_23] = mat.matrix[_33];
	ret.matrix[_24] = mat.matrix[_42];
	ret.matrix[_31] = mat.matrix[_13];
	ret.matrix[_32] = mat.matrix[_23];
	ret.matrix[_33] = mat.matrix[_33];
	ret.matrix[_34] = mat.matrix[_43];
	ret.matrix[_41] = mat.matrix[_14];
	ret.matrix[_42] = mat.matrix[_24];
	ret.matrix[_43] = mat.matrix[_34];
	ret.matrix[_44] = mat.matrix[_44];

	return ret;
}




Matrix Matrix::RotationAxis(const Vector3& axis, float rad)
{

	Vector3 norm = Vector3::Normalize(axis);

	const float x = norm.x;
	const float y = norm.y;
	const float z = norm.z;
	const float sinRad = sinf(rad);
	const float cosRad = cosf(rad);

	Matrix ret(cosRad + (x * x * (1.0f - cosRad)), x * y * (1.0f - cosRad) + z * sinRad, x * z * (1.0f - cosRad) - y * sinRad, 0.0f,
		x * y * (1.0f - cosRad) - z * sinRad, cosRad + (y * y * (1.0f - cosRad)), y * z * (1.0f - cosRad) + x * sinRad, 0.0f,
		x * z * (1.0f - cosRad) + y * sinRad, y * z * (1.0f - cosRad) - x * sinRad, cosRad + (z * z * (1.0f - cosRad)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return ret;

}

Matrix Math::Matrix::RotationQuaternion(const Quaternion& q)
{
	return Matrix
	(
		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
		(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);

}

Matrix Matrix::RotateX(const float angle)
{
	Matrix mat;
	mat.matrix[_11] = 1.0f;			mat.matrix[_12] = 0.0f;				mat.matrix[_13] = 0.0f;				mat.matrix[_14] = 0.0f;
	mat.matrix[_21] = 0.0f;			mat.matrix[_22] = cosf(angle);		mat.matrix[_23] = sinf(angle);		mat.matrix[_24] = 0.0f;
	mat.matrix[_31] = 0.0f;			mat.matrix[_32] = -sinf(angle);		mat.matrix[_33] = cosf(angle);		mat.matrix[_34] = 0.0f;
	mat.matrix[_41] = 0.0f;			mat.matrix[_42] = 0.0f;				mat.matrix[_43] = 0.0f;				mat.matrix[_44] = 1.0f;

	return mat;

}

Matrix Matrix::RotateY(const float angle)
{
	Matrix mat;
	mat.matrix[_11] = cosf(angle);			mat.matrix[_12] = 0.0f;				mat.matrix[_13] = -sinf(angle);		mat.matrix[_14] = 0.0f;
	mat.matrix[_21] = 0;					mat.matrix[_22] = 1.0f;				mat.matrix[_23] = 0.0f;				mat.matrix[_24] = 0.0f;
	mat.matrix[_31] = sinf(angle);			mat.matrix[_32] = 0.0f;				mat.matrix[_33] = cosf(angle);		mat.matrix[_34] = 0.0f;
	mat.matrix[_41] = 0;					mat.matrix[_42] = 0.0f;				mat.matrix[_43] = 0.0f;				mat.matrix[_44] = 1.0f;

	return mat;
}

Matrix Matrix::RotateZ(const float angle)
{
	Matrix mat;
	mat.matrix[_11] = cosf(angle);			mat.matrix[_12] = sinf(angle);				mat.matrix[_13] = 0;			mat.matrix[_14] = 0;
	mat.matrix[_21] = -sinf(angle);			mat.matrix[_22] = cosf(angle);				mat.matrix[_23] = 0.0f;			mat.matrix[_24] = 0.0f;
	mat.matrix[_31] = 0;					mat.matrix[_32] = 0.0f;						mat.matrix[_33] = 1.0f;			mat.matrix[_34] = 0.0f;
	mat.matrix[_41] = 0;					mat.matrix[_42] = 0.0f;						mat.matrix[_43] = 0.0f;			mat.matrix[_44] = 1.0f;

	return mat;
}

Matrix Matrix::MakeScaleMatrix(const Vector3 & scale)
{
	return Matrix(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

float Matrix::Determinant() const
{
	float det = 0.0f;
	det = (matrix[_11] * (matrix[_22] * (matrix[_33] * matrix[_44] - (matrix[_43] * matrix[_34])) - matrix[_23] * (matrix[_32] * matrix[_44] - (matrix[_42] * matrix[_34])) + matrix[_24] * (matrix[_32] * matrix[_43] - (matrix[_42] * matrix[_33]))));
	det -= (matrix[_12] * (matrix[_21] * (matrix[_33] * matrix[_44] - (matrix[_43] * matrix[_34])) - matrix[_23] * (matrix[_31] * matrix[_44] - (matrix[_41] * matrix[_34])) + matrix[_24] * (matrix[_31] * matrix[_43] - (matrix[_41] * matrix[_33]))));
	det += (matrix[_13] * (matrix[_21] * (matrix[_32] * matrix[_44] - (matrix[_42] * matrix[_34])) - matrix[_22] * (matrix[_31] * matrix[_44] - (matrix[_41] * matrix[_34])) + matrix[_24] * (matrix[_31] * matrix[_42] - (matrix[_41] * matrix[_32]))));
	det -= (matrix[_14] * (matrix[_21] * (matrix[_32] * matrix[_43] - (matrix[_42] * matrix[_33])) - matrix[_22] * (matrix[_31] * matrix[_43] - (matrix[_41] * matrix[_33])) + matrix[_23] * (matrix[_31] * matrix[_42] - (matrix[_41] * matrix[_32]))));
	return det;
}

Matrix Matrix::Adjoint(const Matrix& mat)
{
	return{
		(mat.matrix[_22] * ((mat.matrix[_33] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_34])) - mat.matrix[_23] * ((mat.matrix[_32] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_34])) + mat.matrix[_24] * ((mat.matrix[_32] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_33]))),
		-(mat.matrix[_12] * ((mat.matrix[_33] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_34])) - mat.matrix[_13] * ((mat.matrix[_32] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_34])) + mat.matrix[_14] * ((mat.matrix[_32] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_33]))),
		(mat.matrix[_12] * ((mat.matrix[_23] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_24])) - mat.matrix[_13] * ((mat.matrix[_22] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_24])) + mat.matrix[_14] * ((mat.matrix[_22] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_23]))),
		-(mat.matrix[_12] * ((mat.matrix[_23] * mat.matrix[_34]) - (mat.matrix[_33] * mat.matrix[_24])) - mat.matrix[_13] * ((mat.matrix[_22] * mat.matrix[_34]) - (mat.matrix[_32] * mat.matrix[_24])) + mat.matrix[_14] * ((mat.matrix[_22] * mat.matrix[_33]) - (mat.matrix[_32] * mat.matrix[_23]))),

		-(mat.matrix[_21] * ((mat.matrix[_33] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_34])) - mat.matrix[_31] * ((mat.matrix[_23] * mat.matrix[_44]) - (mat.matrix[_24] * mat.matrix[_43])) + mat.matrix[_41] * ((mat.matrix[_23] * mat.matrix[_34]) - (mat.matrix[_24] * mat.matrix[_33]))),
		(mat.matrix[_11] * ((mat.matrix[_33] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_34])) - mat.matrix[_13] * ((mat.matrix[_31] * mat.matrix[_44]) - (mat.matrix[_41] * mat.matrix[_34])) + mat.matrix[_14] * ((mat.matrix[_31] * mat.matrix[_43]) - (mat.matrix[_41] * mat.matrix[_33]))),
		-(mat.matrix[_11] * ((mat.matrix[_23] * mat.matrix[_44]) - (mat.matrix[_43] * mat.matrix[_24])) - mat.matrix[_13] * ((mat.matrix[_21] * mat.matrix[_44]) - (mat.matrix[_41] * mat.matrix[_24])) + mat.matrix[_14] * ((mat.matrix[_21] * mat.matrix[_43]) - (mat.matrix[_41] * mat.matrix[_23]))),
		(mat.matrix[_11] * ((mat.matrix[_23] * mat.matrix[_34]) - (mat.matrix[_33] * mat.matrix[_24])) - mat.matrix[_13] * ((mat.matrix[_21] * mat.matrix[_34]) - (mat.matrix[_31] * mat.matrix[_24])) + mat.matrix[_14] * ((mat.matrix[_21] * mat.matrix[_33]) - (mat.matrix[_31] * mat.matrix[_23]))),

		(mat.matrix[_21] * ((mat.matrix[_32] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_34])) - mat.matrix[_31] * ((mat.matrix[_22] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_24])) + mat.matrix[_41] * ((mat.matrix[_22] * mat.matrix[_34]) - (mat.matrix[_32] * mat.matrix[_24]))),
		-(mat.matrix[_11] * ((mat.matrix[_32] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_34])) - mat.matrix[_31] * ((mat.matrix[_12] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_14])) + mat.matrix[_41] * ((mat.matrix[_12] * mat.matrix[_34]) - (mat.matrix[_32] * mat.matrix[_14]))),
		(mat.matrix[_11] * ((mat.matrix[_22] * mat.matrix[_44]) - (mat.matrix[_42] * mat.matrix[_24])) - mat.matrix[_12] * ((mat.matrix[_21] * mat.matrix[_44]) - (mat.matrix[_41] * mat.matrix[_24])) + mat.matrix[_14] * ((mat.matrix[_21] * mat.matrix[_42]) - (mat.matrix[_41] * mat.matrix[_22]))),
		-(mat.matrix[_11] * ((mat.matrix[_22] * mat.matrix[_34]) - (mat.matrix[_32] * mat.matrix[_24])) - mat.matrix[_21] * ((mat.matrix[_12] * mat.matrix[_34]) - (mat.matrix[_32] * mat.matrix[_14])) + mat.matrix[_31] * ((mat.matrix[_12] * mat.matrix[_24]) - (mat.matrix[_22] * mat.matrix[_14]))),

		-(mat.matrix[_21] * ((mat.matrix[_32] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_33])) - mat.matrix[_31] * ((mat.matrix[_22] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_23])) + mat.matrix[_41] * ((mat.matrix[_22] * mat.matrix[_33]) - (mat.matrix[_32] * mat.matrix[_23]))),
		(mat.matrix[_11] * ((mat.matrix[_32] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_33])) - mat.matrix[_12] * ((mat.matrix[_31] * mat.matrix[_43]) - (mat.matrix[_41] * mat.matrix[_33])) + mat.matrix[_13] * ((mat.matrix[_31] * mat.matrix[_42]) - (mat.matrix[_41] * mat.matrix[_32]))),
		-(mat.matrix[_11] * ((mat.matrix[_22] * mat.matrix[_43]) - (mat.matrix[_42] * mat.matrix[_23])) - mat.matrix[_12] * ((mat.matrix[_21] * mat.matrix[_43]) - (mat.matrix[_41] * mat.matrix[_23])) + mat.matrix[_13] * ((mat.matrix[_21] * mat.matrix[_42]) - (mat.matrix[_41] * mat.matrix[_22]))),
		(mat.matrix[_11] * ((mat.matrix[_22] * mat.matrix[_33]) - (mat.matrix[_32] * mat.matrix[_23])) - mat.matrix[_12] * ((mat.matrix[_21] * mat.matrix[_33]) - (mat.matrix[_31] * mat.matrix[_23])) + mat.matrix[_13] * ((mat.matrix[_21] * mat.matrix[_32]) - (mat.matrix[_31] * mat.matrix[_22])))
	};
}

Matrix Matrix::Inverse(const Matrix& mat)
{
	const float determinant = mat.Determinant();
	const float invDet = 1.0f / determinant;
	return Adjoint(mat) * invDet;
}


Matrix Math::Matrix::Scale(const Vector3& scale)
{
	Matrix scaleMatrix = MakeScaleMatrix(scale);

	*this *= scaleMatrix;

	return *this;
}

Matrix Matrix::operator+(const Matrix & other) const
{
	Matrix ret;

	for (size_t i = _11; i < matrixMax; i++)
	{
		ret.matrix[i] = matrix[i] + other.matrix[i];
	}

	return ret;
}

Matrix Matrix::operator+=(const Matrix & other)
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		matrix[i] += other.matrix[i];
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix & other) const
{
	Matrix ret;

	for (size_t i = _11; i < matrixMax; i++)
	{
		ret.matrix[i] = matrix[i] - other.matrix[i];
	}

	return ret;
}

Matrix Matrix::operator-=(const Matrix & other)
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		matrix[i] -= other.matrix[i];
	}
	return *this;
}

Matrix Matrix::operator-() const
{
	Matrix ret;

	for (size_t i = _11; i < matrixMax; i++)
	{
		ret.matrix[i] = -matrix[i];
	}
	return ret;
}

Matrix Matrix::operator*(const float scalar)
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		matrix[i] *= scalar;
	}

	return *this;
}

Matrix Matrix::operator*=(const float scalar)
{
	for (size_t i = _11; i < matrixMax; i++)
	{
		matrix[i] *= scalar;
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix ret;

	ret.matrix[_11] = (matrix[_11] * other.matrix[_11]) + (matrix[_12] * other.matrix[_21]) + (matrix[_13] * other.matrix[_31]) + (matrix[_14] * other.matrix[_41]);
	ret.matrix[_12] = (matrix[_11] * other.matrix[_12]) + (matrix[_12] * other.matrix[_22]) + (matrix[_13] * other.matrix[_32]) + (matrix[_14] * other.matrix[_42]);
	ret.matrix[_13] = (matrix[_11] * other.matrix[_13]) + (matrix[_12] * other.matrix[_23]) + (matrix[_13] * other.matrix[_33]) + (matrix[_14] * other.matrix[_43]);
	ret.matrix[_14] = (matrix[_11] * other.matrix[_14]) + (matrix[_12] * other.matrix[_24]) + (matrix[_13] * other.matrix[_34]) + (matrix[_14] * other.matrix[_44]);

	ret.matrix[_21] = (matrix[_21] * other.matrix[_11]) + (matrix[_22] * other.matrix[_21]) + (matrix[_23] * other.matrix[_31]) + (matrix[_24] * other.matrix[_41]);
	ret.matrix[_22] = (matrix[_21] * other.matrix[_12]) + (matrix[_22] * other.matrix[_22]) + (matrix[_23] * other.matrix[_32]) + (matrix[_24] * other.matrix[_42]);
	ret.matrix[_23] = (matrix[_21] * other.matrix[_13]) + (matrix[_22] * other.matrix[_23]) + (matrix[_23] * other.matrix[_33]) + (matrix[_24] * other.matrix[_43]);
	ret.matrix[_24] = (matrix[_21] * other.matrix[_14]) + (matrix[_22] * other.matrix[_24]) + (matrix[_23] * other.matrix[_34]) + (matrix[_24] * other.matrix[_44]);

	ret.matrix[_31] = (matrix[_31] * other.matrix[_11]) + (matrix[_32] * other.matrix[_21]) + (matrix[_33] * other.matrix[_31]) + (matrix[_34] * other.matrix[_41]);
	ret.matrix[_32] = (matrix[_31] * other.matrix[_12]) + (matrix[_32] * other.matrix[_22]) + (matrix[_33] * other.matrix[_32]) + (matrix[_34] * other.matrix[_42]);
	ret.matrix[_33] = (matrix[_31] * other.matrix[_13]) + (matrix[_32] * other.matrix[_23]) + (matrix[_33] * other.matrix[_33]) + (matrix[_34] * other.matrix[_43]);
	ret.matrix[_34] = (matrix[_31] * other.matrix[_14]) + (matrix[_32] * other.matrix[_24]) + (matrix[_33] * other.matrix[_34]) + (matrix[_34] * other.matrix[_44]);

	ret.matrix[_41] = (matrix[_41] * other.matrix[_11]) + (matrix[_42] * other.matrix[_21]) + (matrix[_43] * other.matrix[_31]) + (matrix[_44] * other.matrix[_41]);
	ret.matrix[_42] = (matrix[_41] * other.matrix[_12]) + (matrix[_42] * other.matrix[_22]) + (matrix[_43] * other.matrix[_32]) + (matrix[_44] * other.matrix[_42]);
	ret.matrix[_43] = (matrix[_41] * other.matrix[_13]) + (matrix[_42] * other.matrix[_23]) + (matrix[_43] * other.matrix[_33]) + (matrix[_44] * other.matrix[_43]);
	ret.matrix[_44] = (matrix[_41] * other.matrix[_14]) + (matrix[_42] * other.matrix[_24]) + (matrix[_43] * other.matrix[_34]) + (matrix[_44] * other.matrix[_44]);

	return ret;
}

Matrix Matrix::operator*=(const Matrix& other)
{
	matrix[_11] = (matrix[_11] * other.matrix[_11]) + (matrix[_12] * other.matrix[_21]) + (matrix[_13] * other.matrix[_31]) + (matrix[_14] * other.matrix[_41]);
	matrix[_12] = (matrix[_11] * other.matrix[_12]) + (matrix[_12] * other.matrix[_22]) + (matrix[_13] * other.matrix[_32]) + (matrix[_14] * other.matrix[_42]);
	matrix[_13] = (matrix[_11] * other.matrix[_13]) + (matrix[_12] * other.matrix[_23]) + (matrix[_13] * other.matrix[_33]) + (matrix[_14] * other.matrix[_43]);
	matrix[_14] = (matrix[_11] * other.matrix[_14]) + (matrix[_12] * other.matrix[_24]) + (matrix[_13] * other.matrix[_34]) + (matrix[_14] * other.matrix[_44]);

	matrix[_21] = (matrix[_21] * other.matrix[_11]) + (matrix[_22] * other.matrix[_21]) + (matrix[_23] * other.matrix[_31]) + (matrix[_24] * other.matrix[_41]);
	matrix[_22] = (matrix[_21] * other.matrix[_12]) + (matrix[_22] * other.matrix[_22]) + (matrix[_23] * other.matrix[_32]) + (matrix[_24] * other.matrix[_42]);
	matrix[_23] = (matrix[_21] * other.matrix[_13]) + (matrix[_22] * other.matrix[_23]) + (matrix[_23] * other.matrix[_33]) + (matrix[_24] * other.matrix[_43]);
	matrix[_24] = (matrix[_21] * other.matrix[_14]) + (matrix[_22] * other.matrix[_24]) + (matrix[_23] * other.matrix[_34]) + (matrix[_24] * other.matrix[_44]);

	matrix[_31] = (matrix[_31] * other.matrix[_11]) + (matrix[_32] * other.matrix[_21]) + (matrix[_33] * other.matrix[_31]) + (matrix[_34] * other.matrix[_41]);
	matrix[_32] = (matrix[_31] * other.matrix[_12]) + (matrix[_32] * other.matrix[_22]) + (matrix[_33] * other.matrix[_32]) + (matrix[_34] * other.matrix[_42]);
	matrix[_33] = (matrix[_31] * other.matrix[_13]) + (matrix[_32] * other.matrix[_23]) + (matrix[_33] * other.matrix[_33]) + (matrix[_34] * other.matrix[_43]);
	matrix[_34] = (matrix[_31] * other.matrix[_14]) + (matrix[_32] * other.matrix[_24]) + (matrix[_33] * other.matrix[_34]) + (matrix[_34] * other.matrix[_44]);

	matrix[_41] = (matrix[_41] * other.matrix[_11]) + (matrix[_42] * other.matrix[_21]) + (matrix[_43] * other.matrix[_31]) + (matrix[_44] * other.matrix[_41]);
	matrix[_42] = (matrix[_41] * other.matrix[_12]) + (matrix[_42] * other.matrix[_22]) + (matrix[_43] * other.matrix[_32]) + (matrix[_44] * other.matrix[_42]);
	matrix[_43] = (matrix[_41] * other.matrix[_13]) + (matrix[_42] * other.matrix[_23]) + (matrix[_43] * other.matrix[_33]) + (matrix[_44] * other.matrix[_43]);
	matrix[_44] = (matrix[_41] * other.matrix[_14]) + (matrix[_42] * other.matrix[_24]) + (matrix[_43] * other.matrix[_34]) + (matrix[_44] * other.matrix[_44]);

	return *this;
}

Vector3 Matrix::TransformPoint(const Vector3 & point) const
{
	Vector3 ret;

	ret.x = matrix[_11] * point.x + matrix[_12] * point.y + matrix[_13] * point.z + matrix[_14];
	ret.y = matrix[_21] * point.x + matrix[_22] * point.y + matrix[_23] * point.z + matrix[_24];
	ret.z = matrix[_31] * point.x + matrix[_32] * point.y + matrix[_33] * point.z + matrix[_34];

	return ret;
}

