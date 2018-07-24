#include "Precompiled.h"
#include "CameraControllerComponent.h"
#include "TransformComponent.h"
#include "Input/Inc/InputSystem.h"
#include "Input/Inc/InputTypes.h"
#include "GameObject.h"

using namespace Input;

META_DERIVED_BEGIN(CameraControllerComponent, Component)
META_FIELD_BEGIN
META_FIELD(mMoveSpeed, "MoveSpeed")
META_FIELD(mTurnSpeed, "TurnSpeed")
META_FIELD_END
META_CLASS_END

void CameraControllerComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
}

void CameraControllerComponent::Update(f32 deltaTime)
{

	if (InputSystem::Get()->IsKeyDown(Keys::W))
	{
		mCameraComponent->GetCamera().Walk(mMoveSpeed * deltaTime);
	}
	if (InputSystem::Get()->IsKeyDown(Keys::S))
	{
		mCameraComponent->GetCamera().Walk(-mMoveSpeed * deltaTime);
	}
	if (InputSystem::Get()->IsKeyDown(Keys::D))
	{
		mCameraComponent->GetCamera().Strafe(mMoveSpeed * deltaTime);
	}
	if (InputSystem::Get()->IsKeyDown(Keys::A))
	{
		mCameraComponent->GetCamera().Strafe(-mMoveSpeed * deltaTime);
	}

	mCameraComponent->GetCamera().Yaw(mTurnSpeed * deltaTime * InputSystem::Get()->GetMouseMoveX());
	mCameraComponent->GetCamera().Pitch(mTurnSpeed * deltaTime * InputSystem::Get()->GetMouseMoveY());

	if (GetOwner().GetComponent<TransformComponent>())
	{
		GetOwner().GetComponent<TransformComponent>()->SetPosition(mCameraComponent->GetCamera().GetPosition());
		GetOwner().GetComponent<TransformComponent>()->SetForward(mCameraComponent->GetCamera().GetDirection());
	}
}

