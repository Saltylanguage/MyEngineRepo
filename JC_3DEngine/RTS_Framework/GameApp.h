#pragma once
#include "World.h"
#include <Core\Inc\Core.h>
#include <Graphics\Inc\Graphics.h>

#define MAX_BUFFER_SIZE 16384




class GameApp : public Core::Application
{

private:
	virtual void OnInitialize(uint32_t width, uint32_t height) override;
	virtual void OnTerminate() override;
	virtual void OnUpdate() override;

	void GuiInit();
	void GuiUpdate();


public:
	GameApp();

	virtual ~GameApp();

	void Thread_Accept();
	//Window
	Core::Window mWindow;
	Core::Timer mTimer;

	Input::InputSystem* inputSystem;

	uint16_t port = 8888;
	Network::TCPSocket* ServerSocket;
	Network::TCPSocket* ClientSocket;

	Network::SocketAddress serverInfo;
	
	Network::SocketAddress clientAddress;

	bool master = true;
	bool threadStartUp = true;
	


};