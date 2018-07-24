#pragma once


//Description: Class for the game application

#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>
#include <Input\Inc\Input.h>

class GameApp : public Core::Application
{

	struct Room
	{
		Rect bounds;
		Vector3 center;
	};

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
	Graphics::Texture mMainRoomTexture;
	Graphics::Texture mRegularRoomTexture;
	Graphics::Sampler mSampler;

	//Boxes for Dungeon Generation
	std::vector<Rect> cells;
	std::vector<Room> allRooms;
	std::vector<Room> mainRooms;
	std::vector<Room> RegularRooms;

	float mainRoomThreshold = 0.0f;
	float maxNumRooms = 1.0f;

	Math::Matrix mRotation;
	Math::Vector3 mScale;
	int mIndexCount;

	void DrawMesh(Vector3 position, Math::Matrix rotation, Vector3 scale, int indexCount);
	void DrawMeshAtLocation(Vector3 position);
	void SetTexture(Graphics::Texture& texture, Graphics::Sampler& sampler);
	void SetMesh(Graphics::MeshBuffer& meshbuffer);


	void RandomizeCells();
	void ClearCells();
	void ResolveSpecificOverlap(const int xIndex, const int yIndex);
	void ResolveAllOverlaps();

	float FindRoomSize(Rect cell); // Note: size is measured by area
	
	void SetAllRoomPositions();
	void SetMainRoomPositions();
	Vector3 GetCellPosition(Rect cell);

	//std::vector<Vector3> GetAllRoomPositions();
	//std::vector<Vector3> GetMainRoomPositions();

	void DrawRooms();
	
};

