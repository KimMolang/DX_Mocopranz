#include "stdafx.h"
#include "CameraDynamic.h"

#include "Timer.h"
#include "KeyChecker.h"
#include "Export_Function_Mgr.h"

BEGIN(Engine)


CameraDynamic* CameraDynamic::Create()
{
	CameraDynamic* pObject = new CameraDynamic();
	if (FAILED(pObject->Init()))
		::Safe_Delete(pObject);

	return pObject;
}

CameraDynamic::CameraDynamic()
	: m_fSpeed(0.f)
{

}

CameraDynamic::~CameraDynamic()
{
	Release();
}

HRESULT CameraDynamic::Init()
{
	Camera::Init();

	m_fSpeed = 50.f;


	return S_OK;
}

Object::EState CameraDynamic::Update()
{
	CheckKey();
	//FixMouse();
	Camera::Invalidate_View();

	return m_eObjState;
}

void CameraDynamic::Render()
{

}

void CameraDynamic::Release()
{

}

void CameraDynamic::CheckKey()
{
	float fTime = GetTimer()->GetTime();

	CheckKey_Move(fTime);
	CheckKey_Rotate(fTime);
}

void CameraDynamic::CheckKey_Move(float _fTime)
{
	if (GetKeyChecker()->CheckKeyboardPress(DIK_A))
	{
		D3DXVECTOR3		vRight;
		D3DXMATRIX		matCamState;

		D3DXMatrixInverse(&matCamState, NULL, &m_matView);
		memcpy(&vRight, &matCamState.m[0][0], sizeof(D3DXVECTOR3));
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye -= vRight * m_fSpeed * _fTime;
		m_vAt -= vRight * m_fSpeed * _fTime;
	}

	if (GetKeyChecker()->CheckKeyboardPress(DIK_D))
	{
		D3DXVECTOR3		vRight;
		D3DXMATRIX		matCamState;

		D3DXMatrixInverse(&matCamState, NULL, &m_matView);
		memcpy(&vRight, &matCamState.m[0][0], sizeof(D3DXVECTOR3));
		D3DXVec3Normalize(&vRight, &vRight);

		m_vEye += vRight * m_fSpeed * _fTime;
		m_vAt += vRight * m_fSpeed * _fTime;
	}

	if (GetKeyChecker()->CheckKeyboardPress(DIK_W))
	{
		D3DXVECTOR3		vLook;
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);

		m_vEye += vLook * m_fSpeed * _fTime;
		m_vAt += vLook * m_fSpeed * _fTime;
	}

	if (GetKeyChecker()->CheckKeyboardPress(DIK_S))
	{
		D3DXVECTOR3		vLook;
		vLook = m_vAt - m_vEye;
		D3DXVec3Normalize(&vLook, &vLook);

		m_vEye -= vLook * m_fSpeed * _fTime;
		m_vAt -= vLook * m_fSpeed * _fTime;
	}
}

void CameraDynamic::CheckKey_Rotate(float _fTime)
{
	int		iDistance = 0;

	if (iDistance = GetKeyChecker()->GetDIMouseMove(KeyChecker::MOUSE_MOVE_X))
	{
		D3DXMATRIX		matAxis;
		D3DXMatrixRotationY(&matAxis, (float)D3DXToRadian(iDistance / 10.f));

		D3DXVECTOR3		vDir;
		vDir = m_vAt - m_vEye;
		D3DXVec3TransformNormal(&vDir, &vDir, &matAxis);

		m_vAt = m_vEye + vDir;
	}

	if (iDistance = GetKeyChecker()->GetDIMouseMove(KeyChecker::MOUSE_MOVE_Y))
	{
		D3DXVECTOR3		vRight;
		D3DXMATRIX		matViewInverse;

		D3DXMatrixInverse(&matViewInverse, NULL, &m_matView);
		memcpy(&vRight, &matViewInverse.m[0][0], sizeof(D3DXVECTOR3));
		D3DXVec3Normalize(&vRight, &vRight);

		D3DXMATRIX		matAxis;
		D3DXMatrixRotationAxis(&matAxis, &vRight, (float)D3DXToRadian(iDistance / 10.f));

		D3DXVECTOR3		vDir;
		vDir = m_vAt - m_vEye;
		D3DXVec3TransformNormal(&vDir, &vDir, &matAxis);

		m_vAt = m_vEye + vDir;
	}
}

//void CameraDynamic::FixMouse()
//{
//	//POINT	ptMouse = { ::CLIENT_WINCX >> 1, ::CLIENT_WINCY >> 1 }; // (수정) (옵션) 해상도
//	POINT	ptMouse = { 1280 >> 1, 720 >> 1 };
//	ClientToScreen(g_hWnd, &ptMouse);
//	SetCursorPos(ptMouse.x, ptMouse.y);
//}


END