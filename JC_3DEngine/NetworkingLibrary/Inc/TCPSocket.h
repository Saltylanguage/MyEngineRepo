#pragma once


namespace Network
{
	class SocketAddress;
	class TCPSocket
	{
	public:
		TCPSocket();
		~TCPSocket();

		bool Open();
		void Close();

		bool SetNoDelay(bool noDelay);
		bool SetNonBlocking(bool nonBlocking);

		bool Connect(const SocketAddress& address);
		bool Bind(const SocketAddress& address);

		TCPSocket* Accept(SocketAddress& fromAddress, bool& alreadyConnected);

		int Listen(int backlog);
		int Send(const void* buffer, int length);
		int Receive(void* buffer, int length);

		void Terminate();

	private:
		SOCKET mSocket;

			/*

			connect
			bind
			listen int backlog
			accept sockaddr
			send - void* buffer and int length
			receive - void* buffer and int length

			*/

	};
}