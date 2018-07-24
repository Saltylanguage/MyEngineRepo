#include "Precompiled.h"
#include "Vertex.h"

using namespace Graphics;

Vertex::Vertex() : POS(0, 0, 0), NORM(0, 0, 0), COLOR(0, 0, 0, 0), UV(0, 0), TANGENT(0, 0, 0), BINORMAL(0, 0, 0)
{
}

Graphics::Vertex::Vertex(Vector3 position, Vector3 norm, Vector4 color, Vector2 uv)
	: POS(position), NORM(norm), COLOR(color), UV(uv), TANGENT(0, 0, 0), BINORMAL(0, 0, 0)
{
}

Graphics::Vertex::Vertex(Vector3 position,
	Vector3 normal,
	Vector4 color,
	Vector2 uv,
	Vector3 tangent,
	Vector3 binormal) : POS(position), NORM(normal), UV(uv), TANGENT(tangent), BINORMAL(binormal) {}



void Graphics::Vertex::setUV(Vector2 uv)
{
	UV.x = uv.x;
	UV.y = uv.y;
}

void Vertex::setPosition(Vector3 pos)
{
	POS.x = pos.x;
	POS.y = pos.y;
	POS.z = pos.z;
}

void Vertex::setColor(Vector4 color)
{
	COLOR.x = color.x;
	COLOR.y = color.y;
	COLOR.z = color.z;
	COLOR.w = color.w;
}

void Vertex::setTangent(Vector3 tangent)
{
	TANGENT.x = tangent.x;
	TANGENT.y = tangent.y;
	TANGENT.z = tangent.z;
}

void Vertex::setBinormal(Vector3 binormal)
{
	BINORMAL.x = binormal.x;
	BINORMAL.y = binormal.y;
	BINORMAL.z = binormal.z;
}

