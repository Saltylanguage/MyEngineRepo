#include "Precompiled.h"

#include "MetaType.h"
#include "MetaUtil.h"

#include "Math/Inc/EngineMath.h"


MetaType::MetaType(const char* name, Type type, uint32_t size, CreateFunc create, DestroyFunc destroy)
	: mName(name)
	, mType(type)
	, mSize(size)
	, mCreate(create)
	, mDestroy(destroy)
{}

MetaType::~MetaType()
{}


#define META_REGISTER_TYPE(Name, DataType)\
	namespace Meta {namespace Detail {\
		void* Create##Name() {return new DataType;}\
		void Destroy##Name(void* data) {delete static_cast<DataType*>(data);}\
	}}\
	template <> const MetaType* MetaUtil::DeduceDataType<DataType>()\
	{\
		static MetaType sMetaType(#Name, MetaType::Type::##Name, sizeof(DataType),\
										 Meta::Detail::Create##Name,\
										 Meta::Detail::Destroy##Name);\
		return &sMetaType;\
	}


META_REGISTER_TYPE(Int, int);
META_REGISTER_TYPE(UInt, uint32_t);
META_REGISTER_TYPE(Float, float);
META_REGISTER_TYPE(Bool, bool);
META_REGISTER_TYPE(String, std::string);
META_REGISTER_TYPE(Vector2, Math::Vector2);
META_REGISTER_TYPE(Vector3, Math::Vector3);
META_REGISTER_TYPE(Quaternion, Math::Quaternion);
META_REGISTER_TYPE(Color, Math::Vector4);

