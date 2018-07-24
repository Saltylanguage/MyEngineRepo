#include "Precompiled.h"
#include "Texture.h"
#include "GraphicsSystem.h"

#include <Externals/DirectXTK/Inc/DDSTextureLoader.h>
#include <Externals/DirectXTK/Inc/WICTextureLoader.h>

using namespace Graphics;

Texture::Texture() : mpTexture(nullptr)
{
}

Texture::~Texture()
{
	ASSERT(mpTexture == nullptr, "[Graphics::Texture] Terminate was not called!");
}


void Texture::Initialize(const void * data, uint32_t width, uint32_t height)
{
	D3D11_TEXTURE2D_DESC desc;
	D3D11_SUBRESOURCE_DATA initData;
	auto device = Graphics::GraphicsSystem::Get()->GetDevice();


	desc.Width = 500; //TODO find actual width
	desc.Height = 500; //TODO find actual height
	desc.MipLevels = 0;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	HRESULT hr;
	ID3D11Texture2D* texture;
	hr = device->CreateTexture2D(&desc, &initData, &texture);
	ASSERT(SUCCEEDED(hr), "[Graphics::Texture] Failed to create Texture.");
	hr = device->CreateShaderResourceView(texture, nullptr, &mpTexture);
	ASSERT(SUCCEEDED(hr), "[Graphics::Texture] Failed to create Shader Resource View.");
	SafeRelease(texture);
}

void Texture::Initialize(const wchar_t* filename)
{
	auto device = Graphics::GraphicsSystem::Get()->GetDevice();
	
	if (wcsstr(filename, L".dds") != nullptr)
	{
		DirectX::CreateDDSTextureFromFile(device, filename, nullptr, &mpTexture);
	}
	else
	{
		DirectX::CreateWICTextureFromFile(device, filename, nullptr, &mpTexture);
	}
}

void Texture::Terminate()
{
	SafeRelease(mpTexture);
}

void Texture::BindPS(uint32_t slot)
{
	GraphicsSystem::Get()->GetContext()->PSSetShaderResources(slot, 1, &mpTexture);
}

void Graphics::Texture::BindVS(uint32_t slot)
{
	GraphicsSystem::Get()->GetContext()->VSSetShaderResources(slot, 1, &mpTexture);
}
