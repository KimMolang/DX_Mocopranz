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
	// (고민) 이렇게 얕은 복사 할 거면 그냥 new 하지말고 this 포인터를 넘기는 게 어떨까..?
	// 그러면 m_pRefCnt 이 멤버 변수도 필요없고
	// shard_ptr 쓰면 되잖앙?
}

void Resource::Release_RefCnt()
{
	::Safe_Delete(m_pRefCnt);
}


END