//====================================================================================================
// Filename:	Lighting.fx
// Created by:	Peter Chan
// Description:	Simple shader for lighting & texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================
//cbuffer WorldBuffer : register(b0)
//{
//	matrix world;
//	matrix wvp;
//
//	float3 cameraPosition;
//}
//
//cbuffer LightBuffer : register (b1)
//{
//	float4 lightAmbient;
//	float4 lightDiffuse;
//	float4 lightSpecular;
//	float3 lightDirection;
//}
//
//cbuffer MaterialBuffer : register (b2)
//{
//	float4 materialAmbient;
//	float4 materialDiffuse;
//	float4 materialSpecular;
//}


cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix wvp;

	float3 cameraPosition;

	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
	float3 lightDirection;

	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;

	float materialPower;
}

cbuffer BoneConstantBuffer : register(b1)
{
	matrix boneTransforms[128];
}

static matrix Identity =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};


matrix GetBoneTransform(int4 indices, float4 weights)
{
	matrix transform = Identity;
	
	transform += boneTransforms[0] * weights[0];
	transform += boneTransforms[1] * weights[1];
	transform += boneTransforms[2] * weights[2];
	transform += boneTransforms[3] * weights[3];

	return transform;

}

Texture2D diffuseMap : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	int4 blendIndices : BLENDINDICES;
	float4 blendWeights : BLENDWEIGHTS;

};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;

	float3 normal : NORMAL;

	float3 directionToLight : TEXCOORD1;
	float4 directionToView :TEXCOORD2;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;

	matrix boneTransform = GetBoneTransform(input.blendIndices, input.blendWeights);

	float4 posBone = input.position;
	float4 posLocal = mul(posBone, boneTransform);
	float4 posWorld = mul(posLocal, world);
	float4 posProj = mul(posLocal, wvp);

	float3 normalBone = input.normal;
	float3 normalLocal = mul(float4(normalBone, 0.0f), boneTransform);
	float3 normalWorld = mul(float4(normalLocal, 0.0f), world).xyz;

	float3 directionToLight = -normalize(lightDirection);
	float3 directionToView = normalize(cameraPosition - mul(input.position, world).xyz);
	

	output.position = posProj;
	output.normal = normalWorld;
	output.directionToLight = directionToLight;
	output.directionToView = directionToView;
	output.texCoord = input.texCoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{

	return input.color * diffuseMap.Sample(textureSampler, input.texCoord);
}
