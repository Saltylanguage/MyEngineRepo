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
Texture2D specularMap : register(t1);
Texture2D normalMap   : register(t2);
Texture2D displacementMap   : register(t3);

SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal   : NORMAL;
	float3 tangent   : TANGENT;
	float3 binormal  : BINORMAL;
	float2 texCoord	: TEXCOORD;
	float4 color	: COLOR;
};

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TEXTCOORD4;
	float3 binormal		: TEXTCOORD5;
	float3 dirToLight	: TEXCOORD;
	float3 dirToView	: TEXCOORD1;
	float2 texCoord		: TEXCOORD3;
	float4 ambient		: COLOR;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float3 normal   = mul(float4(input.normal,   0.0f), world).xyz;
	float3 tangent  = mul(float4(input.tangent,  0.0f), world).xyz;
	float3 binormal = cross(normal, tangent);	
	
	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;

	float4 position = input.position + float4((displacement * input.normal), 0);

	float3 directionToLight = -normalize(lightDirection);
	float3 directionToView = normalize(cameraPosition - mul(position, world).xyz);
	
	output.position = mul(position, wvp);
	//Ambient
	output.ambient = lightAmbient * materialAmbient;

	output.normal = normal;
	output.tangent = tangent;
	output.binormal = binormal;
	output.dirToLight = directionToLight;
	output.dirToView = directionToView;
	output.texCoord = input.texCoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 normalColor = normalMap.Sample(textureSampler, input.texCoord);
	float3 sampledNormal = float3((2.0f * normalColor.xy) - 1.0f, normalColor.z);

	float3 t = normalize(input.tangent);
	float3 b = normalize(input.binormal);
	float3 n = normalize(input.normal);
	
	float3x3 TBN = float3x3(t, b, n);
	float3 normal = mul(sampledNormal, TBN);

	float3 dirToView = normalize(input.dirToView);
	float3 dirToLight = normalize(input.dirToLight);

	//Normal
	//normal =((normalMap.Sample(textureSampler, input.texCoord).xyz * 2) - 1);
	//normal = mul(normal, TBN);

	//Diffuse
	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	//Specular
	
	float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);
	float4 specularColor = specularMap.Sample(textureSampler, input.texCoord).rrrr;

	float3 reflectionVector = reflect(-dirToLight, normal);
	float specFactor = saturate(dot(dirToView, reflectionVector));
	float h = normalize((dirToLight + dirToView) * 0.5f);
	float4 specular = pow(specFactor, 25) * lightSpecular * materialSpecular;

	return (diffuse + input.ambient) * diffuseColor + specular * specularColor;
}




