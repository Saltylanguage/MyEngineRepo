#include "Precompiled.h"
#include "MemoryStream.h"
#include "StreamReader.h"

Network::StreamReader::StreamReader(MemoryStream & memStream)
	:mMemoryStream(memStream)
{
}

void Network::StreamReader::Read(int & data)
{
	data = *reinterpret_cast<int*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	mMemoryStream.mHead += sizeof(int);
}

void Network::StreamReader::Read(size_t& data)
{
	data = *reinterpret_cast<size_t*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	mMemoryStream.mHead += sizeof(size_t);
}

void Network::StreamReader::Read(float & data)
{
	data = *reinterpret_cast<float*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	//memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	mMemoryStream.mHead += sizeof(float);
}

void Network::StreamReader::Read(double & data)
{
	data = *reinterpret_cast<double*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	//memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	mMemoryStream.mHead += sizeof(double);
}

void Network::StreamReader::Read(bool & data)
{
	data = *reinterpret_cast<bool*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	//memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	mMemoryStream.mHead += sizeof(bool);
}

void Network::StreamReader::Read(char & data)
{
	data = *reinterpret_cast<char*>(mMemoryStream.mBuffer + mMemoryStream.mHead);
	//memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	mMemoryStream.mHead += sizeof(char);
}

void Network::StreamReader::Read(std::string & data)
{
	data = *reinterpret_cast<std::string*>(mMemoryStream.mBuffer + mMemoryStream.mHead);

	//memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));

	mMemoryStream.mHead += sizeof(data);
}

uint32_t Network::StreamReader::GetRemainingDataSize() const
{
	return mMemoryStream.mSize - mMemoryStream.mHead;
}