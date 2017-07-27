/*!
 * \file SceneMgr.h
 * \date 2015/12/08 11:44
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

#ifndef SceneMgr_h__
#define SceneMgr_h__

#include "Include.h"

//#include "Loading.h"
//#include "Title.h"
//#include "Lobby.h"
//#include "Room.h"
//#include "InMap.h"


class CDevice;
class CScene;
class CRenderer;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public :
	enum SceneID
	{
		SCENE_ID_NONE,

		SCENE_ID_TITLE,
		SCENE_ID_LOBBY,
		SCENE_ID_ROOM,
		SCENE_ID_INMAP
	};

private :
	CDevice*		m_pDevice;

	SceneID			m_eCurScene;
	CScene*			m_pScene;
	bool			m_bSceneLoadingEnd;


	CRenderer*		m_pRenderer;

public :
	HRESULT		SetScene(SceneID _eSceneID);
	HRESULT		SetSceneAftherLoading();

	SceneID		GetScene()						{ return m_eCurScene; }
	bool		GetSceneLoadingEnd()			{ return m_bSceneLoadingEnd; }
	void		SetSceneLoadingEnd(bool _bEnd)	{ m_bSceneLoadingEnd = _bEnd; }

public :
	HRESULT		Init(CDevice* _pDevice);
	void		Update();
	void		Render();
	void		Release();

private:
	CSceneMgr();
	~CSceneMgr();
};



#endif // SceneMgr_h__

