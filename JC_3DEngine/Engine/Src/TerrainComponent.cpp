#include "Precompiled.h"

#include "TerrainComponent.h"
#include "CameraComponent.h"

#include "GameObject.h"

META_DERIVED_BEGIN(TerrainComponent, Component)
META_FIELD_BEGIN
META_FIELD(mTerrainFileName, "TerrainFileName")
META_FIELD(mWidth, "Width")
META_FIELD(mLength, "Length")
META_FIELD(mScale, "Scale")
META_FIELD(mBaseTextureFileName, "BaseTexture")
META_FIELD(mMainTextureFileName, "MainTexture")
META_FIELD_END
META_CLASS_END

TerrainComponent::TerrainComponent() :
	mMaxHeight(30) {}


TerrainComponent::~TerrainComponent()
{
}

void TerrainComponent::Initialize()
{
	mTerrain.Initialize(mTerrainFileName.c_str(), (uint32_t)mLength, (uint32_t)mWidth, mMaxHeight);
	
	mBaseLayer.Initialize(std::wstring(mBaseTextureFileName.begin(), mBaseTextureFileName.end()).c_str());
	mMainLayer.Initialize(std::wstring(mMainTextureFileName.begin(), mMainTextureFileName.end()).c_str());
	
	mTerrain.SetLayer(&mBaseLayer, 0, 0.0f, 20.0f, 17.0f); //TODO EXpose these to xml
	mTerrain.SetLayer(&mMainLayer, 1, 10.0f, 30.0f, 21.0f);		
	
	mTerrain.SetCamera(*Graphics::Camera::main);
}

void TerrainComponent::Render()
{
	mTerrain.Render(*Graphics::Camera::main);
}

void TerrainComponent::Terminate()
{
	mTerrain.Terminate();
	mBaseLayer.Terminate();
	mMainLayer.Terminate();
}