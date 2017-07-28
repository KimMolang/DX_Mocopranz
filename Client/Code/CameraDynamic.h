/*!
 * \file DynamicCamera.h
 * \date 2016/01/31 9:41
 *
 * \author ±è¸íÁö
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef DynamicCamera_h__
#define DynamicCamera_h__

#include "Camera.h"


class CKeyMgr;
class CTimer;
class CCameraDynamic : public CCamera
{
private :
	CKeyMgr*	m_pKeyMgr;
	CTimer*		m_pTimer;

	float		m_fSpeed;


public :
	static CObj*	Create(CDevice*);

public:
	virtual HRESULT	Init();
	virtual int		Update();
	virtual void	Render();
	virtual void	Release();


private :
	void	CheckKey();
	void	CheckKey_Move(float _fTime);
	void	CheckKey_Rotate(float _fTime);

	void	FixMouse();


public :
	void SetPos(const D3DXVECTOR3& _vEye)	{ m_vEye = _vEye; }


private :
	explicit CCameraDynamic(CDevice*);
public :
	virtual ~CCameraDynamic();
};

#endif // DynamicCamera_h__
