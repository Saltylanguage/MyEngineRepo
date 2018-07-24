//====================================================================================================
// Filename:	SpriteRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SpriteRenderer.h"
#include "GraphicsSystem.h"
#include "Graphics\Inc\Texture.h"
#include <Externals\DirectXTK\Inc\CommonStates.h>
#include <Externals\DirectXTK\Inc\SpriteBatch.h>

using namespace Graphics;

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	SpriteRenderer* sSpriteRenderer = nullptr;
}

//====================================================================================================
// Class Definitions
//====================================================================================================

void SpriteRenderer::StaticInitialize()
{
	if (sSpriteRenderer == nullptr)
	{
		sSpriteRenderer = new SpriteRenderer();
		sSpriteRenderer->Initialize();
	}
}

//----------------------------------------------------------------------------------------------------

void SpriteRenderer::StaticTerminate()
{
	if (sSpriteRenderer)
	{
		sSpriteRenderer->Terminate();
		SafeDelete(sSpriteRenderer);
	}
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer* SpriteRenderer::Get()
{
	return sSpriteRenderer;
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::SpriteRenderer()
	: mpStateObjects(nullptr)
	, mpSpriteBatch(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::~SpriteRenderer()
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

//----------------------------------------------------------------------------------------------------

void SpriteRenderer::Initialize()
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	mpStateObjects = new DirectX::CommonStates(Graphics::GraphicsSystem::Get()->GetDevice());
	mpSpriteBatch = new DirectX::SpriteBatch(Graphics::GraphicsSystem::Get()->GetContext());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Terminate()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Already terminated.");
	SafeDelete(mpSpriteBatch);
	SafeDelete(mpStateObjects);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::BeginRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, mpStateObjects->NonPremultiplied());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::EndRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->End();

	// Restore state objects
	auto blendState = mpStateObjects->Opaque();
	auto depthStencilState = mpStateObjects->DepthDefault();
	auto rasterizerState = mpStateObjects->CullCounterClockwise();

	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(depthStencilState, 0);
	context->RSSetState(rasterizerState);
}

//----------------------------------------------------------------------------------------------------


void SpriteRenderer::Draw(Texture& texture, const Math::Vector2& position)
{	
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->Draw(texture.mpTexture, DirectX::XMFLOAT2(position.x, position.y));
}

/*

Problems:

1) Graphics - Sprite Renderer & Circular Dependancy
2) Delete Util - Solution thinks the functions are already defined somewhere
3) Unclear where to put Meta and how to reference it
(everything that can be a component: that project needs ref to meta)
4) Need to reformat all GameApp code to work with new architecture.

Questions:

1) Can you overload an operator outside of a class? 
	(Color = Vector4 OR Vector4 = Color)
2) Is there anything wrong with include's that start at the SolutionDir?

3) Why is my RTS not drawing Grid or units.
4) Why is my other apps not drawing mesh, terrain, etc.?

*/