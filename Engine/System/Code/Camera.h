#pragma once

#include "Object.h"

BEGIN(Engine)


class ENGINE_DLL Camera abstract : public Object
{
protected:
	explicit Camera();
public:
	virtual ~Camera()	PURE;

private:
	void	Init_Viewport();
	void	Init_ViewBuffer();
	void	Init_ProjBuffer();

protected :
	virtual HRESULT	Init();

public:
	virtual void	Invalidate_View();
	virtual void	Invalidate_Proj();
	virtual void	Invalidate_Ortho();

protected:
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
};


END