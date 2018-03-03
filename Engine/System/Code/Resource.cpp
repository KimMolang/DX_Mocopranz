#include "stdafx.h"
#include "Resource.h"

BEGIN(Engine)


Resource::Resource()
	: m_pRefCnt(new WORD(0))
{

}

Resource::~Resource()
{

}

Resource* Resource::Clone()
{
	++(*m_pRefCnt);
	return this;
	//return new T(*this);
}

void Resource::Release_RefCnt()
{
	::Safe_Delete(m_pRefCnt);
}


END