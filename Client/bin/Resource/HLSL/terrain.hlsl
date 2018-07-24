//
// terrain_vs.hlsl
//
// register : https://docs.microsoft.com/ko-kr/windows/desktop/direct3dhlsl/dx-graphics-hlsl-variable-register
// What are registers in HLSL for? : https://gamedev.stackexchange.com/questions/55319/what-are-registers-in-hlsl-for
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
cbuffer LightBuffer : register(b3)
{
	float4 colorAmbient : packoffset(c0);	// Ambient : °£Á¢±¤.
	float4 colorDiffuse : packoffset(c1);	// Diffuse : ³­¹Ý»ç. °´Ã¼ÀÇ Ç¥¸é¿¡ ºÎµúÈù ÈÄ Àü¹æÇâÀ¸·Î Èð¾îÁö´Â ºû
	//float4 colorSpecular;	// Specular : Á¤¹Ý»ç.
	//float4 colorEmissive.	// Emissive : ¹ß±¤.
	float3 dirLight : packoffset(c2);

	float padding : packoffset(c3);
};

struct Vertex_In
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct Pixel_In
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

Pixel_In VS(Vertex_In input)
{
	Pixel_In output = (Pixel_In)0;

	matrix matAll = mul(matrixWorld, matrixView);
	matAll = mul(matAll, matrixProjection);

	output.position = mul(input.position, matAll);

	output.normal = input.normal;
	output.normal = normalize(output.normal);

	output.tex = input.tex;


	return output;
}


Texture2D shaderTexture : register(t0);
SamplerState samplerState : register(s0);

float4 PS(Pixel_In input) : SV_Target
{
	float lightIntensity = saturate(dot(input.normal, (dirLight * -1)));
	float4 color = colorAmbient;
	
	if (lightIntensity > 0.0f)
	{
		color += (colorDiffuse * lightIntensity);
	}


	float4 colorTexture
		= shaderTexture.Sample(samplerState, input.tex);

	color = saturate(color) * colorTexture;

	// for test
	//color.x = input.normal.x;
	//color.y = input.normal.y;
	//color.z = input.normal.z;

	return color;
}