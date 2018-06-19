#pragma once

#include "Scene.h"

BEGIN(Engine)


class ENGINE_DLL SceneLoading abstract : public Scene
{
public :
	enum class ELoadingState
	{
		LOADING_STATE_READY,
		LOADING_STATE_LOADING,
		LOADING_STATE_END,

		LOADING_STATE_CHANGE_SCENE // : You have to release this scene and then set new(next) scene.
	};

public:
	explicit SceneLoading();
	virtual ~SceneLoading() PURE;


public:
	virtual HRESULT		Init();
	virtual HRESULT		StartLoading();
	virtual void		Update();
	virtual void		Render();
	virtual void		Release();


public:
	ELoadingState GetLoadingState() { return m_eLoadingState; }


private:
	CRITICAL_SECTION GetCriticalSection() { return m_csCriticalSection; }
private:
	static unsigned int	__stdcall StartLoading(void* _pArg);
private:
	virtual void DoBeforeLoading() {}	// ex) Load the Loading Img for Render during the Load
	virtual void LoadContens() PURE;	// Contents of Loading
	virtual void DoAfterLoading() {}	// ex) Release the Loading Img for Render during the Load


private :
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_csCriticalSection;

	ELoadingState			m_eLoadingState;
};


END