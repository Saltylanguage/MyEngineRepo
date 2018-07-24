#pragma once
#include <Winsock2.h>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER_SIZE 1024




struct Data
{
	char Buffer[MAX_BUFFER_SIZE];
	int Bytes;
};

int main(int argc, char* argv[])
{

	//Defaults
	const char* hostAddress = "127.0.0.1";
	uint16_t port = 8888;

	//Check for arguments
	if (argc >= 2)
	{
		hostAddress = argv[1];
	}
	if (argc >= 3)
	{
		port = static_cast<uint16_t>(atoi(argv[2]));
	}

	// Initialize Winsock api version 2.2
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed.\n");
		return -1;
	}

	//Creates a listener socket using TCP/IP
	SOCKET mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket == INVALID_SOCKET)
	{
		printf("socket failed.\n");
		return -1;
	}

	std::string ipString;
	printf("Enter IP: ");
	getline(std::cin, ipString);

	//Resolve host using address
	in_addr iaHost;
	
	iaHost.s_addr = inet_addr(ipString.c_str());
	HOSTENT* hostEntry = gethostbyaddr((const char *)&iaHost, sizeof(struct in_addr), AF_INET);

	if (hostEntry == nullptr)
	{
		printf("gethostbyaddr failed.\n");
		return -1;
	}

	//Fill host address information and connect
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(8888);
	result = connect(mySocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));

	if (result == SOCKET_ERROR)
	{
		printf("connect failed.\n");
		return -1;
	}

	printf("Connected to server!\n");
	printf("Enter Message: ");

	std::string message;
	getline(std::cin, message);

	printf("Sending : %s\n", message.c_str());

	//Send User message
	send(mySocket, message.c_str(), (int)message.length(), 0);

	//Wait for server response **BLOCKING**

	
	int bytesReceived = 0;

	Data mData;
	int totalBytesReceived = 0;

	if (strcmp(message.c_str(), "list") == 0)
	{
		mData.Bytes = recv(mySocket, mData.Buffer, MAX_BUFFER_SIZE - 1, 0);
		printf(mData.Buffer);
	}
	else
	{
		FILE* receivedFile;
		receivedFile = fopen(message.c_str(), "wb");
		while (mData.Bytes = recv(mySocket, mData.Buffer, MAX_BUFFER_SIZE - 1, 0))
		{
			if (SOCKET_ERROR == mData.Bytes)
			{
				printf("recv failed\n");
				return -1;
			}
			if (0 == mData.Bytes)
			{
				printf("Connection closed. \n");
				closesocket(mySocket);
				return 0;
			}

			totalBytesReceived += mData.Bytes;
			fwrite(mData.Buffer, 1, mData.Bytes, receivedFile);

			printf("Recieving %d bytes\n Total Bytes Received: %d\n", mData.Bytes, totalBytesReceived);

			// Add % complete:   100.0f * (float)totalBytesReceived / (float)fileSize)
			// printf signature: %.2f%% complete
		}

		fclose(receivedFile);
	}
	system("pause");

	//Close All Sockets
	closesocket(mySocket);

	return 0;
}


