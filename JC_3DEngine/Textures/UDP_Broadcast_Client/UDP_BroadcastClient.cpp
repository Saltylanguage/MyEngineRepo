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
sockaddr_in Sender_addr;

int len = sizeof(sockaddr_in);

char recvBuff[50];
int recvBuffLen = 50;


void receiveMessage(void* param)
{
	recv(mySocket, buffer, MAX_BUFFER_SIZE, 0);
	printf(buffer);
}


void recvFunct(void *param)
{
	while (1)
	{
		int bytesReceived = -1;
		bytesReceived = recvfrom(mySocket, recvBuff, recvBuffLen, 0, (sockaddr *)&Sender_addr, &len);
		recvBuff[bytesReceived] = (char)'/0';
		std::cout << "received message: " << recvBuff << std::endl;
		
		//recvfrom(mySocket, recvBuff, recvBuffLen, 0, (sockaddr *)&Sender_addr, &len);
		//std::cout << "received message: " << buffer << std::endl;
	}
}


int main(int argc, char* argv[])
{
	//Defaults
	//const char* hostAddress = "127.0.0.1";
	uint16_t port = 8888;

	//Check for arguments
	if (argc >= 2)
	{
		//hostAddress = argv[1];
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
	//in_addr iaHost;
	//iaHost.s_addr = inet_addr(ipString.c_str());
	//HOSTENT* hostEntry = gethostbyaddr((const char *)&iaHost, sizeof(struct in_addr), AF_INET);

	//if (hostEntry == nullptr)
	//{
	//	printf("gethostbyaddr failed.\n");
	//	return -1;
	//}

	//Fill host address information and connect
	SOCKADDR_IN serverInfo;

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(8888);
	serverInfo.sin_addr.s_addr = INADDR_ANY;

	result = bind(mySocket, (sockaddr*)&serverInfo, sizeof(serverInfo));
	
	if (result == SOCKET_ERROR)
	{
		printf("connect failed.\n");
		return -1;
	}
	char *buffer = new char[1024];
	int fromLength = sizeof(sockaddr_in);
	//int bytesReceived;
	//bytesReceived = recvfrom(mySocket, buffer, sizeof(buffer), 0, (sockaddr*)&serverInfo, &fromLength);	
	//printf("Connected to server!\n");

	_beginthread(recvFunct, 0, NULL);
	//Wait for server response **BLOCKING**
	_getch();
	//Close All Sockets
	closesocket(mySocket);
	system("pause");
	return 0;
}


