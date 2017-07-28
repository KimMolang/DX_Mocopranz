/*!
 * \file SkyBox.h
 * \date 2016/02/15 1:35
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

#ifndef SkyBox_h__
#define SkyBox_h__

#include "BackGround.h"


class CSkyBoxBuffer;
class CTexture;
//class CCameraObserver;
class CSkyBox : public CBackGround
{
private:
	CTexture*			m_pTexture;
	D3DXVECTOR3*		m_pTargetPos;

	//CCameraObserver*	m_pCameraObserver;


public:
	static CObj*	Create(CDevice* _pDevice, const wstring& _wstrTextureKey);

private:
	void	AddComponent(const wstring& _wstrTextureKey);

public:
	virtual HRESULT	Init();
	virtual int		Update();
	virtual void	Render();
	virtual void	Release();


public :
	void	SetTargetPos(D3DXVECTOR3* _pTargetPos)	{ m_pTargetPos = _pTargetPos; }


protected:
	explicit CSkyBox(CDevice* _pDevice);
public:
	virtual ~CSkyBox();
};

#endif // SkyBox_h__
