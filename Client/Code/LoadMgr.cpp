#include "stdafx.h"
#include "LoadMgr.h"

#include "ResourceMgr.h"
#include <fstream>

//#include "Player.h"
#include "CameraDynamic.h"
//#include "CameraStatic.h"
//#include "Floor.h"
//#include "SkyBox.h"
//#include "Decoration.h"
//#include "DirectionSign.h"
//
//#include "Item.h"
//#include "BoosterZone.h"
//#include "UnMovableZone.h"
//#include "ProgressRateZone.h"
//
//#include "Status.h"
//#include "TargetBox.h"
//#include "Ammo.h"
//#include "Grade.h"
//#include "ProgressRate.h"
//#include "Notify.h"
//
//#include "InMapMgr.h"
//#include "ProgressMgr.h"

IMPLEMENT_SINGLETON(CLoadMgr)


CLoadMgr::CLoadMgr()
{

}

CLoadMgr::~CLoadMgr()
{
	RemoveFontResourceEx(L"../bin/Resource/Font/HANSomaB.ttf", FR_PRIVATE, NULL);
}

HRESULT CLoadMgr::LoadResource(CDevice* _pDevice,
								const CSceneMgr::SceneID& _eSceneID)
{
	CResourceMgr* pResourceMgr = CResourceMgr::GetInstance();


	switch (_eSceneID)
	{
	case CSceneMgr::SCENE_ID_TITLE:
		break;

	case CSceneMgr::SCENE_ID_LOBBY:
		break;

	case CSceneMgr::SCENE_ID_ROOM:
		break;

	case CSceneMgr::SCENE_ID_INMAP:

		pResourceMgr->Add_Shader(_pDevice, CResourceMgr::RESOURCE_ATTRI_STATIC,
			CResourceMgr::SHADER_TYPE_COLOR, L"Shader_Color");
		pResourceMgr->Add_Shader(_pDevice, CResourceMgr::RESOURCE_ATTRI_STATIC,
			CResourceMgr::SHADER_TYPE_TEXTURE, L"Shader_Texture");
		pResourceMgr->Add_Shader(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
			CResourceMgr::SHADER_TYPE_SKYBOX, L"Shader_SkyBox");
		pResourceMgr->Add_Shader(_pDevice, CResourceMgr::RESOURCE_ATTRI_STATIC,
			CResourceMgr::SHADER_TYPE_ANI, L"Shader_Ani");

		pResourceMgr->Add_Buffer(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
			CResourceMgr::BUFFER_TYPE_CUBE, L"Buffer_Cube");
		pResourceMgr->Add_Buffer(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
			CResourceMgr::BUFFER_TYPE_PLAN, L"Buffer_Plan");
		pResourceMgr->Add_Buffer(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
			CResourceMgr::BUFFER_TYPE_SKYBOX, L"Buffer_SkyBox");
		pResourceMgr->Add_Buffer(_pDevice, CResourceMgr::RESOURCE_ATTRI_STATIC,
			CResourceMgr::BUFFER_TYPE_UI, L"Buffer_UI");


		// 스카이박스 텍스쳐는 파일로 읽어 드렸었네??
		// 내가 근데 이거 왜 다이나믹 리소스로 해놨징?
		pResourceMgr->Add_Texture(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
			CTexture::TEXTURE_TYPE_DDS, L"Texture_SkyBox_00", L"./bin/Resource/Texture/SkyBox/SkyBox_01.dds");

//		AddFontResourceEx(L"../bin/Resource/Font/HANSomaB.ttf", FR_PRIVATE, NULL);
//		pResourceMgr->Add_Font(_pDevice, CResourceMgr::RESOURCE_ATTRI_STATIC,
//			L"Font_HANSomaB", L"한컴 소망 B");
//
//		LoadResourceByFile(_pDevice, LOAD_RESOURCE_TYPE_TEXTURE, L"../bin/Data/ResourcePath/TexturePath_InMap.txt");
//
//#ifdef _DEBUG
//		if (!(g_dwClientDebugMode & CLIENT_DEBUG_MODE_NO_ANIMATION))
//#endif
//			LoadResourceByFile(_pDevice, LOAD_RESOURCE_TYPE_ANI, L"../bin/Data/ResourcePath/AniPath_InMap.txt");
//
//#ifdef _DEBUG
//		if (!(g_dwClientDebugMode & CLIENT_DEBUG_MODE_NO_BG))
//			LoadResourceByFile(_pDevice, LOAD_RESOURCE_TYPE_MODEL, L"../bin/Data/ResourcePath/ModelPath_InMap.txt");
//#else
//		LoadResourceByFile(_pDevice, LOAD_RESOURCE_TYPE_MODEL, L"../bin/Data/ResourcePath/ModelPath_InMap.txt");
//#endif

		break;

	default:
		break;
	}

	return S_OK;
}

