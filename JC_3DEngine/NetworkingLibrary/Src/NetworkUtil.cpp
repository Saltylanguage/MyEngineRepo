#include "Precompiled.h"
#include "Network.h"

using namespace Network;

bool Network::Initialize()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	return result == 0;	
}

bool Network::Terminate()
{
	//Shutdown winsock
	int result = WSACleanup();
	return result == 0;
}

