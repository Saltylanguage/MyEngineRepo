#pragma once

namespace Graphics
{
	
	class ScreenMeshBuffer
	{

		NONCOPYABLE(ScreenMeshBuffer);
		
	public:
		ScreenMeshBuffer() {}
		~ScreenMeshBuffer() {}

		void Initialize();
		void Terminate();

		void Render();

	private:

		ID3D11Buffer* mVertexBuffer;

	};

}