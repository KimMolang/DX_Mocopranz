#pragma once

#include "Include.h"


class CDevice
{
	DECLARE_SINGLETON(CDevice)

public :
	enum WinMode { WIN_MODE_FULL, WIN_MODE_WIN };

private :
	static const float COLOR_BACKBUFFER[COLOR_NUM];

private :
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;

	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D*		m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11BlendState*		m_pBlendState;

	
public:
	HRESULT		Init(WinMode _eWinMode = WIN_MODE_WIN);
	void		Release();

	void		Render_Begin();
	void		Render_End();

	void		Blend_Begin();
	void		Blend_End();

private :
	HRESULT		Init_Blend();


public :
	const ID3D11Device*			GetDevice()					{ return m_pDevice; }
	const ID3D11DeviceContext*	GetDeviceContext()			{ return m_pDeviceContext; }

	const IDXGISwapChain*			GetSwapChain()				{ return m_pSwapChain; }
	const ID3D11RenderTargetView*	GetRenderTargetView()		{ return m_pRenderTargetView; }
	const ID3D11Texture2D*			GetSDepthStencilBuffer()	{ return m_pDepthStencilBuffer; }
	const ID3D11DepthStencilView*	GetDepthStencilView()		{ return m_pDepthStencilView; }
	const ID3D11BlendState*			GetBlendState()				{ return m_pBlendState; }


private :
	explicit CDevice();
	~CDevice();
};

