#pragma once

namespace Engine
{
	class GraphicDevice;

	class Timer;
	class KeyChecker;
	class SceneMgr;
}
class MainGame
{
public:
	explicit MainGame();
	~MainGame();

private :
	//std::shared_ptr<Engine::GraphicDevice>	m_pGraphicDevice;
	Engine::GraphicDevice*	m_pGraphicDevice;

	Engine::Timer*			m_pTimer;
	Engine::KeyChecker*		m_pKeyChecker;
	Engine::SceneMgr*		m_pSceneMgr;

public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();
};

