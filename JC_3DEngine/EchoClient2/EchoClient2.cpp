#include <NetworkingLibrary\Inc\Network.h>

constexpr int kMaxBufferSize = 1024;

int main(int argc, char** argv)
{
	int result = 0;
	printf("Hello!\n");

	const char* hostAddress = "127.0.0.1";
	uint16_t port = 8888;

	if (argc >= 2)
	{
		hostAddress = argv[1];
	}
	if (argc >= 3)
	{
		port = static_cast<uint16_t>(atoi(argv[2]));
	}

	//Network::Socket socket;

	if (!Network::Initialize())
	{
		printf("Network Initialization Failed.\n");
		return -1;
	}

	Network::TCPSocket mTCPSocket;

	//Fill server address information
	Network::SocketAddress serverInfo(hostAddress,port);
	mTCPSocket.Connect(serverInfo);

	printf("Enter message: ");

	std::string message;
	getline(std::cin, message);

	printf("Sending: %s\n", message.c_str());
	mTCPSocket.Send((void*)message.c_str(), message.length());

	void* buffer = new char[kMaxBufferSize];
	const int bytesReceived = mTCPSocket.Receive((void*)buffer, kMaxBufferSize);

	// Shutdown Winsock
	Network::Terminate();
	// Close listener socket
	mTCPSocket.Terminate();

	system("pause");
	return 0;
}