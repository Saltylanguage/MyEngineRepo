#pragma once

namespace Graphics
{
	class VertexShader
	{
	public:
		VertexShader() :Shader(nullptr), mInputLayout(nullptr) {};
		~VertexShader() {}

		//ID3D11DeviceContext* context;
		ID3D11VertexShader* Shader;
		ID3D11InputLayout* mInputLayout;

	public:

		void Bind();
		void Initialize(const wchar_t* fileName);
		void InitializePositionUV(const wchar_t* filename);
		void Terminate();

	};
}