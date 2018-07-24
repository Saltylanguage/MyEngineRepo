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
	Graphics::SimpleDraw::Initialize();

	mCamera.SetPosition(Vector3(675.0f, 290.0f, 240.0f));
	mCamera.SetDirection(Vector3(1.0f, -0.9f, 1.0f));
	mConstantBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	MeshBuilder::buildCube(mMesh);

	mMainRoomTexture.Initialize(L"../Textures/RedBrick_Texture.bmp");
	mRegularRoomTexture.Initialize(L"../Textures/Grass.jpg");
	mVShader.Initialize(L"../Data/Shaders/Texturing.fx");
	mPShader.Initialize(L"../Data/Shaders/Texturing.fx");

	//MeshBuilder::buildPlane(mMesh);

	mMeshBuffer.Initialize(mMesh.GetVertices(), mMesh.GetVertexCount(), mMesh.GetIndices(), mMesh.GetIndexCount());

	mRotation = Math::Matrix::Identity();
	mScale = Vector3(1, 1, 1);

	//mVShader.Initialize(L"../Data/Shaders/DoSomething.fx");
	//mPShader.Initialize(L"../Data/Shaders/DoSomething.fx");

}

void GameApp::OnTerminate()
{
	mVShader.Terminate();
	mPShader.Terminate();

	mRegularRoomTexture.Terminate();
	mMainRoomTexture.Terminate();
	mSampler.Terminate();

	mMeshBuffer.Terminate();
	mMesh.Terminate();

	mConstantBuffer.Terminate();

	Graphics::SimpleDraw::Terminate();
	Input::InputSystem::StaticTerminate();
	Graphics::GraphicsSystem::StaticTerminate();

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
	static float dt = 0.0f;

	//==================ROTATION==================
	//dt += 0.0005f;
	//==================ROTATION==================

	CB cb;
	cb.world = Matrix::Transpose(Matrix().RotateY(dt));
	cb.view = Matrix::Transpose(mCamera.GetViewMatrix());
	cb.projection = Matrix::Transpose(mCamera.GetProjectionMatrix());

	if (InputSystem->IsKeyPressed(Keys::SPACE))
	{
		RandomizeCells();
		SetAllRoomPositions();
		SetMainRoomPositions();
	}
	//ResolveOverlaps();
	if (InputSystem->IsKeyPressed(Keys::BACKSPACE))
	{
		ClearCells();
	}

	//ResolveOverlaps();

	//for (auto& cell : cells)
	//{
	//	SimpleDraw::AddScreenRect(cell, Math::Vector4::Cyan());
	//}

	Graphics::GraphicsSystem::Get()->BeginRender();

	//Rendering Code Goes Here
	SetMesh(mMeshBuffer);
	SetTexture(mMainRoomTexture, mSampler);
	mIndexCount = mMeshBuffer.mIndexCount;

	//for (int i = 0; i < cells.size(); i++)
	//{
	//	float x = i * 5;
	//	mScale = Vector3(1, 10, 1);
	//	DrawMeshAtLocation(Vector3(x, 0, x));
	//}

	DrawRooms();

	//set constant buffer and bind vertex shader
//	mConstantBuffer.Set(cb);
//	mConstantBuffer.BindVS();
//
//	mVShader.Bind();
//	mTexture.BindPS(0);
//	mSampler.BindPS(0);
//
//	//bind the input layout, vertex shader, and pixel shader
//	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();
//
//	context->PSSetShader(mPShader.Shader, nullptr, 0);
//
//	//set vertex buffer
//	UINT stride = sizeof(Vertex);
//	UINT offset = 0;
//
//	context->IASetVertexBuffers(0, 1, &mMeshBuffer.mVertexBuffer, &stride, &offset);
//
//	//set index buffer
//	context->IASetIndexBuffer(mMeshBuffer.mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//
//	//set primitieve topology
//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	//draw mesh
//	context->DrawIndexed(mMesh.GetIndexCount(), 0, 0);
//
	SimpleDraw::Render(*Graphics::Camera::main);
	Graphics::GraphicsSystem::Get()->EndRender();




}

void GameApp::RandomizeCells()
{
	float w = Graphics::GraphicsSystem::Get()->GetWidth() * 0.5f;
	float h = Graphics::GraphicsSystem::Get()->GetHeight() * 0.5f;
	float size = 30.0f;

	for (int i = 0; i < 50; ++i)
	{
		float minX = RandomFloat(-size + w, 0.0f + w);
		float maxX = RandomFloat(0.0f + w, size + w);
		float minY = RandomFloat(-size + h, 0.0f + h);
		float maxY = RandomFloat(0.0f + h, size + h);
		cells.emplace_back(minX, minY, maxX, maxY);
	}
}


void GameApp::ClearCells()
{
	cells.clear();
}

void GameApp::ResolveSpecificOverlap(const int xIndex, const int yIndex)
{
	auto& a = cells[xIndex];
	auto& b = cells[yIndex];
	if (Math::Intersect(a, b))
	{
		if (a.right > b.left)
		{

		}
	}
}

