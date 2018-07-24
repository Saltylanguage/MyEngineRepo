#pragma once

class MetaType;

namespace MetaUtil
{
	template <typename DataType>
	const MetaType* DeduceDataType();

	template <typename ClassType, typename DataType>
	inline uint32_t GetFieldOffset(DataType ClassType::* field)
	{
		return (uint32_t)(void*)&(((ClassType*)nullptr)->*field);
	}


	template <typename ToType, typename FromType>
	inline ToType* DynamicCast(FromType* from)
	{
		const MetaClass* metaClass = from->GetMetaClass();
		while (metaClass)
		{
			if (metaClass == ToType::GetStaticMetaClass())
			{
				return static_cast<ToType*>(from);
			}
			metaClass = metaClass->GetParent();
		}
		return nullptr;
	}


}