#include "stdafx.h"
#include "Resource.h"

BEGIN(Engine)


Resource::Resource()
	: m_pRefCnt(new WORD(0))
{

}

Resource::~Resource()
{
	Release();
}

void Resource::Release()
{
	if ((*m_pRefCnt) == 0)
	{
		Release_RefCnt();
	}
	else --(*m_pRefCnt);
}

void Resource::Release_RefCnt()
{
	::Safe_Delete(m_pRefCnt);
}


END