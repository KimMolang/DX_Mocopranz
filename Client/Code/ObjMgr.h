/*!
 * \file ObjMgr.h
 * \date 2016/01/25 3:17
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

#ifndef ObjMgr_h__
#define ObjMgr_h__

#include "Layer.h"


class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CLayer*			m_pLayer[CLayer::LAYERTYPE_END];


public :
	void SetLayer(CLayer* _pLayer_Environment, CLayer* _pLayer_GameLogic, CLayer* _pLayer_UI)
	{
		m_pLayer[CLayer::LAYERTYPE_ENVIRONMENT] = _pLayer_Environment;
		m_pLayer[CLayer::LAYERTYPE_GAMELOGIC] = _pLayer_GameLogic;
		m_pLayer[CLayer::LAYERTYPE_UI] = _pLayer_UI;
	}
	void SetLayer_Evironment(CLayer* _pLayer)		{ m_pLayer[CLayer::LAYERTYPE_ENVIRONMENT] = _pLayer; }
	void SetLayer_GameLogic(CLayer* _pLayer)		{ m_pLayer[CLayer::LAYERTYPE_GAMELOGIC] = _pLayer; }
	void SetLayer_UI(CLayer* _pLayer)				{ m_pLayer[CLayer::LAYERTYPE_UI] = _pLayer; }

	void AddObj(const CLayer::LayerType& _eLayerType, const wstring& _wstrObjKey, CObj* _pObj);
	const CObj* GetObj(const CLayer::LayerType& _eLayerType, const wstring& _wstrObjKey, const int& _iIdx = 0);

public :
	void Release();

private :
	CObjMgr();
	~CObjMgr();
};


#endif // ObjMgr_h__
