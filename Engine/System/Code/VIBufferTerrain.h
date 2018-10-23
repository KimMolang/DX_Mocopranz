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

public :
	inline float GetTerrainWidth() { return (float)m_iBoxNumX; /** (float)m_iBoxSizeX;*/ }
	inline float GetTerrainDepth() { return (float)m_iBoxNumZ; /** (float)m_iBoxSizeZ;*/ }
	GET(int, BoxNumX, m_iBoxNumX);
	GET(int, BoxNumZ, m_iBoxNumZ);
	//GET(int, BoxSizeX, m_iBoxSizeX);
	//GET(int, BoxSizeZ, m_iBoxSizeZ);


protected :
	HRESULT LoadHeightMap(const char* _Path);
	void	NormalizeHeightMap();

	HRESULT	Init_Buffer(const int _iCntX, const int _iCntY);

protected:
	int		m_iHeighMapImgWidth;
	int		m_iHeighMapImgHeight;

	D3DXVECTOR3* m_pHeightMapTypeInfoArray;

protected :
	VertexTexture * m_pVertexInfoArray;
	//int m_iBoxSizeX, m_iBoxSizeZ;
	int m_iBoxNumX, m_iBoxNumZ;

protected:
	ID3D11Buffer*		m_pLightBuffer;
};


END