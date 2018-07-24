#pragma once
#include "Common.h"
#include "BlockAllocator.h"
#include "TypeHandle.h"

template<typename T>
class TypeAllocator : private BlockAllocator
{
public:
	TypeAllocator(u32 capacity);
	~TypeAllocator();

	TypeHandle<T> New();
	void Delete(TypeHandle<T> handle);

	bool IsValid(TypeHandle<T> handle) const;

	T* Get(TypeHandle<T>);

private:

	u32* mGenerations;

	//std::vector<int> generationVec;

};




template <typename T>
TypeAllocator<T>::TypeAllocator(u32 capacity)
	: BlockAllocator(sizeof(T), capacity), mGenerations(nullptr)
{

	ASSERT(capacity < (0x1 << TypeHandle<T>::IndexBits), "[TypeAllocator] capacity too large.");
	mGenerations = (u32*)calloc(capacity, sizeof(u32));
	TypeHandle<T>::sAllocator = this;
}

template <typename T>
TypeHandle<T> TypeAllocator<T>::New()
{

	TypeHandle<T> tHandle;
	if (mNextSlot == -1)
	{
		return tHandle;
	}

	tHandle.mIndex = (u32)mNextSlot;
	tHandle.mGeneration = mGenerations[mNextSlot];

	// Allocate Memory
	void* instance = Allocate();
	new(instance) T();

	return tHandle;
}
//Check if allocation was successful
//if (instance == nullptr)
//{
//	return TypeHandle<T>();
//}
//else (instance != nullptr)
//{
//	new(instance) T();
//	tHandle.mIndex = GetIndex(ptr);
//	tHandle.mGeneration = generationVec[tHandle.mIndex];
//	return tHandle;
//}


template <typename T>
T* TypeAllocator<T>::Get(TypeHandle<T> handle)
{
	if (!IsValid(handle))
	{
		return nullptr;
	}

	return reinterpret_cast<T*>(mData) + handle.mIndex;
}

template <typename T>
void TypeAllocator<T>::Delete(TypeHandle<T> handle)
{
	// Call the destructor
	T* ptr = handle.Get();

	if (ptr == nullptr)
	{
		return;
	}

	++mGenerations[handle.mIndex];

	ptr->~T();
	Free(ptr);

	//Release memory
}

template<typename T>
inline bool TypeAllocator<T>::IsValid(TypeHandle<T> handle) const
{
	const u32 index = handle.GetIndex();
	const u32 generation = handle.GetGeneration();

	return (index < mCapacity) && (generation == mGenerations[index]);
}


template<typename T>
TypeAllocator<T>::~TypeAllocator()
{
	TypeHandle<T>::sAllocator = nullptr;
}

//Week 2:

/*
TypeAllocator
- Adds method: New & Delete

New: Create a slot for designated type of the correct size
Calls block allocators new
Get the index of the allocated block ptr


*/