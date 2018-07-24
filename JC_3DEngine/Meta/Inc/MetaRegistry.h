#pragma once

class MetaClass;

namespace MetaRegistry
{

	void Register(const MetaClass* metaClass);
	const MetaClass* GetMetaClass(const char* className);

};