#pragma once

namespace Graphics
{
	class DepthStencilState
	{
	public:
		DepthStencilState();
		~DepthStencilState();
		
		void Initialize();
		void Terminate();

		void EnableTesting(bool enabled);

	private:
		
		ID3D11DepthStencilState* mDepthStencilState;
		
	};

}