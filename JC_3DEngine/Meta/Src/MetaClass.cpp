#include "Precompiled.h"

#include "MetaClass.h"
#include "MetaField.h"

MetaClass::MetaClass(const char* name, uint32_t size, MetaType::CreateFunc create, MetaType::DestroyFunc destroy, const MetaClass* parent, const MetaField* fields, uint32_t numFields)
	: MetaType(name, MetaType::Type::Class, size, create, destroy)
	, mParent(parent)
	, mFields(fields)
	, mNumFields(numFields)
{}

const MetaField* MetaClass::FindField(const char* name) const
{
	for (uint32_t i = 0; i < mNumFields; ++i)
	{
		const MetaField& f = mFields[i];
		if (strcmp(name, f.GetName()) == 0)
		{
			return &f;
		}
	}

	if (mParent != nullptr)
	{
		return mParent->FindField(name);
	}

	return nullptr;
}