#pragma once
#include <Winsock2.h>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")


#define MAX_BUFFER_SIZE 1024

struct FileInfo
{
	std::string fileName;
	LONGLONG fileSize;
};

int main(int argc, char* argv[]){
	// Initialize Winsock api version 2.2
	uint16_t port = 8888;
	const char* dataPath = "Data/*";
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA fileFoundData;
	LONGLONG fileSize = 0;
	int numfiles = 0;
	std::vector<FileInfo> fileInfo;


	hFind = FindFirstFile(dataPath, &fileFoundData);
	do
	{
		char currentFileName[MAX_BUFFER_SIZE];
		if (fileFoundData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}
		else
		{
			FileInfo tempFileInfo;

			sprintf_s(currentFileName, "%s", fileFoundData.cFileName);
			tempFileInfo.fileName = currentFileName;

			LARGE_INTEGER tempFileSize;
			tempFileSize.HighPart = fileFoundData.nFileSizeHigh;
			tempFileSize.LowPart = fileFoundData.nFileSizeLow;
			fileSize = tempFileSize.QuadPart;

			tempFileInfo.fileSize = fileSize;
			fileInfo.push_back(tempFileInfo);
			numfiles++;
		}
	} while (FindNextFile(hFind, &fileFoundData) != 0);

	FindClose(hFind);

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
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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


	//Serve Forever....
	while (true)
	{
		//Accept any incoming client connection **BLOCKING**
		SOCKET client = accept(listener, NULL, NULL);
		if (client == INVALID_SOCKET)
		{
			printf("Accept Failed.\n");
			return -1;
		}

		printf("Client Connected!\n");

		//Create a buffer stream to fill with data for sending and receiving
		char buffer[MAX_BUFFER_SIZE];
		int bytesReceived = recv(client, buffer, MAX_BUFFER_SIZE - 1, 0);
		buffer[bytesReceived] = '\0';

		if (bytesReceived == SOCKET_ERROR)
		{
			printf("recv failed.\n");
			return -1;
		}
		if (bytesReceived == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			if (strcmp(buffer, "list") == 0)
			{

				printf("Files in %s:\n", dataPath);
				for (int i = 0; i < numfiles; i++)
				{	
					if (i == 0)
					{
						sprintf_s(buffer, "%s %lld\n", fileInfo[i].fileName.c_str(), fileInfo[i].fileSize);				
					}
					else
					{
						sprintf_s(buffer + strlen(buffer), MAX_BUFFER_SIZE, "%s %lld\n", fileInfo[i].fileName.c_str(), fileInfo[i].fileSize);
						//sprintf(buffer + strlen(buffer), "%s %lld\n", fileInfo[i].fileName.c_str(), fileInfo[i].fileSize);
					}
					if (fileInfo[i].fileSize == SOCKET_ERROR)
					{
						printf("Send Failed\n");
						return -1;
					}
				}
				send(client, buffer, MAX_BUFFER_SIZE, 0);
				printf(buffer);
			}
			else
			{
				FILE* currentFile;
				for (auto file : fileInfo)
				{
					if (strcmp(buffer, file.fileName.c_str()) == 0)
					{
						char* fileName = new char[(int)file.fileSize];
						sprintf_s(fileName, (int)file.fileSize, "Data//%s", file.fileName.c_str());			
						
						

						fopen_s(&currentFile, fileName, "rb");
						//currentFile = fopen(fileName, "rb");
						if (!currentFile)
						{
							printf("Error Reading File");
							return -1;
						}

						fseek(currentFile, 0, SEEK_SET);

						char *fileBuffer = new char[(int)file.fileSize];

						fread(fileBuffer, 1, (size_t)file.fileSize, currentFile);

						fclose(currentFile);

						int bytesSent = 0;
						int totalBytesSent = 0;

						do				
						{
							bytesSent = send(client, fileBuffer + totalBytesSent, (int)file.fileSize, 0);
							totalBytesSent += bytesSent;
						} while (bytesSent > 0);

						free(fileBuffer);
					}
				}
			}



			//Local IP
			//192.168.1.103
			// Sending a file in WinSock:
			// https://stackoverflow.com/questions/15170161/c-winsock-sending-file

		}

		//Close client connection
		closesocket(client);
	}

	// Close Listener Socket
	closesocket(listener);

	WSACleanup(); // shut down Winsock api

	system("pause");
	return 0;
}