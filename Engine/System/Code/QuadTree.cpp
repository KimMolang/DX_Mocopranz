#include "stdafx.h"
#include "QuadTree.h"

#include "VIBufferTerrain.h"
#include "ShaderTerrain.h"
#include "Frustum.h"

#include <cmath>

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
	//m_iRectanglesCount = TOTAL_VERTEX_NUM * 2;

	m_pVertexList = new VertexTexture[TOTAL_VERTEX_NUM];
	_pTerrain->CopyVertexInfoArray(m_pVertexList);

	float fWidth = _pTerrain->GetTerrainWidth();
	float fDepth = _pTerrain->GetTerrainDepth();
	float fCenterX = fWidth / 2.0f;
	float fCenderZ = fDepth / 2.0f;

	m_pParentNode = new NodeType();
	CreateTreeNode(m_pParentNode, fCenterX, fCenderZ, fWidth, fDepth);

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

void QuadTree::CreateTreeNode(NodeType* node, float positionX, float positionZ, float width, float depth)
{
	node->fPosX = positionX;
	node->fPosZ = positionZ;
	node->width = width;
	node->width = depth;

	node->iRectanglesCount = 0;

	int numRectangles = CountRectangles(-1, positionX, positionZ, width, depth);

	// Case 1: If there are no triangles in this node then this part of the tree is complete.
	if (numRectangles == 0)
	{
		return;
	}


	// Case 2: If there are too many triangles inside this node
	// then it gets split into four new quads/nodes.
	if (numRectangles > MAX_RECTANGLES)
	{
		float childrenWidth = (width / 2.0f);
		float childrenDepth = (depth / 2.0f);

		for (int i = 0; i < 4; ++i)
		{
			// Calculate the position offsets for the new child node.
			float offsetX = ((i % 2 == 0) ? -1.0f : 1.0f) * (width / 4.0f);
			float offsetZ = ((i <= 2) ? -1.0f : 1.0f) * (width / 4.0f);

			// See if there are any triangles in the new node.
			float childPositionX = positionX + offsetX;
			float childPositionZ = positionZ + offsetZ;
			
			int count = CountRectangles(i, childPositionX, childPositionZ, childrenWidth, childrenDepth);

			if (count > 0)
			{
				// If there are triangles inside where this new node would be then create the child node.
				node->nodes[i] = new NodeType;

				// Extend the tree starting from this new child node now.
				CreateTreeNode(node->nodes[i], childPositionX, childPositionZ, childrenWidth, childrenDepth);
			}
		}


		return;
	}

	//Case 3: If there are the right number of triangles
	// then create and load the vertex and index buffer from the terrain list into this node.
	// We have also determined that this must be a bottom child node.
	node->iRectanglesCount = numRectangles;
	//int vertexCount = numRectangles * 3;

	//VertexTexture* pVectexInfo = new VertexTexture[numRectangles];
	// **
}

int QuadTree::CountRectangles(int childrendIndex, float positionX, float positionZ, float width, float depth)
{
	if (childrendIndex == -1)
	{
		// Top of parents!! root!!
		return (int)(width * depth);
	}


	int count = 0;

	int iCntZ = (int)floorf(width);
	int iCntX = (int)floorf(depth);

	int offsetX = (int)floorf( positionX + ((childrendIndex % 2 == 0) ? -1.0f : 0.0f) * (width/2.0f) );
	int offsetZ = (int)floorf( positionZ + ((childrendIndex <= 2) ? 0.0f : -1.0f) * (depth/2.0f) );

	for (int j = offsetZ; j < (offsetZ + iCntZ) - 1; ++j)
	{
		for (int i = offsetX; i < (offsetX + iCntX) - 1; ++i)
		{
			// Vertex
			int iVtxIndex = (j * iCntX) + i;
			/*
			iIndex	+ _iCntX ---  iIndex + _iCntX + 1
			|\|
			iIndex	---	 iIndex	+ 1
			*/

			// 전체 갯수 알아야함
			//
			//m_pVertexList[iVtxIndex].vPos.x;
			//m_pVertexList[iVtxIndex + 1].vPos.x;
			//m_pVertexList[iVtxIndex + 1].vPos.x;
		}
	}

	return count;
}

void QuadTree::ReleaseNode(NodeType * node)
{
}

void QuadTree::RenderNode(NodeType * node, Frustum * frustum)
{
}


END