void GameApp::ResolveAllOverlaps()
{
	bool overlap = false;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		for (size_t j = 0; j < cells.size(); ++j)
		{
			if (i == j)
				continue;

			auto& a = cells[i];
			auto& b = cells[j];

			if (Math::Intersect(a, b))
			{
				if (a.right > b.left)
				{
					if (a.left < b.left)
					{
						float diff = a.right - b.left;
						a.left -= diff * 0.5f - 1.0f;
						a.right -= diff * 0.5f - 1.0f;
						b.left += diff * 0.5f;
						b.right += diff * 0.5f;
					}
					else
					{
						float diff = b.right - a.left;
						a.left += diff * 0.5f + 1.0f;
						a.right += diff * 0.5f + 1.0f;
						b.left -= diff * 0.5f;
						b.right -= diff * 0.5f;
					}
				}
			}
			if (Math::Intersect(a, b))
			{
				if (a.bottom > b.top)
				{
					if (a.top < b.top)
					{
						float diff = a.bottom - b.top;
						a.top -= diff * 0.5f - 1.0f;
						a.bottom -= diff * 0.5f - 1.0f;
						b.top += diff * 0.5f;
						b.bottom += diff * 0.5f;
					}
					else
					{
						float diff = b.bottom - a.top;
						a.top += diff * 0.5f + 1.0f;
						a.bottom += diff * 0.5f + 1.0f;
						b.top -= diff * 0.5f;
						b.bottom -= diff * 0.5f;
					}
				}
			}
		}
	}
}

float GameApp::FindRoomSize(Rect cell)
{
	float x = abs(cell.right - cell.left);
	float y = abs(cell.bottom - cell.top);

	return x*y;
}

void GameApp::SetAllRoomPositions()
{
	allRooms.clear();
	for (size_t i = 0; i < cells.size(); i++)
	{
		Room newRoom;
		newRoom.center = GetCellPosition(cells[i]);
		newRoom.bounds.bottom = cells[i].bottom;
		newRoom.bounds.top = cells[i].top;
		newRoom.bounds.left = cells[i].left;
		newRoom.bounds.right = cells[i].right;

		//		position.x = (((cells[i].right + cells[i].left) / 2.0f) - 1);
		//		position.y = 0;
		//		position.z = ((cells[i].top + cells[i].bottom) / 2.0f);
		allRooms.push_back(newRoom);
	}
}

void GameApp::SetMainRoomPositions()
{
	std::vector<Vector3> ret;
	for (size_t i = 0; i < allRooms.size(); i++)
	{
		Room newRoom;
		newRoom.center = GetCellPosition(cells[i]);
		newRoom.bounds.bottom = cells[i].bottom;
		newRoom.bounds.top = cells[i].top;
		newRoom.bounds.left = cells[i].left;
		newRoom.bounds.right = cells[i].right;

		if (FindRoomSize(allRooms[i].bounds) >= mainRoomThreshold && allRooms.size() < maxNumRooms)
		{
			mainRooms.push_back(newRoom);
		}
		else
		{
			RegularRooms.push_back(newRoom);
		}
	}
}

Vector3 GameApp::GetCellPosition(Rect cell)
{
	Vector3 position;

	position.x = (((cell.right + cell.left) / 2.0f) - 1);
	position.y = 0;
	position.z = ((cell.top + cell.bottom) / 2.0f);

	return position;
}




void GameApp::DrawMesh(Vector3 position, Math::Matrix rotation, Vector3 scale, int indexCount)
{
	CB cb;
	cb.world = Matrix::Transpose(Matrix::MakeScaleMatrix(scale) * rotation * Matrix::Translation(position));
	cb.view = Matrix::Transpose(Graphics::Camera::main->GetViewMatrix());
	cb.projection = Matrix::Transpose(Graphics::Camera::main->GetProjectionMatrix());

	mConstantBuffer.Set(cb);
	mConstantBuffer.BindVS();
	mVShader.Bind();
	mPShader.Bind();
	GraphicsSystem::Get()->GetContext()->DrawIndexed(indexCount, 0, 0);
}

void GameApp::DrawMeshAtLocation(Vector3 position)
{
	DrawMesh(position, mRotation, mScale, mIndexCount);
}

void GameApp::SetTexture(Graphics::Texture & texture, Graphics::Sampler & sampler)
{
	texture.BindPS(0);
	sampler.BindPS(0);
}

void GameApp::SetMesh(Graphics::MeshBuffer & meshbuffer)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	auto context = GraphicsSystem::Get()->GetContext();
	context->IASetVertexBuffers(0, 1, &mMeshBuffer.mVertexBuffer, &stride, &offset);

	//set index buffer
	context->IASetIndexBuffer(mMeshBuffer.mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


void GameApp::DrawRooms()
{
	float w = Graphics::GraphicsSystem::Get()->GetWidth() * 0.5f;
	float h = Graphics::GraphicsSystem::Get()->GetHeight() * 0.5f;


	for (size_t i = 0; i < cells.size(); i++)
	{
		Vector3 position;
		position.x = (((cells[i].right + cells[i].left) / 2.0f) - 1);
		position.y = 0;
		position.z = ((cells[i].top + cells[i].bottom) / 2.0f);

		mScale.x = abs(cells[i].right - position.x);
		mScale.y = 1.0f;
		mScale.z = abs(cells[i].bottom - position.z);

		DrawMesh(position, mRotation, mScale, mIndexCount);
	}
}
