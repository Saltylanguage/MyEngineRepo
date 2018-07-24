#pragma once
#include "Component.h"
#include "Math/Inc/EngineMath.h"

class TransformComponent : public Component
{
public:
	META_CLASS_DECLARE

	TransformComponent();
	~TransformComponent() override;

	Math::Matrix GetLocalToWorld() const;

	void SetPosition(const Math::Vector3& pos)		{ mPosition = pos; }
	void SetForward(const Math::Vector3& forward)	{ mForward = forward; }

	const Math::Vector3& GetPosition() const		{ return mPosition; }
	const Math::Vector3& GetForward() const			{ return mForward; }

private:
	Math::Vector3 mPosition;
	Math::Vector3 mForward;
};

