#pragma once

class BlockAllocator
{
public:	
	BlockAllocator(u32 blockSize, u32 capacity);
	~BlockAllocator();

	void* Allocate();
	void Free(void* ptr);

	s32& GetBlockAsInt(u32 index);

protected:
	s32 GetIndex(void* ptr);
	void* GetPointer(int index);

	u32 mBlockSize;
	u32 mCapacity;
	u8* mData;
	s32 mNextSlot;

	//Homework:
	// 1) Finish implementing the block allocator class
	//	  There should only be one single malloc/free operation during the lifetime of the allocator

	// 2) Call BlockAllocator::Allocate() should return a valid address when there are free slots and
	//	  should return nullptr otherwise.

	// 3) Calling BlockAllocator::Free() should recycle the slot pointed to by the input pointer which
	//	  can be assigned out again in sebsequent Allocate() calls.
};




