#include "stdafx.h"
#include "Resource.h"

CResource::CResource(CDevice* _pDevice)
: m_pDevice(_pDevice)
, m_pRefCnt(new WORD(0))
{

}

CResource::~CResource()
{

}

void CResource::Release_RefCnt()
{
	::Safe_Delete(m_pRefCnt);
}
