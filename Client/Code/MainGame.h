#pragma once

//class CServerMgr;
class CMainGame
{
private:
	class CDevice*		m_pDevice;

	class CSceneMgr*	m_pSceneMgr;
	class CTimer*		m_pTimer;

	class CKeyMgr*		m_pKeyMgr;
	//CServer*		m_pServerMgr;

public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();

public:
	CMainGame();
	~CMainGame();
};

