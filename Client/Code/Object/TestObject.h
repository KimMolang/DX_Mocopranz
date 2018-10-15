#pragma once

#include "Object.h"

namespace Engine
{
	class Resource;
}

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

private :
	class Engine::Resource*		m_pShader;
	class Engine::Resource*		m_pBuffer;
};
