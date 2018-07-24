//====================================================================================================
// Filename:	CubeMapping.fx
// Created by:	Peter Chan
// Description:	Simple shader for lighting & texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	matrix world;
	matrix wvp;	
	float3 cameraPos;
}

TextureCube diffuseMap : register(t0);
SamplerState SamplerLinear : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal   : NORMAL;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;

};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float3 normal	: TEXCOORD1;
	float3 directionToViewer : TEXCOORD2;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.position = mul(input.position, wvp);
	output.directionToViewer = normalize(cameraPos - mul(input.position, world).xyz);
	output.normal = normalize(mul(float4(input.normal, 0), world).xyz);
	
	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 Reflection = reflect(-normalize(input.directionToViewer), normalize(input.normal));

	return diffuseMap.Sample(SamplerLinear, Reflection);	
}
