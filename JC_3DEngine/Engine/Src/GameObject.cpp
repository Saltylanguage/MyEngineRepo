#include "Precompiled.h"
#include "GameObject.h"
#include <Core\Inc\Core.h>



GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (auto component : mComponents)
	{
		SafeDelete(component);
	}
}

void GameObject::Initialize()
{
	for (auto component : mComponents)
	{
		component->Initialize();
	}
}

void GameObject::Terminate()
{
		for (auto component : mComponents)
		{
			component->Terminate();
		}
}

void GameObject::Update(f32 deltaTime)
{
	for (auto component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	for (auto component : mComponents)
	{
		component->Render();
	}
}

void GameObject::Render2D()
{
		for (auto component : mComponents)
		{
			component->Render2D();
		}
}

void GameObject::AddComponent(Component * component)
{
	ASSERT(component->mGameObject == nullptr, 
	"[GameObject] Cannot add a component associated with another game object.");
	component->mGameObject = this;
	mComponents.push_back(component);
}

const char * GameObject::GetName()
{
	return mName.c_str();
}

const GameObjectHandle GameObject::GetHandle()
{
	return mHandle;
}

