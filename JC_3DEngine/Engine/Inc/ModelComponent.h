#ifndef INCLUDED_ENGINE_MODELCOMPONENT_H
#define INCLUDED_ENGINE_MODELCOMPONENT_H

#include "Component.h"
#include "Math/Inc/EngineMath.h"
#include "Graphics\Inc\Model.h"

class TransformComponent;

class ModelComponent : public Component
{
public:
	META_CLASS_DECLARE;

	ModelComponent();
	~ModelComponent() override;

	void Initialize() override;
	void Terminate() override;

	void Render() override;
	
	void SetFilename(const char* filename)			{ mFilename = filename; }
	void SetRotation(const Math::Vector3& rotation)	{ mRotation = rotation; }
	void SetOffset(const Math::Vector3& offset)		{ mOffset = offset; }

private:
	const TransformComponent* mTransformComponent;

	Graphics::Model mModel;

	std::string mFilename;

	Math::Vector3 mRotation;
	Math::Vector3 mOffset;
};

#endif // #ifndef INCLUDED_ENGINE_MODELCOMPONENT_H