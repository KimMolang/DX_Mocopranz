#include "stdafx.h"
#include "CameraStatic.h"

#include "Timer.h"
#include "KeyChecker.h"
#include "Export_Function_Mgr.h"

BEGIN(Engine)


const float CameraStatic::MAX_ZOOM_VALUE = 5.f;
const float CameraStatic::MIN_ZOOM_VALUE = 2.f;


CameraStatic* CameraStatic::Create()
{
	CameraStatic* pObject = new CameraStatic();
	if (FAILED(pObject->Init()))
		::Safe_Delete(pObject);

	return pObject;
}

CameraStatic::CameraStatic()
	: /*m_pTargetPhysics(NULL) // (수정) Transform

	,*/ m_eWheelEvent(WHEEL_EVENT_NONE)
	, m_fTargetZoom(0.f)

	, m_fZoom(0.f)
{

}

CameraStatic::~CameraStatic()
{
	Release();
}

HRESULT CameraStatic::Init()
{
	Camera::Init();

	m_fZoom = MAX_ZOOM_VALUE;
	m_fTargetZoom = MIN_ZOOM_VALUE;
	//m_fTargetZoom = m_fZoom;


	return S_OK;
}

Object::EState CameraStatic::Update()
{
	CheckKey();
	MoveToTarget();
	AnimatingWheel();
	Camera::Invalidate_View();


	return m_eObjState;
}

void CameraStatic::Render()
{
}

void CameraStatic::Release()
{

}

void CameraStatic::CheckKey()
{
	int		iDistance = 0;
	float	fTime = GetTimer()->GetTime();

	if (iDistance = GetKeyChecker()->GetDIMouseMove(KeyChecker::MOUSE_MOVE_Z))
	{
		m_fTargetZoom -= iDistance * fTime;

		if (m_fTargetZoom > MAX_ZOOM_VALUE)
			m_fTargetZoom = MAX_ZOOM_VALUE;
		else if (m_fTargetZoom < MIN_ZOOM_VALUE)
			m_fTargetZoom = MIN_ZOOM_VALUE;
	}
}

void CameraStatic::MoveToTarget()
{
	// (수정) Transform
	//if (m_pTargetPhysics == NULL)
	//	return;

	////const static float	DISTANCE_VALUE_EYE = 6.f;
	////const static float	DISTANCE_VALUE_EYE_Y = 12.f;
	////const static float	DISTANCE_VALUE_AT_Y = 9.f;


	////m_vEye = m_pTargetPhysics->m_vPos + (-(m_pTargetPhysics->m_vDir) * DISTANCE_VALUE_EYE * m_fZoom);
	////m_vEye.y += DISTANCE_VALUE_EYE_Y;

	////m_vAt = m_pTargetPhysics->m_vPos;
	////m_vAt.y += DISTANCE_VALUE_AT_Y;


	//const static float	DISTANCE_VALUE_EYE = 10.f;
	//const static float	DISTANCE_VALUE_AT_Y = 12.f;

	//m_vEye = -(m_pTargetPhysics->m_vDir) * DISTANCE_VALUE_EYE * m_fZoom;

	//D3DXVECTOR3		vTargetRight;
	//memcpy(&vTargetRight, &(m_pTargetPhysics->m_matWorld.m[0][0]), sizeof(D3DXVECTOR3));

	//D3DXMATRIX		matRotAxis;
	//D3DXMatrixRotationAxis(&matRotAxis, &vTargetRight, D3DXToRadian(30.f));
	//D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	//m_vAt = m_pTargetPhysics->m_vPos;
	//m_vAt.y += DISTANCE_VALUE_AT_Y;
	//m_vEye += m_pTargetPhysics->m_vPos;
}

void CameraStatic::AnimatingWheel()
{
	//const float SPEED_WHEEL = 10.f;
	const float SPEED_WHEEL = 8.f;

	if (m_fZoom == m_fTargetZoom)		m_eWheelEvent = WHEEL_EVENT_NONE;
	else if (m_fZoom < m_fTargetZoom)	m_eWheelEvent = WHEEL_EVENT_UP;
	else if (m_fZoom > m_fTargetZoom)	m_eWheelEvent = WHEEL_EVENT_DOWN;


	switch (m_eWheelEvent)
	{
	case WHEEL_EVENT_NONE:
		break;

	case WHEEL_EVENT_UP:
		if (m_fZoom < MAX_ZOOM_VALUE)
			m_fZoom += SPEED_WHEEL * GetTimer()->GetTime();
		if (m_fZoom > m_fTargetZoom)
		{
			m_eWheelEvent = WHEEL_EVENT_NONE;
			m_fZoom = m_fTargetZoom;
		}
		break;

	case WHEEL_EVENT_DOWN:
		if (m_fZoom > MIN_ZOOM_VALUE)
			m_fZoom -= SPEED_WHEEL * GetTimer()->GetTime();
		if (m_fZoom < m_fTargetZoom)
		{
			m_eWheelEvent = WHEEL_EVENT_NONE;
			m_fZoom = m_fTargetZoom;
		}
		break;
	}
}


END