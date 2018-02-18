#pragma once

#include "Component.h"

BEGIN(Engine)


class ENGINE_DLL Resource abstract : public Component
{
protected:
	Resource();
public:
	virtual ~Resource() PURE;

public:
	Resource*		Clone();
	virtual void	Update()	PURE;
private:
	virtual void	Release()	PURE;

protected:
	void Release_RefCnt();


protected:
	WORD*					m_pRefCnt;
};


END