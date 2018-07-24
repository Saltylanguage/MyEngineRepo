#include "GameApp.h"

//Hello Light
using namespace Graphics;

namespace
{

	const float kTreeScaleX = 1.0f;
	const float kTreeScaleY = 1.0f;
	const int kTreeCount = 20;

	float RandomFloat()
	{
		return float(rand()) / (float)RAND_MAX;
	}

	float RandomFloat(float min, float max)
	{
		return min + (RandomFloat() * (max - min));
	}
}



GameApp::GameApp() : mPointVertexBuffer(nullptr)
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

	mWorldBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	MeshBuilder::buildSkyBox(mSkybox, 1000);
	skyBoxBuffer.Initialize(mSkybox.GetVertices(), mSkybox.GetVertexCount(), mSkybox.GetIndices(), mSkybox.GetIndexCount());

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Graphics::Vertex) * kTreeCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	Graphics::Vertex vertex[kTreeCount];
	for (int i = 0; i < kTreeCount; i++)
	{
		float x = rand() / (float)RAND_MAX;
		float z = rand() / (float)RAND_MAX;

		vertex[i].POS.x = x;
		vertex[i].POS.y = kTreeScaleY;
		vertex[i].POS.z = z;
	}

	D3D11_SUBRESOURCE_DATA initData;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &vertex;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mPointVertexBuffer);


	float degToRad = 3.14f / 180;

	mSkyBoxTexture.Initialize(L"../Textures/skybox2.jpg");

	uint32_t terrainWidth = 512;
	uint32_t terrainLength = 512;
	mTerrain.Initialize("../Textures/Terrain/FlatTerrainBlack.raw", terrainWidth, terrainLength, 256.0f);

	mTerrain.SetLayer(L"../Textures/Snow.jpg", 0, 0.0f, 15.0f, 15.0f); //first value:1st texture  second value: layer third value: minLimit  fourth value: maxLimit last value: tileFrequency
	mTerrain.SetLayer(L"../Textures/Dirt.jpg", 1, 5.0f, 50.0f, 20.0f);
	mTerrain.SetLayer(L"../Textures/Rock.jpg", 2, 30.0f, 90.0f, 10.0f);
	mTerrain.SetLayer(L"../Textures/Snow.jpg", 3, 75.0f, 100.0f, 25.0f);

	mVShader.Initialize(L"../Data/Shaders/PixelLighting.fx");
	mPShader.Initialize(L"../Data/Shaders/PixelLighting.fx");
	mGShader.Initialize(L"../Data/Shaders/Billboard.fx");

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameApp::OnTerminate()
{

	SafeRelease(mPointVertexBuffer);

	mVShader.Terminate();
	mGShader.Terminate();
	mPShader.Terminate();

	mTexture.Terminate();
	mSampler.Terminate();

	mTerrain.Terminate();

	mWorldBuffer.Terminate();
	mLightBuffer.Terminate();
	mMaterialBuffer.Terminate();

	mSkybox.Terminate();
	mSkyBoxTexture.Terminate();
	skyBoxBuffer.Terminate();

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
	const float kMoveSpeed = 100.0f;
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

	//==================ROTATION==================
	Matrix world = Matrix::RotateY(0);
	//MathLibrary::Matrix4X4 world = MathLibrary::Matrix4X4::RotateY(kTotalTime) * MathLibrary::Matrix4X4::RotateX(kTotalTime);		
	//==================ROTATION==================

	Matrix view = mCamera.GetViewMatrix();
	Matrix projection = mCamera.GetProjectionMatrix();

	Matrix WVP = world * view * projection;

	WorldInfo wInfo;
	LightInfo lInfo;
	MaterialInfo mInfo;

	wInfo.world = Matrix::Transpose(world);
	wInfo.wvp = Matrix::Transpose(WVP);
	wInfo.cameraPosition = mCamera.GetPosition();


	lInfo.lightDirection = Vector3(1.0f, -1.0f, 1.0f);
	lInfo.lightAmbient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	lInfo.lightDiffuse = Vector4::White();
	lInfo.lightSpecular = Vector4::White();

	mInfo.materialAmbient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	mInfo.materialDiffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	mInfo.materialSpecular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//END OF TEMP VALUES

	Graphics::GraphicsSystem::Get()->BeginRender();

	//Rendering Code Goes Here

	//set constant buffer and bind vertex shader
	mWorldBuffer.Set(wInfo);
	mLightBuffer.Set(lInfo);
	mMaterialBuffer.Set(mInfo);

	mWorldBuffer.BindVS(0);
	mLightBuffer.BindVS(1);
	mMaterialBuffer.BindVS(2);

	mWorldBuffer.BindPS(0);
	mLightBuffer.BindPS(1);
	mMaterialBuffer.BindPS(2);

	mVShader.Bind();
	//mGShader.Bind();
	mPShader.Bind();



	mSkyBoxTexture.BindPS(0);
	mSampler.BindPS(0);


	//bind the input layout, vertex shader, and pixel shader

	skyBoxBuffer.Draw();
	mTerrain.Render(mCamera);


	//Set Vertex Buffer
	UINT stride = sizeof(Graphics::Vertex);
	UINT offset = 0;
	Graphics::GraphicsSystem::Get()->GetContext()->IASetVertexBuffers(0, 1, &mPointVertexBuffer, &stride, &offset);
	Graphics::GraphicsSystem::Get()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	Graphics::GraphicsSystem::Get()->GetContext()->Draw(kTreeCount, 0);

	Graphics::GraphicsSystem::Get()->GetContext()->PSSetShader(mPShader.Shader, nullptr, 0); //TODO put inside pixel shader																						

	Graphics::GraphicsSystem::Get()->EndRender();
}
