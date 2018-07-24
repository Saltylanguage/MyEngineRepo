#pragma once
#include "Component.h"
#include <Math/Inc/EngineMath.h>
#include <Graphics/Inc/Terrain.h>
#include <Graphics/Inc/GraphicsSystem.h>
#include <Graphics/Inc/Texture.h>

class TerrainComponent : Component
{
public:
	META_CLASS_DECLARE


	TerrainComponent();
	~TerrainComponent() override;

	void Initialize() override;
	void Render() override;
	void Terminate() override;

private:

	std::string mTerrainFileName;

	std::string mBaseTextureFileName;
	std::string mMainTextureFileName;

	float mWidth;
	float mLength;
	float mMaxHeight;
	float mScale;
	Graphics::Terrain mTerrain;
	Graphics::Texture mBaseLayer;
	Graphics::Texture mMainLayer;
	
};

