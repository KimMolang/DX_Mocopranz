#pragma once

BEGIN(Engine)


class ENGINE_DLL GraphicDevice
{
	DECLARE_SINGLETON(GraphicDevice)

private:
	GraphicDevice();
public:
	~GraphicDevice();

public:
	enum EWinMode { WIN_MODE_FULL, WIN_MODE_WIN };

public:
	HRESULT	Init(const HWND _hWnd
		, const WORD& _wSizeX
		, const WORD& _wSizeY
		, const EWinMode _eWinMode = EWinMode::WIN_MODE_WIN);
private:
	HRESULT		Init_Blend();
public:
	inline void		Render_Begin();
	inline void		Render_End();

	inline void		Blend_Begin();
	inline void		Blend_End();

	inline void		Release();

public:
	inline ID3D11Device*			GetDevice() { return m_pDevice; }
	inline ID3D11DeviceContext*		GetDeviceContext() { return m_pDeviceContext; }

	inline IDXGISwapChain*			GetSwapChain() { return m_pSwapChain; }
	inline ID3D11RenderTargetView*	GetRenderTargetView() { return m_pRenderTargetView; }
	inline ID3D11Texture2D*			GetSDepthStencilBuffer() { return m_pDepthStencilBuffer; }
	inline ID3D11DepthStencilView*	GetDepthStencilView() { return m_pDepthStencilView; }
	inline ID3D11BlendState*		GetBlendState() { return m_pBlendState; }

private:
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;

	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D*		m_pDepthStencilBuffer;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11BlendState*		m_pBlendState;
};


END