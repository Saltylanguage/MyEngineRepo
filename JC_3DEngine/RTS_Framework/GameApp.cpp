#include "GameApp.h"
#include "RTS.h"
#include "World.h"
#include <thread>
#include <mutex>



bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_col = ImColor(114, 144, 154);
bool accepted = false;

Network::SocketAddress clientInfo;

void GameApp::Thread_Accept()
{
	//while (ClientSocket == nullptr)
	//{
	//	Network::SocketAddress clientInfo;
	//	ClientSocket = ServerSocket->Accept(clientInfo);
	//}
}

GameApp::GameApp() :
	ServerSocket(nullptr),
	ClientSocket(nullptr)
{}

GameApp::~GameApp()
{
}

void GameApp::GuiInit()
{

	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = Keys::TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = Keys::LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = Keys::RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = Keys::UP;
	io.KeyMap[ImGuiKey_DownArrow] = Keys::DOWN;
	io.KeyMap[ImGuiKey_PageUp] = Keys::PGUP;
	io.KeyMap[ImGuiKey_PageDown] = Keys::PGDN;
	io.KeyMap[ImGuiKey_Home] = Keys::HOME;
	io.KeyMap[ImGuiKey_End] = Keys::END;
	io.KeyMap[ImGuiKey_Delete] = Keys::DEL;
	io.KeyMap[ImGuiKey_Backspace] = Keys::BACKSPACE;
	io.KeyMap[ImGuiKey_Enter] = Keys::ENTER;
	io.KeyMap[ImGuiKey_Escape] = Keys::ESCAPE;
	io.KeyMap[ImGuiKey_A] = Keys::A;
	io.KeyMap[ImGuiKey_C] = Keys::C;
	io.KeyMap[ImGuiKey_V] = Keys::V;
	io.KeyMap[ImGuiKey_X] = Keys::X;
	io.KeyMap[ImGuiKey_Y] = Keys::Y;
	io.KeyMap[ImGuiKey_Z] = Keys::Z;

	// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
	//if (wParam > 0 && wParam < 0x10000)
	//	io.AddInputCharacter((unsigned short)wParam);
}
void GameApp::GuiUpdate()
{
	//Capture new state
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[0] = inputSystem->Get()->IsMouseDown(Mouse::LBUTTON);
	io.MouseDown[1] = inputSystem->Get()->IsMouseDown(Mouse::RBUTTON);
	io.MouseDown[2] = inputSystem->Get()->IsMouseDown(Mouse::MBUTTON);
	io.MouseWheel += inputSystem->Get()->GetMouseMoveZ();
	io.MousePos.x = (float)inputSystem->Get()->GetMouseScreenX();
	io.MousePos.y = (float)inputSystem->Get()->GetMouseScreenY();

	for (int i = 0; i < 256; ++i)
	{
		io.KeysDown[i] = inputSystem->Get()->IsKeyDown(i);
	}
}

void GameApp::OnInitialize(uint32_t width, uint32_t height)
{
	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());
	inputSystem = Input::InputSystem::Get();
	Network::Initialize();
	World::Initialize();
	mTimer.Initialize();
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Graphics::SimpleDraw::Initialize();
	Graphics::Gui::Initialize(mWindow.GetWindowHandle());
	GuiInit();

	const char* hostAddress = "127.0.0.1";
	if (__argc >= 2)
	{
		hostAddress = __argv[1];
		master = false;
		
		World::Get()->SetTeam(1);
	}
	else
	{
		master = true;
		World::Get()->SetTeam(0);
	}

	Network::SocketAddress tempInfo(hostAddress, port);
	serverInfo = tempInfo;

	if (master)
	{
		ServerSocket = new Network::TCPSocket();
		ServerSocket->Open();
		ServerSocket->SetNonBlocking(true);
		ServerSocket->Bind(serverInfo);
		ServerSocket->Listen(10);
	}
	else if (!master)
	{
		// Resolve host using address
		in_addr iaHost;

		iaHost.s_addr = inet_addr(hostAddress); // LocalHost
		HOSTENT* hostEntry = gethostbyaddr((const char*)&iaHost, sizeof(struct in_addr), AF_INET);
		if (hostEntry == nullptr)
		{
			//SafeDelete(clientSideSocket);
			LOG("hostEntry is nullptr!");
		}

		// Fill host address information and connect

		Network::SocketAddress serverInfo;
		serverInfo.Set(AF_INET, *((LPIN_ADDR)*hostEntry->h_addr_list), port);

		ClientSocket = new Network::TCPSocket();
		ClientSocket->Open();
		ClientSocket->SetNonBlocking(true);
		ClientSocket->SetNoDelay(true);
		ClientSocket->Connect(serverInfo);
	}
}

//Difference Between Server and Client
// Send Command List to :  Server sends to client, Client sends to server
// Receive Other guys commands: Server receives from client, client receives from server
// Everything else = same	

