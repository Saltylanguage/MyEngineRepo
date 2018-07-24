#pragma once

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

	//Camera
	struct CB
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};
	Graphics::Camera mCamera;
	Graphics::TypedConstantBuffer<CB> mConstantBuffer;

	//Mesh
	Graphics::Mesh mMesh;
	Graphics::MeshBuffer mMeshBuffer;

	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;

	//Texture
	Graphics::Texture mTexture;
	Graphics::Sampler mSampler;

};

