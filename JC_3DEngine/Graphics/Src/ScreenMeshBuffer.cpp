#include "Precompiled.h"
#include "ScreenMeshBuffer.h"
#include "Vertex.h"
#include "HeightMap.h"
#include "GraphicsSystem.h"

using namespace Graphics;


void ScreenMeshBuffer::Initialize()
{
	//create and build vertex buffer
	
	struct ScreenVertex
	{
		float x, y, z, u, v;		
	};

	D3D11_BUFFER_DESC bd = {};
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	Vertex vertices[4];
	vertices[0].POS = Vector3(-1.0f, -1.0f, 0.0f); // bottom left
	vertices[1].POS = Vector3(-1.0f, 1.0f, 0.0f);  // top left
	vertices[2].POS = Vector3(1.0f, -1.0f, 0.0f); // bottom right
	vertices[3].POS = Vector3(1.0f, 1.0f, 0.0f); // top right

	vertices[0].UV = Vector2(0.0f, 1.0f);
	vertices[1].UV = Vector2(0.0f, 0.0f);
	vertices[2].UV = Vector2(1.0f, 1.0f);
	vertices[3].UV = Vector2(1.0f, 0.0f);
	
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices;

	Graphics::GraphicsSystem::Get()->GetDevice()->CreateBuffer(&bd, &initData, &mVertexBuffer);
}

void Graphics::ScreenMeshBuffer::Terminate()
{
	SafeRelease(mVertexBuffer);
}

void ScreenMeshBuffer::Render()
{
	//bind the input layout, vertex shader, and pixel shader
	ID3D11DeviceContext* context = Graphics::GraphicsSystem::Get()->GetContext();

	//set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	
	//set primitieve topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//draw mesh
	context->Draw(4, 0);
}


//hookup simple draw
//finish HeightMapLoad
//finish CreateTerrain (meshBuilder)
