#pragma once

class MetaType
{
public:

	typedef void* (*CreateFunc)();
	typedef void(*DestroyFunc)(void*);

	enum class Type
	{
		Int,
		UInt,
		Float,
		Bool,
		String,
		Vector2,
		Vector3,
		Quaternion,
		Color,
		Class
	};

	MetaType(const char* name, Type type, uint32_t size, CreateFunc create, DestroyFunc destroy);
	~MetaType();

	const char* GetName() const { return mName; }
	Type GetType() const { return mType; }
	const uint32_t GetSize() const { return mSize; }
	void* Create() const  { return mCreate(); }
	void Destroy(void* ptr) { mDestroy(ptr); }


private:
	const char* mName;
	const Type mType;
	const uint32_t mSize;

	CreateFunc mCreate;
	DestroyFunc mDestroy;
};