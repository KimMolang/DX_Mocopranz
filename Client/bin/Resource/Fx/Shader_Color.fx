

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

struct Vertex_In
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct Vertex_Out
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

Vertex_Out VS(Vertex_In input)
{
	Vertex_Out output = (Vertex_Out)0;

	matrix matAll = mul(gMatWorld, gMatView);
	matAll = mul(matAll, gMatProj);

	output.pos = mul(input.pos, matAll);
	output.color = input.color;

	return output;
}

float4 PS(Vertex_Out input) : SV_Target
{
	return input.color;
}