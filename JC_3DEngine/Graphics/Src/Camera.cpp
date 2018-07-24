#include "Precompiled.h"
#include <Camera.h>

using namespace Graphics;
using namespace Math;

Camera* Camera::main = nullptr;

Camera::Camera()
	: mPosition(0.0f, 0.0f, 0.0f)
	, mDirection(0.0f, 0.0f, 1.0f)
	, mNearPlane(0.1f)
	, mFarPlane(10000.0f)
	, mFOV(60.0f * kDegToRad) //kDegToRad = pi / 180;
	, mAspect(16.0f / 9.0f)
{
	if (!main)
	{
		main = this;
	}
}

void Graphics::Camera::Setup(float nearPlane, float farPlane, float fov, float aspect)
{
	mNearPlane = nearPlane;
	mFarPlane = farPlane;
	mFOV = fov;
	mAspect = aspect;
}

void Graphics::Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Graphics::Camera::Strafe(float distance)
{
	Vector3 right = Vector3::Normalize(Vector3::YAxis().Cross(mDirection)); 
	mPosition += right * distance;
}

void Graphics::Camera::Rise(float distance)
{
	Math::Vector3 up = Vector3::YAxis();
	mPosition += up * distance;
}

void Graphics::Camera::Yaw(float degree)
{
	Matrix matRotate = Matrix::RotateY(degree * kDegToRad);
	mDirection = mDirection.TransformNormal(mDirection, matRotate);
}

void Graphics::Camera::Pitch(float degree)
{
	Vector3 right = Vector3::Normalize(Vector3::YAxis().Cross(mDirection));
	Matrix matRotate = matRotate.RotationAxis(right, degree * kDegToRad);	
	Vector3 newLook = Vector3::TransformNormal(mDirection, matRotate);

	float dot = newLook.Dot(Vector3::YAxis());
	
	if (General::Abs(dot) < 0.995f)
	{
		mDirection = newLook;
	}

}

Matrix Camera::GetViewMatrix() const
{
	Vector3 look = Vector3::Normalize(mDirection);
	Vector3 right = Vector3::Normalize(Vector3::YAxis().Cross(look));
	Vector3 up = Vector3::Normalize(look.Cross(right));

	float x = (-mPosition).Dot(right);
	float y = (-mPosition).Dot(up);
	float z = (-mPosition).Dot(look);

	float data[16] =
	{
		right.x, up.x, look.x, 0.0f,
		right.y, up.y, look.y, 0.0f,
		right.z, up.z, look.z, 0.0f,
		x,		 y,	   z,      1.0f
	};

	Matrix tempMatrix(data);

	return tempMatrix;
}

Matrix Graphics::Camera::GetProjectionMatrix() const
{

	double h = 1.0 / tan(mFOV * 0.5);
	double w = h / mAspect;
	const float f = mFarPlane;
	const float n = mNearPlane;
	double d = f / (f - n);

	float data[16] =
	{
		 (float)w,		 0.0f,		0.0f,		   0.0f,
				0.0f,	 (float)h,	0.0f,		   0.0f,
				0.0f,	 0.0f,		(float)d,	   1.0f,
				0.0f,	 0.0f,		(float)(-n*d), 0.0f
	};
	Matrix tempMatrix;
	for (size_t i = 0; i < 16; i++)
	{
		tempMatrix.matrix[i] = data[i];
	}
	return tempMatrix;
}

Ray Graphics::Camera::ScreenPointToRay(int screenX, int screenY, uint32_t screenWidth, uint32_t screenHeight) const
{
	const float aspect = (float)screenWidth / (float)screenHeight;
	const float halfWidth = screenWidth * 0.5f;
	const float halfHeight = screenHeight * 0.5f;
	const float tanFOV = tanf(mFOV * 0.5f);
	const float dx = tanFOV * ((float)screenX / halfWidth - 1.0f) * aspect;
	const float dy = tanFOV * (1.0f - (float)screenY / halfHeight);

	Ray ray; 
	ray.org = Vector3::Zero();
	ray.dir = Vector3::Normalize(Vector3(dx, dy, 1.0f));

	Matrix invMatView = Matrix::Inverse(GetViewMatrix());
	ray.org = Vector3::TransformCoord(ray.org, invMatView);
	ray.dir = Vector3::TransformNormal(ray.dir, invMatView);

	return ray;
}

