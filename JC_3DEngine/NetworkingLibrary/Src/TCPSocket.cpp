#include "Precompiled.h"

#include "TCPSocket.h"
#include "SocketAddress.h"

using namespace Network;

Network::TCPSocket::TCPSocket()
	:mSocket(INVALID_SOCKET)
{
}

Network::TCPSocket::~TCPSocket()
{
}

bool Network::TCPSocket::Open()
{
	ASSERT(mSocket == INVALID_SOCKET, "[TCPSocket] Socket already opened!");
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
	{
		LOG("[TCPSocket] Failed to open socket.");
		return false;
	}
	return true;
}

void Network::TCPSocket::Close()
{
	Terminate();
}

bool Network::TCPSocket::SetNoDelay(bool noDelay)
{
	u_long delayArg = noDelay ? 1 : 0;
	int result = setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&delayArg, sizeof(int));
	if (result == SOCKET_ERROR)
	{
		LOG("[TCPSocket] Failed to set non blocking mode. Error %d", WSAGetLastError());
		return false;
	}
	return true;
}

bool Network::TCPSocket::SetNonBlocking(bool nonBlocking)
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

bool TCPSocket::Connect(const SocketAddress & address)
{
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return false;
	}
	int result = connect(mSocket, &(sockaddr&)address.mSockAddr, address.GetSize());
	if (SOCKET_ERROR == result)
	{
		int lastError = WSAGetLastError();
		if (lastError == WSAEWOULDBLOCK)
		{
			fd_set write, err;
			TIMEVAL timeout;
			int timeoutSec = 10;
			FD_ZERO(&write);
			FD_ZERO(&err);
			FD_SET(mSocket, &write);
			FD_SET(mSocket, &err);
			timeout.tv_sec = timeoutSec;
			timeout.tv_usec = 0;
			result = select(0, NULL, &write, &err, &timeout);

			if (result == 0)
			{
				LOG("[TCPSOCKET] Connect timed out");
				return false;
			}
			else
			{
				if (FD_ISSET(mSocket, &write))
				{
					return true;
				}
				if (FD_ISSET(mSocket, &err))
				{
					LOG("[TCPSOCKET] Select Error");
					return false;
				}
			}
		}
		else
		{
			LOG("[TCPSocket] Failed to connect to server\n");
			return false;
		}
	}
	return true;
}

bool TCPSocket::Bind(const SocketAddress & address)
{
	if (mSocket == INVALID_SOCKET && !Open())
	{
		return false;
	}
	int result = bind(mSocket, &(sockaddr&)address.mSockAddr, address.GetSize());
	if (INVALID_SOCKET == result)
	{
		LOG("[Failed to create socket. Error: %d]", result);
		return false;
	}

	return true;
}

TCPSocket * Network::TCPSocket::Accept(SocketAddress & fromAddress, bool& alreadyConnected)
{
	socklen_t length = fromAddress.GetSize();

	SOCKET newSocket = accept(mSocket, &(sockaddr&)fromAddress.mSockAddr, &length);
	int size = (int)sizeof(fromAddress.mSockAddr);

	if (newSocket == INVALID_SOCKET)
	{
		int lastError = WSAGetLastError();
		if (lastError == WSAEWOULDBLOCK)
		{
			return nullptr;
		}
		else
		{
			LOG("[TCPSocket] Failed to accept connection. Error %d", lastError);
			return nullptr;
		}
	}

	TCPSocket* newTCP = new TCPSocket();
	newTCP->mSocket = newSocket;
	alreadyConnected = true;
	return newTCP;
}

int Network::TCPSocket::Listen(int backlog)
{
	return (listen(mSocket, backlog) == 0);
}

int TCPSocket::Send(const void* buffer, int length)
{
	const int bytesSent = send(mSocket, (char*)buffer, length, 0);

	if (SOCKET_ERROR == bytesSent)
	{
		printf("send failed\n");
		return -1;
	}

	return bytesSent;
}

int TCPSocket::Receive(void* buffer, int length)
{
	int bytesReceived = recv(mSocket, (char*)buffer, length, 0);

	if (SOCKET_ERROR == bytesReceived)
	{
		int lastError = WSAGetLastError();
		if (lastError == WSAEWOULDBLOCK)
		{
			bytesReceived = 0;
		}
		else
		{
			LOG("[TCPSOCKET] Failed to receive data. Error %d", (int)WSAGetLastError);
			return SOCKET_ERROR;
		}
	}
	return bytesReceived;
}

void Network::TCPSocket::Terminate()
{
	if (mSocket != SOCKET_ERROR)
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}
}
