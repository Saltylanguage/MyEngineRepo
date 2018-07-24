#include "GameApp.h"

//hello triangle
using namespace Graphics;

	Graphics::Vertex myVertices[] =
	{
		Vertex(Vector3( 0.0f, 0.5f, 0.0f), Vector3(0.0f,0.0f,-1.0f), Vector4( 1.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
		Vertex(Vector3( 0.5f,-0.5f, 0.0f), Vector3(0.0f,0.0f,-1.0f), Vector4( 0.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
		Vertex(Vector3(-0.5f,-0.5f, 0.0f), Vector3(0.0f,0.0f,-1.0f), Vector4( 0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f ))
	};
	
const int kVertexCount = sizeof(myVertices) / sizeof(myVertices[0]);

GameApp::GameApp() : mVertexBuffer(nullptr), mIndexBuffer(nullptr) 
{

}

GameApp::~GameApp()
{

}

void GameApp::OnInitialize(uint32_t width, uint32_t height)
{

	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);

	//create and build vertex buffer

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * kVertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = myVertices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mVertexBuffer);
  
	mVShader.Initialize(L"../Data/Shaders/DoNothing.fx");
	mPShader.Initialize(L"../Data/Shaders/DoNothing.fx");
}

void GameApp::OnTerminate()
{
	SafeRelease(mPShader.Shader);
	SafeRelease(mVertexBuffer);
	SafeRelease(mVShader.Shader);
	SafeRelease(mIndexBuffer);
	SafeRelease(mVertexBuffer);
	
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

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}

	Graphics::GraphicsSystem::Get()->BeginRender();

	//Rendering Code Goes Here

	//bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	//context->IASetInputLayout(mVShader.mInputLayout);
	//context->VSSetShader(mVShader.Shader, nullptr, 0);
	
	mVShader.Bind();
	mPShader.Bind();
	
	//context->PSSetShader(mPShader.Shader, nullptr, 0);

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw mesh
	context->Draw(kVertexCount, 0);

	Graphics::GraphicsSystem::Get()->EndRender();
}
