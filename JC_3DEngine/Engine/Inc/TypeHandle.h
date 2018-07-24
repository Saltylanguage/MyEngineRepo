#pragma once


template<typename T>
class TypeAllocator;

template<typename T>
class TypeHandle
{

public:
	TypeHandle();

	bool IsValid() const;
	void Invalidate();

	T* Get();

	u32 GetIndex() const { return mIndex; }
	u32 GetGeneration() const { return mGeneration; }

	bool operator==(TypeHandle rhs) const
	{
		return mIndex == rhs.mIndex && mGeneration == rhs.mGeneration;
	}
	bool operator!=(TypeHandle rhs) const
	{
		return !(*this == rhs);
	}

private:
	
	static constexpr u32 IndexBits = 24;
	static constexpr u32 GenBits = 8;


	friend class TypeAllocator<T>;

	static TypeAllocator<T>* sAllocator;

	u32 mIndex : IndexBits;
	u32 mGeneration : GenBits;
};

template<typename T>
TypeAllocator<T>* TypeHandle<T>::sAllocator = nullptr;

template <typename T>
TypeHandle<T>::TypeHandle()
	:mIndex(0xffffffff)
	,mGeneration(0xffffffff)
{
	//ASSERT(mCapacity < (0x1 << TypeHandle::IndexBits), "[TypeAllocator] capacity too large.");
}

template <typename T> 
bool TypeHandle<T>::IsValid() const
{
	return sAllocator && sAllocator->IsValid(*this);
}

template <typename T>
void TypeHandle<T>::Invalidate()
{
	*this = Typehandle();
}

template <typename T>
T* TypeHandle<T>::Get()
{
	T* data = nullptr;
	if (sAllocator)
	{
		data = sAllocator->Get(*this);
	}
	return data;
}