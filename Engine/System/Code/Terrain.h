#pragma once

#include "Resource.h"

BEGIN(Engine)


class Camera;
class Layer;
class ENGINE_DLL Terrain : public Resource
{
protected:
	explicit Terrain();
	explicit Terrain(const Terrain&);
public:
	virtual ~Terrain();


public :
	GET(int, IndexNum, m_iIndexNum);

public:
	virtual HRESULT	Init();
	virtual void	Update();
	virtual void	Render();
protected:
	virtual void	Release();

protected :
	HRESULT	Init_Vtx();
	HRESULT	Init_Idx();

protected:
	struct VertexType
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR4 color;
	};

protected:
	ID3D11Buffer*	m_pVtxBuf;
	ID3D11Buffer*	m_pIdxBuf;

	int		m_iWidth;
	int		m_iHeight;
	int		m_iVertexNum;
	int		m_iIndexNum;
};


END