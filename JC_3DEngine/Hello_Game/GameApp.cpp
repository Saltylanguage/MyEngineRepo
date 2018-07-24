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

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	mCamera.SetPosition(Vector3(0.0f, 0.0f, -2.0f));

	mConstantBuffer.Initialize();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	MeshBuilder::buildCube(mMesh);

	mTexture.Initialize(L"../Textures/RedBrick_Texture.bmp");
	mVShader.Initialize(L"../Data/Shaders/Texturing.fx");
	mPShader.Initialize(L"../Data/Shaders/Texturing.fx");

	//MeshBuilder::buildPlane(mMesh);

	mMeshBuffer.Initialize(mMesh.GetVertices(), mMesh.GetVertexCount(), mMesh.GetIndices(), mMesh.GetIndexCount());

	//mVShader.Initialize(L"../Data/Shaders/DoSomething.fx");
	//mPShader.Initialize(L"../Data/Shaders/DoSomething.fx");


}

void GameApp::OnTerminate()
{
	mVShader.Terminate();
	mPShader.Terminate();

	mTexture.Terminate();
	mSampler.Terminate();

	mMeshBuffer.Terminate();
	mMesh.Terminate();

	mConstantBuffer.Terminate();

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

	mCamera.Yaw(InputSystem->GetMouseMoveX() * kTurnSpeed * kDeltaTime);
	mCamera.Pitch(InputSystem->GetMouseMoveY() * kTurnSpeed *kDeltaTime);
	static float dt = 0.0f;

	//==================ROTATION==================
	//dt += 0.0005f;
	//==================ROTATION==================

	CB cb;
	cb.world = Matrix::Transpose(Matrix().RotateY(dt));
	cb.view = Matrix::Transpose(mCamera.GetViewMatrix());
	cb.projection = Matrix::Transpose(mCamera.GetProjectionMatrix());

	Graphics::GraphicsSystem::Get()->BeginRender();

	//Rendering Code Goes Here

	//set constant buffer and bind vertex shader
	mConstantBuffer.Set(cb);
	mConstantBuffer.BindVS();

	mVShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);

	//bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	context->PSSetShader(mPShader.Shader, nullptr, 0);

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &mMeshBuffer.mVertexBuffer, &stride, &offset);

	//set index buffer
	context->IASetIndexBuffer(mMeshBuffer.mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw mesh
	context->DrawIndexed(mMesh.GetIndexCount(), 0, 0);

	Graphics::GraphicsSystem::Get()->EndRender();
}
