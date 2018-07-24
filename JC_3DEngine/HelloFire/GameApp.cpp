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
//4)Bind Texture
//5)Bind pShader
//6)Bind vShader
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

	fireMeshBuffer.Initialize();

	float degToRad = 3.14f / 180;

	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);

	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	mCamera.SetPosition(Vector3(0.0f, 0.0f, -2.0f));

	mWorldBuffer.Initialize();


	//Building Rendered Objects

	//Mesh Buffers

	//Initialize Constant Buffers

	//Initialize Textures

	mFireDiffuse.Initialize(L"../Textures/FireColorTexture.jpg");
	mFireNoise.Initialize(L"../Textures/FireNoiseTexture.png");;
	mFireAlpha.Initialize(L"../Textures/FireColorTexture.jpg");

	//Initialize Shaders
	mVShader.InitializePositionUV(L"../Data/Shaders/FireShader.fx");
	mPShader.Initialize(L"../Data/Shaders/FireShader.fx");

	//Initialize Sampler
	mClampSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Clamp);
	mWrapSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mBlendState.Initialize(Graphics::BlendState::Mode::AlphaBlend);

}

void GameApp::OnTerminate()
{
	mClampSampler.Terminate();
	mWrapSampler.Terminate();

	mVShader.Terminate();
	mPShader.Terminate();

	mFireAlpha.Terminate();
	mFireNoise.Terminate();
	mFireDiffuse.Terminate();

	mWorldBuffer.Terminate();


	fireMeshBuffer.Terminate();

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
	Matrix world = Matrix::RotateY(kTotalTime * 0.0f);
	//==================ROTATION==================

	//Matrix Math
	Matrix view = mCamera.GetViewMatrix();
	Matrix projection = mCamera.GetProjectionMatrix();
	Matrix WVP = world * view * projection;

	//Create Constant Buffers
	WorldInfo wInfo;

	//WorldInfo reflectionInfo;

	//Set World Constant Buffer
	wInfo.world = Matrix::Transpose(world);
	wInfo.wvp = Matrix::Transpose(WVP);
	wInfo.cameraPosition = mCamera.GetPosition();

	// ==================== RENDERING CODE GOES HERE ===============================

	//send our C++ constant buffers to DirectX's containers
	mWorldBuffer.Set(wInfo);

	//Bind Main Shaders
	mVShader.Bind();
	mPShader.Bind();

	mFireDiffuse.BindPS(0);
	mFireNoise.BindPS(1);
	mFireAlpha.BindPS(2);

	//Update constant buffer

	//Bind cube map and sampler
	
	mWrapSampler.BindPS(0);
	mClampSampler.BindPS(0);

	//Bind vertex and pixel shaders

	//Render the mesh buffer

	//bind the input layout, vertex shader, and pixel shader

	//Bind Specific Pixel Shaders
	mWorldBuffer.BindPS(0);
	mWorldBuffer.BindVS(0);

	mPShader.Bind();
	mVShader.Bind();

	fireMeshBuffer.Render();

	Graphics::GraphicsSystem::Get()->BeginRender();

	// =========================== RENDERING CODE ENDS HERE ===========================
	Graphics::GraphicsSystem::Get()->EndRender();

}
