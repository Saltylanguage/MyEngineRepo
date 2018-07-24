#pragma once

#include "Graphics/Inc/Color.h"
#include "Component.h"
#include "Math\Inc\EngineMath.h"
#include <Meta\Inc\Meta.h>

class TransformComponent;

class ColliderComponent : public Component
{
public:

	META_CLASS_DECLARE

	ColliderComponent();
	~ColliderComponent() override;

	void Initialize() override;
	void Render() override;

	const TransformComponent* GetTransform() { return mTransformComponent; }

	void SetCenter(const Math::Vector3& center)	{ mCenter = center; }
	void SetExtend(const Math::Vector3& extend)	{ mExtend = extend; }
	void SetColor(const Graphics::Color& color)			{ mColor = color; }
	
	Math::AABB GetAABB() const;

private:
	const TransformComponent* mTransformComponent;
	Math::Vector3 mCenter;
	Math::Vector3 mExtend;
	Graphics::Color mColor;
};

