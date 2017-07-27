/*!
* \file Physics.h
* \date 2016/01/21 4:56
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

#ifndef Physics_h__
#define Physics_h__

#include "Component.h"

class CPhysics : public CComponent
{
public :
	enum PhysicsType { STATIC, DYNAMIC };

public :
	class CDevice*		m_pDevice;
	ID3D11Buffer*	m_pWorldBuffer;
	PhysicsType	m_eType;

public:
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;
	D3DXVECTOR3		m_vRadian;

	D3DXMATRIX		m_matWorld;

	float			m_fSpeed;
	float			m_fAccel;
	float			m_fWeight;

	float			m_fAcctime;

	float			m_fBoosterTimer;


public :
	D3DXVECTOR3		m_vScale;


public:
	static CComponent*		Create(CDevice*);
public :
	void					Init();
	virtual void			Update();
	void					Render();
	void					AvoidPhysics(float _fTime);

	float					BounceDecel(float _fTime);
	void					BoosterAccel(float _fTime);

private:
	virtual void			Release();


private:
	void Init_WorldBuffer();

public :
	void SetWorldMatrix(const D3DXVECTOR3& _vPos,
		const D3DXVECTOR3& _vRadian, const D3DXVECTOR3& _vScale = D3DXVECTOR3(1.f, 1.f, 1.f));
	void Update_WorldMatrix();


public:
	explicit CPhysics(CDevice*);
	virtual ~CPhysics();
};

#endif // Physics_h__
