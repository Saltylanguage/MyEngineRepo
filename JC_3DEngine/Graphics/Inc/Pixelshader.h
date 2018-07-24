#pragma once


namespace Graphics
{
	class PixelShader
	{
	public:

		PixelShader() : Shader(nullptr) {}
		~PixelShader() {}
	
		ID3D11PixelShader* Shader;

		void Bind();
		void Initialize(const wchar_t* fileName);
		void Terminate();

	};
}
