#pragma once
#ifndef INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

//Description: Class for the game application

#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>



class GameApp : public Core::Application
{
public:
	GameApp();

	virtual ~GameApp();

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;

	//Window
	Core::Window mWindow;
	Core::Timer mTimer;

	//C++ Constant Buffer Structs
	struct WorldInfo
	{
		Matrix world;
		Matrix wvp;

		Vector3 cameraPosition;
	};

	struct FireInfo
	{
		Matrix wvp;
	};

	//Camera
	Graphics::Camera mCamera;

	//Meshes
	Graphics::Mesh mMesh;

	//Mesh Buffers
	Graphics::MeshBuffer mMeshBuffer;

	//Constant Buffers
	Graphics::TypedConstantBuffer<WorldInfo> mWorldBuffer;

	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;

	//Texture
	Graphics::Texture mFireDiffuse;
	Graphics::Texture mFireNoise;
	Graphics::Texture mFireAlpha;
	
	Graphics::ScreenMeshBuffer fireMeshBuffer;

	//Sampler
	Graphics::Sampler mClampSampler;
	Graphics::Sampler mWrapSampler;

	Graphics::BlendState mBlendState;

};

#endif //ifndef INCLUDED_GAMEAPP_H




//set up an array of objects
// first pass paint render id's set to a different shaders
//different colors for different objects

// second pass is for visualization of the scene