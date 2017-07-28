/*!
 * \file Shader.h
 * \date 2016/01/30 18:23
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

#ifndef Shader_h__
#define Shader_h__

#include "Resource.h"

class CDevice;
class CShader abstract : public CResource
{
protected:
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11InputLayout*		m_pVertexLayout;

	ID3D11PixelShader*		m_pPixelShader;


public :
	virtual void	Render();

private :
	void			Release();

protected:
	explicit CShader(CDevice*);
public:
	virtual ~CShader()			PURE;
};

#endif // Shader_h__
