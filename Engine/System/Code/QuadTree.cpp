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
	//m_iTriangleCount = TOTAL_VERTEX_NUM * 2;

	m_pVertexList = new VertexTexture[TOTAL_VERTEX_NUM];
	_pTerrain->CopyVertexInfoArray(m_pVertexList);

	float fWidth = _pTerrain->GetTerrainWidth();
	float fCenterX = fWidth / 2.0f;
	float fCenderZ = _pTerrain->GetTerrainDepth() / 2.0f;

	//CalculateMeshDimensions(TOTAL_VERTEX_NUM, fCenterX, fCenderZ, fWidth);

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

// How come I should do that?
// I think I don't have to do.
//void QuadTree::CalculateMeshDimensions(int vertexCount, float& centerX, float& centerZ, float& meshWidth)
//{
//	for (int i = 0; i < vertexCount; ++i)
//	{
//		centerX += m_pVertexList[i].vPos.x;
//		centerZ += m_pVertexList[i].vPos.z;
//	}
//
//	// the mid-point of the mesh.
//	centerX = centerX / (float)vertexCount;
//	centerZ = centerZ / (float)vertexCount;
//
//	float maxWidth = 0.0f;
//	float maxDepth = 0.0f;
//
//	float minWidth = fabsf(m_pVertexList[0].vPos.x - centerX);
//	float minDepth = fabsf(m_pVertexList[0].vPos.z - centerZ);
//
//
//	// Go through all the vertices and find the maximum and minimum width and depth of the mesh.
//	for (int i = 0; i < vertexCount; ++i)
//	{
//		float width = fabsf(m_pVertexList[i].vPos.x - centerX);
//		float depth = fabsf(m_pVertexList[i].vPos.z - centerZ);
//
//		if (width > maxWidth) { maxWidth = width; }
//		if (depth > maxDepth) { maxDepth = depth; }
//		if (width < minWidth) { minWidth = width; }
//		if (depth < minDepth) { minDepth = depth; }
//	}
//
//	// Find the absolute maximum value between the min and max depth and width.
//	float maxX = (float)max(fabs(minWidth), fabs(maxWidth));
//	float maxZ = (float)max(fabs(minDepth), fabs(maxDepth));
//
//	meshWidth = max(maxX, maxZ) * 2.0f; // radius * 2.0f;
//}

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