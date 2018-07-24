#pragma once

namespace Graphics
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void Initialize(const wchar_t* filename);
		void Terminate();

		void BindPS(uint32_t slot);
		void BindVS(uint32_t slot);
		void Initialize(const void * data, uint32_t width, uint32_t height);

	private:
		friend class SpriteRenderer;

		ID3D11ShaderResourceView* mpTexture;
		
	};

}