void GameApp::OnUpdate()
{
	if (master)
	{
		if (!accepted)
		{
			IN_ADDR sinAddr;
			sinAddr.S_un.S_addr = INADDR_ANY;
			serverInfo.Set(AF_INET, sinAddr, port);
			ClientSocket = ServerSocket->Accept(serverInfo, accepted);
		}
	}

	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

	mTimer.Update();

	inputSystem->Get()->Update();

	if (inputSystem->Get()->IsKeyPressed(Keys::ESCAPE))
	{
		PostQuitMessage(0);
	}

	GuiUpdate();

	//Steps to Sending and Receiving Commands
	// 1) Get my World's Commands
	//	CHECK
	// 2) Serialize CommandList to the MemStream
	// CHECK
	// 3) Send CommandList to the Other Guy
	//	CHECK
	// 4) Rewind the MemStream header
	// CHECK
	// 5) Receive the Other Guy's (Serialized) Commands 
	// CHECK
	// 6) Deserialize the Received Commands and append the CommandList	
	// CHECK
	// 7) Process all the Commands
	// CHECK

	//Get my world's commands
	CommandList commands = World::Get()->GetCommands();

	Network::MemoryStream memoryStream(MAX_BUFFER_SIZE);
	Network::StreamWriter writer(memoryStream);

	//Serialize to memstream
	for (auto c : commands)
	{
		//TODO extend writer to take CommandType
		writer.Write((int)c->GetType());
		c->Serialize(writer);
	}

	int bytesSent = 0;
	//Send my world's commands
	if (ClientSocket)
	{
		Graphics::SimpleDraw::AddScreenCircle(50, 50, 10, Vector4::Blue());
		if (commands.size() > 0)
		{
			bytesSent = ClientSocket->Send(memoryStream.GetData(), memoryStream.GetHead());
		}
	}
	if (ServerSocket)
	{
		Graphics::SimpleDraw::AddScreenCircle(50, 100, 10, Vector4::Green());
	}

	memoryStream.Reset();

	//Receive other guy's commands


	// On normal game loop bytes received is always zero
	// But if we break before receivecall, make commands, and step through to receive
	// bytesReceived returns a positive number

	char buffer[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	if (ClientSocket)
	{
		bytesReceived = ClientSocket->Receive(buffer, MAX_BUFFER_SIZE);
	}

	for (int i = 0; i < bytesReceived; i++)
	{
		writer.Write(buffer[i]);
	}

	memoryStream.SetSize();
	memoryStream.Rewind();
	Network::StreamReader reader(memoryStream);

	//Deserialize commands & append to command list
	if (bytesReceived > 0)
	{
		int bytesLeft = reader.GetRemainingDataSize();
		while (bytesLeft > 0)
		{
			bytesLeft = reader.GetRemainingDataSize();

			int commandType;
			reader.Read(commandType);
			ICommand* c = nullptr;
			switch ((Command)commandType)
			{
			case Command::Spawn:
			{
				c = new SpawnCommand();
				break;
			}
			case Command::Move:
			{
				c = new MoveCommand();
				break;
			}
			}
			if (c)
			{
				c->Deserialize(reader);
				commands.push_back(c);
			}
		}
	}

	//Process ALL commands
	World::Get()->ProcessCommands(commands);

	//delete the commands (flush the commandlist for next frame)	
	for (auto c : commands)
	{
		SafeDelete(c);
	}

	if (inputSystem->IsKeyPressed(Keys::LCONTROL))
	{
		Network::MemoryStream saveStream;
		Network::StreamWriter fileWriter(saveStream);
		World::Get()->WriteSnapshot(fileWriter);

		FILE* file = nullptr;
		fopen_s(&file, "save.dat", "wb");
		fwrite(saveStream.GetData(), saveStream.GetSize(), 1, file);
		fclose(file);
	}
	if (inputSystem->IsKeyPressed(Keys::RCONTROL))
	{
		FILE* file = nullptr;
		fopen_s(&file, "save.dat", "rb");

		fseek(file, 0L, SEEK_END);
		int fileSize = ftell(file);
		fseek(file, 0L, SEEK_SET);

		char* fileBuffer = (char*)malloc(fileSize * sizeof(char));
		fread(fileBuffer, fileSize, 1, file);
		fclose(file);

		Network::MemoryStream loadStream((uint8_t*)fileBuffer, fileSize, true);
		Network::StreamReader fileReader(memoryStream);
		World::Get()->ApplySnapshot(fileReader);
	}

	RTS::UpdateCamera(mTimer.GetElapsedTime(), World::Get()->GetCamera());
	World::Get()->Update(mTimer.GetElapsedTime());

	Graphics::GraphicsSystem::Get()->BeginRender();

	RTS::DrawGround();
	World::Get()->Draw();
	RTS::DrawCursor();

	Graphics::SimpleDraw::Render(World::Get()->GetCamera());

	Graphics::Gui::BeginRender(mTimer.GetElapsedTime());
	static float f = 0.0f;
	ImGui::Text("Hello World");
	ImGui::SliderFloat("Float", &f, 0.0f, 1.0f);
	ImGui::ColorEdit3("clear color", (float*)&clear_col);
	if (ImGui::Button("Test Window")) show_test_window = !show_test_window;
	if (ImGui::Button("Another Window")) show_another_window = !show_another_window;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	Graphics::Gui::EndRender();

	Graphics::GraphicsSystem::Get()->EndRender();

	//TODO Put everything below this line above EndRender()

}


void GameApp::OnTerminate()
{
	if (ServerSocket)
	{
		ServerSocket->Close();
	}
	if (ClientSocket)
	{
		ClientSocket->Close();
	}
	Graphics::Gui::Terminate();
	Graphics::SimpleDraw::Terminate();
	Graphics::GraphicsSystem::StaticTerminate();
	Input::InputSystem::StaticTerminate();

	World::Terminate();
	Network::Terminate();

	UnhookWindow();
	mWindow.Terminate();
}


