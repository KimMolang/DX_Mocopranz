#pragma once

BEGIN(Engine)



const int MAX_RECTANGLES = 5000;

class VIBufferTerrain;
class Frustum; // ÀýµÎÃ¼
class ENGINE_DLL QuadTree
{
public:
	QuadTree();
	QuadTree(const QuadTree& other);
	~QuadTree();

public :
	void Initialize(VIBufferTerrain*);
	void Render(Frustum*);
	void Release();

public :
	GET(int, DrawCount, m_iDrawCount);


private:
	struct NodeType
	{
		float fPosX, fPosY, fPosZ;
		float width, depth;
		int iRectanglesCount;

		ID3D11Buffer* pVertexBuffer, *pIndexBuffer;
		NodeType* nodes[4];

		NodeType()
			: fPosX(0.0f), fPosY(0.0f), fPosZ(0.0f)
			, width(0.0f), depth(0.0f)
			, iRectanglesCount(0)
			, pVertexBuffer(nullptr), pIndexBuffer(nullptr)
		{
			nodes[0] = nodes[1] = nodes[2] = nodes[3] = nullptr;
		}
	};

private :
	void CreateTreeNode(NodeType* node, float positionX, float positionZ, float width, float depth);
	int CountRectangles(int childrendIndex, float positionX, float positionZ, float width, float depth);
	void ReleaseNode(NodeType*);
	void RenderNode(NodeType*, Frustum*);

private:
	//int m_iRectanglesCount
	int m_iDrawCount;
	struct VertexTexture* m_pVertexList;
	NodeType* m_pParentNode;
};


END