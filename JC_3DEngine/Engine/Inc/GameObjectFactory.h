#ifndef INCLUDED_ENGINE_GAMEOBJECTFACTORY_H
#define INCLUDED_ENGINE_GAMEOBJECTFACTORY_H

#include "GameObject.h"

class GameObjectFactory
{
public:
	GameObjectFactory(u16 capacity);

	GameObjectHandle Create(const char* templateFilename);
	void Destroy(GameObjectHandle handle);

private:
	GameObjectAllocator mGameObjectAllocator;
};

#endif // #ifndef INCLUDED_ENGINE_GAMEOBJECTFACTORY_H