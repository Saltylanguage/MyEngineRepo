#ifndef INCLUDED_GRAPHICS_CONSTANTBUFFER_H
#define INCLUDED_GRAPHICS_CONSTANTBUFFER_H

//====================================================================================================
// Filename:	ConstantBuffer.h
// Created by:	Peter Chan
// Description:	Class for a constant buffer.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Graphics
{

//====================================================================================================
// Class Declarations
//====================================================================================================

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Initialize(uint32_t bufferSize, const void* initData = nullptr);
	void Terminate();

	void Set(const void* data);
	
	void BindVS(uint32_t slot = 0);
	void BindGS(uint32_t slot = 0);
	void BindPS(uint32_t slot = 0);
	void BindCS(uint32_t slot = 0);

private:
	ID3D11Buffer* mBuffer;
};

//----------------------------------------------------------------------------------------------------

template <typename T>
class TypedConstantBuffer : public ConstantBuffer
{
public:
	void Initialize()
	{
		ConstantBuffer::Initialize(GetPaddedSize());
	}

	void Initialize(const T& data)
	{
		ConstantBuffer::Initialize(GetPaddedSize(), &data);
	}

	void Set(const T& data)
	{
		ConstantBuffer::Set(&data);
	}

private:
	uint32_t GetPaddedSize() const
	{
		const uint32_t typeSize = sizeof(T);
		const uint32_t bufferSize = (typeSize % 16) ? ((typeSize / 16) + 1) * 16 : typeSize;
		return bufferSize;
	}
};

} // namespace Graphics

#endif // #ifndef INCLUDED_GRAPHICS_CONSTANTBUFFER_H