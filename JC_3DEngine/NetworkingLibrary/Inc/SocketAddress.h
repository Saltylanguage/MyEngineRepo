#pragma once


namespace Network 
{
	
	class SocketAddress
	{
	public:
		SocketAddress();
		SocketAddress(const char* host, uint16_t port);
		SocketAddress(uint16_t port);
		SocketAddress(const sockaddr& sockAddr);

		const char* GetHost() const;
		void Set(ADDRESS_FAMILY addressFamily, IN_ADDR address, uint16_t port)
		{
			mSockAddr.sin_family = addressFamily;
			mSockAddr.sin_addr = address;
			mSockAddr.sin_port = htons(port);
		}

	private:
		friend class UDPSocket;
		friend class TCPSocket;

		sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
		const sockaddr_in* GetAsSockAddrIn() const { return reinterpret_cast<const sockaddr_in*>(&mSockAddr); }

		uint32_t& GetIP4() { return *reinterpret_cast<uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
		const uint32_t& GetIP4() const { return *reinterpret_cast<const uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }

		uint16_t& GetPort() { return *reinterpret_cast<uint16_t*>(&GetAsSockAddrIn()->sin_port); }
		const uint16_t& GetPort() const { return *reinterpret_cast<const uint16_t*>(&GetAsSockAddrIn()->sin_port); }

		size_t GetSize() const { return sizeof(sockaddr); }

		sockaddr_in mSockAddr;
	};

} // namespace Network

