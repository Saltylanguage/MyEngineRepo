#pragma once

class MetaType;

class MetaField
{
public:
	MetaField(const char* name, const MetaType* type, uint32_t memOffset);

	const char* GetName() const { return mName; }
	const MetaType* GetMetaType() const { return mType; }
	uint32_t GetMemoryOffset() const { return mMemoryOffset; }

private:
	const char* mName;
	const MetaType* mType;
	const uint32_t mMemoryOffset;
};