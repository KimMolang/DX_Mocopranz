#include "stdafx.h"
#include "QuadTree.h"

#include "VIBufferTerrain.h"
#include "ShaderTerrain.h"
#include "Frustum.h"

BEGIN(Engine)


QuadTree::QuadTree()
	: m_pVertexList(nullptr)
	, m_pParentNode(nullptr)
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
	const int TOTAL_VERTEX_NUM = _pTerrain->GetVtxNum();
	m_iTriangleCount = TOTAL_VERTEX_NUM / 3; // ...?
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