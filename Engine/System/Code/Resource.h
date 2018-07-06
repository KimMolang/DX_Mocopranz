#pragma once

#include "Component.h"

BEGIN(Engine)

#define CLONE(TYPE)			\
virtual TYPE* Clone()		\
{							\
	++(*m_pRefCnt);			\
	return new TYPE(*this);	\
}

class ENGINE_DLL Resource abstract : public Component
{
protected:
	Resource();
public:
	virtual ~Resource() PURE;

public:
	virtual Resource* Clone()	PURE;
	virtual void	Update()	PURE;
	virtual void	Render()	PURE;
protected:
	virtual void	Release();

private:
	void Release_RefCnt();


protected:
	WORD*			m_pRefCnt;
};


END