/*!
 * \file Component.h
 * \date 2016/01/11 3:43
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

#ifndef Component_h__
#define Component_h__

class CComponent
{
public :
	virtual void			Update()	PURE;
private :
	virtual void			Release()	PURE;

public :
	explicit CComponent();
	virtual ~CComponent();
};

#endif // Component_h__
