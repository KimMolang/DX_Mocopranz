/*!
 * \file Camera.h
 * \date 2016/01/30 18:36
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

#ifndef Camera_h__
#define Camera_h__

#include "Obj.h"
//#include "InfoSubject.h"


class CCamera abstract : public CObj
{
protected :
	D3DXMATRIX			m_matView;
	D3DXVECTOR3			m_vEye, m_vAt;
	static const D3DXVECTOR3	m_vUp;

	D3DXMATRIX			m_matProj;
	float				m_fFovy, m_fAspect, m_fNear, m_fFar;

	D3D11_VIEWPORT		m_tViewport;
	
	ID3D11Buffer*		m_pViewBuffer;
	ID3D11Buffer*		m_pProjBuffer;

protected:
	D3DXMATRIX			m_matOrtho;


protected :
	ID3D11DeviceContext*	m_pDeviceContext;
	//CInfoSubject*			m_pInfoSubject;
	

private :
	void	Init_Viewport();
	void	Init_ViewBuffer();
	void	Init_ProjBuffer();

public:
	void	InitInfoSubject();

	void	Invalidate_View();
	void	Invalidate_Proj();
	void	Invalidate_Ortho();

protected:
	explicit CCamera(CDevice* _pDevice);
public :
	virtual ~CCamera()		PURE;
};

#endif // Camera_h__
