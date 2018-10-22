#pragma once

BEGIN(Engine)



const int MAX_RECTANGLES = 5000;

class VIBufferTerrain;
class Frustum; // ����ü
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
		float width;
		int iRectanglesCount;

		ID3D11Buffer* pVertexBuffer, *pIndexBuffer;
		NodeType* nodes[4];

		NodeType()
			: fPosX(0.0f), fPosY(0.0f), fPosZ(0.0f)
			, width (0.0f)
			, iRectanglesCount(0)
			, pVertexBuffer(nullptr), pIndexBuffer(nullptr)
		{
			nodes[0] = nodes[1] = nodes[2] = nodes[3] = nullptr;
		}
	};

private :
	void CreateTreeNode(NodeType* node, float positionX, float positionZ, float width);
	int CountRectangles(float positionX, float positionZ, float width);
	bool IsRectangleContained(int index, float positionX, float positionZ, float width);
	void ReleaseNode(NodeType*);
	void RenderNode(NodeType*, Frustum*);

private:
	//int m_iRectanglesCount
	int m_iDrawCount;
	struct VertexTexture* m_pVertexList;
	NodeType* m_pParentNode;
};


END