#include "Precompiled.h"

#include "UDPSocket.h"
#include "SocketAddress.h"

bool Network::UDPSocket::Open()
{
	ASSERT(mSocket == INVALID_SOCKET, "[UDPSocket] Socket already opened");
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		LOG("[UDPSocket] Failed to open socket");
		return false;
	}

	return true;

}

void Network::UDPSocket::Close()
{
	if (mSocket != INVALID_SOCKET)
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}
}

bool Network::UDPSocket::Bind(const SocketAddress &address)
{

	
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return false;
	}
	int result = bind(mSocket, &(sockaddr&)address.mSockAddr, address.GetSize());
	if (result == SOCKET_ERROR)
	{
		LOG("[UDPSocket] Failed to bind socket. Error: %d", WSAGetLastError())
		return false;
	}
	return true;
}

bool Network::UDPSocket::SetBroadcast(bool broadcast)
{
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return false;
	}

	BOOL optVal = broadcast;
	int result = setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optVal, sizeof(BOOL));
	if (result == SOCKET_ERROR)
	{

		return false;
	}
	return true;
}

bool Network::UDPSocket::SetNonBlocking(bool nonBlocking)
{
	u_long arg = nonBlocking ? 1 : 0;
	int result = ioctlsocket(mSocket, FIONBIO, &arg);
	if (result == SOCKET_ERROR)
	{
		LOG("[TCPSocket] Failed to set non blocking mode. Error %d", WSAGetLastError());
		return false;
	}
	return true;
}

int Network::UDPSocket::SendTo(const void * buffer, int len, const SocketAddress & toAddress)
{
	return 0;
}

int Network::UDPSocket::ReceiveFrom(void * buffer, int len, SocketAddress & fromAddress)
{
	int fromLength = fromAddress.GetSize();
	int bytesRead = recvfrom(mSocket, static_cast<char*>(buffer), len, 0, &(sockaddr&)fromAddress.mSockAddr, &fromLength);
	if (bytesRead >= 0)
	{
		return bytesRead;
	}
	else
	{
		int error = WSAGetLastError();
		if (error == WSAEWOULDBLOCK)
		{
			LOG("[UDPSocket] Connection reset");
			return -WSAECONNRESET;
		}
		else
		{
			LOG("[UDPSocket] Error on receive");
			return -error;
		}
	}	
}
