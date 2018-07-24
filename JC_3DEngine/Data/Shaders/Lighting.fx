//====================================================================================================
// Filename:	Lighting.fx
// Created by:	Peter Chan
// Description:	Simple shader for lighting & texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================
cbuffer WorldBuffer : register(b0)
{
	matrix world;
	matrix wvp;

	float3 cameraPosition;
}

cbuffer LightBuffer : register (b1)
{
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
	float3 lightDirection;
}

cbuffer MaterialBuffer : register (b2)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
}

Texture2D diffuseMap : register(t0);
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

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul(input.position, wvp );

	float3 directionToLight = -normalize(lightDirection);
	float3 directionToView = normalize(cameraPosition - mul(input.position, world).xyz);
	float3 normal = normalize(mul(float4(input.normal, 0), world).xyz);

	//Ambient
	float4 ambient = lightAmbient * materialAmbient;
	
	//Diffuse
	float d = saturate(dot(directionToLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;
	
	//Specular
	float3 reflectionVector = reflect(-directionToLight, normal);
	float specFactor = saturate(dot(directionToView, reflectionVector));
	float4 specular =  specFactor * lightSpecular * materialSpecular;

	output.color = ambient + diffuse + specular;
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
