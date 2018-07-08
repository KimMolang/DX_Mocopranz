#pragma once

#include "Object.h"

namespace Engine
{
	class Resource;
}

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

private :
	class Engine::Resource*		m_pTexture;
	class Engine::Resource*		m_pBuffer;
};
