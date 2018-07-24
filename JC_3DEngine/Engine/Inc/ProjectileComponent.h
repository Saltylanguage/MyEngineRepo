#pragma once
#include "Component.h"
#include "ColliderComponent.h"



class ProjectileComponent : public Component
{
public:

	META_CLASS_DECLARE

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:

	Math::Vector3 mVelocity;
	float mSpeedFactor;
	Graphics::Color mColor;
	
	//Math::Sphere mSphere;

	float mSphereRadius;
	
	TransformComponent* mTransform;
	

};