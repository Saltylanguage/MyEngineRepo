#include "Precompiled.h"

#include "CursorComponent.h"
#include "GameObject.h"
#include "Input/Inc/InputSystem.h"


#include "SpriteComponent.h"

META_DERIVED_BEGIN(CursorComponent, Component)
	META_FIELD_EMPTY
META_CLASS_END

CursorComponent::CursorComponent()
{
}

CursorComponent::~CursorComponent()
{
}

void CursorComponent::Initialize()
{
	mSpriteComponent = GetOwner().GetComponent<SpriteComponent>();
	ASSERT(mSpriteComponent, "[CursorComponent] You are using a CursorComponent without a SpriteComponent in GameObject: %s", GetOwner().GetName());
}

void CursorComponent::Update(f32 deltaTime)
{
	Input::InputSystem* is = Input::InputSystem::Get();
	
	const f32 screenX = (f32)is->GetMouseScreenX();
	const f32 screenY = (f32)is->GetMouseScreenY();
	mSpriteComponent->SetPosition(Math::Vector2(screenX, screenY));
}