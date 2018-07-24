#pragma once
#include "GameObjectFactory.h"

class GameWorld
{
public:
	GameWorld(u32 capacity);
	~GameWorld();

	void Initialize();
	void Terminate();

	GameObjectHandle Create(const char* templateFileName, const char* name);
	GameObjectHandle Find(const char* name);
	void Destroy(GameObjectHandle handle);

	void Update(f32 deltaTime);
	void Render();
	void Render2D();

	void LoadLevel(const char* levelFileName);

private:
	typedef std::vector<GameObject*> GameObjectList;
	typedef std::vector<GameObjectHandle> DestroyList;

	void DestroyInternal(GameObjectHandle handle);
	void ProcessDestroyList();

	GameObjectFactory mGameObjectFactory;
	GameObjectList mUpdateList;
	DestroyList mDestroyList;

	bool mIsUpdating;
};