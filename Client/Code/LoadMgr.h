/*!
* \file LoadMgr.h
* \date 2016/03/01 23:54
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

#ifndef LoadMgr_h__
#define LoadMgr_h__

#include "Include.h"
#include "SceneMgr.h"


class CDevice;
class CTexture;
class CModelBuffer;
class CLoadMgr
{
	DECLARE_SINGLETON(CLoadMgr)

private:
	enum LoadResourceType
	{
		LOAD_RESOURCE_TYPE_MODEL,
		LOAD_RESOURCE_TYPE_TEXTURE,
		LOAD_RESOURCE_TYPE_ANI
	};

public:
	HRESULT	LoadResource(CDevice*, const CSceneMgr::SceneID&);
//	void	LoadUI(CDevice*, const CSceneMgr::SceneID&, CLayer**);
//	void	LoadMap(CDevice*, const MapType& _eMapType, CLayer**, CLayer**);
//
//private:
//	HRESULT	LoadResourceByFile(CDevice*,
//		const LoadResourceType&, const wstring&);


private:
	CLoadMgr();
	~CLoadMgr();
};

#endif // LoadMgr_h__
