#pragma once
#include "Vertex.h"

namespace Graphics
{
	
	class Mesh
	{
		friend class MeshBuilder;

	private:
		//NONCOPYABLE(Mesh);
	public:
		Mesh() : vertices(nullptr), vertexCount(0), indices(nullptr), indexCount(0)
		{}

		Vertex* vertices;
		uint32_t vertexCount;
		uint32_t* indices;
		uint32_t indexCount;

	public:
		void SetVertices(Vertex* verts) { vertices = verts; }
		void SetVertexCount(uint32_t vertCount) { vertexCount = vertCount; }
		void SetIndices(uint32_t* inds) { indices = inds; }
		void SetIndexCount(uint32_t indCount) { indexCount = indCount; }

		Vertex GetVertex(uint32_t vertexIndex) { return vertices[vertexIndex]; }
		Vertex* GetVertices() { return vertices; }
		uint32_t GetVertexCount() { return vertexCount; }
		uint32_t* GetIndices() { return indices; }
		uint32_t GetIndexCount() { return indexCount; }

		void Initialize( Vertex* verts, uint32_t vertCount, uint32_t* inds, uint32_t indCount);

		void TranslateMesh(Vector3 newPos);

		void Terminate();

	};

}