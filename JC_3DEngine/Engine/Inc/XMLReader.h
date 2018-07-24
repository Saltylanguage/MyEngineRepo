#pragma once
#include "Meta\Inc\Meta.h"


class TiXmlNode;


class XMLReader
{
public:
	static bool Read(void* instance, const MetaClass* metaClass, const TiXmlNode* node);
};