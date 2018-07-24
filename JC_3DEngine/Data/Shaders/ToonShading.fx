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
Texture2D gradientMap : register(t1);

SamplerState textureSampler : register(s0);
SamplerState pointSampler : register(s1);


//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;
	float2 texCoord	: TEXCOORD;
	float4 color	: COLOR;
};

struct VS_OUTPUT
{
	float4 position			: SV_POSITION;
	float3 normal			: NORMAL;
	float3 tangent			: TEXTCOORD4;
	float3 binormal			: TEXTCOORD5;
	float3 dirToLight		: TEXTCOORD;
	float3 dirToView		: TEXTCOORD1;
	float2 texCoord			: TEXTCOORD3;
	float ambient			: COLOR;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float3 normal = normalize(mul(float4(input.normal, 0.0f), world).xyz);
	float3 tangent = normalize(mul(float4(input.tangent, 0.0f), world).xyz);
	float3 binormal = cross(normal, tangent);
	float3 directionToLight = -normalize(lightDirection);
	float3 directionToView = normalize(cameraPosition - mul(input.position, world).xyz);
	
	output.position = mul(input.position, wvp );

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

    float3 tangent = normalize(input.tangent);
    float3 binormal = normalize(input.binormal);	
	float3 normal = normalize(input.normal);

    float3x3 TBN = float3x3(tangent, binormal, normal);
    float3 n = mul(sampledNormal, TBN);
	
	float3 directionToLight = normalize(input.dirToLight);
	float3 directionToView = normalize(input.dirToView);

	//Ambient
	float4 ambient = lightAmbient * materialAmbient;

	//Diffuse
	float d = saturate(dot(directionToLight, normal));
	d = gradientMap.Sample(pointSampler, float2(d, 0), 0).r;
	
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	//Specular
	float3 reflectionVector = reflect(-directionToLight, normal);
	float specFactor = saturate(dot(directionToView, reflectionVector));
	float4 specular = specFactor * lightSpecular * materialSpecular;

	float4 diffuseColor = diffuseMap.Sample(textureSampler, input.texCoord);


	return ((ambient + diffuse) * diffuseColor);	
}

