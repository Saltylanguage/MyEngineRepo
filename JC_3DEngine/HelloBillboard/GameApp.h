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

	struct WorldInfo
	{
		Matrix world;
		Matrix wvp;

		Vector3 cameraPosition;
	};

	struct LightInfo
	{

		Vector4 lightAmbient;
		Vector4 lightDiffuse;
		Vector4 lightSpecular;

		Vector3 lightDirection;
	};


	//Camera
	struct MaterialInfo
	{
		Vector4 materialAmbient;
		Vector4 materialDiffuse;
		Vector4 materialSpecular;
	};

	Graphics::Camera mCamera;
	Graphics::TypedConstantBuffer<WorldInfo> mWorldBuffer;
	Graphics::TypedConstantBuffer<LightInfo> mLightBuffer;
	Graphics::TypedConstantBuffer<MaterialInfo> mMaterialBuffer;


	//Meshes
	Graphics::Mesh cubeMesh;
	Graphics::MeshBuffer cubeMeshBuffer;

	Graphics::Mesh mMesh;
	Graphics::MeshBuffer mMeshBuffer;

	Graphics::Mesh mPlaneMesh;
	Graphics::MeshBuffer mPlaneMeshBuffer;


	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;
	Graphics::GeometryShader mGShader;

	//Texture
	Graphics::Texture mTexture;
	Graphics::Sampler mSampler;

	Graphics::Terrain mTerrain;


	Graphics::Texture* mTextures;

	Graphics::Texture mSkyBoxTexture;
	Graphics::MeshBuffer skyBoxBuffer;
	Graphics::Mesh mSkybox;

	

	ID3D11Buffer* mPointVertexBuffer;


};

#endif //ifndef INCLUDED_GAMEAPP_H