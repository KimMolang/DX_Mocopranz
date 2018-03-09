#pragma once

#include "Object.h"


class TestObject : public Engine::Object
{
public:
	explicit TestObject();
	virtual ~TestObject();

public:
	virtual HRESULT					Init();
	virtual Engine::Object::EState	Update();
	virtual void					Render();
	virtual void					Release();
};
