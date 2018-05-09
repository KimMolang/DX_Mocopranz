#pragma once

#include "Scene.h"

BEGIN(Engine)


class ENGINE_DLL SceneLoading : public Scene
{
public:
	explicit SceneLoading();
	virtual ~SceneLoading() PURE;


public:
	virtual HRESULT		Init();
	virtual void		Update();
	virtual void		Render();
	virtual void		Release();


public:
	CRITICAL_SECTION GetCriticalSection() { return m_csCriticalSection; }

private :
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_csCriticalSection;


};


END