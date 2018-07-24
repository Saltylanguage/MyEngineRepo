#include "Precompiled.h"
#include "Particle.h"

using namespace Physics;



Particle::Particle() :
	mPosition(0.0f, 0.0f, 0.0f),
	mPositionOld(0.0f, 0.0f, 0.0f),
	mAcceleration(0.0f,0.0f, 0.0f),
	mRadius(0.0f),
	mInvMass(0.0f)
{
}

Particle::Particle(const MathLibrary::Vector3& pos) :
	mPosition(pos),
	mPositionOld(pos),
	mAcceleration(0.0f, 0.0f, 0.0f),
	mRadius(0.02f),
	mInvMass(1.0f)
{}

Particle::Particle(const MathLibrary::Vector3& pos, float radius, float invMass) :
	mPosition(pos),
	mPositionOld(pos),
	mAcceleration(0.0f, 0.0f, 0.0f),
	mRadius(radius),
	mInvMass(invMass)
{}

void Particle::DebugDraw()
{
	Graphics::SimpleDraw::AddSphere(MathLibrary::Sphere(mPosition, mRadius), MathLibrary::Vector4::Cyan, 4, 2);
}

void Particle::SetPosition(const MathLibrary::Vector3& pos)
{
	mPosition = mPositionOld = pos;	
}


void Particle::SetVelocity(const MathLibrary::Vector3& vel)
{
	mPositionOld = mPosition - vel;
}