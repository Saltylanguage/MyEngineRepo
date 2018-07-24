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
	matrix wvp;	
}

TextureCube TextureSkybox : register(t0);

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
	float3 texCoord	: TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.position = mul(input.position, wvp);
	output.texCoord = input.position.xyz;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	return TextureSkybox.Sample(SamplerLinear, input.texCoord);	
}
