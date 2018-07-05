#pragma once

#include "Object.h"


class TestTerrain : public Engine::Object
{
public:
	explicit TestTerrain();
	virtual ~TestTerrain();

public:
	virtual HRESULT					Init();
	virtual Engine::Object::EState	Update();
	virtual void					Render();
	virtual void					Release();
};
