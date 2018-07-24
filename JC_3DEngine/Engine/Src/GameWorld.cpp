#include "Precompiled.h"
#include "GameWorld.h"


#include "GameObject.h"
#include "TransformComponent.h"
#include "Utils.h"
#include "Externals/TinyXML/tinyxml.h"


GameWorld::GameWorld(u32 capacity)
	:mGameObjectFactory(capacity)
	, mIsUpdating(false)
{}

GameWorld::~GameWorld()
{}

void GameWorld::Initialize()
{
}

void GameWorld::Terminate()
{
	ASSERT(!mIsUpdating, "[World] Cannot terminate world during update.");

	//Add all active objects to the destroy list
	for (auto gameObject : mUpdateList)
	{
		mDestroyList.push_back(gameObject->GetHandle());
	}


	// Now Destroy Everything
	ProcessDestroyList();
}

GameObjectHandle GameWorld::Create(const char * templateFileName, const char * name)
{
	GameObjectHandle handle = mGameObjectFactory.Create(templateFileName);
	ASSERT(handle.IsValid(), "[GameWorld] Failed to create game object with template %s", templateFileName);

	//Initialize the Game Object
	GameObject* gameObject = handle.Get();
	gameObject->mWorld = this;
	gameObject->mHandle = handle;
	gameObject->mName = name;
	gameObject->Initialize();

	mUpdateList.push_back(gameObject);

	return handle;
}

GameObjectHandle GameWorld::Find(const char * name)
{
	for (auto gameObject : mUpdateList)
	{
		if (Utils::AreEqual(gameObject->GetName(), name))
		{
			return gameObject->GetHandle();
		}
	}
	return GameObjectHandle();
}

void GameWorld::Destroy(GameObjectHandle handle)
{
	// if handle is invalid do nothing
	if (!handle.IsValid())
	{
		return;
	}
	if (!mIsUpdating)
	{
		DestroyInternal(handle);
	}
	else
	{
		mDestroyList.push_back(handle);
	}
}

void GameWorld::Update(f32 deltaTime)
{
	ASSERT(!mIsUpdating, "[World] Already Updating the World");

	//Lock the update List
	mIsUpdating = true;

	for (u32 i = 0; i < (u32)mUpdateList.size(); ++i)
	{
		GameObject*  gameObject = mUpdateList[i];
		gameObject->Update(deltaTime);
	}

	//Unlock the update list
	mIsUpdating = false;

	//Now we can safely destroy objects
	ProcessDestroyList();
}

void GameWorld::Render()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}

void GameWorld::Render2D()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render2D();
	}
}

void GameWorld::LoadLevel(const char * levelFileName)
{
	TiXmlDocument levelDoc;
	levelDoc.LoadFile(levelFileName);

	const TiXmlNode* levelNode = levelDoc.FirstChild();
	if (Utils::AreEqual(levelNode->Value(), "GameObjects"))
	{
		const TiXmlNode* gameObjectNode = levelNode->FirstChild();
		if (Utils::AreEqual(gameObjectNode->Value(), "GameObject"))
		{
			while (gameObjectNode)
			{
				const TiXmlNode* NameNode = gameObjectNode->FirstChild();
				if (NameNode == nullptr)
					return;
				if (Utils::AreEqual(NameNode->Value(), "Name"))
				{
					const TiXmlNode* fileNameNode = NameNode->NextSibling();	
					Create(fileNameNode->FirstChild()->Value(), NameNode->FirstChild()->Value());				
				}
				gameObjectNode = gameObjectNode->NextSibling();
			}
		}
	}
}
//Homework
//Load level xml doc
//Parse for name, template and call create to spawn each object
//Apply instant specific data


void GameWorld::DestroyInternal(GameObjectHandle handle)
{
	ASSERT(!mIsUpdating, "[World] Cannot destroy game objects during update.");

	if (!handle.IsValid())
	{
		return;
	}
	//Terminate Game Object
	GameObject* gameObject = handle.Get();
	gameObject->Terminate();

	auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);
	if (iter != mUpdateList.end())
	{
		mUpdateList.erase(iter);
	}
	//Now we can safely Destroy the game object
	mGameObjectFactory.Destroy(handle);
}

void GameWorld::ProcessDestroyList()
{
	for (auto handle : mDestroyList)
	{
		DestroyInternal(handle);
	}
	mDestroyList.clear();
}



//TODO Separate camera into 2 components:
	//1) Camera Component
	//2) Camera Controller

//TODO Make sure Terrain Component is working

//TODO Create Spawner Component
	//Needs 2 Things
		//1) Template Name
		//2) Instance Data (Name, Position)