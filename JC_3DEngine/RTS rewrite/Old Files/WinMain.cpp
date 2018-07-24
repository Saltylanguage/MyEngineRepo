
#include "GameApp.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameApp myApp;
	myApp.Initialize(hInstance, "RTS", 1280, 720);

	while (myApp.IsRunning())
	{
		myApp.Update();
	}

	myApp.Terminate();
	return 0;

	return 0;
}







//
//bool GameLoop(float deltaTime)
//{
//	RTS::UpdateCamera(deltaTime,  myApp.mCamera);
//	World::Get()->Update(deltaTime);
//
//	RTS::DrawGround();
//	World::Get()->Draw();
//	RTS::DrawCursor();
//
//	if ( inputSystem->IsKeyPressed(Keys::SPACE))
//	{
//		World::Get()->SpawnUnitRandom();
//	}
//	if (inputSystem->IsKeyPressed(Keys::LCONTROL))
//	{
//		Network::MemoryStream memoryStream;
//		Network::StreamWriter writer(memoryStream);
//		World::Get()->WriteSnapshot(writer);
//
//		FILE* file = nullptr;
//		fopen_s(&file, "save.dat", "wb");
//		fwrite(memoryStream.GetData(), memoryStream.GetSize(), 1, file);
//		fclose(file);
//	}
//	if (inputSystem->IsKeyPressed(Keys::RCONTROL))
//	{
//		FILE* file = nullptr;
//		fopen_s(&file, "save.dat", "rb");
//
//		fseek(file, 0L, SEEK_END);
//		int fileSize = ftell(file);
//		fseek(file, 0L, SEEK_SET);
//
//		char* fileBuffer = (char*)malloc(fileSize * sizeof(char));
//		fread(fileBuffer, fileSize, 1, file);
//		fclose(file);
//
//		Network::MemoryStream memoryStream((uint8_t*)fileBuffer, fileSize, true);
//		Network::StreamReader reader(memoryStream);
//		World::Get()->ApplySnapshot(reader);
//	}
//
//	return inputSystem->IsKeyPressed(Keys::ESCAPE);
//}