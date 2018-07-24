#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "Particle.h"

using namespace Physics;

PhysicsWorld::PhysicsWorld() :
	mTimer(0.0f)
{

}
PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::Setup(const Settings& settings)
{
	mSettings = settings;
}

void PhysicsWorld::Update(float deltaTime)
{
	AccumulateForces();
	Integrate();
	SatisfyConstraints();
}

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

void Physics::PhysicsWorld::AddConstraint(Constraint * c)
{
	mConstraints.push_back(c);
}

void Physics::PhysicsWorld::AddPlane(const MathLibrary::Plane p)
{
	mPlanes.push_back(p);
}

void Physics::PhysicsWorld::ClearDynamic()
{
	SafeDeleteVector(mParticles);
	SafeDeleteVector(mConstraints);	
}

void Physics::PhysicsWorld::ClearAll()
{
	ClearDynamic();
	mPlanes.clear();
}

void PhysicsWorld::DebugDraw() const
{
	for (auto p : mParticles)
	{
		p->DebugDraw();
	}
	for (auto c : mConstraints)
	{
		c->DebugDraw();
	}
	for (const auto& plane : mPlanes)
	{
		//Graphics::SimpleDraw::AddPlane(plane, position, size, MathLibrary::Vector4::White);
	}

}

void PhysicsWorld::AccumulateForces()
{
	for (auto p : mParticles)
	{
		p->mPosition = mSettings.gravity;
	}
}

void PhysicsWorld::Integrate()
{
	const float kTimeStepSqr = MathLibrary::Sqr(mSettings.timeStep);

	for (auto p : mParticles)
	{
		MathLibrary::Vector3 displacement = p->mPosition - p->mPositionOld + (p->mAcceleration * kTimeStepSqr);
		p->mPositionOld = p->mPosition;
		p->mPosition = p->mPosition + displacement;
	}

}

void PhysicsWorld::SatisfyConstraints()
{
	for (uint32_t n = 0; n < mSettings.iterations; n++)
	{

	}
}