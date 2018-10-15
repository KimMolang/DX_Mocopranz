#pragma once

#include "Object.h"

namespace Engine
{
	class Component;
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
	// ComponentNull ��� �����մϴ�
	class Engine::Component*		m_pTexture;
	class Engine::Component*		m_pShader;
	class Engine::Component*		m_pBuffer;
};
