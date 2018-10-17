#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


class Camera;
class Layer;
class ENGINE_DLL VIBufferTerrain : public VIBuffer
{
public:
	static VIBufferTerrain* Create
	(
		const int _iCntX
		, const int _iCntY
		, const char* _Path = nullptr
	);
	CLONE(VIBufferTerrain);
private:
	explicit VIBufferTerrain();
public:
	virtual ~VIBufferTerrain();


public :
	void CopyVertexInfoArray(void* _pArray)
	{
		memcpy(_pArray, m_pVertexInfoArray, sizeof(VertexTexture) * m_nVtxNum);
	}


public:
	virtual HRESULT	Init(const int _iCntX, const int _iCntZ, const char* _Path = nullptr);
	virtual void	Update();
	virtual void	Render();
protected:
	virtual void	CreateRasterizerState();
protected:
	virtual void	Release();

protected :
	HRESULT LoadHeightMap(const char* _Path);
	void	NormalizeHeightMap();

	HRESULT	Init_Buffer(const int _iCntX, const int _iCntY);

protected:
	int		m_iWidth;
	int		m_iHeight;

	D3DXVECTOR3* m_pHeightMapTypeInfoArray;

protected :
	VertexTexture * m_pVertexInfoArray;

protected:
	ID3D11Buffer*		m_pLightBuffer;
};


END