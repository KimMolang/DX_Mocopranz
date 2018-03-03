#include "stdafx.h"
#include "SceneSetter.h"

#include "SceneMgr.h"
#include "Export_Function_Mgr.h"

#include "../Scene/SceneTown.h"

IMPLEMENT_SINGLETON(SceneSetter)


SceneSetter::SceneSetter()
: m_eCurScene(SCENE_ID_NONE)
{
}


SceneSetter::~SceneSetter()
{

}

HRESULT SceneSetter::SetScene(const ESceneID& _eSceneID)
{
	Engine::Scene* pScene = nullptr;

	switch (_eSceneID)
	{
	case SCENE_ID_TOWN:		pScene = new SceneTown();		break;
	default:				return E_FAIL;
	}

	CHECK_NULLPTR_RETURN(pScene, E_FAIL);
	Engine::GetSceneMgr()->SetScene(pScene);

	return S_OK;
}