#include "GameApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int port = 8888;
	bool isServer = true;

	if (__argc >= 2)
	{
		isServer = false;
	}

	GameApp myApp;
	myApp.port = port;
	myApp.Initialize(hInstance, isServer ? "RTS_Server" : "RTS_Client", 1280, 720);

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();
	return 0;
	
}


//THINGS TO DO FOR FINAL

/*
	
	1) Turn world into a bytestream and send it across the network

	2) Minimize how much is being sent across network (using commands)
		
	3) 



	Send Commands across the stream and have it update the position of units on both sides









*/