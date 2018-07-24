
#include "Precompiled.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

#include "TransformComponent.h"
#include "XMLReader.h"

#include "Utils.h"
#include "Externals\TinyXML\tinyxml.h"

#pragma region Unimplemented Components
// Components
//#include "AIComponent.h"
//#include "CameraComponent.h"
//#include "CameraControllerComponent.h"
//#include "ColliderComponent.h"
//#include "CursorComponent.h"
//#include "FSMComponent.h"
//#include "HealthComponent.h"
//#include "ModelComponent.h"
//#include "PathingComponent.h"
//#include "PlayerComponent.h"
//#include "ProjectileComponent.h"
//#include "RTSCameraControllerComponent.h"
//#include "SpawnerComponent.h"
//#include "SpriteComponent.h"
//#include "TeamComponent.h"
//#include "TerrainComponent.h"
//#include "TowerComponent.h"
//#include "WeaponComponent.h"
#pragma endregion

namespace
{
	const char* ReadString(const TiXmlNode* stringNode)
	{
		return stringNode->FirstChild()->Value();
	}

	bool ReadBool(const TiXmlNode* node)
	{
		return Utils::AreEqual(node->FirstChild()->Value(), "True");
	}

	s32 ReadS32(const TiXmlNode* node)
	{
		return (s32)atoi(node->FirstChild()->Value());
	}

	u32 ReadU32(const TiXmlNode* node)
	{
		return (u32)atoi(node->FirstChild()->Value());
	}

	f32 ReadFloat(const TiXmlNode* node)
	{
		return (f32)atof(node->FirstChild()->Value());
	}

	Math::Vector3 ReadVector(const TiXmlNode* vectorNode)
	{
		const TiXmlNode* xNode = vectorNode->FirstChild();
		const TiXmlNode* yNode = vectorNode->FirstChild()->NextSibling();
		const TiXmlNode* zNode = vectorNode->FirstChild()->NextSibling()->NextSibling();
		f32 x = ReadFloat(xNode);
		f32 y = ReadFloat(yNode);
		f32 z = ReadFloat(zNode);
		return Math::Vector3(x, y, z);
	}

	Math::Vector4 ReadColor(const TiXmlNode* colorNode)
	{
		const TiXmlNode* rNode = colorNode->FirstChild();
		const TiXmlNode* gNode = colorNode->FirstChild()->NextSibling();
		const TiXmlNode* bNode = colorNode->FirstChild()->NextSibling()->NextSibling();
		const TiXmlNode* aNode = colorNode->FirstChild()->NextSibling()->NextSibling()->NextSibling();
		f32 r = ReadFloat(rNode);
		f32 g = ReadFloat(gNode);
		f32 b = ReadFloat(bNode);
		f32 a = ReadFloat(aNode);
		return Math::Vector4(r, g, b, a);
	}
}

GameObjectFactory::GameObjectFactory(u16 capacity)
	: mGameObjectAllocator(capacity)
{
}

GameObjectHandle GameObjectFactory::Create(const char* templateFilename)
{
	GameObjectHandle handle = mGameObjectAllocator.New();
	GameObject* gameObject = handle.Get();

	TiXmlDocument templateDoc;
	VERIFY(templateDoc.LoadFile(templateFilename), "[GameObjectFactory] Failed to open template file '%s'.", templateFilename);

	const TiXmlNode* gameObjectNode = templateDoc.FirstChild();
	if (Utils::AreEqual(gameObjectNode->Value(), "GameObject"))
	{
		const TiXmlNode* componentsNode = gameObjectNode->FirstChild();
		if (Utils::AreEqual(componentsNode->Value(), "Components"))
		{
			const TiXmlNode* nextComponentNode = componentsNode->FirstChild();
			while (nextComponentNode != nullptr)
			{
				const char* componentName = nextComponentNode->Value();

				const MetaClass* metaClass = MetaRegistry::GetMetaClass(componentName);
				if (metaClass == nullptr)
				{
					LOG("Class [%s] not registered wtih the meta system. Ignoring....", componentName);
				}
				else
				{
					void* newComponent = metaClass->Create();
					const TiXmlNode* data = nextComponentNode->FirstChild();
					bool success = XMLReader::Read(newComponent, metaClass, data);
					if (!success)
					{
						LOG("Problem reading XML template %s", templateFilename);
					}
					gameObject->AddComponent((Component*)newComponent);
				}


				nextComponentNode = nextComponentNode->NextSibling();
			}
		}
	}

	return handle;
}

void GameObjectFactory::Destroy(GameObjectHandle handle)
{
	// This will automatically invalidate all existing handle to this object
	mGameObjectAllocator.Delete(handle);
}