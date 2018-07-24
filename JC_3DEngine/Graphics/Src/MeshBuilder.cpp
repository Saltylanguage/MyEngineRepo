#include "Precompiled.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "HeightMap.h"
#include "Bone.h"
#include "AnimationClip.h"
#include <inttypes.h>



using namespace Graphics;

namespace
{
	std::vector<Vertex> sVertices;
	std::vector<uint32_t> sIndices;
}

void MeshBuilder::StartMesh()
{
	sVertices.clear();
	sIndices.clear();
}

uint32_t MeshBuilder::AddVertexToMesh(const Vertex& vertex)
{
	sVertices.push_back(vertex);
	return sVertices.size() - 1;
}

void MeshBuilder::AddFaceToMesh(uint32_t a, uint32_t b, uint32_t c)
{
	sIndices.push_back(a);
	sIndices.push_back(b);
	sIndices.push_back(c);
}

void MeshBuilder::FinalizeMesh(Mesh& mesh)
{
	GenerateMesh(mesh, sVertices.data(), sVertices.size(), sIndices.data(), sIndices.size());
}

void MeshBuilder::GenerateMesh(Mesh& mesh, const Vertex* vertexData, uint32_t numVertices, const uint32_t* indexData, uint32_t numIndices)
{
	//free any existing data
	mesh.Terminate();

	//allocate memory
	Vertex* vertices = new Vertex[numVertices];
	uint32_t* indices = new uint32_t[numIndices];

	//copy data
	memcpy(vertices, vertexData, numVertices * sizeof(Vertex));
	memcpy(indices, indexData, numIndices * sizeof(uint32_t));

	//bind new data
	mesh.SetVertices(vertices);
	mesh.SetIndices(indices);
	mesh.SetVertexCount(numVertices);
	mesh.SetIndexCount(numIndices);

}

// =========================== Mesh Builders ================================

