#pragma once

class CDevice
{
private :
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;

	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D*		m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11BlendState*		m_pBlendState;
	
public:
	HRESULT		Init();
	void		Release();

	inline void		Render_Begin();
	inline void		Render_End();

	inline void		Blend_Begin();
	inline void		Blend_End();

private :
	HRESULT		Init_Blend();


public :
	inline ID3D11Device*			GetDevice()					{ return m_pDevice; }
	inline ID3D11DeviceContext*		GetDeviceContext()			{ return m_pDeviceContext; }

	inline IDXGISwapChain*			GetSwapChain()				{ return m_pSwapChain; }
	inline ID3D11RenderTargetView*	GetRenderTargetView()		{ return m_pRenderTargetView; }
	inline ID3D11Texture2D*			GetSDepthStencilBuffer()	{ return m_pDepthStencilBuffer; }
	inline ID3D11DepthStencilView*	GetDepthStencilView()		{ return m_pDepthStencilView; }
	inline ID3D11BlendState*		GetBlendState()				{ return m_pBlendState; }


public :
	explicit CDevice();
	~CDevice();
};

