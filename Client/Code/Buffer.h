/*!
 * \file Buffer.h
 * \date 2016/01/24 4:18
 *
 * \author �����
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef Buffer_h__
#define Buffer_h__

#include "Resource.h"

const WORD	BONE_NUM = 8;
const WORD	BONE_MATRIX_NUM = 128;


class CDevice;
class CBuffer abstract : public CResource
{
protected:
	ID3D11RasterizerState*		m_pRasterizerState;

protected: // Vectex
	ID3D11Buffer*		m_pVtxBuffer;
	UINT				m_nVtxNum;
	UINT				m_nVtxStride;
	UINT				m_nVtxOffset;
	UINT				m_nVtxStart;

protected: // Index
	ID3D11Buffer*		m_pIdxBuffer;
	UINT				m_nIdxNum;
	UINT				m_nIdxStart;
	UINT				m_nIdxPlus;


public :
	virtual void	Render();


protected:
	virtual void	CreateRasterizerState();


protected:
	explicit CBuffer(CDevice*);
public :
	virtual ~CBuffer()		PURE;
};


struct VertexColor
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR4		vColor;
};

struct VertexFont
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR2		vTextureUV;

	VertexFont() {}
	VertexFont(D3DXVECTOR3 _vPos, D3DXVECTOR2 _vTextureUV)
		: vPos(_vPos), vTextureUV(_vTextureUV) {}
};

struct VertexTexture
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vNormal;
	D3DXVECTOR2		vTextureUV;

	VertexTexture() {}
	VertexTexture(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vNormal, D3DXVECTOR2 _vTextureUV)
		: vPos(_vPos), vNormal(_vNormal), vTextureUV(_vTextureUV) {}
};

struct VertexAni
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vNormal;
	D3DXVECTOR2		vTextureUV;

	int				iBoneIdx[BONE_NUM];
	float			fBoneWeight[BONE_NUM];

	VertexAni() {}
	VertexAni(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vNormal)
		: vPos(_vPos), vNormal(_vNormal) {}
	VertexAni(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vNormal, D3DXVECTOR2 _vTextureUV)
		: vPos(_vPos), vNormal(_vNormal), vTextureUV(_vTextureUV) {}
	
	void SetPos(float _x, float _y, float _z)		{ vPos.x = _x; vPos.y = _y; vPos.z = _z; }
	void SetNormal(float _x, float _y, float _z)	{ vNormal.x = _x; vNormal.y = _y; vNormal.z = _z; }
	void AddBone(int _iIdx, float _fWeight);
};

struct VertexSkyBox
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR2		vTextureUV;

	VertexSkyBox() {}
	VertexSkyBox(D3DXVECTOR3 _vPos, D3DXVECTOR2 _vTextureUV)
		: vPos(_vPos),  vTextureUV(_vTextureUV) {}
};

struct Index16
{
	WORD	_1, _2, _3;

	Index16(WORD _1, WORD _2, WORD _3) : _1(_1), _2(_2), _3(_3) {}
};

struct Index32
{
	DWORD	_1, _2, _3;

	Index32(DWORD _1, DWORD _2, DWORD _3) : _1(_1), _2(_2), _3(_3) {}
};


#endif // Buffer_h__
