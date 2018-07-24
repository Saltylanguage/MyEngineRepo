#pragma once
#include "Component.h"
#include "CameraComponent.h"


class CameraControllerComponent : public Component
{
public:

	META_CLASS_DECLARE

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:

	float mTurnSpeed;
	float mMoveSpeed;
	CameraComponent* mCameraComponent;

};