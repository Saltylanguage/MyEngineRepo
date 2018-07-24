#include "Precompiled.h"

#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "Math\Inc\EngineMath.h"
#include "Input\Inc\InputSystem.h"
#include "Input\Inc\InputTypes.h"
#include "GameObject.h"
#include "Graphics\SimpleDraw.h"

using namespace Math;

META_DERIVED_BEGIN(ProjectileComponent, Component)
META_FIELD_BEGIN
//META_FIELD(mSphere.radius, "SphereRadius")
//META_FIELD(mSphere.center, "SphereCenter")
META_FIELD(mSphereRadius, "SphereRadius")
META_FIELD(mSpeedFactor, "Speed")
META_FIELD(mColor, "Color")
META_FIELD_END
META_CLASS_END

void ProjectileComponent::Initialize()
{
	mTransform = GetOwner().GetComponent<TransformComponent>();	
}

void ProjectileComponent::Update(f32 deltaTime)
{	

	mVelocity = Math::Vector3::Normalize(mTransform->GetForward()) * mSpeedFactor;
	mTransform->SetPosition(mTransform->GetPosition() + mVelocity);
	Graphics::SimpleDraw::AddSphere(mTransform->GetPosition(), mSphereRadius, Vector4(mColor.r, mColor.g, mColor.b, mColor.a), 10, 10);
}

