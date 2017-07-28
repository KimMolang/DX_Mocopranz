/*!
 * \file SkyBoxShader.h
 * \date 2016/02/15 2:13
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

#ifndef SkyBoxShader_h__
#define SkyBoxShader_h__

#include "Shader.h"

class CShaderSkyBox : public CShader
{
public:
	static CResource*		Create(CDevice*);
	virtual CResource*		Clone();

public:
	virtual HRESULT			Init();
	virtual void			Update();
private:
	virtual void			Release();


protected:
	explicit CShaderSkyBox(CDevice*);
public:
	virtual ~CShaderSkyBox();
};

#endif // SkyBoxShader_h__
