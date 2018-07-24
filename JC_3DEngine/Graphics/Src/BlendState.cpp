//====================================================================================================
// Filename:	BlendState.cpp
// Created by:	Peter Chan
//====================================================================================================

#include "Precompiled.h"

#include "BlendState.h"

#include "GraphicsSystem.h"

using namespace Graphics;

namespace
{
	D3D11_BLEND GetSrcBlend(BlendState::Mode mode)
	{
		switch(mode)
		{
		case BlendState::Mode::Opaque:
			return D3D11_BLEND_ONE;
		case BlendState::Mode::AlphaBlend:
			return D3D11_BLEND_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:
			return D3D11_BLEND_ONE;
		case BlendState::Mode::Additive:
			return D3D11_BLEND_SRC_ALPHA;
		default:
			ASSERT(false, "[BlendState] Invalid blend mode.");
			break;
		}
		return D3D11_BLEND_ONE;
	};

	D3D11_BLEND GetDestBlend(BlendState::Mode mode)
	{
		switch(mode)
		{
		case BlendState::Mode::Opaque:
			return D3D11_BLEND_ZERO;
		case BlendState::Mode::AlphaBlend:
			return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:
			return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::Additive:
			return D3D11_BLEND_ONE;
		default:
			ASSERT(false, "[BlendState] Invalid blend mode.");
			break;
		}
		return D3D11_BLEND_ZERO;
	};
}

BlendState::BlendState()
	: mBlendState(nullptr)
{
}

//----------------------------------------------------------------------------------------------------

BlendState::~BlendState()
{
	ASSERT(mBlendState == nullptr, "[BlendState] Blend state not released!");
}

//----------------------------------------------------------------------------------------------------

void BlendState::Initialize(Mode mode)
{
	D3D11_BLEND srcBlend = GetSrcBlend(mode);
	D3D11_BLEND destBlend = GetDestBlend(mode);

	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) || (destBlend != D3D11_BLEND_ZERO);

	desc.RenderTarget[0].SrcBlend  = desc.RenderTarget[0].SrcBlendAlpha  = srcBlend;
	desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOp   = desc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11Device* device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = device->CreateBlendState(&desc, &mBlendState);
	ASSERT(SUCCEEDED(hr), "[BlendState] Failed to create Blend state.");
}

//----------------------------------------------------------------------------------------------------

void BlendState::Terminate()
{
	SafeRelease(mBlendState);
}

//----------------------------------------------------------------------------------------------------

void BlendState::Set()
{
	GraphicsSystem::Get()->GetContext()->OMSetBlendState(mBlendState, nullptr, 0xffffffff);
}

//----------------------------------------------------------------------------------------------------

void BlendState::Clear()
{
	GraphicsSystem::Get()->GetContext()->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}