#include "stdafx.h"
#include "QuadTree.h"

#include "VIBufferTerrain.h"
#include "ShaderTerrain.h"
#include "Frustum.h"

BEGIN(Engine)


QuadTree::QuadTree()
{

}

QuadTree::QuadTree(const QuadTree & other)
{
}

QuadTree::~QuadTree()
{
}

void QuadTree::Initialize(VIBufferTerrain * _pTerrain)
{
	float centerX = 0.0f;
}

void QuadTree::Render(Frustum * pFrustum)
{
}

void QuadTree::Release()
{
}

void QuadTree::CalculateMeshDimensions(int vertexCount, float& centerX, float& centerZ, float& meshWidth)
{
}

void QuadTree::CreateTreeNode(NodeType* node, float positionX, float positionZ, float width)
{
}

int QuadTree::CountTriangles(float positionX, float positionZ, float width)
{
	return 0;
}

bool QuadTree::IsTriangleContained(int index, float positionX, float positionZ, float width)
{
	return false;
}

void QuadTree::ReleaseNode(NodeType * node)
{
}

void QuadTree::RenderNode(NodeType * node, Frustum * frustum)
{
}


END