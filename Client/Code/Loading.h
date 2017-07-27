#pragma once
#include "Scene.h"
#include "SceneMgr.h"


class CDevice;
class CLoading : public CScene
{
private :
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_tCriticalSection;

public :
	CRITICAL_SECTION GetCriticalSection()	{ return m_tCriticalSection; }


public :
	static CLoading*	Create(CDevice*);

private:
	HRESULT		AddLayer_Environment();
	HRESULT		AddLayer_GameLogic();
	HRESULT		AddLayer_UI();

public:
	virtual HRESULT		Init();
	virtual void		Update();
	virtual void		Render();
	virtual void		Release();

private:
	explicit CLoading(CDevice*);
public :
	virtual ~CLoading();
};

