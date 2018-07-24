#include "Precompiled.h"
#include "PixelShader.h"
#include "GraphicsSystem.h"

using namespace Graphics;

void PixelShader::Bind()
{
	auto context = Graphics::GraphicsSystem::Get()->GetContext();

	context->PSSetShader(Shader, nullptr, 0);
}

void PixelShader::Initialize(const wchar_t* fileName)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	ID3DBlob* pShaderBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
		(
			fileName,
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			shaderFlags,
			0,
			&pShaderBlob,
			&pErrorBlob
			);
	ASSERT(SUCCEEDED(hr), "Failed to compile shader, Error %s", (char*)pErrorBlob->GetBufferPointer());
	SafeRelease(pErrorBlob);

	hr = Graphics::GraphicsSystem::Get()->GetDevice()->CreatePixelShader
		(
			pShaderBlob->GetBufferPointer(),
			pShaderBlob->GetBufferSize(),
			nullptr,
			&Shader
			);

	SafeRelease(pShaderBlob);
}

void PixelShader::Terminate()
{
	SafeRelease(Shader);
}