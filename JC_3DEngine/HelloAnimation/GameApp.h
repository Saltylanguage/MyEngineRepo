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
		Matrix wvp;
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
		Matrix world;
		Matrix wvp;
		Vector3 cameraPosition;	
	};
	struct LightInfo
	{		
		Vector4 lightDiffuse;
		Vector4 lightAmbient;
		Vector4 lightSpecular;

		Vector3 lightDirection;
	};	
	struct MaterialInfo
	{
		Vector4 materialAmbient;
		Vector4 materialDiffuse;
		Vector4 materialSpecular;
	};

	//Camera
	Graphics::Camera mCamera;
	
	//Model
	Graphics::Model mModel;
	Graphics::AnimationController mAnimController;

	//Meshes
	
	Graphics::Mesh mSkyboxMesh;
	
	
	/*Graphics::Mesh mMesh;*/

	//Mesh Buffers
	Graphics::MeshBuffer mSkyboxMeshBuffer;
	
	//Constant Buffers
	Graphics::TypedConstantBuffer<WorldInfo> mWorldBuffer;
	Graphics::TypedConstantBuffer<LightInfo> mLightBuffer;
	Graphics::TypedConstantBuffer<MaterialInfo> mMaterialBuffer;
	Graphics::TypedConstantBuffer<ConstantDataSkybox> mConstantSkyboxBuffer;

	//Shaders
	Graphics::PixelShader mPShader;
	Graphics::VertexShader mVShader;
	Graphics::PixelShader mSkyboxPixelShader;
	Graphics::VertexShader mSkyboxVertexShader;

	//Texture
		
	//Sampler
	Graphics::Sampler mSampler;

	Graphics::DepthStencilState mDepthStencilState;

};

#endif //ifndef INCLUDED_GAMEAPP_H




//set up an array of objects
// first pass paint render id's set to a different shaders
//different colors for different objects

// second pass is for visualization of the scene