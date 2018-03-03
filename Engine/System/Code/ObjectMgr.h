#pragma once

#include "Scene.h"

BEGIN(Engine)


class Layer;
class Object;
class ENGINE_DLL ObjectMgr
{
	DECLARE_SINGLETON(ObjectMgr)

private:
	ObjectMgr();
	~ObjectMgr();

public:
	void SetLayer(Layer* _pLayer_Environment, Layer* _pLayer_GameLogic, Layer* _pLayer_UI)
	{
		m_pLayer[Scene::ELayerType::LAYER_TYPE_BACK] = _pLayer_Environment;
		m_pLayer[Scene::ELayerType::LAYER_TYPE_GAMELOGIC] = _pLayer_GameLogic;
		m_pLayer[Scene::ELayerType::LAYER_TYPE_UI] = _pLayer_UI;
	}

	void AddObj(
		const Scene::ELayerType& _eLayerType
		//, const std::wstring& _wstrObjKey
		, Object* _pObj);

public:
	void Release();


private:
	Layer * m_pLayer[Scene::ELayerType::LAYER_TYPE_MAX];

};


END