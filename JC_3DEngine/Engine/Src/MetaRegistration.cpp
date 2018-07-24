#include "Precompiled.h"


#include <Meta\Inc\MetaRegistry.h>
#include "MetaRegistration.h"
#include <Graphics\Inc\Camera.h>

#include <Component.h>

#include "Component.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "ColliderComponent.h"
#include "CursorComponent.h"
#include "ModelComponent.h"
#include "ProjectileComponent.h"
#include "SpawnerComponent.h"

//#include "SpriteComponent.h"
#include "TerrainComponent.h"
#include "TransformComponent.h"

void MetaRegistration()
{
#define REGISTER(x)\
	MetaRegistry::Register(x::StaticGetMetaClass())

	//Componenets
	REGISTER(Component);
	REGISTER(CameraComponent);
	REGISTER(CameraControllerComponent);
	REGISTER(ColliderComponent);
	REGISTER(CursorComponent);
	REGISTER(ModelComponent);
	REGISTER(ProjectileComponent);
	REGISTER(SpawnerComponent);
	//REGISTER(SpriteComponent);
	REGISTER(TerrainComponent);
	REGISTER(TransformComponent);

#undef REGISTER
}