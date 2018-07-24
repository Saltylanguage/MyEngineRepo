#include "GameApp.h"

//Hello Light
using namespace Graphics;


//Homework:
// Specular Map Lighting
// Update vertex  
	// update meshbuilder to take in binomral and tangent
//compute TBNW Matrix
// Sample Normal Map

//Render Checklist
//1) Init Mesh
//2) init meshbuffer
//3) Init texture
//4) Bind Texture
//5) Bind pShader
//6) Bind vShader
//7) Sampler
//8) Set Constant Buffer info
//9) Draw

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize(uint32_t width, uint32_t height)
{
	float degToRad = 3.14f / 180;

	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	
	Graphics::SimpleDraw::Initialize();

	mDepthStencilState.Initialize();

	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	mCamera.SetPosition(Vector3(0.0f, 0.0f, -2.0f));

	mWorldBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	//Building Rendered Objects

	MeshBuilder::buildIcoSphere(mEarth, 4);
	MeshBuilder::buildSkyBox(mSkyboxMesh, 1000);
	
	//Mesh Buffers

	mEarthBuffer.Initialize(mEarth.GetVertices(), mEarth.GetVertexCount(), mEarth.GetIndices(), mEarth.GetIndexCount());
	mSkyboxMeshBuffer.Initialize(mSkyboxMesh.GetVertices(), mSkyboxMesh.GetVertexCount(), mSkyboxMesh.GetIndices(), mSkyboxMesh.GetIndexCount());

	//Initialize Constant Buffers
	mConstantSkyboxBuffer.Initialize();

	
	//Initialize Textures
	mEarthTexture.Initialize(L"../Textures/earth.jpg");
	mCubeMap.Initialize(L"../Textures/space_cube.dds");	

	//Initialize Shaders
	//Changed
	mVShader.Initialize(L"../Data/Shaders/SpecularLighting.fx");
	mPShader.Initialize(L"../Data/Shaders/SpecularLighting.fx");

	mSkyboxPixelShader.Initialize(L"../Data/Shaders/CubeMapping.fx");
	mSkyboxVertexShader.Initialize(L"../Data/Shaders/CubeMapping.fx");

	//Initialize Sampler
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameApp::OnTerminate()
{
	mSampler.Terminate();

	mSkyboxVertexShader.Terminate();
	mSkyboxPixelShader.Terminate();

	mVShader.Terminate();
	mPShader.Terminate();

	mNormalMap.Terminate();
	mEarthTexture.Terminate();
	mSpecularMap.Terminate();
	mDisplacementMap.Terminate();

	mWorldBuffer.Terminate();
	mLightBuffer.Terminate();
	mMaterialBuffer.Terminate();

	mSkyboxMesh.Terminate();
	mCubeMap.Terminate();
	mSkyboxMeshBuffer.Terminate();
	mConstantSkyboxBuffer.Terminate();

	mDepthStencilState.Terminate();

	Graphics::SimpleDraw::Terminate();
	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();

	UnhookWindow();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}
	// Get systems
	Graphics::GraphicsSystem* GraphicsSystem = Graphics::GraphicsSystem::Get();
	Input::InputSystem* InputSystem = Input::InputSystem::Get();

	InputSystem->Update();

	if (InputSystem->IsKeyPressed(Keys::ESCAPE))
	{
		PostQuitMessage(0);
	}
	if (InputSystem->IsKeyPressed(Keys::F1))
	{
		GraphicsSystem->ToggleFullScreen();
	}

	mTimer.Update();
	const float kDeltaTime = mTimer.GetElapsedTime();
	const float kTotalTime = mTimer.GetTotalTime();
	const float kMoveSpeed = 1.0f;
	const float kTurnSpeed = 250.0f;


	//KEYBOARD MOVEMENT START
	if (InputSystem->IsKeyDown(Keys::W))
	{
		mCamera.Walk(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::A))
	{
		mCamera.Strafe(-kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::S))
	{
		mCamera.Walk(-kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::D))
	{
		mCamera.Strafe(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::E))
	{
		mCamera.Rise(kMoveSpeed * kDeltaTime);
	}
	if (InputSystem->IsKeyDown(Keys::Q))
	{
		mCamera.Rise(-kMoveSpeed * kDeltaTime);
	}
	// KEYBOARD MOVEMENT END

	//MOUSE MOVEMENT START
	mCamera.Yaw(InputSystem->GetMouseMoveX() * kTurnSpeed * kDeltaTime);
	mCamera.Pitch(InputSystem->GetMouseMoveY() * kTurnSpeed *kDeltaTime);
	//MOUSE MOVEMENT END

	//==================ROTATION==================
	Matrix world = Matrix::RotateY(kTotalTime * 0.5f);		
	//==================ROTATION==================

	//Matrix Math
	Matrix view = mCamera.GetViewMatrix();
	Matrix projection = mCamera.GetProjectionMatrix();
	Matrix WVP = world * view * projection;

	//Create Constant Buffers
	WorldInfo wInfo;
	LightInfo lInfo;
	MaterialInfo mInfo;
	//WorldInfo reflectionInfo;

	//Set World Constant Buffer
	wInfo.world = Matrix::Transpose(world);
	wInfo.wvp = Matrix::Transpose(WVP);
	wInfo.cameraPosition = mCamera.GetPosition();

	//Set Light Constant Buffer
	lInfo.lightDirection = Vector3(1.0f, -1.0f, 1.0f);
	lInfo.lightAmbient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	lInfo.lightDiffuse = Vector4::White();
	lInfo.lightSpecular = Vector4::White();

	//Set Material Constant Buffer
	mInfo.materialAmbient =  Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	mInfo.materialDiffuse =  Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	mInfo.materialSpecular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	
	Graphics::GraphicsSystem::Get()->BeginRender();
	// ==================== RENDERING CODE GOES HERE ===============================

	//send our C++ constant buffers to DirectX's containers
	mWorldBuffer.Set(wInfo);
	mLightBuffer.Set(lInfo);
	mMaterialBuffer.Set(mInfo);

	//Bind Main Shaders
	mVShader.Bind();
	mPShader.Bind();

	//Skybox transform is based on camera position ONLY (no rotation)	
	mDepthStencilState.EnableTesting(false); // Things draw over skybox regardless of depth value
	
	Matrix matWorldSkybox = Matrix::Translation(mCamera.GetPosition());

	//Update constant buffer
	ConstantDataSkybox dataSkybox;
	dataSkybox.wvp = Matrix::Transpose(matWorldSkybox * view * projection);
	mConstantSkyboxBuffer.Set(dataSkybox);
	mConstantSkyboxBuffer.BindVS(0);

	//Bind cube map and sampler
	mCubeMap.BindPS(0);
	mSampler.BindPS(0);

	//Bind vertex and pixel shaders
	mSkyboxVertexShader.Bind();	
	mSkyboxPixelShader.Bind();
	
	//Render the mesh buffer
	mSkyboxMeshBuffer.Draw();

	mDepthStencilState.EnableTesting(true);

	//bind the input layout, vertex shader, and pixel shader
	
	//Bind Specific Pixel Shaders
	mWorldBuffer.BindPS(0);
	mWorldBuffer.BindVS(0);

	mLightBuffer.BindPS(1);
	mLightBuffer.BindVS(1);
	mMaterialBuffer.BindPS(2);

	mPShader.Bind();
	mVShader.Bind();

	mEarthTexture.BindPS(0);
	mSpecularMap.BindPS(1);
	mNormalMap.BindPS(2);
	mDisplacementMap.BindVS(3);

	mEarthBuffer.Draw();

	float pi = 3.14159f;
	Matrix rotation = Matrix::RotateZ(- 45 * pi / 180);
	Matrix transform = rotation * Matrix::Translation(Vector3(0, 0, 0));
	Graphics::SimpleDraw::AddTransform(transform);

	Graphics::SimpleDraw::Render(mCamera);

	// =========================== RENDERING CODE ENDS HERE ===========================
	Graphics::GraphicsSystem::Get()->EndRender();
}
