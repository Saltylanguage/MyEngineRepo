#include "GameApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdline, int nCmdShow)
{

	GameApp myApp;
	myApp.Initialize(hInstance, "Hello Engine", 1024, 768);

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();
	return 0;
}
	