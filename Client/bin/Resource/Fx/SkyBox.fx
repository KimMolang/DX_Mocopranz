

cbuffer cbViewMatrix : register(b0)
{
	matrix gMatView : packoffset(c0);
}

cbuffer cbProjMatrix : register(b1)
{
	matrix gMatProj : packoffset(c0);
}

cbuffer cbWorldMatrix : register(b2)
{
	matrix gMatWorld : packoffset(c0);
}

struct Vertex_Out
{
	float4 pos : SV_POSITION;
	float3 tex2dcoord : TEXCOORD;
};

Vertex_Out VS(float3 inPos : POSITION, float2 inTexCoord : TEXCOORD)
{
	Vertex_Out output = (Vertex_Out)0;

	matrix matAll = mul(gMatWorld, gMatView);
	matAll = mul(matAll, gMatProj);

	output.pos = mul(float4(inPos, 1.0f), matAll);
	output.tex2dcoord = inPos;

	return output;
}

Texture2D gTexture;
SamplerState gSamplerState : register(s0);
TextureCube gTextureCube : register(t0);

float4 PS(Vertex_Out input) : SV_Target
{
	float4 color = gTextureCube.Sample(gSamplerState, input.tex2dcoord);
	color.a = 1.f;
	return color;
}