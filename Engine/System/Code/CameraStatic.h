#pragma once

#include "Camera.h"

BEGIN(Engine)


class ENGINE_DLL CameraStatic : public Camera
{
public:
	static CameraStatic* Create();
private:
	explicit CameraStatic();
public:
	virtual ~CameraStatic();

private:
	enum EWheelEvent
	{
		WHEEL_EVENT_NONE,

		WHEEL_EVENT_UP,
		WHEEL_EVENT_DOWN
	};

public:
	const static float	MAX_ZOOM_VALUE;
	const static float	MIN_ZOOM_VALUE;


public: // (수정) Transform
	//void SetTargetPhysics(CPhysics* _pTargetPhysics) { m_pTargetPhysics = _pTargetPhysics; }

public:
	virtual HRESULT			Init();
	virtual Object::EState	Update();
	virtual void			Render();
	virtual void			Release();


private:
	void	CheckKey();
	void	MoveToTarget();
	void	AnimatingWheel();


private:
	// (수정) Transform
	//Physics*		m_pTargetPhysics;

private:
	EWheelEvent			m_eWheelEvent;
	float				m_fTargetZoom;
	float				m_fZoom;
};


END