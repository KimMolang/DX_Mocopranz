#pragma once

#include "Scene.h"

class SceneTown : public Engine::Scene
{
public:
	explicit SceneTown();
	virtual ~SceneTown();

private:
	virtual HRESULT		Init();
	virtual void		Update();
	virtual void		Render();
	virtual void		Release();
};

