

#include <NetworkingLibrary\Inc\Network.h>

#include <cstdio>
#include <iostream>
#include <string>

constexpr int kMaxBufferSize = 1024;

int main(int argc, char** argv)
{
	int result = 0;
	printf("Oh hai!\n");

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

	// Creates a listener socket using TCP/IP
	SOCKET sender = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sender)
	{
		printf("Failed to create socket.\n");	
		return -1;
	}

	//Fill server address information

	in_addr iaHost;
	iaHost.s_addr = inet_addr(hostAddress);
	HOSTENT* hostEntry = gethostbyaddr((const char*)&iaHost, sizeof(in_addr), AF_INET);

	if (nullptr == hostEntry)
	{
		printf("hostEntry incorrect");
		return -1;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(port);

	result = connect(sender, (LPSOCKADDR)&serverInfo, sizeof(sockaddr));
	if (SOCKET_ERROR == result)
	{
		printf("Failed to connect to server\n");
		return -1;
	}

	printf("Connected to server!\n");
	printf("Enter message: ");

	std::string message;
	getline(std::cin, message);

	printf("Sending: %s\n", message.c_str());

	send(sender, message.c_str(), (int)message.length(), 0);

	char buffer[kMaxBufferSize];
	const int bytesReceived = recv(sender, buffer, kMaxBufferSize - 1, 0);

	if (SOCKET_ERROR == bytesReceived)
	{
		printf("recv failed\n");
		return -1;
	}

	if (bytesReceived == 0)
	{
		printf("Connection closed. \n");
	}
	else
	{
		buffer[bytesReceived] = '\0';
		printf("Received: %s \n", buffer);
	}


	Network::Terminate();
	// Close listener socket
	closesocket(sender);

	// Shutdown Winsock


	system("pause");
	return 0;
}