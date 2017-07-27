/*!
 * \file Renderer.h
 * \date 2016/01/11 1:44
 *
 * \author �����
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef Renderer_h__
#define Renderer_h__

#include "Scene.h"

class CDevice;
class CTextureShader;
class CRenderer
{
private :
	CDevice*		m_pDevice;
	CScene*			m_pScene;


public :
	// (����) �̰� static ���� �� ������?
	static DWORD	m_dwFPSCnt;
	static float	m_fTimer;


public :
	static CRenderer* Create(CDevice* _pDeviceClass);

public :
	void SetScene(CScene* _pScene)	{ m_pScene = _pScene; }

public :
	HRESULT	Init();
	void	Render();


private:
	explicit CRenderer(CDevice*);
public:
	~CRenderer(void);
};

#endif // Renderer_h__
