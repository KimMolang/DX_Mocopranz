/*!
 * \file BackGround.h
 * \date 2016/02/11 19:52
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

#ifndef BackGround_h__
#define BackGround_h__

#include "Obj.h"


class CBuffer;
class CBackGround abstract : public CObj
{
protected:
	CBuffer*			m_pBuffer;


public:
	void	SetWorldMatrix(const D3DXVECTOR3& _vPos = D3DXVECTOR3(0.f, 0.f, 0.f),
		const D3DXVECTOR3& _vRadian = D3DXVECTOR3(0.f, 0.f, 0.f),
		const D3DXVECTOR3& _vScale = D3DXVECTOR3(1.f, 1.f, 1.f));


protected:
	explicit CBackGround(CDevice* _pDevice);
public:
	virtual ~CBackGround()	PURE;
};

#endif // BackGround_h__
