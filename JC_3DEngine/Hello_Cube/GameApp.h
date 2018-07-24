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

	Math::Matrix mRotation;
	Math::Vector3 mScale;
	int mIndexCount;
	

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

	//Dungeon Gen Stuff
	std::vector<Rect> cells;

	void DrawMesh(Vector3 position, Math::Matrix rotation, Vector3 scale, int indexCount);
	void DrawMeshAtLocation(Vector3 position);
	void SetTexture(Graphics::Texture& texture, Graphics::Sampler& sampler);
	void SetMesh(Graphics::MeshBuffer& meshbuffer);

	void DrawRooms()
	{
		for (size_t i = 0; i < cells.size(); i++)
		{
			
			Vector3 position;
			position.x = (cells[i].right + cells[i].left) / 2.0f;
			position.y = 0;
			position.z = (cells[i].top + cells[i].bottom) / 2.0f;

			mScale.x = abs(cells[i].right -  position.x);
			mScale.y = 1.0f;
			mScale.z = abs(cells[i].bottom - position.z);

			DrawMeshAtLocation(position);
		}
	}

};

