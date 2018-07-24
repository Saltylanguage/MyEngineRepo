#include "GameApp.h"
#include "Graphics\Inc\Graphics.h"

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

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
}

void GameApp::OnTerminate()
{
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

	//Draw Stuff Here

	Graphics::GraphicsSystem::Get()->EndRender();
}
