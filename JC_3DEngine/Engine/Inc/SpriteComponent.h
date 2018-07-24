#pragma once

#include "Component.h"
#include "Math\Inc\EngineMath.h"
#include "Graphics\Inc\Texture.h"

class SpriteComponent : public Component
{
public:
	META_CLASS_DECLARE;

	SpriteComponent();
	~SpriteComponent() override;

	void Initialize() override;
	void Terminate() override;

	void Render2D() override;

	void SetPosition(const Math::Vector2& pos) { mPosition = pos; }
	void SetTextureName(const char* textureName) { mTextureName = textureName; }
	//void SetTexture() {	mTexture.Initialize(*GraphicsSystem::Get(), std::wstring(mTextureName.begin(), mTextureName.end()).c_str()); }

private:
	Math::Vector2 mPosition;
	std::string mTextureName;
	Graphics::Texture mTexture;
};

