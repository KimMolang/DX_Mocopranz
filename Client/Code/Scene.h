/*!
 * \file Scene.h
 * \date 2015/12/08 11:38
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

#ifndef Scene_h__
#define Scene_h__

#include "Layer.h"

class CScene
{
protected:
	class CDevice*		m_pDevice;
	CLayer*				m_pLayer[CLayer::LAYERTYPE_END];

	class CCamera*		m_pMainCamera;
	

public:
	virtual HRESULT		Init()			PURE;
	virtual void		Update()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;

public :
	void Update_Layer();
	void Render_Layer();
private :
	void Release_Layer();


public:
	CScene(CDevice* _pDevice);
	~CScene();
};

#endif // Scene_h__


