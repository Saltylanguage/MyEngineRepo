
#include "Precompiled.h"
#include <Mesh.h>
#include <Vertex.h>
#include "GraphicsSystem.h"

using namespace Graphics;

void Graphics::Mesh::Initialize( Vertex* verts, uint32_t vertCount, uint32_t * inds, uint32_t indCount)
{
	vertices = verts;
	indices = inds;
	vertexCount = vertCount;
	indexCount = indCount;

}

void Graphics::Mesh::TranslateMesh(Vector3 newPos)
{
	for (uint32_t i = 0; i < vertexCount; i++)
	{
		vertices[i].setPosition(vertices->getPosition() + newPos);
	}
}

void Mesh::Terminate()
{
	SafeDeleteArrays(vertices);
	SafeDeleteArrays(indices);
}
