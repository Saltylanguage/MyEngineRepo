
#include "Precompiled.h"

#include <MetaField.h>



MetaField::MetaField(const char* name, const MetaType* type, uint32_t memOffset)
	: mName(name)
	, mType(type)
	, mMemoryOffset(memOffset)
{
}