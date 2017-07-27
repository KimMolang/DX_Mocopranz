#pragma once
/*!
 * \file Timer.h
 * \date 2015/12/08 12:03
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

#ifndef Timer_h__
#define Timer_h__

#include "Include.h"


class CTimer
{
	DECLARE_SINGLETON(CTimer)

private :
	LARGE_INTEGER		m_liFrameTime;
	LARGE_INTEGER		m_liFixTime;
	LARGE_INTEGER		m_liLastTime;
	LARGE_INTEGER		m_liCpuTick;

	float				m_fTime;


public :
	void	Init();
	void	Update();

	const float	GetTime() { return m_fTime;  }


public:
	CTimer();
	~CTimer();
};


#endif // Timer_h__