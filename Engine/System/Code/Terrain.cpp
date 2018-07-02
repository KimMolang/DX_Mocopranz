#include "stdafx.h"
#include "Terrain.h"


BEGIN(Engine)


Terrain::Terrain()
	: m_pVtxBuf(nullptr)
	, m_pIdxBuf(nullptr)
{

}

Terrain::Terrain(const Terrain &)
{

}


Terrain::~Terrain()
{

}

HRESULT Terrain::Init()
{
	// for test
	m_iWidth = 100;
	m_iHeight = 100;

	CHECK_FAILED_RETURN(Init_Vtx());
	CHECK_FAILED_RETURN(Init_Idx());

	return S_OK;
}

void Terrain::Update()
{
}

void Terrain::Render()
{
}

void Terrain::Release()
{
}

HRESULT Terrain::Init_Vtx()
{
	// http://www.rastertek.com/tertut01.html

	return S_OK;
}

HRESULT Terrain::Init_Idx()
{
	return S_OK;
}


END