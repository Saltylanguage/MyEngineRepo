#pragma once
#include <Math\Inc\EngineMath.h>

using namespace Math;

namespace Graphics
{
	class KeyFrame
	{
		friend class Animation;
	public:

		Vector3 position;
		Vector3 scale;
		Quaternion rotation;

		float time;

		Matrix posVecToMatrix()
		{
			return Matrix
			(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				position.x, position.y, position.z, 1
			);
		}

		Matrix scaleVecToMatrix()
		{
			return Matrix
			(
				scale.x, 0, 0, 0,
				0, scale.y, 0, 0,
				0, 0, scale.z, 0,
				0, 0, 0, 1
			);
		}

		Matrix rotVecToMatrix()
		{
			return Matrix
			(
				rotation.QuaternionToMatrix()
			);
		}

		void SetPosition(const Vector3& pos) { position = pos; }
		void SetScale(const Vector3& s) { scale = s; }
		void SetRotation(const Quaternion& rot) { rotation = rot; }
		void SetTime(float t) { time = t; }

		Matrix GetTransform()
		{
			return rotVecToMatrix() * scaleVecToMatrix() * posVecToMatrix();
		}

		static KeyFrame Lerp(const KeyFrame& A, const KeyFrame& B, float t)
		{
			KeyFrame keyFrame;
			keyFrame.position = Vector3::Lerp(A.position, B.position, t);
			keyFrame.scale = Vector3::Lerp(A.scale, B.scale, t);
			keyFrame.rotation = Quaternion::Lerp(A.rotation, B.rotation, t);

			return keyFrame;
		}
	};
}

//BUild robotic arm
//Key 1 and 2 rotate first joint
//key 2 and 3 rotate second joint
//key 3 and 4 rotate third joint
//etc.