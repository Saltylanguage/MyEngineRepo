
#include "Precompiled.h"
#include "MemoryStream.h"
#include "StreamWriter.h"


using namespace Network;

Network::StreamWriter::StreamWriter(MemoryStream & memStream)
	:mMemoryStream(memStream)
{
}

void StreamWriter::Write(int data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(int)));
	}
	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(int);
}


void Network::StreamWriter::Write(float data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(float)));
	}
	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(float);
}



void Network::StreamWriter::Write(double data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(double)));
	}
	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(double);
}

void Network::StreamWriter::Write(size_t data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(size_t)));
	}
	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(size_t));
	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(size_t);
}


void StreamWriter::Write(bool data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(bool)));
	}

	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));

	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(bool);
}



void StreamWriter::Write(char data)
{

	//1 - if the head is at the end increase the size of the stream
	if(mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(char)));
	}
	//2 - write the data to the memoryStream
	//reinterpret_cast<char&>(*mMemoryStream.mBuffer) = data;
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, sizeof(data));
	//3 - move the head ptr forward 1 byte 
	mMemoryStream.mHead += sizeof(char);
}



void Network::StreamWriter::Write(const std::string & data)
{
	//1 - if the head is at the end increase the size of the stream
	if (mMemoryStream.mHead >= mMemoryStream.mCapacity)
	{
		//increase size some amount
		mMemoryStream.ReallocBuffer(mMemoryStream.mCapacity + (resizeAmount * sizeof(data)));
	}


	
	// Get the size of the string
	int size = data.length();
	// Send the size so we know how many bytes to read from the string
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &size, sizeof(int));
	//Move the head ptr 1 forward
	mMemoryStream.mHead += sizeof(int);

	//2 - write the data to the memoryStream
	memcpy(mMemoryStream.mBuffer + mMemoryStream.mHead, &data, size);
	//3 - move the head ptr forward by the length of the string
	mMemoryStream.mHead += size;
}
