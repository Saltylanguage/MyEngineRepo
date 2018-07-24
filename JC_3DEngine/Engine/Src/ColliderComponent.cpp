#include "Precompiled.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Graphics/Inc/SimpleDraw.h"
#include "Math/Inc/EngineMath.h"
#include "Graphics/Inc/Color.h"

using namespace Graphics;


META_DERIVED_BEGIN(ColliderComponent, Component)
META_FIELD_BEGIN
META_FIELD(mCenter, "Center")
META_FIELD(mExtend, "Extend")
META_FIELD(mColor, "Color")
META_FIELD_END
META_CLASS_END

ColliderComponent::ColliderComponent()
	: mTransformComponent(nullptr)
	, mCenter(Math::Vector3::Zero())
	, mExtend(Math::Vector3::One())
	, mColor(Graphics::Color::Green())	
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Initialize()
{
mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void ColliderComponent::Render()
{
	Vector4 color;
	color.x = mColor.r;
	color.y = mColor.g;
	color.z = mColor.b;
	color.w = mColor.a;
	Graphics::SimpleDraw::AddAABB(GetAABB(), color);
}

Math::AABB ColliderComponent::GetAABB() const
{
	Math::Vector3 pos = mTransformComponent->GetPosition();
	return Math::AABB(mCenter + pos, mExtend);
}