#include "Precompiled.h"

#include "ModelComponent.h"

#include "GameObject.h"
#include "Graphics/Inc/GraphicsSystem.h"
#include "TransformComponent.h"
#include "Math/Inc/EngineMath.h"

//#include "MeshRenderer.h"

META_DERIVED_BEGIN(ModelComponent, Component)
META_FIELD_BEGIN
META_FIELD(mFilename, "Filename")
META_FIELD(mRotation, "Rotation")
META_FIELD(mOffset, "Offset")
META_FIELD_END
META_CLASS_END

using namespace Graphics;

ModelComponent::ModelComponent()
	: mTransformComponent(nullptr)
{
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::Initialize()
{
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();

	GraphicsSystem* gs = GraphicsSystem::Get();
	mModel.Load(mFilename.c_str());
}

void ModelComponent::Terminate()
{
	mModel.Unload();
}

void ModelComponent::Render()
{
	//Math::Matrix matRotX = Math::Matrix::RotationX(mRotation.x * Math::kDegToRad);
	Math::Matrix matRotY = Math::Matrix::RotationY(mRotation.y * Math::kDegToRad);
	Math::Matrix matRotZ = Math::Matrix::RotationZ(mRotation.z * Math::kDegToRad);
	Math::Matrix matOffset = Math::Matrix::Translation(mOffset);
	Math::Matrix matWorld = mTransformComponent->GetLocalToWorld();
	//Math::Matrix transform = matRotX * matRotY * matRotZ * matOffset * matWorld;
	//mModel.Render(*MeshRenderer::Get(), transform);
}