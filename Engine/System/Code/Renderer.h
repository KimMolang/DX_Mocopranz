#pragma once

#include "Scene.h"

BEGIN(Engine)

class GraphicDevice;
class Scene;
class Renderer
{
public:
	explicit Renderer();
	~Renderer(void);

public:
	HRESULT	Init();
	void	Render(Scene* _pScene);


public:
	static DWORD	m_dwFPSCnt;
	static float	m_fTimer;

private:
	GraphicDevice *		m_pGraphicDevice;
};


END