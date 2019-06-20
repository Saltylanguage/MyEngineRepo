
#include "Precompiled.h"
#include "BlockAllocator.h"
#include <algorithm>
#include <vector>



BlockAllocator::BlockAllocator(u32 blockSize, u32 capacity) :
	mBlockSize(std::max<s32>(sizeof(s32),(s32)blockSize)),
	mCapacity(capacity),
	mData(nullptr),
	mNextSlot(0)
{	
	mData = (reinterpret_cast<u8*>(malloc(mBlockSize * capacity)));
	for (int i = 0; i + 1 < (s32)mCapacity; ++i)
	{
		GetBlockAsInt(i) = i + 1;
	}
	GetBlockAsInt(capacity - 1) = -1;
}


s32& BlockAllocator::GetBlockAsInt(u32 index)
{
	return *(reinterpret_cast<s32*>(mData + (index * mBlockSize)));
}

s32 BlockAllocator::GetIndex(void * ptr)
{
	return (reinterpret_cast<u8*>(ptr) - mData) / mBlockSize;
}

void * BlockAllocator::GetPointer(int index)
{
	return mData + mBlockSize * index;
}

BlockAllocator::~BlockAllocator()
{
	// free memory
	free(mData);
}

void * BlockAllocator::Allocate()
{
	if (mNextSlot != -1)
	{
		void* ptr = mData + (mBlockSize *mNextSlot);

		mNextSlot = *(reinterpret_cast<int*>(ptr));

		return ptr;
	}	
	return nullptr;
}

void BlockAllocator::Free(void * ptr)
{
	if (ptr == nullptr || ptr < mData || ptr > (mData + mCapacity * mBlockSize))
	{
		return;
	}
	int newFreeSlot = ((u8*)ptr - mData) / mBlockSize;
	*(reinterpret_cast<int*>(ptr)) = mNextSlot;
	
	mNextSlot = newFreeSlot;
}