void Graphics::MeshBuilder::buildPlane(Mesh & mesh)
{
	Vertex PlaneVerts[] =
	{
		Vertex(Vector3(-1.0, 0.0f, -1.0f), Vector3(-1.0f, 0.0f, -1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)),
		Vertex(Vector3(1.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, -1.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)),

		Vertex(Vector3(1.0f, 0.0f, 1.0f), Vector3(1.0f, 0.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(1.0, 1.0)),
		Vertex(Vector3(-1.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 1.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0, 1.0))
	};

	uint32_t PlaneIndices[] =
	{
		0,3,2,
		0,2,1,

		2,3,0,
		1,2,0,

	};

	mesh.Initialize(PlaneVerts, 4, PlaneIndices, 12);
}

void Graphics::MeshBuilder::buildCube(Mesh & mesh)
{
	Vertex* CubeVerts = new Vertex[24]
	{
		//front face
		Vertex(Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4::Red(),   Vector2(0.0, 0.0)),
		Vertex(Vector3(1.0f, 1.0f, -1.0f),  Vector3(0.0f, 0.0f, -1.0f), Vector4::Green(), Vector2(1.0, 0.0)),
		Vertex(Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4::Blue(),  Vector2(1.0, 1.0)),
		Vertex(Vector3(-1.0f,-1.0f, -1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector4::Green(), Vector2(0.0, 1.0)),
		//back face			 											  
		Vertex(Vector3(1.0f, 1.0f, 1.0f),  Vector3(0.0f, 0.0f, 1.0f), Vector4::Red(),   Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f),  Vector3(0.0f, 0.0f, 1.0f), Vector4::Green(), Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f),  Vector3(0.0f, 0.0f, 1.0f), Vector4::Blue(),  Vector2(1.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f),   Vector3(0.0f, 0.0f, 1.0f), Vector4::Green(), Vector2(0.0, 1.0)),
		//left face									     
		Vertex(Vector3(-1.0f, 1.0f,-1.0f),  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f),  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f),  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(-1.0f,-1.0f,-1.0f),  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
		//right face								    
		Vertex(Vector3(1.0f, 1.0f, 1.0f),  Vector3(1.0f, 0.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(1.0f, 1.0f,-1.0f),   Vector3(1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(1.0f,-1.0f,-1.0f),   Vector3(1.0f, 0.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f),   Vector3(1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
	
		
		//top face									    
		Vertex(Vector3(1.0f, 1.0f, 1.0f),  Vector3(0.0f, 1.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f),  Vector3(0.0f, 1.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f,-1.0f),  Vector3(0.0f, 1.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f, 1.0f,-1.0f),   Vector3(0.0f, 1.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
		//bottom face								    
		Vertex(Vector3(1.0f,-1.0f,-1.0f),  Vector3(0.0f, -1.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f,-1.0f),  Vector3(0.0f, -1.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f),  Vector3(0.0f, -1.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f),   Vector3(0.0f, -1.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
	};

	uint32_t* CubeIndices = new uint32_t[36]
	{
		//FRONT FACE
		0,1,2,
		0,2,3,

		//BACK FACE
		4,5,6,
		7,4,6,

		//LEFT FACE
		10,9,8,
		11,10,8,

		//RIGHT FACE
		14,13,12,
		15,14,12,

		//TOP FACE
		18,17,16,
		19,18,16,

		//BOTTOM FACE
		22,21,20,
		23,22,20
	};

	mesh.Initialize(CubeVerts, 24, CubeIndices, 36);
}

void Graphics::MeshBuilder::buildSkyBox(Mesh & mesh, float scale)
{
	Vertex* SkyBoxVerts = new Vertex[24]
	{
		//front face
		Vertex(Vector3(-1.0f, 1.0f, -1.0f) * scale,  Vector3(0.0f, 0.0f, -1.0f),  Vector4::Red(),   Vector2(0.0, 0.0)),
		Vertex(Vector3(1.0f, 1.0f, -1.0f) * scale,   Vector3(0.0f, 0.0f, -1.0f),   Vector4::Green(), Vector2(1.0, 0.0)),
		Vertex(Vector3(1.0f, -1.0f, -1.0f) * scale,  Vector3(0.0f, 0.0f, -1.0f),   Vector4::Blue(),  Vector2(1.0, 1.0)),
		Vertex(Vector3(-1.0f,-1.0f, -1.0f) * scale,  Vector3(0.0f, 0.0f, -1.0f),   Vector4::Green(), Vector2(0.0, 1.0)),
		//back face			 											  
		Vertex(Vector3(1.0f, 1.0f, 1.0f) * scale,   Vector3(0.0f, 0.0f, 1.0f), Vector4::Red(),   Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f) * scale,   Vector3(0.0f, 0.0f, 1.0f), Vector4::Green(), Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f) * scale,   Vector3(0.0f, 0.0f, 1.0f), Vector4::Blue(),  Vector2(1.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f) * scale,   Vector3(0.0f, 0.0f, 1.0f), Vector4::Green(), Vector2(0.0, 1.0)),
		//left face								    
		Vertex(Vector3(-1.0f, 1.0f,-1.0f) * scale,  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f) * scale,  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f) * scale,  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(-1.0f,-1.0f,-1.0f) * scale,  Vector3(-1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
		//right face								    
		Vertex(Vector3(1.0f, 1.0f, 1.0f) * scale,  Vector3(1.0f, 0.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(1.0f, 1.0f,-1.0f) * scale,  Vector3(1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(1.0f,-1.0f,-1.0f) * scale,   Vector3(1.0f, 0.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f) * scale,  Vector3(1.0f, 0.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
		//top face									 
		Vertex(Vector3(1.0f, 1.0f, 1.0f) * scale,  Vector3(0.0f, 1.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f, 1.0f) * scale,  Vector3(0.0f, 1.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f, 1.0f,-1.0f) * scale,  Vector3(0.0f, 1.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f, 1.0f,-1.0f) * scale,   Vector3(0.0f, 1.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
		//bottom face								 
		Vertex(Vector3(1.0f,-1.0f,-1.0f) * scale,  Vector3(0.0f, -1.0f, 0.0f), Vector4::Red(),   Vector2(1.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f,-1.0f) * scale,  Vector3(0.0f, -1.0f, 0.0f), Vector4::Green(), Vector2(0.0, 0.0)),
		Vertex(Vector3(-1.0f,-1.0f, 1.0f) * scale,  Vector3(0.0f, -1.0f, 0.0f), Vector4::Blue(),  Vector2(0.0, 1.0)),
		Vertex(Vector3(1.0f,-1.0f, 1.0f) * scale,   Vector3(0.0f, -1.0f, 0.0f), Vector4::Green(), Vector2(1.0, 1.0)),
	};

	uint32_t* SkyBoxIndices = new uint32_t[36]
	{
		//FRONT FACE		
		2,1,0,
		3,2,0,

		//BACK FACE		
		6,5,4,
		6,4,7,

		//LEFT FACE		
		8,9,10,
		8,10,11,

		//RIGHT FACE	
		12,13,14,
		12,14,15,

		//TOP FACE		
		16,17,18,
		16,18,19,

		//BOTTOM FACE		
		20,21,22,
		20,22,23

	};

	mesh.Initialize(SkyBoxVerts, 24, SkyBoxIndices, 36);
}

void Graphics::MeshBuilder::buildIcosahedron(Mesh & mesh)
{
	Vertex IcoVerts[12]
	{
		//FRONT

		Vertex(Vector3(-0.26286500f, 0.0000000f, 0.42532500f),
			   Vector3::Normalize(Vector3(-0.26286500f, 0.0000000f, 0.42532500f)),
			   Vector4::Red(),
			   Vector2::CalculateUV(Vector3(-0.26286500f, 0.0000000f, 0.42532500f))),

		Vertex(Vector3(0.26286500f, 0.0000000f, 0.42532500f),
			   Vector3::Normalize(Vector3(0.26286500f, 0.0000000f, 0.42532500f)),
			   Vector4::Green(),
			   Vector2::CalculateUV(Vector3(0.26286500f, 0.0000000f, 0.42532500f))),

		Vertex(Vector3(-0.26286500f, 0.0000000f, -0.42532500f),
			   Vector3::Normalize(Vector3(-0.26286500f, 0.0000000f, -0.42532500f)),
			   Vector4::Blue(),
			   Vector2::CalculateUV(Vector3(-0.26286500f, 0.0000000f, -0.42532500f))),

		Vertex(Vector3(0.26286500f, 0.0000000f, -0.42532500f),
			   Vector3::Normalize(Vector3(0.26286500f, 0.0000000f, -0.42532500f)),
			   Vector4::Red(),
			   Vector2::CalculateUV(Vector3(0.26286500f, 0.0000000f, -0.42532500f))),


		Vertex(Vector3(0.0000000f, 0.42532500f, 0.26286500f),
			   Vector3::Normalize(Vector3(0.0000000f, 0.42532500f, 0.26286500f)),
			   Vector4::Green(),
			   Vector2::CalculateUV(Vector3(0.0000000f, 0.42532500f, 0.26286500f))),

		Vertex(Vector3(0.0000000f, 0.42532500f, -0.26286500f),
			   Vector3::Normalize(Vector3(0.0000000f, 0.42532500f, -0.26286500f)),
			   Vector4::Blue(),
			   Vector2::CalculateUV(Vector3(0.0000000f, 0.42532500f, -0.26286500f))),

		//BACK
 Vertex(Vector3(0.0000000f, -0.42532500f, 0.26286500f),
	   Vector3::Normalize(Vector3(0.0000000f, -0.42532500f, 0.26286500f)),
	   Vector4::Red(),
	   Vector2::CalculateUV(Vector3(0.0000000f, -0.42532500f, 0.26286500f))),


Vertex(Vector3(0.0000000f, -0.42532500f, -0.26286500f),
	  Vector3::Normalize(Vector3(0.0000000f, -0.42532500f, -0.26286500f)),
	  Vector4::Green(),
	  Vector2::CalculateUV(Vector3(0.0000000f, -0.42532500f, -0.26286500f))),

Vertex(Vector3(0.42532500f, 0.26286500f, 0.0000000f),
	  Vector3::Normalize(Vector3(0.42532500f, 0.26286500f, 0.0000000f)),
	  Vector4::Blue(),
	  Vector2::CalculateUV(Vector3(0.42532500f, 0.26286500f, 0.0000000f))),

Vertex(Vector3(-0.42532500f, 0.26286500f, 0.0000000f),
	  Vector3::Normalize(Vector3(-0.42532500f, 0.26286500f, 0.0000000f)),
	  Vector4::Red(),
	  Vector2::CalculateUV(Vector3(-0.42532500f, 0.26286500f, 0.0000000f))),

Vertex(Vector3(0.42532500f, -0.26286500f, 0.0000000f),
	  Vector3::Normalize(Vector3(0.42532500f, -0.26286500f, 0.0000000f)),
	  Vector4::Green(),
	  Vector2::CalculateUV(Vector3(0.42532500f, -0.26286500f, 0.0000000f))),

Vertex(Vector3(-0.42532500f, -0.26286500f, 0.0000000f),
	  Vector3::Normalize(Vector3(-0.42532500f, -0.26286500f, 0.0000000f)),
	  Vector4::Blue(),
	  Vector2::CalculateUV(Vector3(-0.42532500f, -0.26286500f, 0.0000000f))),
	};

	uint32_t IcoIndices[60]
	{
		0,6,1,
		0,11,6,

		1,4,0,
		1,8,4,
		1,10,8,

		2,5,3,
		2,9,5,
		2,11,9,

		3,7,2,
		3,10,7,

		4,8,5,
		4,9,0,

		5,8,3,
		5,9,4,

		6,10,1,
		6,11,7,

		7,10,6,
		7,11,2,

		8,10,3,

		9,11,0,
	};

	mesh.Initialize(IcoVerts, 12, IcoIndices, 60);
}

void MeshBuilder::buildIcoSphere(Mesh& mesh, uint32_t refineLevel)
{

	struct TriIndices
	{
		TriIndices() { v1 = 0; v2 = 0; v3 = 0; }
		TriIndices(uint32_t a, uint32_t b, uint32_t c) : v1(a), v2(b), v3(c) {}
		uint32_t v1;
		uint32_t v2;
		uint32_t v3;
	};

	std::unordered_map<long, uint32_t> middlePointCache;
	std::vector<Vertex> vertices;
	uint32_t indexCount = 0;

	AddVertex(Vector3(-0.26286500f, 0.0000000f, 0.42532500f), vertices, indexCount);
	AddVertex(Vector3(0.26286500f, 0.0000000f, 0.42532500f), vertices, indexCount);
	AddVertex(Vector3(-0.26286500f, 0.0000000f, -0.42532500f), vertices, indexCount);
	AddVertex(Vector3(0.26286500f, 0.0000000f, -0.42532500f), vertices, indexCount);
	AddVertex(Vector3(0.0000000f, 0.42532500f, 0.26286500f), vertices, indexCount);
	AddVertex(Vector3(0.0000000f, 0.42532500f, -0.26286500f), vertices, indexCount);

	AddVertex(Vector3(0.0000000f, -0.42532500f, 0.26286500f), vertices, indexCount);
	AddVertex(Vector3(0.0000000f, -0.42532500f, -0.26286500f), vertices, indexCount);
	AddVertex(Vector3(0.42532500f, 0.26286500f, 0.0000000f), vertices, indexCount);
	AddVertex(Vector3(-0.42532500f, 0.26286500f, 0.0000000f), vertices, indexCount);
	AddVertex(Vector3(0.42532500f, -0.26286500f, 0.0000000f), vertices, indexCount);
	AddVertex(Vector3(-0.42532500f, -0.26286500f, 0.0000000f), vertices, indexCount);

	std::vector<TriIndices> Faces =
	{
		{ 0,6,1 },
		{ 0,11,6 },
		{ 1,4,0 },
		{ 1,8,4 },
		{ 1,10,8 },

		{ 2,5,3 },
		{ 2,9,5 },
		{ 2,11,9 },
		{ 3,7,2 },
		{ 3,10,7 },

		{ 4,8,5, },
		{ 4,9,0, },
		{ 5,8,3, },
		{ 5,9,4, },
		{ 6,10,1 },

		{ 6,11,7 },
		{ 7,10,6 },
		{ 7,11,2 },
		{ 8,10,3 },
		{ 9,11,0 }
	};

	for (size_t i = 0; i < refineLevel; i++)
	{
		std::vector<TriIndices> newFaces;

		for (uint32_t currentVert = 0; currentVert < Faces.size(); currentVert++)
		{
			uint32_t a = GetMidPoint(Faces[currentVert].v1, Faces[currentVert].v2, middlePointCache, vertices, indexCount);
			uint32_t b = GetMidPoint(Faces[currentVert].v2, Faces[currentVert].v3, middlePointCache, vertices, indexCount);
			uint32_t c = GetMidPoint(Faces[currentVert].v3, Faces[currentVert].v1, middlePointCache, vertices, indexCount);

			newFaces.push_back({ Faces[currentVert].v1, a,c });
			newFaces.push_back({ Faces[currentVert].v2, b,a });
			newFaces.push_back({ Faces[currentVert].v3, c,b });
			newFaces.push_back({ a, b, c });
		}
		Faces = newFaces;
	}

	uint32_t* indices = new uint32_t[Faces.size() * 3];

	for (uint32_t i = 2, currentFace = 0; i < Faces.size() * 3; i = i + 3, currentFace++)
	{
		indices[i - 2] = Faces[currentFace].v1;
		indices[i - 1] = Faces[currentFace].v2;
		indices[i] = Faces[currentFace].v3;
	}

	Vertex* verticesArray = new Vertex[vertices.size()];

	for (uint32_t i = 0; i < vertices.size(); i++)
	{
		verticesArray[i] = vertices[i];
	}

	mesh.Initialize(verticesArray, vertices.size(), indices, Faces.size() * 3);
}

uint32_t MeshBuilder::AddVertex(Vector3 point, std::vector<Vertex>& verts, uint32_t& indexCount)
{

	Vector3 normal = Vector3::Normalize(point);

	Vector3 tangent = Vector3(-normal.z, 0, normal.x);
	tangent = Vector3::Normalize(tangent);

	Vector3 binormal = tangent.Cross(normal);
	binormal = Vector3::Normalize(binormal);

	verts.push_back
		(
			Vertex(normal,
				normal,
				Vector4::Red(),
				Vector2::CalculateUV(point),
				tangent,
				binormal)
			);

	return indexCount++;
}

uint32_t MeshBuilder::GetMidPoint(
	uint32_t point1, uint32_t point2,
	std::unordered_map<long, uint32_t> midPointCache,
	std::vector<Vertex>& verts, uint32_t& indexCount
	)
{
	uint32_t smallerIndex = (point1 < point2) ? point1 : point2;
	uint32_t largerIndex = (point1 == smallerIndex) ? point2 : point1;
	long key = (smallerIndex << 16) + largerIndex;

	if (midPointCache.find(key) != midPointCache.end()) // if the point is already there
	{
		return midPointCache.at(key);
	}

	Vector3 p1 = verts[point1].getPosition();
	Vector3 p2 = verts[point2].getPosition();
	Vector3 middle{ (p1.x + p2.x) / 2.0f, (p1.y + p2.y) / 2.0f, (p1.z + p2.z) / 2.0f, };

	uint32_t temp = MeshBuilder::AddVertex(middle, verts, indexCount);
	midPointCache.insert({ key, temp });
	return temp;
}

void MeshBuilder::buildTerrain(Mesh& mesh, const HeightMap& heightMap, uint32_t width, uint32_t length, float maxHeight)
{
	uint32_t vertCounts = width * length;
	uint32_t indCounts = (width - 1) * (length - 1) * 6;

	Vertex* TerrainVerts = new Vertex[vertCounts];
	uint32_t* TerrainIndices = new uint32_t[indCounts];

	float minX = -(float)width / 2.0f;
	float minZ = -(float)length / 2.0f;

	for (uint32_t row = 0; row < length; ++row)
	{
		for (uint32_t col = 0; col < width; ++col)
		{
			TerrainVerts[col + (row * width)] = Vertex
				(Vector3(minX + col, heightMap.GetHeight(col, row) * maxHeight, -(minZ + row)), // pos
					Vector3::YAxis(),															 // norm
					Vector4::Black(),															 // color
					Vector2(col / (float)(width - 1), row / (float)(length - 1)));							 // uv
		}
	}



	for (uint32_t row = 0; row < length - 1; ++row)
	{
		for (uint32_t col = 0; col < width - 1; ++col)
		{
			TerrainIndices[(row *(width - 1) + col) * 6 + 0] = row * length + col;
			TerrainIndices[(row *(width - 1) + col) * 6 + 1] = row * length + col + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 2] = row * length + col + length + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 3] = row * length + col;
			TerrainIndices[(row *(width - 1) + col) * 6 + 4] = row * length + col + length + 1;
			TerrainIndices[(row *(width - 1) + col) * 6 + 5] = row * length + col + length;
		}
	}

	mesh.Initialize(TerrainVerts, vertCounts, TerrainIndices, indCounts);

}

// =========================== END OF Mesh Builders ================================


typedef std::vector<Mesh> MeshList;
typedef std::vector<std::string> TextureList;

void MeshBuilder::AssignBonePointers(Bone* bArray, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (bArray[i].parentIndex != -1)
		{
			bArray[i].parent = &bArray[bArray[i].parentIndex];
		}
	}
}

bool MeshBuilder::LoadModel(const char* filename, MeshList& meshes, TextureList& textures)
{
	FILE* modelFile;
	fopen_s(&modelFile, filename, "r");

	uint32_t textureCount;
	uint32_t meshCount;
	uint32_t vertCount;
	uint32_t indexCount;
	uint32_t numBones;
	uint32_t numAnims;

	fscanf(modelFile, "MeshCount = %d\n", &meshCount);
	fscanf(modelFile, "TextureCount = %d\n", &textureCount);
	fscanf(modelFile, "BoneCount: %d\n", &numBones);
	fscanf(modelFile, "AnimationCount: %d\n", &numAnims);
	fscanf(modelFile, "VertexCount = %d\n", &vertCount);
	fscanf(modelFile, "IndexCount = %d\n", &indexCount);

	meshes.resize(meshCount);
	textures.resize(textureCount);

	for (uint32_t meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{

		Graphics::Vertex* vertArray = new Graphics::Vertex[vertCount];

		for (uint32_t vertIndex = 0; vertIndex < vertCount; ++vertIndex)
		{
			fscanf(modelFile, "Position: %f %f %f\n", &vertArray[vertIndex].POS.x, &vertArray[vertIndex].POS.y, &vertArray[vertIndex].POS.z);
			fscanf(modelFile, "Normal: %f %f %f\n", &vertArray[vertIndex].NORM.x, &vertArray[vertIndex].NORM.y, &vertArray[vertIndex].NORM.z);
			fscanf(modelFile, "TextCoord: %f %f\n", &vertArray[vertIndex].UV.x, &vertArray[vertIndex].UV.y);
		}

		uint32_t * indexArray = new uint32_t[indexCount];
		for (uint32_t index = 0; index < indexCount; ++index)
		{
			fscanf(modelFile, "Vertex Index: %d\n", &indexArray[index]);
		}
		meshes[meshIndex] = new Mesh();
		meshes[meshIndex]->Initialize(vertArray, vertCount, indexArray, indexCount);
	}


	for (uint32_t textureIndex = 0; textureIndex < textureCount; textureIndex++)
	{
		char buffer[1024];
		fscanf(modelFile, "FileName: %s\n", &buffer);
		textures[textureIndex] = buffer;
	}

	Bone* boneArray = new Bone[numBones];
	std::string* nameArray = new std::string[numBones];
	uint32_t* parentArray = new uint32_t[numBones];
	uint32_t* childCountArray = new uint32_t[numBones];
	AnimationClip* animationArray = new AnimationClip[numAnims];



	for (uint32_t boneIndex = 0; boneIndex < numBones; boneIndex++)
	{		
		char buffer[1024];
		fscanf(modelFile, "Name: %s\n", buffer);	
		boneArray[boneIndex].mName = buffer;
		fscanf(modelFile, "Parent: %d\n", &boneArray[boneIndex].parentIndex);
	
		uint32_t childCount; //TODO take away this 0
		fscanf(modelFile, "Children: %d\n", &childCount);

		boneArray[boneIndex].childrenIndex.resize(childCount);

		for (uint32_t childIndex = 0; childIndex < childCount; childIndex++)
		{
			fscanf(modelFile, "%d ", &boneArray[boneIndex].childrenIndex[childIndex]);
		}
		fscanf(modelFile, "Transform: %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			&boneArray[boneIndex].transform.matrix[0],  &boneArray[boneIndex].transform.matrix[1],   &boneArray[boneIndex].transform.matrix[2],
			&boneArray[boneIndex].transform.matrix[3],  &boneArray[boneIndex].transform.matrix[4],   &boneArray[boneIndex].transform.matrix[5],
			&boneArray[boneIndex].transform.matrix[6],  &boneArray[boneIndex].transform.matrix[7],   &boneArray[boneIndex].transform.matrix[8],
			&boneArray[boneIndex].transform.matrix[9],  &boneArray[boneIndex].transform.matrix[10],  &boneArray[boneIndex].transform.matrix[11],
			&boneArray[boneIndex].transform.matrix[12], &boneArray[boneIndex].transform.matrix[13], &boneArray[boneIndex].transform.matrix[14],
			&boneArray[boneIndex].transform.matrix[15]
			);	
		fscanf(modelFile, "Bone Index: %d\n", &boneArray[boneIndex].index);
	}


	
	
	for (uint32_t animIndex = 0; animIndex < numAnims; animIndex++)
	{

		char buffer[1024];
		fscanf(modelFile, "Name: %s\n", buffer);
		animationArray[animIndex].mName = buffer;
		fscanf(modelFile, "Duration: %f\n", &animationArray[animIndex].duration);
		fscanf(modelFile, "TicksPerSecond: %f\n", &animationArray[animIndex].ticksPerSecond);
		int numBoneAnims = 0;
		fscanf(modelFile, "BoneAnimations: %d\n", &numBoneAnims);	
		
		animationArray[animIndex].boneAnimations.resize(numBoneAnims);
		for (int boneAnimIndex = 0; boneAnimIndex < numBoneAnims; boneAnimIndex++)
		{

			animationArray[animIndex].boneAnimations[boneAnimIndex] = new BoneAnimation();
			
			fscanf(modelFile, "Bone Index: %d\n", &animationArray[animIndex].boneAnimations[boneAnimIndex]->boneIndex);
			fscanf(modelFile, "Keyframes: %d\n", &animationArray[animIndex].keyFrameCount);

			std::vector<KeyFrame>& temp = animationArray[animIndex].boneAnimations[boneAnimIndex]->keyframes;
			temp.resize(animationArray[animIndex].keyFrameCount);
			for (uint32_t keyframeIndex = 0; keyframeIndex < animationArray[animIndex].keyFrameCount; keyframeIndex++)
			{
				fscanf(modelFile, "Keyframe %d: %f %f %f %f %f %f %f %f %f %f %f\n",

					&keyframeIndex,
					&temp[keyframeIndex].position.x,
					&temp[keyframeIndex].position.y,
					&temp[keyframeIndex].position.z,
						 
					&temp[keyframeIndex].rotation.x,
					&temp[keyframeIndex].rotation.y,
					&temp[keyframeIndex].rotation.z,
					&temp[keyframeIndex].rotation.w,
						 
					&temp[keyframeIndex].scale.x,
					&temp[keyframeIndex].scale.y,
					&temp[keyframeIndex].scale.z,

					&temp[keyframeIndex].time
					);
			}
		}
		AssignBonePointers(boneArray, numBones);

		return true;
	}
	return false;
}

//TODO List

// 1 - Reassign bone pointers to the corresponding indices (this is in meshbuilder)
// 2 - Build an array of matrices (each bone's transform matrix) (this is also in meshbuilder but store it in model class?)
// 3 - Use SimpleDraw to go through the array and draw the skeleton (inside GameApp)


/*
Normal Mapping Requirements:
1) normal  - the vector pointing straight out from a surface (normal = (2* color) - 1)
(orthagonal to any coplanar vector for a flat surface OR orthagonal to the tangent of a NON-flat surface)
2) Tangent - a vector which is coplanar to the reference point. it is perpendicular to the normal of the reference point
3) BiNormal

Think of it this way:
Red is Tangent and faces right
Green is Bitangent and faces up
Blue is Normal and faces out

using 2 edges of our triangle:     edge1 and edge2
and   2 UV positions in triangle:  UV1   and UV2
Tangent:  T
Binormal: B
then:
edge1 = UV1.x * T + UV1.y * B
edge2 = UV2.x * T + UV2.y * B

Solve this sytem for T and B to get TBN matrix

Transpose of TBN Matrix = TangentSpace

To find T B and N:
1) N = (color * 2) - 1
2) T =
3) B = N.cross(T);


*/

//void ComputeTangentSpace
//(
//	std::vector<MathLibrary::Vector3> & vertexList,
//	std::vector<MathLibrary::Vector2>& uvList,
//	std::vector<MathLibrary::Vector3>& normalList,
//	std::vector<MathLibrary::Vector3>& tangentList,
//	std::vector<MathLibrary::Vector3>& binormalList
//	)
//{
//	for (int i = 0; i < vertexList.size(); i++)
//	{
//
//		MathLibrary::Vector3 & v0 = vertexList[i];
//		MathLibrary::Vector3 & v1 = vertexList[i + 1];
//		MathLibrary::Vector3 & v2 = vertexList[i + 2];
//
//		MathLibrary::Vector2 & uv0 = uvList[i];
//		MathLibrary::Vector2 & uv1 = uvList[i + 1];
//		MathLibrary::Vector2 & uv2 = uvList[i + 2];
//
//		//find edges
//		MathLibrary::Vector3 edge1 = v1 - v0;
//		MathLibrary::Vector3 edge2= v2 - v0;
//
//		MathLibrary::Vector2 deltaUV1 = uv1 - uv0;
//		MathLibrary::Vector2 deltaUV2 = uv2 - uv0;
//	}
//}
