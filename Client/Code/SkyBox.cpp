#include "stdafx.h"
#include "SkyBox.h"

#include "ResourceMgr.h"
#include "Texture.h"
#include "BufferSkyBox.h"

//#include "CameraObserver.h"


CSkyBox::CSkyBox(CDevice* _pDevice)
: CBackGround(_pDevice)
, m_pTexture(nullptr)
, m_pTargetPos(nullptr)
//, m_pCameraObserver(nullptr)
{

}

CSkyBox::~CSkyBox()
{
	Release();
}

CObj* CSkyBox::Create(CDevice* _pDevice, const wstring& _wstrTextureKey)
{
	CObj* pObj = new CSkyBox(_pDevice);
	if (FAILED(pObj->Init()))
		::Safe_Delete(pObj);

	((CSkyBox*)pObj)->AddComponent(_wstrTextureKey);

	return pObj;
}

void CSkyBox::AddComponent(const wstring& _wstrTextureKey)
{
	// Texture ---------------
	m_pTexture = dynamic_cast<CTexture*>(
		CResourceMgr::GetInstance()->CloneResource(
		CResourceMgr::RESOURCE_ATTRI_DYNAMIC, CResourceMgr::RESOURCE_TYPE_TEXTURE, _wstrTextureKey));
	NULL_CHECK(m_pTexture);
	m_mapComponent.insert(make_pair(L"Texture", m_pTexture));


	// Plan Buffer ---------------------
	m_pBuffer = dynamic_cast<CBufferSkyBox*>(CResourceMgr::GetInstance()->CloneResource(
		CResourceMgr::RESOURCE_ATTRI_DYNAMIC, CResourceMgr::RESOURCE_TYPE_BUFFER, L"Buffer_SkyBox"));
	NULL_CHECK(m_pBuffer);
	m_mapComponent.insert(make_pair(L"Buffer", m_pBuffer));
}

HRESULT CSkyBox::Init()
{
	m_eObjState = CObj::OBJ_STATE_ALIVE;
	//m_pCameraObserver = CCameraObserver::Create();
	//CInfoSubject::GetInstance()->Subscribe(m_pCameraObserver);

	return S_OK;
}

int CSkyBox::Update()
{
	//m_pPhysics->m_vPos = m_pCameraObserver->GetEye();
	CObj::Update_Component();


	return m_eObjState;
}

void CSkyBox::Render()
{
	m_pPhysics->Render();
	m_pTexture->Render();
	m_pBuffer->Render();
}

void CSkyBox::Release()
{
	//CInfoSubject::GetInstance()->Unsubscribe(m_pCameraObserver);
	//::Safe_Delete(m_pCameraObserver);
}

