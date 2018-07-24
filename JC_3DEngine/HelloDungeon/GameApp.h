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

	//Meshes
	Graphics::Mesh mMesh;
	Graphics::MeshBuffer mMeshBuffer;

	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;

	//Textures
	Graphics::Texture mTexture;
	
	//Sampler
	Graphics::Sampler mSampler;

	//Boxes for Dungeon Generation
	std::vector<Rect> cells;
	std::vector<Vector3> scales;
	std::vector<Math::Vector3> cellPositions;
	
	void RandomizeCells();
	void ClearCells();
	void ResolveSpecificOverlap(const int xIndex, const int yIndex);
	void ResolveAllOverlaps();

	void DrawMesh(Vector3 position, Math::Matrix rotation, Vector3 scale, int indexCount);
	void DrawMeshAtLocation(Vector3 position);

	void SetTexture(Graphics::Texture& texture, Graphics::Sampler& sampler);
	void SetMesh(Graphics::MeshBuffer& meshbuffer);



};

