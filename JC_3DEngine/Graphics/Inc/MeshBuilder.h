#pragma once
#include "Mesh.h"
#include <vector>
#include <unordered_map>


namespace Graphics
{
struct Bone;
	class HeightMap;
	class MeshBuilder
	{			
	public:
		static void StartMesh();
		static uint32_t AddVertexToMesh(const Vertex& vertex);
		static void AddFaceToMesh(uint32_t a, uint32_t b, uint32_t c);
		static void FinalizeMesh(Mesh& mesh);
		static void GenerateMesh(Mesh& mesh, const Vertex* vertexData, uint32_t numberVertices, const uint32_t* indexData, uint32_t numIndices);

		static void buildCube(Mesh& mesh);
		static void buildSkyBox(Mesh& mesh, float scale);
		static void buildPlane(Mesh& mesh);
		static void buildTerrain(Mesh& mesh, const HeightMap& heightMap, uint32_t width, uint32_t length, float maxHeight );		
		static void buildIcosahedron(Mesh& mesh);		
		static void buildIcoSphere(Mesh& mesh, uint32_t refineLevel);

		//Icosphere Helpers
			static uint32_t GetMidPoint(
										uint32_t point1, uint32_t point2,
										std::unordered_map<long, uint32_t> midPointCache,
										std::vector<Vertex>& verts, uint32_t& indexCount
										);
		static uint32_t AddVertex(Vector3 point, std::vector<Vertex>& verts, uint32_t& indexCount);
		static void RefineTriangles(Mesh& mesh, uint32_t refineLevel);


		typedef std::vector<Mesh*> MeshList;
		typedef std::vector<std::string> TextureList;

		static bool LoadModel(const char* filename, MeshList& meshes, TextureList& textures);

		static void AssignBonePointers(Bone* bArray, int count);

		//static MathLibrary::Vector3 GetMidPoint(MathLibrary::Vector3 point1, MathLibrary::Vector3 point2);
	
	};
}