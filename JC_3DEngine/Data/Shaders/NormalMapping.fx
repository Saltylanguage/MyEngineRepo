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
	matrix World;
	matrix WVP;
	vector ViewPosition;
	vector LightDirection;
	vector LightAmbient;
	vector LightDiffuse;
	vector LightSpecular;
	vector MaterialAmbient;
	vector MaterialDiffuse;
	vector MaterialSpecular;
	vector MaterialEmissive;
	float MaterialPower;
	float DisplacementScale;
};

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);
Texture2D displacementMap : register(t3);

SamplerState textureSampler : register(s0);

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

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float3 binormal		: BINORMAL;
	float3 dirToLight	: TEXCOORD0;
	float3 dirToView	: TEXCOORD1;
	float2 texCoord		: TEXCOORD2;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float4 position = input.position + (float4(input.normal, 0.0f) * DisplacementScale * displacement);

	float4 posWorld = mul(position, World);
	float4 posProj = mul(position, WVP);

	float3 normal = mul(float4(input.normal, 0.0f), World).xyz;
	float3 tangent = mul(float4(input.tangent, 0.0f), World).xyz;
	float3 binormal = cross(normal, tangent);

	float3 dirToLight = -normalize(LightDirection.xyz);
	float3 dirToView = normalize(ViewPosition.xyz - posWorld.xyz);

	output.position = posProj;
	output.normal = normal;
	output.tangent = tangent;
	output.binormal = binormal;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
	output.texCoord = input.texCoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	// Sample normal from normal map
	float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
	float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);

	// Transform to world space
	float3 t = normalize(input.tangent);
	float3 b = normalize(input.binormal);
	float3 n = normalize(input.normal);
	float3x3 tbn = float3x3(t, b, n);
	float3 normal = mul(sampledNormal, tbn);

	float3 dirToLight = normalize(input.dirToLight);
	float3 dirToView = normalize(input.dirToView);

	// Ambient
	float4 ambient = LightAmbient * MaterialAmbient;

	// Diffuse
	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = d * LightDiffuse * MaterialDiffuse;

	// Specular
	float3 h = normalize((dirToLight + dirToView) * 0.5f);
	float s = saturate(dot(h, normal));
	float4 specular = pow(s, MaterialPower) * LightSpecular * MaterialSpecular;

	float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 specularColor = specularMap.Sample(textureSampler, input.texCoord).rrrr;

	return ((ambient + diffuse) * diffuseColor) + (specular * specularColor);
}
