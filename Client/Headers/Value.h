/*!
 * \file Value.h
 * \date 2015/12/06 3:16
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

#ifndef Value_h__
#define Value_h__

#include <atltypes.h>


const DWORD CLIENT_WINCX = 1280;
const DWORD CLIENT_WINCY = 720;

const DWORD TOOL_WINCX = 985;
const DWORD TOOL_WINCY = 610;

const CRect TAB_WINDOW_SIZE = CRect(5, 25, 12, 30);

const DWORD CLIENT_DEBUG_MODE_BASIC			= 0x00000001;
const DWORD CLIENT_DEBUG_MODE_NO_BG			= 0x00000002;
const DWORD CLIENT_DEBUG_MODE_NO_ANIMATION	= 0x00000004;


const WORD		MIN			= 64;
const WORD		MIDDLE		= 128;
const WORD		MAX			= 256;


const D3DXVECTOR3 g_vLook	= D3DXVECTOR3(0.f, 0.f, 1.f);

const WORD		HEXAHEDRON_POINT_NUM = 8;
const WORD		HEXAHEDRON_AXIS_NUM = 3;

const WORD		PAIR		= 2;


const WORD	MAX_USER_NUM	= 8;

const WORD	MAX_RECOSTER = 450;
const WORD	MAX_BULLET_NUM = 100;
const WORD	MAX_HP = 500;

const WORD	RECOSTER_GAUGE_FULL		= MAX_RECOSTER / 3;
const WORD	RECOSTER_GAUGE_THIRD	= RECOSTER_GAUGE_FULL / 3;

const WORD	RECOSTER_HEAL_HP		= 100;

const WORD	PROGRESS_RATE_ZONE_NUM	= 21;


#endif // Value_h__

