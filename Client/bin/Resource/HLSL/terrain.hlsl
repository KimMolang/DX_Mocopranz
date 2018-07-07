//
// terrain_vs.hlsl

cbuffer ViewMatrixBuffer : register(b0)
{
	matrix matrixView : packoffset(c0);
}

cbuffer ProjMatrixBuffer : register(b1)
{
	matrix matrixProjection : packoffset(c0);
}

cbuffer WorldMatrixBuffer : register(b2)
{
	matrix matrixWorld : packoffset(c0);
}

// https://www.slideshare.net/SukwooLee4/ss-87133392
cbuffer LightBuffer
{
	float4 colorAmbient;	// Ambient : °£Á¢±¤.
	float4 colorDiffuse;	// Diffuse : ³­¹Ý»ç. °´Ã¼ÀÇ Ç¥¸é¿¡ ºÎµúÈù ÈÄ Àü¹æÇâÀ¸·Î Èð¾îÁö´Â ºû
	//float4 colorSpecular;	// Specular : Á¤¹Ý»ç.
	//float4 colorEmissive.	// Emissive : ¹ß±¤.
	float3 dirLight;

	float padding;
};

struct Vertex_In
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	//float4 color : COLOR;
};

struct Pixel_In
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	//float4 color : COLOR;
};

Pixel_In VS(Vertex_In input)
{
	Pixel_In output = (Pixel_In)0;

	matrix matAll = mul(matrixWorld, matrixView);
	matAll = mul(matAll, matrixProjection);

	output.position = mul(input.position, matAll);
	output.normal = input.normal;
	//output.color = input.color;
}

SamplerState samplerState;
float4 PS(Pixel_In input) : SV_Target
{
	float3 dirLight = -dirLight;
	float3 lightIntensity = saturate(dot(input.normal, dirLight));
	float4 color = colorAmbient;

	if (lightIntensity > 0.0f)
	{
		color += (colorDiffuse * lightIntensity);
	}

	color = saturate(color);


	return color;
}