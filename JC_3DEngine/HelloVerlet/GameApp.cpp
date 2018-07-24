#include "GameApp.h"

//hello cube
using namespace Graphics;

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize(uint32_t width, uint32_t height)
{
	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	mTimer.Initialize();

	Graphics::SimpleDraw::Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	
}

void GameApp::OnTerminate()
{

	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();

	UnhookWindow();
	mWindow.Terminate();
}

void GameApp::SpawnParticles()
{
	mWorld.ClearAll();

	for (int i = 0; i < 100; i++)
	{
		Physics::Particle* p = new Physics::Particle();
		p->SetPosition(MathLibrary::Vector3(0.0f, 1.0f, 0.0f));
		p->SetVelocity(MathLibrary::Vector3(i, i, 0.0f));
	}
}


void GameApp::OnUpdate()
{
	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

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
	
	const float kMoveSpeed = 10.0f;
	const float kTurnSpeed = 250.0f;

	static float dt = 0.0f;

	//==================ROTATION==================
	//dt += 0.0005f;
	//==================ROTATION==================
	
	mCamera.Yaw(InputSystem->GetMouseMoveX() * kTurnSpeed *kDeltaTime);
	mCamera.Pitch(InputSystem->GetMouseMoveY() * kTurnSpeed *kDeltaTime);
	
	Graphics::GraphicsSystem::Get()->BeginRender();
	//Rendering Code Goes Here
	SpawnParticles();
	mWorld.Update(kDeltaTime);
	
	Graphics::SimpleDraw::AddTransform(MathLibrary::Matrix4X4::Identity());
	Graphics::SimpleDraw::Render(mCamera);
	Graphics::GraphicsSystem::Get()->EndRender();

	//set constant buffer and bind vertex shader

	//bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//set index buffer

	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



	Graphics::GraphicsSystem::Get()->EndRender();
}
