#pragma once

// Description: Helpers for deallocation


template <typename T>
inline void SafeDelete(T * &ptr)
{
	delete ptr;
	ptr = nullptr;
}


template <typename T>
inline void SafeDeleteArrays(T * &ptr)
{
	delete[] ptr;
	ptr = nullptr;
}

template<typename T>
inline void SafeRelease(T*& ptr)
{
	if (ptr != nullptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}
