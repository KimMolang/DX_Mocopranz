/*!
 * \file Resource.h
 * \date 2016/01/11 4:01
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

#ifndef Resource_h__
#define Resource_h__

#include "Component.h"

class CDevice;
class CResource : public CComponent
{
protected:
	CDevice*				m_pDevice;
	WORD*					m_pRefCnt;

public:
	virtual CResource*		Clone()		PURE;
	virtual void			Update()	PURE;
private :
	virtual void			Release()	PURE;

protected:
	void Release_RefCnt();

protected:
	CResource(CDevice*);
public :
	virtual ~CResource();
};

#endif // Resource_h__
