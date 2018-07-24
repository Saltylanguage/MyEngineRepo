#pragma once

namespace Graphics
{
	class RenderTarget
	{
		NONCOPYABLE(RenderTarget);
	public:
		RenderTarget();
		~RenderTarget();
		enum Format
		{
			RGBA_U8,
			R_F16,
			RGBA_F16
		};


		void Initialize(uint32_t width, uint32_t height, Format format);
		void Terminate();

		void BeginRender();
		void EndRender();

		void BindPS(uint32_t index);
		void UnbindPS(uint32_t index);

	private:
		ID3D11ShaderResourceView* mShaderResourceView;
		ID3D11RenderTargetView* mRenderTargetView;
		ID3D11DepthStencilView* mDepthStencilView;
		D3D11_VIEWPORT mViewport;


	};
}


