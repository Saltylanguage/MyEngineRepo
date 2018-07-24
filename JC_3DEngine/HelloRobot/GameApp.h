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

	struct Model
	{
		std::vector<Graphics::Mesh*> Meshes;
		std::vector<std::string> Textures;
		std::vector<Graphics::MeshBuffer*> MeshBuffers;
	};
	
	struct ConstantDataSkybox
	{
		MathLibrary::Matrix4X4 wvp;
	};

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
		MathLibrary::Matrix4X4 world;
		MathLibrary::Matrix4X4 wvp;

		MathLibrary::Vector3 cameraPosition;	
	};
	struct LightInfo
	{		
		MathLibrary::Vector4 lightAmbient;
		MathLibrary::Vector4 lightDiffuse;
		MathLibrary::Vector4 lightSpecular;

		MathLibrary::Vector3 lightDirection;
	};	
	struct MaterialInfo
	{
		MathLibrary::Vector4 materialAmbient;
		MathLibrary::Vector4 materialDiffuse;
		MathLibrary::Vector4 materialSpecular;
	};

	//Camera
	Graphics::Camera mCamera;
	
	//Meshes
	
	Graphics::Mesh mSkyboxMesh;
	Graphics::Terrain mTerrain;
	Graphics::Mesh mSphereMesh;
	/*Graphics::Mesh mMesh;*/

	//Mesh Buffers
	/*Graphics::MeshBuffer mMeshBuffer;	*/

	Graphics::MeshBuffer mSkyboxMeshBuffer;
	Graphics::MeshBuffer mSphereMeshBuffer;

	//Constant Buffers
	Graphics::TypedConstantBuffer<WorldInfo> mWorldBuffer;
	Graphics::TypedConstantBuffer<LightInfo> mLightBuffer;
	Graphics::TypedConstantBuffer<MaterialInfo> mMaterialBuffer;
	Graphics::TypedConstantBuffer<ConstantDataSkybox> mConstantSkyboxBuffer;

	Graphics::TypedConstantBuffer<WorldInfo> mReflectionBuffer;

	

	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;
	Graphics::PixelShader mSkyboxPixelShader;
	Graphics::VertexShader mSkyboxVertexShader;

	//Texture
	Graphics::Texture mTexture;
	Graphics::Texture mCubeMap;
	Graphics::Texture* mTextures;

	Graphics::Texture mEarthTexture;
	Graphics::Texture mSpecularMap;
	Graphics::Texture mNormalMap;
	Graphics::Texture mDisplacementMap;

	//Sampler
	Graphics::Sampler mSampler;

	Graphics::DepthStencilState mDepthStencilState;

};

#endif //ifndef INCLUDED_GAMEAPP_H




//set up an array of objects
// first pass paint render id's set to a different shaders
//different colors for different objects

// second pass is for visualization of the scene