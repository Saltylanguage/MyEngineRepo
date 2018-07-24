#include "Precompiled.h"
#include <GraphicsSystem.h>

using namespace Graphics;

namespace
{
	const D3D_DRIVER_TYPE kDriverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	const UINT kNumDriverTypes = ARRAYSIZE(kDriverTypes);

	const D3D_FEATURE_LEVEL kFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	const UINT kNumFeatureLevels = ARRAYSIZE(kFeatureLevels);

	GraphicsSystem* sGraphicsSystem = nullptr;
}

void Graphics::GraphicsSystem::StaticInitialize(HWND window, bool fullscreen)
{
	ASSERT(sGraphicsSystem == nullptr, "[Graphics::GraphicsSystem] System Already Initialized!");

	sGraphicsSystem = new GraphicsSystem();

	sGraphicsSystem->Initialize(window, fullscreen);	
}

void Graphics::GraphicsSystem::StaticTerminate()
{
	if (sGraphicsSystem != nullptr)
	{
		sGraphicsSystem->Terminate();

		SafeDelete(sGraphicsSystem);
	}
}

GraphicsSystem * Graphics::GraphicsSystem::Get()
{
	ASSERT(sGraphicsSystem != nullptr, "[Graphics::GraphicsSystem] No System Registered");
	return sGraphicsSystem;
}

//Start of Constructor/Destructor
Graphics::GraphicsSystem::GraphicsSystem() :
	mD3dDevice(nullptr),
	mImmediateContext(nullptr),
	mSwapChain(nullptr),
	mRenderTargetView(nullptr),
	mDepthStencilBuffer(nullptr),
	mDepthStencilView(nullptr),	
	mDriverType(D3D_DRIVER_TYPE_NULL),
	mFeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
}

Graphics::GraphicsSystem::~GraphicsSystem()
{
	ASSERT(mD3dDevice == nullptr, "[Graphics::GraphicsSystem] Terminate() must be called to clean up!");
}
// End of Constructor/Destructor



void Graphics::GraphicsSystem::Initialize(HWND window, bool fullscreen)
{

	RECT rc = {};
	GetClientRect(window, &rc);
	LONG width = rc.right - rc.left;
	LONG height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#if ((defined(DEBUG)) || defined(_DEBUG))
	{
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
#endif

	DXGI_SWAP_CHAIN_DESC descSwapChain = {};
	descSwapChain.BufferCount = 1;
	descSwapChain.BufferDesc.Width = width;
	descSwapChain.BufferDesc.Height = height;
	descSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descSwapChain.BufferDesc.RefreshRate.Numerator = 60;
	descSwapChain.BufferDesc.RefreshRate.Denominator = 1;
	descSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	descSwapChain.OutputWindow = window;
	descSwapChain.SampleDesc.Count = 1;
	descSwapChain.SampleDesc.Quality = 0;
	descSwapChain.Windowed = !fullscreen;
	descSwapChain.Flags = createDeviceFlags;

	HRESULT hr = S_OK;
	for (UINT driverTypeIndex = 0; driverTypeIndex < kNumDriverTypes; ++driverTypeIndex)
	{
		mDriverType = kDriverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain
		(
			nullptr,
			mDriverType,
			nullptr,
			createDeviceFlags,
			kFeatureLevels,
			kNumFeatureLevels,
			D3D11_SDK_VERSION,
			&descSwapChain,
			&mSwapChain,
			&mD3dDevice,
			&mFeatureLevel,
			&mImmediateContext
		);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	ASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSystem] Failed to create device or swap chain");
	//cache swap chain description
	mSwapChain->GetDesc(&mSwapChainDesc);

	//create a render target view
	ID3D11Texture2D* backbuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backbuffer);
	ASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSystem] Failed to acces swap chain buffer");

	hr = mD3dDevice->CreateRenderTargetView(backbuffer, nullptr, &mRenderTargetView);
	SafeRelease(backbuffer);
	ASSERT(SUCCEEDED(hr), "Graphics::GraphicsSystem] Failed to create render target view.");
	
	//create depth stencil buffer
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = mD3dDevice->CreateTexture2D(&descDepth, nullptr, &mDepthStencilBuffer);

	ASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSystem] Failed to create depth stencil buffer.");

	//create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = mD3dDevice->CreateDepthStencilView(mDepthStencilBuffer, &descDSV, &mDepthStencilView);
	ASSERT(SUCCEEDED(hr), "[Graphics::GraphicsSystem] Failed to create depth stencil view");

	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	mViewport.Width = (FLOAT)width;
	mViewport.Height = (FLOAT)height;
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
	mViewport.TopLeftX = 0;
	mViewport.TopLeftY = 0;
	mImmediateContext->RSSetViewports(1, &mViewport);

}

void Graphics::GraphicsSystem::Terminate()
{
	SafeRelease(mDepthStencilView);
	SafeRelease(mDepthStencilBuffer);
	SafeRelease(mRenderTargetView);
	SafeRelease(mSwapChain);
	SafeRelease(mImmediateContext);
	SafeRelease(mD3dDevice);
}


void Graphics::GraphicsSystem::BeginRender()
{
	FLOAT clearColor[4]{ 0.0f,0.0f,0.0f,0.0f };
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, clearColor);
	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Graphics::GraphicsSystem::EndRender()
{
	mSwapChain->Present(0, 0);
}

void Graphics::GraphicsSystem::ToggleFullScreen()
{
	BOOL fullscreen;
	mSwapChain->GetFullscreenState(&fullscreen, nullptr);
	mSwapChain->SetFullscreenState(!fullscreen, nullptr);
}

uint32_t Graphics::GraphicsSystem::GetWidth() const
{
	return  mSwapChainDesc.BufferDesc.Width;
}

uint32_t Graphics::GraphicsSystem::GetHeight() const
{
	return  mSwapChainDesc.BufferDesc.Height;
}

void GraphicsSystem::ResetRenderTarget()
{
	ASSERT(mImmediateContext != nullptr, "[GraphicsSystem] failed to reset render target.");
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}
					 
void GraphicsSystem::ResetViewPort()
{
	ASSERT(mImmediateContext != nullptr, "[GraphicsSystem] failed to reset viewport");
	mImmediateContext->RSSetViewports(1, &mViewport);
}