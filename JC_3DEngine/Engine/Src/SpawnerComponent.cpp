#include "Precompiled.h"
#include "SpawnerComponent.h"

#include "TransformComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "Input/Inc/InputSystem.h"
#include "Input/Inc/InputTypes.h"



META_DERIVED_BEGIN(SpawnerComponent, Component)
META_FIELD_BEGIN
META_FIELD(mFileName, "FileName")
META_FIELD(mSpawnType, "SpawnType")
META_FIELD_END
META_CLASS_END

SpawnerComponent::SpawnerComponent() :
	mFileName(""),
	mTransformComponent(nullptr),
	mObjectID(0),
	mCounter(0),
	mFireRate(0)
{
}

SpawnerComponent::~SpawnerComponent()
{
}

void SpawnerComponent::Initialize() 
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void SpawnerComponent::Update(f32 deltaTime)
{
	switch ((SpawnType)mSpawnType)
	{
	case timed:
		if (mCounter >= 1.0f)
		{
			Spawn();
			mCounter = 0;
		}
		mCounter += deltaTime;
		break;
	case onClick:
		if (Input::InputSystem::Get()->IsMousePressed(Mouse::LBUTTON) && mCounter >= mFireRate)
		{
			Spawn();
			mCounter = 0;
		}
		mCounter += deltaTime;
		break;
	}
}

void SpawnerComponent::Spawn()
{
	std::string objectName = mFileName.substr(mFileName.rfind("/") + 1);

	objectName = objectName.substr(0, objectName.rfind("."));
	objectName += std::to_string(mObjectID);
	auto handle = GetOwner().GetWorld()->Create(mFileName.c_str(), objectName.c_str());
	GameObject* go = handle.Get();
	TransformComponent* transform = go->GetComponent<TransformComponent>();
	transform->SetPosition(mTransformComponent->GetPosition());
	transform->SetForward(mTransformComponent->GetForward());
	mObjectID++;
}