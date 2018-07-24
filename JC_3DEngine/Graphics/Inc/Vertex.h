#pragma once
#include <Math\Inc\Vector3.h>
#include <Math\Inc\Vector4.h>


using namespace Math;

namespace Graphics
{
	class Vertex
	{
	public:
		Vector3 POS;
		Vector3 NORM;
		Vector4 COLOR;
		Vector2 UV;

		Vector3 TANGENT;
		Vector3 BINORMAL;

		int boneIndex[4];
		float boneWeight[4];

	public:
		Vertex();
		
		Vertex(Vector3 position, Vector3 normal, Vector4 color, Vector2 uv);
		
		Vertex(Vector3 position,
			Vector3 normal,
			Vector4 color,
			Vector2 uv,
			Vector3 tangent,
			Vector3 binormal);
		
		void setUV(Vector2 uv);
		void setPosition(Vector3 pos);
		void setColor(Vector4 color);
		void setTangent(Vector3 tangent);
		void setBinormal(Vector3 binormal);

		const Vector2& getUV() const { return UV; } // make things private and copy this signature
		Vector3 getPosition() { return POS; }
		Vector4 getColor() { return COLOR; }
		Vector3 getNorm() { return NORM; }
		Vector3 getTangent() { return TANGENT; }
		Vector3 getBinormal() { return BINORMAL; }
	};
}