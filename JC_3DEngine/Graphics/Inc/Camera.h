#pragma once


#include <Math\Inc\EngineMath.h>

using namespace Math;

namespace Graphics
{
	//NOTE: This is not the best camera in the world!
	//If you want to write a perfect camera, ask Shiva
	
	class Camera
	{
	public:
		static Camera* main;
		Camera();
		~Camera() {};

		void Setup(float nearPlane, float farPlane, float fov, float aspect);

		void Walk(float distance);
		void Strafe(float distance);
		void Rise(float distance);

		void Yaw(float degree);
		void Pitch(float degree);
		
		void SetPosition(const  Vector3& position) { mPosition = position; }
		void SetDirection(const Vector3& direction) { mDirection = direction; }

		const Vector3& GetPosition() const { return mPosition; }
		const Vector3& GetDirection() const { return mDirection; }

		Matrix GetViewMatrix() const;
		Matrix GetProjectionMatrix() const;

		Ray ScreenPointToRay(int screenX, int screenY, uint32_t screenWidth, uint32_t screenHeight) const;

	private:

		Vector3 mPosition;
		Vector3 mDirection;
		Vector3 mRight;

		float mNearPlane, mFarPlane;
		float mFOV, mAspect;

	};



}