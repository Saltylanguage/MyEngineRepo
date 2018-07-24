#include "Precompiled.h"

//#include "SpriteComponent.h"

#include "GameObject.h"
#include "Graphics\Inc\GraphicsSystem.h"
#include "SpriteComponent.h"
#include "Graphics\Inc\SpriteRenderer.h"


//#include "SpriteRenderer.h"

META_DERIVED_BEGIN(SpriteComponent, Component)
META_FIELD_BEGIN
	META_FIELD(mTextureName, "TextureName")
	META_FIELD(mPosition, "Position")
META_FIELD_END
META_CLASS_END

SpriteComponent::SpriteComponent()
	: mPosition(0.0f, 0.0f)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Initialize()
{
	Graphics::GraphicsSystem* gs = Graphics::GraphicsSystem::Get();

	wchar_t wbuffer[1024];
	mbstowcs_s(nullptr, wbuffer, mTextureName.c_str(), 1024);
	mTexture.Initialize(wbuffer);
}

void SpriteComponent::Terminate()
{
	mTexture.Terminate();
}

void SpriteComponent::Render2D()
{
	Graphics::SpriteRenderer::Get()->Draw(mTexture, mPosition);
}