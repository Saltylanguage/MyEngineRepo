#include "Precompiled.h"
#include "MeshBuffer.h"
#include "Vertex.h"
#include "GraphicsSystem.h"
#include "HeightMap.h"

using namespace Graphics;


void MeshBuffer::Initialize(const Vertex * vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount)
{
	//create and build vertex buffer
	mIndexCount = indexCount;

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mVertexBuffer);

	//create and fill index buffer
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(uint32_t) * indexCount;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mIndexBuffer);
}

void MeshBuffer::Draw()
{
	//bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	//set index buffer
	context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//draw mesh
	context->DrawIndexed(mIndexCount, 0, 0);
}


//hookup simple draw
//finish HeightMapLoad
//finish CreateTerrain (meshBuilder)
