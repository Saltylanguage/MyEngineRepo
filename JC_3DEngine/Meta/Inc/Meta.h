#pragma once

#include "MetaType.h"
#include "MetaUtil.h"

#include "MetaClass.h"
#include "MetaField.h"

#include "MetaRegistry.h"

#include <iterator>


#define META_CLASS_DECLARE\
	static const MetaClass* StaticGetMetaClass();\
	virtual const MetaClass* GetMetaClass() const {return StaticGetMetaClass();}

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	namespace Meta {namespace Detail {\
		void* Create##ClassType() {return new ClassType();}\
		void Destroy##ClassType(void* data) {delete static_cast<ClassType*>(data);}\
	}}\
	template<> const MetaType* MetaUtil::DeduceDataType<ClassType>()\
	{\
		return ClassType::StaticGetMetaClass();\
	}\
	const MetaClass* ClassType::StaticGetMetaClass()\
	{\
		typedef ClassType ClassTypeDef;\
		const char* ClassName = #ClassType;\
		MetaType::CreateFunc Create = Meta::Detail::Create##ClassType;\
		MetaType::DestroyFunc Destroy = Meta::Detail::Destroy##ClassType;

#define META_CLASS_BEGIN(ClassType)\
	 META_CLASS_BEGIN_INTERNAL(ClassType)\
		const MetaClass* parent = nullptr;	

#define META_DERIVED_BEGIN(ClassType, BaseType)\
	 META_CLASS_BEGIN_INTERNAL(ClassType)\
		const MetaClass* parent = BaseType##::StaticGetMetaClass();
	
#define META_FIELD_BEGIN\
	static const MetaField fields[] = {

#define META_FIELD(Var, Name)\
	MetaField(Name, MetaUtil::DeduceDataType<decltype(ClassTypeDef::##Var)>(), MetaUtil::GetFieldOffset(&ClassTypeDef::##Var)),

#define META_FIELD_END\
	};\
	const u32 numFields = (std::size)(fields);

#define META_FIELD_EMPTY\
	const MetaField* fields = nullptr;\
	const u32 numFields = 0;

#define META_CLASS_END\
	static const MetaClass sMetaClass(ClassName, sizeof(ClassTypeDef), Create, Destroy, parent, fields, numFields); \
	return &sMetaClass; \
}









