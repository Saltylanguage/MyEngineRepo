#pragma once


namespace Physics
{
	class Particle
	{

	public:
		Particle();
		Particle(const MathLibrary::Vector3& pos);
		Particle(const MathLibrary::Vector3& pos, float radius = 0.01f, float invMass = 1.0f);

		void DebugDraw() const ;

		void SetPosition(const MathLibrary::Vector3& pos);
		void SetVelocity(const MathLibrary::Vector3& vel);

	
		MathLibrary::Vector3 mPosition;
		MathLibrary::Vector3 mPositionOld;
		MathLibrary::Vector3 mAcceleration;

		float mRadius;
		float mInvMass;

		~Particle() {}
	};

}