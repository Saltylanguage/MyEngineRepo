#pragma once

#include "Component.h"
#include "TypeAllocator.h"


class GameObject;
class GameWorld;

typedef TypeHandle<GameObject> GameObjectHandle;
typedef TypeAllocator<GameObject> GameObjectAllocator;


class GameObject
{
public:
	GameObject();
	~GameObject();

	void Initialize();
	void Terminate();

	void Update(f32 deltaTime);
	void Render();
	void Render2D();

	void AddComponent(Component* component);

	template <typename T>
	T* GetComponent();
	template <typename T>
	const T* GetComponent() const;

	GameWorld* GetWorld() { return mWorld; }

private:
	friend class GameWorld;

	GameWorld* mWorld;
	GameObjectHandle mHandle;
	std::string mName;

	typedef std::vector<Component*> Components;
	Components mComponents;

public:

	const char* GetName();
	const GameObjectHandle GetHandle();
};

class TransformComponent;
class ColliderComponent;

//template<>
//inline TransformComponent* GameObject::GetComponent()
//{
//	return (TransformComponent*)(mComponents[0]);
//}
//
//template<>
//inline ColliderComponent* GameObject::GetComponent()
//{
//	return (ColliderComponent*)(mComponents[1]);
//}

template<typename T>
T * GameObject::GetComponent()
{
	const GameObject* constMe = this;

	return const_cast<T*>(constMe->GetComponent<T>());
}

template<typename T>
const T* GameObject::GetComponent() const
{
	for (auto c : mComponents)
	{
		if (c->GetMetaClass() == T::StaticGetMetaClass())
		{
			return static_cast<const T*>(c);
		}
	}
	return nullptr;
}



//Homework:

// Step 1: Allocate a new game object
// Step 2: Load Template file using TiXMLDocument::LoadFile();
// Step 3:
//			TiXmlNode::FirstChild()
//			TiXmlNode::NextSibling()
//			TiXmlNode::Value()
// Step 4: Add Components to the game object
// Step 5: Return the handle
