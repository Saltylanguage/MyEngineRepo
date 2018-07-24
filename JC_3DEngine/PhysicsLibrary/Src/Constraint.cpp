#include "Precompiled.h"
#include "Constraint.h"

#include "Particle.h"

using namespace Physics;

Fixed::Fixed(Particle* p) :
	mParticle(p),
	mLocation(p->mPosition) {}

Fixed::Fixed(Particle* p, const MathLibrary::Vector3& location) :
	mParticle(p),
	mLocation(location)
{

}

void Fixed::Apply()
{
	mParticle->SetPosition(mLocation);
}

//void Fixed::DebugDraw()
//{
//	Graphics::SimpleDraw::AddAABB(mLocation, 0.1f, MathLibrary::Vector4::Cyan());
//}

Spring::Spring(Particle* a, Particle* b, float restLength) :
	mparticleA(a),
	mparticleB(b),
	mRestLength(restLength)
{
	if (mRestLength <= 0.0f)
	{
		mRestLength = MathLibrary::Distance(a->mPosition, b->mPosition);
	}
}

void Spring::Apply()
{
	MathLibrary::Vector3 delta = mparticleB->mPosition - mparticleA->mPosition;
	//float dist = MathLibrary::Vector3::Length(delta);
	/*float diff(dist - mRestLength) / (dist * (mparticleA->mInvMass + mparticleB->mInvMass);*/
	//mparticleA->mPosition += delta * diff * mparticleA->mInvMass;
	//mparticleB->mPosition += delta * diff * mparticleB->mInvMass;
}

void Spring::DebugDraw()
{
	Graphics::SimpleDraw::AddLine(mparticleA->mPosition, mparticleB->mPosition, MathLibrary::Vector4::Green);
}
