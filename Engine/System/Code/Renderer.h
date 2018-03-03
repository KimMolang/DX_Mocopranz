#pragma once

#include "Scene.h"

BEGIN(Engine)

class GraphicDevice;
class Renderer
{
public:
	explicit Renderer();
	~Renderer(void);

public:
	void SetScene(Scene* _pScene) { m_pScene = _pScene; }

public:
	HRESULT	Init();
	void	Render();


public:
	static DWORD	m_dwFPSCnt;
	static float	m_fTimer;

private:
	GraphicDevice *		m_pGraphicDevice;
	Scene*				m_pScene;
};


END