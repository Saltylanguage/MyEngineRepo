#include "Precompiled.h"
#include "DepthStencilState.h"
#include "GraphicsSystem.h"

using namespace Graphics;

DepthStencilState::DepthStencilState() : mDepthStencilState(nullptr)
{
}

DepthStencilState::~DepthStencilState()
{
	ASSERT(mDepthStencilState == nullptr, "[Graphics::DepthStencilState] Terminate was not called!");
}


void DepthStencilState::Initialize()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = false;
	GraphicsSystem::Get()->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState);
}

void DepthStencilState::Terminate()
{
	SafeRelease(mDepthStencilState);
}

void DepthStencilState::EnableTesting(bool enabled)
{
	ASSERT(mDepthStencilState != nullptr, "[Graphics::DepthStencilState] Failed to get DepthStencilState (Not Initialized?)");
	GraphicsSystem::Get()->GetContext()->OMSetDepthStencilState(enabled ? nullptr : mDepthStencilState, 0);
}