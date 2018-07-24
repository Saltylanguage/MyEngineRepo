//====================================================================================================
// Filename:	Lighting.fx
// Created by:	Peter Chan
// Description: Shader for billboarding a point list
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer CBBillborad :  register (b0)
{
	matrix ViewProj;
	float4 ViewPosition;
	float4 Dimension;
}

//====================================================================================================
//Textures and Samplers
//====================================================================================================

Texture2D TextureBillboard : register(t0);
SamplerState SamplerLinear: register(s0);

//====================================================================================================
// Structs
//====================================================================================================


struct A2V
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;

};

struct V2G
{
	float3 position : POSITION;
};

struct G2P
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};



//====================================================================================================
// Vertex Shader
//====================================================================================================

V2G VS(A2V input)
{
	V2G output = (V2G)0;
	output.position = input.position.xyz;
	return output;
}


//====================================================================================================
// Geometry Shader
//====================================================================================================

[maxvertexcount(4)]
void GS(point V2G input[1], inout TriangleStream<G2P> outputStream)
{
	float3 up = float3(0.0f, 1.0f, 0.0f);
	float3 look = normalize(ViewPosition.xyz - input[0].position);
	float3 right = normalize(cross(up, look));

	float4 v[4];
	v[0] = float4(input[0].position.xyz + (right * Dimension.x) - (up * Dimension.y), 1.0f);
	v[1] = float4(input[0].position.xyz + (right * Dimension.x) + (up * Dimension.y), 1.0f);
	v[2] = float4(input[0].position.xyz - (right * Dimension.x) - (up * Dimension.y), 1.0f);
	v[3] = float4(input[0].position.xyz - (right * Dimension.x) + (up * Dimension.y), 1.0f);

	float2 uv[4];

	uv[0] = float2(0.0f, 1.0f);
	uv[1] = float2(0.0f, 0.0f);
	uv[2] = float2(1.0f, 1.0f);
	uv[3] = float2(1.0f, 0.0f);

	G2P output = (G2P)0;

	[unroll] 
	for (int i = 0; i < 4; i++)
	{
		output.position = mul(v[i], ViewProj);
		output.texCoord = uv[i];
		outputStream.Append(output);
	}


}


//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(G2P input) : SV_Target
{
	float4 texColor = TextureBillboard.Sample(SamplerLinear, input.texCoord);
	return texColor;
}

