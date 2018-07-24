#include "Precompiled.h"
#include "XMLReader.h"

#include "Engine.h"
#include "Utils.h"
#include <Externals/TinyXML/tinyxml.h>
#include <Graphics/Inc/Color.h>
#include <Math/Inc/EngineMath.h>

using namespace Math;
using namespace Graphics;

namespace
{
	bool ReadValue(int* instance, const TiXmlNode* node)
	{		
		*instance = atoi(node->Value());
		return true;
	}

	bool ReadValue(float* instance, const TiXmlNode* node)
	{
		*instance = (float)atof(node->Value());
		return true;
	}

	bool ReadValue(bool* instance, const TiXmlNode* node)
	{
		*instance = Utils::AreEqual(node->Value(), "true");
		return true;
	}

	bool ReadValue(std::string* instance, const TiXmlNode* node)
	{
		*instance = node->Value();
		return true;
	}

	bool ReadValue(Vector3* instance, const TiXmlNode* node)
	{
		int count = sscanf_s(node->Value(), "%f,%f,%f", &instance->x, &instance->y, &instance->z);

		return count == 3;
	}

	bool ReadValue(Graphics::Color* instance, const TiXmlNode* node)
	{
		int count = sscanf_s(node->Value(), "%f,%f,%f,%f", &instance->r, &instance->g, &instance->b, &instance->a);

		return count == 4;
	}


	bool ReadType(void* instance, const MetaType* metaType, const TiXmlNode* node)
	{
		bool success = false;

		if (node != nullptr)
		{
			switch (metaType->GetType())
			{
			case MetaType::Type::Int:
				success = ReadValue((int*)instance, node);
				break;
			case MetaType::Type::Float:
				success = ReadValue((float*)instance, node);
				break;
			case MetaType::Type::Bool:
				success = ReadValue((bool*)instance, node);
				break;
			case MetaType::Type::String:
				success = ReadValue((std::string*)instance, node);
				break;
			case MetaType::Type::Vector3:
				success = ReadValue((Math::Vector3*)instance, node);
				break;
			case MetaType::Type::Color:
				success = ReadValue((Graphics::Color*)instance, node);
				break;
			case MetaType::Type::Class:
				success = XMLReader::Read(instance, (const MetaClass*)metaType, node);
				break;
			default:
				ASSERT(false, "Unexpected meta type %d,", (s32)metaType->GetType());
				break;
			}
		}
			return success;
	}

}

bool XMLReader::Read(void * instance, const MetaClass * metaClass, const TiXmlNode * node)
{
	ASSERT(instance, "[XMLReader] instance should never be nullptr");
	bool success = true;
	while (node != nullptr)
	{
		const TiXmlElement* element = node->ToElement();
		if (element != nullptr)
		{
			const char* fieldName = element->Attribute("name");
			const MetaField* metaField = metaClass->FindField(fieldName);
			if (metaField != nullptr)
			{
				void* member = (u8*)instance + metaField->GetMemoryOffset();
				bool readSuccess = ReadType(member, metaField->GetMetaType(), element->FirstChild());
				if (!readSuccess)
				{
					LOG("[XMLReader] Problem reading data for %s:%s.", metaClass->GetName(), metaField->GetName());
					success = false;
				}
			}
		}
		node = node->NextSibling();		
	}

	return success;
}
