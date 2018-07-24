#pragma once


#include "MetaType.h"

class MetaField;

class MetaClass : public MetaType
{
public:
	MetaClass(const char* name, uint32_t size, 
			  MetaType::CreateFunc create,
			  MetaType::DestroyFunc destroy,
		      const MetaClass* parent, 
			  const MetaField* fields, uint32_t numFields);

	const MetaClass* GetParent() const { return mParent; }

	const MetaField* FindField(const char* name) const;

private:

	const MetaClass* mParent;
	const MetaField* mFields;
	uint32_t mNumFields;
};