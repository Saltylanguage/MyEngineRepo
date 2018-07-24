#pragma once
#include <Winsock2.h>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_BUFFER_SIZE 1024



SOCKET mySocket;
std::mutex mainLock;
std::string userName;
std::thread receiveMessageThread;
std::thread killThread;


bool isAlive = true;

void Thread_Receive()
{
	while (true)
	{
		char messageBuffer[MAX_BUFFER_SIZE];
		int bytesReceived = recv(mySocket, messageBuffer, MAX_BUFFER_SIZE - 1, 0);
		messageBuffer[bytesReceived] = '\0';
		mainLock.lock();

		for (size_t i = 0; i <= userName.length() + 1; i++)
		{
			printf("\b");
		}
		for (size_t i = 0; i <= userName.length() + 1; i++)
		{
			printf(" ");
		}
		for (size_t i = 0; i <= userName.length() + 1; i++)
		{
			printf("\b");
		}

		printf("%s\n%s> ", messageBuffer, userName.c_str());
		mainLock.unlock();
	}

}

void Thread_Kill()
{
	while (GetAsyncKeyState(VK_ESCAPE) == 0)
	{
		Sleep(10);
	}	
	exit(0);
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
		mainLock.lock();
		printf("WSAStartup failed.\n");
		mainLock.unlock();
		return -1;
	}

	//Creates a listener socket using TCP/IP
	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket == INVALID_SOCKET)
	{
		mainLock.lock();
		printf("socket failed.\n");
		mainLock.unlock();
		return -1;
	}

	//std::string ipString;

	//printf("Enter IP: ");
	//getline(std::cin, ipString);
	printf("Enter your Name: ");
	getline(std::cin, userName);

	//Resolve host using address
	in_addr iaHost;
	iaHost.s_addr = inet_addr(hostAddress);
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

	mainLock.lock();
	printf("Connected to server!\n");
	mainLock.unlock();

	result = send(mySocket, userName.c_str(), (int)userName.length(), 0);

	receiveMessageThread = std::thread(Thread_Receive);
	killThread = std::thread(Thread_Kill);

	bool firstPass = true;
	while (true)
	{
			mainLock.lock();
			printf("%s> ", userName.c_str());
			mainLock.unlock();
			firstPass = false;


		std::string message;

		getline(std::cin, message);

		std::string fullMessageWithName = userName + "> " + message;

		//Send User message
		send(mySocket, fullMessageWithName.c_str(), (int)fullMessageWithName.length(), 0);
	}
	//Close All Sockets

	receiveMessageThread.join();
	killThread.join();
	closesocket(mySocket);


	return 0;
}


