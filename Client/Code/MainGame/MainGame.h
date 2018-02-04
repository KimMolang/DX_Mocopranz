#pragma once

namespace Engine
{
	class GraphicDevice;
}
class MainGame
{
public:
	explicit MainGame();
	~MainGame();

private :
	//std::shared_ptr<Engine::GraphicDevice>	m_pGraphicDevice;
	Engine::GraphicDevice*	m_pGraphicDevice;

public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();
};

