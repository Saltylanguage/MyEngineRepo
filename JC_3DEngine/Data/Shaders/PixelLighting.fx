//====================================================================================================
// Filename:	Lighting.fx
// Created by:	Peter Chan
// Description:	Simple shader for lighting & texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer WorldBuffer : register( b0 )
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
	float3 normal   : NORMAL;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;

	float4 tangent : TANGENT;
	float4 biNormal : BINORMAL;
		
};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float4 ambient	: COLOR;
	float3 dirToLight : TEXCOORD;
	float3 dirToView : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float2 texCoord	: TEXCOORD3;

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
	output.ambient = lightAmbient * materialAmbient;

	output.dirToLight = directionToLight;
	output.dirToView = directionToView;
	output.normal = normal;
	output.texCoord = input.texCoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 normal = normalize(input.normal);
	float3 dirView = normalize(input.dirToView);
	float3 dirLight = normalize(input.dirToLight);

	//Diffuse
	float d = saturate(dot(dirLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;
	
	//Specular
	float3 reflectionVector = reflect(-dirLight, normal);
	float specFactor = saturate(dot(dirView, reflectionVector));
	float4 specular =  specFactor * lightSpecular * materialSpecular;

	return (input.ambient + diffuse + specular) * diffuseMap.Sample(textureSampler, input.texCoord);
	//return saturate(float4(normal, 1.0f)) * diffuseMap.Sample(textureSampler, input.texCoord);
}
