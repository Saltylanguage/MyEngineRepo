#include "Precompiled.h"
#include "GraphicsSystem.h"
#include "Terrain.h"
#include "Camera.h"
#include "MeshBuilder.h"

using namespace Graphics;

Terrain::Terrain() {}
Terrain::~Terrain() {}

void Terrain::Initialize(const char* filename, uint32_t width, uint32_t length, float maxHeight)
{
	mCBuffer.Initialize();

	mVertexShader.Initialize(L"../Data/Shaders/Terrain.fx");
	mPixelShader.Initialize(L"../Data/Shaders/Terrain.fx");
	
	mHeightMap.GenerateFromRAW(filename, width, length);
	
	MeshBuilder::buildTerrain(mMesh, mHeightMap, width, length, maxHeight);
	mMeshBuffer.Initialize(mMesh.GetVertices(), mMesh.GetVertexCount(), mMesh.GetIndices(), mMesh.GetIndexCount());

	mSampler.Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);

	for (int i = 0; i < kMaxTerrainLayers; ++i)
	{
		mLayerTextures[i] = new Texture();
	}
}
void Terrain::Terminate()
{
	mCBuffer.Terminate();

	mVertexShader.Terminate();
	mPixelShader.Terminate();

	mHeightMap.Clear();
	mMesh.Terminate();
	mMeshBuffer.Terminate();

	for (uint32_t i = 0; i < kMaxTerrainLayers; ++i)
	{
		mLayerTextures[i]->Terminate();
		SafeDelete(mLayerTextures[i]);
	}
	mSampler.Terminate();
}

void Graphics::Terrain::SetCamera(Graphics::Camera& camera)
{
	mpCamera = &camera;
}

void Terrain::SetLayer(const wchar_t* filename, uint32_t layer, float minHeight, float MaxHeight, float frequency)
{
	ASSERT(layer < kMaxTerrainLayers, "[Terrain] Only Supports %d layers.", kMaxTerrainLayers);
	ASSERT(minHeight <= MaxHeight && frequency > 0.0f, "[Terrain] Invalid layer params.");


	//TODO Move this to Helper function somewhere and use char* everywhere else
	//e.g. Utils::CstringToWString(...)
	//wchar_t buffer[1024];
	//mbstowcs(buffer, filename, 1024);

	mLayerTextures[layer]->Initialize(filename);
	mLayerinfo[layer].x = minHeight;
	mLayerinfo[layer].y = MaxHeight;
	mLayerinfo[layer].z = frequency;

}

void Graphics::Terrain::SetLayer(Texture * texture, uint32_t layer, float minHeight, float maxHeight, float frequency)
{
	ASSERT(layer < kMaxTerrainLayers, "[Terrain] Only Supports %d layers.", kMaxTerrainLayers);
	ASSERT(minHeight <= maxHeight && frequency > 0.0f, "[Terrain] Invalid layer params.");


	//TODO Move this to Helper function somewhere and use char* everywhere else
	//e.g. Utils::CstringToWString(...)
	//wchar_t buffer[1024];
	//mbstowcs(buffer, filename, 1024);

	mLayerTextures[layer] = texture;
	
	mLayerinfo[layer].x = minHeight;
	mLayerinfo[layer].y = maxHeight;
	mLayerinfo[layer].z = frequency;

}

void Terrain::Render(const Camera& camera)
{
	Math::Matrix matView = camera.GetViewMatrix();
	Math::Matrix matProj = camera.GetProjectionMatrix();

	CBuffer cb;
	cb.WVP = Math::Matrix::Transpose(matView * matProj);
	for (uint32_t i = 0; i < kMaxTerrainLayers; ++i)
	{
		cb.layer[i] = Math::Vector4(mLayerinfo[i].x, mLayerinfo[i].y, mLayerinfo[i].z, 0.0f);
		mLayerTextures[i]->BindPS(i);
	}
	mCBuffer.Set(cb);
	mCBuffer.BindVS(0);
	mCBuffer.BindPS(0);

	mSampler.BindPS(0);

	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Draw(); 
}