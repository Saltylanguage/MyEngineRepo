//====================================================================================================
// Filename:	Texturing.fx
// Created by:	Peter Chan
// Description:	Simple shader for texturing.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

//cbuffer ConstantBuffer : register(b0)
//{
//	matrix World;
//	matrix View;
//	matrix Projection;
//}

cbuffer ConstantBuffer : register(b0)
{
	matrix WVP;

	float2 distortion1;
	float2 distortion2;
	float2 distortion3;

	float distortionScale;
	float distortionBias;
}




Texture2D fireTexture     :  register(t0);
Texture2D noiseTexture    :  register(t1);
Texture2D alphaTexture    :  register(t2);

SamplerState wrapSampler  :  register(s0);
SamplerState clampSampler :  register(s1);

//====================================================================================================
// Structs
//====================================================================================================

struct VertextInputType
{
	float4 position : POSITION;
	float2 tex: TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float2 texCoords1 : TEXCOORD1;
	float2 textCoords2 : TEXCOORD2;
	float2 texCoords3 : TEXCOORD3;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

PixelInputType VS(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = input.position * WVP;
	output.tex = input.tex;

	output.texCoords1 = (input.tex * scales.x);
	output.texCoords1.y = output.texCoords.y + (frameTime * scrollSpeeds.x);

	output.texCoords2 = (input.tex * scales.y);
	output.texCoords2.y = output.texCoords2.y + (frameTime * scrollSpeeds.y);

	output.texCoords3 = (input.tex * scales.z);
	output.texCoords3.y = output.texCoords3.y + (frameTime * scrollsSpeeds.z);

	return output;
}


//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(PixelInputType input) : SV_TARGET
{
	float4 noise1;
	float4 noise2;
	float4 noise3;
	float4 finalNoise;
	float perturb;
	float2 noiseCoords;
	float4 fireColor;
	float4 alphaColor;

	//====================================================================================================
	// HANDLE NOISE
	//====================================================================================================
	noise1 = noiseTexture.Sample(wrapSampler, input.texCoords1);
	noise2 = noiseTexture.Sample(wrapSampler, input.texCoords2);
	noise3 = noiseTexture.Sample(wrapSampler, input.texCoords3);

	noise1 = (noise1 - 0.5f) * 2.0f;
	noise2 = (noise2 - 0.5f) * 2.0f;
	noise3 = (noise3 - 0.5f) * 2.0f;

	finalNoise = noise1 + noise2 + noise3;

	perturb = ((1.0f - input.tex.y) * distortionScale) + distortionBias;

	noiseCoords.xy = (finalNoise.xy * perturb) + input.tex.xy;

	//====================================================================================================
	// HANDLE COLOR
	//====================================================================================================
	fireColor = fireTexture.Sample(clampSampler, noiseCoords.xy);

	//====================================================================================================
	// HANDLE ALPHA
	//====================================================================================================
	alphaColor = alphaTexture.Sample(clampSampler, noiseCoords.xy);

	fireColor.a = alphaColor;

	return fireColor;
}


