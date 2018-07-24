#pragma once
#include <Winsock2.h>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <mutex>

#pragma comment(lib, "Ws2_32.lib")


#define MAX_BUFFER_SIZE 1024

struct Client
{
	SOCKET clientSocket;
	std::string userName;
};

std::vector<Client> clients;
SOCKET listener;
std::queue<std::string> messageQueue;
const int maxThreads = 10;
std::thread clientThreads[maxThreads];
std::mutex lock;



void Thread_ReceiveMessage(int index)
{
	int bytesReceived;
	while (true)
	{
		char messageBuffer[MAX_BUFFER_SIZE];

		bytesReceived = recv(clients[index].clientSocket, messageBuffer, MAX_BUFFER_SIZE - 1, 0);
		messageBuffer[bytesReceived] = '\0';
		if (bytesReceived == SOCKET_ERROR)
		{
			printf("recv failed.\n");
			return;
		}

		char formattedString[MAX_BUFFER_SIZE];
		lock.lock();
		sprintf_s(formattedString, "%s\0\n", messageBuffer);
		messageQueue.push(formattedString);

		printf("\n%s", formattedString);
		lock.unlock();
	}
}

void Thread_Accept()
{
	//printf("Accept Thread Start!");
	//fflush(stdout);
	int clientIndex = 0;
	int bytesReceived = 0;
	clients.reserve(10);
	while (true)
	{
		//Accept any incoming client connection **BLOCKING**
		Client tempClient;
		tempClient.clientSocket = accept(listener, NULL, NULL);

		if (tempClient.clientSocket == INVALID_SOCKET)
		{
			printf("Accept Failed.\n");
			return;
		}

		//Accept new clients and output client's username when they connect successfully
		char userNameBuffer[MAX_BUFFER_SIZE];
		bytesReceived = recv(tempClient.clientSocket, userNameBuffer, MAX_BUFFER_SIZE - 1, 0);
		userNameBuffer[bytesReceived] = '\0';

		tempClient.userName = userNameBuffer;

		printf("%s Connected!\n", tempClient.userName.c_str());

		clients.push_back(tempClient);
		//Start up a new thread to receive messages from each client
		clientThreads[clientIndex] = std::thread(Thread_ReceiveMessage, clientIndex);

		clientIndex++;

	}
}



void Thread_Dispatcher()
{
	while (true)
	{
		if (!messageQueue.empty())
		{
			std::string message = messageQueue.back();
			std::string nameString = message;
			int stopPoint = nameString.find_first_of('>');
			nameString = nameString.substr(0, stopPoint);
			for (size_t i = 0; i < clients.size(); i++)
			{
				if (nameString != clients[i].userName)
				{
					clients[i].userName;
					send(clients[i].clientSocket, messageQueue.back().c_str(), messageQueue.back().length(), 0);
				}
			}
			messageQueue.pop();
		}
		Sleep(100);
	}
}

int main(int argc, char* argv[]) {

	// Initialize Winsock api version 2.2
	uint16_t port = 8888;
	const char* dataPath = "Data/*";
	HANDLE hFind = INVALID_HANDLE_VALUE;
	//WIN32_FIND_DATA fileFoundData;
	LONGLONG fileSize = 0;
	int numfiles = 0;

	//char* username = nullptr;

	//Client testClient;
	//testClient.userName = username;

	//Check for arguments

	if (argc >= 2)
	{
		port = static_cast<uint32_t>(atoi(argv[1]));
	}
	if (argc >= 3)
	{
		dataPath = argv[2];
	}

	printf("Hello Network: Waiting for connections.\n");
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		printf("WSAStartup failed.\n");
		return -1;
	}

	//Creates a listener socket using TCP/IP

	listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listener == INVALID_SOCKET)
	{
		printf("Failed to create socket.\n");
		return -1;
	}

	// Fill server Address information
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(port);

	//Bind the address to our listener socket and listen for connection
	result = bind(listener, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	if (result == SOCKET_ERROR)
	{
		printf("Bind Failed.\n");
		return -1;
	}
	result = listen(listener, 10);
	if (result == SOCKET_ERROR)
	{
		printf("Listen failed.\n");
		return -1;
	}

	printf("Listening on port %hu...\n", port);


	std::thread acceptThread(Thread_Accept);
	std::thread dispatcherThread(Thread_Dispatcher);

	//Serve Forever....

	//Local IP
	//192.168.1.103
	// Sending a file in WinSock:
	// https://stackoverflow.com/questions/15170161/c-winsock-sending-file
//Close client connection


// Close Listener Socket
	_getch();
	for (size_t i = 0; i < clients.size(); i++)
	{
		clientThreads[i].join();
	}
	acceptThread.join();
	dispatcherThread.join();
	closesocket(listener);

	WSACleanup(); // shut down Winsock api

	system("pause");
	return 0;
}