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
	m_iTriangleCount = TOTAL_VERTEX_NUM * 2;

	m_pVertexList = new VertexTexture[TOTAL_VERTEX_NUM];
	_pTerrain->CopyVertexInfoArray(m_pVertexList);
	
	float fCenterX, fCenderZ, fWidth;
	CalculateMeshDimensions(TOTAL_VERTEX_NUM, fCenterX, fCenderZ, fWidth);

	m_pParentNode = new NodeType();
	CreateTreeNode(m_pParentNode, fCenterX, fCenderZ, fWidth);

	m_pVertexList = nullptr;
}

/*
The Render function calls RenderNode
which goes through the tree and renders nodes using the frustum object
which determines the node visibility.
The m_drawCount variable must be initialized to zero before the rendering is done
as it will be incremented for each node drawn for all the triangles in each node.
*/
void QuadTree::Render(Frustum * _pFrustum)
{
	// Reset the number of triangles that are drawn for this frame.
	m_iDrawCount = 0;

	// Render each node that is visible starting at the parent node and moving down the tree.
	RenderNode(m_pParentNode, _pFrustum);
}

void QuadTree::Release()
{
	if (m_pParentNode)
	{
		ReleaseNode(m_pParentNode);
		::Safe_Delete(m_pParentNode);
	}
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