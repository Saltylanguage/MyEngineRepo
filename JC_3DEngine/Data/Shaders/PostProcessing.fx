//====================================================================================================
// Filename:	NormalMapping.fx
// Created by:	Peter Chan
// Description:	Shader performing normal mapping.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register(b0)
{
	int postProcessingIndex;
	float timer;
};

//====================================================================================================
// Textures and Samplers
//====================================================================================================
Texture2D textureScene : register(t0);
SamplerState textureSampler: register(s0);

//====================================================================================================
// Structs
//====================================================================================================
struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;
};

struct VS_OUTPUT
{
	float4 position  : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = input.position;
	output.texCoord = input.texCoord;

	return output;
}
//====================================================================================================
// Pixel Shader
//====================================================================================================



////NIGHT VISION
float4 PS(VS_OUTPUT input) : SV_Target
{
	input.texCoord.y += sin(input.texCoord.y * 1080 * timer) * 0.03 ;
	
	float4 color = textureScene.Sample(textureSampler, input.texCoord);

	color.r = 0.0f;
	color.b = 0.0f;

	return color;
}

////ZERG VIEW
//float4 PS(VS_OUTPUT input) : SV_Target
//{
//	input.texCoord.y -= (sin(input.texCoord.x * 10 )) * timer * 0.5f;
//
//	float4 color = textureScene.Sample(textureSampler, input.texCoord);
//
//	color.b *= 0.10f;
//	color.g *= 0.10f;
//
//	return color;
//}



