#pragma once
#include <Core\Inc\DeleteUtil.h>


namespace Graphics
{
	class Vertex;
	class MeshBuffer
	{
	private:
		NONCOPYABLE(MeshBuffer);
		
	public:

		MeshBuffer() : mVertexBuffer(nullptr), mIndexBuffer(nullptr), mIndexCount(0) {}

		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		uint32_t mIndexCount;
		
		

	public:
		void Initialize(const Vertex* vertices, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount);
		void Terminate()
		{
			SafeRelease(mVertexBuffer);
			SafeRelease(mIndexBuffer);
		};

		void Draw();
	};

}