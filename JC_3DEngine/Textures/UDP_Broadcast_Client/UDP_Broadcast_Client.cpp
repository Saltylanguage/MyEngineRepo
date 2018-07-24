#pragma once
#include <Winsock2.h>
#include <cstdint>
#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <process.h>


#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER_SIZE 1024

SOCKET mySocket;
char *buffer = new char[MAX_BUFFER_SIZE];

void receiveMessage(void* param)
{
	 recv(mySocket, buffer, MAX_BUFFER_SIZE, 0);
	 printf(buffer);
}


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
	mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

	_beginthread(receiveMessage, 0, NULL);
	//Wait for server response **BLOCKING**
	_getch();
	//Close All Sockets
	closesocket(mySocket);

	return 0;
}


