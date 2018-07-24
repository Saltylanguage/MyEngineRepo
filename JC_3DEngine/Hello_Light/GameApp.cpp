#include "GameApp.h"

//Hello Light
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

	mWorldBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();

	mModel.Load("..\\Data\\Models\\jeep.txt");
	mSpaceShipModel.Load("..\\Data\\Models\\spaceShip.txt");
	mSpaceShipModel2.Load("..\\Data\\Models\\spaceShip.txt");
	mSpaceShipModel3.Load("..\\Data\\Models\\spaceShip.txt");
	mSpaceShipModel4.Load("..\\Data\\Models\\spaceShip.txt");
	mSpaceShipModel5.Load("..\\Data\\Models\\spaceShip.txt");
	mSoldier.Load("..\\Data\\Models\\soldier.txt");

	mBrickModel.Load("..\\Data\\Models\\Brick.txt");

	Animation animation;
	KeyFrame keyframe;
	keyframe.SetPosition({ 0.f, 20.0f, 0.0f });
	keyframe.SetScale({ 1.0f, 1.0f, 1.0f });
	keyframe.SetRotation(Quaternion{});
	keyframe.SetTime(0.0f);
	animation.AddKeyFrame(keyframe);
	//mModel.SetAnimation(animation);
	mModel.Update(0.0f);

	MeshBuilder::buildSkyBox(mSkybox, 1000);
	skyBoxBuffer.Initialize(mSkybox.GetVertices(), mSkybox.GetVertexCount(), mSkybox.GetIndices(), mSkybox.GetIndexCount());

	mModel.SetPosition(Vector3(100, -4, -80));
	mModel.SetRotation(Vector3(0, 0, 1), 0);
	mModel.SetScale(Vector3(1, 1, 1));

	mSoldier.SetPosition(Vector3(160, 0, 100));
	mSoldier.SetRotation(Vector3(0, 0, 1), 0);
	mSoldier.SetScale(Vector3(0.1f, 0.1f, 0.1f));

	float degToRad = 3.14f / 180;
	//SpaceShip 1
	mBrickModel.SetPosition(Vector3(-130, 200, 0));
	//mBrickModel.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	//mBrickModel.SetScale(Vector3(1, 1, 1));

	mSpaceShipModel.SetPosition(Vector3(-130, 200, 0));
	mSpaceShipModel.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	mSpaceShipModel.SetScale(Vector3(1, 1, 1));

	//SpaceShip 2
	mSpaceShipModel2.SetPosition(Vector3(-100, 210, 30));
	mSpaceShipModel2.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	mSpaceShipModel2.SetScale(Vector3(1, 1, 1));

	//SpaceShip 3
	mSpaceShipModel3.SetPosition(Vector3(-100, 190, -30));
	mSpaceShipModel3.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	mSpaceShipModel3.SetScale(Vector3(1, 1, 1));

	//SpaceShip 4
	mSpaceShipModel4.SetPosition(Vector3(-70, 220, 60));
	mSpaceShipModel4.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	mSpaceShipModel4.SetScale(Vector3(1, 1, 1));

	//SpaceShip 5
	mSpaceShipModel5.SetPosition(Vector3(-70, 180, -60));
	mSpaceShipModel5.SetRotation(Vector3(1, 0, 0), -110 * degToRad);
	mSpaceShipModel5.SetScale(Vector3(1, 1, 1));

	mSkyBoxTexture.Initialize(L"../Textures/skybox2.jpg");

	uint32_t terrainWidth = 512;
	uint32_t terrainLength = 512;
	mTerrain.Initialize("../Textures/Terrain/2x2-island.raw", terrainWidth, terrainLength, 256.0f);

	//first value:1st texture  second value: layer third value: minLimit  fourth value: maxLimit last value: tileFrequency
	mTerrain.SetLayer(L"../Textures/Grass.jpg", 0, 0.0f, 15.0f, 15.0f);
	mTerrain.SetLayer(L"../Textures/Dirt.jpg", 1, 5.0f, 50.0f, 20.0f);
	mTerrain.SetLayer(L"../Textures/Rock.jpg", 2, 30.0f, 90.0f, 10.0f);
	mTerrain.SetLayer(L"../Textures/Snow.jpg", 3, 75.0f, 100.0f, 25.0f);

	mVShader.Initialize(L"../Data/Shaders/PixelLighting.fx");
	mPShader.Initialize(L"../Data/Shaders/PixelLighting.fx");

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameApp::OnTerminate()
{

	mBrickModel.Unload();

	mModel.Unload();

	mSpaceShipModel.Unload();
	mSpaceShipModel2.Unload();
	mSpaceShipModel3.Unload();
	mSpaceShipModel4.Unload();
	mSpaceShipModel5.Unload();

	mSoldier.Unload();

	mVShader.Terminate();
	mPShader.Terminate();

	mTexture.Terminate();
	mSampler.Terminate();

	mMeshBuffer.Terminate();
	mMesh.Terminate();
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
	//Matrix4X4 world = Matrix4X4::RotateY(kTotalTime) * Matrix4X4::RotateX(kTotalTime);		
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
	mPShader.Bind();

	mSkyBoxTexture.BindPS(0);
	mSampler.BindPS(0);

	//bind the input layout, vertex shader, and pixel shader

	skyBoxBuffer.Draw();
	mModel.Draw(mCamera);

	mSpaceShipModel.Draw(mCamera);

	mSpaceShipModel.SetPosition(Vector3(100, 100, 100));
	mSpaceShipModel.Draw(mCamera);
	mSpaceShipModel.SetPosition(Vector3(150, 150, 150));
	mSpaceShipModel.Draw(mCamera);
	mSpaceShipModel.SetPosition(Vector3(200, 200, 200));
	mSpaceShipModel.Draw(mCamera);
	mSpaceShipModel.SetPosition(Vector3(250, 250, 250));
	mSpaceShipModel.Draw(mCamera);
	mSpaceShipModel.SetPosition(Vector3(300, 300, 300));
	mSpaceShipModel.Draw(mCamera);

	//mSpaceShipModel2.Draw(mCamera);
	//mSpaceShipModel3.Draw(mCamera);
	//mSpaceShipModel4.Draw(mCamera);
	//mSpaceShipModel5.Draw(mCamera);

	mSoldier.Draw(mCamera);

	mBrickModel.Draw(mCamera);

	mTerrain.Render(mCamera);

	Graphics::GraphicsSystem::Get()->GetContext()->PSSetShader(mPShader.Shader, nullptr, 0); //TODO put inside pixel shader

	//mMeshBuffer.Draw();

	Graphics::GraphicsSystem::Get()->EndRender();
}
