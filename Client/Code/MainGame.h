#pragma once

//class CServerMgr;
class CMainGame
{
private:
	// (수정) 아래에 있는 것들 다 Mgr로 할 필요없다!
	// 싱글톤일 이유가 없엉
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

