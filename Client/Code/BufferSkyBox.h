/*!
* \file SkyBoxColor.h
* \date 2016/01/24 3:23
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

#ifndef SkyBoxBuffer_h__
#define SkyBoxBuffer_h__

#include "Buffer.h"

class CShaderSkyBox;
class CBufferSkyBox : public CBuffer
{
private:
	CShaderSkyBox*				m_pSkyBoxShader;
	ID3D11DepthStencilState*	m_pDepthStencilState;

public:
	static CResource*		Create(CDevice*);
	virtual CResource*		Clone();

public:
	virtual HRESULT			Init();
	virtual void			Update();
	virtual void			Render();
private:
	virtual void			Release();


private:
	void			Init_Vtx();
	void			Init_Idx();
	void			Init_ShaderSkyBox();

	virtual void	CreateRasterizerState();


protected:
	explicit CBufferSkyBox(CDevice*);
public:
	virtual ~CBufferSkyBox();
};

#endif // SkyBoxBuffer_h__
