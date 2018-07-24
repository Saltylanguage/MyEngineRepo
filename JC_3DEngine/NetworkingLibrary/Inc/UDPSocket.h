#pragma once


namespace Network
{
	class SocketAddress;

	class UDPSocket
	{
		bool Open();
		void Close();
		
		bool Bind(const SocketAddress& fromAddress);
		bool SetBroadcast(bool broadcast);
		bool SetNonBlocking(bool nonBlocking);

		int SendTo(const void* buffer, int len, const SocketAddress& toAddress);
		int ReceiveFrom(void* buffer, int len, SocketAddress& fromAddress);

	private:
		UDPSocket(const UDPSocket&) = delete;
		UDPSocket& operator=(const UDPSocket&) = delete;

		SOCKET mSocket;
	};
}