#pragma once


#include "ConstantBuffer.h"
#include "Heightmap.h"
#include "Mesh.h"
#include "MeshBuffer.h"
#include "Pixelshader.h"
#include "Sampler.h"
#include "Texture.h"
#include "VertexShader.h"
#include "Camera.h"

using namespace Math;

namespace Graphics
{
	class Camera;

	class Terrain
	{
	public:
		static Terrain* main;

		Terrain();
		~Terrain();

		void Initialize(const char* fileName, uint32_t width, uint32_t length, float maxHeight);
		void Terminate();

		void SetCamera(Camera& camera);
		void SetLayer(const wchar_t* filename, uint32_t layer, float minHeight, float maxHeight, float frequency);
		void SetLayer(Texture* filename, uint32_t layer, float minHeight, float maxHeight, float frequency);

		void Update();

		HeightMap& GetHeightMap() { return mHeightMap; }

		void Render(const Camera& camera);

	private:
		NONCOPYABLE(Terrain);
		static const uint32_t  kMaxTerrainLayers = 4;

		struct CBuffer
		{
			Matrix WVP;
			Vector4 layer[kMaxTerrainLayers];
		};

		//GraphicsSystem* mpGraphicsSystem;
		Camera* mpCamera;

		TypedConstantBuffer<CBuffer> mCBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		HeightMap mHeightMap;
		Mesh mMesh;
		MeshBuffer mMeshBuffer;

		Texture* mLayerTextures[kMaxTerrainLayers];
		Vector3 mLayerinfo[kMaxTerrainLayers];

		Sampler mSampler;

	};
}