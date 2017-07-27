/*!
 * \file Obj.h
 * \date 2016/01/11 4:10
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

#ifndef Obj_h__
#define Obj_h__

#include "Include.h"
#include "Physics.h"


class CComponent;
class CObj
{
public :
	enum ObjState
	{
		OBJ_STATE_NONE,

		OBJ_STATE_IDLE,
		OBJ_STATE_ALIVE,
		OBJ_STATE_DIE
	};


public :
	static bool			m_bRenderObjCol_ProgressRateZone;
	static bool			m_bRenderObjCol_UnMovableZone;
	static bool			m_bRenderObjCol_Other;

protected:
	class CDevice*		m_pDevice;
	ObjState			m_eObjState;

	map<wstring, CComponent*>	m_mapComponent;

protected:
	CPhysics*			m_pPhysics;


private:
	void	AddComponent();


public :
	void	Update_Component();
private :
	void	Release_Component();


public :
	virtual HRESULT	Init()			PURE;
	virtual int		Update()		PURE;
	virtual void	Render()		PURE;
	virtual void	Release()		PURE;


public:
	const CComponent*	GetComponent(const wstring&	_wstrComponentKey);

	ObjState	GetObjState()						{ return m_eObjState; }
	void		SetObjState(ObjState _eObjState)	{ m_eObjState = _eObjState; }

	CPhysics*	GetPhysics()					{ return m_pPhysics; }
	virtual void SetPos(const D3DXVECTOR3& _vPos)		{ m_pPhysics->m_vPos = _vPos; }
	virtual void SetDir(const D3DXVECTOR3& _vDir)		{ m_pPhysics->m_vDir = _vDir; }
	virtual D3DXVECTOR3* GetPos()		{ return &(m_pPhysics->m_vPos); }
	virtual D3DXVECTOR3* GetDir()		{ return &(m_pPhysics->m_vDir); }


protected:
	explicit CObj(CDevice* _pDevice);
public :
	virtual ~CObj();
};

#endif // Obj_h__