//HRESULT CLoadMgr::LoadResourceByFile(CDevice* _pDevice,
//									const LoadResourceType& _eLoadResourceType,
//									const wstring& _wstrPath)
//{
//	wifstream	tLoadFile;
//	tLoadFile.open(_wstrPath.c_str(), ios::in);
//
//	TCHAR		szType[MIN] = L"";
//	TCHAR		szAttri[MIN] = L"";
//
//	TCHAR		szEachType[MIN] = L"";
//
//	TCHAR		szKey[MIN] = L"";
//	TCHAR		szPath[MAX_PATH] = L"";
//
//	vector<string> vecAniName;
//	TCHAR		szAniName[MIN] = L"";
//	TCHAR		szAniNum[MIN] = L"";
//	int			iAniNum;
//
//
//	CResourceMgr* pResourceMgr = CResourceMgr::GetInstance();
//
//	switch (_eLoadResourceType)
//	{
//	case LOAD_RESOURCE_TYPE_MODEL:
//
//		while (!tLoadFile.eof())
//		{
//			tLoadFile.getline(szType, MIN, '\t');
//			tLoadFile.getline(szAttri, MIN, '\t');
//
//			tLoadFile.getline(szEachType, MIN, '\t');
//
//			tLoadFile.getline(szKey, MIN, '\t');
//			tLoadFile.getline(szPath, MAX_PATH);
//
//			char cModelPath[MAX_PATH];
//			WideCharToMultiByte(CP_ACP, 0, szPath, MAX_PATH, cModelPath, MAX_PATH, NULL, NULL);
//
//			pResourceMgr->Add_Model(_pDevice, (CResourceMgr::ResourceAttri)_ttoi(szAttri),
//				CResourceMgr::MODEL_TYPE_STATIC, szKey, cModelPath);
//		}
//		break;
//
//	case LOAD_RESOURCE_TYPE_TEXTURE:
//
//		while (!tLoadFile.eof())
//		{
//			tLoadFile.getline(szType, MIN, '\t');
//			tLoadFile.getline(szAttri, MIN, '\t');
//
//			tLoadFile.getline(szEachType, MIN, '\t');
//
//			tLoadFile.getline(szKey, MIN, '\t');
//			tLoadFile.getline(szPath, MAX_PATH);
//
//
//			pResourceMgr->Add_Texture(_pDevice, (CResourceMgr::ResourceAttri)_ttoi(szAttri),
//				(CTexture::TextureType)_ttoi(szEachType), szKey, szPath);
//		}
//
//		break;
//
//	case LOAD_RESOURCE_TYPE_ANI :
//
//		while (!tLoadFile.eof())
//		{
//			tLoadFile.getline(szKey, MIN, '\t');
//			tLoadFile.getline(szPath, MAX_PATH, '\t');
//			tLoadFile.getline(szAniNum, MIN);
//
//			char cModelPath[MAX_PATH];
//			WideCharToMultiByte(CP_ACP, 0, szPath, MAX_PATH, cModelPath, MAX_PATH, NULL, NULL);
//
//			vecAniName.clear();
//			iAniNum = _ttoi(szAniNum);
//
//
//			for (int i = 0; i < iAniNum; ++i)
//			{
//				tLoadFile.getline(szAniName, MIN);
//
//				char cAniName[MIN];
//				WideCharToMultiByte(CP_ACP, 0, szAniName, MIN, cAniName, MIN, NULL, NULL);
//
//				vecAniName.push_back(cAniName);
//			}
//
//			pResourceMgr->Add_Model(_pDevice, CResourceMgr::RESOURCE_ATTRI_DYNAMIC,
//				CResourceMgr::MODEL_TYPE_DYNAMIC, szKey, cModelPath, vecAniName);
//		}
//		break;
//
//	default:
//		break;
//	}
//	return S_OK;
//}
//
//void CLoadMgr::LoadUI(CDevice* _pDevice,
//					const CSceneMgr::SceneID& _eSceneID,
//					CLayer** _ppLayer_UI)
//{
//	CObj* pObj = NULL;
//
//	switch (_eSceneID)
//	{
//	case CSceneMgr::SCENE_ID_TITLE:
//		break;
//
//	case CSceneMgr::SCENE_ID_LOBBY:
//		break;
//
//	case CSceneMgr::SCENE_ID_ROOM:
//		break;
//
//	case CSceneMgr::SCENE_ID_INMAP:
//		pObj = CNotify::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//		CInMapMgr::GetInstance()->SetUI_Notify((CNotify*)pObj);
//
//		pObj = CTargetBox::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//
//		pObj = CStatus::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//
//		pObj = CAmmo::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//
//		pObj = CGrade::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//		CInMapMgr::GetInstance()->SetUI_Grade((CGrade*)pObj);
//
//		pObj = CProgressRate::Create(_pDevice);
//		NULL_CHECK(pObj);
//		(*_ppLayer_UI)->AddObj(L"UI", pObj);
//		break;
//
//	default:
//		break;
//	}
//}
//
//void CLoadMgr::LoadMap(CDevice* _pDevice,
//						const MapType& _eMapType,
//						CLayer** _ppLayer_Environment,
//						CLayer** _ppLayer_GameLogic)
//{
//	wstring wstrMapDataPath = L"";
//
//	switch (_eMapType)
//	{
//	case MAP_TYPE_THEGOREST :
//
//#ifdef _DEBUG
//		if (!(g_dwClientDebugMode & CLIENT_DEBUG_MODE_NO_BG))
//			wstrMapDataPath = L"../bin/Data/Map/TheGorest.dat";
//#else
//		wstrMapDataPath = L"../bin/Data/Map/TheGorest.dat";
//#endif
//
//		break;
//
//	default : return;
//	}
//
//	HANDLE		hFile = CreateFile(
//		wstrMapDataPath.c_str(),
//		GENERIC_READ,
//		0,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//
//
//	DWORD		dwByte = 0;
//	ObjInfo		tObjInfo;
//	CObj*		pObj = NULL;
//
//	TCHAR		szDiviName[MIN] = L"";
//	TCHAR		szObjKey[MIN] = L"";
//
//	TCHAR		szROName[MIN] = L"";
//	TCHAR		szBufferKey[MIN] = L"";
//	TCHAR		szTextureKey[MIN] = L"";
//
//
//	while (true)
//	{
//		ReadFile(hFile, &szDiviName, sizeof(TCHAR)* MIN, &dwByte, NULL);
//
//		if (0 == dwByte)
//			break;
//
//
//		ReadFile(hFile, &szObjKey, sizeof(TCHAR)* MIN, &dwByte, NULL);
//		ReadFile(hFile, &szROName, sizeof(TCHAR)* MIN, &dwByte, NULL);
//		ReadFile(hFile, &szBufferKey, sizeof(TCHAR)* MIN, &dwByte, NULL);
//		ReadFile(hFile, &szTextureKey, sizeof(TCHAR)* MIN, &dwByte, NULL);
//
//		ReadFile(hFile, &(tObjInfo.m_iLayerIdx), sizeof(int), &dwByte, NULL);
//		ReadFile(hFile, &(tObjInfo.m_vPos), sizeof(D3DXVECTOR3), &dwByte, NULL);
//		ReadFile(hFile, &(tObjInfo.m_vRadian), sizeof(D3DXVECTOR3), &dwByte, NULL);
//		ReadFile(hFile, &(tObjInfo.m_vScale), sizeof(D3DXVECTOR3), &dwByte, NULL);
//
//		ReadFile(hFile, &(tObjInfo.m_vBoxSize), sizeof(D3DXVECTOR3), &dwByte, NULL);
//		ReadFile(hFile, &(tObjInfo.m_vBoxPlus), sizeof(D3DXVECTOR3), &dwByte, NULL);
//
//		tObjInfo.m_wstrDiviName = szDiviName;
//		tObjInfo.m_wstrObjKey = szObjKey;
//		tObjInfo.m_tPrefab.m_wstrROName = szROName;
//		tObjInfo.m_tPrefab.m_wstrBufferKey = szBufferKey;
//		tObjInfo.m_tPrefab.m_wstrTextureKey = szTextureKey;
//
//
//		switch ((CLayer::LayerType)tObjInfo.m_iLayerIdx)
//		{
//		case CLayer::LAYERTYPE_ENVIRONMENT:
//			if (L"Floor" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CFloor::Create(_pDevice, tObjInfo.m_tPrefab.m_wstrTextureKey);
//
//				((CBackGround*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian, tObjInfo.m_vScale);
//				(*_ppLayer_Environment)->AddObj(L"Floor", pObj);
//			}
//			else if (L"SkyBox" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CSkyBox::Create(_pDevice, tObjInfo.m_tPrefab.m_wstrTextureKey);
//
//				((CBackGround*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian, tObjInfo.m_vScale);
//				(*_ppLayer_Environment)->AddObj(L"SkyBox", pObj);
//			}
//			else if (L"Decoration" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CDecoration::Create( _pDevice,
//					tObjInfo.m_tPrefab.m_wstrTextureKey, tObjInfo.m_tPrefab.m_wstrBufferKey);
//
//				((CBackGround*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian, tObjInfo.m_vScale);
//				(*_ppLayer_Environment)->AddObj(L"Decoration", pObj);
//			}
//			break;
//
//		case CLayer::LAYERTYPE_GAMELOGIC:
//			if (L"BoosterZone" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CBoosterZone::Create(_pDevice);
//
//				((CBoosterZone*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian);
//				(*_ppLayer_GameLogic)->AddObj(L"BoosterZone", pObj);
//			}
//			else if (L"Item" == tObjInfo.m_wstrObjKey)
//			{
//				if(L"Texture_Item_Full" == tObjInfo.m_tPrefab.m_wstrTextureKey)
//					pObj = CItem::Create(_pDevice, CItem::ITEM_TYPE_FULL);
//				else pObj = CItem::Create(_pDevice, CItem::ITEM_TYPE_THIRD);
//
//				((CItem*)pObj)->SetWorldMatrix(tObjInfo.m_vPos);
//				(*_ppLayer_GameLogic)->AddObj(L"Item", pObj);
//				CInMapMgr::GetInstance()->PushBackItem(pObj);
//			}
//			else if (L"UnmovableZone" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CUnMovableZone::Create(_pDevice);
//
//				((CUnMovableZone*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian);
//				((CTrigger*)pObj)->SetObjColScale(tObjInfo.m_vBoxSize);
//				((CTrigger*)pObj)->SetObjColPlusPos(tObjInfo.m_vBoxPlus);
//				(*_ppLayer_GameLogic)->AddObj(L"UnmovableZone", pObj);
//			}
//			else if (L"ProgressRateZone" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CProgressRateZone::Create(_pDevice);
//
//				((CProgressRateZone*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian);
//				((CTrigger*)pObj)->SetObjColScale(tObjInfo.m_vBoxSize);
//				((CTrigger*)pObj)->SetObjColPlusPos(tObjInfo.m_vBoxPlus);
//				(*_ppLayer_GameLogic)->AddObj(L"ProgressRateZone", pObj);
//
//				CProgressMgr::GetInstance()->PushBackProrate(pObj);
//			}
//			else if (L"DirectionSign" == tObjInfo.m_wstrObjKey)
//			{
//				pObj = CDirectionSign::Create(_pDevice);
//
//				((CDirectionSign*)pObj)->SetWorldMatrix(tObjInfo.m_vPos, tObjInfo.m_vRadian);
//				(*_ppLayer_Environment)->AddObj(L"Decoration", pObj);
//			}
//			break;
//
//		default:
//			break;
//		}
//	}
//
//
//	CloseHandle(hFile);
//}
//
