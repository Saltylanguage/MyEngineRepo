//================================================================================
// Filename:	SiegeSimpleDraw.fx
// Created by:	Peter Chan
// Description:	Shader for line rendering.
//================================================================================

//================================================================================
// Constant Buffers
//================================================================================

cbuffer CBSimpleDraw : register( b0 )
{
	matrix transform;
}

//================================================================================
// Structs
//================================================================================

struct A2V
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;
};

//--------------------------------------------------------------------------------

struct V2P
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR;
};

//================================================================================
// Vertex Shader
//================================================================================

V2P VS(A2V input)
{
	V2P output = (V2P)0;

	output.position = mul(input.position, transform);
	output.color = input.color;

	return output;
}

//================================================================================
// Pixel Shader
//================================================================================

float4 PS(V2P input) : SV_Target
{
	return input.color;
}