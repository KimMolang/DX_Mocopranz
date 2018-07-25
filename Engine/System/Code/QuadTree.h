#pragma once

BEGIN(Engine)


const int MAX_TRIANGLES = 10000;

class VIBufferTerrain;
//class ShaderTerrain;
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


private:
	struct NodeType
	{
		float fPosX, fPosY, fPosZ;
		int iTriangleCount;

		ID3D11Buffer* pVertexBuffer, * pIndexBuffer;
		NodeType* nodes[4];

		NodeType()
			: fPosX(0.0f), fPosY(0.0f), fPosZ(0.0f)
			, iTriangleCount(0)
			, pVertexBuffer(nullptr), pIndexBuffer(nullptr)
		{ }
	};

private :
	void CalculateMeshDimensions(int vertexCount, float& centerX, float& centerZ, float& meshWidth);
	void CreateTreeNode(NodeType* node, float positionX, float positionZ, float width);
	int CountTriangles(float positionX, float positionZ, float width);
	bool IsTriangleContained(int index, float positionX, float positionZ, float width);
	void ReleaseNode(NodeType*);
	void RenderNode(NodeType*, Frustum*);

private:
	int m_iTriangleCount, m_iDrawCount;
	NodeType* m_pParentNode;
};


END