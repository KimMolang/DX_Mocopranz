#pragma once

class CDevice;
class CMainGame
{
public:
	explicit CMainGame();
	~CMainGame();

private :
	std::unique_ptr<CDevice>	m_pDevice;

public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();
};

