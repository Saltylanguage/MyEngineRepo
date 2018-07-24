#pragma once
#include "Constraint.h"

namespace Physics
{

	class Particle;

	struct Settings
	{
		Settings() :
			gravity(0.0f, -9.81f, 0.0f),
			timeStep(1.0f / 60.0f),
			drag(0.0f),
			iterations(1)
		{}


		MathLibrary::Vector3 gravity;
		float timeStep;
		float drag;
		uint32_t iterations;

	};


	class PhysicsWorld
	{

	public:

		PhysicsWorld();
		~PhysicsWorld();

		void Setup(const Settings& settings);

		void Update(float deltaTime);

		void AddParticle(Particle* p);
		void AddConstraint(Constraint* c);
		void AddPlane(const MathLibrary::Plane p);
		void ClearDynamic();
		void ClearAll();

		void DebugDraw() const;

	private:

		void AccumulateForces();
		void Integrate();
		void SatisfyConstraints();

		typedef std::vector<Particle*> Particles;
		typedef std::vector<Constraint*> Constraints;
		typedef std::vector<MathLibrary::Plane> Planes;

		Settings mSettings;
		Particles mParticles;
		Constraints mConstraints;
		Planes mPlanes;

		float mTimer;

	};


}   //namespace physics
