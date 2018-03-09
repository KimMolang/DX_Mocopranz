#pragma once

#include "Object.h"


class TestObject abstract : public Engine::Object
{
protected:
	explicit TestObject();
public:
	virtual ~TestObject();

protected:
	virtual HRESULT					Init();
	virtual Engine::Object::EState	Update();
	virtual void					Render();
	virtual void					Release();
};
