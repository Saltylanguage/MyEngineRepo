#pragma once


namespace Graphics
{
	class GeometryShader
	{
	public:

		GeometryShader() : Shader(nullptr) {}
		~GeometryShader() { ASSERT(Shader == nullptr, "[GeometryShader] Terminate was not called.") }

	
		ID3D11GeometryShader* Shader;

		void Bind();
		void Initialize(const wchar_t* fileName);
		void Terminate();

	};
}
