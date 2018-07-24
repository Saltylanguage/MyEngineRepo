#pragma once



namespace Network
{
	class MemoryStream;

	class StreamWriter
	{
	public:
		StreamWriter(MemoryStream& memStream);
		~StreamWriter() {}
		
		void Write(int data);
		void Write(float data);
		void Write(double data);
		void Write(size_t data);
		void Write(bool data);

		void Write(char data);
		void Write(const std::string& data);

	private:

		MemoryStream& mMemoryStream;
		int resizeAmount = 10;

	};

}