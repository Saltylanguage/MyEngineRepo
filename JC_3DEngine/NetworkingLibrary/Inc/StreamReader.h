#pragma once

namespace Network
{
	class MemoryStream;
	class StreamReader
	{
	public:
		StreamReader(MemoryStream& memStream);
		~StreamReader() {}

		void Read(int& data);
		void Read(size_t& data);
		void Read(float& data);
		void Read(double& data);

		void Read(bool& data);

		void Read(char& data);
		void Read(std::string& data);

		uint32_t GetRemainingDataSize() const;
		
	private:
		
		MemoryStream& mMemoryStream;

	};

}
