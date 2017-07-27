/*!
 * \file Struct.h
 * \date 2015/12/06 3:30
 *
 * \author ±è¸íÁö
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef Struct_h__
#define Struct_h__

using namespace std;

struct Buffer_View
{
	D3DXMATRIX			m_matView;
};

struct Buffer_Proj
{
	D3DXMATRIX			m_matProj;
};

struct Buffer_World
{
	D3DXMATRIX			m_matWorld;
};


struct ResourcePath
{
	WORD			wType;
	WORD			wAttri;
	
	short			wEachType;

	wstring			wstrKey;
	wstring			wstrPath;

	ResourcePath()
		: wType(0), wAttri(0)
		, wEachType(-1)
		, wstrKey(L""), wstrPath(L"") {}
};

struct Prefab
{
	wstring		m_wstrROName;

	wstring		m_wstrBufferKey;
	wstring		m_wstrTextureKey;


	Prefab()
		: m_wstrROName(L"")
		, m_wstrBufferKey(L"")
		, m_wstrTextureKey(L"") {}
};

struct ObjInfo
{
	wstring			m_wstrDiviName;

	int				m_iLayerIdx;
	wstring			m_wstrObjKey;
	Prefab			m_tPrefab;

	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vRadian;
	D3DXVECTOR3		m_vScale;

	D3DXVECTOR3		m_vBoxSize;
	D3DXVECTOR3		m_vBoxPlus;

	ObjInfo()
		: m_wstrDiviName(L"")
		, m_iLayerIdx(-1)
		, m_wstrObjKey(L"")
		, m_vPos(0.f, 0.f, 0.f)
		, m_vRadian(0.f, 0.f, 0.f)
		, m_vScale(0.f, 0.f, 0.f)

		, m_vBoxSize(1.f, 1.f, 1.f)
		, m_vBoxPlus(0.f, 0.f, 0.f) {}
};
#endif // Struct_h__