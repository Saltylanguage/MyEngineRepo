#pragma once
#include "Component.h"

enum SpawnType
{
	none = 0,
	timed,
	onClick
};

class TransformComponent;
class SpawnerComponent : public Component
{
public:
	META_CLASS_DECLARE

		SpawnerComponent();
		~SpawnerComponent() override;

	void Initialize() override;
	void Update(f32 deltaTime) override;

	void Spawn();
	
	void SetFileName(std::string name) { mFileName = name; }
	std::string GetFileName() { return mFileName; }

private:

	std::string mFileName;
	size_t mObjectID;
	TransformComponent* mTransformComponent;
	int mSpawnType;

	float mCounter;
	float mFireRate;

};