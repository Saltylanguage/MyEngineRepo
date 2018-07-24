#include "Precompiled.h"

#include "TransformComponent.h"

#include "GameObject.h"

META_DERIVED_BEGIN(TransformComponent, Component)
META_FIELD_BEGIN
	META_FIELD(mPosition, "Position")
	META_FIELD(mForward, "Forward")
META_FIELD_END
META_CLASS_END

TransformComponent::TransformComponent()
	: mPosition(Math::Vector3::Zero())
	, mForward(Math::Vector3::ZAxis())
{
}

TransformComponent::~TransformComponent()
{
}

Math::Matrix TransformComponent::GetLocalToWorld() const
{
	Math::Vector3 yAxis = Math::Vector3::YAxis();
	Math::Vector3 forward = Math::Vector3::Normalize(mForward);
	Math::Vector3 side = Math::Vector3::Cross(yAxis, forward);
	Math::Vector3 up = Math::Vector3::Cross(forward, side);
	Math::Vector3 pos = mPosition;

	return Math::Matrix
	(
		side.x, side.y, side.z, 0.0f,
		up.x, up.y, up.z, 0.0f,
		forward.x, forward.y, forward.z, 0.0f,
		pos.x, pos.y, pos.z, 1.0f
	);
}


